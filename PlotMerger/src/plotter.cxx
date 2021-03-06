
#include <getopt.h>
#include <iostream>
using namespace std;

#include <TChain.h>
#include <TMath.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TSystem.h>

#include <inc/TControlPlot.h>
#include <inc/normtype.h>

int main (int argc, char **argv) {

    // some declarations
    TString     BinningFileSuffix;
    TString     HistogramsVersionEnding;
    TString     remark = "";
    TString     config_file="";
    Bool_t      use_scaling_factors = false;
    Bool_t      include_resolved = false;
    Bool_t      include_direct = false;
    Bool_t      no_beauty_resolved = false;
    Bool_t      no_charm_resolved = false;
    Bool_t      no_indices = false;
    Bool_t      only_png = false;
    Bool_t      print_root = false;
    TString     bin = "";

    // declare long options
    static struct option long_options[] = {
        {"no_beauty_resolved", no_argument, 0, 1},
        {"no_charm_resolved", no_argument, 0, 2},
        {"config_file", required_argument, 0, 3},
        {"no_indices", no_argument, 0, 4},
        {"only_png", no_argument, 0, 5},
        {"print_root", no_argument, 0, 6},
        {"bin", required_argument, 0, 7},
    };

    // handle command line options
    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    opterr = 0;
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "b:v:desr:h", long_options, &option_index)) != -1) {
        switch (option) {
            case 'b':
                BinningFileSuffix=optarg;
                break;
            case 'v':
                HistogramsVersionEnding=optarg;
                break;
            case 'd':
                include_direct = true;
                break;
            case 'e':
                include_resolved = true;
                break;
            case 's':
                use_scaling_factors = true;
                break;
            case 'r':
                remark = (TString)optarg;
                break;
            case 1:
                no_beauty_resolved = true;
                break;
            case 2:
                no_charm_resolved = true;
                break;
            case 3:
                config_file = optarg;
                break;
            case 4:
                no_indices = true;
                break;
            case 5:
                only_png = true;
                break;
            case 6:
                print_root = true;
                break;
            case 7:
                bin = optarg;
                break;
            case 'h':
                cout<<"\nUsage:\n\t plotter -b <Binning File Suffix> -v <Histograms Version Ending> --config_file <config file> [--bin <bin number>] [Options]\n"<<endl;
                cout<<"\t List of Options:"<<endl;
                cout<<"\n\t\t-d include direct"<<endl;
                cout<<"\t\t-e include resolved"<<endl;
                cout<<"\t\t-no_beauty_resolved do not include beauty resolved, use with -e"<<endl;
                cout<<"\t\t-no_charm_resolved do not include charm resolved, use with -e"<<endl;
                cout<<"\t\t-r remark (special suffix in the histogram version; default: .0405e06e07p - as in merger and fitter!)"<<endl;
                cout<<"\t\t-s apply scaling factors from the fit"<<endl;
                cout<<"\t\t--no_indices for axes titles, don't display _{da}, _{jb} or _{el} indices for kinematic variables"<<endl;
                cout<<"\t\t--only_png print only png files; otherwise - eps"<<endl;
                cout<<"\t\t--print_root print also root files; otherwise - eps"<<endl;
                cout<<"\t\t-h Show this help and exit\n"<<endl;
                exit(-1);
            default:
                abort ();
        }
    }

    for (int index = optind; index < argc; index++) {
        printf ("WARNING: Non-option argument %s\n", argv[index]);
    }

    // welcome message
    cout<<"******************************************************"<<endl;
    cout<<"* Welcome to ZEUS Common Ntuple analysis framework   *"<<endl;
    cout<<"* Step 4: Visualizing the data                       *"<<endl;
    cout<<"* Input: root files with merged histograms           *"<<endl;
    cout<<"******************************************************"<<endl;

    // construct files suffix as binning file suffix concatenated with version of histograms
    TString     HistogramsVersion = BinningFileSuffix + HistogramsVersionEnding;
    cout << "INFO: Histograms Version: " << HistogramsVersion << endl;

    // by default, process all periods
    if (remark == "") remark = ".0405e06e07p";
    // in case selected to add resolved, but no charm and beauty - switch off including resolved,
    // i.e. no_beauty_resolved and no_charm_resolved options override include_resolved
    if (no_beauty_resolved && no_charm_resolved) include_resolved = false;
    if (include_resolved) {
        remark += ".including_resolved";
        if (no_beauty_resolved) remark += ".no_beauty_resolved";
        if (no_charm_resolved) remark += ".no_charm_resolved";
    }

    // get the CN version from the environment
    TString CN_VERSION=getenv("CN_VERSION");

    // extend remark if selected plots with application of scaling factors
    if (use_scaling_factors) remark += ".scaled";

    // print info
    cout << "INFO: remark " << remark << endl;

    // get final suffix
    HistogramsVersion += remark;

    // create an instance of TControlPlot
    TControlPlot *myPlots=new TControlPlot(HistogramsVersion);

    // set config file to select plots
    myPlots -> SetConfigFile(config_file);

    // select which figure type
    if (only_png) {
        myPlots -> SetPrintPNG(true);
    } else {
        myPlots -> SetPrintEPS(true);
    }
    if (print_root) myPlots -> SetPrintROOT(true);

    // switch off indices if selected
    if (no_indices) myPlots -> SetNoIndices(true);

    // set binning
    if ( bin != "" ) myPlots -> SetBin("bin"+bin);

    // initialize
    myPlots -> Initialize();

    // perform drawing and store to file
    myPlots->Draw();

    // finished successfully
    return 0;
}
