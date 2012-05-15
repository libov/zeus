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
#include <fstream>
#include <getopt.h>
using namespace std;

// my headers
#include <TResultPlotter.h>
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

enum flavour {
  kCharm,
  kBeauty
};

ofstream output;

void print(TCrossSection * instance, unsigned bin1, unsigned bin2, flavour f, TString variable);

// my includes
int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"file", required_argument, 0, 1}
    };

    // results of the command line option processing will be stored here
    TString binningXMLfileName;
    bool plot_beauty = false;    // default: plot charm

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                binningXMLfileName = optarg;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "\tresult_printer --file <xmlfile> [-h]\n\n";
                cout << "\tOptions:\n";
                cout << "\t-h\tPrint this help and exit\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // create a TCrossSection object that keeps the fit results (cross sections)
    TCrossSection instance(binningXMLfileName);

    // open the text file to store the results
    TString PLOTS_PATH=getenv("PLOTS_PATH");
    output.open(PLOTS_PATH+"/"+binningXMLfileName+".RESULTS");

    if (binningXMLfileName.Contains("full.forCHARM")) {

        print(&instance, 2, 12, kCharm, "Eta");
        print(&instance, 14, 20, kCharm, "Et");
        print(&instance, 31, 36, kCharm, "xda");
        print(&instance, 38, 45, kCharm, "q2da");
        print(&instance, 46, 49, kCharm, "x_q2bin1");
        print(&instance, 50, 54, kCharm, "x_q2bin2");
        print(&instance, 55, 58, kCharm, "x_q2bin3");
        print(&instance, 59, 61, kCharm, "x_q2bin4");
        print(&instance, 62, 63, kCharm, "x_q2bin5");

    } else {

        print(&instance, 2, 11, kBeauty, "Eta");
        print(&instance, 13, 19, kBeauty, "Et");
        print(&instance, 30, 35, kBeauty, "xda");
        print(&instance, 37, 44, kBeauty, "q2da");
        print(&instance, 45, 48, kBeauty, "x_q2bin1");
        print(&instance, 49, 53, kBeauty, "x_q2bin2");
        print(&instance, 54, 57, kBeauty, "x_q2bin3");
        print(&instance, 58, 60, kBeauty, "x_q2bin4");
        print(&instance, 61, 62, kBeauty, "x_q2bin5");
    }

    // finished successfully
    return 0;
}

// prints cross-section results
void print(TCrossSection * instance, unsigned bin1, unsigned bin2, flavour f, TString variable) {

    TString flavour;
    if (f==kCharm) flavour = "Charm";
    if (f==kBeauty) flavour = "Beauty";

    output << "\n" << flavour << " differential cross sections d sigma / dY in bins of " << variable << endl;

    unsigned counter = 1;

    for (int i=bin1; i<=bin2; i++) {
        TCrossSectionBin bin = instance -> getCrossSectionBin(i);
        Float_t sigma, sigma_err, sigma_rel_err;
        if (f==kCharm) {
            sigma = bin.get_sigma_c();
            sigma_err = bin.get_sigma_c_err();
            sigma_rel_err = 100 * sigma_err / sigma;
        } else if (f==kBeauty) {
            sigma = bin.get_sigma_b();
            sigma_err = bin.get_sigma_b_err();
            sigma_rel_err = 100 * sigma_err / sigma;
        }
        output << "Bin " << counter << ": " << sigma << " +/- " << sigma_err << " ("<<sigma_rel_err<<"%)" << endl;
        counter++;
    }
}

