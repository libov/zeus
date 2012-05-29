// system includes
#include <getopt.h>
#include <iostream>
#include <fstream>
using namespace std;

// custom includes
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

// ROOT includes
#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>

int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"input_file", required_argument, 0, 1},
        {"cross_sections", no_argument, 0, 2},
        {"systematics", no_argument, 0, 3},
        {"XMLfile", required_argument, 0, 4},
        {"beauty", no_argument, 0, 5}
    };

    // results of the command line option processing will be stored here
    TString input_file="";
    bool    cross_sections = false;
    bool    systematics = false;
    TString XMLfile="";
    bool    beauty = false;

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                input_file = optarg;
                break;
            case 2:
                cross_sections = true;
                break;
            case 3:
                systematics = true;
                break;
            case 4:
                XMLfile = optarg;
                break;
            case 5:
                beauty = true;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "./txt2XML --input_file <full path> [--cross_sections] [--systematics --XMLfile <XML file> [--beauty]]  [-h]\n\n";
                cout << "\n\nThe program can be run in two modes selected by the following options: \n";
                cout << "\n--cross_sections - cross-sections from the txt file (if given in the right format) will be converted to standard XML cross-section file (a new one will be created)\n";
                cout << "\n--systematics - systematics from the txt file (if given in the right format) will be written to an existing XML cross-section file; the filename has to\n";
                cout << "\nbe provided with the --XMLfile\n";
                cout << "\nExamples of txt file in the right format are given here: http://www-zeus.desy.de/~libov/F2cb_vtx_paper_May2012/\n";
                cout << "\n-h - Show this help\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // check if options are ok
    if ( cross_sections && systematics ) {
        cout << "ERROR: options --cross_sections and --systematics cannot be selected simultaneously!" << endl;
        abort();
    }

    if ( ! (cross_sections || systematics) ) {
        cout << "ERROR: one of the options --cross_sections or --systematics has to be selected!" << endl;
        abort();
    }

    if ( input_file == "" ) {
        cout << "ERROR: --input_file with an argument have to be provided!" << endl;
        abort();
    }

    if ( systematics && (XMLfile=="") ) {
        cout << "ERROR: --XMLfile with an argument have to be provided if using --systematics mode!" << endl;
        abort();
    }

    if (systematics) {

        // open the file with cross-sections
        TCrossSection cCrossSection(XMLfile);

        // this string appears before new differential cross-section starts
        TString new_xsect_prefix;
        if (beauty) {
            new_xsect_prefix = "Beauty systematics in differential cross sections d sigma / dY in bins of";
        } else {
            new_xsect_prefix = "Charm systematics in differential cross sections d sigma / dY in bins of";
        }

        // open input file with the systematics
        ifstream f(input_file);
        if (!f.is_open()) {
            cout << "ERROR: could not open " << input_file << endl;    
            abort();
        }
        cout << "INFO: opened " << input_file << " for reading" << endl;

        // counts bins in the XML file
        unsigned bin = 1;
        // loop over lines in the input file
        string line;
        while ( f.good() ) {

            // get a line
            getline (f,line);
            TString line_str = line;

            // tokenize it, skip if empty
            TObjArray * tokens = line_str.Tokenize(" ");
            if (tokens -> IsEmpty()) continue;

            // if the line containts a prefix, a new differential cross-section appears
            if ( line_str.Contains(new_xsect_prefix)) {
                TString last = ((TObjString*)tokens->Last()) -> GetString();
                // this is to skip phi distribution
                if (last == "xda") bin+=10;
                // this is to take into account that before any cross-section, an inclusive bin exists, except for double differential cross-sections
                else if (!last.Contains("x_q2bin")) bin++;
                continue;
            }

            // First word has to be "Bin", in that case this line corresponds to the systematics in the bin
            TString token0 = ((TObjString*) tokens->At(0)) -> GetString();
            if (token0 != "Bin") continue;

            // these words correspond to up and down systematics
            TString syst_up = ((TObjString*) tokens->At(2)) -> GetString();
            TString syst_down = ((TObjString*) tokens->At(3)) -> GetString();

            // get the cross-section bin from the given XML file
            TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(bin);
            if (!beauty) {
                Float_t sigma_c = cBin.get_sigma_c();
                cBin.set_sigma_c_err_syst_up(syst_up.Atof()*sigma_c);
                cBin.set_sigma_c_err_syst_down(TMath::Abs(syst_down.Atof())*sigma_c);
            }
            if (beauty) {
                Float_t sigma_b = cBin.get_sigma_b();
                cBin.set_sigma_b_err_syst_up(syst_up.Atof()*sigma_b);
                cBin.set_sigma_b_err_syst_down(TMath::Abs(syst_down.Atof())*sigma_b);
            }

            // write the bin object with the new info to CrossSection object
            cCrossSection.modifyCrossSectionBin(bin, cBin);
            bin++;
        }
        f.close();

        XMLfile += ".SYST";
        cCrossSection.WriteXMLfile(XMLfile);
    }

    if (cross_sections) {
        cout << "ERROR: not implemented yet, sorry" << endl;
        abort();
    }

    return 0;
}
