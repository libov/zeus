// \author Libov Vladyslav
// libov@mail.desy.de

// system includes
#include<iostream>
#include<fstream>
#include <exception>
using namespace std;

// ROOT includes
#include<TCollection.h>
#include<TMath.h>
#include<TFile.h>
#include<TLorentzVector.h>
#include<TVector3.h>

// my includes
#include <inc/TMiniNtupleAnalyzer.h>
#include <inc/TGlobalBin.h>
#include <inc/TVertex.h>

void TMiniNtupleAnalyzer::TrackingEfficiency() {

    // get a pointer to inclusive bin
    TGlobalBin      *inclusiveBin = NULL;
    TIter           Iter_TGlobalBin_event(fList_TGlobalBin);
    inclusiveBin = (TGlobalBin*) Iter_TGlobalBin_event.Next();
    if ( (inclusiveBin == NULL) || (inclusiveBin -> BinName != "bin1")) {
        cout << "ERROR: not able to get the global bin" << endl;
        abort();
    }
    inclusiveBin->SetWeightingFactor(1);

    // helping variable
    Int_t  Nevents;
    // check if user selected to run in a test mode
    unsigned    first_event=0;
    if (fTestMode) {
        Nevents = fTestNumberOfEvents;
        first_event = fTestFirstEvent;
    } else {
        Nevents = fNevents;
    }

    // let user know how many events will be processed
    cout << "INFO: " << Nevents << " events will be processed" << endl;

    // ********************************************************************************************
    // ********************************************************************************************
    // ************************************* MAIN EVENT LOOP **************************************
    // ********************************************************************************************
    // ********************************************************************************************
    for (unsigned i=first_event; i < first_event+Nevents; i++) {

        // print number of processed events every n events;
        if ( i % fPrintingFreq == 0 )   cout<< " processing event " << i << endl;

        // try to get an entry from the chain
        // (at some point I had an bad_alloc exception while calling this,
        // that's why this try-catch block is here)
        try {
            // realized it's quite a dangerous function! if the array dimensions are smaller than what is in the Ntuple
            // there will be a buffer overflow - and that can lead to any consequences - namely overwriting
            // some variables with arbitrary values; in the best case, the program crashes, in the worst - 
            // gives wrong results.
            fChain->GetEntry(i);
        } catch(exception& e){
            cout << " Failed to get entry. Exception: " << e.what() << endl;
            cout << " Terminating." << endl;
            abort();
        }

        // DIS event selection
        if (!IsDIS_Rho()) continue;

        // selection of rho mesons

        // calculate number of non-electron ZTT tracks
        // belonging to various categories
        fPrimary_ZTT_tracks = 0;
        fLong_primary_ZTT_tracks = 0;
        fLong_ZTT_tracks = 0;
        // number of tracks identified with an electron (should be exactly 1)
        unsigned   electron_tracks = 0;
        // minimal distance from SA track to any other long track
        Double_t    Rmin = 10000;
        for (int j = 0; j < Trk_ntracks; j++) {
            if (Trk_id[j] == Sitrknr[0]) {
                electron_tracks++;
                continue;
            }
            Int_t   inner = Trk_layinner[j];
            Int_t   outer = Trk_layouter[j];
            bool    long_track = ((inner<=1) && (outer>=3));
            TVector3    track(Trk_px[j], Trk_py[j], Trk_pz[j]);
            if (long_track) fLong_ZTT_tracks++;
            if (Trk_prim_vtx[j] == 1) fPrimary_ZTT_tracks++;
            if ( (Trk_prim_vtx[j] == 1) && (long_track) ) fLong_primary_ZTT_tracks++;

            // for events with 1 standalone track, find the distance to the closest track
            if (long_track && (Trkmsa_ntracks == 1) ) {
                TVector3    long_track(Trk_px[j], Trk_py[j], Trk_pz[j]);
                TVector3    MSA_track(Trkmsa_px[0], Trkmsa_py[0], Trkmsa_pz[0]);
                Double_t    dR = long_track.DeltaR(MSA_track);
                if (dR < Rmin) Rmin = dR;
            }
        }

        // sanity check
        if (electron_tracks>1) {
            cout << "ERROR: several electron candidates in the tracking block" << endl;
            abort();
        }

        // find also a true distance between daughter pions
        Double_t DeltaR;
        if (fIsMC) {
            TLorentzVector pi_plus = get_pi_plus();
            TLorentzVector pi_minus = get_pi_minus();
            DeltaR = pi_plus.DeltaR(pi_minus);
        }

        // for MC, fill fate points of pions
        if (fIsMC) FillPionsFatePoint();

        // loop over all zufos to calculate the total energy
        fNonElectronEnergyZufo = 0;
        fElectronEnergyZufo = 0;
        fNonTrackEnergyZufo = 0;

        // look for energetic island not matched to any track(based on the classification in ZUFO block)
        Int_t   zufo_id_electron = -1;
        for (int zufo=0; zufo<Nzufos; zufo++) {

            // define the type of the zufo
            Int_t   type = Tufo[zufo][0];

            // sanity check
            if (type < 0) {
                cout << "ERROR: zufo type < 0" << endl;
                abort();
            }

            // noise threshold
            bool not_noise = (Zufo[zufo][3]>0.5);

            // count energy coming not from the electron
            if ( not_noise && (type < 3000) ) fNonElectronEnergyZufo += Zufo[zufo][3];

            // count energy from electron
            if ( not_noise && (type >= 3000) ) fElectronEnergyZufo += Zufo[zufo][3];

            // get an id of the electron zufo
            if ((type >= 3000) && (zufo_id_electron != -1)) {
                cout << "ERROR: more than 1 electron found within ZUFOs" << endl;
                abort();
            }
            if ((type >= 3000) && (zufo_id_electron == -1)) zufo_id_electron = zufo;

            // define whether this zufo has a track matched to it
            bool zufo_no_track = ((type==31) || (type==32) || (type==1031) || (type==1032) || (type==1131) || (type==1132));

            // if the energy of the zufo is above the noise threshold and has no track matched - add it to the sum
            if (not_noise && zufo_no_track) fNonTrackEnergyZufo += Zufo[zufo][3];
        }

        // event printout for events with extra energy in the calorimeter
        if ( (fNonTrackEnergyZufo > 0.5) && (fDebugPrintout) ) {
            cout << Eventnr << endl;
            cout << "Nzufos= " << Nzufos << endl;
            for (int j=0; j<Nzufos; j++) {
                cout << "INFO: type: " << Tufo[j][0] << " energy: " << Zufo[j][3] << endl;
            }
        }

        // create vectors to store rho and daughters 4vectors
        vector<TLorentzVector> cand_classI;
        vector<TLorentzVector> cand_classII;
        cand_classI.clear();
        cand_classII.clear();

        // reset track ids
        fTrack1Id = -1;
        fTrack2Id = -1;

        // define class I and class II criteria

        // class I: exactly 2 primary tracks in event
        bool    classI = ( (fPrimary_ZTT_tracks==2) && (fLong_ZTT_tracks==2) && ((Trk_ntracks-electron_tracks) == 2) );

        // classII: exactly 1 primary track and exactly 1 SA track
        bool    classII = ((fPrimary_ZTT_tracks==1) && (Trkmsa_ntracks==1));

        // sanity check
        if ( classI && classII ) {
            cout << "ERROR: event is classified as classI and classII!" << endl;
            abort();
        }

        // skip if event doesn't satisfy criteria for classI or classII
        if ( !(classI || classII) ) continue;

        // search for ZTT-ZTT candidates (class I) and ZTT-MSA candidates (class II)
        if ( classI ) FindRho(cand_classI, true);
        if ( classII ) FindRho(cand_classII, false);

        // skip if no suitable rho candidate was found
        if (classI && (cand_classI.size()==0) ) continue;
        if (classII && (cand_classII.size()==0) ) continue;

        // now that we know the ids of the rho decay products, can apply the elasticity cut
        fUnmatchedIslandsEnergy = 0;
        for (int isl = 0; isl<Nisl; isl++) {
            // skip if the island is below the noise threshold
            if (Eisl[isl]<0.5) continue;
            // skip if this island is due to the scattered electron
            if ( (zufo_id_electron != -1) && (((Tufo[zufo_id_electron][2]-1) == isl) || ((Tufo[zufo_id_electron][3]-1) == isl))) continue;
            // get DCA of this island to the track (classI: one of the two which is closer; classII: to the only long ZTT)
            Float_t min_dca = 9999;
            // relevant for class II only
            Double_t dR = 9999;
            if (classI) {
                Double_t    DCA1 = getIslandDCA(isl, fTrack1Id);
                if (min_dca > DCA1) min_dca = DCA1;
                Double_t    DCA2 = getIslandDCA(isl, fTrack2Id);
                if (min_dca > DCA2) min_dca = DCA2;
            } else if (classII) {
                Double_t    DCA1 = getIslandDCA(isl, fTrack1Id);
                if (min_dca > DCA1) min_dca = DCA1;
                // get a distance in eta-phi between an island and MVDSA track
                TVector3 island(Xisl[isl] - Xvtx, Yisl[isl] - Yvtx, Zisl[isl] - Zvtx);
                TVector3 msa_track(Trkmsa_px[0], Trkmsa_py[0], Trkmsa_pz[0]);
                dR = island.DeltaR(msa_track);
            }
            inclusiveBin -> FillHistogram("min_dca", min_dca);
            if (classI) if (min_dca > 30) fUnmatchedIslandsEnergy += Eisl[isl];
            if (classII) if ( (min_dca > 30) && (dR>0.5) ) fUnmatchedIslandsEnergy += Eisl[isl];
        }

        // other ways to define the elasticity criterion for classII: allowing islands around all long tracks
        Float_t unmatched_islands_energy_classII_relaxed = 0;
        if (classII) {
            for (int isl = 0; isl<Nisl; isl++) {
                // skip if the island is below the noise threshold
                if (Eisl[isl]<0.5) continue;
                // skip if this island is due to the scattered electron
                if ( (zufo_id_electron != -1) && (((Tufo[zufo_id_electron][2]-1) == isl) || ((Tufo[zufo_id_electron][3]-1) == isl))) continue;
                // get DCA of this island to the track (classI: one of the two which is closer; classII: to the only long ZTT)
                Float_t min_dca = 9999;
                for (int j=0; j<Trk_ntracks; j++) {
                    if (Trk_id[j] == Sitrknr[0]) {
                        electron_tracks++;
                        continue;
                    }
                    if ( (Trk_layinner[j]>1) || (Trk_layouter[j]<3) ) continue;
                    Double_t    DCA = getIslandDCA(isl, j);
                    if (min_dca > DCA) min_dca = DCA;
                }
                if (min_dca > 30) unmatched_islands_energy_classII_relaxed += Eisl[isl];
            }
        }

        // same requirement for both classI and classII,
        // however the definition of fUnmatchedIslandsEnergy is different for both cases
        if (classI || classII) if (fUnmatchedIslandsEnergy > 0) continue;

        // loop over long, non-primary tracks and calculate the sum of track momenta:
        // this is what we call momentum excess
        Float_t     scalar_pt_sum=0;
        TVector3    vector_p_sum(0,0,0);

        for (int j=0; j<Trk_ntracks; j++) {
            // skip if electron track
            if (Trk_id[j] == Sitrknr[0]) {
                electron_tracks++;
                continue;
            }
            // skip if not long track starting in the 1st CTD layer or MVD
            if ( (Trk_layinner[j]>1) || (Trk_layouter[j]<3) ) continue;
            // skip if primary
            if (Trk_prim_vtx[j] == 1) continue;
            TVector3    track(Trk_px[j], Trk_py[j], Trk_pz[j]);
            TVector2    track_2d = track.XYvector();
            scalar_pt_sum += track.Perp();
            vector_p_sum += track;
        }

        fPtExcess = 0;
        fPExcess = 0;
        fScalarPtExcess = 0;
        if (classII) {
            TVector3 track(Trkmsa_px[0], Trkmsa_py[0], Trkmsa_pz[0]);
            fScalarPtExcess = scalar_pt_sum - track.Perp();
            fPtExcess = vector_p_sum.Perp() - track.Perp();
            fPExcess = vector_p_sum.Mag() - track.Mag();
        } else if (classI) {
            fScalarPtExcess = scalar_pt_sum;
            fPtExcess = vector_p_sum.Perp();
            fPExcess = vector_p_sum.Mag();
        }

        // fill trigger histograms
        // loop over all FLT slots, 0-63
        for (int slot=0; slot<64; slot++) {
            int id = -1;
            // 0-31: 1st element of array (i.e. [0])
            // 32-63: 2nd element of array (i.e. [1])
            if ( (slot>=0) && (slot<=31) ) id = 0;
            if ( (slot>=32) && (slot<=63) ) id = 1;
            // sanity check
            if (id == -1) abort();
            // check whether this trigger slot fired
            bool flt_slot_fired = (bool) ( (Fltpsw[id] >> slot) & 1 );
            // fill the histogram if yes
            if (flt_slot_fired) if (classI) inclusiveBin -> FillHistogram("FLT_classI", slot);
            if (flt_slot_fired) if (classII) inclusiveBin -> FillHistogram("FLT_classII", slot);
        }

        // now fill the histograms
        if (classI) FillRhoHistograms (cand_classI, true);
        if (classII) FillRhoHistograms (cand_classII, false);

    } // end loop over events

    // store the histograms to file
    this->WriteHistograms();
}

