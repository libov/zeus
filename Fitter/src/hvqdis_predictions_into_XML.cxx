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

void getCrossSection (TH1F * h, unsigned bin1, unsigned bin2, Float_t * diff_xsect_theo );

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
    cout << "INFO: opened " << binningXMLfileName << endl;

    // construct name of the output file
    TString out_file_name = "hvqdis_predictions." + meta_file + ".xml";
    // jobs directory is assumed to have the same name as the prefix of the metafile
    TString job_directory = meta_file;
    // this is total number of cross-sections sets including the central value, i.e. 
    // the number of variations is in fact (N_VARIATIONS-1)
    const unsigned N_VARIATIONS_MAX= 20;
    unsigned N_VARIATIONS = 0;
    // number  of bins in the XML cross-section file
    const unsigned  N_BINS = cCrossSection.getNBins();
    // array to store theoretical xsections; "+1" is to account the here we count from 1, not from 0
    Float_t diff_xsect_theo[N_VARIATIONS_MAX+1][N_BINS+1];
    Float_t diff_xsect_theo_err_up[N_BINS+1];
    Float_t diff_xsect_theo_err_down[N_BINS+1];
    // initialize arrays to zero (so that for inclusive bins zeros are written)
    for (int j=0; j<(N_BINS+1); j++) {
        diff_xsect_theo_err_up[j] = 0;
        diff_xsect_theo_err_down[j] = 0;
        for (int i=0; i<(N_VARIATIONS_MAX+1); i++) diff_xsect_theo[i][j] = 0;
    }

    // get full path to the metafile
    TString HVQDIS = getenv("HVQDIS");
    TString metafile_path = HVQDIS + "/" + meta_file+".txt";

    // read values of hadronization and QED corrections
    TString DATABASE_PATH=getenv("DATABASE_PATH");
    TString filename=DATABASE_PATH+"/hadr_qed_corr_charm.txt";
    ifstream hadr(filename);
    if (!hadr.is_open()) {
        cout << "ERROR: Unable to open file " << filename; 
        abort();
    }
    cout << "INFO: opened " << filename << endl;

    // an array to store corrections
    Float_t hadr_qed_corr[N_BINS+1];
    // initialize with zeros
    for (int i=0; i<(N_BINS+1); i++) {
        hadr_qed_corr[i] = 0;
    }
    
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
        TString hadr_corr =  ((TObjString*) tokens->At(1)) -> GetString();
        TString qed_corr =  ((TObjString*) tokens->At(2)) -> GetString();

        // store to the array
        hadr_qed_corr[bin_id.Atoi()] = hadr_corr.Atof() * qed_corr.Atof();
    }

    // open the metafile
    ifstream f(metafile_path);
    if (!f.is_open()) {
        cout << "ERROR: Unable to open file " << metafile_path; 
        abort();
    }
    cout << "INFO: opened " << metafile_path << endl;

    // loop over its lines
    while ( f.good() ) {
        // read each line
        getline (f,line);
        // skip if empty line
        if (line=="") continue;

        // split the line into tokens and read relevant variables: job id, q2, uncertainty counter (1=central, rest - variations)
        unsigned token_id = 1;
        char * str=(char*)line.c_str();
        char * pch = strtok (str," ");
        unsigned job_id=0;
        Float_t q2=0;
        unsigned uncertainty_counter=0;

        while (pch != NULL) {
            if (token_id==1) job_id =atoi(pch);
            if (token_id==2) q2 = atof(pch);
            if (token_id==8) uncertainty_counter = atoi(pch);
            pch = strtok (NULL," ");
            token_id++;
        }

        // here we are interested in the visible cross-sections, hence
        // q2=0, x=0 in the metafile (see e.g. $HVQDIS/submit_hvqdis.sh);
        // therefore skip if q2 not equal to 0
        if (q2!=0) continue;

        // get the root file with histograms corresponding to this job
        TString JOBS_HVQDIS = getenv("JOBS_HVQDIS");
        TString filename = JOBS_HVQDIS + "/" + job_directory + "/000";
        filename +=  job_id;
        filename += "/histograms.root";
        TFile * file  = new TFile (filename, "read");

        // get the histograms with the visible cross-sections
        TH1F * et =  (TH1F*) file -> Get ("HISB/h30101");
        TH1F * eta =  (TH1F*) file -> Get ("HISB/h30102");
        TH1F * hq2 =  (TH1F*) file -> Get ("HISB/h30103");
        TH1F * x =  (TH1F*) file -> Get ("HISB/h30104");

        TH1F * q2x_1 = (TH1F*) file -> Get ("HISB/h31101");
        TH1F * q2x_2 = (TH1F*) file -> Get ("HISB/h31102");
        TH1F * q2x_3 = (TH1F*) file -> Get ("HISB/h31103");
        TH1F * q2x_4 = (TH1F*) file -> Get ("HISB/h31104");
        TH1F * q2x_5 = (TH1F*) file -> Get ("HISB/h31105");

        // for every histogram, get all the cross-sections and store to an array
        getCrossSection(eta, 2, 12, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(et, 14, 20, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(x, 31, 36, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(hq2, 38, 45, diff_xsect_theo[uncertainty_counter]);

        getCrossSection(q2x_1, 46, 49, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(q2x_2, 50, 54, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(q2x_3, 55, 58, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(q2x_4, 59, 61, diff_xsect_theo[uncertainty_counter]);
        getCrossSection(q2x_5, 62, 63, diff_xsect_theo[uncertainty_counter]);

        // correct for qed and hadronization effects
        for (int i=1;i<=N_BINS; i++) diff_xsect_theo[uncertainty_counter][i] *= hadr_qed_corr[i];

        // number of variations matches maximum uncertainty counter in a metafile
        if (uncertainty_counter>N_VARIATIONS) N_VARIATIONS = uncertainty_counter;
    }
    f.close();

    // sanity check
    if (N_VARIATIONS == 0) {
        cout << "ERROR: could not read uncertainty counter" << endl;
        abort();
    }
    cout << "INFO: N_VARIATIONS = " << N_VARIATIONS << endl;

    if (N_VARIATIONS >=2 ) {
    // evaluate uncertainty for every differential bin
    // loop over bins
    for (int i=1; i<=N_BINS; i++) {
        Float_t uncertainty_up = 0;
        Float_t uncertainty_down = 0;
        // uncertainty_counter=1 => central value
        // uncertainty_counter=[2,N_VARIATIONS] => variations
        // loop over variations for the current bin, compare to its central value,
        // determine whether this is up or down variation, add in quadrature
        for (int j=2; j<=N_VARIATIONS; j++) {
            Float_t delta = diff_xsect_theo[j][i] - diff_xsect_theo[1][i];
            if (delta > 0) uncertainty_up += (delta*delta);
            if (delta < 0) uncertainty_down += (delta*delta);
        }
        // take a square root, since that was added in quadrature
        diff_xsect_theo_err_up[i] = TMath::Sqrt(uncertainty_up);
        diff_xsect_theo_err_down[i] = TMath::Sqrt(uncertainty_down);
    }
    }

    // finally, store the obtained cross-section value and uncertainty to an XML file!
    for (int i=1; i<=N_BINS; i++) {
        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(i);
        cBin.set_sigma_c(diff_xsect_theo[1][i]);
        cBin.set_sigma_c_err_syst_up(diff_xsect_theo_err_up[i]);
        cBin.set_sigma_c_err_syst_down(diff_xsect_theo_err_down[i]);
        cCrossSection.modifyCrossSectionBin(i, cBin);
    }

    // write data to file
    cCrossSection.WriteXMLfile(out_file_name);

    // finished successfully
    return 0;
}

void getCrossSection (TH1F * h, unsigned bin1, unsigned bin2, Float_t * diff_xsect_theo ) {
    unsigned j=1;
    for (int i=bin1; i<=bin2; i++) {
        diff_xsect_theo[i] = h -> GetBinContent(j);
        j++;
    }
}
