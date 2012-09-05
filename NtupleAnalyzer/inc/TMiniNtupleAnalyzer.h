//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////

#ifndef __TMININTUPLEANALYZER_H__
#define __TMININTUPLEANALYZER_H__

// ROOT includes
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TList.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TLorentzVector.h>

// my includes
#include <inc/TNtupleAnalyzer.h>
#include <inc/TVertex.h>
#include <TDataset.h>
#include <inc/constants.h>
using namespace constants;

// system includes
#include <vector>
using namespace std;

// forward declaration of TGlobalBin - in order to resolve circular dependency
class TGlobalBin;

/*! \brief Class for private mini ntuples analysis.
*/

class TMiniNtupleAnalyzer : public TNtupleAnalyzer {

    public:

        // constructors, desctructors
        TMiniNtupleAnalyzer() {};
        TMiniNtupleAnalyzer(TString HistoVersion, TString BinningFile, TString	DeclareHistoFileName);
        ~TMiniNtupleAnalyzer() {};

        // various setters
        void            SetBinningFileName (TString filename) {fBinningFileName=filename;};
        void            SetDropTracks (bool drop_tracks) { fDropTracks = drop_tracks; };
        void            SetUseHadronicInteractionMap(bool use_map) {fUseHadronicInteractionMap = use_map;}
        void            SetOnlyCalculateEventsPerRun (bool calc_events) { fOnlyCalculateEventsPerRun = calc_events; };
        void            SetSecondaryVertexSmearing (bool smear) { fApplySmearing = smear; };
        void            SetDropTrackProbability(Float_t prob) {fDropProbability = prob;};
        void            SetHadronicInteractionCorrection(Float_t corr) {fHadronicInteractionCorrection = corr;};
        void            SetEtReweightingLF_filename(TString name) {fEtReweightingLF_filename = name;};
        void            SetEtReweightingLF(bool do_reweighting) {fEtReweightingLF = do_reweighting;};
        void            SetSeedVertexSmearing(unsigned seed1, unsigned seed2) {fSeed_rnd = seed1; fSeed_rnd2 = seed2;};
        void            SetSeedCrudeTrackingEfficiency(unsigned seed) {fSeed_rnd_eff = seed;};

        void            SetJetEnergyUncertainty(Double_t    jet_unc) {fJetEnergyUncertainty = jet_unc;}
        void            SetEMScaleUncertainty(Double_t em_scale) {f_EM_scale = em_scale;}
        void            SetVaryTotalJetEnergy(bool vary_total) {fVaryTotalJetEnergy = vary_total;};
        void            SetTrueLevelStudies(bool true_studies) {fTrueLevelStudies = true_studies;};

        void            SetFragmentationReweighting_filename(TString name) {fFragmentationReweighting_filename = name;};
        void            SetFragmentationReweighting(bool do_reweighting) {fFragmentationReweighting = do_reweighting;};
        void            SetCharmFragmentationReweightingSize(Double_t    size) {fCharmFragm_variation_size = size;};
        void            SetBeautyFragmentationReweightingSize(Double_t    size) {fBeautyFragm_variation_size = size;};

        void            SetSashasReweighting(bool apply_reweighting) {fSashasReweighting = apply_reweighting;};

        void            SetJetEtCut(Double_t    jet_et_cut) {fJetEtCut = jet_et_cut;};
        void            SetUpEtaCut(Double_t    jet_eta_cut) {fJetEtaUpCut = jet_eta_cut;};
        void            SetLowEtaCut(Double_t    jet_eta_cut) {fJetEtaLowCut = jet_eta_cut;};

        void            SetApplyQ2Reweighting(bool apply_reweighting) {fApplyQ2Reweighting = apply_reweighting;};
        void            SetApplyCharmEtaReweighting(bool apply_reweighting) {fApplyCharmEtaReweighting = apply_reweighting;};
        void            SetApplyCharmETReweighting(bool apply_reweighting) {fApplyCharmETReweighting = apply_reweighting;};

