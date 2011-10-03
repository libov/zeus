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

// Sasha's reweighting class
#include <weight_function.h>

//Loops over the sample and performs analysis
void TMiniNtupleAnalyzer::Loop(Bool_t reject_cb_ari) {
    // helping variable
    Int_t  Nevents;
    unsigned        nvertices_ora=0;
    unsigned        nvertices_cn=0;
    unsigned        nevents_more_vetices_ora = 0;
    unsigned        nevents_more_vetices_cn = 0;
    // check if user selected to run in a test mode
    unsigned    first_event=0;
    if (fTestMode) {
        Nevents = fTestNumberOfEvents;
        first_event = fTestFirstEvent;
    } else {
        Nevents = fNevents;
    }

    // some options, hardcoded at the moment;
    // TODO: check whether more flexibility is needed (e.g. setting these variables outside the class)
    Bool_t  estimate_trackeff_uncertainty_crude = 0;

    // let user know how many events will be processed
    cout << "INFO: " << Nevents << " events will be processed" << endl;

    // get a pointer to inclusive bin - NOT USED AT THE MOMENT
    TGlobalBin      *inclusiveBin = NULL;
    TIter           Iter_TGlobalBin_event(fList_TGlobalBin);
    inclusiveBin = (TGlobalBin*) Iter_TGlobalBin_event.Next();
    if ( (inclusiveBin == NULL) || (inclusiveBin -> BinName != "bin1")) {
        cout << "ERROR: not able to get the global bin" << endl;
        abort();
    }

    // initialize Sasha's reweighting class object according to his recipe
    TRew            rewObj(&Fmck_nstor, Fmck_id, Fmck_prt, Fmck_daug);
    Double_t        FragFracBRWeight = 1;

    // quite often we need to distinguish charm and beauty so let's define these flags once
    fIsCharm = false;
    fIsBeauty = false;
    if (fIsMC) {
        if (fSubSet.getFlavourENUM() == TSubSet::kCHARM) fIsCharm = true;
        if (fSubSet.getFlavourENUM() == TSubSet::kBEAUTY) fIsBeauty = true;
        // sanity checks
        if (fIsCharm and fIsBeauty) {
            cout << "ERROR from Loop(): something is wrong with flavour identification" << endl;
            abort ();
        }
        if ( (!fIsCharm) and (!fIsBeauty) and (fSubSet.getFlavourENUM() != TSubSet::kLIGHT)) {
            cout << "ERROR from Loop(): something is wrong with flavour identification (none of the flavours selected)" << endl;
            cout << fSubSet.getFlavourENUM() << endl;
            abort ();
        }
    }

    // ********************************************************************************************
    // ********************************************************************************************
    // ************************************* MAIN EVENT LOOP **************************************
    // ********************************************************************************************
    // ********************************************************************************************
    for (int i=first_event; i < first_event+Nevents; i++) {

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

        //sanity checks: array bounds check
        checkArrayBounds();

        // in case selected to calculate data luminosity (data only):
        // get a runnumber and increment an event counter for this run,
        // skip all further processing
        if (fOnlyCalculateEventsPerRun && (!fIsMC) ) {
            // increment event counter for ALL
            fEventsPerRun_ALL[Runnr]++;

            // this one only for events that we select
            #ifdef CN_VERSION_V02
            if ( (Evtake > 0) && (Mvdtake > 0) ) {
                fEventsPerRun_EVTAKE_MVDTAKE[Runnr]++;
            }
            #endif

            #ifdef CN_VERSION_V04
            if ( ((Evtake_iwant == 1) || (Evtake_iwant == 2)) && (Mvdtake > 0) ) {
                fEventsPerRun_EVTAKE_MVDTAKE[Runnr]++;
            }
            #endif

            // WHAT HAS TO BE USED FOR V06? TAKING THE SAME AS FOR V04 FOR THE TIMEBEING
            #ifdef CN_VERSION_V06
            if ( ((Evtake_iwant == 1) || (Evtake_iwant == 2)) && (Mvdtake > 0) ) {
                fEventsPerRun_EVTAKE_MVDTAKE[Runnr]++;
            }
            #endif

            // don't do any further processing
            continue;
        }

        // ********************************************************************************************
        // ********************************************************************************************
        // the main analysis starts:
        // Mostly calculation of relevant variables that determine which bin will be fired
        // and how to proceed with event;
        // the good thing is to implement some variables as TMiniNtupleAnalyzer members;
        // certain operations can be done for all bins, while others should be done for
        // each bin (e.g histograms filling)
        // put everything you can before loop over bins, so that it takes less CPU time,
        // e.g. in order to use some variables in binning they should be calculated BEFORE the loop
        // over bins! (and I guess it's better to implement them as members)
        // e.g. eta of jet with as. svtx
        // ********************************************************************************************
        // ********************************************************************************************

        // set the variables, needed for the transformation to the gamma-p frame
        get_gammaP_boost();

        // get the weight from Sasha's reweighting routine
        // NOTE: this is done before any selection, also on true level, because
        // this weighting has to be applied also on true level, where we might have
        // events outside true level fiducial volume, due to migrations
        if (fSashasReweighting && (fIsCharm || fIsBeauty) ) {
            if (fIsCharm) FragFracBRWeight = rewObj.GetEventWeight(true);
            else if (fIsBeauty) FragFracBRWeight = rewObj.GetEventWeight(false);
        }

        // ********************************************************************************************
        // ********************************************************************************************
        // *********************************** True level analysis ************************************
        // ********************************************************************************************
        // ********************************************************************************************

        // Calculate number of jets that satisfy true level cuts. Should be done before any cuts on reconstructed level.
        if ( fIsMC ) {
            // Define fiducial volume for analysis, event level.
            Bool_t  InFiducial = true;
            // TODO: cuts are now hardcoded, moreover they are duplicated elsewhere!! to be improved!
            if ( ( Mc_q2_cr < 5.) || ( Mc_q2_cr > 1000.) ) InFiducial = false;
            fTrue_y = Mc_q2_cr / (318.*318.* Mc_x_cr);
            if ( ( fTrue_y < 0.02 ) || ( fTrue_y > 0.7 ) ) InFiducial = false;

            // if this MC event passes true cuts on Q2 and y:
            if (InFiducial) {

                // apply weight for the true cross-sections (for charm and beauty MC)
                Bool_t  weight_true = false;
                if ( fIsCharm ) {
                    fTrueQ2Weight = (TMath::Exp(-0.486-0.0158*Mc_q2_cr)+0.781);
                    weight_true = true;
                }
                if ( fIsBeauty ){
                    fTrueQ2Weight = (TMath::Exp(-0.599-0.00389*Mc_q2_cr)+0.631);
                    weight_true = true;
                }

                // variable to store a weight for fragmentation fraction studies
                fZstring_weight = 1;

                // some histograms are desirable to have, but they are quite CPU
                // expensive to fill for every single GlobalBin (i.e. in the loop below);
                // hence filling it here once for the inclusive bin
                inclusiveBin -> FillHistogram("Mc_q2", Mc_q2);
                inclusiveBin -> FillHistogram( "Nhbmjets", Nhbmjets);

                // loop over all bins to fill histograms, which will be used later for
                // true cross-section calculation
                TGlobalBin      *currentTGlobalBin;
                TIter           Iter_TGlobalBin(fList_TGlobalBin);
                while ( (currentTGlobalBin=(TGlobalBin*) Iter_TGlobalBin.Next()) ) {
                    /** Check if MC event is in current bin, true event level
                    *  (see VaribalePhase for variables classification)
                    */
                    if ( ! currentTGlobalBin->CheckGlobalBin(kTrueVarEvent) ) continue;

                    // set weighting factor
                    // reset from previous event
                    currentTGlobalBin -> ApplyWeighting (false);
                    // set if needed; NB. in principle could do it just before the loop over bins!!
                    if (weight_true) {
                        currentTGlobalBin -> ApplyWeighting (true);
                        currentTGlobalBin -> SetWeightingFactor (fTrueQ2Weight);
                    }

                    //fill_parton_histograms(currentTGlobalBin);
                    // if (currentTGlobalBin -> BinName == "bin1") print_fmckin_table();

                    // get a fragmentation function weight, if selected so;
                    // do this for the 1st bin only and apply that afterwards for every bin
                    // TODO: at the moment, there's no check whether there's already a weighinh histo or not;
                    // in principle, we first want to run the code in order to get the weighting function,
                    // and only later apply it...
                    if ((currentTGlobalBin -> BinName == "bin1") && fFragmentationReweighting && (fIsCharm || fIsBeauty)) {
                        get_Zstring_weight(currentTGlobalBin);
                    }

                    // set fragmentation function weighting factor
                    if (fFragmentationReweighting && (fIsCharm || fIsBeauty) ) {
                        Double_t        old_factor = currentTGlobalBin -> GetWeightingFactor ();
                        Double_t        new_factor = old_factor;
                        if (fIsCharm) {
                            new_factor = old_factor * ( 1 - (1 - fZstring_weight) * fCharmFragm_variation_size);
                        } else if (fIsBeauty) {
                            new_factor = old_factor * ( 1 - (1 - fZstring_weight) * fBeautyFragm_variation_size);
                        } else {
                            cout << "ERROR from Loop(): shouldn't get here" << endl;
                            abort();
                        }
                        currentTGlobalBin -> SetWeightingFactor (new_factor);
                    }

                    // apply Sasha's reweighting
                    if (fSashasReweighting && (fIsCharm || fIsBeauty) ) {
                        // apply the weight
                        Double_t        old_factor = currentTGlobalBin -> GetWeightingFactor ();
                        Double_t        new_factor = old_factor * FragFracBRWeight;
                        currentTGlobalBin -> SetWeightingFactor (new_factor);
                    }

                    // Calculate number of true jets in current bin; will be used at the fitter level
                    // to get the true cross-sections
                    // loop over the true jets
                    for (int trueJet = 0; trueJet < Nhbmjets; trueJet++) {

                        // create root lorentz vectors whith jet 4-momentum
                        TLorentzVector	jet(Pxhbmjet[trueJet], Pyhbmjet[trueJet], Pzhbmjet[trueJet], Ehbmjet[trueJet]);
                        /** Set values for members fTrueJetEta, fTrueJetPhi and fTrueJetEt - will be used in CheckGlobalBin()
                        */
                        fTrueJetEta=jet.Eta();
                        fTrueJetEt=jet.Et();
                        fTrueJetPhi=jet.Phi();

                        // ROOT gives values in range [-pi, pi]. We need [0, 2*pi]
                        if (fTrueJetPhi<0) fTrueJetPhi += (2*TMath::Pi());

                        currentTGlobalBin->FillHistogram( "truejetet1", fTrueJetEt);
                        currentTGlobalBin->FillHistogram( "truejeteta1", fTrueJetEta);
                        
                        // ------------------------------------------------------------------

                        /** Fiducial volume cuts, jet level.
                        */
                        // TODO: these cuts are hardcoded here and duplicated elsewhere!!! to be improved!!
                        if ( ( fTrueJetEta > 2.2 ) || ( fTrueJetEta < - 1.6 ) ) continue;
                        if ( fTrueJetEt < fJetEtCut ) continue;

                        /** Check if jet is in current bin, jet level
                        */
                        if ( ! currentTGlobalBin -> CheckGlobalBin (kTrueVarJet) ) continue;
                        currentTGlobalBin->FillHistogram( "truejets", 0);
                        currentTGlobalBin->FillHistogram( "truejetet", fTrueJetEt);
                        currentTGlobalBin->FillHistogram( "truejeteta", fTrueJetEta);
                    }

                    // resolution histograms - fill on request only [SetStudyResolutions(true)] since
                    // this is quite CPU expensive here in this loop.
                    if (fStudyResolutions) {
                        currentTGlobalBin->FillHistogram("sira_px_reso", f_k_prim_reco.Px() - f_k_prim_true.Px());
                        currentTGlobalBin->FillHistogram("sira_py_reso", f_k_prim_reco.Py() - f_k_prim_true.Py());
                        currentTGlobalBin->FillHistogram("sira_pz_reso", f_k_prim_reco.Pz() - f_k_prim_true.Pz());
                        currentTGlobalBin->FillHistogram("sira_E_reso", f_k_prim_reco.E() - f_k_prim_true.E());
                        currentTGlobalBin->FillHistogram("q2_reco_reso", fq.M2() - f_true_q.M2());
                        currentTGlobalBin->FillHistogram("q2da_reso", Siq2da[0] - TMath::Abs(f_true_q.M2()));
                        currentTGlobalBin->FillHistogram("q2el_reso", Siq2el[0] - TMath::Abs(f_true_q.M2()));
                        currentTGlobalBin->FillHistogram("q2jb_reso", Siq2jb[0] - TMath::Abs(f_true_q.M2()));
    
                        currentTGlobalBin->FillHistogram("Wda_reso", fWda - fW_true);
                        currentTGlobalBin->FillHistogram("W_reso", f_gamma_p.M() - fW_true);
    
                        currentTGlobalBin->FillHistogram("photon_energy_gp_reso", fq.E() - f_true_q.E());
                    }

                    // calculate x_gamma on true level: based on parton and also hadron jets;
                    // to save some time, doing this for the 1st bin only
                    if ( currentTGlobalBin -> BinName == "bin1") {

                        vector<TLorentzVector>  parton_jets;
                        for (int i=0; i<Npmjets; i++) {
                            TLorentzVector  parton_jet(Pxpmjet[i], Pypmjet[i], Pzpmjet[i], Epmjet[i]);
                            parton_jets.push_back(parton_jet);
                        }

                        vector<TLorentzVector>  hadron_jets;
                        for (int i=0; i<Nhbmjets; i++) {
                            TLorentzVector  hadron_jet(Pxhbmjet[i], Pyhbmjet[i], Pzhbmjet[i], Ehbmjet[i]);
                            hadron_jets.push_back(hadron_jet);
                        }

                        // fill the histos
                        Float_t x_gamma_partons = get_x_gamma(parton_jets, false);
                        if ( x_gamma_partons >= 0 ) currentTGlobalBin->FillHistogram("x_gamma_true_partons", x_gamma_partons);
                        Float_t x_gamma_hadrons = get_x_gamma(hadron_jets, false);
                        if ( x_gamma_hadrons >= 0 ) currentTGlobalBin->FillHistogram("x_gamma_true_hadrons", x_gamma_hadrons);
                    }

                    currentTGlobalBin -> ApplyWeighting (false);    // extra protection ;)

                }   // end loop over global bins
            }   // end if (isInFiducial)
        }   // end if (fIsMC) condition

        // check whether this is only for true studies and skip if the case
        if (fTrueLevelStudies) continue;

        // ********************************************************************************************
        // ********************************************************************************************
        // ******************************* part2 - reco level analysis ********************************
        // ********************************************************************************************
        // ********************************************************************************************

        // check whether this event passes recostructed level DIS cuts
        if ( ! this -> IsDIS() ) continue;

        fFillMirrored=false;    // this is used in TGLobalBin::FillHistogram()

        //Exclude heavy quarks from ARIADNE light flavour MC
        if (fIsMC && (fSubSet.getFlavourENUM() == TSubSet::kLIGHT) && reject_cb_ari && (Ncb>0)) continue;

        #ifdef CN_VERSION_V02
        //  beam spot correction for beam slope 07/04/2010 (before was in significance calculation)
        if (! fIsMC) {
            // for v02e (Vtxredprm_z is called differently in v04)
            Bspt_x = Bspt_x + Bspt_dxdz * (Vtxredprm_z - Bspt_z);
            Bspt_y = Bspt_y + Bspt_dydz * (Vtxredprm_z - Bspt_z);
        } else if (fIsMC) {
            // for v02e (Vtxredprm_z is called differently in v04)
            Bspt_x = Bspt_x + Vtxredprm_z * (-0.00027) ;
            Bspt_y = Bspt_y + Vtxredprm_z * (-0.00013) ;
        }
        #endif

        // Select Secondary Vertices
        // this is specific for different CN versions, hence ifdef statements

        // some initializations
        fSecondaryVertexFound = false;
        fVertices.clear();

        #ifdef CN_VERSION_V02
        // for v02: loop over jets in ktjetsA algorithm, check whether there is 
        // a corresponding jet in ktjetsB block, otherwise skip this jet
        for (int vertex=0; vertex < Kt_njet_a; vertex++) {

            fDebugSVTX->Fill(0);

            // try to match one this jet (from block A) to one of the jets in block B
            // helping variables
            Bool_t      jetAinB=false;
            Int_t       correspjetB=-1;
            // loop over jets in block B
            for (int jetB=0; jetB<Kt_njet_b; jetB++) {
                // check whether Eta, Et and Phi are the same for both jets
                Float_t     deltaEta=Kt_etajet_a[vertex]-Kt_etajet_b[jetB];
                Float_t     deltaPhi=Kt_phijet_a[vertex]-Kt_phijet_b[jetB];
                Float_t     deltaEt=Kt_etjet_a[vertex]-Kt_etjet_b[jetB];
                if ( (deltaEta==0) and (deltaPhi==0) and  (deltaEt==0) ) {
                    // found a match!
                    jetAinB=true;
                    correspjetB=jetB;
                }
            }

            // skip this block-A-jet if couldn't find a corresponding block-B-jet.
            if ( !jetAinB ) continue;
            fDebugSVTX->Fill(1);

            // for systematic studies (jet energy scale uncertainty)
            Float_t     ZUFO_jet_ratio=0;
            Float_t     CAL_total_ratio=0;
            int         ZUFO_type=-99;
            if (fIsMC && fDoJetEnergyScaleSyst) {
                // loop over ZUFOs and associate them to our jets
                double phi_jet =  Kt_phijet_b[correspjetB];
                double eta_jet =  Kt_etajet_b[correspjetB];
                double et_jet =  Kt_etjet_b[correspjetB];
                double theta_jet = 2 * atan( TMath::Exp( (-1) * eta_jet) );
                double e_jet = et_jet/sin(theta_jet);
                        
                unsigned    matched = 0;
                double      matched_et = 0;
                double      matched_e = 0;
                unsigned    from_CAL = 0;
                double      matched_e_CAL = 0;
                for (unsigned m = 0; m < Nzufos; m++ ) {

                    TLorentzVector zufo_Lorentz(Zufo[m][0], Zufo[m][1], Zufo[m][2], Zufo[m][3]);

                    double  phi_zufo = zufo_Lorentz.Phi();
                    double  eta_zufo = zufo_Lorentz.Eta();
                    double  et_zufo = zufo_Lorentz.Et();
                    double  e_zufo = zufo_Lorentz.E();

                    // ROOT gives values in range [-pi, pi]. We need [0, 2*pi]
                    if (phi_zufo<0) phi_zufo += (2*TMath::Pi());

                    if (e_zufo != Zufo[m][3]) {
                        cout << "energy zufo error" << endl;
                        cout << et_zufo << " " << e_zufo << endl;
                        abort();
                    }

                    double  dphi = phi_jet - phi_zufo;
                    double  deta = eta_jet - eta_zufo;

                    double R = sqrt( dphi*dphi + deta*deta );
            
                    if (R<1) {
                        matched++;
                        matched_et += et_zufo;
                        matched_e += e_zufo;
                        //inclusiveBin -> FillHistogram("ZUFO_type", Tufo[m][0]);
                        ZUFO_type = Tufo[m][0];
                        if ( (Tufo[m][0] == 30) || (Tufo[m][0] == 31) ) {
                            from_CAL ++;
                            matched_e_CAL += e_zufo;
                        }
                    }
                }

                // now get the fraction of the jet energy that was measured by the calorimeter
                // if none of ZUFOs were matched to a jet (why such events appear?),
                // then take the fraction to be 1 (i.e. the total jet energy - hope it's
                // a conservative approach)
                double CAL_fraction = 0;
                if (matched !=0 ) {
                    CAL_fraction = matched_e_CAL / matched_e;
                } else {
                    cout << "WARNING: NO ZUFOS WERE MATCHED TO THE JET!! TAKING THE TOTAL JET ENERGY AS ITS CALORIMETRIC PART\n";
                    cout << "EVENT: " << i << endl;
                    CAL_fraction = 1;
                }

                // cross-check: one can vary total jet energy, then
                // the following variable should equal to unity
                if (fVaryTotalJetEnergy) {
                    CAL_fraction = 1;
                }
                  
                double  e_jet_CAL = e_jet * CAL_fraction;
                        
                double jet_energy_variation = e_jet_CAL * fJetEnergyUncertainty;

                Kt_etjet_b[correspjetB] += jet_energy_variation * sin(theta_jet);
                Kt_etjet_a[vertex] += jet_energy_variation * sin(theta_jet);

                ZUFO_jet_ratio = matched_e / e_jet; 
                CAL_total_ratio =  matched_e_CAL / matched_e;
            }

            // JET ET CUT
            if ( Kt_etjet_b[correspjetB] < fJetEtCut) continue;
            fDebugSVTX->Fill(2);

            // JET ETA CUT
            if ( ( Kt_etajet_b[correspjetB] > 2.2 ) || ( Kt_etajet_b[correspjetB] < -1.6 ) ) continue;
            fDebugSVTX->Fill(3);

            // calculate significance of the vertex
            Float_t Significance = CalculateSignificance(vertex);

            // check whether it was successful
            if (Significance==(-999)) continue;
            fDebugSVTX->Fill(4);
            if (Significance==(-998)) continue;
            fDebugSVTX->Fill(5);

            // calculate also projected decay length
            Float_t     ProjDecayLength = CalculateProjDecayLength(vertex);

            // calculate chi2 over NDOF (in the ntuples we have only chi2)
            Float_t     chi2ndf=Vtxsec_chi2[vertex]/Vtxsec_ndf[vertex];
            // chi2/NDOF cut
            if (chi2ndf>6.) continue;
            fDebugSVTX->Fill(6);

            // create a vertex object to be stored for later processing
            TVertex	vtx;
            vtx.Significance = Significance;
            vtx.id = vertex;
            vtx.ProjDecayLength = ProjDecayLength;
            vtx.fJetB = correspjetB;
            vtx.chi2ndf = chi2ndf;
    
            // for jet energy scale studies
            if (fDoJetEnergyScaleSyst) {
                vtx.SetZUFO_jet_ratio(ZUFO_jet_ratio);
                vtx.SetCAL_total_ratio(CAL_total_ratio);
                vtx.SetZUFO_type(ZUFO_type);
            }
    
            // ok, a good vertex was found, store it to array and raise the good-vtx-found flag
            fVertices.push_back(vtx);
            fSecondaryVertexFound=true;
        }
        #endif

        #if defined CN_VERSION_V04 || defined CN_VERSION_V06
        if (fRedoVertexing) {
            findVertices();
        } else {
            // secondary vertex selection - version v04/v06
            // don't loop over jets anymore as in v02, loop over all secondaries instead
            for (int vertex=0; vertex < Nr_secvtx; vertex++) {
                                                    
                fDebugSVTX->Fill(0);
    
                // consider only vertices with jet from block B as a reference
                // type 2 = ktJetsB as a reference
                // (no need to match jets A to B anymore)
                if (Vtxsec_type[vertex] != 2) continue;
                fDebugSVTX->Fill(1);
    
                // get id of the vertex
                int correspjetB = Vtxsec_ref[vertex] - 1;    // -1 is to correct for fortran/C++ indexing convention
    
                // JET ET CUT
                if ( Kt_etjet_b[correspjetB] < fJetEtCut) continue;
                fDebugSVTX->Fill(2);
    
                // JET ETA CUT
                if ( ( Kt_etajet_b[correspjetB] > 2.2 ) || ( Kt_etajet_b[correspjetB] < -1.6 ) ) continue;
                fDebugSVTX->Fill(3);
    
                // now look at the vertex; TVertex class is designed to deal with e.g. calculations of significance
                // and revertexing in case of evaluation of tracking uncertainty due to tracking inefficiency
                TVertex cVtx;
    
                // check whether smearing should be applied
                if (fApplySmearing && fIsMC) { 
                    cVtx.SetApplySmearing(true);
                } else { 
                    cVtx.SetApplySmearing(false);
                }
                            
                // set coordinates of the secondary vertex as given from Orange
                cVtx.SetVertexCoordinates(Vtxsec_x[vertex], Vtxsec_y[vertex], Vtxsec_z[vertex]);
    
                // set coordinates of the primary vertex; TODO: this might be wrong conceptually
                // that we have to store primary vertex coordinates for the secondary vertex, but stick to this now
                // NOTE: if reduced primary vertex to be calculated for each vertex, then this is correct
                #if defined CN_VERSION_V04
                Float_t     bsptx;
                Float_t     bspty;
                if (! fIsMC){
                    // v04b
                    bsptx = Bspt_x + Bspt_dxdz * (Vtxredprm_z[Nr_redprm - 1] - Bspt_z);
                    bspty = Bspt_y + Bspt_dydz * (Vtxredprm_z[Nr_redprm - 1] - Bspt_z);
                }
    
                if (fIsMC) {
                    // v04b
                    bsptx = Bspt_x + Vtxredprm_z[Nr_redprm - 1] * (-0.00027) ;
                    bspty = Bspt_y + Vtxredprm_z[Nr_redprm - 1] * (-0.00013) ;
                }
                cVtx.SetPrimaryVertexCoordinates(bsptx, bspty, Vtxredprm_z[Nr_redprm - 1]);
                #endif
                #if defined CN_VERSION_V06
                Float_t     bsptx;
                Float_t     bspty;
                if (! fIsMC){
                    // v06
                    bsptx = Bspt_x + Bspt_dxdz * (Vtxredprim_z[Nr_redprim - 1] - Bspt_z);
                    bspty = Bspt_y + Bspt_dydz * (Vtxredprim_z[Nr_redprim - 1] - Bspt_z);
                }
    
                if (fIsMC) {
                    // v06
                    bsptx = Bspt_x + Vtxredprim_z[Nr_redprim - 1] * (-0.00027) ;
                    bspty = Bspt_y + Vtxredprim_z[Nr_redprim - 1] * (-0.00013) ;
                }
                cVtx.SetPrimaryVertexCoordinates(bsptx, bspty, Vtxredprim_z[Nr_redprim - 1]);
                #endif
    
                // set reference axis for this vertex
                cVtx.SetAxisVector(Kt_etajet_b[correspjetB], Kt_phijet_b[correspjetB] );
    
    
                TSubSet::Period period = fSubSet.getPeriodENUM();
                if ( (period == TSubSet::k0304P) || (period == TSubSet::k03P) || (period == TSubSet::k04P) || (period == TSubSet::k0607P) || (period == TSubSet::k06P) || (period == TSubSet::k07P) ){
                    Bspt_xer=0.0088;
                    Bspt_yer=0.0024;
                } else if ((period==TSubSet::k05E) || (period==TSubSet::k06E))	{
                    Bspt_xer=0.0080;
                    Bspt_yer=0.0022;
                }
    
                // set beam spot size as error on primary vertex coordinate
                // only X, Y are relevant, NULL for Z is just dummy
                cVtx.SetPrimaryVertexCoordinatesError(Bspt_xer, Bspt_yer, 0 );
    
                // now get secondary vertex covariance matrix from orange, and set it to the vertex
                Float_t * Vtxsec_cov_tmp = new Float_t [6];
                for (int k=0; k<6; k++) Vtxsec_cov_tmp[k] = Vtxsec_cov[vertex][k];
                cVtx.SetVertexCovariance(Vtxsec_cov_tmp);
                delete[] Vtxsec_cov_tmp;
    
                // now ready for significance calculation
                Float_t     Significance = cVtx.CalculateVertexSignificance();
    
                // I'm not sure whether this can be removed for v04, so keep for the timebeing (the 2nd one has some effect!)
                if (Significance==(-999)) continue;
                fDebugSVTX->Fill(4);
                if (Significance==(-998)) continue;
                fDebugSVTX->Fill(5);
    
                // chi2ndf is available directly from orange
                Float_t chi2ndf=Vtxsec_chi2[vertex]/Vtxsec_ndf[vertex];
                cVtx.chi2ndf=chi2ndf;
                cVtx.SetVertexMass(Vtxsec_mass[vertex]);
                cVtx.SetChi2(Vtxsec_chi2[vertex]);
                cVtx.SetNTracks(Vtxsec_multi[vertex]);
    
                // leftover from v02
                cVtx.id=vertex;
                cVtx.fJetB=correspjetB;
    
                // if selected, do a uncertainty estimation due to tracking inefficiency,
                // that is drop tracks with a certain probability which is a measure of how well
                // tracking efficiency is known in the Monte Carlo simulation
                if (fIsMC && fDropTracks) {
    
                    // specific for v04/v06; get track helix parameters and covariance for tracks
                    // belonging to a secondary vertex
    
                    // some initializations
                    Float_t     trackhelix[60][5];
                    Float_t     trackhelixcov[60][15];
                    Float_t     trackmomentum[60];
                    Int_t       trackIDs[60];
                    
                    // loop over tracks belonging to the vertex
                    for (int k=0; k<Vtxsec_multi[vertex]; k++) {
    
                        // try to find this track in the Tracking block
                        int track_id = -1;
                        for (int j = 0; j<Trk_ntracks; j++){
                            if (Trk_id[j] == Vtxsec_zttid[vertex][k]) {
                                track_id = j;
                                break;
                            }
                        }
    
                        // sanity check
                        if (track_id == -1) {
                            cout << "Unable to find vertex track in the Tracking block. Terminating" << endl;
                            abort();
                        }
    
                        // get helix parameters from the Tracking block
                        for (int j=0; j<5; j++){
                            trackhelix[k][j] = Trk_helpar[track_id][j]; 
                        }
    
                        // get helix parameter covariance from orange
                        for (int j=0; j<15; j++){
                            trackhelixcov[k][j] = Trk_covmat[track_id][j];
                        }
    
                        // get track momentum
                        trackmomentum[k] = Trk_helmom[track_id];

                        // now save also track ID
                        trackIDs[k] = track_id;
                    }
    
                    // ok, set all track parameters
                    cVtx.SetTrackParameters(Vtxsec_multi[vertex], trackhelix, trackhelixcov, trackmomentum);
                    cVtx.SetVertexTracks(Vtxsec_multi[vertex], trackIDs);
    
                    // do the fits
                    // first redo the fit without track dropping in order to check that results
                    // are the same as in ORANGE
                    cVtx.SetDropTracks(false);
                    // refit the vertex; this makes the fit, updates relevant TVertex parameters
                    // (coordinates and covariance matrix), recalculates significance, chi2ndf, mass and updates those parameters
                    cVtx.RefitVertex();
    
                    // various sanity checks below (to check if results are the same as in orange)
                    const Float_t   EQUALITY_CRITERION = 1e-6;
                    // sanity check: compare to what we got in orange
                    // now get new values of vertex coordinates
                    Float_t   vertexX_refitted = 0;
                    Float_t   vertexY_refitted = 0;
                    Float_t   vertexZ_refitted = 0;
                    cVtx.GetVertexCoordinates(vertexX_refitted, vertexY_refitted, vertexZ_refitted);
                    Float_t   diffX = fabs ( (Vtxsec_x[vertex] - vertexX_refitted) / Vtxsec_x[vertex] );
                    Float_t   diffY = fabs ( (Vtxsec_y[vertex] - vertexY_refitted) / Vtxsec_y[vertex] );
                    Float_t   diffZ = fabs ( (Vtxsec_z[vertex] - vertexZ_refitted) / Vtxsec_z[vertex] );
    
                    if ( ( diffX > EQUALITY_CRITERION ) || ( diffY > EQUALITY_CRITERION ) || ( diffZ > EQUALITY_CRITERION )) {
                        cout << "WARNING: refitted vertex coordinates without track dropping are not the same as from orange!! Terminating!" << endl;
                        cout << "X: " << Vtxsec_x[vertex] << " " << vertexX_refitted << endl;
                        cout << "Y: " << Vtxsec_y[vertex] << " " << vertexY_refitted << endl;
                        cout << "Z: " << Vtxsec_z[vertex] << " " << vertexZ_refitted << endl;
                    }
    
                    // another sanity check: covariance matrices
                    Float_t * cov_refitted = cVtx.GetVertexCovariance();
                    for (unsigned j = 0; j < 6; j++ ) {
                        Float_t diff = fabs ( (Vtxsec_cov[vertex][j] -  cov_refitted[j]) / Vtxsec_cov[vertex][j] );
                        if ( diff > EQUALITY_CRITERION ) {
                            cout << "WARNING: refitted vertex covariance matrix without track dropping are not the same as from orange!!";
                            cout << Vtxsec_cov[vertex][j] << " --> " << cov_refitted[j] << endl;
                        }
                    }
    
                    // mass sanity check
                    Float_t   mass_diff = fabs ( (Vtxsec_mass[vertex] - cVtx.GetVertexMass()) / Vtxsec_mass[vertex] );
                    if (mass_diff > EQUALITY_CRITERION) {
                        cout << "WARNING: Mass of refitted vertex isn't equal to the mass from Orange!\n";
                        cout << Vtxsec_mass[vertex] <<" -> " << cVtx.GetVertexMass() << endl;
                    }
                            
                    // chi2ndf sanity check
                    Float_t   diff_chi2ndf = fabs((chi2ndf - cVtx.chi2ndf) / chi2ndf);
                    if (diff_chi2ndf > EQUALITY_CRITERION) {
                        cout << "WARNING: chi2/ndf after refit isn't equal to the value from Orange:\n";
                        cout << chi2ndf << " vs " << cVtx.chi2ndf << endl;
                    }
    
                    // drop tracks from the vertex and redo the fit if selected
                    if (fIsMC && fDropTracks) {
                        cVtx.SetDropTracks(true);
                        cVtx.SetDropTrackProbability(fDropProbability);
                        //NOTE: all the relevant vertex parameters are updated automatically when calling to RefitVertex();
                        bool  fit_successful = cVtx.RefitVertex();
                        //skip this vertex in case of not successfull fit (2 track vertex with dropped track)
                        if ( ! fit_successful ) continue; 
                    }
                }
    
                // the chi2 cut
                if (cVtx.chi2ndf>6.) continue;
                fDebugSVTX->Fill(6);
    
                // and the mass cut
                 if ( (cVtx.GetVertexMass()<1.) || (cVtx.GetVertexMass()>6) ) continue;
                fDebugSVTX->Fill(7);
    
                // ok, this is a good vertex/jet; store it to the vector and raise the flag that 
                // there was at least one good vertex in this event
                fVertices.push_back(cVtx);
                fSecondaryVertexFound=true;
            } // end loop over vertices
        } // end if statement: else 
        #endif

//         for (int vtx=0; vtx < fVertices.size(); vtx++ ) {
//             cout << "significance: " <<fVertices[vtx].GetVertexSignificance() << endl;
//         }


//         findVertices(); // debug case
//         if (fVertices.size() > fVerticesRefitted.size()) nevents_more_vetices_ora++;
//         if (fVertices.size() < fVerticesRefitted.size()) nevents_more_vetices_cn++;
//         nvertices_ora += fVertices.size();
//         nvertices_cn += fVerticesRefitted.size();
//         for (int vtx=0; vtx < fVertices.size(); vtx++ ) {
//             cout << "sign: " <<fVertices[vtx].GetVertexSignificance() << " -- vs -- " << fVerticesRefitted[vtx].GetVertexSignificance()<< "= ";
//             Double_t    diff = fVertices[vtx].GetVertexSignificance() - fVerticesRefitted[vtx].GetVertexSignificance();
//             cout << diff << endl;
// //             cout << "mass: " <<fVertices[0].GetVertexMass() << " -- vs -- " << fVerticesRefitted[0].GetVertexMass()<< "= ";
// //             diff = fVertices[0].GetVertexMass() - fVerticesRefitted[0].GetVertexMass();
// //             cout << diff << endl;
// 
//         }

/*        if (fVerticesRefitted.size() != fVertices.size()) {
            //cout << " *******      ora more   ***********: " << Eventnr << endl;
            cout << "ORANGE FINDER" << endl;
            for (unsigned i=0; i < fVertices.size(); i++) {
                Int_t       ntracks;
                Float_t     trackhelix[60][5];
                Float_t     trackhelixcov[60][15];
                Float_t     trackmomentum[60];
                Int_t       trackIDs[60];
                fVertices[i].GetTrackParameters(ntracks, trackhelix, trackhelixcov, trackmomentum);
                fVertices[i].GetVertexTracks(ntracks, trackIDs);
                fVertices[i].Print();

                for (unsigned trk=0; trk < ntracks; trk++) {
                    cout << "track " << trk << ": " << trackmomentum[trk] << " " << trackIDs[trk] << endl;
                    Int_t   extra_trackID = trackIDs[trk];
                    //Int_t   extra_trackID = 0;
                    cout << Trk_layinner[extra_trackID] << " " << Trk_layouter[extra_trackID] << "; ";
                    cout << Trk_nbr[extra_trackID] + Trk_nbz[extra_trackID] + Trk_nwu[extra_trackID] + Trk_nwv[extra_trackID] << "; ";
                    cout << Trk_nstt[extra_trackID] << "; ";
                    cout << sqrt(Trk_px[extra_trackID]*Trk_px[extra_trackID] + Trk_py[extra_trackID]*Trk_py[extra_trackID] + Trk_pz[extra_trackID]*Trk_pz[extra_trackID])<<"; ";
                    cout << sqrt(Trk_px[extra_trackID]*Trk_px[extra_trackID] + Trk_py[extra_trackID]*Trk_py[extra_trackID])<<";";
                    TVector3 track(Trk_px[extra_trackID], Trk_py[extra_trackID], Trk_pz[extra_trackID]);
                    cout << "(cross: "<< track.Mag() << ", "<< track.Pt()<< "); ";
                    Float_t phi = track.Phi(); if (phi < 0) phi += 2*TMath::Pi();
                    cout << phi << " - " << fVertices[i].GetAxisPhi() << "; " << track.Eta() << " - " << fVertices[i].GetAxisEta() << "; " << endl;
                }


            }
            cout << "CN FINDER" << endl;
            for (int i=0; i < fVerticesRefitted.size(); i++) {
                Int_t       ntracks;
                Float_t     trackhelix[60][5];
                Float_t     trackhelixcov[60][15];
                Float_t     trackmomentum[60];
                Int_t       trackIDs[60];
                fVerticesRefitted[i].GetTrackParameters(ntracks, trackhelix, trackhelixcov, trackmomentum);
                fVerticesRefitted[i].GetVertexTracks(ntracks, trackIDs);
                fVerticesRefitted[i].Print();

                for (int trk=0; trk < ntracks; trk++) {
                    cout << "track " << trk << ": " << trackmomentum[trk] << " " << trackIDs[trk] << endl;
                    Int_t   extra_trackID = trackIDs[trk];
                    //Int_t   extra_trackID = 0;
                    cout << Trk_layinner[extra_trackID] << " " << Trk_layouter[extra_trackID] << "; ";
                    cout << Trk_nbr[extra_trackID] + Trk_nbz[extra_trackID] + Trk_nwu[extra_trackID] + Trk_nwv[extra_trackID] << "; ";
                    cout << Trk_nstt[extra_trackID] << "; ";
                    cout << sqrt(Trk_px[extra_trackID]*Trk_px[extra_trackID] + Trk_py[extra_trackID]*Trk_py[extra_trackID] + Trk_pz[extra_trackID]*Trk_pz[extra_trackID])<<"; ";
                    cout << sqrt(Trk_px[extra_trackID]*Trk_px[extra_trackID] + Trk_py[extra_trackID]*Trk_py[extra_trackID])<<";";
                    TVector3 track(Trk_px[extra_trackID], Trk_py[extra_trackID], Trk_pz[extra_trackID]);
                    cout << "(cross: "<< track.Mag() << ", "<< track.Pt()<< "); ";
                    Float_t phi = track.Phi(); if (phi < 0) phi += 2*TMath::Pi();
                    cout << phi << " - " << fVerticesRefitted[i].GetAxisPhi() << "; " << track.Eta() << " - " << fVerticesRefitted[i].GetAxisEta() << "; " << endl;
                }
            }
        }*/

        /** Loop over the TGlobalBins - fill the histograms
        */
        TGlobalBin      *currentTGlobalBin;
        TIter           Iter_TGlobalBin(fList_TGlobalBin);
        
        // determine the Q2 weight
        Bool_t          weight_reco = false;
        if ( fSampleName.Contains("nc.c") or fSampleName.Contains("ccbar") ){
            fRecoQ2Weight = (TMath::Exp(-0.486-0.0158*Mc_q2_cr)+0.781);
            weight_reco = true;
        }
        if ( fSampleName.Contains("nc.b") or fSampleName.Contains("bbbar") ){
            fRecoQ2Weight = (TMath::Exp(-0.599-0.00389*Mc_q2_cr)+0.631);
            weight_reco = true;
        }

        Bool_t          weight_q2g4 = false;
        if ((fApplyQ2g4Weighting) && (Mc_q2_cr > 4)) weight_q2g4 = 1;

        // now fill the histograms
        // loop over Global Bins and if this event satisfies bin's criteria - fill histograms that belong to the bin
        while (currentTGlobalBin=(TGlobalBin*) Iter_TGlobalBin.Next()) {

            // check if event satisfies bin's criteria (i.e. event level)
            Bool_t      GlobalBinFired=currentTGlobalBin->CheckGlobalBin(kEventVar);
            if (!GlobalBinFired) continue;

            /** \todo check if this command is really needed
            */
            fHistogramsFile->cd(currentTGlobalBin->BinName);

            // reweight Q2 according to Philipp's recipe
            currentTGlobalBin -> ApplyWeighting (false);
            if (weight_reco or weight_q2g4 ) currentTGlobalBin ->ApplyWeighting (true);

            if ( weight_reco && (!weight_q2g4) ) currentTGlobalBin -> SetWeightingFactor (fRecoQ2Weight);
            if ( weight_q2g4  && (!weight_reco) ) currentTGlobalBin -> SetWeightingFactor (fCharmQ2g4Weight);
            if ( weight_reco && weight_q2g4 ) currentTGlobalBin -> SetWeightingFactor (fRecoQ2Weight * fCharmQ2g4Weight);

            // fragmentation function studies - reweight the z distribution
            if (fFragmentationReweighting && fIsMC && (fIsCharm || fIsBeauty)) {
                Double_t        old_factor = currentTGlobalBin -> GetWeightingFactor ();
                Double_t        new_factor = old_factor;
                if (fIsCharm) {
                    new_factor = old_factor * ( 1 - (1 - fZstring_weight) * fCharmFragm_variation_size);
                } else if (fIsBeauty) {
                    new_factor = old_factor * ( 1 - (1 - fZstring_weight) * fBeautyFragm_variation_size);
                } else {
                    cout << "ERROR from Loop(): shouldn't get here" << endl;
                    abort();
                }
                currentTGlobalBin -> SetWeightingFactor (new_factor);
            }

            // apply Sasha's reweighting
            if (fSashasReweighting && (fIsCharm || fIsBeauty) ) {
                // apply it
                Double_t        old_factor = currentTGlobalBin -> GetWeightingFactor ();
                Double_t        new_factor = old_factor * FragFracBRWeight;
                currentTGlobalBin -> SetWeightingFactor (new_factor);
            }

            // fill true Q2 distribution
            if (fIsMC) currentTGlobalBin -> FillHistogram("Mc_q2", Mc_q2);
            currentTGlobalBin->FillHistogram("nvertices", fVertices.size());

            // Now loop over selected vertices and fill histos for each vertex
            if ( !fSecondaryVertexFound )   continue;   // TODO: MOVE OUTSIDE LOOP OVER BINS?????

            // sanity check
            if ( fVertices.size() == 0 ) { 
                cout<<"ERROR: Vertices vector empty but it shouldn't be if we got here!!!"<<endl;
                cout << "Terminating!" << endl;
                abort();
            }

            for ( int j=0; j < fVertices.size(); j++ ) {

                Int_t   jetB=fVertices[j].fJetB;
                Int_t   vertex=fVertices[j].id;

                // TODO: not really sure that this should be different for v02 and v04 - check!
                #ifdef CN_VERSION_V02

                fSignificance = fVertices[j].Significance;
                fRecoJetEta = Kt_etajet_a[vertex];
                fRecoJetEt = Kt_etjet_a[vertex];
                fRecoJetPhi = Kt_phijet_a[vertex];
                Float_t mass = Vtxsec_mass[vertex];
                Int_t   vtx_multi = Vtxsec_multi[vertex];
                Float_t chi2 = Vtxsec_chi2[vertex];
                #endif

                #if defined CN_VERSION_V04 || defined CN_VERSION_V06
                fSignificance = fVertices[j].GetVertexSignificance();
                fRecoJetEta = Kt_etajet_b[jetB];
                fRecoJetEt = Kt_etjet_b[jetB];
                fRecoJetPhi = Kt_phijet_b[jetB];
                Float_t     mass = fVertices[j].GetVertexMass();
                Int_t       vtx_multi = fVertices[j].GetNTracks() - fVertices[j].GetNTracksDropped();
                Float_t chi2 = fVertices[j].GetChi2();
                #endif
                
                // estimate efficiency with the method proposed by Olaf
                if (estimate_trackeff_uncertainty_crude && fIsMC) {
                    // get a random number
                    Double_t    tmp_rand = rnd_eff->Rndm();
                    // cast float to vertex multiplicity
                    Float_t N = (Float_t)Vtxsec_multi[vertex]; // see notes from 09/04/2010
                    // not sure anymore it;s correct in this way (12 March 2011)
                    if (tmp_rand < 0.02 * N) {
                        // drop the vertex if 2 tracks only
                        if ( N < 3) continue;
                        // otherwise scale mass and significance
                        mass = mass * (N - 1)/N;
                        fSignificance = fSignificance * sqrt((N - 1)/N);
                    }
                }


                if ( !currentTGlobalBin -> CheckGlobalBin (kVertexVar) ) continue;
                
                // now weight if this is LF; done here because we weight every
                // jet separately (according to its energy)
                // for the timebeing, don't jet matching to true level and use
                // simply the reconstructed value
                // NB. in principle it overwrites the previous weighting factors: q2 reweightings and fragm. fraction,
                // but the fact that ET reweighting is done only for LF, while those mentioned above -  
                // just for charm or for beauty - there's no contradiction;
                // still this is very obscure and should be done better
            
                if (fIsMC && (fSubSet.getFlavourENUM()==TSubSet::kLIGHT) && fEtReweightingLF) {
                    currentTGlobalBin -> ApplyWeighting(true);
                    Double_t    et_weighting_factor = getEtReweighting(fRecoJetEt);
                    currentTGlobalBin -> SetWeightingFactor(et_weighting_factor);
                }

                // only for v02 because for v04 the mass is cut already at vertex selection stage
                #ifdef CN_VERSION_V02
                currentTGlobalBin->FillHistogram("significance_allmasses", fSignificance);
                #endif

                // NOTE: in v04 this is done in the sec vtx selection loop; can somehow affect??
                if ((mass<1.) || (mass>6)) continue;

                fFillMirrored = true; // following histograms can be mirrored
                currentTGlobalBin -> FillHistogram("vtxsec_multi", vtx_multi);
                currentTGlobalBin -> FillHistogram("vtxsec_chi2", chi2);
                currentTGlobalBin -> FillHistogram("vtxsec_chi2ndf", fVertices[j].chi2ndf);

                currentTGlobalBin->FillHistogram("significance", fSignificance);
                #ifdef CN_VERSION_V02
                currentTGlobalBin->FillHistogram("decay_length", fVertices[j].ProjDecayLength);
                #endif

                #if defined CN_VERSION_V04 || defined CN_VERSION_V06
                currentTGlobalBin->FillHistogram("decay_length", fVertices[j].GetVertexProjectedDecayLength());
                // brand new: track pT. NOTE: works only if tracks are un-dropped!
                Float_t     trackPT[30];
                fVertices[j].GetTrackPt(trackPT);
                for (int trk=0; trk < fVertices[j].GetNTracks(); trk++) {
                    currentTGlobalBin->FillHistogram("track_vtx_pT", trackPT[trk]);
                }
                #endif

                if ( (mass<1.4) && (mass>1.) ) {
                    currentTGlobalBin->FillHistogram("significance_massbin1", fSignificance);
                }
                if ( (mass>1.4) && (mass<2.) ) {
                    currentTGlobalBin->FillHistogram("significance_massbin2", fSignificance);
                }
                if ( (mass>2.) && (mass<6.) ) {
                    currentTGlobalBin->FillHistogram("significance_massbin3", fSignificance);
                }

                currentTGlobalBin->FillHistogram("vtxsec_mass", mass);

                #ifdef CN_VERSION_V02
                currentTGlobalBin->FillHistogram("kt_etjet_a", Kt_etjet_a[vertex]);
                currentTGlobalBin->FillHistogram("kt_etajet_a", Kt_etajet_a[vertex]);
                currentTGlobalBin->FillHistogram("kt_phijet_a", Kt_phijet_a[vertex]);
                currentTGlobalBin->FillHistogram("kt_masjet_a", Kt_masjet_a[vertex]);
                #endif

                // sanity check
                if ( jetB < 0 ) {
                    cout<<"ERROR: jetA not found in jetB!"<<endl;
                    abort();
                }

                currentTGlobalBin->FillHistogram("kt_etjet_b", Kt_etjet_b[jetB]);
                currentTGlobalBin->FillHistogram("kt_etajet_b", Kt_etajet_b[jetB]);
                currentTGlobalBin->FillHistogram("kt_phijet_b", Kt_phijet_b[jetB]);
                currentTGlobalBin->FillHistogram("kt_masjet_b", Kt_masjet_b[jetB]);
                fFillMirrored=false;    // switch off mirroring

                currentTGlobalBin->FillHistogram("xel", TMath::Log10(Sixel[0]));
                currentTGlobalBin->FillHistogram("xjb", TMath::Log10(Sixjb[0]));
                currentTGlobalBin->FillHistogram("xda", TMath::Log10(Sixda[0]));

                currentTGlobalBin->FillHistogram("yel", Siyel[0]);
                currentTGlobalBin->FillHistogram("yjb", Siyjb[0]);
                currentTGlobalBin->FillHistogram("yda", Siyda[0]);

                currentTGlobalBin->FillHistogram("q2el", TMath::Log10(Siq2el[0]));
                currentTGlobalBin->FillHistogram("q2jb", TMath::Log10(Siq2jb[0]));
                currentTGlobalBin->FillHistogram("q2da", TMath::Log10(Siq2da[0]));

                // electron quantities
                currentTGlobalBin->FillHistogram("siecorr", Siecorr[0][2]);
                currentTGlobalBin->FillHistogram("thetael", Sith[0]);
                currentTGlobalBin->FillHistogram("phiel", Siph[0]);
                currentTGlobalBin->FillHistogram("zel", Sipos[0][2]);

                // event quantities
                currentTGlobalBin->FillHistogram("xvtx", Xvtx);
                currentTGlobalBin->FillHistogram("yvtx", Yvtx);
                currentTGlobalBin->FillHistogram("zvtx", Zvtx);

                currentTGlobalBin->FillHistogram("empz", V_h_e_zu-V_h_pz_zu);

                currentTGlobalBin->FillHistogram("ZUFO_jet_ratio", fVertices[j].GetZUFO_jet_ratio());
                currentTGlobalBin->FillHistogram("CAL_total_ratio", fVertices[j].GetCAL_total_ratio());
                currentTGlobalBin->FillHistogram("ZUFO_type", fVertices[j].GetZUFO_type());

                // fill some histos related to track density effects

                // now calculate x_gamma
                // reconstructed jets in the lab frame
                vector<TLorentzVector>  reco_jets_lab;
                for (int jet=0; jet<Kt_njet_b; jet++) {
                    Float_t     theta = 2 * atan (exp( (-1) * Kt_etajet_b[jet]));
                    Float_t     E = Kt_etjet_b[jet] / sin(theta);
                    Float_t     p = sqrt(E*E - Kt_masjet_b[jet]*Kt_masjet_b[jet]);
                    Float_t     pT = p * sin (theta);
                    TLorentzVector  reco_jet;
                    reco_jet.SetPtEtaPhiM(pT, Kt_etajet_b[jet], Kt_phijet_b[jet], Kt_masjet_b[jet]);
                    reco_jets_lab.push_back(reco_jet);
                }
                Float_t x_gamma_lab_jets = get_x_gamma(reco_jets_lab, false);
                if (x_gamma_lab_jets>=0) currentTGlobalBin->FillHistogram("x_gamma_lab_jets", x_gamma_lab_jets);

                // also try to reconstruct x_gamma using a tagged jet
                Float_t x_gamma_lab_jets_tagged = get_x_gamma(reco_jets_lab, false, jetB);
                if (x_gamma_lab_jets_tagged>=0) currentTGlobalBin->FillHistogram("x_gamma_lab_jets_tagged", x_gamma_lab_jets_tagged);

                // jets, reconstructed in the breit frame
                vector<TLorentzVector>  reco_jets_breit;
                for (int jet=0; jet<Kt_njet_d; jet++) {
                    Float_t     theta = 2 * atan (exp( (-1) * Kt_etajet_d[jet]));
                    Float_t     E = Kt_etjet_d[jet] / sin(theta);
                    Float_t     p = sqrt(E*E - Kt_masjet_d[jet]*Kt_masjet_d[jet]);
                    Float_t     pT = p * sin (theta);
                    TLorentzVector  reco_jet;
                    reco_jet.SetPtEtaPhiM(pT, Kt_etajet_d[jet], Kt_phijet_d[jet], Kt_masjet_d[jet]);
                    reco_jets_breit.push_back(reco_jet);
                }
                Float_t x_gamma_breit_jets = get_x_gamma(reco_jets_breit, true);
                if (x_gamma_breit_jets>=0) currentTGlobalBin->FillHistogram("x_gamma_breit_jets", x_gamma_breit_jets);

                // -------- Enriched plots. Added 30/03/2010 -----------//
                fFillMirrored=true;

                // charm enriched plots
                if ( ( TMath::Abs(fSignificance) > 4 ) && (mass>1) && (mass<2) ) {
                    currentTGlobalBin->FillHistogram("q2da_charm", TMath::Log10(Siq2da[0]));
                    currentTGlobalBin->FillHistogram("xda_charm", TMath::Log10(Sixda[0]));
                    currentTGlobalBin->FillHistogram("yel_charm", Siyel[0]);
                    currentTGlobalBin->FillHistogram("yjb_charm", Siyjb[0]);
                    currentTGlobalBin->FillHistogram("zvtx_charm", Zvtx);
                    currentTGlobalBin->FillHistogram("kt_etjet_b_charm", Kt_etjet_b[jetB]);
                    currentTGlobalBin->FillHistogram("kt_etajet_b_charm", Kt_etajet_b[jetB]);
                    currentTGlobalBin->FillHistogram("kt_phijet_b_charm", Kt_phijet_b[jetB]);
                    currentTGlobalBin->FillHistogram("empz_charm", V_h_e_zu-V_h_pz_zu);
                    // added 08 february 2011
                    currentTGlobalBin->FillHistogram("vtxsec_multi_charm", vtx_multi);
                    currentTGlobalBin->FillHistogram("vtxsec_chi2_charm", chi2);
                    currentTGlobalBin->FillHistogram("vtxsec_chi2ndf_charm", fVertices[j].chi2ndf);
                    // fill x_gamma, if was determined (i.e. two satisfactory jets were found)
                    if (x_gamma_lab_jets>=0) currentTGlobalBin->FillHistogram("x_gamma_lab_jets_charm", x_gamma_lab_jets);
                    if (x_gamma_lab_jets_tagged>=0) currentTGlobalBin->FillHistogram("x_gamma_lab_jets_tagged_charm", x_gamma_lab_jets_tagged);
                    if (x_gamma_breit_jets>=0) currentTGlobalBin->FillHistogram("x_gamma_breit_jets_charm", x_gamma_breit_jets);
                }
                // for the mass plot it is desired to see it in the full mass range, and not just from 1 to 2 GeV
                if (TMath::Abs(fSignificance) > 4) currentTGlobalBin->FillHistogram("vtxsec_mass_charm", mass);
                
                // beauty enriched plots
                if ( ( TMath::Abs(fSignificance) > 8 ) && (mass>2) && (mass<6) ) {

                    currentTGlobalBin->FillHistogram("q2da_beauty", TMath::Log10(Siq2da[0]));
                    currentTGlobalBin->FillHistogram("xda_beauty", TMath::Log10(Sixda[0]));
                    currentTGlobalBin->FillHistogram("yel_beauty", Siyel[0]);
                    currentTGlobalBin->FillHistogram("yjb_beauty", Siyjb[0]);
                    currentTGlobalBin->FillHistogram("zvtx_beauty", Zvtx);
                    currentTGlobalBin->FillHistogram("kt_etjet_b_beauty", Kt_etjet_b[jetB]);
                    currentTGlobalBin->FillHistogram("kt_etajet_b_beauty", Kt_etajet_b[jetB]);
                    currentTGlobalBin->FillHistogram("kt_phijet_b_beauty", Kt_phijet_b[jetB]);
                    currentTGlobalBin->FillHistogram("empz_beauty", V_h_e_zu-V_h_pz_zu);
                    // added 08 february 2011
                    currentTGlobalBin->FillHistogram("vtxsec_multi_beauty", vtx_multi);
                    currentTGlobalBin->FillHistogram("vtxsec_chi2_beauty", chi2);
                    currentTGlobalBin->FillHistogram("vtxsec_chi2ndf_beauty", fVertices[j].chi2ndf);
                    // fill x_gamma, if was determined (i.e. two satisfactory jets were found)
                    if (x_gamma_lab_jets>=0) currentTGlobalBin->FillHistogram("x_gamma_lab_jets_beauty", x_gamma_lab_jets);
                    if (x_gamma_lab_jets_tagged>=0) currentTGlobalBin->FillHistogram("x_gamma_lab_jets_tagged_beauty", x_gamma_lab_jets_tagged);
                    if (x_gamma_breit_jets>=0) currentTGlobalBin->FillHistogram("x_gamma_breit_jets_beauty", x_gamma_breit_jets);
                }
                // as for charm, it is desirable to see the whole mass range and not only restricted 2 to 6 GeV
                if (TMath::Abs(fSignificance) > 8) currentTGlobalBin->FillHistogram("vtxsec_mass_beauty", mass);
                fFillMirrored=false;

            } // end loop over bins
        }
    }   // *** end main event loop ***

    // mirror histograms
    TGlobalBin  *currentTGlobalBin;
    TIter   Iter_TGlobalBin(fList_TGlobalBin);
    while (currentTGlobalBin=(TGlobalBin*) Iter_TGlobalBin.Next())  {
        currentTGlobalBin->MirrorHistograms();
    }

    // now this  serves just as a cross check; mirroring is now made automatically
    // for any selected vertex variables, e.g. jet or vertex multiplicity (put mirror
    // switch in declarehist.cfg)
    // 26/03/2010 --> mirrored histograms obtained in this way are still used in the fitting!
    // so this is for sure not just a cross check! ;)
    this->MirrorHistogramOLD("significance");
    this->MirrorHistogramOLD("significance_massbin1");
    this->MirrorHistogramOLD("significance_massbin2");
    this->MirrorHistogramOLD("significance_massbin3");

    // store the histograms to file
    this->WriteHistograms();

    cout << "total nr of vertices by orange finder " << nvertices_ora << endl;
    cout << "total nr of vertices by cn finder " << nvertices_cn << endl;
    cout << "nr of events where there are more vertices in orange " << nevents_more_vetices_ora << endl;
    cout << "nr of events where there are more vertices in cn " << nevents_more_vetices_cn << endl;

}

