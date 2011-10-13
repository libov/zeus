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
#include <TString.h>
#include <TList.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TLorentzVector.h>

// my includes
#include <inc/TNtupleAnalyzer.h>
#include <inc/TVertex.h>
#include <TDataset.h>

// system includes
#include <vector>
using namespace std;

// forward declaration of TGlobalBin - in order to resolve circular dependency TODO: more info
class TGlobalBin;

/*! \brief Class for private mini ntuples analysis.
*  continue brief description here
*
* put detailed description here
*/

class	TMiniNtupleAnalyzer : public TNtupleAnalyzer
{
    public:

        // constructors, desctructors
        TMiniNtupleAnalyzer() {};
        TMiniNtupleAnalyzer(TString HistoVersion, TString BinningFile, TString	DeclareHistoFileName);
        ~TMiniNtupleAnalyzer() {};

        // various setters
        void            SetBinningFileName (TString filename) {fBinningFileName=filename;};
        void            SetDropTracks (bool drop_tracks) { fDropTracks = drop_tracks; };
        void            SetOnlyCalculateEventsPerRun (bool calc_events) { fOnlyCalculateEventsPerRun = calc_events; };
        void            SetSecondaryVertexSmearing (bool smear) { fApplySmearing = smear; };
        void            SetDropTrackProbability(Float_t prob) {fDropProbability = prob;};
        void            SetEtReweightingLF_filename(TString name) {fEtReweightingLF_filename = name;};
        void            SetEtReweightingLF(bool do_reweighting) {fEtReweightingLF = do_reweighting;};
        void            SetTestFirstEvent(unsigned first_event) {fTestFirstEvent = first_event;};
        void            SetSeedVertexSmearing(unsigned seed1, unsigned seed2) {fSeed_rnd = seed1; fSeed_rnd2 = seed2;};
        void            SetSeedCrudeTrackingEfficiency(unsigned seed) {fSeed_rnd_eff = seed;};

        void            SetJetEnergyUncertainty(Double_t    jet_unc) {fJetEnergyUncertainty = jet_unc;}
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
    
        // initialisator the class - TODO: more info here
        void            Initialize();

        //TODO: description here
        void            RecalculateLuminosity();

        // main functionality - loops over events and fills the histograms
        void            Loop (Bool_t IsInclusive);
        void            Loop_v04b (Bool_t IsInclusive);

        // print number of events per run for runs that have non-zero event number
        void            PrintEventsPerRun();

        void            SetPrintingFreq(Int_t   events) {fPrintingFreq = events;};

        void            SetRundCache (bool run_dcache) {fRun_dCache = run_dcache;};
        void            SetDoJetEnergyScaleSyst (bool do_syst) {fDoJetEnergyScaleSyst = do_syst;};

        // vertexing on the CN level
        void            SetRedoVertexing(bool redo_vertexing) {fRedoVertexing = redo_vertexing;};
        void            SetRcut(Float_t r_cut) {fRcut = r_cut;};            //!< Set Cone cut
        void            SetpT(Float_t pt_cut) {fpT = pt_cut;};             //!< Set minimal track pT
        void            SetSTT(Int_t stt) {fSTT = stt;};                   //!< Set minimal number of STT hits
        void            SetCTD(Int_t ctd) {fCTD = ctd;};                   //!< Set minimal number of CTD hits
        void            SetMVD(Int_t mvd) {fMVD = mvd;};                   //!< Set minimal number of MVD hits
        void            SetUseHelixTrackParameters(Bool_t   setHelix) {fUseHelixTrackParameters = setHelix;};

        void            SetStudyResolutions(bool study) {fStudyResolutions = study;};

        // -- analysis-specific variables (not generic)
        // -- change if you want to use for your own analysis
        // NOTE: this remark is rather obsolete, as most of the stuff here is already
        // very analysis-specific; the development isn't done anymore with keeping in mind
        // possible generic usage of this class

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
        
        // TODO: description here
        void        CreateBinHistograms();

        // older methods, to be reviewed
        void        DeclareHistograms(TGlobalBin* tgb);
        void        FillHist(TGlobalBin* tgb, TString HistTitle, Float_t	Value);
        void        MirrorHistogramOLD(TString HistName);
        void        MirrorHistograms();
        Float_t     CalculateSignificance(Int_t	vertex);
        Float_t     CalculateProjDecayLength(Int_t	vertex);
        Bool_t      IsDIS();
        void        WriteHistograms();

        void        GetEtReweightingLF_histo();
        Float_t     getEtReweighting(Float_t   jet_et);

        void        GetFragmentationReweighting_Histo();
        
        // this is similar to getEtReweighting but more generic - works for each histogram/value
        Int_t       getReweightingHistoBin(TH1F * histo, Float_t   value);

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

        TString     fBinningFileName;
        TString     fHistogramDeclarationFile;
        Bool_t      fApplyQ2g4Weighting;
        Double_t    fCharmQ2g4Weight;
        Double_t    fTrueQ2Weight;
        Double_t    fRecoQ2Weight;

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

        // a probability to loose track when the fDropTracks flag is enabled
        Float_t     fDropProbability;
        
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

        unsigned    fTestFirstEvent;

        // for jet energy uncertainty studies
        // can be positive or negative (+-3% being the most common choice)
        Double_t    fJetEnergyUncertainty;
        // if this variable is true, vary total jet energy as given from the jet algo
        // otherwise vary only Calorimetric part of the et energy from ZUFO information
        // default: false (more correct approach)
        bool        fVaryTotalJetEnergy;
        bool        fDoJetEnergyScaleSyst;

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
        void            get_gammaP_boost();             //!< sets the relevant variables used for transformation to gamma-p

        void            print_fmckin_table();
        void            checkArrayBounds();             //!< checks whether array bounds are not violated

        bool            fIsCharm;               //!< true, if this sample is charm, false otherwise
        bool            fIsBeauty;              //!< true, if this sample is beauty, false otherwise

        bool            fStudyResolutions;      //!< a switch to select resolution studies
        
        Float_t         getAverageAngle(Int_t  vertex_id);  //!< calculates an average angle between all possible track combination in the vertex
};
#endif