        void            SetCharmEtaReweighting_p0(Float_t   par) {fCharmEtaReweighting_p0 = par;};
        void            SetCharmEtaReweighting_p1(Float_t   par) {fCharmEtaReweighting_p1 = par;};
        void            SetCharmEtaReweighting_p2(Float_t   par) {fCharmEtaReweighting_p2 = par;};

        void            SetCharmETReweightingPar(Float_t par0, Float_t par1);

        // initialisator the class
        void            Initialize();

        // recalculates luminosity
        void            RecalculateLuminosity();

        // main functionality - loops over events and fills the histograms
        void            Loop (Bool_t IsInclusive);

        // print number of events per run for runs that have non-zero event number
        void            PrintEventsPerRun();

        void            SetPrintingFreq(Int_t   events) {fPrintingFreq = events;};

        void            SetRundCache (bool run_dcache) {fRun_dCache = run_dcache;};
        void            SetDoJetEnergyScaleSyst (bool do_syst) {fDoJetEnergyScaleSyst = do_syst;};
        void            set_do_EM_scale_syst (bool do_syst) {f_do_EM_scale_syst = do_syst;}

        // vertexing on the CN level
        void            SetRedoVertexing(bool redo_vertexing) {fRedoVertexing = redo_vertexing;};
        void            SetRcut(Float_t r_cut) {fRcut = r_cut;};            //!< Set Cone cut
        void            SetpT(Float_t pt_cut) {fpT = pt_cut;};             //!< Set minimal track pT
        void            SetSTT(Int_t stt) {fSTT = stt;};                   //!< Set minimal number of STT hits
        void            SetCTD(Int_t ctd) {fCTD = ctd;};                   //!< Set minimal number of CTD hits
        void            SetMVD(Int_t mvd) {fMVD = mvd;};                   //!< Set minimal number of MVD hits
        void            SetUseHelixTrackParameters(Bool_t   setHelix) {fUseHelixTrackParameters = setHelix;};

        void            SetStudyResolutions(bool study) {fStudyResolutions = study;};

        // rho tracking efficiency studies routines

        void            TrackingEfficiency(); //!< main event loop
        void            FindRho(vector<TLorentzVector> &rho, bool  ZTT); //!< rho candidate search
        void            FillRhoHistograms(vector<TLorentzVector> &cand, bool  ZTT); //!< reweighing and histograms filling

        Double_t        getIslandDCA(int isl, int trk); //!< calculates DCA of an island wrt to a given track
        bool            TrackMatch(TLorentzVector track1, TLorentzVector track2);   //!< defines whether two tracks are close in eta-phi

        // these functions are used to get true-level pions
        int             get_pi_id(bool is_plus);
        int             get_pi_plus_id();
        int             get_pi_minus_id();
        TLorentzVector  get_pi_plus();
        TLorentzVector  get_pi_minus();
        int             getRhoEventClass(); //!< classifies an event
        void            FillPionsFatePoint(); //!< fills a histogram with a fate point of pions

        Double_t        getElectronEnergyConstrainedMethod(TLorentzVector rho); //!< scattered electron energy based on the constrained method
        TLorentzVector  getElectronConstrainedMethod(TLorentzVector rho); //!< scattered electron 4-vector based on the constrained method
        Double_t        getQ2ConstrainedMethod(TLorentzVector rho); //!< q2 based on the constrained method

        Double_t        getThetaStar(TLorentzVector pi1, TLorentzVector pi2); //!< theta* determination
        Double_t        get_PHI_h(TLorentzVector rho, bool q_reco); //!< helicity PHI determination (see rho papers)
        TLorentzVector  getPiPlusInRhoHelicityFrame(TLorentzVector pi_plus, TLorentzVector pi_minus, bool q2_reco); //!< boost of pi+ to the helicity frame
        Double_t        get_cos_theta_h(TLorentzVector pi_plus, TLorentzVector pi_minus, bool q2_reco); //!< helicity theta determination
        Double_t        get_phi_h(TLorentzVector pi_plus, TLorentzVector pi_minus, bool q2_reco); //!< helicity phi determination

