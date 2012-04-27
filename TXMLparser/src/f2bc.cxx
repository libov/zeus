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

const unsigned  max_f2c_points = 20;

void addToGraph(Float_t * x, Float_t * f2, Float_t * f2_err_up, Float_t * f2_err_down, unsigned & point_counter, TPointF2theo point) {
    x[point_counter] = point.getX();
    f2[point_counter] = point.getF2();
    f2_err_up[point_counter] = point.getRelativeUncertaintyUp() * point.getF2();
    f2_err_down[point_counter] = point.getRelativeUncertaintyDown() * point.getF2();
    point_counter++;
}

void drawGraph (Float_t * x, Float_t * f2, Float_t * f2_err_up, Float_t * f2_err_down, Float_t * x_err_up, Float_t * x_err_down, TCanvas * c, TH1F * h, unsigned & canvas_counter, unsigned & point_counter) {
    
    c -> cd(canvas_counter);
    h -> Draw();
            
    gPad -> SetLogx();
    gPad -> SetTicks(1,1);
    gPad -> SetBottomMargin(0);
    gPad -> SetTopMargin(0);
        
    TGraphAsymmErrors * g_band = new TGraphAsymmErrors(point_counter, x, f2, x_err_down, x_err_up, f2_err_down, f2_err_up);
    g_band -> Draw("3L");
    g_band -> SetFillColor(kOrange);

    TGraph * g_central = new TGraph(point_counter, x, f2);
    g_central -> Draw("L");
    g_central -> SetLineColor(kBlack);
    g_central -> SetLineWidth(2);

    // and make all arrays zero
    for (unsigned j=0; j<max_f2c_points; j++) {
        x[j] = 0;
        f2[j] = 0;
        f2_err_up[j] = 0;
        f2_err_down[j] = 0;
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

// main function
int main(int argc, char **argv) {

    // ----------------------------- // 
    // ------- USER SETTINGS ------- //
    // ----------------------------- // 

    TString metafile_name = "meta_Apr21_2012_14:35:32.txt";
    TString job_directory = "01_tests/05a_1M_5_1M_10_charm";
    const unsigned  N_F2_POINTS = 18;
    unsigned f2_points[N_F2_POINTS] = {1, 2, 8, 9, 12, 13, 17, 18, 19, 21, 22, 23, 24, 28, 29, 30, 33, 34};
    TString results_filename = "results.full.forCHARM2.34.3.0405e06e07p.v02.true05e06e0607p.xml";

    // ---------------------------- //
    // ------- PREPARATIONS ------- //
    // ---------------------------- //

    // get measured double-differential cross-sections and statistical uncertainties
    TCrossSection cCrossSection(results_filename);
    Float_t diff_xsect_meas[N_F2_POINTS];
    Float_t diff_xsect_meas_err[N_F2_POINTS];
    unsigned counter=0;
    for (int bin=46; bin<=63; bin++) {
        diff_xsect_meas[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_c();
        diff_xsect_meas_err[counter] = cCrossSection.getCrossSectionBin(bin).get_sigma_c_err();
        counter++;
    }
    // sanity check
    if (counter != N_F2_POINTS) {
        cout << "ERROR" << endl;
        abort();
    }

    // array to store theoretical xsections
    Float_t diff_xsect_theo[N_F2_POINTS];

    // maps to store q2-x F2 points
    map<unsigned, TPointF2theo> vtx;
    map<unsigned, TPointF2theo>::iterator iter;
    // map identifier: integer number, uniquely specifies a q2-x point
    unsigned point_counter=1;

    // a string for file operations
    string line;

    // meta file name and full path
    TString HVQDIS = getenv("HVQDIS");
    TString metafile_path = HVQDIS + "/" + metafile_name;

    // count the number of lines in the metafile, i.e. get the total number of jobs submitted
    unsigned n_jobs=0;
    ifstream metafile(metafile_path);
    if (!metafile.is_open()) abort();
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
            if (uncertainty_counter==1) {
                    TString JOBS_HVQDIS = getenv("JOBS_HVQDIS");
                    TString filename = JOBS_HVQDIS + "/" + job_directory + "/000";
                    filename +=  job_id;
                    filename += "/histograms.root";
                    TFile * file  = new TFile (filename, "read");

                    TH1F * q2x_1 = (TH1F*) file -> Get ("HISB/h31101");
                    TH1F * q2x_2 = (TH1F*) file -> Get ("HISB/h31102");
                    TH1F * q2x_3 = (TH1F*) file -> Get ("HISB/h31103");
                    TH1F * q2x_4 = (TH1F*) file -> Get ("HISB/h31104");
                    TH1F * q2x_5 = (TH1F*) file -> Get ("HISB/h31105");

                    diff_xsect_theo[0]=(q2x_1 -> GetBinContent(1)) * 1.19 * 0.96;
                    diff_xsect_theo[1]=(q2x_1 -> GetBinContent(2)) * 1.21 * 0.98;
                    diff_xsect_theo[2]=(q2x_1 -> GetBinContent(3)) * 1.23 * 0.98;
                    diff_xsect_theo[3]=(q2x_1 -> GetBinContent(4)) * 1.07 * 1.00;

                    diff_xsect_theo[4]=q2x_2 -> GetBinContent(1) * 1.13 * 0.97;
                    diff_xsect_theo[5]=q2x_2 -> GetBinContent(2) * 1.09 * 0.97;
                    diff_xsect_theo[6]=q2x_2 -> GetBinContent(3) * 1.05 * 0.98;
                    diff_xsect_theo[7]=q2x_2 -> GetBinContent(4) * 1.01 * 0.99;
                    diff_xsect_theo[8]=q2x_2 -> GetBinContent(5) * 0.91 * 0.99;

                    diff_xsect_theo[9]=q2x_3 -> GetBinContent(1) * 1.07 * 0.97;
                    diff_xsect_theo[10]=q2x_3 -> GetBinContent(2) * 1.03 * 0.99;
                    diff_xsect_theo[11]=q2x_3 -> GetBinContent(3) * 1.01 * 0.98;
                    diff_xsect_theo[12]=q2x_3 -> GetBinContent(4) * 0.93 * 0.93;

                    diff_xsect_theo[13]=q2x_4 -> GetBinContent(1) * 1.05 * 0.97;
                    diff_xsect_theo[14]=q2x_4 -> GetBinContent(2) * 1.01 * 1.00;
                    diff_xsect_theo[15]=q2x_4 -> GetBinContent(3) * 0.96 * 0.80;

                    diff_xsect_theo[16]=q2x_5 -> GetBinContent(1) * 1.02 * 0.88;
                    diff_xsect_theo[17]=q2x_5 -> GetBinContent(2) * 1.01 * 0.84;
            }
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
        //if (xsect<0) continue;

        // in this case this is a central value
        if (uncertainty_counter==1) {
            if (xsect>0) {
                TPointF2theo point(q2, x, xsect, q2min, q2max, xmin, xmax);
                vtx[point_counter]=point;
            }
            point_counter++;
        } else { // otherwise

            bool this_counter_found = false;
                
            for ( iter=vtx.begin() ; iter != vtx.end(); iter++ ) {
                if ((*iter).first == point_counter) { 
                    this_counter_found = true;
                    break;
                }
            }

            if (this_counter_found) {
                // sanity check
                if ( (q2 != vtx[point_counter].getQ2()) || (x != vtx[point_counter].getX()) ) {
                    cout << "ERROR: q2,x for the central value does not match those for variation for the point " << point_counter << endl;
                    cout << q2 << " != " << vtx[point_counter].getQ2() << ", " << x << " != " << vtx[point_counter].getX() << endl;
                }
                if (xsect>0) vtx[point_counter].addVariation(xsect);
            }

            point_counter++;
        }
    }
    metafile.close();

    // printout the number of F2 points found, stop execution of none
    cout << "Total number of F2 points: " << vtx.size() << endl;
    if (vtx.size()==0) return 0;

    // printout the F2 values with errors for every point
    cout << endl;
    for ( iter=vtx.begin() ; iter != vtx.end(); iter++ ) (*iter).second.Print();
    cout << endl;

    // ---------------------------------------- //
    // ---------- plot the F2c_theo ----------- //
    // ---------------------------------------- //

    // arrays to store f2 values and uncertainties - for plotting!
    Float_t x[max_f2c_points];
    Float_t f2[max_f2c_points];
    //Float_t f2_meas[max_f2c_points];
    Float_t f2_err_up[max_f2c_points];
    Float_t f2_err_down[max_f2c_points];
    Float_t x_err_up[max_f2c_points];
    Float_t x_err_down[max_f2c_points];

    // horizontal errors are zero
    for (unsigned i=0; i<max_f2c_points; i++) {
        x_err_up[i] = 0;
        x_err_down[i] = 0;
    }

    // create a canvas
    TCanvas * c = new TCanvas();
    c->Divide(3,3,0,0);

    // dummy histo
    TH1F * h = new TH1F ("", "", 100, 6e-5, 2.5e-1);
    h -> SetStats(kFALSE);
    h -> SetAxisRange(0, 0.7, "Y");
    h -> SetNdivisions(504, "Y");

    unsigned canvas_counter = 1;
    Float_t previous_Q2 = vtx[1].getQ2();
    point_counter = 0;
    // loop over all points
    for ( iter=vtx.begin() ; iter != vtx.end(); iter++ ) {
        TPointF2theo point = (*iter).second;
        // if Q2 is the same as for previous point (holds by definition for the 1st point),
        // add this point to the current graph
        if (point.getQ2() == previous_Q2) {
            // add to current graph
            addToGraph(x, f2, f2_err_up, f2_err_down, point_counter, point);
        } else {
            // create a graph
            drawGraph(x, f2, f2_err_up, f2_err_down, x_err_up, x_err_down, c, h, canvas_counter, point_counter);
            previous_Q2 = point.getQ2();
            // add to current graph
            addToGraph(x, f2, f2_err_up, f2_err_down, point_counter, point);
        }
    }

    // create a graph
    drawGraph(x, f2, f2_err_up, f2_err_down, x_err_up, x_err_down, c, h, canvas_counter, point_counter);

    // ---------------------------------------- //
    // ---------- plot the F2c_meas ----------- //
    // ---------------------------------------- //
    point_counter = 0;
    canvas_counter = 1;
    previous_Q2 = vtx[f2_points[0]].getQ2();
    // loop over all q2-x points at which we measure
    for (int i=0; i<N_F2_POINTS; i++) {
        unsigned q2x_point_id = f2_points[i];
        TPointF2theo point = vtx[q2x_point_id];

        if ( (point.getQ2() != previous_Q2) || (i==(N_F2_POINTS-1)) ) {
            if (i==(N_F2_POINTS-1)) {
                x[point_counter] = point.getX();
                f2[point_counter] = (diff_xsect_meas[i] / diff_xsect_theo[i]) * point.getF2();
                f2_err_up[point_counter] = f2[point_counter] * (diff_xsect_meas_err[i]/diff_xsect_meas[i]);
                f2_err_down[point_counter] = f2[point_counter] * (diff_xsect_meas_err[i]/diff_xsect_meas[i]);
                // increment counter
                point_counter++;
            }
            TGraphAsymmErrors * g_f2_meas = new TGraphAsymmErrors(point_counter, x, f2, x_err_down, x_err_up, f2_err_down, f2_err_up);
            g_f2_meas -> SetMarkerStyle(20);
            c -> cd (canvas_counter);
            canvas_counter++;
            g_f2_meas -> Draw("samep");
            for (int k=0; k<point_counter; k++) {
                cout << "\tQ2= " << previous_Q2 << "\t\tx= " << x[k] << "\tF2_meas= " << f2[k] << " +" << f2_err_up[k] << " -" << f2_err_down[k] << endl;
            }
            point_counter = 0;
        }

        // add to current graph
        x[point_counter] = point.getX();
        f2[point_counter] = (diff_xsect_meas[i] / diff_xsect_theo[i]) * point.getF2();
        f2_err_up[point_counter] = f2[point_counter] * (diff_xsect_meas_err[i]/diff_xsect_meas[i]);
        f2_err_down[point_counter] = f2[point_counter] * (diff_xsect_meas_err[i]/diff_xsect_meas[i]);
        // increment counter
        point_counter++;

        previous_Q2 = point.getQ2();
    }

    // print the results
    TString PLOTS_PATH=getenv("PLOTS_PATH");
    c->Print(PLOTS_PATH+"/f2c.eps");
    c->Print(PLOTS_PATH+"/f2c.root");

    return 0;
}