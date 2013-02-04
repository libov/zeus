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
#include <map>
#include <string.h>
#include <getopt.h>
#include <sys/stat.h>
using namespace std;

// custom headers
#include<TPointF2theo.h>
#include <TCrossSection.h>

// ROOT headers
#include <TROOT.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TFile.h>
#include <TObjString.h>
#include <TObjArray.h>
#include <TPad.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TText.h>
#include <TLegend.h>
#include <TLatex.h>

const unsigned  max_f2c_points = 20;

void addToGraph(TPointF2theo point);

void drawGraph (TCanvas * c, TH1F * h, unsigned & canvas_counter);

Float_t get_xsect(unsigned job_id, TString job_directory);

void addToGraphF2(TPointF2theo point, unsigned i, unsigned q2x_point_id);

TPad * pads[10];

TGraph * theory;

// globals

// number of points at which we extract F2
const unsigned  N_F2_POINTS = 18;

// arays to store measured double-differential cross-sections
Float_t diff_xsect_meas[N_F2_POINTS];
Float_t diff_xsect_meas_err[N_F2_POINTS];
Float_t diff_xsect_meas_err_syst_up[N_F2_POINTS];
Float_t diff_xsect_meas_err_syst_down[N_F2_POINTS];

// array to store theoretical xsections [q2-x point][uncertainty counter]
Float_t diff_xsect_theo[N_F2_POINTS][10];

// maps to store q2-x F2 point objects: vtx[q2-x point counter][uncertainty counter]
map<unsigned, map<unsigned, TPointF2theo> > vtx;
map<unsigned, map<unsigned, TPointF2theo> >::iterator iter1;
map<unsigned, TPointF2theo>::iterator iter2;
// map identifier: integer number, uniquely specifies a q2-x point
unsigned point_counter=1;

// arrays to store f2 values and uncertainties for plotting (some will be used only for F2_meas plotting)
// x and uncertainties
Float_t x[max_f2c_points];
Float_t x_err_up[max_f2c_points];
Float_t x_err_down[max_f2c_points];
// F2
Float_t f2[max_f2c_points];
// F2 uncertaintines
Float_t f2_err_stat[max_f2c_points];
Float_t f2_err_syst_up[max_f2c_points];
Float_t f2_err_syst_down[max_f2c_points];
Float_t extrap_unc_up[max_f2c_points];
Float_t extrap_unc_down[max_f2c_points];
Float_t f2_err_tot_up[max_f2c_points];
Float_t f2_err_tot_down[max_f2c_points];

