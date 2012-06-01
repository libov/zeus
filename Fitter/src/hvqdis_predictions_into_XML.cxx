//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  April 2012                                  //
//                                              //
//////////////////////////////////////////////////

// ROOT includes
#include <TString.h>
#include <TObjString.h>
#include <TH1F.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TMath.h>

// system  includes
#include <fstream>
#include <iostream>
#include <getopt.h>
using namespace std;

// my includes
#include <TCrossSection.h>

int main(int argc, char **argv) {

    // some declarations
    TString     BinningFileSuffix;

    // declare long options
    static struct option long_options[] = {
        {"meta_file", required_argument, 0, 1}
    };

    TString meta_file = "";

    // handle command line options
    opterr = 0;
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "b:h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                meta_file = optarg;
                break;
            case 'b':
                BinningFileSuffix = optarg;
                break;
            case  'h':
                cout<<"usage:\n\t hvqdis_predictions_into_XML  -b <Binning File Suffix> --meta_file <filename prefix (without extension)> [options]\n"<<endl;
                cout << "List of options\n" << endl;
                cout << "-h\t\tprint this help"<<endl;
                exit(0);
                break;
            default:
                abort ();
        }
    }

    for (int index = optind; index < argc; index++) {
        printf ("WARNING: Non-option argument %s\n", argv[index]);
    }

    // read binning from the XML file
    TString binningXMLfileName = "binning."+BinningFileSuffix+".xml";
    // everything should be ok if this does not crash:
    TCrossSection   cCrossSection(binningXMLfileName);

    TString out_file_name = "hvqdis_predictions.xml";

    // write data to file
    cCrossSection.WriteXMLfile(out_file_name);

    // finished successfully
    return 0;
}