        Double_t        getPionPtReweighting (Double_t pt);
        Double_t        getPionPhiReweighting (Double_t phi);
        Double_t        getThetaStarReweighting(Double_t theta_star);
        Double_t        getRhoPhiReweighting(Double_t phi);
        Double_t        getRhoThetaReweighting(Double_t theta);
        Double_t        getRhoPtReweighting(Double_t pt);

        void            setApplyPtReweighting(bool apply) {fApplyPtReweighting = apply;};
        void            setApplyPhiReweighting(bool apply) {fApplyPhiReweighting = apply;};
        void            setApplyThetaStarReweighting(bool apply) {fApplyThetaStarReweighting = apply;};
        void            setApplyRhoPtReweighting(bool apply) {fApplyRhoPtReweighting = apply;};
        void            setApplyRhoThetaReweighting(bool apply) {fApplyRhoThetaReweighting = apply;};
        void            setApplyRhoPhiReweighting(bool apply) {fApplyRhoPhiReweighting = apply;};
        void            setDebugPrintout(bool debug) {fDebugPrintout = debug;};

        unsigned        fPrimary_ZTT_tracks;
        unsigned        fLong_primary_ZTT_tracks;
        unsigned        fLong_ZTT_tracks;
        bool            fApplyPtReweighting;
        bool            fApplyPhiReweighting;
        bool            fApplyThetaStarReweighting;
        bool            fApplyRhoPhiReweighting;
        bool            fApplyRhoPtReweighting;
        bool            fApplyRhoThetaReweighting;
        bool            fDebugPrintout;
        Double_t        fNonElectronEnergyZufo;
        Double_t        fElectronEnergyZufo;
        Double_t        fNonTrackEnergyZufo;
        Double_t        fUnmatchedIslandsEnergy;
        Double_t        fPtExcess;
        Double_t        fPExcess;
        Double_t        fScalarPtExcess;

        Int_t           fTrack1Id;
        Int_t           fTrack2Id;

        Bool_t          fSecondaryVertexFound;
        // the following variables are used heavily TGlobalBim; TODO: think whether this could be improved
        Float_t         fSignificance;
        Float_t         fRecoJetEt;
        Float_t         fRecoJetEta;
        Float_t         fRecoJetPhi;
        Float_t         fTrueJetEt;
        Float_t         fTrueJetEta;
        Float_t         fTrueJetPhi;

        // used in TGlobalBin::FillHistogram
        Bool_t          fFillMirrored;
        // vector of vertices in the event
        vector<TVertex> fVertices;
        vector<TVertex> fVerticesRefitted;  // temporary, for tests

        Float_t         fTrue_y;

        Bool_t          fApplySmearing;
        Double_t        fSmearingGauss1Prob;
        Double_t        fSmearingGauss1Width;
        Double_t        fSmearingGauss2Prob;
        Double_t        fSmearingGauss2Width;
        Double_t        fSmearingExpProb;
        Double_t        fSmearingExpCoeff;

        Bool_t          fTrueLevelStudies;

    private:

        // set of private methods, should be used only within the class

        // gets path to minintuples
        //void        getMiniNtuplesPath();

        // creates a structure to cope with multiple bins
        void        SetBinning();

        // sets weighting factor for CHARM MC
        void        CalculateCharmQg4WeightingFactor();

        // initialize random generators
        void        InitializeRandomGenerators();

        void        CreateBinHistograms();