// main function
int main(int argc, char **argv) {

    // handle command line options

    // declare long options
    static struct option long_options[] = {
        {"meta_file", required_argument, 0, 1},
        {"XMLfile", required_argument, 0, 2},
        {"beauty", no_argument, 0, 3},
        {"only_print_f2", no_argument, 0, 4},
        {"no_qed", no_argument, 0, 5},
    };

    TString meta_file = "";
    TString XMLfile="";
    bool    beauty = false;
    bool    only_print_f2 = false;
    bool    no_qed = false;

    // handle command line options
    opterr = 0;
    int option;
    int option_index;
    while ((option = getopt_long (argc, argv, "h", long_options, &option_index)) != -1) {
        switch (option) {
            case 1:
                meta_file = optarg;
                break;
            case 2:
                XMLfile = optarg;
                break;
            case 3:
                beauty = true;
                break;
            case 4:
                only_print_f2 = true;
                break;
            case 5:
                no_qed = true;
                break;
            case  'h':
                cout<<"usage:\n\t ./f2bc --meta_file <filename prefix (without extension)> --XMLfile <XML file> [--beauty] [options]\n"<<endl;
                cout << "List of options\n" << endl;
                cout << "--only_print_f2\tdon't extract F2 from data, only print theoretical predictions on it" << endl;
                cout << "--no_qed\tData points are not corrected for QED radiation, hence correct them in the extraction" << endl;
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

    // ----------------------------- //
    // ------- USER SETTINGS ------- //
    // ----------------------------- //

    // q2_x_grid.txt
    unsigned f2_points_charm[N_F2_POINTS] = {1, 2, 8, 9, 12, 13, 17, 18, 19, 21, 22, 23, 24, 28, 29, 30, 33, 34};

    // q2_x_grid_beauty.txt
    unsigned f2_points_beauty[N_F2_POINTS] = {1, 2, 7, 8, 12, 13, 20, 21, 22, 23, 24, 25, 26, 29, 30, 32, 35, 37};

    // q2_x_grid_only_extraction_points.txt
    unsigned f2_points_only_extraction[N_F2_POINTS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    // pick up the proper array depending on charm or beauty
    unsigned f2_points[N_F2_POINTS];
    for (int i=0; i<N_F2_POINTS; i++) {
        if (beauty) {
            f2_points[i] = f2_points_beauty[i];
        } else {
            f2_points[i] = f2_points_charm[i];
        }
    }

    // ---------------------------- //
    // ------- PREPARATIONS ------- //
    // ---------------------------- //

    // output text file
    TString PLOTS_PATH=getenv("PLOTS_PATH");
    ofstream output;
    ofstream output_tex;
    if (beauty) {
        output.open(PLOTS_PATH+"/f2b.txt");
        output_tex.open(PLOTS_PATH+"/f2b_tex.txt");
    } else {
        output.open(PLOTS_PATH+"/f2c.txt");
        output_tex.open(PLOTS_PATH+"/f2c_tex.txt");
    }

    // get constants
    TString metafile_name = meta_file+".txt";
    TString job_directory = meta_file;

    // get measured double-differential cross-sections and uncertainties
    TCrossSection cCrossSection(XMLfile);

    // number  of bins in the XML cross-section file
    const unsigned  N_BINS = cCrossSection.getNBins();

    unsigned counter=0;
    if (!beauty) {
        for (int bin=46; bin<=63; bin++) {
            diff_xsect_meas[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_c();
            diff_xsect_meas_err[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_c_err();
            diff_xsect_meas_err_syst_up[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_c_err_syst_up();
            diff_xsect_meas_err_syst_down[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_c_err_syst_down();
            counter++;
        }
    } else {

        for (int bin=45; bin<=62; bin++) {
            diff_xsect_meas[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_b();
            diff_xsect_meas_err[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_b_err();
            diff_xsect_meas_err_syst_up[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_b_err_syst_up();
            diff_xsect_meas_err_syst_down[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_b_err_syst_down();
            counter++;
        }
    }

    // sanity check
    if (counter != N_F2_POINTS) {
        cout << "ERROR" << endl;
        abort();
    }

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
    Float_t hadr_qed_corr[N_BINS+1];
    // initialize with zeros
    for (int i=0; i<(N_BINS+1); i++) {
        hadr_qed_corr[i] = 0;
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
        TString hadr_corr =  ((TObjString*) tokens->At(1)) -> GetString();
        TString qed_corr =  ((TObjString*) tokens->At(2)) -> GetString();

        // store to the array
        hadr_qed_corr[bin_id.Atoi()] = hadr_corr.Atof() * qed_corr.Atof();
    }

    // meta file name and full path
    TString HVQDIS = getenv("HVQDIS");
    TString metafile_path = HVQDIS + "/metafiles/" + metafile_name;

    // count the number of lines in the metafile, i.e. get the total number of jobs submitted
    unsigned n_jobs=0;
    ifstream metafile(metafile_path);
    if (!metafile.is_open()) {
        cout << "ERROR: could not open " << metafile_path << endl;
        abort();
    }
    cout << "INFO: opened " << metafile_path << endl;
    // loop over lines and count them
    while ( getline (metafile,line) ) n_jobs++;
    cout << "INFO: " << n_jobs << " jobs in total" << endl;
    metafile.close();

    // ----------------------------------------------------------------------- //
    // ------- READ METAFILE AND EXTRACT THE INFORMATION FOR EVERY JOB ------- //
    // ----------------------------------------------------------------------- //

    // helping counter
    unsigned previous_uncertainty_counter = 1;
    // open the metafile
    metafile.open(metafile_path, ifstream::in);
    if (!metafile.is_open()) {
        cout << "ERROR: Unable to open file " << metafile_path;
        abort();
    }
    // loop over its lines
    while ( metafile.good() ) {
        // read each line
        getline (metafile,line);
        // skip if empty line
        if (line=="") continue;

        // split the line into tokens
        unsigned token_id = 1;
        char * str=(char*)line.c_str();
        char * pch = strtok (str," ");
        unsigned job_id=0;
        Float_t q2=0;
        Float_t x=0;
        Float_t q2min=0;
        Float_t q2max=0;
        Float_t xmin=0;
        Float_t xmax=0;
        unsigned uncertainty_counter=0;

        while (pch != NULL) {
            if (token_id==1) job_id =atoi(pch);
            if (token_id==2) q2 = atof(pch);
            if (token_id==3) x = atof(pch);
            if (token_id==4) q2min = atof(pch);
            if (token_id==5) q2max = atof(pch);
            if (token_id==6) xmin = atof(pch);
            if (token_id==7) xmax = atof(pch);
            if (token_id==8) uncertainty_counter = atoi(pch);
            pch = strtok (NULL," ");
            token_id++;
        }

        // if q2=0 and x=0, this is an inclusive run for the full q2-x space
        if ( (q2==0) && (x==0) ) {

            TString JOBS_HVQDIS = getenv("JOBS_HVQDIS");
            TString filename = JOBS_HVQDIS + "/" + job_directory + "/000";
            filename +=  job_id;
            TString root_filename = filename + "/histograms.root";
            TString paw_filename = filename + "/histograms.histos";
            struct stat buffer ;
            if ( stat( root_filename.Data(), &buffer ) ) system ("h2root " + paw_filename); 
            TFile * file  = new TFile (root_filename, "read");

            // get the histograms with the visible cross-sections
            TH1F *q2x_1, *q2x_2, *q2x_3, *q2x_4, *q2x_5;

            if (beauty) {

                q2x_1 = (TH1F*) file -> Get ("HISB/h31001");
                q2x_2 = (TH1F*) file -> Get ("HISB/h31002");
                q2x_3 = (TH1F*) file -> Get ("HISB/h31003");
                q2x_4 = (TH1F*) file -> Get ("HISB/h31004");
                q2x_5 = (TH1F*) file -> Get ("HISB/h31005");

            } else {

                q2x_1 = (TH1F*) file -> Get ("HISB/h31101");
                q2x_2 = (TH1F*) file -> Get ("HISB/h31102");
                q2x_3 = (TH1F*) file -> Get ("HISB/h31103");
                q2x_4 = (TH1F*) file -> Get ("HISB/h31104");
                q2x_5 = (TH1F*) file -> Get ("HISB/h31105");
            }

            unsigned first_bin;
            if (beauty) {
                first_bin = 45;
            } else {
                first_bin = 46;
            }

            diff_xsect_theo[0][uncertainty_counter] = q2x_1 -> GetBinContent(1) * hadr_qed_corr[first_bin + 0];
            diff_xsect_theo[1][uncertainty_counter] = q2x_1 -> GetBinContent(2) * hadr_qed_corr[first_bin + 1];
            diff_xsect_theo[2][uncertainty_counter] = q2x_1 -> GetBinContent(3) * hadr_qed_corr[first_bin + 2];
            diff_xsect_theo[3][uncertainty_counter] = q2x_1 -> GetBinContent(4) * hadr_qed_corr[first_bin + 3];

            diff_xsect_theo[4][uncertainty_counter] = q2x_2 -> GetBinContent(1) * hadr_qed_corr[first_bin + 4];
            diff_xsect_theo[5][uncertainty_counter] = q2x_2 -> GetBinContent(2) * hadr_qed_corr[first_bin + 5];
            diff_xsect_theo[6][uncertainty_counter] = q2x_2 -> GetBinContent(3) * hadr_qed_corr[first_bin + 6];
            diff_xsect_theo[7][uncertainty_counter] = q2x_2 -> GetBinContent(4) * hadr_qed_corr[first_bin + 7];
            diff_xsect_theo[8][uncertainty_counter] = q2x_2 -> GetBinContent(5) * hadr_qed_corr[first_bin + 8];

            diff_xsect_theo[9][uncertainty_counter] = q2x_3 -> GetBinContent(1) * hadr_qed_corr[first_bin + 9];
            diff_xsect_theo[10][uncertainty_counter] = q2x_3 -> GetBinContent(2) * hadr_qed_corr[first_bin + 10];
            diff_xsect_theo[11][uncertainty_counter] = q2x_3 -> GetBinContent(3) * hadr_qed_corr[first_bin + 11];
            diff_xsect_theo[12][uncertainty_counter] = q2x_3 -> GetBinContent(4) * hadr_qed_corr[first_bin + 12];

            diff_xsect_theo[13][uncertainty_counter] = q2x_4 -> GetBinContent(1) * hadr_qed_corr[first_bin + 13];
            diff_xsect_theo[14][uncertainty_counter] = q2x_4 -> GetBinContent(2) * hadr_qed_corr[first_bin + 14];
            diff_xsect_theo[15][uncertainty_counter] = q2x_4 -> GetBinContent(3) * hadr_qed_corr[first_bin + 15];

            diff_xsect_theo[16][uncertainty_counter] = q2x_5 -> GetBinContent(1) * hadr_qed_corr[first_bin + 16];
            diff_xsect_theo[17][uncertainty_counter] = q2x_5 -> GetBinContent(2) * hadr_qed_corr[first_bin + 17];

            continue;
        }

        // here comes reading of the cross-section from the job directory
        if (uncertainty_counter != previous_uncertainty_counter ) {
            point_counter = 1;
            previous_uncertainty_counter++;
            // sanity check
            if (previous_uncertainty_counter != uncertainty_counter) {
                cout << "ERROR: not consecutive uncertainty counters in the metafile" << endl;
                abort();
            }
        }

        Float_t xsect = get_xsect(job_id, job_directory);
        if (xsect<=0) {
            cout << "ERROR: could not read out the cross-section from " << job_id << endl;
            abort();
        }

        // create an object
        TPointF2theo point(q2, x, xsect, q2min, q2max, xmin, xmax);

        // for the central value
        if (uncertainty_counter==1) vtx[point_counter][uncertainty_counter]=point;
        // for variations - some additional sanity checks
        if (uncertainty_counter>1) {

            // check that this q2-x point is already present
            bool this_counter_found = false;
            for ( iter1=vtx.begin() ; iter1 != vtx.end(); iter1++ ) {
                if ((*iter1).first == point_counter) { 
                    this_counter_found = true;
                    break;
                }
            }

            if (!this_counter_found) {
                cout << "ERROR: could not find central value with q2-x point number " << point_counter << endl;
                abort();
            }

            // check that q2 and x of this point match that of central value point
            if ( (q2 != vtx[point_counter][1].getQ2()) || (x != vtx[point_counter][1].getX()) ) {
                cout << "ERROR: q2,x for the central value does not match those for variation for the point " << point_counter << endl;
                cout << q2 << " != " << vtx[point_counter][1].getQ2() << ", " << x << " != " << vtx[point_counter][1].getX() << endl;
                abort();
            }

            // add the point to the map and to the variation list of the central point
            vtx[point_counter][1].addVariation(xsect);
            vtx[point_counter][uncertainty_counter] = point;
        }

        point_counter++;
    }
    metafile.close();

    // printout the number of F2 points found, stop execution if none
    cout << "Total number of F2 points: " << vtx.size() << endl;
    if (vtx.size()==0) return 0;

    // printout the F2 values with errors for every point
    cout << endl;
    for ( iter1=vtx.begin() ; iter1 != vtx.end(); iter1++ ) (*iter1).second[1].Print();
    cout << endl;

    if (only_print_f2) return 0;

    // ---------------------------------------- //
    // ---------- plot the F2c_theo ----------- //
    // ---------------------------------------- //

    // horizontal errors are zero
    for (unsigned i=0; i<max_f2c_points; i++) {
        x_err_up[i] = 0;
        x_err_down[i] = 0;
    }

    // create a canvas
    TCanvas * c = new TCanvas("c", "F_{2}", 800, 800);
    c -> cd();
    gStyle -> SetFrameBorderMode(0);
    // divide the canvas manually
    Float_t margin_x = 0.13;
    Float_t margin_y = 0.08;
    Float_t pad_size_y = (1.0 - 2 * margin_y)/3;
    Float_t pad_size_x = (1.0 - margin_x)/3;
    pads[1] = new TPad ("p1", "", 0*pad_size_x + margin_x, 2*pad_size_y + margin_y, 1*pad_size_x + margin_x, 3*pad_size_y + margin_y);
    pads[2] = new TPad ("p2", "", 1*pad_size_x + margin_x, 2*pad_size_y + margin_y, 2*pad_size_x + margin_x, 3*pad_size_y + margin_y);
    pads[3] = new TPad ("p3", "", 2*pad_size_x + margin_x, 2*pad_size_y + margin_y, 1, 3*pad_size_y + margin_y);

    pads[4] = new TPad ("p4", "", 0*pad_size_x + margin_x, 1*pad_size_y + margin_y, 1*pad_size_x + margin_x, 2*pad_size_y + margin_y);
    pads[5] = new TPad ("p5", "", 1*pad_size_x + margin_x, 1*pad_size_y + margin_y, 2*pad_size_x + margin_x, 2*pad_size_y + margin_y);
    pads[6] = new TPad ("p6", "", 2*pad_size_x + margin_x, 1*pad_size_y + margin_y, 1, 2*pad_size_y + margin_y);

    pads[7] = new TPad ("p7", "", 0*pad_size_x + margin_x, 0*pad_size_y + margin_y, 1*pad_size_x + margin_x, 1*pad_size_y + margin_y);

    // cosmetics
    c -> SetFillColor(0);
    for (int i=1; i<=7; i++) {
        pads[i] -> Draw();
        pads[i] -> SetFrameFillColor(0);
        pads[i] -> SetFillColor(0);
    }

    for (int i=1; i<=7; i++) {
        pads[i] -> SetTopMargin(0);
        pads[i] -> SetRightMargin(0);
        pads[i] -> SetBottomMargin(0);
        pads[i] -> SetLeftMargin(0);
    }

    Float_t right_margin = 0.015; // will be also used below
    pads[3] -> SetRightMargin(right_margin);
    pads[6] -> SetRightMargin(right_margin);

    // dummy histo
    Float_t xmin = 4e-5;
    Float_t xmax = 2.5e-1;
    TH1F * h = new TH1F ("", "", 100, xmin, xmax);
    h -> SetStats(kFALSE);
    Float_t ymin = 0;
    Float_t ymax_beauty = 0.057;
    Float_t ymax_beauty_upper_row = 0.02;
    Float_t ymax_charm = 0.7;
    if (beauty) h -> SetAxisRange(ymin, ymax_beauty, "Y");
    else h -> SetAxisRange(ymin, ymax_charm, "Y");
    h -> SetNdivisions(504, "Y");
    TH1F * h2 = (TH1F *) h -> Clone();
    h2 -> SetAxisRange(0, ymax_beauty_upper_row, "Y"); 

    TH1F * dummy;

    unsigned canvas_counter = 1;
    Float_t previous_Q2 = vtx[1][1].getQ2();
    point_counter = 0;
    // loop over all points
    for ( iter1=vtx.begin() ; iter1 != vtx.end(); iter1++ ) {
        if (canvas_counter<=3 && beauty) dummy = h2;
        else dummy = h;

        TPointF2theo point = (*iter1).second[1];
        // if Q2 is the same as for previous point (holds by definition for the 1st point),
        // add this point to the current graph
        if (point.getQ2() == previous_Q2) {
            // add to current graph
            addToGraph(point);
        } else {
            // create a graph
            drawGraph(c, dummy, canvas_counter);
            previous_Q2 = point.getQ2();
            // add to current graph
            addToGraph(point);
        }
    }

    // create a graph
    drawGraph(c, dummy, canvas_counter);

    c -> cd();

    // horizontal axes (for labels and title)
    Float_t label_size_x = 0.027;
    Float_t label_size_y = 0.027;
    Float_t title_offset_x = 0.93;
    Float_t title_size_x = 0.035;
    TString axis_title_x = "x ";
    TGaxis *axis1 = new TGaxis(margin_x, margin_y, margin_x+pad_size_x, margin_y, xmin, xmax, 510,"G");
    axis1 -> SetLabelSize(label_size_x);
    axis1 -> SetLabelOffset(0.002);
    axis1 -> SetTitleOffset(title_offset_x);
    axis1 -> SetTitle(axis_title_x);
    axis1 -> SetTitleSize(title_size_x);
    axis1 -> Draw();

    TGaxis *axis2 = new TGaxis(margin_x+pad_size_x, margin_y+pad_size_y, margin_x+2*pad_size_x, margin_y+pad_size_y, xmin, xmax, 510, "G");
    axis2 -> SetLabelSize(label_size_x);
    axis2 -> SetLabelOffset(0.002);
    axis2 -> SetTitleOffset(title_offset_x);
    axis2 -> SetTitle(axis_title_x);
    axis2 -> SetTitleSize(title_size_x);
    axis2 -> Draw();

    TGaxis *axis3 = new TGaxis(margin_x+2 * pad_size_x, margin_y+pad_size_y, margin_x+3*pad_size_x-right_margin*pad_size_x, margin_y+pad_size_y, xmin, xmax, 510, "G");
    axis3 -> SetLabelSize(label_size_x);
    axis3 -> SetLabelOffset(0.002);
    axis3 -> SetTitleOffset(title_offset_x);
    axis3 -> SetTitle(axis_title_x);
    axis3 -> SetTitleSize(title_size_x);
    axis3 -> Draw();

    // vertical ones
    TGaxis *axis4;
    if (!beauty) axis4 = new TGaxis(margin_x, margin_y+2*pad_size_y, margin_x, margin_y+3*pad_size_y, ymin, ymax_charm, 504);
    if (beauty) axis4 = new TGaxis(margin_x, margin_y+2*pad_size_y, margin_x, margin_y+3*pad_size_y, ymin, ymax_beauty_upper_row, 504);
    axis4 -> SetLabelSize(label_size_y);
    axis4 -> SetTitleOffset(1.2);
    if (beauty) axis4 -> SetTitleOffset(1.4);
    if (beauty) axis4 -> SetTitle("F_{2}^{b#bar{b}}");
    else axis4 -> SetTitle("F_{2}^{c#bar{c}}");
    axis4 -> Draw();

    TGaxis *axis5;
    if (!beauty) axis5 = new TGaxis(margin_x, margin_y+1*pad_size_y, margin_x, margin_y+2*pad_size_y, ymin, ymax_charm, 504);
    if (beauty) axis5 = new TGaxis(margin_x, margin_y+1*pad_size_y, margin_x, margin_y+2*pad_size_y, ymin, ymax_beauty, 504);
    axis5 -> SetLabelSize(label_size_y);
    axis5 -> Draw();

    TGaxis *axis6;
    if (!beauty) axis6 = new TGaxis(margin_x, margin_y, margin_x, margin_y+1*pad_size_y, ymin, ymax_charm, 504);
    if (beauty) axis6 = new TGaxis(margin_x, margin_y, margin_x, margin_y+1*pad_size_y, ymin, ymax_beauty, 504);
    axis6 -> SetLabelSize(label_size_y);
    axis6 -> Draw();

    // ---------------------------------------- //
    // ---------- plot the F2c_meas ----------- //
    // ---------------------------------------- //

    // set size of the tick marks at the end of error bars
    gStyle -> SetEndErrorSize(5);

    TGraphAsymmErrors * data;

    point_counter = 0;
    canvas_counter = 1;
    previous_Q2 = vtx[f2_points[0]][1].getQ2();
    // loop over all q2-x points at which we measure
    for (int i=0; i<N_F2_POINTS; i++) {
        unsigned q2x_point_id = f2_points[i];
        TPointF2theo point = vtx[q2x_point_id][1];

        // if this is the next Q2 point or this is the last point, the graph has to be drawn
        if ( (point.getQ2() != previous_Q2) || (i==(N_F2_POINTS-1)) ) {
            // if this is the last point, it has to be added to the current graph (otherwise not!)
            if (i==(N_F2_POINTS-1)) {
                addToGraphF2(point, i, q2x_point_id);
            }

            // one of the points have to be removed for beauty
            if (canvas_counter == 5 && beauty) point_counter--;

            pads[canvas_counter] -> cd ();
            canvas_counter++;

            TGraphAsymmErrors * g_f2_meas = new TGraphAsymmErrors(point_counter, x, f2, x_err_down, x_err_up, f2_err_stat, f2_err_stat);
            g_f2_meas -> Draw("||");

            TGraphAsymmErrors * g_f2_meast = new TGraphAsymmErrors(point_counter, x, f2, x_err_down, x_err_up, f2_err_tot_down, f2_err_tot_up);
            g_f2_meast -> SetMarkerStyle(20);
            g_f2_meast -> SetMarkerSize(0.7);
            g_f2_meast -> Draw("samepz");

            data = g_f2_meast;

            for (int k=0; k<point_counter; k++) {
                output << "\tQ2= " << previous_Q2 << "\t\tx= " << x[k] << "\tF2_meas= " << f2[k] << " +- " << f2_err_stat[k] << " (" << 100*f2_err_stat[k]/f2[k] << "%) (stat.)";
                output << " +" << f2_err_syst_up[k] << " (" << 100*f2_err_syst_up[k]/f2[k] << "%)";
                output << " -" << f2_err_syst_down[k] << " (" << 100*f2_err_syst_down[k]/f2[k] << "%)";
                output << " (syst.) +" << extrap_unc_up[k] << " -" << extrap_unc_down[k] << " (extrap.)" << endl;
                output_tex << previous_Q2 << " & " << x[k] << " & " << "$\\unit["<< f2[k] << " \\pm " << f2_err_stat[k] << "\\,^{+" << f2_err_syst_up[k] << "}_{-"<< f2_err_syst_down[k] << "}\\,^{+" << extrap_unc_up[k] << "}_{-" << extrap_unc_down[k] << "}]{}$ \\\\"<<endl;
            }
            point_counter = 0;
        }

        // add to current graph
        addToGraphF2(point, i, q2x_point_id);

        previous_Q2 = point.getQ2();
    }

    // select the canvas
    c -> cd();

    // the legend
    TLegend * leg = new TLegend(0.5, 0.1, 0.8, 0.28);
    leg->AddEntry(data, "ZEUS 354 pb^{-1}","p");
    leg -> AddEntry(theory, "HVQDIS #otimes HERAPDF 1.0", "l");
    leg -> SetFillColor(0);
    leg -> SetBorderSize(0);
    leg->Draw();

    // additionally a box and a line for HVQDIS entry
    TBox * box_hvqdis = new TBox (0.51, 0.13, 0.57, 0.16);
    box_hvqdis -> SetFillColor(7);
    box_hvqdis -> Draw();

    TLine * line_hvqdis = new TLine (0.51, 0.145, 0.57, 0.145);
    line_hvqdis -> SetLineWidth(2);
    line_hvqdis -> Draw();

    // finally, print the ZEUS on top
    TText * zeus = new TText (0.49, 0.94, "ZEUS");
    zeus -> SetTextFont(22);
    zeus -> SetTextSize (0.07);
    zeus -> Draw();

    // create Q2 labels
    Float_t y_position;
    if (beauty) y_position = 0.87;
    if (!beauty) y_position = 0.87;
    TLatex * q2_values[10];
    q2_values[0] = new TLatex(0.24 + 0 * pad_size_x, y_position, "Q^{2} = 6.5 GeV^{2}");
    q2_values[1] = new TLatex(0.24 + 1 * pad_size_x, y_position, "Q^{2} = 12 GeV^{2}");
    q2_values[2] = new TLatex(0.24 + 2 * pad_size_x, y_position, "Q^{2} = 25 GeV^{2}");
    q2_values[3] = new TLatex(0.24 + 0 * pad_size_x, y_position - 1 * pad_size_y, "Q^{2} = 30 GeV^{2}");
    q2_values[4] = new TLatex(0.24 + 1 * pad_size_x, y_position - 1 * pad_size_y, "Q^{2} = 80 GeV^{2}");
    q2_values[5] = new TLatex(0.24 + 2 * pad_size_x, y_position - 1 * pad_size_y, "Q^{2} = 160 GeV^{2}");
    q2_values[6] = new TLatex(0.24 + 0 * pad_size_x, y_position- 2 * pad_size_y, "Q^{2} = 600 GeV^{2}");

    for (int i=0; i<7; i++) {
        q2_values[i] -> Draw();
        q2_values[i] -> SetTextSize(0.025);
    }

    // print the results
    if (beauty) {
        c->Print(PLOTS_PATH+"/f2b.eps");
    } else {
        c->Print(PLOTS_PATH+"/f2c.eps");
    }

    // close the text file
    output.close();
    output_tex.close();

    return 0;
}

void addToGraph(TPointF2theo point) {
    x[point_counter] = point.getX();
    f2[point_counter] = point.getF2();
    f2_err_tot_up[point_counter] = point.getRelativeUncertaintyUp() * point.getF2();
    f2_err_tot_down[point_counter] = point.getRelativeUncertaintyDown() * point.getF2();
    point_counter++;
}

void drawGraph (TCanvas * c, TH1F * h, unsigned & canvas_counter) {

    pads[canvas_counter] -> cd();
    h -> Draw();

    gPad -> SetLogx();
    gPad -> SetTicks(1,1);

    TGraphAsymmErrors * g_band = new TGraphAsymmErrors(point_counter, x, f2, x_err_down, x_err_up, f2_err_tot_down, f2_err_tot_up);
    g_band -> Draw("3C");
    g_band -> SetFillColor(7);

    TGraph * g_central = new TGraph(point_counter, x, f2);
    g_central -> Draw("C");
    g_central -> SetLineColor(kBlack);
    g_central -> SetLineWidth(2);

    theory = g_central;

    // and make all arrays zero
    for (unsigned j=0; j<max_f2c_points; j++) {
        x[j] = 0;
        f2[j] = 0;
        f2_err_tot_up[j] = 0;
        f2_err_tot_down[j] = 0;
    }

    canvas_counter++;
    point_counter = 0;
}

Float_t get_xsect(unsigned job_id, TString job_directory) {

    TString JOBS_HVQDIS = getenv("JOBS_HVQDIS");
    TString job = JOBS_HVQDIS + "/" + job_directory + "/000";
    job += job_id;
    TString logfile_name = job+"/hvqdis.out";
    ifstream logfile(logfile_name);
    if (!logfile.is_open()) return -1;
    TString phrase = " 'Total      sig (pb):' ";
    system("rm -f tmp.txt");
    system("grep " + phrase + logfile_name + " | awk '{print $4}' > tmp.txt");
    ifstream tmp("tmp.txt");
    if (!tmp.is_open()) return -1;
    string line;
    getline(tmp, line);
    tmp.close();
    system("rm -f tmp.txt");
    Float_t xsect = atof(line.c_str());
    return xsect;
}

void addToGraphF2(TPointF2theo point, unsigned i, unsigned q2x_point_id) {

    // fill the arrays
    x[point_counter] = point.getX();
    f2[point_counter] = (diff_xsect_meas[i] / diff_xsect_theo[i][1]) * point.getF2();

    // get extrapolation uncertainties
    extrap_unc_up[point_counter] = 0;
    extrap_unc_down[point_counter] = 0;
    for (int k=2; k<=7; k++) {
        Float_t delta = f2[point_counter] - (diff_xsect_meas[i] / diff_xsect_theo[i][k]) * vtx[q2x_point_id][k].getF2();
        if (delta<0) extrap_unc_up[point_counter] += delta*delta;
        if (delta>0) extrap_unc_down[point_counter] += delta*delta;
    }

    extrap_unc_up[point_counter] = sqrt(extrap_unc_up[point_counter]);
    extrap_unc_down[point_counter] = sqrt(extrap_unc_down[point_counter]);

    // statistical uncertainty
    f2_err_stat[point_counter] = f2[point_counter] * (diff_xsect_meas_err[i]/diff_xsect_meas[i]);

    // systematic uncertainty
    f2_err_syst_up[point_counter] = f2[point_counter] * (diff_xsect_meas_err_syst_up[i]/diff_xsect_meas[i]);
    f2_err_syst_down[point_counter] = f2[point_counter] * (diff_xsect_meas_err_syst_down[i]/diff_xsect_meas[i]);

    // stat + syst + extr
    f2_err_tot_up[point_counter] = sqrt(f2_err_stat[point_counter]*f2_err_stat[point_counter] + f2_err_syst_up[point_counter]*f2_err_syst_up[point_counter] + extrap_unc_up[point_counter]*extrap_unc_up[point_counter]);
    f2_err_tot_down[point_counter] = sqrt(f2_err_stat[point_counter]*f2_err_stat[point_counter] + f2_err_syst_down[point_counter]*f2_err_syst_down[point_counter]+ extrap_unc_down[point_counter]*extrap_unc_down[point_counter]);

    // increment counter
    point_counter++;
}