void TMiniNtupleAnalyzer::FindRho(vector<TLorentzVector> &cand, bool  classI) {

    // classI = true: look for rho candidates with both tracks ZTT (classI)
    // classI = false: look for rho candidates with ZTT and standalone track (classII)

    // clear the array
    cand.clear();

    // loop over track1 candidates; 1st track is always ZTT
    for (int t1 = 0; t1 < Trk_ntracks; t1++) {

        // ZTT quality cuts for the track1
        if (Trk_id[t1] == Sitrknr[0]) continue;
        if (Trk_layouter[t1] < 3) continue;
        if (Trk_prim_vtx[t1] != 1) continue;
        if (Trk_imppar[t1]>0.2) continue;

        // create a 4-vector for this track
        TLorentzVector track1;
        track1.SetXYZM(Trk_px[t1], Trk_py[t1], Trk_pz[t1], M_PION);

        // kinematics
        if (track1.Pt()<0.2) continue;
        if ((track1.Theta()<0.44) || (track1.Theta()>2.7)) continue;

        if (classI) {
            // loop over track2 candidates
            for (int t2 = t1+1; t2 < Trk_ntracks; t2++) {

                // ZTT quality cuts for the track2
                if (Trk_id[t2] == Sitrknr[0]) continue;
                if (Trk_layouter[t2] < 3) continue;
                if (Trk_prim_vtx[t2] != 1) continue;
                if (Trk_imppar[t2]>0.2) continue;

                // tracks should be of opposite charge
                if ((Trk_charge[t1]*Trk_charge[t2]) > 0) continue;

                // create a 4-vector for this track
                TLorentzVector track2;
                track2.SetXYZM(Trk_px[t2], Trk_py[t2], Trk_pz[t2], M_PION);
                // kinematics
                if (track2.Pt()<0.2) continue;
                if ((track2.Theta()<0.44) || (track2.Theta()>2.7)) continue;

                // found a suitable track pair
                // reconstruct rho candidate now
                TLorentzVector rho = track1 + track2;

                // get phi mass: kaon hypothesis
                TLorentzVector kaon1, kaon2, phi;
                kaon1.SetXYZM(Trk_px[t1], Trk_py[t1], Trk_pz[t1], M_KAON);
                kaon2.SetXYZM(Trk_px[t2], Trk_py[t2], Trk_pz[t2], M_KAON);
                phi = kaon1 + kaon2;
                cand.push_back(rho);
                // write first pi+ and then pi- (class I)
                if ( (Trk_charge[t1]>0) && (Trk_charge[t2]<0) ) {
                    cand.push_back(track1);
                    cand.push_back(track2);
                    fTrack1Id = t1;
                    fTrack2Id = t2;
                } else if ( (Trk_charge[t1]<0) && (Trk_charge[t2]>0) ) {
                    cand.push_back(track2);
                    cand.push_back(track1);
                    fTrack1Id = t2;
                    fTrack2Id = t1;
                } else {
                    cout << "ERROR: wrong charge selection" << endl;
                    abort();
                }
                cand.push_back(phi);
                cand.push_back(kaon1);
                cand.push_back(kaon2);


            } // end loop over track2 candidates
        } else {
            // loop over track2 candidates
            for (int t2 = 0; t2 < Trkmsa_ntracks; t2++) {

                // MVD SA quality cuts for the track2
                if (Trkmsa_imppar[t2]>0.2) continue;
                Int_t   nhits = Trkmsa_nbz[t2] + Trkmsa_nbr[t2];
                if (nhits<5) continue;

                // tracks should be of opposite charge
                if ((Trkmsa_charge[t2]*Trk_charge[t1]) > 0) continue;

                // create a 4-vector for this track
                TLorentzVector track2;
                track2.SetXYZM(Trkmsa_px[t2], Trkmsa_py[t2], Trkmsa_pz[t2], M_PION);
                // kinematics
                if (track2.Pt()<0.2) continue;
                if ((track2.Theta()<0.44) || (track2.Theta()>2.7)) continue;

                // found a suitable track pair
                // reconstruct rho candidate now
                TLorentzVector rho = track1 + track2;

                // get phi mass: kaon hypothesis
                TLorentzVector kaon1, kaon2, phi;
                kaon1.SetXYZM(Trk_px[t1], Trk_py[t1], Trk_pz[t1], M_KAON);
                kaon2.SetXYZM(Trkmsa_px[t2], Trkmsa_py[t2], Trkmsa_pz[t2], M_KAON);
                phi = kaon1 + kaon2;
                cand.push_back(rho);
                // write first ZTT and then MSA  - class II
                cand.push_back(track1);
                cand.push_back(track2);
                cand.push_back(phi);
                cand.push_back(kaon1);
                cand.push_back(kaon2);
                fTrack1Id = t1;
                fTrack2Id = t2;
                if (fTrack2Id != 0 ) abort();
            } // end loop over track2 candidates
        } // end of if (classI) statement
    } // end loop over track1 candidates
}

