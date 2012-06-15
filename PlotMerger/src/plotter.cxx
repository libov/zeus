
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

    // declare long options
    static struct option long_options[] = {
        {"no_beauty_resolved", no_argument, 0, 1},
        {"no_charm_resolved", no_argument, 0, 2},
        {"config_file", required_argument, 0, 3}
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
            case 'h':
                cout<<"\nUsage:\n\t plotter -b <Binning File Suffix> -v <Histograms Version Ending> --config_file <config file> [Options]\n"<<endl;
                cout<<"\t List of Options:"<<endl;
                cout<<"\n\t\t-d include direct"<<endl;
                cout<<"\t\t-e include resolved"<<endl;
                cout<<"\t\t-no_beauty_resolved do not include beauty resolved, use with -e"<<endl;
                cout<<"\t\t-no_charm_resolved do not include charm resolved, use with -e"<<endl;
                cout<<"\t\t-r remark (special suffix in the histogram version; default: .0405e06e07p - as in merger and fitter!)"<<endl;
                cout<<"\t\t-s apply scaling factors from the fit"<<endl;
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

    // specify what has to be plotted;
    // plots will appear in the same order they are added via AddPlotType
    // first agrument comes from TPlotMerger.cxx (?)
    // (REMINDER: TControlPlot::AddPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Int_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth))
    myPlots->AddPlotType("mc", true, 0,0, kYellow, kBlack, 1);
    myPlots->AddPlotType("light", true, 0, 0, 0, kRed, 2);
    if (include_direct) {
        myPlots->AddPlotType("beauty", true, 0, 0, 0, kBlue, 2);
        myPlots->AddPlotType("charm", true, 0, 0, 0, kGreen, 2);
    }
    if (include_resolved) {
        if (!no_beauty_resolved) myPlots->AddPlotType("beauty_resolved", true, 0, 0, 0, kBlue, 5);
        if (!no_charm_resolved) myPlots->AddPlotType("charm_resolved", true, 0, 0, 0, kGreen, 5);
    }
    myPlots->AddPlotType("data", false, 20, 0.5, 0, 1, 0);

    // set config file to select plots
    myPlots -> SetConfigFile(config_file);

    // select which figure type
    myPlots -> SetPrintEPS(true);

    // initialize
    myPlots -> Initialize();

    // perform drawing and store to file
    myPlots->Draw();

    // finished successfully
    return 0;
}
