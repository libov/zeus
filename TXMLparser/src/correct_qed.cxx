// system headers
#include <iostream>
#include <fstream>
#include <getopt.h>
using namespace std;

// ROOT headers
#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>

// custom headers
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

int main(int argc, char **argv) {

    // declare long options
    static struct option long_options[] = {
        {"XMLfile", required_argument, 0, 1},
        {"beauty", no_argument, 0, 2},
    };

    TString XMLfile="";
    bool    beauty = false;

    // handle command line options
    opterr = 0;
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                XMLfile = optarg;
                break;
            case 2:
                beauty = true;
                break;
            case  'h':
                cout<<"usage:\n\t ./correct_qed --XMLfile <XML file> [--beauty] [options]\n"<<endl;
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

    // get measured double-differential cross-sections and uncertainties
    TCrossSection cCrossSection(XMLfile);

    // number  of bins in the XML cross-section file
    const unsigned  N_BINS = cCrossSection.getNBins();
    cout << "INFO: N_BINS = " << N_BINS << endl;

    // read values of hadronization and QED corrections
    TString DATABASE_PATH=getenv("DATABASE_PATH");
    TString filename;
    if (beauty) {
        filename = DATABASE_PATH+"/hadr_qed_corr_beauty.txt";
    } else {
        filename = DATABASE_PATH+"/hadr_qed_corr_charm.txt";
    }
    ifstream hadr(filename);
    if (!hadr.is_open()) {
        cout << "ERROR: Unable to open file " << filename; 
        abort();
    }
    cout << "INFO: opened " << filename << endl;

    // an array to store corrections
    Float_t qed_corr[N_BINS+1];
    // initialize with zeros
    for (int i=0; i<(N_BINS+1); i++) {
        qed_corr[i] = 0;
    }

    // a string for file operations
    string line;
    while ( hadr.good() ) {
        // read each line
        getline (hadr,line);
        TString line_str = line;

        // tokenize it, skip if empty
        TObjArray * tokens = line_str.Tokenize("\t");
        if (tokens -> IsEmpty()) continue;

        // get the id of the bin (is assumed to match those of the XML binning file)
        TString bin_id = ((TObjString*) tokens->At(0)) -> GetString();
        TString hadr_correction =  ((TObjString*) tokens->At(1)) -> GetString();
        TString qed_correction =  ((TObjString*) tokens->At(2)) -> GetString();

        // store to the array
        qed_corr[bin_id.Atoi()] = qed_correction.Atof();
    }

    // now correct the cross sections
    for (unsigned i = 1; i<=N_BINS; i++) {
        // get a bin
        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(i);

        // get values of cross-sections
        Float_t sigma;
        Float_t sigma_err;

        if (beauty) {
            sigma = cBin.get_sigma_b();
            sigma_err = cBin.get_sigma_b_err();
        } else {
            sigma = cBin.get_sigma_c();
            sigma_err = cBin.get_sigma_c_err();
        }

        if (qed_corr[i] != 0) {
            sigma /= qed_corr[i];
            sigma_err /= qed_corr[i];
        } else {
            sigma = 0;
            sigma_err = 0;
        }

        if (beauty) {
            cBin.set_sigma_b(sigma);
            cBin.set_sigma_b_err(sigma_err);
        } else {
            cBin.set_sigma_c(sigma);
            cBin.set_sigma_c_err(sigma_err);
        }

        cCrossSection.modifyCrossSectionBin(i, cBin);
    }

    XMLfile += ".QED_corrected";
    cCrossSection.WriteXMLfile(XMLfile);

    return 0;
}