Float_t TMiniNtupleAnalyzer::get_x_gamma(vector<TLorentzVector> jet_list, bool breit_jets, Int_t tagged_jet_id) {

    // for the timebeing, skip those events where reconstructed W is < 0 (=> E>p for q+p vector, hence velocity>c)
    // don't do this for the breit case, since there we don't need to do any boosts,
    // so gamma_p doesn't matter (only the sqrt(Q2))
    if ((f_gamma_p.M() < 0) && (!breit_jets)) {
        return -1;
    }

    Int_t   njets = jet_list.size();
    vector<TLorentzVector>  jet_list_boosted;

    for (int j = 0; j < njets; j++) {
        // get a jet from the list
        TLorentzVector  jet = jet_list[j];

        // if selected, boost the jet to gamma-p frame
        if (!breit_jets) {
            jet.Boost(fBoost);
            jet.Rotate(fAngle, fRotationAxis);
        }
        // fill the array of boosted jets
        jet_list_boosted.push_back(jet);
    }

    // now find two highest et jets

    // helping variables
    Int_t       jet1_id = -1;
    Int_t       jet2_id = -1;
    Float_t     jet1_et_max  = -999;
    Float_t     jet2_et_max = -999;
    // jet selection criteria
    Float_t     breit_et_cut = 4.2;
    Float_t     breit_eta_low = -9999;
    Float_t     breit_eta_high = 9999;

    // highest energy jet
    // A. no tagging requirement => look for a highest energy jet
    if (tagged_jet_id == -1) {
        for (int j = 0; j < njets; j++) {
            
            // get et of the jet
            Float_t  jet_et = jet_list_boosted[j].Et();
            Float_t  jet_eta = jet_list_boosted[j].Eta();
            // phase space cuts
            if (jet_et < breit_et_cut) continue;
            // if the jet energy is above the max energy found so far, call it highest energy jet (1st jet)
            if (jet_et > jet1_et_max) {
                jet1_et_max = jet_et;
                jet1_id = j;
                // if, however doesn't pass eta cuts, skip the jet
                if ((jet_eta > breit_eta_high) || (jet_eta < breit_eta_low)) jet1_id = -1;
            }
        }
    } else { // B. 1st jet tagged => don't have to search for highest et jet
        jet1_id = tagged_jet_id;
    }

    // 2nd highest energy jet
    for (int j = 0; j < njets; j++) {
        // get et of the jet
        Float_t  jet_et = jet_list_boosted[j].Et();
        Float_t  jet_eta = jet_list_boosted[j].Eta();
        // phase space cuts
        if (jet_et < breit_et_cut) continue;
        // if the jet energy is above the max energy found so far
        // but this jet is not the 1st one (in both tagged and untagged cases)
        if ( (jet_et > jet2_et_max) && (j != jet1_id) ) {
            jet2_et_max = jet_et;
            jet2_id = j;
            if ((jet_eta > breit_eta_high) || (jet_eta < breit_eta_low)) jet2_id = -1;
        }
    }

    // now calculate x_gamma
    if ( (jet1_id == (-1)) || (jet2_id == (-1)) ) return -1;
    
    // jet 1
    TLorentzVector jet1 = jet_list_boosted[jet1_id];
    TLorentzVector jet2 = jet_list_boosted[jet2_id];
    // x = [jet1(e-pz) + jet2(e-pz)]/[photon(e-pz)]
    Float_t         numerator = jet1.E() - jet1.Pz() + jet2.E() - jet2.Pz();
    Float_t         denominator;
    if (breit_jets) {
        // if jets are already in the breit frame, then e-pz = 0 - (-sqrt(Q2)) = sqrt(Q2)
        denominator = TMath::Abs(fq.M());
    } else {
        denominator = fq.E() - fq.Pz();
    }

    Float_t x_gamma = numerator / denominator;
    
    return x_gamma;
}

