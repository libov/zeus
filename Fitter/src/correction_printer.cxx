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

void print(TCrossSection * instance1, TCrossSection * instance2, unsigned bin1, unsigned bin2, flavour f, TString variable);

// my includes
int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"file1", required_argument, 0, 1},
        {"file2", required_argument, 0, 2}
    };

    // results of the command line option processing will be stored here
    TString binningXMLfileName1;
    TString binningXMLfileName2;

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                binningXMLfileName1 = optarg;
                break;
            case 2:
                binningXMLfileName2 = optarg;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "\tresult_printer --file1 <xmlfile 1> --file2 <xmlfile 2> [-h]\n\n";
                cout << "\tOptions:\n";
                cout << "\t-h\tPrint this help and exit\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // create a TCrossSection object that keeps the fit results (cross sections)
    TCrossSection instance1(binningXMLfileName1);
    TCrossSection instance2(binningXMLfileName2);

    // open the text file to store the results
    TString PLOTS_PATH=getenv("PLOTS_PATH");
    output.open(PLOTS_PATH + "/" + binningXMLfileName1 + "__vs__" + binningXMLfileName2 + ".DIFFERENCE");

    if (binningXMLfileName1.Contains("full.forCHARM")) {

        print(&instance1, &instance2, 2, 12, kCharm, "Eta");
        print(&instance1, &instance2, 14, 20, kCharm, "Et");
        print(&instance1, &instance2, 31, 36, kCharm, "xda");
        print(&instance1, &instance2, 38, 45, kCharm, "q2da");
        print(&instance1, &instance2, 46, 49, kCharm, "x_q2bin1");
        print(&instance1, &instance2, 50, 54, kCharm, "x_q2bin2");
        print(&instance1, &instance2, 55, 58, kCharm, "x_q2bin3");
        print(&instance1, &instance2, 59, 61, kCharm, "x_q2bin4");
        print(&instance1, &instance2, 62, 63, kCharm, "x_q2bin5");

    } else {

        print(&instance1, &instance2, 2, 11, kBeauty, "Eta");
        print(&instance1, &instance2, 13, 19, kBeauty, "Et");
        print(&instance1, &instance2, 30, 35, kBeauty, "xda");
        print(&instance1, &instance2, 37, 44, kBeauty, "q2da");
        print(&instance1, &instance2, 45, 48, kBeauty, "x_q2bin1");
        print(&instance1, &instance2, 49, 53, kBeauty, "x_q2bin2");
        print(&instance1, &instance2, 54, 57, kBeauty, "x_q2bin3");
        print(&instance1, &instance2, 58, 60, kBeauty, "x_q2bin4");
        print(&instance1, &instance2, 61, 62, kBeauty, "x_q2bin5");
    }

    // finished successfully
    return 0;
}

// prints cross-section results
void print(TCrossSection * instance1, TCrossSection * instance2, unsigned bin1, unsigned bin2, flavour f, TString variable) {

    TString flavour;
    if (f==kCharm) flavour = "Charm";
    if (f==kBeauty) flavour = "Beauty";

    output << "\n" << flavour << " relative difference in differential cross sections d sigma / dY in bins of " << variable << endl;

    unsigned counter = 1;

    for (int i=bin1; i<=bin2; i++) {
        TCrossSectionBin bin1 = instance1 -> getCrossSectionBin(i);
        TCrossSectionBin bin2 = instance2 -> getCrossSectionBin(i);
        Float_t sigma_diff_rel;
        if (f==kCharm) {
            Float_t sigma1 = bin1.get_sigma_c();
            Float_t sigma2 = bin2.get_sigma_c();
            sigma_diff_rel = (sigma2-sigma1)/sigma1;
        } else if (f==kBeauty) {
            Float_t sigma1 = bin1.get_sigma_b();
            Float_t sigma2 = bin2.get_sigma_b();
            sigma_diff_rel = (sigma2-sigma1)/sigma1;
        }
        if (sigma_diff_rel>0) output << "Bin " << counter << ": +" << sigma_diff_rel << endl;
        else output << "Bin " << counter << ": " << sigma_diff_rel << endl;
        counter++;
    }
}

