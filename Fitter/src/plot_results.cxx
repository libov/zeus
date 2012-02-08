//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav,                            //
//  DESY,                                       //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

// system headers
#include <iostream>
#include <getopt.h>
using namespace std;

// my headers
#include <TResultPlotter.h>
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

// my includes
int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"file1", required_argument, 0, 1},
        {"file2", required_argument, 0, 2},
    };

    // results of the command line option processing will be stored here
    TString binningXMLfileName1;
    TString binningXMLfileName2;
    bool plot_beauty = false;    // default: plot charm

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "bh", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                binningXMLfileName1 = optarg;
                break;
            case 2:
                binningXMLfileName2 = optarg;
                break;
            case 'b':
                plot_beauty = true;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "\tplot_results --file1 <xmlfile1> --file2 <xmlfile1> [-b] [-h]\n\n";
                cout << "\tOptions:\n";
                cout << "\t-b\tPlot beauty results; otherwise - charm\n";
                cout << "\t-h\tPrint this help and exit\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // create TResultPlotter
    TResultPlotter  cResultPlotter;

    // select whether plot beauty or charm (SHOULD BE DONE BEFORE AddXMLFile)
    cResultPlotter.SetPlotCharm(true);
    if (plot_beauty) cResultPlotter.SetPlotCharm(false);

    // false: plot cross-sections; true: plot scaling factors
    cResultPlotter.SetPlotScalingFactors(false);

    // add XML files, where results to be displayed are
    cResultPlotter.AddXMLFile(binningXMLfileName1);
    cResultPlotter.AddXMLFile(binningXMLfileName2);

    // choose layout of the canvas
    cResultPlotter.Divide(2, 2);
    cResultPlotter.SetLogY(2);

    // do the histogramming
    // 1st subpad, linear scale
    cResultPlotter.DrawPlots(binningXMLfileName1, true, 1, false, 2);
    cResultPlotter.DrawPlots(binningXMLfileName2, false, 1, true, 1);

    // 2nd subpad, log scale
    cResultPlotter.DrawPlots(binningXMLfileName1, false, 2, false, 2);
    cResultPlotter.DrawPlots(binningXMLfileName2, false, 2, true, 1);

    // 3rd subpad, ratio plots
    cResultPlotter.DrawPlots(binningXMLfileName2, binningXMLfileName1, false, 3, false);

    // save results
    cResultPlotter.PrintCanvases();

    // finished successfully
    return 0;
}