void TMiniNtupleAnalyzer::fill_parton_histograms(TGlobalBin* global_bin) {
    // this is for some true studies we performed,
    // in particular - kinematics of b quark - to check the source of 4.6%
    // discrepancy in observed true cross sections/jet kinematics between 06e and 0607p
    // looking at parton level distributions (not jets) should point to the reason:
    // generator level distributions OR jet finder problem
    for (int k = 0; k< Fmck_nstor; k++) {
        if ( Fmck_prt[k] == 9 ) {
            TLorentzVector	quark(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
            global_bin->FillHistogram("bbbar_mass", quark.M());
            // need on-shell only
            if ((quark.M() < 4.5) || (quark.M() > 5)) continue;
            global_bin->FillHistogram("bbbar_et", quark.Et());
            global_bin->FillHistogram("bbbar_eta", quark.Eta());
            break;
         }
    }
    
    for (int k = 0; k< Fmck_nstor; k++) {
        if ( (Fmck_prt[k] == 10) ) {
            TLorentzVector	quark(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
            global_bin->FillHistogram("bbbar_mass", quark.M());
            // need on-shell only
            if ((quark.M() < 4.5) || (quark.M() > 5)) continue;
            global_bin->FillHistogram("bbbar_et", quark.Et());
            global_bin->FillHistogram("bbbar_eta", quark.Eta());
            break;
        }
    }
    for (int k = 0; k< Fmck_nstor; k++) {

        if ( Fmck_prt[k] == 7 ) {
            TLorentzVector	quark(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
            global_bin->FillHistogram("ccbar_mass", quark.M());
            // need on-shell only
            if ((quark.M() < 1) || (quark.M() > 2)) continue;
            global_bin->FillHistogram("ccbar_et", quark.Et());
            global_bin->FillHistogram("ccbar_eta", quark.Eta());
            break;
        }
    }
    for (int k = 0; k< Fmck_nstor; k++) {
        if ( (Fmck_prt[k] == 8) ) {
            TLorentzVector	quark(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
            global_bin->FillHistogram("ccbar_mass", quark.M());
            // need on-shell only
            if ((quark.M() < 1) || (quark.M() > 2)) continue;
            global_bin->FillHistogram("ccbar_et", quark.Et());
            global_bin->FillHistogram("ccbar_eta", quark.Eta());
            break;
        }
    }
}

void TMiniNtupleAnalyzer::print_fmckin_table() {

    // general info
    cout << "INFO: "<< Fmck_nstor << " particles stored (Fmck_nkin= " <<Fmck_nkin << ", Npart= "<<Npart<<")\n";

    // loop over the particles
    for (int k = 0; k < Fmck_nstor; k++) {
        // get the type of the particle
        TString type;
        switch (Fmck_prt[k]) {
            case 23:
                type = "e-"; break;
            case 24:
                type = "e+"; break;
            case 25:
                type = "mu-"; break;
            case 26:
                type = "mu+"; break;
            case 32:
                type = "Z0"; break;
            case 29:
                type = "gamma"; break;
            case 7:
                type = "c"; break;
            case 8:
                type = "cbar"; break;
            case 2092:
                type = "string"; break;
            case 54:
                type = "pi+"; break;
            case 55:
                type = "pi-"; break;
            case 56:
                type = "pi0"; break;
            case 57:
                type = "eta"; break;
            case 58:
                type = "K+"; break;
            case 59:
                type = "K-"; break;
            case 60:
                type = "K0"; break;
            case 61:
                type = "K0bar"; break;
            case 62:
                type = "K0S"; break;
            case 63:
                type = "K0L"; break;
            case 64:
                type = "D+"; break;
            case 65:
                type = "D-"; break;
            case 66:
                type = "D0"; break;
            case 67:
                type = "D0bar"; break;
            case 33:
                type = "g"; break;
            case 188:
                type = "D*0"; break;
            case 189:
                type = "D*0bar"; break;
            case 190:
                type = "proton+"; break;
            case 191:
                type = "proton-"; break;
        }
        // 4 vector for this particle
        TLorentzVector  particle(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
        // and boost it
        particle.Boost(fBoost);
        particle.Rotate(fAngle, fRotationAxis);
        cout << "INFO: particle " << k << " of type " << Fmck_prt[k] << " (" << type << ") with fmckin id " << Fmck_id[k] << " produced at " << Fmck_prat[k] << " by " << Fmck_daug[k] <<"; " << " Et= "<<particle.Et() << " Eta= "<<particle.Eta() << endl;
        // trying to find conversions
        if ((Fmck_prt[k] == 23) || (Fmck_prt[k] == 24)) {
            cout << "Mother of e-/e+:" << Fmck_prt[Fmck_daug[k]-1] << endl;
            if (Fmck_prt[Fmck_daug[k]-1] == 29) abort();
        }
    }
}

void TMiniNtupleAnalyzer::checkArrayBounds() {
    if (Sincand >= 10) {cout << " ALARM! Sincand= " << Sincand << endl; abort();}
    if (Kt_njet_b >= 30) {cout << " ALARM! Kt_njet_b= " << Kt_njet_b << endl; abort();}
    if (Kt_njet_a >= 30) {cout << " ALARM! Kt_njet_a= " << Kt_njet_a << endl; abort();}
    if (Nzufos >= 250){ cout << " ALARM! Nzufos= " << Nzufos << endl; abort();}
    if (Trk_ntracks >= 400) {cout << " ALARM! Trk_ntracks= " << Trk_ntracks << endl; abort();}
    if (Nr_secvtx >= 60) {cout << " ALARM! Nr_secvtx= " << Nr_secvtx << endl; abort();}
    #ifdef CN_VERSION_V06
    if (Nr_redprim >= 30) {cout << " ALARM! Nr_redprim= " << Nr_redprim << endl; abort();}
    #endif
    if (Npart >= 2044){ cout << " ALARM! Npart= " << Npart << endl; abort();}
    if (Fmck_nstor >= 3000) {cout << " ALARM! Fmck_nstor= " << Fmck_nstor << endl; abort();}
    if (Nhbmjets >= 100){ cout << " ALARM! Nhbmjets= " << Nhbmjets << endl; abort();}
}

void TMiniNtupleAnalyzer::get_gammaP_boost() {
    bool    q_reco = true;
    bool    pure_electron = true;   // valid only for q_reco = true;
    // q reconstructed from leptons
    TLorentzVector  k(0, 0, (-1)*27.5, sqrt(27.5*27.5 + 0.000511 * 0.000511));
    TLorentzVector  k_prim_reco;
    if (pure_electron) {
        f_k_prim_reco.SetPxPyPzE(sin(Sith[0])*cos(Siph[0]), sin(Sith[0])*sin(Siph[0]), cos(Sith[0]), 1);
        f_k_prim_reco *= Siecorr[0][2];
    } else {
        Float_t ratio = Siq2da[0] / (4 * 27.5 * 27.5 * (1-Siyda[0]));
        Float_t c_theta = (ratio - 1) / (ratio + 1);
        Float_t E_prim = Siq2da[0]/(2 * 27.5 * (1 + c_theta));
        Float_t s_theta = sqrt(1-c_theta*c_theta);
        f_k_prim_reco.SetPxPyPzE(s_theta*cos(Siph[0]), s_theta*sin(Siph[0]), c_theta, 1);
        f_k_prim_reco *= E_prim;
    }
    
    if (q_reco) {
        fq = k - f_k_prim_reco;
    } else {
        fq.SetPxPyPzE(Pboson[0], Pboson[1], Pboson[2], Pboson[3]);
    }
    
    // initial state proton
    TLorentzVector  p(0, 0, 920, sqrt(920*920+0.938*0.938));
    // gamma+p vector
    f_gamma_p = fq + p;
    
    // now boost to gamma p
    // first, get a boost vector;
    // original frame: gamma p rest frame
    // rod frame: laboratory frame
    // boost vector: speed of laboratory frame wrt gamma p rest frame,
    // obviously (-1)x(f_gamma_p velocity,lab)=(-1)x(f_gamma_p momentum,lab)/(f_gamma_p energy, lab)
    fBoost.SetXYZ((-1)*f_gamma_p.Px()/f_gamma_p.E(), (-1)*f_gamma_p.Py()/f_gamma_p.E(), (-1)*f_gamma_p.Pz()/f_gamma_p.E());
    // boosting to gamma p rest frame; these will be needed in gamma-p frame
    fq.Boost(fBoost);
    p.Boost(fBoost);
    
    // now need to rotate the frame, so that z axis is aligned with proton direction
    // get a rotation angle (=angle between old and new z axis, that is proton direction
    // in the old frame)
    TVector3 z_new(p.Px()/p.P(), p.Py()/p.P(), p.Pz()/p.P());
    TVector3 z_old(0,0,1);
    fAngle = acos(z_new * z_old);
    // get a direction of rotation - that is a vector perpendicular
    // to the plane that contains old z and new z
    // can be obtained by a vector product
    fRotationAxis = z_new.Cross(z_old);
    fq.Rotate(fAngle, fRotationAxis);
    p.Rotate(fAngle, fRotationAxis);
    
    // calculate W from this
    Float_t fWda = sqrt(0.938*0.938 + Siq2da[0]*(1./Sixda[0] - 1));
    // true W
    TLorentzVector  f_true_q(Pboson[0], Pboson[1], Pboson[2], Pboson[3]);
    TLorentzVector  true_p(0, 0, 920, sqrt(920*920+0.938*0.938));
    TLorentzVector  true_gamma_p = f_true_q + true_p;
    Float_t fW_true = true_gamma_p.M();
    
    // true q
    f_true_q.Boost(fBoost);
    f_true_q.Rotate(fAngle, fRotationAxis);
    
    // true scattered electron
    f_k_prim_true.SetPxPyPzE(Plepton[0], Plepton[1], Plepton[2], Plepton[3]);
}

void TMiniNtupleAnalyzer::get_Zstring_weight(TGlobalBin * currentTGlobalBin) {

    // look for charm/beauty hadrons,
    // loop over all true particles
    for (int k = 0; k < Fmck_nstor; k++) {
    
        // get a particle type
        Int_t   t = Fmck_prt[k];
                        
        // proceed only for some charm and beauty hadrons (for charm and beauty sample respectively)
        if ( fIsCharm ) {
            if (!( ( (t>=64) && (t<=71) ) || ( (t>=186) && (t<=189) ) || (t==208) || (t==209) )) continue;
        } else if ( fIsBeauty ) {
            if (!( ( (t>=72) && (t<=75) ) || (t==214) || (t==215) || ( (t>=468) && (t<=529)) || ( (t>=2349) && (t<=2378)))) continue;
        } else { // sanity check
            cout << "ERROR from Loop(): shouldn't get here" << endl;
            abort();
        }
        
        // get 4-momentum of the charm/beauty hadron
        TLorentzVector hadron(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
        
        // loop over the table again to find index of the mother particle of our charm hadron
        Int_t       string_ind = -1;
        for (int ii = 0; ii < Fmck_nstor; ii++) {
            if (Fmck_daug[k] == Fmck_id[ii]) {
                string_ind = ii;
                break;
            }
        }
        
        // we are interested only in hadrons created directly in string fragmentation (not in the decays 
        // of other hadrons);
        // string code is 2092
        if (Fmck_prt[string_ind] != 2092) continue;
    
        // get 4-momentum of the string
        TLorentzVector  string(Fmck_px[string_ind], Fmck_py[string_ind], Fmck_pz[string_ind], Fmck_e[string_ind]);
    
        // get also c/cbar quark - parent of the string
        Int_t       quark_ind = -1;
        for (int ii = 0; ii < Fmck_nstor; ii++) {
            if (Fmck_daug[string_ind] == Fmck_id[ii]) {
                quark_ind = ii;
                break;
            }
        }
    
        // check whether this is c/cbar
        Int_t   quark_id = Fmck_prt[quark_ind];
        if ( (fIsCharm&&(quark_id != 7)&&(quark_id != 8)) || (fIsBeauty&&(quark_id != 9)&&(quark_id != 10)) ) {
            cout << "WARNING: parent of the string is not c/cbar or b/bar! Skipping this event" << endl;
            cout << quark_id << endl;
            continue;
        }
    
        TLorentzVector  quark(Fmck_px[quark_ind], Fmck_py[quark_ind], Fmck_pz[quark_ind], Fmck_e[quark_ind]);
    
        // charm hadron variables
        Double_t    qphi = hadron.Phi();
        if (qphi<0) qphi += (2*TMath::Pi());
        Double_t    qeta = hadron.Eta();
    
        // find a jet to which charm hadron is associated;
        // first, find closest jet to the hadron
        Double_t    Rmin = 99999;
        Int_t       jet_ind = -1;
        for (int m = 0; m < Nhbmjets; m++) {
            TLorentzVector jet(Pxhbmjet[m], Pyhbmjet[m], Pzhbmjet[m], Ehbmjet[m]);
            Double_t    jphi = jet.Phi();
            if (jphi<0) jphi += (2*TMath::Pi());
        
            Double_t    deta = qeta - jet.Eta();
            Double_t    dphi = qphi - jphi;
            Double_t    R = sqrt(deta*deta + dphi*dphi);
            if (R<Rmin) {
                Rmin = R;
                jet_ind = m;
            }
        }
    
        currentTGlobalBin->FillHistogram( "R_hadron_jet", Rmin);
        // closest jet should be close enough
        if (Rmin>1) continue;
    
        // ok, found a jet which contains our charm hadron
        TLorentzVector jet(Pxhbmjet[jet_ind], Pyhbmjet[jet_ind], Pzhbmjet[jet_ind], Ehbmjet[jet_ind]);
    
        // now boost to string rest frame, where we want to work;
        // first, get a boost vector;
        // original frame: string rest frame
        // rod frame: laboratory frame
        // boost vector: speed of laboratory frame wrt string rest frame,
        // obviously (-1)x(string velocity,lab)=(-1)x(string momentum,lab)/(string energy, lab)
        TVector3     boost((-1)*string.Px()/string.E(), (-1)*string.Py()/string.E(), (-1)*string.Pz()/string.E());
    
        // boosting to string rest frame
        hadron.Boost(boost);
        jet.Boost(boost);
        quark.Boost(boost);
        string.Boost(boost);
        
        // now can calculate z, taking different variables
        Double_t    p_hadr_parallel = (quark.Vect().Dot(hadron.Vect()))/quark.Vect().Mag();
        Double_t    z_quark = (hadron.E() + p_hadr_parallel) / (quark.E() + quark.P());
        Double_t    z_string = (hadron.E() + p_hadr_parallel) / (string.E() + string.P());
        currentTGlobalBin->FillHistogram( "z_true_quark", z_quark);
        currentTGlobalBin->FillHistogram( "z_true_string", z_string);
    
        Double_t    p_charm_hadr_parallel_jet = (jet.Vect().Dot(hadron.Vect()))/jet.Vect().Mag();
        Double_t    z_jet = (hadron.E() + p_hadr_parallel) / (jet.E() + jet.P());
        currentTGlobalBin->FillHistogram( "z_true_jet", z_jet);
    
        // now define weight from this hadron
        // first get a bin number
        Int_t   bin_rew_histo = getReweightingHistoBin(fFragmentationReweighting_histo, z_string);
        // now get value
        Double_t    weight = fFragmentationReweighting_histo -> GetBinContent(bin_rew_histo);
        fZstring_weight *= weight;
    }
}

// hadron jet matching to partons
/*
                // hacks 17 May 2011, closer look onto true distributions in context
        // of fragmentation function systematic studies
        Double_t        R_c = -1;
        Double_t        R_cbar = -1;
        Double_t        c_et = -1;
        Double_t        cbar_et = -1;
        Int_t           c_fmckinID = -1;
        Int_t           cbar_fmckinID = -1;
        for (int k = 0; k< Fmck_nstor; k++) {

            if ( Fmck_prt[k]==7 ) {
                c_fmckinID = Fmck_id[k];
                TLorentzVector	quark(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
                // delta eta
                Double_t    deta = quark.Eta() - jet.Eta();
                // delta phi
                Double_t    qphi = quark.Phi();
                if (qphi<0) qphi += (2*TMath::Pi());
                Double_t    dphi = qphi - fTrueJetPhi;
                // get R-distance
                R_c = sqrt(deta*deta + dphi*dphi);
                c_et = quark.Et();
                break;
            }
        }
    
        for (int k = 0; k< Fmck_nstor; k++) {
            if ( (Fmck_prt[k]==8) ) {
                cbar_fmckinID = Fmck_id[k];
                TLorentzVector	quark(Fmck_px[k], Fmck_py[k], Fmck_pz[k], Fmck_e[k]);
                // delta eta
                Double_t    deta = quark.Eta() - jet.Eta();
                // delta phi
                Double_t    qphi = quark.Phi();
                if (qphi<0) qphi += (2*TMath::Pi());
                Double_t    dphi = qphi - fTrueJetPhi;
                // get R-distance
                R_cbar = sqrt(deta*deta + dphi*dphi);
                cbar_et = quark.Et();
                break;
            }
        }
        if (R_c < R_cbar) {
            currentTGlobalBin->FillHistogram( "R", R_c);
            if (R_c < 1)
                currentTGlobalBin->FillHistogram( "delta_et", c_et - fTrueJetEt);
        } else {
            currentTGlobalBin->FillHistogram( "R", R_cbar);
            if (R_cbar < 1)
                currentTGlobalBin->FillHistogram( "delta_et", cbar_et - fTrueJetEt);
        }
        */
/*
                // now calculate x_gamma
                Float_t     x_gamma_1;
                Float_t     x_gamma_2;
                Float_t     x_gamma_3;
                // loop over jets again to find whethere there's an additional high ET jet
                Float_t     gamma_p_et_cut = fJetEtCut;
                Int_t       max_et_jet_id = -1;
                Float_t     max_et_jet = -999;
                // flag to determine whether vertex jet has high et also in the gamma p frame
                bool        vertex_jet_high_et = false;
                for (int k = 0; k < Kt_njet_b; k++) {

    Float_t     theta = 2 * atan (exp( (-1) * Kt_etajet_b[k]));
    Float_t     E = Kt_etjet_b[k] / sin(theta);
    Float_t     p = sqrt(E*E - Kt_masjet_b[k]*Kt_masjet_b[k]);
    Float_t     pT = p * sin (theta);
    TLorentzVector  jet;
    jet.SetPtEtaPhiM(pT, Kt_etajet_b[k], Kt_phijet_b[k], Kt_masjet_b[k]);
    // boost the jet to the gamma_p frame
    jet.Boost(fBoost);
    // rotate the frame so that z is aligned to proton/photon direction
    jet.Rotate(fAngle, fRotationAxis);

    if (jet.Et() < gamma_p_et_cut) continue;
    if (k == jetB) {
        vertex_jet_high_et = true;
        continue;
    }

    if (jet.Et() > max_et_jet) {
        max_et_jet = jet.Et();
        max_et_jet_id = k;
    }
                }

                // if the second high et jet was found, calculate x_gamma
                if ((max_et_jet_id != (-1)) && vertex_jet_high_et) {
    // now construct x_gamma
    // jet 1 (tagged one)
    Float_t     theta = 2 * atan (exp( (-1) * Kt_etajet_b[jetB]));
    Float_t     E = Kt_etjet_b[jetB] / sin(theta);
    Float_t     p = sqrt(E*E - Kt_masjet_b[jetB]*Kt_masjet_b[jetB]);
    Float_t     pT = p * sin (theta);
    TLorentzVector  jet1;
    jet1.SetPtEtaPhiM(pT, Kt_etajet_b[jetB], Kt_phijet_b[jetB], Kt_masjet_b[jetB]);
    jet1.Boost(fBoost);
    jet1.Rotate(fAngle, fRotationAxis);
    Float_t     E1 = jet1.E();
    Float_t     pz1 = jet1.Pz();

    // jet 2 (untagged one)
    theta = 2 * atan (exp( (-1) * Kt_etajet_b[max_et_jet_id]));
    E = Kt_etjet_b[max_et_jet_id] / sin(theta);
    p = sqrt(E*E - Kt_masjet_b[max_et_jet_id]*Kt_masjet_b[max_et_jet_id]);
    pT = p * sin (theta);
    TLorentzVector  jet2;
    jet2.SetPtEtaPhiM(pT, Kt_etajet_b[max_et_jet_id], Kt_phijet_b[max_et_jet_id], Kt_masjet_b[max_et_jet_id]);
    jet2.Boost(fBoost);
    jet2.Rotate(fAngle, fRotationAxis);
    Float_t     E2 = jet2.E();
    Float_t     pz2 = jet2.Pz();

    // calculate x_gamma with two slightly different definitions
    //Float_t     denominator = 2 * Siyjb[0] * 27.5;
    Float_t       denominator = 2 * fq.E();
    Float_t     numerator_1 = jet1.Et() * exp((-1)*jet1.Eta())+jet2.Et() * exp((-1)*jet2.Eta());
    Float_t     numerator_2 = (E1 - pz1) + (E2 - pz2);
    
    x_gamma_1  = numerator_1 / denominator;
    x_gamma_2  = numerator_2 / denominator;
    // yet another version
    TLorentzVector  total_ZUFO(0, 0, 0, 0);
    for (int z = 0; z < Nzufos; z++) {  
        TLorentzVector  zufo(Zufo[z][0], Zufo[z][1], Zufo[z][2], Zufo[z][3]);
        total_ZUFO += zufo;
    }
    total_ZUFO -= f_k_prim_reco;
    // now boost
    total_ZUFO.Boost(boost);
    total_ZUFO.Rotate(fAngle, fRotationAxis);

    TLorentzVector  hadronic_sira(Sizuhmom[0][0], Sizuhmom[0][1], Sizuhmom[0][2], Sizuhmom[0][3]);
    // now boost
    hadronic_sira.Boost(fBoost);
    hadronic_sira.Rotate(fAngle, fRotationAxis);
    Float_t denominator3 = hadronic_sira.E() - hadronic_sira.Pz();
    x_gamma_3 = numerator_2 / denominator3;
    currentTGlobalBin->FillHistogram("x_gamma_1", x_gamma_1);
    currentTGlobalBin->FillHistogram("x_gamma_2", x_gamma_2);

*/