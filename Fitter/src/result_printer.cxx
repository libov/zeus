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

#include<TMath.h>
#include <TObjString.h>
#include <TObjArray.h>

enum flavour {
  kCharm,
  kBeauty
};

ofstream output;
ofstream output_true;
ofstream output_tex;

void print(TCrossSection * instance, unsigned bin1, unsigned bin2, flavour f, TString variable, Float_t * hadr, Float_t * qed);

// my includes
int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"file", required_argument, 0, 1},
        {"beauty", no_argument, 0, 2},
        {"only_inclusive", no_argument, 0, 3},
    };

    // results of the command line option processing will be stored here
    TString binningXMLfileName;
    bool plot_beauty = false;    // default: plot charm
    bool only_inclusive = false;

    // loop over program arguments (i.e. argv array) and store info to above variables
    // depending on an option
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                binningXMLfileName = optarg;
                break;
            case 2:
                plot_beauty = true;
                break;
            case 3:
                only_inclusive = true;
                break;
            case 'h':
                cout << "\nUsage:\n\n";
                cout << "\tresult_printer --file <xmlfile> [--beauty] [--only_inclusive] [-h]\n\n";
                cout << "\tOptions:\n";
                cout << "\t--beauty:\tPrint beauty results\n\n";
                cout << "\t--only_inclusive:\tPrint the inclusive cross-sections and scaling factors\n\n";
                cout << "\t-h\tPrint this help and exit\n\n";
                exit(-1);
                break;
            default:
                abort ();
        }
    }

    // create a TCrossSection object that keeps the fit results (cross sections)
    TCrossSection instance(binningXMLfileName);

    // number  of bins in the XML cross-section file
    const unsigned  N_BINS = instance.getNBins();

    // read values of hadronization and QED corrections (Chad, Crad)
    TString DATABASE_PATH=getenv("DATABASE_PATH");
    TString filename;
    if (plot_beauty) {
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
    Float_t hadr_corr[N_BINS+1];
    Float_t qed_corr[N_BINS+1];
    // initialize with zeros
    for (int i=0; i<(N_BINS+1); i++) {
        hadr_corr[i] = 0;
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
        // store to the array
        hadr_corr[bin_id.Atoi()] =  (((TObjString*) tokens->At(1)) -> GetString()).Atof();
        qed_corr[bin_id.Atoi()] =  (((TObjString*) tokens->At(2)) -> GetString()).Atof();

    }

    // if --only_inclusive option was selected, print results for bin1 only and exit
    if (only_inclusive) {

        cout << "results for " << binningXMLfileName << ": " << endl;

        TCrossSectionBin bin = instance.getCrossSectionBin(1);

        cout << "sigma_c= " << bin.get_sigma_c() << " +- " << bin.get_sigma_c_err() << " ( " << 100*bin.get_sigma_c_err()/bin.get_sigma_c() << " % )"<<endl;
        cout << "sigma_b= " << bin.get_sigma_b() << " +- " << bin.get_sigma_b_err() << " ( " << 100*bin.get_sigma_b_err()/bin.get_sigma_b() << " % )"<<endl;

        cout << "k_c= " << bin.get_k_c() << " +- " << bin.get_k_c_err() << " ( " << 100*bin.get_k_c_err()/bin.get_k_c() << " % )"<<endl;
        cout << "k_b= " << bin.get_k_b() << " +- " << bin.get_k_b_err() << " ( " << 100*bin.get_k_b_err()/bin.get_k_b() << " % )"<<endl;
        cout << "k_uds= " << bin.get_k_uds() << " +- " << bin.get_k_uds_err() << " ( " << 100*bin.get_k_uds_err()/bin.get_k_uds() << " % )"<<endl;

        return 0;
    }

    // open the text file to store the results
    TString PLOTS_PATH=getenv("PLOTS_PATH");
    output.open(PLOTS_PATH+"/"+binningXMLfileName+".RESULTS");
    output_true.open(PLOTS_PATH+"/"+binningXMLfileName+".TRUE");
    output_tex.open(PLOTS_PATH+"/"+binningXMLfileName+".tex");

    if (!plot_beauty) {

        print(&instance, 2, 12, kCharm, "Eta", hadr_corr, qed_corr);
        print(&instance, 14, 20, kCharm, "Et", hadr_corr, qed_corr);
        print(&instance, 31, 36, kCharm, "xda", hadr_corr, qed_corr);
        print(&instance, 38, 45, kCharm, "q2da", hadr_corr, qed_corr);
        print(&instance, 46, 49, kCharm, "x_q2bin1", hadr_corr, qed_corr);
        print(&instance, 50, 54, kCharm, "x_q2bin2", hadr_corr, qed_corr);
        print(&instance, 55, 58, kCharm, "x_q2bin3", hadr_corr, qed_corr);
        print(&instance, 59, 61, kCharm, "x_q2bin4", hadr_corr, qed_corr);
        print(&instance, 62, 63, kCharm, "x_q2bin5", hadr_corr, qed_corr);

    } else {

        print(&instance, 2, 11, kBeauty, "Eta", hadr_corr, qed_corr);
        print(&instance, 13, 19, kBeauty, "Et", hadr_corr, qed_corr);
        print(&instance, 30, 35, kBeauty, "xda", hadr_corr, qed_corr);
        print(&instance, 37, 44, kBeauty, "q2da", hadr_corr, qed_corr);
        print(&instance, 45, 48, kBeauty, "x_q2bin1", hadr_corr, qed_corr);
        print(&instance, 49, 53, kBeauty, "x_q2bin2", hadr_corr, qed_corr);
        print(&instance, 54, 56, kBeauty, "x_q2bin3", hadr_corr, qed_corr);
        print(&instance, 58, 60, kBeauty, "x_q2bin4", hadr_corr, qed_corr);
        print(&instance, 61, 62, kBeauty, "x_q2bin5", hadr_corr, qed_corr);
    }

    // finished successfully
    return 0;
}