        // older methods, to be reviewed
        void        DeclareHistograms(TGlobalBin* tgb);
        void        FillHist(TGlobalBin* tgb, TString HistTitle, Float_t	Value);
        void        MirrorHistogramOLD(TString HistName);
        void        MirrorHistograms();
        Float_t     CalculateSignificance(Int_t	vertex);
        Float_t     CalculateProjDecayLength(Int_t	vertex);
        Bool_t      IsDIS();
        Bool_t      IsDIS_Rho();
        void        WriteHistograms();

        void        GetEtReweightingLF_histo();
        Float_t     getEtReweighting(Float_t   jet_et);

        void        GetFragmentationReweighting_Histo();

        // this is similar to getEtReweighting but more generic - works for each histogram/value
        Int_t       getReweightingHistoBin(TH1F * histo, Float_t   value);

        Float_t     getCharmETweightingFactor(Float_t  jet_et);

        void        findVertices();             //!< replacement for orange sec vtx finder - to allow
                                                //!< more flexibility like lower track pT cut
        Float_t     get_x_gamma(vector<TLorentzVector> jet_list, bool breit_jets, Int_t tagged_jet_id = -1);
        void        fill_parton_histograms(TGlobalBin* global_bin);

        // tells whether the program should run on dCache files or on mini ntuples on disk
        bool        fRun_dCache;

        TFile*      fHistogramsFile;
        TString     fHistogramsFileVersion;
        TList*      fList_TGlobalBin;

        TH1F*       fDebugSVTX;

        TH2F*       fMc_q2_et;
        TH2F*       fMc_pt_theta_pi;

        TString     fBinningFileName;
        TString     fHistogramDeclarationFile;
        Bool_t      fApplyQ2g4Weighting;
        Double_t    fCharmQ2g4Weight;
        Double_t    fTrueQ2Weight;
        Double_t    fRecoQ2Weight;
        bool        fApplyQ2Reweighting;
        bool        fApplyCharmEtaReweighting;
        bool        fApplyCharmETReweighting;
        Float_t     fCharmEtaReweighting_p0;
        Float_t     fCharmEtaReweighting_p1;
        Float_t     fCharmEtaReweighting_p2;
        Float_t     fCharmETReweighting_p0;
        Float_t     fCharmETReweighting_p1;

        // Random numbers generators
        TRandom3    *rnd;
        TRandom3    *rnd2;
        TRandom3    *rnd_eff;
        // Seeds for the random number generators
        unsigned    fSeed_rnd;
        unsigned    fSeed_rnd2;
        unsigned    fSeed_rnd_eff;

        // a flag to specify whether we want to do vertex refit with droping tracks or not
        bool        fDropTracks;
        bool        fUseHadronicInteractionMap;

        // a probability to loose track when the fDropTracks flag is enabled
        Float_t     fDropProbability;
        Float_t     fHadronicInteractionCorrection;

        // a structure(s) to calculate number of events per run
        // 1st argument: runnumber
        // 2nd argument: number of events in that run

        // this one is for keeping ALL events (i.e. no selection on EVTAKE or MVDTAKE)
        std::map<unsigned, unsigned>    fEventsPerRun_ALL;
        // this is to keep events that passed EVTAKE and MVDTAKE criteria
        // NOTE: means different thing for v02 and v04 (v02: Evtake > 0, v04: Evtake=1, Evtake=2)
        std::map<unsigned, unsigned>    fEventsPerRun_EVTAKE_MVDTAKE;

        // flag to say whether we should only calculate number of events per run,
        // i.e. fill the above map, and don't run the analysis, histogram filling etc.
        bool                            fOnlyCalculateEventsPerRun;

        // histogram name and pointer to it for LF Et reweighting
        TH1F *      fEtReweightingLF_histo;
        TString     fEtReweightingLF_filename;
        bool        fEtReweightingLF;

        // histogram name and pointer to it for fragmentation function reweighting
        TH1F *      fFragmentationReweighting_histo;
        TString     fFragmentationReweighting_filename;
        bool        fFragmentationReweighting;

