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
            TVector3 pi_plus = get_pi_plus();
            TVector3 pi_minus = get_pi_minus();
            DeltaR = pi_plus.DeltaR(pi_minus);
        }

        // fill true-level histograms
        inclusiveBin->SetWeightingFactor(1);
        inclusiveBin->FillHistogram("Rmin", Rmin);
        inclusiveBin->FillHistogram("truedR", DeltaR);

        // perform also "true level analysis", in this case means filling fate-points histograms
        if (fIsMC) RhoTrueLevelAnalysis();

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
        if (classI || classII) if (fUnmatchedIslandsEnergy > 0.5) continue;

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

    // define constants
    const Float_t M_PION = 0.139570;
    const Float_t M_KAON = 0.4937;

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

        TLorentzVector  proton_rest;
        proton_rest.SetXYZM(0, 0, 0, 0.9383);

        // needed later: number of superlayers for ZTT tracks
        unsigned layout_nr_1= 0;
        if (Trk_layinner[fTrack1Id] == 0) layout_nr_1 = Trk_layouter[fTrack1Id];
        else layout_nr_1 = Trk_layouter[fTrack1Id] - Trk_layinner[fTrack1Id] + 1;
        unsigned layout_nr_2= 0;
        if (Trk_layinner[fTrack2Id] == 0) layout_nr_2 = Trk_layouter[fTrack2Id];
        else layout_nr_2 = Trk_layouter[fTrack2Id] - Trk_layinner[fTrack2Id] + 1;

        // determine pt-reweighting factors for both pions
        Double_t    weight_pi1_pt = 1;
        Double_t    weight_pi2_pt = 1;
        if (fIsMC && fApplyPtReweighting) {
            weight_pi1_pt = getPionPtReweighting(pi1.Pt());
            weight_pi2_pt = getPionPtReweighting(pi2.Pt());
        }
        // determine phi-reweighting for both pions
        Double_t    weight_pi1_phi = 1;
        Double_t    weight_pi2_phi = 1;
        if (fIsMC && fApplyPhiReweighting) {
            weight_pi1_phi = getPionPhiReweighting(pi1.Phi());
            weight_pi2_phi = getPionPhiReweighting(pi2.Phi());
        }

        // determine theta star weighting
        Double_t    weight_theta_star = 1;
        if (fIsMC && fApplyThetaStarReweighting) {
            weight_theta_star = getThetaStarReweighting(getThetaStar(pi1, pi2));
            if (getThetaStar(pi1, pi2) < 0) abort();
        }

        // now fill the histograms
        // loop over Global Bins and if this event satisfies bin's criteria - fill histograms that belong to the bin
        TGlobalBin  *cGlobalBin;
        TIter       Iter_TGlobalBin(fList_TGlobalBin);
        while ((cGlobalBin=(TGlobalBin*) Iter_TGlobalBin.Next())) {

            // check if event satisfies bin's criteria on the event level
            Bool_t GlobalBinFired=cGlobalBin->CheckGlobalBin(kEventVar);
            if (!GlobalBinFired) continue;

            fHistogramsFile->cd(cGlobalBin->BinName);

            // switch on reweighting if mc
            if (fIsMC) cGlobalBin -> SetWeightingFactor(1);

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
            // for rho/phi histograms, we weight according to the pt of the 1st pion (could do also for the 2nd)
            if (fIsMC) cGlobalBin -> SetWeightingFactor (weight_pi1_pt * weight_pi1_phi * weight_theta_star);

            // fill the phi mass
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (classI) cGlobalBin->FillHistogram("phi_mass_classI", phi.M());
                if (!classI) cGlobalBin->FillHistogram("phi_mass_classII", phi.M());
            }
            // skip if kaon-kaon hypothesis is consistent with phi
            if ( (phi.M()>1.012) && (phi.M()<1.028) ) continue;

            // fill the rho mass
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (classI) cGlobalBin->FillHistogram("rho_mass_classI", rho.M());
                if (!classI) cGlobalBin->FillHistogram("rho_mass_classII", rho.M());
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

            // fill various event histograms (at the moment without binning)

            // electron histograms

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

            // for MC: get event class,see the definition in RhoTrueLevelAnalysis()
            int event_class;
            if (fIsMC) event_class = RhoTrueLevelAnalysis();
            // fill event histograms for class I or class II
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

                // true class II reconstructed as class II
                if ( fIsMC && ( event_class == 2 ) ) {
                    cGlobalBin->FillHistogram("Trk_ntracks_classII_as_classII", Trk_ntracks);
                    cGlobalBin->FillHistogram("long_ZTT_tracks_classII_as_classII", fLong_ZTT_tracks);
                    cGlobalBin->FillHistogram("primary_ZTT_tracks_classII_as_classII", fPrimary_ZTT_tracks);
                    // subset of those events, which have exactly two long tracks
/*                    if (fLong_ZTT_tracks==2) {
                        if (fDebugPrintout) cout << "INFO: class 2 as class2, fLong_ZTT_tracks=2! " << Runnr << " " << Eventnr << endl;
                        int long_tracks_found = 0;
                        int primary_tracks_found = 0;
                        int track1 = 0;     // long primary
                        int track2 = 0;     // other long
                        for (int j = 0; j < Trk_ntracks; j++) {
                            if (Trk_id[j] == Sitrknr[0])continue;
                            Int_t   inner = Trk_layinner[j];
                            Int_t   outer = Trk_layouter[j];
                            bool    long_track = ((inner<=1) && (outer>=3));
                            if (long_track && (Trk_prim_vtx[j] == 1) ) track1 = j;
                            if (long_track && (Trk_prim_vtx[j] != 1) ) track2 = j;
                            if (long_track) long_tracks_found++;
                            if (Trk_prim_vtx[j] == 1) primary_tracks_found++;
                        }
                        if (long_tracks_found!=2) { cout << "wtf!!" << endl; abort(); }
                        if (primary_tracks_found!=1) { cout << "wtf!!" << endl; abort(); }
                        TLorentzVector t1;
                        t1.SetXYZM(Trk_px[track1], Trk_py[track1], Trk_pz[track1], 0.139570);
                        TLorentzVector t2;
                        t2.SetXYZM(Trk_px[track2], Trk_py[track2], Trk_pz[track2], 0.139570);
                        TLorentzVector rho = t1 + t2;
                        cGlobalBin->FillHistogram("mass_rho_classII_as_classII", rho.M());
                        TLorentzVector  long_track(Trk_px[track2], Trk_py[track2], Trk_pz[track2], 0.139570);
                        TLorentzVector  MSA_track(Trkmsa_px[0], Trkmsa_py[0], Trkmsa_pz[0], 0.139570);
                        Double_t dR = long_track.DeltaR(MSA_track);
                        cGlobalBin->FillHistogram("dR_classII_as_classII", dR);
                    }*/
                }
                // true class I reconstructed as class II 
                if ( fIsMC && ( event_class == 1 ) ) {
                    cGlobalBin->FillHistogram("Trk_ntracks_classI_as_classII", Trk_ntracks);
                    cGlobalBin->FillHistogram("long_ZTT_tracks_classI_as_classII", fLong_ZTT_tracks);
                    cGlobalBin->FillHistogram("primary_ZTT_tracks_classI_as_classII", fPrimary_ZTT_tracks);
                    if (fDebugPrintout) cout << "selected for class 2, but belongs to class1 " << Runnr << " " << Eventnr << endl;

                    TVector3 pi1 = get_pi_plus();
                    TVector3 pi2 = get_pi_plus();
                    if (fDebugPrintout) cout << pi1.Mag() << " " << pi1.Pt() << " " << pi2.Mag() << " " << pi2.Pt() << endl;

                    // subset of those events, which have exactly two long tracks
/*                    if (fLong_ZTT_tracks==2) {
                        int long_tracks_found = 0;
                        int primary_tracks_found = 0;
                        int track1 = 0;     // long primary
                        int track2 = 0;     // other long
                        for (int j = 0; j < Trk_ntracks; j++) {
                            if (Trk_id[j] == Sitrknr[0])continue;
                            Int_t   inner = Trk_layinner[j];
                            Int_t   outer = Trk_layouter[j];
                            bool    long_track = ((inner<=1) && (outer>=3));
                            if (long_track && (Trk_prim_vtx[j] == 1) ) track1 = j;
                            if (long_track && (Trk_prim_vtx[j] != 1) ) track2 = j;
                            if (long_track) long_tracks_found++;
                            if (Trk_prim_vtx[j] == 1) primary_tracks_found++;
                        }
                        if (long_tracks_found!=2) { cout << "wtf!!" << endl; abort(); }
                        if (primary_tracks_found!=1) { cout << "wtf!!" << endl; abort(); }
                        TLorentzVector t1;
                        t1.SetXYZM(Trk_px[track1], Trk_py[track1], Trk_pz[track1], 0.139570);
                        TLorentzVector t2;
                        t2.SetXYZM(Trk_px[track2], Trk_py[track2], Trk_pz[track2], 0.139570);
                        TLorentzVector rho = t1 + t2;
                        cGlobalBin->FillHistogram("mass_rho_classI_as_classII", rho.M());
                        TLorentzVector  long_track(Trk_px[track2], Trk_py[track2], Trk_pz[track2], 0.139570);
                        TLorentzVector  MSA_track(Trkmsa_px[0], Trkmsa_py[0], Trkmsa_pz[0], 0.139570);
                        Double_t dR = long_track.DeltaR(MSA_track);
                        cGlobalBin->FillHistogram("dR_classI_as_classII", dR);

                    }*/
                }
            }

            // *****************************************
            // ******* rho histograms, 1st pion ********
            // *****************************************

            Double_t    dPhi = TMath::Abs(pi1.DeltaPhi(pi2));
            Double_t    dTheta = TMath::Abs(pi1.Theta() - pi2.Theta());
            Double_t    dPt = TMath::Abs(pi1.Pt() - pi2.Pt());
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (classI) {
                    cGlobalBin->FillHistogram("rho_pt_classI", rho.Pt());
                    cGlobalBin->FillHistogram("rho_phi_classI", rho.Phi());
                    cGlobalBin->FillHistogram("rho_theta_classI", rho.Theta());
                    cGlobalBin->FillHistogram("dPhi_classI", dPhi);
                    cGlobalBin->FillHistogram("dTheta_classI", dTheta);
                    cGlobalBin->FillHistogram("dPt_classI", dPt);
                    cGlobalBin->FillHistogram("theta_star_classI", getThetaStar(pi1, pi2));
                } else {
                    cGlobalBin->FillHistogram("rho_pt_classII", rho.Pt());
                    cGlobalBin->FillHistogram("rho_phi_classII", rho.Phi());
                    cGlobalBin->FillHistogram("rho_theta_classII", rho.Theta());
                    cGlobalBin->FillHistogram("dPhi_classII", dPhi);
                    cGlobalBin->FillHistogram("dTheta_classII", dTheta);
                    cGlobalBin->FillHistogram("dPt_classII", dPt);
                    cGlobalBin->FillHistogram("theta_star_classII", getThetaStar(pi1, pi2));
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
                if (fIsMC) cGlobalBin -> SetWeightingFactor (weight_pi1_pt * weight_pi1_phi * weight_theta_star);
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

                // for classI, 1st pion is positive
                // for classII, 1st pion is ZTT track (positive or negative)
                if (classI) {
                    cGlobalBin->FillHistogram("pi_plus_pt_classI", pi1.Pt());
                    cGlobalBin->FillHistogram("pi_plus_phi_classI", pi1.Phi());
                    cGlobalBin->FillHistogram("pi_plus_theta_classI", pi1.Theta());
                    cGlobalBin->FillHistogram("pi_plus_layinner_classI", Trk_layinner[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_plus_layouter_classI", Trk_layouter[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_plus_laynr_classI", layout_nr_1);
                    cGlobalBin->FillHistogram("pi_plus_chi2_classI", Trk_chi2[fTrack1Id]);
                } else {
                    cGlobalBin->FillHistogram("pi_ZTT_pt_classII", pi1.Pt());
                    cGlobalBin->FillHistogram("pi_ZTT_phi_classII", pi1.Phi());
                    cGlobalBin->FillHistogram("pi_ZTT_theta_classII", pi1.Theta());
                    cGlobalBin->FillHistogram("pi_ZTT_layinner_classII", Trk_layinner[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_ZTT_layouter_classII", Trk_layouter[fTrack1Id]);
                    cGlobalBin->FillHistogram("pi_ZTT_laynr_classII", layout_nr_1);
                    cGlobalBin->FillHistogram("pi_ZTT_chi2_classII", Trk_chi2[fTrack1Id]);
                }
            }

            // *****************************************
            // ******* pion histograms, 2nd pion *******
            // *****************************************

            // set fPionThetaReco variable so that CheckGlobalBin can work
            fPionThetaReco = pi2.Theta();
            fPionPhiReco = pi2.Phi();
            // fill the 1st pion to the histos if it passes the pion cuts
            if ( cGlobalBin -> CheckGlobalBin(kPionVar) ) {
                if (fIsMC) cGlobalBin -> SetWeightingFactor (weight_pi2_pt * weight_pi2_phi * weight_theta_star);
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

                // for classI, 2nd pion is negative
                // for classII, 2nd pion is MSA track (positive or negative)
                if (classI) {
                    cGlobalBin->FillHistogram("pi_minus_pt_classI", pi2.Pt());
                    cGlobalBin->FillHistogram("pi_minus_phi_classI", pi2.Phi());
                    cGlobalBin->FillHistogram("pi_minus_theta_classI", pi2.Theta());
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
            }

        } // end loop over bins
}

Double_t TMiniNtupleAnalyzer::getPionPhiReweighting (Double_t phi) {

//     Double_t p0 = 1.23939;      // +/-     0.0114037
//     Double_t p1 = -0.0549178;   // +/-     0.0126261
//     Double_t p2 = -0.119674;    // +/-     0.0055402
//     Double_t p3 = 0.022167;     // +/-     0.00449931
//     Double_t p4 = 0.0103398;    // +/-     0.000570118
//     Double_t p5 = -0.00175276;  // +/-     0.000375304

    Double_t p0 =     1.33098;   //         +/-     0.00762926
    Double_t p1 =     -0.0334553;   //      +/-     0.00810863
    Double_t p2 =     -0.139294;   //       +/-     0.00349777
    Double_t p3 =     0.0132893;   //       +/-     0.0027489
    Double_t p4 =     0.0102305;   //       +/-     0.000348818
    Double_t p5 =     -0.0010197;   //      +/-     0.000221275

    Double_t weight = p0  + p1 * phi + p2 * pow(phi, 2) + p3 * pow(phi, 3) + p4 * pow(phi, 4) + p5 * pow(phi, 5);
    return weight;
}

Double_t TMiniNtupleAnalyzer::getPionPtReweighting (Double_t pt) {

//     Double_t p0 = 3.40286;  // +/- 0.0459327
//     Double_t p1 = -7.26273; // +/- 0.167761
//     Double_t p2 = 5.96992;  // +/- 0.215883
//     Double_t p3 = -2.04569; // +/- 0.122476
//     Double_t p4 = 0.319297; // +/- 0.0309977
//     Double_t p5 = -0.018484;// +/- 0.00283858

    Double_t p0                        =     1.09509;  //         +/-     0.0329055
    Double_t p1                        =     0.17879;  //         +/-     0.13525
    Double_t p2                        =     -0.746055;  //       +/-     0.178135
    Double_t p3                        =     0.534439;  //        +/-     0.0999949
    Double_t p4                        =     -0.136556;  //       +/-     0.0247568
    Double_t p5                        =     0.0116791;  //       +/-     0.00221369


    if (pt>5) return getPionPtReweighting(5);

    Double_t weight = p0  + p1 * pt + p2 * pow(pt, 2) + p3 * pow(pt, 3) + p4 * pow(pt, 4) + p5 * pow(pt, 5);
    return weight;
}

Double_t TMiniNtupleAnalyzer::getThetaStarReweighting(Double_t theta_star) {

    Double_t p0 = 4.55375;  // +/- 0.650318
    Double_t p1 = -12.0416; // +/- 3.83131
    Double_t p2 = 28.3297;  // +/- 8.5852
    Double_t p3 = -36.0429; // +/- 9.18135
    Double_t p4 = 20.5197;  // +/- 4.71102
    Double_t p5 = -4.2362;  // +/- 0.932609

    Double_t weight = p0 + p1*theta_star + p2*pow(theta_star,2) + p3*pow(theta_star,3) + p4*pow(theta_star,4) + p5*pow(theta_star,5);
    return weight;
}

bool TMiniNtupleAnalyzer::TrackMatch(TLorentzVector track1, TLorentzVector track2) {
    bool matched = false;
    Float_t delta = track1.DeltaR(track2);
    if (delta<0.5) matched = true;
    return matched;
}

int TMiniNtupleAnalyzer::RhoTrueLevelAnalysis() {

    // classifies events according to the following definition:
    // class 0: pions are not in the fiducial volume
    // class 1: pions did not interact before a certain radius
    // class 2: one of the pions interacted before the CTD (R<17.5)
    // class 3: does not fall in those above

    TVector3 pi1 = get_pi_plus();
    TVector3 pi2 = get_pi_minus();

    if (pi1.Pt()<0.2) return 0;
    if ( (pi1.Theta()<0.44) || (pi1.Theta()>2.7) ) return 0;
    if (pi2.Pt()<0.2) return 0;
    if ( (pi2.Theta()<0.44) || (pi2.Theta()>2.7) ) return 0;

    int pi_plus_id = get_pi_plus_id();
    int pi_minus_id = get_pi_minus_id();

    fMc_pt_theta_pi -> Fill(Fmcf_rm[pi_plus_id][0], Fmcf_rm[pi_plus_id][1]);
    fMc_pt_theta_pi -> Fill(Fmcf_rm[pi_minus_id][0], Fmcf_rm[pi_minus_id][1]);
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

TVector3 TMiniNtupleAnalyzer::get_pi_plus() {
    int pi_plus_id = get_pi_plus_id();
    TVector3 pi_plus(Fmck_px[pi_plus_id], Fmck_py[pi_plus_id], Fmck_pz[pi_plus_id]);
    return pi_plus;
}

TVector3 TMiniNtupleAnalyzer::get_pi_minus() {
    int pi_minus_id = get_pi_minus_id();
    TVector3 pi_minus(Fmck_px[pi_minus_id], Fmck_py[pi_minus_id], Fmck_pz[pi_minus_id]);
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

Double_t TMiniNtupleAnalyzer::getThetaStar(TLorentzVector pi1, TLorentzVector pi2) {

    const Float_t M_PION = 0.139570;

    TLorentzVector rho = pi1 + pi2;
    Double_t    mass = rho.M();

    TVector3 pi1_p = pi1.Vect();
    TVector3 pi2_p = pi2.Vect();
    TVector3 rho_p = rho.Vect();

//     TVector3 pi1_p = get_pi_plus();
//     TVector3 pi2_p = get_pi_minus();
//     TVector3 rho_p = pi1_p + pi2_p;

    Double_t cos_theta_lab = pi1_p.Dot(rho_p)/(pi1_p.Mag() * rho_p.Mag());
    Double_t pT_rel = sqrt(1-cos_theta_lab*cos_theta_lab) * pi1_p.Mag();
    // pT is invariant
    Double_t P_star = sqrt(mass*mass/4 - M_PION * M_PION);
    Double_t sin_theta_star = pT_rel / P_star;
    return TMath::ASin(sin_theta_star);
}
