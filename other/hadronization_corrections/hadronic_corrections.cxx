// FastJet headers
#include "fastjet/ClusterSequence.hh"

// ROOT headers
#include <TROOT.h>
#include <TSystem.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFile.h>

// system headers
#include <iostream>
#include <vector>
#include <getopt.h>
using namespace std;

// ZACON CN filelists
#include <rg_incl_beauty_dir_DIS_0304p_Q1.h>
#include <rg_incl_beauty_dir_DIS_05e_Q1.h>
#include <rg_incl_beauty_dir_DIS_0607p_Q1.h>
#include <rg_incl_beauty_dir_DIS_06e_Q1.h>
#include <rg_incl_charm_dir_DIS_0304p_Q1.5.h>
#include <rg_incl_charm_dir_DIS_0304p_Q4.h>
#include <rg_incl_charm_dir_DIS_05e_Q1.5.h>
#include <rg_incl_charm_dir_DIS_05e_Q4.h>
#include <rg_incl_charm_dir_DIS_0607p_Q1.5.h>
#include <rg_incl_charm_dir_DIS_0607p_Q4.h>
#include <rg_incl_charm_dir_DIS_06e_Q1.5.h>
#include <rg_incl_charm_dir_DIS_06e_Q4.h>

int main (int argc, char **argv) {

    // parse command line options
    static struct option long_options[] = {
        {"sample",     required_argument, 0, 1},
        {"nevents",    required_argument, 0, 2},
        {"maxpartons", required_argument, 0, 3},
    };
    TString  sample     = "";
    unsigned nevents    = 0;
    unsigned maxpartons = 0;

    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                sample = optarg;
                cout << "INFO: sample= " << sample << endl;
                break;
            case 2:
                nevents = atoi(optarg);
                cout << "INFO: nevents= " << nevents << endl;
                break;
            case 3:
                maxpartons = atoi(optarg);
                cout << "INFO: maxpartons= " << maxpartons << endl;
                break;
            case 'h':
                cout<<"\nUsage: " << endl;
                cout<<"\thadronic_corrections  --sample <sample name> [--maxpartons <max number of partons>] [--nevents <max number of events>]\n"<<endl;
                cout<<"\t\t--sample <sample name> \twhere sample name corresponds to sample name in cninfo; see code or inc/ for list of currently implemented samples." << endl;
                cout <<"\t\t\t\t\t(the two latter combine all available charm/beauty samples"<<endl;
                cout << endl;
                exit(-1);
            default:
                cout << "Unknown opiton or missing option argument. The program will terminate, sorry." << endl;
                exit(-1);
        }
    }

    // create a "chain" - an object that will contain all the ROOT files ("ntuples") we want to analyze
    TChain  * fChain = new TChain ("orange");

    TString dataset = sample;

    if      ( dataset == "rg_incl_beauty_dir_DIS_0304p_Q1" ) ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_0304p_Q1::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_beauty_dir_DIS_05e_Q1" ) ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_05e_Q1::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_beauty_dir_DIS_0607p_Q1" ) ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_0607p_Q1::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_beauty_dir_DIS_06e_Q1" ) ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_06e_Q1::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_0304p_Q1.5" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0304p_Q1_5::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_0304p_Q4" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0304p_Q4::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_05e_Q1.5" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_05e_Q1_5::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_05e_Q4" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_05e_Q4::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_0607p_Q1.5" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0607p_Q1_5::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_0607p_Q4" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0607p_Q4::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_06e_Q1.5" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_06e_Q1_5::addToZaconChain(fChain);
    else if ( dataset == "rg_incl_charm_dir_DIS_06e_Q4" ) ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_06e_Q4::addToZaconChain(fChain);
    // all charm
    else if ( dataset == "charm" ) {
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0304p_Q1_5::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0304p_Q4::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_05e_Q1_5::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_05e_Q4::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0607p_Q1_5::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_0607p_Q4::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_06e_Q1_5::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_charm_dir_DIS_06e_Q4::addToZaconChain(fChain);
    // all beauty
    } else if ( dataset == "beauty" ) {
        ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_0304p_Q1::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_05e_Q1::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_0607p_Q1::addToZaconChain(fChain);
        ZaconChainFactory_v06b_rg_incl_beauty_dir_DIS_06e_Q1::addToZaconChain(fChain);
    } else {
        cout << "ERROR: this dataset is not supported at the moment." << endl;
        abort();
    }

    // calculate number of events (entries) in this set of files or take the number from the command line if given
    unsigned   Nevents;
    if (nevents == 0 ) {
        Nevents = fChain -> GetEntries ();
    } else {
        Nevents = nevents;
    } 
    cout << Nevents << " events will be processed" << endl;

    // declare variables
    Int_t	Nhbmjets;
    Float_t	Pxhbmjet[100];
    Float_t	Pyhbmjet[100];
    Float_t	Pzhbmjet[100];
    Float_t	Ehbmjet[100];
    Int_t	Nphbmjet[100];
    Int_t	Phbmjet[100][512];

    Int_t       Fmck_nstor;
    Int_t       Fmck_prt[10000];
    Int_t       Fmck_daug[10000];
    Int_t       Fmck_daug2[10000];
    Int_t       Fmck_isthep[10000];
    Int_t       Fmck_id[10000];

    Float_t     Fmck_px[10000];
    Float_t     Fmck_py[10000];
    Float_t     Fmck_pz[10000];
    Float_t     Fmck_e[10000];
    Float_t     Fmck_m[10000];

    Float_t	Mc_q2_cr;
    Float_t	Mc_x_cr;

    Int_t       Npart;
    Int_t       Fmck_nkin;

    fChain->SetBranchStatus("*", 0);

    fChain->SetBranchStatus("Nhbmjets", 1);
    fChain->SetBranchAddress("Nhbmjets",&Nhbmjets);
    fChain->SetBranchStatus("Pxhbmjet", 1);
    fChain->SetBranchAddress("Pxhbmjet",Pxhbmjet);
    fChain->SetBranchStatus("Pyhbmjet", 1);
    fChain->SetBranchAddress("Pyhbmjet",Pyhbmjet);
    fChain->SetBranchStatus("Pzhbmjet", 1);
    fChain->SetBranchAddress("Pzhbmjet",Pzhbmjet);
    fChain->SetBranchStatus("Ehbmjet", 1);
    fChain->SetBranchAddress("Ehbmjet",Ehbmjet);

    fChain->SetBranchStatus("Nphbmjet", 1);
    fChain->SetBranchAddress("Nphbmjet",Nphbmjet);
    fChain->SetBranchStatus("Phbmjet", 1);
    fChain->SetBranchAddress("Phbmjet",Phbmjet);

    fChain->SetBranchStatus ("Fmck_nstor", 1);
    fChain->SetBranchAddress("Fmck_nstor",&Fmck_nstor);
    fChain->SetBranchStatus ("Fmck_prt", 1);
    fChain->SetBranchAddress("Fmck_prt", Fmck_prt);
    fChain->SetBranchStatus ("Fmck_daug",1);
    fChain->SetBranchAddress("Fmck_daug", Fmck_daug);
    fChain->SetBranchStatus ("Fmck_daug2",1);
    fChain->SetBranchAddress("Fmck_daug2", Fmck_daug2);
    fChain->SetBranchStatus ("Fmck_id",1);
    fChain->SetBranchAddress("Fmck_id", Fmck_id);
    fChain->SetBranchStatus ("Fmck_px",1);
    fChain->SetBranchAddress("Fmck_px", Fmck_px);
    fChain->SetBranchStatus ("Fmck_py",1);
    fChain->SetBranchAddress("Fmck_py", Fmck_py);
    fChain->SetBranchStatus ("Fmck_pz",1);
    fChain->SetBranchAddress("Fmck_pz", Fmck_pz);
    fChain->SetBranchStatus ("Fmck_m",1);
    fChain->SetBranchAddress("Fmck_m", Fmck_m);
    fChain->SetBranchStatus ("Fmck_e",1);
    fChain->SetBranchAddress("Fmck_e", Fmck_e);
    fChain->SetBranchStatus ("Fmck_isthep",1);
    fChain->SetBranchAddress("Fmck_isthep", Fmck_isthep);

    fChain->SetBranchStatus("Mc_q2_cr", 1);
    fChain->SetBranchAddress("Mc_q2_cr",&Mc_q2_cr);
    fChain->SetBranchStatus("Mc_x_cr", 1);
    fChain->SetBranchAddress("Mc_x_cr",&Mc_x_cr);

    fChain->SetBranchStatus("Fmck_nkin", 1);
    fChain->SetBranchAddress("Fmck_nkin",&Fmck_nkin);

    fChain->SetBranchStatus("Npart", 1);
    fChain->SetBranchAddress("Npart",&Npart);

    // reference hadronization corrections from Philipp
    Float_t chad_et_paper_values_beauty[]= {0.95, 1.08, 1.05, 1.04, 0.99, 0.93, 0.80};
    Float_t chad_et_paper_values_charm[]=  {1.06, 1.05, 1.03, 0.99, 0.96, 0.95, 0.86};
    Float_t * CHAD_ET_PAPER_VALUES;

    Float_t chad_eta_paper_values_beauty[]= {0.96, 0.98, 0.93, 0.91, 0.94, 1.01, 1.06, 1.07, 1.07, 1.07};
    Float_t chad_eta_paper_values_charm[]=  {0.89, 0.97, 1.02, 1.05, 1.07, 1.10, 1.11, 1.10, 1.09, 1.07, 1.13};
    Float_t * CHAD_ETA_PAPER_VALUES;

    Float_t chad_q2_paper_values_beauty[]= {1.01, 1.01, 0.99, 0.98, 0.98, 0.99, 0.99, 1.01};
    Float_t chad_q2_paper_values_charm[]=  {1.15, 1.08, 1.01, 1, 1, 1.01, 1.01, 1.02};
    Float_t * CHAD_Q2_PAPER_VALUES;

    Float_t chad_x_paper_values_beauty[]= {1.09, 1.05, 0.99, 0.95, 0.93, 0.92};
    Float_t chad_x_paper_values_charm[]=  {1.19, 1.20, 1.09, 0.97, 0.91, 0.88};
    Float_t * CHAD_X_PAPER_VALUES;

    Float_t chad_x_q2bin1_paper_values_beauty[]= {1.09, 1.07, 1.04, 0.91};
    Float_t chad_x_q2bin1_paper_values_charm[]=  {1.19, 1.21, 1.23, 1.07};
    Float_t * CHAD_X_Q2BIN1_PAPER_VALUES;

    Float_t chad_x_q2bin2_paper_values_beauty[]= {1.07, 1.05, 1, 0.94, 0.81};
    Float_t chad_x_q2bin2_paper_values_charm[]=  {1.13, 1.09, 1.05, 1.01, 0.91};
    Float_t * CHAD_X_Q2BIN2_PAPER_VALUES;

    Float_t chad_x_q2bin3_paper_values_beauty[]= {1.03, 1.02, 0.98};
    Float_t chad_x_q2bin3_paper_values_charm[]=  {1.07, 1.03, 1.01, 0.93};
    Float_t * CHAD_X_Q2BIN3_PAPER_VALUES;

    Float_t chad_x_q2bin4_paper_values_beauty[]= {1.01, 0.99, 0.92};
    Float_t chad_x_q2bin4_paper_values_charm[]=  {1.05, 1.01, 0.96};
    Float_t * CHAD_X_Q2BIN4_PAPER_VALUES;

    Float_t chad_x_q2bin5_paper_values_beauty[]= {1.01, 1};
    Float_t chad_x_q2bin5_paper_values_charm[]=  {1.02, 1.01};
    Float_t * CHAD_X_Q2BIN5_PAPER_VALUES;

    // binning
    unsigned NBINS_ETA;
    Float_t BINS_ETA_CHARM[] = {-1.6, -1.1, -0.8, -0.5, -0.2, 0.1, 0.4, 0.7, 1, 1.3, 1.6, 2.2};
    Float_t BINS_ETA_BEAUTY[] = {-1.6, -0.8, -0.5, -0.2, 0.1, 0.4, 0.7, 1, 1.3, 1.6, 2.2};
    Float_t * BINS_ETA;

    const unsigned NBINS_ET = 7; 
    const Float_t BINS_ET[] = {5, 8, 11, 14, 17, 20, 25, 35};

    const unsigned NBINS_Q2 = 8; 
    const Float_t BINS_Q2[] = {5, 10, 20, 40, 70, 120, 200, 400, 1000};

    const unsigned NBINS_X = 6; 
    const Float_t BINS_X[] = {0.00008, 0.0002, 0.0006, 0.0016, 0.005, 0.01, 0.1};

    const unsigned NBINS_X_Q2BIN1 = 4;
    Float_t BINS_X_Q2BIN1[] = {8e-05, 0.0002, 0.0003, 0.0005, 0.003};

    const unsigned NBINS_X_Q2BIN2 = 5;
    Float_t BINS_X_Q2BIN2[] = {0.0003, 0.0005, 0.0012, 0.002, 0.0035, 0.01};

    unsigned NBINS_X_Q2BIN3;
    Float_t * BINS_X_Q2BIN3;
    Float_t BINS_X_Q2BIN3_CHARM[] = {0.0008, 0.0018, 0.003, 0.006, 0.04};
    Float_t BINS_X_Q2BIN3_BEAUTY[] = {0.0008, 0.0018, 0.003, 0.006};

    const unsigned NBINS_X_Q2BIN4 = 3;
    Float_t BINS_X_Q2BIN4[] = {0.0016, 0.005, 0.016, 0.06};

    const unsigned NBINS_X_Q2BIN5 = 2;
    Float_t BINS_X_Q2BIN5[] = {0.005, 0.02, 0.1};

    // jet cuts
    Float_t JET_ET_MIN;
    const Float_t JET_ETA_MAX = 2.2;
    const Float_t JET_ETA_MIN = -1.6;

    // charm/beauty dependent quantities
    if ( dataset.Contains("charm") ) {
        NBINS_ETA = 11;
        BINS_ETA = BINS_ETA_CHARM;
        NBINS_X_Q2BIN3 = 4;
        BINS_X_Q2BIN3 = BINS_X_Q2BIN3_CHARM;
        CHAD_ET_PAPER_VALUES  = chad_et_paper_values_charm;
        CHAD_ETA_PAPER_VALUES = chad_eta_paper_values_charm;
        CHAD_Q2_PAPER_VALUES  = chad_q2_paper_values_charm;
        CHAD_X_PAPER_VALUES   = chad_x_paper_values_charm;
        CHAD_X_Q2BIN1_PAPER_VALUES = chad_x_q2bin1_paper_values_charm;
        CHAD_X_Q2BIN2_PAPER_VALUES = chad_x_q2bin2_paper_values_charm;
        CHAD_X_Q2BIN3_PAPER_VALUES = chad_x_q2bin3_paper_values_charm;
        CHAD_X_Q2BIN4_PAPER_VALUES = chad_x_q2bin4_paper_values_charm;
        CHAD_X_Q2BIN5_PAPER_VALUES = chad_x_q2bin5_paper_values_charm;
        JET_ET_MIN = 4.2;
    } else if ( dataset.Contains("beauty") ) {
        NBINS_ETA = 10;
        BINS_ETA = BINS_ETA_BEAUTY;
        NBINS_X_Q2BIN3 = 3;
        BINS_X_Q2BIN3 = BINS_X_Q2BIN3_BEAUTY;
        CHAD_ET_PAPER_VALUES  = chad_et_paper_values_beauty;
        CHAD_ETA_PAPER_VALUES = chad_eta_paper_values_beauty;
        CHAD_Q2_PAPER_VALUES  = chad_q2_paper_values_beauty;
        CHAD_X_PAPER_VALUES   = chad_x_paper_values_beauty;
        CHAD_X_Q2BIN1_PAPER_VALUES = chad_x_q2bin1_paper_values_beauty;
        CHAD_X_Q2BIN2_PAPER_VALUES = chad_x_q2bin2_paper_values_beauty;
        CHAD_X_Q2BIN3_PAPER_VALUES = chad_x_q2bin3_paper_values_beauty;
        CHAD_X_Q2BIN4_PAPER_VALUES = chad_x_q2bin4_paper_values_beauty;
        CHAD_X_Q2BIN5_PAPER_VALUES = chad_x_q2bin5_paper_values_beauty;
        JET_ET_MIN = 5.0;
    }

    // create histograms
    TH1F * hadr_ORANGE_njets = new TH1F ("hadr_ORANGE_njets", "", 20, 0, 20);
    TH1F * hadr_CN_njets     = new TH1F ("hadr_CN_njets",     "", 20, 0, 20);
    TH1F * part_CN_njets     = new TH1F ("part_CN_njets",     "", 20, 0, 20);

    TH1F * hadr_ORANGE_et = new TH1F ("hadr_ORANGE_et", "", NBINS_ET, BINS_ET);
    TH1F * hadr_CN_et     = new TH1F ("hadr_CN_et",     "", NBINS_ET, BINS_ET);
    TH1F * part_CN_et     = new TH1F ("part_CN_et",     "", NBINS_ET, BINS_ET);

    TH1F * hadr_ORANGE_eta = new TH1F ("hadr_ORANGE_eta", "", NBINS_ETA, BINS_ETA);
    TH1F * hadr_CN_eta     = new TH1F ("hadr_CN_eta",     "", NBINS_ETA, BINS_ETA);
    TH1F * part_CN_eta     = new TH1F ("part_CN_eta",     "", NBINS_ETA, BINS_ETA);

    TH1F * hadr_ORANGE_q2 = new TH1F ("hadr_ORANGE_q2", "", NBINS_Q2, BINS_Q2);
    TH1F * hadr_CN_q2     = new TH1F ("hadr_CN_q2",     "", NBINS_Q2, BINS_Q2);
    TH1F * part_CN_q2     = new TH1F ("part_CN_q2",     "", NBINS_Q2, BINS_Q2);

    TH1F * hadr_ORANGE_x = new TH1F ("hadr_ORANGE_x", "", NBINS_X, BINS_X);
    TH1F * hadr_CN_x     = new TH1F ("hadr_CN_x",     "", NBINS_X, BINS_X);
    TH1F * part_CN_x     = new TH1F ("part_CN_x",     "", NBINS_X, BINS_X);

    TH1F * hadr_CN_x_q2bin1 = new TH1F ("hadr_CN_x_q2bin1",     "", NBINS_X_Q2BIN1, BINS_X_Q2BIN1);
    TH1F * part_CN_x_q2bin1 = new TH1F ("part_CN_x_q2bin1",     "", NBINS_X_Q2BIN1, BINS_X_Q2BIN1);

    TH1F * hadr_CN_x_q2bin2 = new TH1F ("hadr_CN_x_q2bin2",     "", NBINS_X_Q2BIN2, BINS_X_Q2BIN2);
    TH1F * part_CN_x_q2bin2 = new TH1F ("part_CN_x_q2bin2",     "", NBINS_X_Q2BIN2, BINS_X_Q2BIN2);

    TH1F * hadr_CN_x_q2bin3 = new TH1F ("hadr_CN_x_q2bin3",     "", NBINS_X_Q2BIN3, BINS_X_Q2BIN3);
    TH1F * part_CN_x_q2bin3 = new TH1F ("part_CN_x_q2bin3",     "", NBINS_X_Q2BIN3, BINS_X_Q2BIN3);

    TH1F * hadr_CN_x_q2bin4 = new TH1F ("hadr_CN_x_q2bin4",     "", NBINS_X_Q2BIN4, BINS_X_Q2BIN4);
    TH1F * part_CN_x_q2bin4 = new TH1F ("part_CN_x_q2bin4",     "", NBINS_X_Q2BIN4, BINS_X_Q2BIN4);

    TH1F * hadr_CN_x_q2bin5 = new TH1F ("hadr_CN_x_q2bin5",     "", NBINS_X_Q2BIN5, BINS_X_Q2BIN5);
    TH1F * part_CN_x_q2bin5 = new TH1F ("part_CN_x_q2bin5",     "", NBINS_X_Q2BIN5, BINS_X_Q2BIN5);

    TH1F * part_npartons = new TH1F ("part_npartons", "", 20, 0, 20);

    TIter next(gDirectory->GetList());
    TObject* obj;
    while ( obj= (TObject*)next() ) {
        TString className = obj -> ClassName();
        if ( className != "TH1F") continue;
        ( (TH1F*)obj ) -> Sumw2();
    }

    // vector to store FMCK_ID of stable c/b hadrons and their daughters (the daughters won't be considered in the clustering algorithm)
    vector<unsigned> donttake;

    // 2D-arrays to store particle ID ranges
    unsigned const NBRANGE = 7;
    unsigned const NCRANGE = 3;
    unsigned BRANGE[2][NBRANGE] = {
                                   {72, 214, 468, 480, 500, 504, 508},
                                   {75, 215, 471, 497, 501, 505, 509}
                                  };
    unsigned CRANGE[2][NCRANGE] = {
                                   {64, 208, 466},
                                   {69, 211, 467}
                                  };

    // electron flag
    bool electron_flag = false;

    // input to the jet finder
    vector<fastjet::PseudoJet> hadrons;
    vector<fastjet::PseudoJet> partons;

    // resulting jets
    vector<fastjet::PseudoJet> hadron_jets;
    vector<fastjet::PseudoJet> parton_jets;

    // choose a jet definition
    double R = 1.0;
    fastjet::JetDefinition jet_def(fastjet::kt_algorithm, R, fastjet::E_scheme);

    // helper
    bool skip_this_particle = false;

    // loop over events
    for (unsigned event = 0; event < Nevents; event++) {

        if ( event % 100000 == 0 )   cout<< " processing event " << event << endl;

        fChain -> GetEntry(event);

        // fiducial volume
        if (Mc_q2_cr<5) continue;
        if (Mc_q2_cr>1000) continue;
        Float_t Mc_y = Mc_q2_cr / (318.*318.* Mc_x_cr);
        if (Mc_y < 0.02)  continue;
        if (Mc_y > 0.7)  continue;

        // clean up
        donttake.clear();
        electron_flag = false;
        hadrons.clear();
        partons.clear();
        hadron_jets.clear();
        parton_jets.clear();

        // ------ CN HADRON JETS ------ //
        // loop over FMCKIN table
        for (Int_t prt=0; prt<Fmck_nstor; prt++) {

            skip_this_particle = false;
            // check if this is a daughter particle
            if ( Fmck_daug[prt] > 0 ) {
                // check whether part of the decay chain of already found b/c hadrons that should be treated as stable
                for (unsigned prt_notake=0; prt_notake<donttake.size(); prt_notake++) {
                    // if this is a daughter of one of those - add to the list
                    if ( Fmck_daug[prt] == donttake[prt_notake] ) {
                        donttake.push_back( Fmck_id[prt] );
                        skip_this_particle = true;
                        break;
                    }
                }
            }

            // skip this particle - in the decay chain of the b/c hadron which should be treated as stable
            if (skip_this_particle) continue;

            bool stable_hadron=false;
            // check whether this is a weakly decaying b/c hadron,
            // add to the donttake array if yes
            // beauty
            for (unsigned bhadr = 0; bhadr < NBRANGE; bhadr++) {
                if ( (Fmck_prt[prt] >= BRANGE[0][bhadr]) && (Fmck_prt[prt] <= BRANGE[1][bhadr]) ) {
                    donttake.push_back( Fmck_id[prt] );
                    stable_hadron = true;
                    break;
                }
            }
            // charm
            for (unsigned chadr = 0; chadr < NCRANGE; chadr++) {
                if ( (Fmck_prt[prt] >= CRANGE[0][chadr]) && (Fmck_prt[prt] <= CRANGE[1][chadr]) ) {
                    donttake.push_back( Fmck_id[prt] );
                    stable_hadron = true;
                    break;
                }
            }

            // sanity check: hadron we treat stable should have decayed in fact
            // if (stable_hadron && ((Fmck_isthep[prt] % 10000) != 2) ) {
            //    cout << "WARNING: weakly decaying hadron has not decayed in MC! " << endl;
            // }

            // check whether this is the scattered electron; skip if yes
            if ( (Fmck_isthep[prt] % 10000) == 1 ) {
                if (  ((Fmck_prt[prt]==23)||(Fmck_prt[prt]==24)) && (!electron_flag) ) {
                    electron_flag = true;
                    // sanity check
                    if (Fmck_daug[prt] != 1) abort();
                    continue;
                }
            }

            if ( stable_hadron || ( (Fmck_isthep[prt] % 10000) == 1 ) ) {
                // ok, this is input particle to jet finder
                fastjet::PseudoJet particle(Fmck_px[prt], Fmck_py[prt], Fmck_pz[prt], Fmck_e[prt]);
                hadrons.push_back(particle);
             }
        }

        // run the clustering, extract the jets
        fastjet::ClusterSequence ClusterSequenceHadrons(hadrons, jet_def);
        hadron_jets = ClusterSequenceHadrons.inclusive_jets();

        // ------ CN PARTON JETS ------ //
        // note: this is a c++ implementation of the relevant part of code from mcjets.fpp originally written by Philipp Roloff
        unsigned first_string = 0;
        unsigned first_mother = 10000;
        for (Int_t prt=0; prt<Fmck_nstor; prt++) {

            // find the first string and the first mother-of-a-string
            if (Fmck_prt[prt] == 2092) {
                if ( first_string == 0 ) first_string = Fmck_id[prt];
                if ( Fmck_daug[prt] < first_mother) first_mother = Fmck_daug[prt];
            }
        }

        for (Int_t prt=0; prt<Fmck_nstor; prt++) {

            if ( (Fmck_id[prt]>=first_mother) && (Fmck_id[prt]<first_string) ) {
                fastjet::PseudoJet particle(Fmck_px[prt], Fmck_py[prt], Fmck_pz[prt], Fmck_e[prt]);
                partons.push_back(particle);
            }
        }

        unsigned npartons = partons.size();

        // for Achim's systematic check - skip event if more than a certain number of partons
        if ( (maxpartons != 0) && (npartons > maxpartons) ) continue;

        part_npartons -> Fill(npartons);
        fastjet::ClusterSequence ClusterSequencePartons(partons, jet_def);
        parton_jets = ClusterSequencePartons.inclusive_jets();

        // ------ FILL HISTOGRAMS ------ //
        // CN hadron jets
        unsigned cn_hadron_jets = 0;
        for (int jet=0; jet<hadron_jets.size(); jet++) {
            Double_t et = hadron_jets[jet].Et();
            Double_t eta = hadron_jets[jet].eta();
            if ( et < JET_ET_MIN ) continue;
            if ( eta > JET_ETA_MAX ) continue;
            if ( eta < JET_ETA_MIN ) continue;
            hadr_CN_et -> Fill( et );
            hadr_CN_eta -> Fill( eta );
            hadr_CN_q2 -> Fill( Mc_q2_cr );
            hadr_CN_x -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 5) && (Mc_q2_cr < 20) )  hadr_CN_x_q2bin1 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 20) && (Mc_q2_cr < 60) )  hadr_CN_x_q2bin2 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 60) && (Mc_q2_cr < 120) )  hadr_CN_x_q2bin3 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 120) && (Mc_q2_cr < 400) )  hadr_CN_x_q2bin4 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 400) && (Mc_q2_cr < 1000) )  hadr_CN_x_q2bin5 -> Fill( Mc_x_cr );
            cn_hadron_jets++;
        }
        hadr_CN_njets -> Fill (cn_hadron_jets);

        // ORANGE hadron jets
        unsigned orange_jets = 0;
        for (int k=0; k<Nhbmjets; k++) {
            TLorentzVector jet(Pxhbmjet[k], Pyhbmjet[k], Pzhbmjet[k], Ehbmjet[k]);
            if ( jet.Et() < JET_ET_MIN ) continue;
            if ( jet.Eta() > JET_ETA_MAX ) continue;
            if ( jet.Eta() < JET_ETA_MIN ) continue;
            // fill histos
            hadr_ORANGE_et -> Fill( jet.Et() );
            hadr_ORANGE_eta -> Fill( jet.Eta() );
            hadr_ORANGE_q2 -> Fill( Mc_q2_cr );
            hadr_ORANGE_x -> Fill( Mc_x_cr );
            orange_jets++;
        }
        hadr_ORANGE_njets -> Fill (orange_jets);

        // CN parton jets
        unsigned cn_parton_jets = 0;
        for (int jet=0; jet<parton_jets.size(); jet++) {
            Double_t et = parton_jets[jet].Et();
            Double_t eta = parton_jets[jet].eta();
            if ( et < JET_ET_MIN ) continue;
            if ( eta > JET_ETA_MAX ) continue;
            if ( eta < JET_ETA_MIN ) continue;
            part_CN_et -> Fill( et );
            part_CN_eta -> Fill( eta );
            part_CN_q2 -> Fill( Mc_q2_cr );
            part_CN_x -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 5) && (Mc_q2_cr < 20) )  part_CN_x_q2bin1 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 20) && (Mc_q2_cr < 60) )  part_CN_x_q2bin2 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 60) && (Mc_q2_cr < 120) )  part_CN_x_q2bin3 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 120) && (Mc_q2_cr < 400) )  part_CN_x_q2bin4 -> Fill( Mc_x_cr );
            if ( (Mc_q2_cr >= 400) && (Mc_q2_cr < 1000) )  part_CN_x_q2bin5 -> Fill( Mc_x_cr );
            cn_parton_jets++;
        }
        part_CN_njets -> Fill (cn_parton_jets);

    }

    gROOT -> SetStyle("Plain");
    TString PLOTS_PATH = getenv("PLOTS_PATH");

    TString maxpartons_str = "";
    maxpartons_str += maxpartons;
    TFile * output = new TFile (PLOTS_PATH+"/"+dataset+"_max_"+maxpartons_str+"_partons"+".root", "recreate");
    output -> cd();

    // hadron level
    hadr_ORANGE_njets -> Write();
    hadr_ORANGE_et -> Write();
    hadr_ORANGE_eta -> Write();
    hadr_CN_njets -> Write();
    hadr_CN_et -> Write();
    hadr_CN_eta -> Write();
    hadr_CN_x_q2bin1 -> Write();
    hadr_CN_x_q2bin2 -> Write();
    hadr_CN_x_q2bin3 -> Write();
    hadr_CN_x_q2bin4 -> Write();
    hadr_CN_x_q2bin5 -> Write();

    // parton level
    part_CN_njets -> Write();
    part_CN_et -> Write();
    part_CN_eta -> Write();
    part_CN_x_q2bin1 -> Write();
    part_CN_x_q2bin2 -> Write();
    part_CN_x_q2bin3 -> Write();
    part_CN_x_q2bin4 -> Write();
    part_CN_x_q2bin5 -> Write();

    // hadronisation corrections
    TH1F * chad_et = (TH1F*)hadr_CN_et -> Clone("chad_et");
    chad_et -> Divide(part_CN_et);
    chad_et -> Write();

    TH1F * chad_eta = (TH1F*)hadr_CN_eta -> Clone("chad_eta");
    chad_eta -> Divide(part_CN_eta);
    chad_eta -> Write();

    TH1F * chad_q2 = (TH1F*)hadr_CN_q2 -> Clone("chad_q2");
    chad_q2 -> Divide(part_CN_q2);
    chad_q2 -> Write();

    TH1F * chad_x = (TH1F*)hadr_CN_x -> Clone("chad_x");
    chad_x -> Divide(part_CN_x);
    chad_x -> Write();

    TH1F * chad_x_q2bin1 = (TH1F*)hadr_CN_x_q2bin1 -> Clone("chad_x_q2bin1");
    chad_x_q2bin1 -> Divide(part_CN_x_q2bin1);
    chad_x_q2bin1 -> Write();

    TH1F * chad_x_q2bin2 = (TH1F*)hadr_CN_x_q2bin2 -> Clone("chad_x_q2bin2");
    chad_x_q2bin2 -> Divide(part_CN_x_q2bin2);
    chad_x_q2bin2 -> Write();

    TH1F * chad_x_q2bin3 = (TH1F*)hadr_CN_x_q2bin3 -> Clone("chad_x_q2bin3");
    chad_x_q2bin3 -> Divide(part_CN_x_q2bin3);
    chad_x_q2bin3 -> Write();

    TH1F * chad_x_q2bin4 = (TH1F*)hadr_CN_x_q2bin4 -> Clone("chad_x_q2bin4");
    chad_x_q2bin4 -> Divide(part_CN_x_q2bin4);
    chad_x_q2bin4 -> Write();

    TH1F * chad_x_q2bin5 = (TH1F*)hadr_CN_x_q2bin5 -> Clone("chad_x_q2bin5");
    chad_x_q2bin5 -> Divide(part_CN_x_q2bin5);
    chad_x_q2bin5 -> Write();

    // draw also the current corrections
    TH1F * chad_et_paper = new TH1F ("chad_et_paper", "", NBINS_ET, BINS_ET);
    for (unsigned i=0; i<NBINS_ET; i++) chad_et_paper -> SetBinContent(i+1, CHAD_ET_PAPER_VALUES[i]);
    chad_et_paper -> Write();

    TH1F * chad_eta_paper = new TH1F ("chad_eta_paper", "", NBINS_ETA, BINS_ETA);
    for (unsigned i=0; i<NBINS_ETA; i++) chad_eta_paper -> SetBinContent(i+1, CHAD_ETA_PAPER_VALUES[i]);
    chad_eta_paper -> Write();

    TH1F * chad_q2_paper = new TH1F ("chad_q2_paper", "", NBINS_Q2, BINS_Q2);
    for (unsigned i=0; i<NBINS_Q2; i++) chad_q2_paper -> SetBinContent(i+1, CHAD_Q2_PAPER_VALUES[i]);
    chad_q2_paper -> Write();

    TH1F * chad_x_paper = new TH1F ("chad_x_paper", "", NBINS_X, BINS_X);
    for (unsigned i=0; i<NBINS_X; i++) chad_x_paper -> SetBinContent(i+1, CHAD_X_PAPER_VALUES[i]);
    chad_x_paper -> Write();

    TH1F * chad_x_q2bin1_paper = new TH1F ("chad_x_q2bin1_paper", "", NBINS_X_Q2BIN1, BINS_X_Q2BIN1);
    for (unsigned i=0; i<NBINS_X_Q2BIN1; i++) chad_x_q2bin1_paper -> SetBinContent(i+1, CHAD_X_Q2BIN1_PAPER_VALUES[i]);
    chad_x_q2bin1_paper -> Write();

    TH1F * chad_x_q2bin2_paper = new TH1F ("chad_x_q2bin2_paper", "", NBINS_X_Q2BIN2, BINS_X_Q2BIN2);
    for (unsigned i=0; i<NBINS_X_Q2BIN2; i++) chad_x_q2bin2_paper -> SetBinContent(i+1, CHAD_X_Q2BIN2_PAPER_VALUES[i]);
    chad_x_q2bin2_paper -> Write();

    TH1F * chad_x_q2bin3_paper = new TH1F ("chad_x_q2bin3_paper", "", NBINS_X_Q2BIN3, BINS_X_Q2BIN3);
    for (unsigned i=0; i<NBINS_X_Q2BIN3; i++) chad_x_q2bin3_paper -> SetBinContent(i+1, CHAD_X_Q2BIN3_PAPER_VALUES[i]);
    chad_x_q2bin3_paper -> Write();

    TH1F * chad_x_q2bin4_paper = new TH1F ("chad_x_q2bin4_paper", "", NBINS_X_Q2BIN4, BINS_X_Q2BIN4);
    for (unsigned i=0; i<NBINS_X_Q2BIN4; i++) chad_x_q2bin4_paper -> SetBinContent(i+1, CHAD_X_Q2BIN4_PAPER_VALUES[i]);
    chad_x_q2bin4_paper -> Write();

    TH1F * chad_x_q2bin5_paper = new TH1F ("chad_x_q2bin5_paper", "", NBINS_X_Q2BIN5, BINS_X_Q2BIN5);
    for (unsigned i=0; i<NBINS_X_Q2BIN5; i++) chad_x_q2bin5_paper -> SetBinContent(i+1, CHAD_X_Q2BIN5_PAPER_VALUES[i]);
    chad_x_q2bin5_paper -> Write();

    part_npartons -> Write();

    return 0;
}