        // for jet energy uncertainty studies
        // can be positive or negative (+-3% being the most common choice)
        Double_t    fJetEnergyUncertainty;
        // if this variable is true, vary total jet energy as given from the jet algo
        // otherwise vary only Calorimetric part of the et energy from ZUFO information
        // default: false (more correct approach)
        bool        fVaryTotalJetEnergy;
        bool        fDoJetEnergyScaleSyst;
        bool        f_do_EM_scale_syst;

        // this is event-by-event weitght to be applied to charm MC
        Double_t    fZstring_weight;
        void        get_Zstring_weight(TGlobalBin * bin);
        // this is a variable to allow the usual systematics scan: 0 = no effect taken into account; 1 = reweighting according to weight
        Double_t    fCharmFragm_variation_size;
        Double_t    fBeautyFragm_variation_size;

        // whether to apply Sasha's reweighting or not
        Bool_t      fSashasReweighting;

        // variable to store a value of the jet Et cut;
        Double_t    fJetEtCut;
        Double_t    fJetEtaUpCut;
        Double_t    fJetEtaLowCut;

        // bla bla
        Int_t       fPrintingFreq;

        Bool_t      fRedoVertexing;             //!< redo secondary vertexing (including track selection) on the CN level
        Float_t     fRcut;                      //!< Cone cut
        Float_t     fpT;                        //!< minimal track pT
        Int_t       fSTT;                       //!< minimal number of STT hits
        Int_t       fCTD;                       //!< OR minimal number of CTD hits
        Int_t       fMVD;                       //!< minimal number of MVD hits
        Bool_t      fUseHelixTrackParameters;   //!< whether to use Trk_Helix or Tracking

        // boost to gamma-p, x_gamma
        TVector3        fBoost;                 //!< boost vector to gamma-p frame for current event
        TVector3        fRotationAxis;          //!< rotation axis 3-vector - a rotation after the boost in order
                                                //!< to align p direction with +z axis (and gamma direction with -z)
        Float_t         fAngle;                 //!< rotation angle

        TLorentzVector  fq;                     //!< 4-vector of the exchanged boson, to be boosted to the gamma-p frame
        TLorentzVector  f_gamma_p;              //!< 4 vector of the gamma-p system, not boosted to the gamma-p frame
        TLorentzVector  f_k_prim_reco;          //!< 4 vector of the scattered electron, reco level (at the moment electron method)
        TLorentzVector  f_k_prim_true;          //!< 4 vector of the scattered electron, true level, makes sennse for MC only
        TLorentzVector  f_true_q;               //!< 4 vector of the exchanged boson, true level
        Float_t         fWda;                   //!< W reconstructed by DA method
        Float_t         fW_true;                //!< W true value
        void            get_gammaP_boost(bool q_reco, bool use_rho); //!< sets the relevant variables used for transformation to gamma-p

        void            print_fmckin_table();
        void            checkArrayBounds();             //!< checks whether array bounds are not violated

        bool            fIsCharm;               //!< true, if this sample is charm, false otherwise
        bool            fIsBeauty;              //!< true, if this sample is beauty, false otherwise

        bool            fStudyResolutions;      //!< a switch to select resolution studies

        Float_t         getAverageAngle(Int_t  vertex_id);  //!< calculates an average angle between all possible track combination in the vertex

        bool            isHFLJet(TLorentzVector * jet);     //!< for the true cross section calculation: is used to separate
                                                            //!< charm/beauty jets from other (e.g. gluon jets)
        Float_t         fPionThetaReco;                     //!< a variable needed to use theta of the pion for binning
        Float_t         fPionThetaTrue;                     //!< a variable needed to use theta of the pion for binning
        Float_t         fPionPhiReco;                       //!< a variable needed to use phi of the pion for binning
        Float_t         fPionPhiTrue;                       //!< a variable needed to use phi of the pion for binning

        Float_t         f_EM_scale;                         //!< for EM scale systematic studies
};
#endif