void TMiniNtupleAnalyzer::FillRhoHistograms(vector<TLorentzVector> &cand, bool  classI) {

        // check whether a candidate was found
        if (cand.size() == 0) return;

        // pick up the relevant vectors
        TLorentzVector  rho = cand[0];
        TLorentzVector  pi1 = cand[1];
        TLorentzVector  pi2 = cand[2];
        TLorentzVector  phi = cand[3];

        // needed for Ecm determination
        TLorentzVector  proton_rest;
        proton_rest.SetXYZM(0, 0, 0, M_PROTON);

        // number of superlayers for ZTT tracks
        unsigned layout_nr_1= 0;
        if (Trk_layinner[fTrack1Id] == 0) layout_nr_1 = Trk_layouter[fTrack1Id];
        else layout_nr_1 = Trk_layouter[fTrack1Id] - Trk_layinner[fTrack1Id] + 1;
        unsigned layout_nr_2= 0;
        if (Trk_layinner[fTrack2Id] == 0) layout_nr_2 = Trk_layouter[fTrack2Id];
        else layout_nr_2 = Trk_layouter[fTrack2Id] - Trk_layinner[fTrack2Id] + 1;

        // *********************************
        // ******* determine weights *******
        // *********************************

        // rho phi reweighting
        Double_t    weight_rho_phi = 1;
        if (fIsMC && fApplyRhoPhiReweighting) {
            TLorentzVector rho = get_pi_plus() + get_pi_minus();
            weight_rho_phi = getRhoPhiWeight(rho.Phi());
        }

        // cos theta* reweighting
        Double_t    weight_cos_theta_star = 1;
        if (fIsMC && fApplyThetaStarReweighting) {
            TLorentzVector pi_plus = get_pi_plus();
            TLorentzVector pi_minus = get_pi_minus();
            TLorentzVector rho = pi_plus + pi_minus;
            Double_t cos_theta_h = get_cos_theta_star(pi_plus, pi_minus);
            weight_cos_theta_star = get_cos_theta_star_weight(cos_theta_h);
        }

        Double_t    TOTAL_WEIGHT = weight_rho_phi * weight_cos_theta_star;

        // now fill the histograms
        // loop over Global Bins and if this event satisfies bin's criteria - fill histograms that belong to the bin
        TGlobalBin  *cGlobalBin;
        TIter       Iter_TGlobalBin(fList_TGlobalBin);
        while ((cGlobalBin=(TGlobalBin*) Iter_TGlobalBin.Next())) {

            // check if event satisfies bin's criteria on the event level
            Bool_t GlobalBinFired=cGlobalBin->CheckGlobalBin(kEventVar);
            if (!GlobalBinFired) continue;

            fHistogramsFile->cd(cGlobalBin->BinName);

            // set factor to unity - no reweighting
            cGlobalBin -> SetWeightingFactor(1);

            // apply weight for MC
            if (fIsMC) cGlobalBin -> SetWeightingFactor (TOTAL_WEIGHT);

            // the order of histogram filling
            // 1. rho/phi/event histograms; for binning, we use the information of the 1st pion
            // one could alternatively use pi2, the 2nd pion, or choose some particular charge
            // sign. here we just do the simplest thing, i.e. picking up randomly one of the two
            // pions for binning
            // 2. pion histograms; there's no ambiguity here; for each pion its information is
            // used for binning

            // phi, rho histograms

            // set fPionThetaReco variable so that CheckGlobalBin can work (as discussed above)
            fPionThetaReco = pi1.Theta();
            fPionPhiReco = pi1.Phi();

            // fill the phi mass
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (classI) cGlobalBin->FillHistogram("phi_mass_classI", phi.M());
                if (!classI) cGlobalBin->FillHistogram("phi_mass_classII", phi.M());
            }
            // skip if kaon-kaon hypothesis is consistent with phi
            if ( (phi.M()>1.012) && (phi.M()<1.028) ) continue;

            // fill the rho mass
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (classI) {
                    cGlobalBin->FillHistogram("rho_mass_classI", rho.M());
                    cGlobalBin->FillHistogram("rho_mass_signal_classI", rho.M());
                    if (rho.Pt()<1.5) cGlobalBin->FillHistogram("rho_mass_lowpt_classI", rho.M());
                    if (rho.Pt()>=1.5) cGlobalBin->FillHistogram("rho_mass_highpt_classI", rho.M());
                }
                if (!classI) {
                    cGlobalBin->FillHistogram("rho_mass_classII", rho.M());
                    cGlobalBin->FillHistogram("rho_mass_signal_classII", rho.M());
                    if (rho.Pt()<1.5) cGlobalBin->FillHistogram("rho_mass_lowpt_classII", rho.M());
                    if (rho.Pt()>=1.5) cGlobalBin->FillHistogram("rho_mass_highpt_classII", rho.M());
                }
            }

            if (!classI) {
                if (fPExcess>0) cGlobalBin->FillHistogram("rho_mass_background_classII", rho.M());
            } else if (classI && (fLong_ZTT_tracks>2)) {
                if (fPExcess>0.5) cGlobalBin->FillHistogram("rho_mass_background_classI", rho.M());
            }

            // skip if not in the peak region
            if ( (rho.M()<0.6) || (rho.M()>1.1) ) continue;

            // debug printouts
            if ((!classI) &&  (cGlobalBin -> BinName == "bin1")) {
                cout << "Runnr= "<<Runnr<<" Eventnr= "<<Eventnr<<" Trk_ntracks= "<<Trk_ntracks;
                cout << " fLong_ZTT_tracks= "<<fLong_ZTT_tracks<<" fPrimary_ZTT_tracks= "<<fPrimary_ZTT_tracks<<endl;
                cout << "MVDSA track momentum: " << Trkmsa_px[0] << ", " << Trkmsa_py[0] << ", " << Trkmsa_pz[0];
                TVector3 msa(Trkmsa_px[0], Trkmsa_py[0], Trkmsa_pz[0]);
                cout << " (p= " <<msa.Mag() << ", pt= "<<msa.Perp()<<")"<<endl;
                cout << " (phi= " <<msa.Phi() << ", theta= "<<msa.Theta()<<")"<<endl;
            }

            if (!classI) {
                for (int j=0; j<Trk_ntracks; j++) {
                    // skip if electron track
                    if (Trk_id[j] == Sitrknr[0]) continue;
                    // skip if not long track starting in the 1st CTD layer or MVD
                    if ( (Trk_layinner[j]>1) || (Trk_layouter[j]<3) ) continue;
                    // skip if primary
                    if (Trk_prim_vtx[j] == 1) continue;
                    cGlobalBin->FillHistogram("long_tracks_imppar_classII", Trk_imppar[j]);
                    cGlobalBin->FillHistogram("long_tracks_imppar_fine_classII", Trk_imppar[j]);
                    if (fLong_ZTT_tracks==2) {
                        cGlobalBin->FillHistogram("long_tracks_imppar_2longTracks_classII", Trk_imppar[j]);
                        cGlobalBin->FillHistogram("long_tracks_imppar_fine_2longTracks_classII", Trk_imppar[j]);
                    }
                    if (fLong_ZTT_tracks==3) {
                        cGlobalBin->FillHistogram("long_tracks_imppar_3longTracks_classII", Trk_imppar[j]);
                        cGlobalBin->FillHistogram("long_tracks_imppar_fine_3longTracks_classII", Trk_imppar[j]);
                    }
                }
            }

            cGlobalBin->FillHistogram("NonElectronEnergyZufo", fNonElectronEnergyZufo);
            cGlobalBin->FillHistogram("ElectronEnergyZufo", fElectronEnergyZufo);
            cGlobalBin->FillHistogram("NonTrackEnergyZufo", fNonTrackEnergyZufo);
            cGlobalBin->FillHistogram("fUnmatchedIslandsEnergy", fUnmatchedIslandsEnergy);

            if (!classI) {
                cGlobalBin->FillHistogram("PtExcess_classII", fPtExcess);
                cGlobalBin->FillHistogram("PExcess_classII", fPExcess);
                cGlobalBin->FillHistogram("ScalarPtExcess_classII", fScalarPtExcess);
            } else if (classI && (Trk_ntracks>2)) {
                cGlobalBin->FillHistogram("PtExcess_classI", fPtExcess);
                cGlobalBin->FillHistogram("PExcess_classI", fPExcess);
                cGlobalBin->FillHistogram("ScalarPtExcess_classI", fScalarPtExcess);
            }

            // for MC: get event class,see the definition in getRhoEventClass()
            int event_class;
            if (fIsMC) event_class = getRhoEventClass();

            // *****************************************
            // ********** event histograms ************
            // *****************************************

            if ( classI ) {
                // number of tracks
                cGlobalBin->FillHistogram("Trk_ntracks_classI", Trk_ntracks);
                cGlobalBin->FillHistogram("Trkmsa_ntracks_classI", Trkmsa_ntracks);
                cGlobalBin->FillHistogram("primary_ZTT_tracks_classI", fPrimary_ZTT_tracks);
                cGlobalBin->FillHistogram("long_primary_ZTT_tracks_classI", fLong_primary_ZTT_tracks);
                cGlobalBin->FillHistogram("long_ZTT_tracks_classI", fLong_ZTT_tracks);
                // primary vertex
                cGlobalBin->FillHistogram("Xvtx_classI", Xvtx);
                cGlobalBin->FillHistogram("Yvtx_classI", Yvtx);
                cGlobalBin->FillHistogram("Zvtx_classI", Zvtx);
                // DIS and electron variables
                cGlobalBin->FillHistogram("q2da_classI", Siq2da[0]);
                cGlobalBin->FillHistogram("yda_classI", Siyda[0]);
                cGlobalBin->FillHistogram("Sith_classI", Sith[0]);
                cGlobalBin->FillHistogram("Siph_classI", Siph[0]);
                cGlobalBin->FillHistogram("Siecorr_classI", Siecorr[0][2]);
                cGlobalBin->FillHistogram("Sipos_x_classI", Sipos[0][0]);
                cGlobalBin->FillHistogram("Sipos_y_classI", Sipos[0][1]);
                // zufos
                cGlobalBin->FillHistogram("Nzufos_classI", Nzufos);
                for (int j=0; j<Nzufos; j++) {
                    cGlobalBin->FillHistogram("Tufo_classI", Tufo[j][0]);
                }
                // for MC only: fill event class as determined from the true level
                if (fIsMC) cGlobalBin->FillHistogram("event_trueclass_classI", event_class);
            } else {
                // number of tracks
                cGlobalBin->FillHistogram("Trk_ntracks_classII", Trk_ntracks);
                cGlobalBin->FillHistogram("Trkmsa_ntracks_classII", Trkmsa_ntracks);
                cGlobalBin->FillHistogram("primary_ZTT_tracks_classII", fPrimary_ZTT_tracks);
                cGlobalBin->FillHistogram("long_primary_ZTT_tracks_classII", fLong_primary_ZTT_tracks);
                cGlobalBin->FillHistogram("long_ZTT_tracks_classII", fLong_ZTT_tracks);
                // primary vertex
                cGlobalBin->FillHistogram("Xvtx_classII", Xvtx);
                cGlobalBin->FillHistogram("Yvtx_classII", Yvtx);
                cGlobalBin->FillHistogram("Zvtx_classII", Zvtx);
                // DIS and electron variables
                cGlobalBin->FillHistogram("q2da_classII", Siq2da[0]);
                cGlobalBin->FillHistogram("yda_classII", Siyda[0]);
                cGlobalBin->FillHistogram("Sith_classII", Sith[0]);
                cGlobalBin->FillHistogram("Siph_classII", Siph[0]);
                cGlobalBin->FillHistogram("Siecorr_classII", Siecorr[0][2]);
                cGlobalBin->FillHistogram("Sipos_x_classII", Sipos[0][0]);
                cGlobalBin->FillHistogram("Sipos_y_classII", Sipos[0][1]);
                // zufos
                cGlobalBin->FillHistogram("Nzufos_classII", Nzufos);
                for (int j=0; j<Nzufos; j++) {
                    cGlobalBin->FillHistogram("Tufo_classII", Tufo[j][0]);
                }
                // for MC only: fill event class as determined from the true level
                if (fIsMC) cGlobalBin->FillHistogram("event_trueclass_classII", event_class);
            }

            // *****************************************
            // ************ rho histograms *************
            // *****************************************

            Double_t    dPhi = TMath::Abs(pi1.DeltaPhi(pi2));
            Double_t    dTheta = TMath::Abs(pi1.Theta() - pi2.Theta());
            Double_t    dPt = TMath::Abs(pi1.Pt() - pi2.Pt());
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (classI) {
                    cGlobalBin->FillHistogram("rho_pt_classI", rho.Pt());
                    cGlobalBin->FillHistogram("rho_theta_classI", rho.Theta());
                    cGlobalBin->FillHistogram("rho_phi_classI", rho.Phi());
                    cGlobalBin->FillHistogram("dPt_classI", dPt);
                    cGlobalBin->FillHistogram("dTheta_classI", dTheta);
                    cGlobalBin->FillHistogram("dPhi_classI", dPhi);
                    cGlobalBin->FillHistogram("cos_theta_star_classI", get_cos_theta_star(pi1, pi2));
                    cGlobalBin->FillHistogram("PHI_h_classI", get_PHI_h(rho, true));
                    cGlobalBin->FillHistogram("cos_theta_h_classI", get_cos_theta_h(pi1, pi2, true));
                    cGlobalBin->FillHistogram("phi_h_classI",  get_phi_h(pi1, pi2, true));
                } else {
                    cGlobalBin->FillHistogram("rho_pt_classII", rho.Pt());
                    cGlobalBin->FillHistogram("rho_theta_classII", rho.Theta());
                    cGlobalBin->FillHistogram("rho_phi_classII", rho.Phi());
                    cGlobalBin->FillHistogram("dPt_classII", dPt);
                    cGlobalBin->FillHistogram("dTheta_classII", dTheta);
                    cGlobalBin->FillHistogram("dPhi_classII", dPhi);
                    cGlobalBin->FillHistogram("cos_theta_star_classII", get_cos_theta_star(pi1, pi2));
                    cGlobalBin->FillHistogram("PHI_h_classII", get_PHI_h(rho, true));
                    cGlobalBin->FillHistogram("cos_theta_h_classII", get_cos_theta_h(pi1, pi2, true));
                    cGlobalBin->FillHistogram("phi_h_classII",  get_phi_h(pi1, pi2, true));
                }
            }

            // *****************************************
            // ******* pion histograms, 1st pion *******
            // *****************************************

            // set fPionThetaReco variable so that CheckGlobalBin can work
            fPionThetaReco = pi1.Theta();
            fPionPhiReco = pi1.Phi();

            // fill the 1st pion to the histos if it passes the pion cuts
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {

                // set weighting factor

                // these histograms are used as control plots only 
                // reminder: for classI, 1st pion is positive,
                // while for classII, 1st pion is a ZTT track (positive or negative)
                if (classI) {
                    cGlobalBin->FillHistogram("pi_plus_pt_classI", pi1.Pt());
                    cGlobalBin->FillHistogram("pi_plus_theta_classI", pi1.Theta());
                    cGlobalBin->FillHistogram("pi_plus_phi_classI", pi1.Phi());
                    cGlobalBin->FillHistogram("pi_plus_layinner_classI", Trk_layinner[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_plus_layouter_classI", Trk_layouter[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_plus_laynr_classI", layout_nr_1);
                    cGlobalBin->FillHistogram("pi_plus_chi2_classI", Trk_chi2[fTrack1Id]);
                } else {
                    cGlobalBin->FillHistogram("pi_ZTT_pt_classII", pi1.Pt());
                    cGlobalBin->FillHistogram("pi_ZTT_theta_classII", pi1.Theta());
                    cGlobalBin->FillHistogram("pi_ZTT_phi_classII", pi1.Phi());
                    cGlobalBin->FillHistogram("pi_ZTT_layinner_classII", Trk_layinner[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_ZTT_layouter_classII", Trk_layouter[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_ZTT_laynr_classII", layout_nr_1);
                    cGlobalBin->FillHistogram("pi_ZTT_chi2_classII", Trk_chi2[fTrack1Id]);
                }

                // the following histograms are used for tracking efficiency evaluation
                cGlobalBin->FillHistogram("pi_pt_ZTT", pi1.Pt());
                cGlobalBin->FillHistogram("pi_pt_classI", pi1.Pt());
                cGlobalBin->FillHistogram("pi_phi_ZTT", pi1.Phi());
                cGlobalBin->FillHistogram("pi_theta_ZTT", pi1.Theta());
                cGlobalBin->FillHistogram("pi_pt_ZTTMSA", pi1.Pt());
                cGlobalBin->FillHistogram("pi_phi_ZTTMSA", pi1.Phi());
                cGlobalBin->FillHistogram("pi_theta_ZTTMSA", pi1.Theta());
                cGlobalBin->FillHistogram("pi_rho_mass_ZTT", rho.M());
                cGlobalBin->FillHistogram("pi_rho_mass_ZTTMSA", rho.M());
                // loop over all FLT slots, 0-63
                for (int slot=0; slot<64; slot++) {
                    int id = -1;
                    // 0-31: 1st element of array (i.e. [0])
                    // 32-63: 2nd element of array (i.e. [1])
                    if ( (slot>=0) && (slot<=31) ) id = 0;
                    if ( (slot>=32) && (slot<=63) ) id = 1;
                    // sanity check
                    if (id == -1) abort();
                    // check whether this trigger slot fired
                    bool flt_slot_fired = (bool) ( (Fltpsw[id] >> slot) & 1 );
                    // fill the histogram if yes
                    if (flt_slot_fired) cGlobalBin -> FillHistogram("pi_FLT_ZTT", slot);
                    if (flt_slot_fired) cGlobalBin -> FillHistogram("pi_FLT_ZTTMSA", slot);
                }

                // now separately for charge
                // classI: this is positive pion (1st)
                if (classI) {
                    cGlobalBin->FillHistogram("pi_plus_pt_ZTT", pi1.Pt());
                    cGlobalBin->FillHistogram("pi_plus_phi_ZTT", pi1.Phi());
                    cGlobalBin->FillHistogram("pi_plus_theta_ZTT", pi1.Theta());
                    cGlobalBin->FillHistogram("pi_plus_pt_ZTTMSA", pi1.Pt());
                    cGlobalBin->FillHistogram("pi_plus_phi_ZTTMSA", pi1.Phi());
                    cGlobalBin->FillHistogram("pi_plus_theta_ZTTMSA", pi1.Theta());
                // class II: this is ZTT track, can be either positive or negative
                } else if (!classI) {
                    if (Trk_charge[fTrack1Id]>0) {
                        cGlobalBin->FillHistogram("pi_plus_pt_ZTT", pi1.Pt());
                        cGlobalBin->FillHistogram("pi_plus_phi_ZTT", pi1.Phi());
                        cGlobalBin->FillHistogram("pi_plus_theta_ZTT", pi1.Theta());
                        cGlobalBin->FillHistogram("pi_plus_pt_ZTTMSA", pi1.Pt());
                        cGlobalBin->FillHistogram("pi_plus_phi_ZTTMSA", pi1.Phi());
                        cGlobalBin->FillHistogram("pi_plus_theta_ZTTMSA", pi1.Theta());
                    } else if (Trk_charge[fTrack1Id]<0) {
                        cGlobalBin->FillHistogram("pi_minus_pt_ZTT", pi1.Pt());
                        cGlobalBin->FillHistogram("pi_minus_phi_ZTT", pi1.Phi());
                        cGlobalBin->FillHistogram("pi_minus_theta_ZTT", pi1.Theta());
                        cGlobalBin->FillHistogram("pi_minus_pt_ZTTMSA", pi1.Pt());
                        cGlobalBin->FillHistogram("pi_minus_phi_ZTTMSA", pi1.Phi());
                        cGlobalBin->FillHistogram("pi_minus_theta_ZTTMSA", pi1.Theta());
                    } else {
                        cout << "ERROR: charge = 0" << endl;
                        abort();
                    }
                }

                TLorentzVector  proton_pion = proton_rest+pi1;
                Float_t Ecm = sqrt(proton_pion.Dot(proton_pion));
                cGlobalBin->FillHistogram("pi_Ecm_ZTT", Ecm);
                cGlobalBin->FillHistogram("pi_Ecm_ZTTMSA",Ecm);
                cGlobalBin->FillHistogram("pi_Ecm_fine_ZTT", Ecm);
                cGlobalBin->FillHistogram("pi_Ecm_fine_ZTTMSA",Ecm);
            }

            // *****************************************
            // ******* pion histograms, 2nd pion *******
            // *****************************************

            // set fPionThetaReco variable so that CheckGlobalBin can work
            fPionThetaReco = pi2.Theta();
            fPionPhiReco = pi2.Phi();

            // fill the 1st pion to the histos if it passes the pion cuts
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {


                // these histograms are used as control plots only 
                // reminder: for classI, 2nd pion is negative,
                // while for classII, 2nd pion is a MSA track (positive or negative)
                if (classI) {
                    cGlobalBin->FillHistogram("pi_minus_pt_classI", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_minus_theta_classI", pi2.Theta());
                    cGlobalBin->FillHistogram("pi_minus_phi_classI", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_minus_layinner_classI", Trk_layinner[fTrack2Id]);
                    cGlobalBin->FillHistogram("pi_minus_layouter_classI", Trk_layouter[fTrack2Id]);
                    cGlobalBin->FillHistogram("pi_minus_laynr_classI", layout_nr_2);
                    cGlobalBin->FillHistogram("pi_minus_chi2_classI", Trk_chi2[fTrack2Id]);
                } else {
                    cGlobalBin->FillHistogram("pi_MSA_pt_classII", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_MSA_phi_classII", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_MSA_theta_classII", pi2.Theta());
                    cGlobalBin->FillHistogram("pi_MSA_chi2_classII", Trkmsa_chi2[0]);
                    cGlobalBin->FillHistogram("pi_MSA_chi2ndof_classII", Trkmsa_chi2[0]/Trkmsa_ndof[0]);
                    if (pi2.Pt() > 1) cGlobalBin->FillHistogram("pi_MSA_highpT_chi2_classII", Trkmsa_chi2[0]);
                    if (pi2.Pt() < 1) cGlobalBin->FillHistogram("pi_MSA_lowpT_chi2_classII", Trkmsa_chi2[0]);

                    cGlobalBin->FillHistogram("pi_MSA_Trkmsa_nbr_classII", Trkmsa_nbr[0]);
                    cGlobalBin->FillHistogram("pi_MSA_Trkmsa_nbz_classII", Trkmsa_nbz[0]);
                    cGlobalBin->FillHistogram("pi_MSA_Trkmsa_nwu_classII", Trkmsa_nwu[0]);
                    cGlobalBin->FillHistogram("pi_MSA_Trkmsa_nwv_classII", Trkmsa_nwv[0]);

                    cGlobalBin->FillHistogram("pi_MSA_Trkmsa_imppar_classII", Trkmsa_imppar[0]);
                    cGlobalBin->FillHistogram("pi_MSA_z_imppar_classII", Trkmsa_pca[0][2] - Zvtx);
                }


                // the following histograms are used for tracking efficiency evaluation

                // ZTT+ZTT (classI=true) or ZTT+MSA (classI=false)
                TLorentzVector  proton_pion = proton_rest+pi2;
                Float_t Ecm = sqrt(proton_pion.Dot(proton_pion));
                if (classI) {
                    cGlobalBin->FillHistogram("pi_pt_ZTT", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_phi_ZTT", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_theta_ZTT", pi2.Theta());
                    cGlobalBin->FillHistogram("pi_Ecm_ZTT", Ecm);
                    cGlobalBin->FillHistogram("pi_Ecm_fine_ZTT", Ecm);
                    cGlobalBin->FillHistogram("pi_rho_mass_ZTT", rho.M());
                    // classI: this is a negative pion (2nd)
                    cGlobalBin->FillHistogram("pi_minus_pt_ZTT", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_minus_phi_ZTT", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_minus_theta_ZTT", pi2.Theta());
                    cGlobalBin->FillHistogram("pi_minus_pt_ZTTMSA", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_minus_phi_ZTTMSA", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_minus_theta_ZTTMSA", pi2.Theta());

                } else {
                    cGlobalBin->FillHistogram("pi_pt_MSA", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_phi_MSA", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_theta_MSA", pi2.Theta());
                    cGlobalBin->FillHistogram("pi_Ecm_MSA", Ecm);
                    cGlobalBin->FillHistogram("pi_Ecm_fine_MSA", Ecm);
                    cGlobalBin->FillHistogram("pi_rho_mass_MSA", rho.M());
                    if (Trkmsa_charge[0] > 0) {
                        cGlobalBin->FillHistogram("pi_plus_pt_MSA", pi2.Pt());
                        cGlobalBin->FillHistogram("pi_plus_phi_MSA", pi2.Phi());
                        cGlobalBin->FillHistogram("pi_plus_theta_MSA", pi2.Theta());
                        cGlobalBin->FillHistogram("pi_plus_pt_ZTTMSA", pi2.Pt());
                        cGlobalBin->FillHistogram("pi_plus_phi_ZTTMSA", pi2.Phi());
                        cGlobalBin->FillHistogram("pi_plus_theta_ZTTMSA", pi2.Theta());
                    } else if (Trkmsa_charge[0] < 0) {
                        cGlobalBin->FillHistogram("pi_minus_pt_MSA", pi2.Pt());
                        cGlobalBin->FillHistogram("pi_minus_phi_MSA", pi2.Phi());
                        cGlobalBin->FillHistogram("pi_minus_theta_MSA", pi2.Theta());
                        cGlobalBin->FillHistogram("pi_minus_pt_ZTTMSA", pi2.Pt());
                        cGlobalBin->FillHistogram("pi_minus_phi_ZTTMSA", pi2.Phi());
                        cGlobalBin->FillHistogram("pi_minus_theta_ZTTMSA", pi2.Theta());
                    } else {
                        cout << "ERROR: MVDSA track charge = 0" << endl;
                        abort();
                    }
                }
                cGlobalBin->FillHistogram("pi_pt_ZTTMSA", pi2.Pt());
                cGlobalBin->FillHistogram("pi_phi_ZTTMSA", pi2.Phi());
                cGlobalBin->FillHistogram("pi_theta_ZTTMSA", pi2.Theta());
                cGlobalBin->FillHistogram("pi_Ecm_ZTTMSA",Ecm);
                cGlobalBin->FillHistogram("pi_Ecm_fine_ZTTMSA",Ecm);
                cGlobalBin->FillHistogram("pi_rho_mass_ZTTMSA", rho.M());
                // loop over all FLT slots, 0-63
                for (int slot=0; slot<64; slot++) {
                    int id = -1;
                    // 0-31: 1st element of array (i.e. [0])
                    // 32-63: 2nd element of array (i.e. [1])
                    if ( (slot>=0) && (slot<=31) ) id = 0;
                    if ( (slot>=32) && (slot<=63) ) id = 1;
                    // sanity check
                    if (id == -1) abort();
                    // check whether this trigger slot fired
                    bool flt_slot_fired = (bool) ( (Fltpsw[id] >> slot) & 1 );
                    // fill the histogram if yes
                    if (flt_slot_fired) if (classI) cGlobalBin -> FillHistogram("pi_FLT_ZTT", slot);
                    if (flt_slot_fired) if (!classI) cGlobalBin -> FillHistogram("pi_FLT_MSA", slot);
                    if (flt_slot_fired) cGlobalBin -> FillHistogram("pi_FLT_ZTTMSA", slot);
                }
            }

        } // end loop over bins
}

bool TMiniNtupleAnalyzer::TrackMatch(TLorentzVector track1, TLorentzVector track2) {
    bool matched = false;
    Float_t delta = track1.DeltaR(track2);
    if (delta<0.5) matched = true;
    return matched;
}

int TMiniNtupleAnalyzer::getRhoEventClass() {

    // classifies events according to the following definition:
    // class 0: pions are not in the fiducial volume
    // class 1: pions did not interact before a certain radius
    // class 2: one of the pions interacted before the CTD (R<17.5)
    // class 3: does not fall in those above

    TLorentzVector pi1 = get_pi_plus();
    TLorentzVector pi2 = get_pi_minus();

    if (pi1.Pt()<0.2) return 0;
    if ( (pi1.Theta()<0.44) || (pi1.Theta()>2.7) ) return 0;
    if (pi2.Pt()<0.2) return 0;
    if ( (pi2.Theta()<0.44) || (pi2.Theta()>2.7) ) return 0;

    int pi_plus_id = get_pi_plus_id();
    int pi_minus_id = get_pi_minus_id();

    Float_t x1 = Fmcf_rm[pi_plus_id][0];
    Float_t y1 = Fmcf_rm[pi_plus_id][1];
    Float_t x2 = Fmcf_rm[pi_minus_id][0];
    Float_t y2 = Fmcf_rm[pi_minus_id][1];

    Float_t r1 = TMath::Sqrt(x1*x1 + y1*y1);
    Float_t r2 = TMath::Sqrt(x2*x2 + y2*y2);
    if ( (r1>40) && (r2>40) ) return 1;
    if ( ( (r1<17.5) && (r2>17.5) ) || ( (r1>17.5) && (r2<17.5) ) ) return 2;
    return 3;
}

void TMiniNtupleAnalyzer::FillPionsFatePoint() {

    TLorentzVector pi1 = get_pi_plus();
    TLorentzVector pi2 = get_pi_minus();

    if (pi1.Pt()<0.2) return;
    if ( (pi1.Theta()<0.44) || (pi1.Theta()>2.7) ) return;
    if (pi2.Pt()<0.2) return;
    if ( (pi2.Theta()<0.44) || (pi2.Theta()>2.7) ) return;

    int pi_plus_id = get_pi_plus_id();
    int pi_minus_id = get_pi_minus_id();

    fMc_pt_theta_pi -> Fill(Fmcf_rm[pi_plus_id][0], Fmcf_rm[pi_plus_id][1]);
    fMc_pt_theta_pi -> Fill(Fmcf_rm[pi_minus_id][0], Fmcf_rm[pi_minus_id][1]);
}

TLorentzVector TMiniNtupleAnalyzer::get_pi_plus() {

    int pi_plus_id = get_pi_plus_id();
    TLorentzVector pi_plus;
    pi_plus.SetXYZM(Fmck_px[pi_plus_id], Fmck_py[pi_plus_id], Fmck_pz[pi_plus_id], M_PION);
    return pi_plus;
}

TLorentzVector TMiniNtupleAnalyzer::get_pi_minus() {
    int pi_minus_id = get_pi_minus_id();
    TLorentzVector pi_minus;
    pi_minus.SetXYZM(Fmck_px[pi_minus_id], Fmck_py[pi_minus_id], Fmck_pz[pi_minus_id], M_PION);
    return pi_minus;
}

int TMiniNtupleAnalyzer::get_pi_plus_id() {
    return get_pi_id(true);
}

int TMiniNtupleAnalyzer::get_pi_minus_id() {
    return get_pi_id(false);
}

int TMiniNtupleAnalyzer::get_pi_id(bool is_plus) {

    // pi_plus = true: return pi+
    // pi_plus = false: return pi-

    // id's of rho and it's decay products on the true level
    int rho_id=-1;
    int pi_plus_id=-1;
    int pi_minus_id=-1;

    // loop over the true level particles to find rho and pions
    for ( int i = 0; i < Fmck_nstor; i++) {
        Int_t   type = Fmck_prt[i];
        if (type==78) rho_id = i;
        if ( (type==54) && (Fmck_daug[i] == Fmck_id[rho_id]) ) pi_plus_id = i;
        if ( (type==55) && (Fmck_daug[i] == Fmck_id[rho_id]) ) pi_minus_id = i;
    }

    // sanity check
    if ( (rho_id == (-1)) || (pi_plus_id == (-1)) || (pi_minus_id == (-1)) ) {
        cout << "ERROR: rho/pions could not be identified on the true level!" << endl;
        abort();
    }

    if (is_plus) return pi_plus_id;
    if (!is_plus) return pi_minus_id;
}

Double_t TMiniNtupleAnalyzer::getIslandDCA(int isl, int trk) {
    // define relevant vectors
    TVector3 island(Xisl[isl], Yisl[isl], Zisl[isl]);
    TVector3 trk_endOfSwim(Vcatcal_x[trk][0], Vcatcal_x[trk][1], Vcatcal_x[trk][2]);
    TVector3 trk_mom_endOfSwim(Vcatcal_p[trk][0], Vcatcal_p[trk][1], Vcatcal_p[trk][2]);

    // get an angle between the relative (to the end of swim point) position vector of the island
    // to the flight direction of a track at the end of swim point
    TVector3 island_relative = island - trk_endOfSwim;
    Double_t cos_alpha = (island_relative.Dot(trk_mom_endOfSwim))/(island_relative.Mag() * trk_mom_endOfSwim.Mag());

    // calculate DCA
    Double_t    DCA = sqrt(1-cos_alpha*cos_alpha) * island_relative.Mag();
    return  DCA;
}

Double_t TMiniNtupleAnalyzer::getElectronEnergyConstrainedMethod(TLorentzVector rho) {

    // use rho information to calculate scattered electron enegry  - "constrained" method, see e.g. eur phys c 6, 603-627 (1999)

    // calculate e-pZ of the rho
    Double_t    empz = rho.E() - rho.Pz();

    // calculate electron energy
    Double_t    E_elec = (2*E_BEAM - empz)/(1 - cos(Sith[0]));

    // done
    return E_elec;
}

TLorentzVector TMiniNtupleAnalyzer::getElectronConstrainedMethod(TLorentzVector rho) {

    // get electron energy from constrained method
    Double_t    E_elec = getElectronEnergyConstrainedMethod(rho);

    // set scattered electron parameters
    TLorentzVector electron; 
    electron.SetXYZM(E_elec*sin(Sith[0])*cos(Siph[0]), E_elec*sin(Sith[0])*sin(Siph[0]), E_elec*cos(Sith[0]), M_ELECTRON);

    return electron;
}

Double_t TMiniNtupleAnalyzer::getQ2ConstrainedMethod(TLorentzVector rho) {

    // get electron energy from constrained method
    Double_t    E_elec = getElectronEnergyConstrainedMethod(rho);

    // calculate Q2
    Double_t    q2 = 2 * E_BEAM * E_elec * ( 1 + cos(Sith[0]) );

    // done
    return q2;
}

Double_t TMiniNtupleAnalyzer::get_PHI_h(TLorentzVector rho, bool q_reco) {

    // set incoming/outgoing lepton 4vectors
    TLorentzVector  e_incoming(0, 0, (-1)*E_BEAM, sqrt(E_BEAM*E_BEAM + M_ELECTRON * M_ELECTRON));
    TLorentzVector  e_outgoing;
    if (q_reco) {
        e_outgoing = getElectronConstrainedMethod(rho);
    } else {
        e_outgoing.SetXYZM(Plepton[0], Plepton[1], Plepton[2], M_ELECTRON);
    }

    // set the incoming proton 4-vector
    TLorentzVector p_incoming(0, 0, E_PROTON, sqrt( E_PROTON * E_PROTON + M_PROTON * M_PROTON ) );

    // get boost and rotation vectors as well as the gamma* vector
    get_gammaP_boost(q_reco, true);

    // boost leptons, incoming proton and the rho to the gamma*-p frame
    e_incoming.Boost(fBoost);
    e_incoming.Rotate(fAngle, fRotationAxis);

    e_outgoing.Boost(fBoost);
    e_outgoing.Rotate(fAngle, fRotationAxis);

    p_incoming.Boost(fBoost);
    p_incoming.Rotate(fAngle, fRotationAxis);

    rho.Boost(fBoost);
    rho.Rotate(fAngle, fRotationAxis);

    // get normals to the scattering and production planes
    TVector3 e_incoming_3vect = e_incoming.Vect();
    TVector3 e_outgoing_3vect = e_outgoing.Vect();
    TVector3 scat_plane_perp = e_incoming_3vect.Cross(e_outgoing_3vect);

    TVector3 gamma_3vect = fq.Vect();
    TVector3 rho_3vect = rho.Vect();
    TVector3 prod_plane_perp = gamma_3vect.Cross(rho_3vect);

    // these vectors are perpendicular to the Z axis (incoming proton/gamma* direction),
    // hence can work in 2D space - that is in XY plane of the gamma*-p frame
    TVector2 vscat = scat_plane_perp.XYvector();
    TVector2 vprod = prod_plane_perp.XYvector();

    // rotate both vectors in such a way that vscat has phi = 0
    vprod=vprod.Rotate((-1)*vscat.Phi());
    vscat=vscat.Rotate((-1)*vscat.Phi());

    // the PHI_h is just the phi angle of vprod (range [0, 2pi], see ROOT docs)
    Double_t PHI_h=vprod.Phi();

    // sanity check
    if ( TMath::IsNaN(PHI_h) ) {
        cout << "ERROR: helicity angle is NAN" << endl;
        abort();
    }

    // the other - equivalent way to define PHI:
    // very similar to the definition in NUCL PHYS B 61 381-413 (1973),
    // except a small thing, see below

    TVector3 z = fq.Vect();
    z = z.Unit();

    TVector3 y = z.Cross(rho_3vect);
    y = y.Unit();

    TVector3 x = y.Cross(z);

    TVector3 scat_plane_norm = e_incoming_3vect.Cross(e_outgoing_3vect);
    scat_plane_norm = scat_plane_norm.Unit();

    // the commented line is according to the paper; however
    // in this case PHI is [0, pi] and not [0, 2pi], since sinPHI>0 - easy to check
    // TVector3 hadr_plane_par = (y.Cross(scat_plane_norm)).Cross(y);
    // this definition is used instead, which allows negative sinPHI!
    TVector3 hadr_plane_par = z.Cross(y);
    hadr_plane_par = hadr_plane_par.Unit();

    Double_t    cosPHI = scat_plane_norm.Dot(y);
    Double_t    sinPHI = scat_plane_norm.Dot(hadr_plane_par);

    Double_t    PHI = atan2(sinPHI, cosPHI);

    if (PHI<0) PHI += 2 * TMath::Pi();

    // sanity check
    Double_t diff = TMath::Abs(PHI_h - PHI);
    if (diff>1e-5) {
        cout << "ERROR: PHI determined by different methods differ by " << diff << endl;
        abort();
    }

    // done
    return PHI_h;
}

TLorentzVector TMiniNtupleAnalyzer::getPiPlusInRhoHelicityFrame(TLorentzVector pi_plus, TLorentzVector pi_minus, bool q_reco) {

    // get boost and rotation vectors as well as the gamma* vector
    get_gammaP_boost(q_reco, true);

    TLorentzVector rho = pi_plus + pi_minus;
    rho.Boost(fBoost);
    rho.Rotate(fAngle, fRotationAxis);

    pi_plus.Boost(fBoost);
    pi_plus.Rotate(fAngle, fRotationAxis);

    // rotate the system in such a way that rho direction is Z 
    // i.e. the outgoing proton direction is opposite to Z - according to a definition of the helicity frame)
    TVector3 z(0,0,1);
    TVector3 rho_vect = rho.Vect();
    // rotation angle is the angle between the original z axis and the rho direction
    // acos input: [-1, 1] output: [0, pi]
    Double_t rotation_angle = acos(rho.Pz()/rho.P());
    // rotation axis is a vector perpendicular to both rho direction and the z axis (i.e. z axis is rotated in z-rho plane)
    TVector3 rotation_axis = rho_vect.Cross(z);

    // perform rotation of lab vectors (need rho and positive pion)
    rho.Rotate(rotation_angle, rotation_axis);
    pi_plus.Rotate(rotation_angle, rotation_axis);

    // determine the boost vector, which is opposite to rho velocity vector and is given in terms of c
    // (for any lorentz vector, velocity/c = momentum*c/energy, we work in natural units, c=1)
    Double_t px = rho.Px();
    Double_t py = rho.Py();
    Double_t pz = rho.Pz();
    Double_t e  = rho.E();
    TVector3 boost(-px/e, -py/e, -pz/e);

    // finally, boost the vectors to the rho rest frame
    rho.Boost(boost);
    pi_plus.Boost(boost);

    // return rotated and boosted pi+
    return pi_plus;
}

Double_t TMiniNtupleAnalyzer::get_cos_theta_h(TLorentzVector pi_plus, TLorentzVector pi_minus, bool q2_reco) {

    // get p+ in rho helicity frame
    TLorentzVector pi_plus_rho_frame = getPiPlusInRhoHelicityFrame(pi_plus, pi_minus, q2_reco);

    // theta*) is the angle between the pi+ direction and the z direction in this frame (e.g. Theta)
    Double_t cos_theta_h = pi_plus_rho_frame.Z() / pi_plus_rho_frame.P();

    return cos_theta_h;
}

Double_t TMiniNtupleAnalyzer::get_phi_h(TLorentzVector pi_plus, TLorentzVector pi_minus, bool q2_reco) {

    // get p+ in rho helicity frame
    TLorentzVector pi_plus_rho_frame = getPiPlusInRhoHelicityFrame(pi_plus, pi_minus, q2_reco);

    // Phi_h is azimutal angle of pi+ in this frame
    Double_t phi_h = pi_plus_rho_frame.Phi();
    phi_h = TVector2::Phi_0_2pi(phi_h);

    return phi_h;
}

Double_t TMiniNtupleAnalyzer::get_cos_theta_star(TLorentzVector pi_plus, TLorentzVector pi_minus) {

    // construct the rho
    TLorentzVector rho = pi_plus + pi_minus;

    // rotate the system in such a way that rho direction is Z 
    // i.e. the outgoing proton direction is opposite to Z - according to a definition of the helicity frame)
    TVector3 z(0,0,1);
    TVector3 rho_vect = rho.Vect();
    // rotation angle is the angle between the original z axis and the rho direction
    // acos input: [-1, 1] output: [0, pi]
    Double_t rotation_angle = acos(rho.Pz()/rho.P());
    // rotation axis is a vector perpendicular to both rho direction and the z axis (i.e. z axis is rotated in z-rho plane)
    TVector3 rotation_axis = rho_vect.Cross(z);

    // perform rotation of lab vectors (need rho and positive pion)
    rho.Rotate(rotation_angle, rotation_axis);
    pi_plus.Rotate(rotation_angle, rotation_axis);

    // determine the boost vector, which is opposite to rho velocity vector and is given in terms of c
    // (for any lorentz vector, velocity/c = momentum*c/energy, we work in natural units, c=1)
    Double_t px = rho.Px();
    Double_t py = rho.Py();
    Double_t pz = rho.Pz();
    Double_t e  = rho.E();
    TVector3 boost(-px/e, -py/e, -pz/e);

    // finally, boost the vectors to the rho rest frame
    rho.Boost(boost);
    pi_plus.Boost(boost);

    // get the cos theta star
    Double_t cos_theta_star = pi_plus.Z()/pi_plus.P();

    // done
    return cos_theta_star;
}

Double_t TMiniNtupleAnalyzer::getRhoPhiWeight(Double_t phi) {

    Double_t p0                        =     1.2885; //          +/-     0.0141317
    Double_t p1                        =     -0.032724; //       +/-     0.0126286
    Double_t p2                        =     0.0797095; //       +/-     0.0131964
    Double_t p3                        =     0.0128284; //       +/-     0.00402727
    Double_t p4                        =     -0.0499703; //      +/-     0.00308789
    Double_t p5                        =     -0.00105036; //     +/-     0.000312665
    Double_t p6                        =     0.00393659; //      +/-     0.00020097

    Double_t weight = p0 + p1*phi + p2*pow(phi,2) + p3*pow(phi,3) + p4*pow(phi,4) + p5*pow(phi,5) + p6*pow(phi,6);
    return weight;
}

Double_t TMiniNtupleAnalyzer::get_cos_theta_star_weight(Double_t cos_theta_star) {

    Double_t p0                        =     0.284033; //        +/-     0.00337638
    Double_t p1                        =     0.00138078; //      +/-     0.00846044
    Double_t p2                        =     2.67141; //         +/-     0.017589

    Double_t weight = p0 + p1*cos_theta_star + p2*pow(cos_theta_star,2);
    return weight;
}
