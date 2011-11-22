
//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  March 2011                                  //
//                                              //
//////////////////////////////////////////////////

// system includes
#include <iostream>
#include <fstream>
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
#include<TDataset.h>

// function declarations
TString     int_to_TString (int i);
TString     float_to_TString (float f);
void        submitJob(TString run_command, TString samplename);

// global constant specifying type of queue
TString ZARAH_QUEUE = "M";
// global switch: true = select only SL4 (kept for backward compatibility); false = don't select specific resources from ZARAH
bool    SELECT_SL4 = false;

// main function
int main(int argc, char **argv) {

    // handle command-line arguments

    // a suffix of a file with binning
    TString     BinningFileSuffix;

    // version of the histograms
    TString     HistogramsVersionEnding;

    // helping boolean variables to make sure all the arguments were passed correctly 
    bool        binning_file_suffix_set = false;
    bool        histogram_version_ending_set = false;
    bool        recalulate_luminosity_only = false;
    // for jet energy scale uncertainty studies
    bool        vary_jet_energy_scale = false;
    Float_t     jet_energy_scale_variation = 0;
    // create minintuples?
    bool        create_minintuples = false;
    // run locally?
    bool        run_locally = false;
    // run over only mc samples?
    bool        run_mc_only = false;
    bool        run_resolved_only = false;
    bool        run_direct_only = false;
    bool        run_data_only = false;
    // a switch to select only filelist creation
    bool        filelist_only = false;
    

    // for significance smearing
    Float_t    SmearingGauss1Prob = -1;
    Float_t    SmearingGauss1Width = -1;
    Float_t    SmearingGauss2Prob = -1;
    Float_t    SmearingGauss2Width = -1;
    Float_t    SmearingExpProb = -1;
    Float_t    SmearingExpCoeff = -1;

    // declare long options
    static struct option long_options[] = {
        {"gaus1prob", required_argument, 0, 1},
        {"gaus1width", required_argument, 0, 2},
        {"gaus2prob", required_argument, 0, 3},
        {"gaus2width", required_argument, 0, 4},
        {"expprob", required_argument, 0, 5},
        {"expcoeff", required_argument, 0, 6},
        {"filelist_only", no_argument, 0, 7},
        {"run_data_only", no_argument, 0, 8}
    };

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "b:v:rhj:mlced", long_options, &option_index)) != -1) {
        switch (option) {
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
            case 'j':
                vary_jet_energy_scale = true;
                jet_energy_scale_variation = atof(optarg);
                break;
            case 'm':
                create_minintuples = true;
                break;
            case 'l':
                run_locally = true;
                break;
            case 'c':
                run_mc_only = true;
                break;
            case 8:
                run_data_only = true;
                break;
            case 'e':
                run_resolved_only = true;
                break;
            case 'd':
                run_direct_only = true;
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
                filelist_only = true;
                break;
            case 'h':
                cout<<"\nUsage: " << endl;
                cout<<"\t submit_analysis  -b <Binning File Suffix> -v <Histograms Version Ending> [OPTIONS]"<<endl;
                cout<<"\nAdditional options: " << endl;
                cout << "\t-r\t\trecalculate luminosity, don't run full analysis\n";
                cout << "\t-j\t\tjet energy scale studies: scale calorimetric part of the jet\n\t\t\tenergy by the value given with this option\n";
                cout << "\t--gaus1prob\tfraction of events smeared by 1st gaussian\n";
                cout << "\t--gaus1width\twidth of the 1st gaussian\n";
                cout << "\t--gaus2prob\tfraction of events smeared by 2nd gaussian\n";
                cout << "\t--gaus2width\twidth of the 2nd gaussian\n";
                cout << "\t--expprob\tfraction of events smeared by the exponent\n";
                cout << "\t--expcoeff\tcoefficient for the exponential smearing\n";
                cout << "\t-m\t\tcreate mini ntuples\n";
                cout << "\t-l\t\trun locally, don't submit to ZARAH\n";
                cout << "\t-c\t\trun only for Monte-Carlo\n";
                cout << "\t--run_data_only\trun only for Data\n";
                cout << "\t-e\t\trun only for resolved MC (excitation)\n";
                cout << "\t-d\t\trun only for direct MC (don't run resolved)\n";
                cout << "\t--filelist_only\tCreate filelists, don't run analysis\n";
                cout << "\t-h\t\tPrint this help\n\n";
                exit(-1);
            default:
                cout << "Unknown opiton or missing option argument. The program will terminate, sorry." << endl;
                exit(-1);
        }
    }

    // TODO: add sanity check of parameters!
    if ( (!(binning_file_suffix_set && histogram_version_ending_set)) && (!create_minintuples) ) {
        cout << "\nIncorrect use of " << argv[0] << endl;
        cout << "\nPlease use\n" << endl;
        cout << "\t"<<argv[0] << " -h\n" << endl;
        cout << "to get more information\n" << endl;
        exit(-1);
    }

    // ok, the necessary number of arguments was provided, the program can continue
    
    // first, open the XML file containing information about the samples
    TString   XMLfilename;
    #ifdef CN_VERSION_V02
        XMLfilename = "samples.v02.xml";
    #elif CN_VERSION_V04
        XMLfilename = "samples.v04.xml";
    #elif CN_VERSION_V06
        XMLfilename = "samples.v06.xml";
    #else
        cout << " Common Ntuple version is not set or not supported." << endl;
        cout << " Please define use -DCN_VERSION_V02 or -DCN_VERSION_V04 as an argument for g++ depending on your CN version.\n";
        cout << " Terminating, sorry." << endl;
        abort();
    #endif

    // open the XML file and create TDataset structure from it
    TDataset cDataset(XMLfilename);

    // create a tarball
    TString ANALYSIS=getenv("ANALYSIS");
    TString     cd_command;
    cd_command = "cd " + ANALYSIS;
    chdir(ANALYSIS);
    system("rm -f NtupleAnalyzer.tar.gz");
    system("tar -zcf NtupleAnalyzer.tar.gz NtupleAnalyzer");
    chdir(getenv("NTUPLEANALYZER"));
    
    // loop over samples and submit each for analysis
    for (unsigned i = 0; i < cDataset.getNSamples(); i++) {

        TSubSet cSubSet  = cDataset.getSubSet_byIndex(i);

        cSubSet.Print();

        // create a filelist; this is an alternative to using stuff from cninfo - seems to be more automatized,
        // but on the other hand cninfo IS safer: in some cases there might be more files satisfying name pattern
        // criteria, of which not all should be used for analysis! in this case cninfo is THE ONLY option
        // (e.g. v02 cc 1.5 0607p) here it is done to test resolved sample stuff - there we had no filelist
        TString     create_filelist_command = "sh create-NtupleList.sh " + cSubSet.getYear() + " " + cSubSet.getCNversion() + " " + cSubSet.getType() + " " + cSubSet.getNamePattern();
        system(create_filelist_command.Data());
        if (filelist_only) continue;

        TString     type = int_to_TString((int)cSubSet.getTypeENUM());
        TString     flavour = int_to_TString((int)cSubSet.getFlavourENUM());
        TString     period = int_to_TString((int)cSubSet.getPeriodENUM());
        TString     q2 = int_to_TString((int)cSubSet.getQ2ENUM());
        TString     process = int_to_TString((int)cSubSet.getProcessENUM());
        TString     trigger_period = int_to_TString((int)cSubSet.getTriggerPeriod());

        TString     command;
        TString     program;
        if (create_minintuples) {
            program = "createMiniNtuples ";
        } else {
            program = "analysis ";
        }
 
        if (cSubSet.getTypeENUM() == TSubSet::kDATA) {
            command = program+" -t" + type + " -p" + period;
        } else if (cSubSet.getTypeENUM() == TSubSet::kMC) {
            command = program+" -t" + type + " -f" + flavour + " -p" + period + " -q" + q2 + " -o" + process + " -g" + trigger_period;
        } else {
            cout << "Sample is neither data nor MC. Terminating!" << endl;
            exit(-1);
        }
        if (!create_minintuples) command += " -b" + BinningFileSuffix + " -v" +HistogramsVersionEnding;
        if (vary_jet_energy_scale) {
            command += " -j \"" + float_to_TString(jet_energy_scale_variation) + "\"";
        }
        if (SmearingGauss1Prob != -1) command += " --gaus1prob " + float_to_TString(SmearingGauss1Prob);
        if (SmearingGauss1Width != -1) command += " --gaus1width " + float_to_TString(SmearingGauss1Width);
        if (SmearingGauss2Prob != -1) command += " --gaus2prob " + float_to_TString(SmearingGauss2Prob);
        if (SmearingGauss2Width != -1) command += " --gaus2width " + float_to_TString(SmearingGauss2Width);
        if (SmearingExpProb != -1) command += " --expprob " + float_to_TString(SmearingExpProb);
        if (SmearingExpCoeff != -1) command += " --expcoeff " + float_to_TString(SmearingExpCoeff);

        // if selected to recalculate luminosity only
        if (recalulate_luminosity_only) command += " -r";

        cout << "INFO: command to be executed: " << command << endl;

        // if this is not MC, but it was selected to run only on MC - skip the sample
        if (run_mc_only && (cSubSet.getTypeENUM() != TSubSet::kMC)) continue;
        if (run_resolved_only && (cSubSet.getTypeENUM()==TSubSet::kMC) && (cSubSet.getProcessENUM()!=TSubSet::kRESOLVED)) continue;
        if (run_direct_only && (cSubSet.getTypeENUM()==TSubSet::kMC) && (cSubSet.getProcessENUM()==TSubSet::kRESOLVED)) continue;

        // if only for data
        if (run_data_only && (cSubSet.getTypeENUM() != TSubSet::kDATA)) continue;

        // if selected to run locally, execute the command and skip to the next sample, don't submit
        if (run_locally) {
            system(command);
            continue;
        }

         // get sample name; it must be given as an argument to submitJob function,
         // just in order to pick up correct txt file containing list of files
         // one could avoid that in principle (e.g. by sending all txt files from the folder)
        cSubSet.defineSampleName();
        TString sample_name = cSubSet.getSampleName();

        // ok, submit the job to ZARAH
        cout << "SUBMITTING THIS SAMPLE TO ZARAH\n" << endl;
        submitJob(command, sample_name);
    }

    // clean up - remove the tarball
    TString rm_command = "rm " + ANALYSIS+"/NtupleAnalyzer.tar.gz";
    system(rm_command.Data());

    // successfully finished
    return 0;
}