// prints cross-section results
void print(TCrossSection * instance, unsigned bin1, unsigned bin2, flavour f, TString variable, Float_t * hadr, Float_t * qed) {

    TString flavour;
    if (f==kCharm) flavour = "Charm";
    if (f==kBeauty) flavour = "Beauty";

    TString line = "\n % " + flavour + " differential cross sections d sigma / dY in bins of " + variable + "\n";
    TString line_true = "\n" + flavour + " RAPGAP differential cross sections d sigma / dY in bins of " + variable + "\n";
    output << line;
    output_true << line_true;
    output_tex << line;

    unsigned counter = 1;
    Float_t total_xsect = 0;
    Float_t total_xsect_err = 0;
    Float_t total_xsect_true = 0;

    for (int i=bin1; i<=bin2; i++) {
        TCrossSectionBin bin = instance -> getCrossSectionBin(i);
        Float_t sigma, sigma_err, sigma_rel_err, sigma_err_syst_up, sigma_err_syst_down, sigma_err_syst_up_rel, sigma_err_syst_down_rel;
        Float_t sigma_true;
        if (f==kCharm) {
            sigma = bin.get_sigma_c();
            sigma_err = bin.get_sigma_c_err();
            sigma_err_syst_up = bin.get_sigma_c_err_syst_up();
            sigma_err_syst_down = bin.get_sigma_c_err_syst_down();
            sigma_true = bin.get_sigma_c_true();

        } else if (f==kBeauty) {
            sigma = bin.get_sigma_b();
            sigma_err = bin.get_sigma_b_err();
            sigma_err_syst_up = bin.get_sigma_b_err_syst_up();
            sigma_err_syst_down = bin.get_sigma_b_err_syst_down();
            sigma_true = bin.get_sigma_b_true();
        }

        sigma_rel_err = 100 * sigma_err / sigma;
        sigma_err_syst_up_rel = 100 * sigma_err_syst_up / sigma;
        sigma_err_syst_down_rel = 100 * sigma_err_syst_down / sigma;

        // get bin boundaries
        Float_t low1, up1, low2, up2;
        Float_t n_sub_bins = bin.getNSubBins();
        if ( (n_sub_bins == 1) || (n_sub_bins == 2) ) {
            low1 = bin.getSubBinLowEdge(0);
            up1 = bin.getSubBinUpEdge(0);
        } else {
            cout << "ERROR: bad TCrossSectionBin object" << endl;
            abort();
        }
        if ( n_sub_bins == 2 ) {
            low2 = bin.getSubBinLowEdge(1);
            up2 = bin.getSubBinUpEdge(1);
        }

        // text file output
        output << "Bin " << counter << ": " << sigma << " +/- " << sigma_err << " ("<<sigma_rel_err<<"%) [STAT] +"<<sigma_err_syst_up << " ("<<sigma_err_syst_up_rel<<"%)";
        output << " -" << sigma_err_syst_down << " (" << sigma_err_syst_down_rel <<"%) [SYST]"  << endl;

        // true cross-sections
        output_true << "Bin " << counter << ": " << sigma_true/bin.getBinWidth () << endl;

        // TEX table output
        if (n_sub_bins == 1) {
            output_tex << low1 << " \t& " << up1 << " \t& " << sigma << " \t& " << sigma_err << " \t& \\numpmerr{+" << sigma_err_syst_up << "}{-" << sigma_err_syst_down << "}{2} \t& " << hadr[i] << "\t& " << qed[i] <<" \t \\\\" << endl;
        } else if (n_sub_bins == 2) {
            output_tex << low1 << " \t& " << up1 << " \t& " << low2 << " & " << up2 << " & " << sigma << " \t& " << sigma_err << " \t& \\numpmerr{+" << sigma_err_syst_up << "}{-" << sigma_err_syst_down << "}{2} \t& " << hadr[i] << "\t& " << qed[i] <<" \t \\\\" << endl;
        }

        // calculate also total cross-sections from every differential ones
        total_xsect += sigma * bin.getBinWidth ();
        total_xsect_err += TMath::Power(sigma_err * bin.getBinWidth (), 2);
        total_xsect_true += sigma_true;

        counter++;
    }

    total_xsect_err = sqrt(total_xsect_err);
    output << "\n TOTAL CROSS-SECTION: " << total_xsect << " +- " << total_xsect_err << " (STAT) " <<    endl;
    output_true << "\n TRUE TOTAL CROSS-SECTION: " << total_xsect_true << endl;
}

