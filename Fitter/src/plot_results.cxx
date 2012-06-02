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
    bool    first_file_given = false;
    bool    second_file_given = false;
    bool    plot_beauty = false;    // default: plot charm

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "bh", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                binningXMLfileName1 = optarg;
                first_file_given = true;
                break;
            case 2:
                binningXMLfileName2 = optarg;
                second_file_given = true;
                break;
            case 'b':
                plot_beauty = true;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "\tplot_results --file1 <xmlfile1> [--file2 <xmlfile1>] [-b] [-h]\n\n";
                cout << "\t This application is designed to visualize cross-sections that are stored in XML files.\n";
                cout << "\t If two files are given (i.e. both options --file1 and --file2 are specified), a ratio plot will be shown below the main graph.\n";
                cout << "\t The functionality of the underlying class TResultPlotter allows any canvas layout and any number of XML files, but that is not implemented in this application.\n";
                cout << "\t Data-to-theory comparisons are also possible. Please keep \"predictions\" keyword in the name of an XML file containting theory cross-sections, so that it";
                cout << " can be recognized.\n";
                cout << "\n\tConventions:\n";
                cout << "\t-> data-to-data comparisons: 1st file is new, 2nd file is old\n";
                cout << "\t-> data-to-theory comparisons: 1st file is data, 2nd file is theory\n";
                cout << "\t-> ratio plot always shows 1st divided by 2nd, which makes sense for both of the two conventions above\n";
                cout << "\t-> 1st-file-plot will appear on top of the 2nd, which makes sense for the data-to-theory convention\n";
                cout << "\n\tOptions:\n";
                cout << "\t-b\tPlot beauty results; otherwise - charm\n";
                cout << "\t-h\tPrint this help and exit\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // sanity checks
    if ( (!first_file_given) && (!second_file_given) ) {
        cout << "ERROR: at least one XML file should be given" << endl;
        abort();
    }

    if (first_file_given && binningXMLfileName1.Contains("predictions")) {
        cout << "ERROR: according to convention, theory cross-sections can't be given as the first file" << endl;
        abort();
    }

    // create TResultPlotter
    TResultPlotter  cResultPlotter;

    // select whether plot beauty or charm (SHOULD BE DONE BEFORE AddXMLFile)
    if (plot_beauty) {
        cResultPlotter.SetPlotCharm(false);
    } else {
        cResultPlotter.SetPlotCharm(true);
    }

    // false: plot cross-sections; true: plot scaling factors
    cResultPlotter.SetPlotScalingFactors(false);

    // the layout of the canvas depending on the number of XML files as stated in the help
    if (first_file_given && second_file_given) {
        cResultPlotter.Divide(1, 2);
    } else {
        cResultPlotter.Divide(1, 1);
    }

    // set the configuration file
    if (plot_beauty) {
        cResultPlotter.SetConfigFile("F2bc_paper_beauty");
    } else {
        cResultPlotter.SetConfigFile("F2bc_paper_charm");
    }

    // initialize
    cResultPlotter.Initialize();

    // add XML files, where results to be displayed are
    if (first_file_given) cResultPlotter.AddXMLFile(binningXMLfileName1);
    if (second_file_given) cResultPlotter.AddXMLFile(binningXMLfileName2);

    // draw plots; file1 should be on top of the file2, hence draw file2 first
    if (second_file_given) cResultPlotter.DrawPlots(binningXMLfileName2, 1, false, 2);
    if (first_file_given) cResultPlotter.DrawPlots(binningXMLfileName1, 1, true, 1);

    // the ratio plot
    if (first_file_given && second_file_given) cResultPlotter.DrawRatio(binningXMLfileName1, binningXMLfileName2, 2, false);

    // save results
    cResultPlotter.PrintCanvases();

    // finished successfully
    return 0;
}