// a simple function to convert integer to TString
TString int_to_TString (int i) {

    char  buf[256];

    sprintf(buf, "%d", (int)i );

    TString temp_TString(buf);

    return temp_TString;
}

// a simple function to convert integer to TString
TString float_to_TString (float f) {

    char  buf[256];

    sprintf(buf, "%f", f );

    TString temp_TString(buf);

    return temp_TString;
}


// a function to submmit a job: creates a script to be launched on ZARAH and submits it, together with needed files
void submitJob(TString run_command, TString samplename) {
        
    // remove old file
    remove("run_zarah.sh");

    // create a new file
    ofstream myfile;
    myfile.open ("run_zarah.sh");

    // add commands to be executed on ZARAH for each job
    myfile << "#!/bin/bash\n";
    myfile << "echo entered $0\n";
    myfile << "source ROOT.sh\n";
    myfile << "source env.sh\n";
    myfile << "echo PATH= $PATH\n";
    myfile << "tar -zxvf NtupleAnalyzer.tar.gz\n";
    myfile << "cd NtupleAnalyzer\n";
    myfile << "ln -s ../libxerces-c.so.27.0 libxerces-c.so\n";
    myfile << "make clean && make analysis && make createMiniNtuples\n";
    myfile << "mv analysis createMiniNtuples ../\n";
    myfile << "mv reweightingFunction/weightTables/* ../\n";
    myfile << "cd ../\n";
    myfile << "rm NtupleAnalyzer.tar.gz\n";
    myfile << "tar -zcvf NtupleAnalyzer.tar.gz NtupleAnalyzer\n";
    myfile << "rm -rf NtupleAnalyzer\n";
    myfile << "ln -s libxerces-c.so.27.0 libxerces-c.so.27\n";
    myfile << "echo content of the job spool:\n";
    myfile << "ls -l\n";
    myfile << "export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH\n";
    myfile << "echo $LD_LIBRARY_PATH\n";
    myfile << run_command;
    myfile.close();

    // change permission on the script file so that in can be executed on ZARAH
    system("chmod a+x run_zarah.sh");

    // construct dubmission command
    TString ANALYSIS = getenv("ANALYSIS");

    TString resources = "";
    if (SELECT_SL4) {
        resources = "-R \"defined(sl4)\"";
    }
    
    TString submit_command="zarah-jobsub -q "+ZARAH_QUEUE+" -s run_zarah.sh " + resources + " ../NtupleAnalyzer.tar.gz "+ANALYSIS+"/*.sh"+" ../xerces/$ZARCH_TYPE/lib* " + " filelists/"+samplename+".txt" ;
    cout << "INFO: submission command: " << submit_command << endl;
    system (submit_command.Data());

    // clean up
    remove("run_zarah.sh");
}
