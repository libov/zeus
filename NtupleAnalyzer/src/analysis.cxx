
//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//  Last Modified: April 2011                   //
//////////////////////////////////////////////////

// system includes
#include <iostream>
#include <getopt.h>
using namespace std;

// ROOT includes
#include <TChain.h>
#include <TMath.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TSystem.h>

// my includes
#include<inc/TMiniNtupleAnalyzer.h>
#include<inc/TVertex.h>

// initialize static members
// NOTE: THESE STATIC OBJECTS (COMING FROM TVERTEX CLASS)
// SHOULD BE INITIALIZED HERE, OTHERWISE THE LINKER WILL FAIL
TRandom3 TVertex::rnd;
TRandom3 TVertex::rnd2;
TRandom3 TVertex::fRndDropTracks;
unsigned TVertex::two_track_vertices_total = 0;
unsigned TVertex::two_track_vertices_dropped = 0;


/*! Main function
    \fn main
*/
int main(int argc, char **argv) {
    // first, handle command-line arguments

    // declare some variables to store command line arguments. they include:
    // properties of the sample
    TSubSet::Type       type;
    TSubSet::Flavour    flavour;
    TSubSet::Period     period;
    TSubSet::Q2         q2;
    TSubSet::Process    process;
    unsigned            trigger_period;

    // a suffix of a file with binning
    TString             BinningFileSuffix;

    // version of the histograms
    TString             HistogramsVersionEnding;

    // helping boolean variables to make sure all the arguments were passed correctly 
    bool                type_set = false;
    bool                flavour_set = false;
    bool                period_set = false;
    bool                q2_set = false;
    bool                process_set = false;
    bool                trigger_period_set = false;
    bool                binning_file_suffix_set = false;
    bool                histogram_version_ending_set = false;
    bool                run_tracking_efficiency = false;
    bool                test_mode = false;
    int                 nevents_test = 500000;
    bool                dCache = false;

    // flag to distinguish luminosity-only mode
    bool                recalulate_luminosity_only = false;

    // flag to state that specific text file was selected for ntuple list
    bool                specific_filelist = false;
    TString             FileList;

    // for jet energy scale uncertainty studies
    bool                vary_jet_energy_scale = false;
    Float_t             jet_energy_scale_variation = 0;

    // for significance smearing
    Float_t             SmearingGauss1Prob = -1;
    Float_t             SmearingGauss1Width = -1;
    Float_t             SmearingGauss2Prob = -1;
    Float_t             SmearingGauss2Width = -1;
    Float_t             SmearingExpProb = -1;
    Float_t             SmearingExpCoeff = -1;

    // declare long options
    static struct option long_options[] = {
        {"gaus1prob", required_argument, 0, 1},
        {"gaus1width", required_argument, 0, 2},
        {"gaus2prob", required_argument, 0, 3},
        {"gaus2width", required_argument, 0, 4},
        {"expprob", required_argument, 0, 5},
        {"expcoeff", required_argument, 0, 6},
        {"tracking", no_argument, 0, 7},
        {"test", no_argument, 0, 8},
        {"nevents_test", required_argument, 0, 9},
        {"dCache", no_argument, 0, 10}
    };
    // loop over program arguments (i.e. argv array) and store info to above variables depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "t:f:p:q:o:g:b:v:rhl:j:", long_options, &option_index)) != -1) {
        switch (option) {
            case 't':
                type = (TSubSet::Type) atoi(optarg);
                type_set = true;
                break;
            case 'f':
                flavour = (TSubSet::Flavour) atoi(optarg);
                flavour_set = true;
                break;
            case 'p':
                period = (TSubSet::Period) atoi(optarg);
                period_set = true;
                break;
            case 'q':
                q2 = (TSubSet::Q2) atoi(optarg);
                q2_set = true;
                break;
            case 'o':
                process = (TSubSet::Process) atoi(optarg);
                process_set = true;
                break;
            case 'g':
                trigger_period = (unsigned) atoi(optarg);
                trigger_period_set = true;
                break;
            case 'b':
                BinningFileSuffix = optarg;
                binning_file_suffix_set = true;
                break;
            case 'v':
                HistogramsVersionEnding = optarg;
                histogram_version_ending_set = true;
                break;
            case 'r':
                recalulate_luminosity_only = true;
                break;
            case 'l':
                specific_filelist = true;
                FileList = optarg;
                break;
            case 'j':
                vary_jet_energy_scale = true;
                jet_energy_scale_variation = atof(optarg);
                break;
            case 1:
                SmearingGauss1Prob = atof(optarg);
                break;
            case 2:
                SmearingGauss1Width = atof(optarg);
                break;
            case 3:
                SmearingGauss2Prob = atof(optarg);
                break;
            case 4:
                SmearingGauss2Width = atof(optarg);
                break;
            case 5:
                SmearingExpProb = atof(optarg);
                break;
            case 6:
                SmearingExpCoeff = atof(optarg);
                break;
            case 7:
                run_tracking_efficiency = true;
                break;
            case 8:
                test_mode = true;
                break;
            case 9:
                nevents_test = (int)atof(optarg);
                break;
            case 10:
                dCache = true;
                break;
            case 'h':
                cout<<"\nUsage: " << endl;
                cout<<"\t analysis  -t <Type> -p <Period> [-f <Flavour> -q <Q2> -o <Process> -g <trigger period>] -b <Binning File Suffix> -v <Histograms Version Ending> [-r] [-j <size of the variation of the jet energy scale>] [-l <filename> run on specific filelist; all the sample properties set from the command line will be just dummies]"<<endl;
                cout << "\n<Type>:\nkDATA = 1,\nkMC = 2,\n\n";
                cout << "<Flavour>:\nkLIGHT = 1,\nkCHARM=2,\nkBEAUTY=3\n\n";
                cout << "<Period>:\nk03P=1, (only DATA!)\nk04P=2, (only DATA!)\nk0304P=3, (only MC!)\nk05E=4,\nk06E=5,\nk06P=6, (only DATA!)\nk07P=7, (only DATA!)\nk0607P=8, (only MC!)\n\n";
                cout << "<Q2>:\nkQ2g1=1,\nkQ2g1_5=2,\nkQ2g4=3\n\n";
                cout << "<Process>:\nkBGF=1,\nkRESOLVED=2\n\n";
                cout << "<trigger period>:\n0 if none selected; positive integer number denotes subtrigger period as given in the XML file\n\n";
                cout << "-r : if selected, only recalculation of the luminosity will take place\n\n";
                cout << "--tracking\t\trun tracking efficiency code, don't run the analysis\n\n";
                cout << "--test\t\trun in test mode\n\n";
                cout << "--nevents_test\t\tnumber of events to be processed in test mode\n\n";
                cout << "--dCache\t\trun directly on dCache\n\n";
                cout << "Consult also TSubSet.h for encoding, this might be outdated\n" << endl;
                exit(-1);
            default:
                cout << "Unknown opiton or missing option argument. The program will terminate, sorry." << endl;
                exit(-1);
        }
    }

    // check whether we have enough arguments to run the program
    // should be different for data and MC (less info needed for data - no flavour, q2 or trigger information)

    // helping variable to flag whether there were enough arguments or not
    bool    not_enough_arguments = false;

    // these arguments should be specified both for data and mc
    if ( ! (type_set && binning_file_suffix_set && histogram_version_ending_set && period_set) ) {
        not_enough_arguments=true;
    }

    // for MC there are also additional requirements
    if ( (type_set) && (type == TSubSet::kMC)) {
        if  ( !(flavour_set && q2_set && process_set && trigger_period_set) ) not_enough_arguments = true;
    }

    // if not enough arguments, inform user and wuit
    if (not_enough_arguments && (!specific_filelist)) {
        cout << "\nNot enough aruments to run " << argv[0] << endl;
        cout << "For more info please try:\n\n";
        cout << argv[0] << " -h" << endl;
        cout << "\nThe program will terminate, sorry." << endl;
        exit(-1);
    }

    // ok, the necessary number of arguments was provided, the program can continue

    // print warm welcome message
    cout<<"\n\n******************************************************"<<endl;
    cout<<"* Welcome to ZEUS Common Ntuple analysis framework   *"<<endl;
    cout<<"* Step 2: analyis of ntuples and filling histograms  *"<<endl;
    cout<<"* Input: root ntuples                                *"<<endl;
    cout<<"* Output: root files with histograms                 *"<<endl;
    cout<<"******************************************************"<<endl<<endl;

    // construct binning file name
    TString     BinningFileName = "binning."+BinningFileSuffix+".cfg";
    cout<<"INFO: File with binning: "<<BinningFileName<<endl;

    // get histograms version
    TString     HistogramsVersion=BinningFileSuffix + HistogramsVersionEnding;
    cout<<"INFO: Histograms Version: "<<HistogramsVersion<<endl;

    // default name of the file containing histograms declaration
    TString     DeclareHistogramsFileName = "declarehist.cfg";
    if (run_tracking_efficiency) DeclareHistogramsFileName = "declarehist.tracking.cfg";
    cout<<"INFO: File with histograms declaration: "<< DeclareHistogramsFileName << endl;

    // a leftover from times when I didn't drop heavy quarks from inclusive ARIADNE MC
    Bool_t      reject_cb_from_ari=true;
    if (reject_cb_from_ari) {
        cout<<"INFO: Selected to remove c & b from ARIADNE MC"<<endl;
    } else {
        cout<<"INFO: Selected NOT to remove c & b from ARIADNE MC"<<endl<<endl;
    }

    // create an instance of NTupleAnalyzer
    TMiniNtupleAnalyzer* instance=new TMiniNtupleAnalyzer(HistogramsVersion, BinningFileName, DeclareHistogramsFileName);

    // set properties of the sample as given from the command line
    instance -> setType(type);
    instance -> setPeriod(period);
    if (type == TSubSet::kMC) {
        instance -> setFlavour(flavour);
        instance -> setQ2(q2);
        instance -> setProcess(process);
    }
    instance -> setTriggerPeriod(trigger_period);

    // set name of the file with list of root files to be processed; normally it's determined
    // automaticaly from name of the sample, but sometimes we want to run on specific file
    if ( specific_filelist ) {
        instance -> setFileListName(FileList);
    }

    // -----------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------
    // ---------------------------  set various specific options -------------------------------------
    // -----------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------
    // select whether should run in the test mode:
    // only reduced number of events (set byTMiniNtupleAnalyzer::SetTestNumberOfEvents) 
    // starting from what is set by SetTestFirstEvent will be processed;
    if (test_mode) instance -> SetTestMode(true);
    else  instance -> SetTestMode(false);
    instance -> SetTestNumberOfEvents(nevents_test);
    instance -> SetTestFirstEvent(0);

    // print every nth event
    instance -> SetPrintingFreq(100000);

    // if this switch is selected, only true variables will be studied; default = false (i.e. process also reco level)
    instance -> SetTrueLevelStudies(false);

    // select whether secondary vertex smearing should be done or not
    instance -> SetSecondaryVertexSmearing (true);
    instance -> SetSeedVertexSmearing (4357, 4357);

    // smearing parameters (default values; OVERWRITTEN IF SET FROM THE COMMAND LINE)
    instance -> fSmearingGauss1Prob = 0.07;
    instance -> fSmearingGauss1Width = 1.6;
    instance -> fSmearingGauss2Prob = 0.002;
    instance -> fSmearingGauss2Width = 7;
    instance -> fSmearingExpProb = 0;
    instance -> fSmearingExpCoeff = 5;
    // if smearingparameters set from the command line - overwrite them
    if (SmearingGauss1Prob != -1) instance -> fSmearingGauss1Prob = SmearingGauss1Prob;
    if (SmearingGauss1Width != -1) instance -> fSmearingGauss1Width = SmearingGauss1Width;
    if (SmearingGauss2Prob != -1) instance -> fSmearingGauss2Prob = SmearingGauss2Prob;
    if (SmearingGauss2Width != -1) instance -> fSmearingGauss2Width = SmearingGauss2Width;
    if (SmearingExpProb != -1) instance -> fSmearingExpProb = SmearingExpProb;
    if (SmearingExpCoeff != -1) instance -> fSmearingExpCoeff = SmearingExpCoeff;

    // print out final values for a later access
    if (type == TSubSet::kMC) {
        cout << "INFO: the following smearing parameters are used:\n";
        cout << "   Gaus1 Probability(%): " << instance -> fSmearingGauss1Prob << endl;
        cout << "   Gaus1 Width: " << instance -> fSmearingGauss1Width << endl;
        cout << "   Gaus2 Probability(%): " << instance -> fSmearingGauss2Prob << endl;
        cout << "   Gaus2 Width: " << instance -> fSmearingGauss2Width << endl;
        cout << "   Exponent probability: " << instance -> fSmearingExpProb << endl;
        cout << "   Exponent coefficient: " << instance -> fSmearingExpCoeff << endl;
    }

    // set the name of the histogram that contains reweighting function
    // for reweighting of Et for LF
    instance -> SetEtReweightingLF(true);
    instance -> SetEtReweightingLF_filename ("ET_reweighting_LF.root");

    // Q2 reweighting
    instance -> SetApplyQ2Reweighting(true);

    // eta reweighting - switch on/off and set the parameters
    instance -> SetApplyCharmEtaReweighting(true);
    instance -> SetCharmEtaReweighting_p0(0.937);
    instance -> SetCharmEtaReweighting_p1(0.109);
    instance -> SetCharmEtaReweighting_p2(0.0715);    // i.e. 0.0888558 / 1.2419

    // Et reweighting
    instance -> SetApplyCharmETReweighting(true);
    instance -> SetCharmETReweightingPar(0.753431, 0.189124);

    // a flag to say whether we want to do tracking uncertainty studies
    instance -> SetDropTracks (false);
    // if true, Sasha Spiridonov's map will be used, meaning that track drop probability is
    // determined on a track-by-track basis
    instance -> SetUseHadronicInteractionMap (true);
    // defines probability to loose a track in case of constant probability (i.e. when SetUseHadronicInteractionMap(false))
    instance -> SetDropTrackProbability (0.02);
    // defines a hadronic interaction correction factor on MC in case of Sasha's map is used (i.e. when SetUseHadronicInteractionMap(true))
    instance -> SetHadronicInteractionCorrection(0.4);

    // for the jet energy scale uncertainty
    // 0 = no change, default
    // +/- 3%  - increase/decrease CAL part of the jet energy by given amount
    instance -> SetDoJetEnergyScaleSyst (vary_jet_energy_scale);
    if (vary_jet_energy_scale) {
        cout << "INFO: varying jet energy by " << jet_energy_scale_variation << endl;
        instance -> SetJetEnergyUncertainty(jet_energy_scale_variation);
    } else {
        instance -> SetJetEnergyUncertainty(0);
    }
    // false - vary only CAL energy, true - vary total jet energy
    instance -> SetVaryTotalJetEnergy(false);

    // for EM scale systematic uncertainty
    // 0 - no change, default
    // +-0.01  - variations (+-1%)
    instance -> set_do_EM_scale_syst (false);
    instance -> SetEMScaleUncertainty (0);  // has effect only if set_do_EM_scale_syst(true) was set

    // use fragmentation function reweighting
    instance -> SetFragmentationReweighting(false);
    instance -> SetCharmFragmentationReweightingSize(0);
    instance -> SetBeautyFragmentationReweightingSize(1.5);
    // different reweighting functions for beauty and charm
    if (flavour == TSubSet::kCHARM) {
        instance -> SetFragmentationReweighting_filename("bowler_to_peterson_zstring.root");
    } else if (flavour == TSubSet::kBEAUTY) {
        instance -> SetFragmentationReweighting_filename("bowler_to_peterson_zstring_BEAUTY.root");
    }

    // use BR and fragm. fraction reweighting routine by S. Viazlo
    instance -> SetSashasReweighting (true);

    // set Et and eta cut for jets
    instance -> SetJetEtCut (4.2);
    instance -> SetUpEtaCut (2.2);
    instance -> SetLowEtaCut (-1.6);

    // redo vertex track selection and revertexing; affects only v04 and higher
    instance -> SetRedoVertexing(true);
    instance -> SetRcut(1);
    instance -> SetpT(0.5);
    instance -> SetSTT(0);
    instance -> SetCTD(3);
    instance -> SetMVD(4);
    instance -> SetUseHelixTrackParameters(true);

    // some histograms to study resolutions (MC only); quite cpu expensive, so do this
    // on part of the sample
    instance -> SetStudyResolutions (false);

    // select whether to run on Minintuples or on dCache
    if (dCache) instance -> SetRundCache (true);
    else instance -> SetRundCache (false);
    // if selected to run on a specific filelist, this must be the dCache run
    if (specific_filelist) instance -> SetRundCache (true);

    // in case of Minintuples, specify the path
    TString     MINI_NTUPLES_PATH = getenv("MINI_NTUPLES_PATH");
    instance -> SetPathToMiniNtuples(MINI_NTUPLES_PATH);
    instance -> SetMiniNtuplesOn_dCache (true);

    // -----------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------

    // now that we have set all the parameters, the Initialize() can be called;
    // this will add the root files, calculate number of events, and other internal stuff
    // that should be done after all the settings were chosen
    instance -> Initialize();

    // if selected only to recalculate luminosity, call the respective routine and
    // return; don't do full analysis
    if (recalulate_luminosity_only) {
        if (type == TSubSet::kMC) {
            instance -> RecalculateLuminosity();
            return 0;
        } else if (type == TSubSet::kDATA) {
            instance -> SetOnlyCalculateEventsPerRun (true);
        }
    }

    // if selected to run only tracking efficiency part
    if (run_tracking_efficiency) {
        // some settings
        instance -> setApplyPtReweighting(true);
        instance -> setApplyPhiReweighting(true);
        instance -> setApplyThetaStarReweighting(true);
        instance -> setDebugPrintout(false);
        // start event loop
        instance -> TrackingEfficiency();
        return 0;
    }

    // loop over events!
    // REMINDER: TMiniNtupleAnalyzer::Loop() takes a boolean agrument = true if reject c and be from ari; else - not;
    // NOTE: this now contains a hack to distinguish between v04 and v02; TODO: revisit, avoid code duplication!
    #ifdef CN_VERSION_V02
        cout << "INFO: RUNNING IN CN_VERSION_V02 MODE " << endl;
    #elif CN_VERSION_V04
        cout << "INFO: RUNNING IN CN_VERSION_V04 MODE " << endl;
    #elif CN_VERSION_V06
        cout << "INFO: RUNNING IN CN_VERSION_V06 MODE " << endl;
    #else
        cout << " Common Ntuple version is not set or not supported." << endl;
        cout << " Please use CN_VERSION_V02, CN_VERSION_V04 or CN_VERSION_V06 as the value of CN_VERSION variable in the Makefile.\n";
        cout << " Terminating, sorry." << endl;
        abort();
    #endif
    instance->Loop(reject_cb_from_ari);

    // print number of events per run, needed for the DATA  luminosity calculation
    instance -> PrintEventsPerRun();

    // for debugging purposes
    #ifdef CN_VERSION_V04
        cout << "INFO: Total number of two-track vertices: " << TVertex::two_track_vertices_total << endl;
        cout << "INFO: Fraction of two-track vertices that were dropped from the fit ";
        cout << ((double)TVertex::two_track_vertices_dropped)/TVertex::two_track_vertices_total << endl;
    #endif

    // successfully finished
    return 0;
}
