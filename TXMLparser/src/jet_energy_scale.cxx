//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//                                              //
//  March 2011                                  //
//////////////////////////////////////////////////

// system includes
#include <iostream>
using namespace std;

// ROOT includes
#include <TGraphErrors.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>
#include <TPaveText.h>
#include <TPaveStats.h>
#include <TList.h>
#include <TH1.h>

// my includes
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

#include <cmath>

// adopted size of the variation for the systematic uncertainty (per cent)
Float_t     VARIATION_SIZE = 3;
// charm or beauty
bool        isBeauty = false;
bool        with0304p = true;
bool        etcut4_2 = false;

// number of point to appear in a graph
const int       NPOINTS = 13;

const TString   VERSION_LIST[NPOINTS] = {
                  "2.15.26",
                  "2.15.15",
                  "2.15.16",
                  "2.15.17",
                  "2.15.18",
                  "2.15.19",
                  "2.15.20",
                  "2.15.21",
                  "2.15.22",
                  "2.15.23",
                  "2.15.24",
                  "2.15.25",
                  "2.15.27"
                };

/*const TString   VERSION_LIST[NPOINTS] = {
                    "2.12.21",
                    "2.12.19",
                    "2.12.7",
                    "2.12.3",
                    "2.12.9",
                    "2.12.11",
                    "2.12.1",
                    "2.12.10",
                    "2.12.8",
                    "2.12.2",
                    "2.12.6",
                    "2.12.18",
                    "2.12.20"
                };*/


/*const TString   VERSION_LIST[NPOINTS] = {
                    "2.12.25",
                    "2.12.23",
                    "2.12.12",
                    "2.12.5",
                    "2.12.13",
                    "2.12.14",
                    "2.12.0",
                    "2.12.15",
                    "2.12.16",
                    "2.12.4",
                    "2.12.17",
                    "2.12.22",
                    "2.12.24"
                };*/

void    getScalingFactorsCharm(TString histo_year, unsigned bin, Float_t & scaling_factor, Float_t & scaling_factor_err);

// main function
int main(int argc, char **argv) {

    if (argc!=3) {
        cout << "Please give id of the bin to be studied and its counter (the latter just for the text output for later use)" << endl;
        exit(-1);
    }
    unsigned bin=0;
    sscanf (argv[1], "%d", &bin);

    unsigned counter=0;
    sscanf (argv[2], "%d", &counter);
    
    // declare the arrays
    double  x[NPOINTS];
    double  x_err[NPOINTS];
    double  y_c[NPOINTS];
    double  y_c_err[NPOINTS];
    double  y_b[NPOINTS];
    double  y_b_err[NPOINTS];

    if (NPOINTS == 13) {
        x [0] = -8;
        x [1] = -6;
        x [2] = -4;
        x [3] = -3;
        x [4] = -2;
        x [5] = -1;
        x [6] = 0;
        x [7] = 1;
        x [8] = 2;
        x [9] = 3;
        x [10] = 4;
        x [11] = 6;
        x [12] = 8;
    } else {
        cout << " x-vector for " << NPOINTS << " points not implemented" << endl;
        cout << "Exiting..." << endl;
        abort();
    }

    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

    // buffers
    Float_t     scaling_factor;
    Float_t     scaling_factor_err;
    
    // tmp, to be passed from above
    //unsigned bin = 20;
    for (unsigned point = 0; point < NPOINTS; point++) {
        getScalingFactorsCharm(VERSION_LIST[point], bin, scaling_factor, scaling_factor_err);
        y_c[point] = scaling_factor;
        y_c_err[point] = scaling_factor_err;
    }

    TCanvas def("","", 1200, 1000);
    def.cd();
    // nice look (no grey background)
    def.SetFillColor(0);
    
    // move upper right corner of statistics box inside a pad
    gStyle->SetStatX(0.8);
    gStyle->SetStatY(0.9);
    // show fit results
    gStyle->SetOptFit(1);
    // don't show histogram title
    gStyle->SetOptTitle(0);

    // create a graph
    TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, y_c, x_err, y_c_err);

    // cosmetics
    gr_charm -> SetMarkerStyle(22);
    gr_charm -> SetMarkerColor(kGreen);
    gr_charm -> SetMarkerSize(1.5);

    // axes titles and ranges
    TAxis   *ax_charm_y = gr_charm -> GetYaxis();
    ax_charm_y -> SetRangeUser(0.5, 3.5);
    ax_charm_y -> SetTitle ("Scaling factor");

    TAxis   *ax_charm_x = gr_charm -> GetXaxis();
    ax_charm_x -> SetTitle("calorimetric energy variation, %");

    // Draw the graph
    gr_charm -> Draw("ap");

    // fit the graph
    gr_charm -> Fit("pol1", "q", "", -9, 9);
    
    // get the function and paramter errors
    TF1 *pol1 = gr_charm->GetFunction("pol1");
    
    Float_t     intercept = pol1 -> GetParameter(0);
    Float_t     slope = pol1 -> GetParameter(1);
    Float_t     slope_err = pol1 -> GetParError(1);

    Float_t     systematic_error = 100 * VARIATION_SIZE * slope / intercept;
    Float_t     systematic_error_error = systematic_error * slope_err / slope;

    // scaled variant
    Float_t     chi_ndf = pol1->GetChisquare() / pol1->GetNDF();
    Float_t     systematic_error_error_scaled = systematic_error_error/sqrt(1./chi_ndf);
    
    // convert int to TString - a better way??
    char tmp[256];
    sprintf(tmp, "%d", bin);
    TString bin_str(tmp);

    if (isBeauty) {
        cout << "cal_b["<<counter<<"]= " << systematic_error << "; cal_b_err["<<counter<<"]=" << systematic_error_error << ";" << endl;
    } else {
        cout << "cal_c["<<counter<<"]= " << systematic_error << "; cal_c_err["<<counter<<"]=" << systematic_error_error << ";" << endl;
    }
    // set parameter names for nice displaying
    pol1 -> SetParName(0, "Intercept");
    pol1 -> SetParName(1, "SLOPE");

    //TPaveText   *  syst = new TPaveText(0.9648241,2.655594,9.557789,2.891608,"br");
    TPaveText   *  syst = new TPaveText(0.44, 0.65, 0.8, 0.73 ,"NDC");
    syst -> SetShadowColor(0);
    syst -> SetTextAlign(12);

    sprintf (tmp, "Syst. error: (%.3f #pm %.3f) %% ", systematic_error, systematic_error_error);
    syst -> AddText(tmp);

    sprintf (tmp, "after scaling: (%.3f #pm %.3f) %% ", systematic_error, systematic_error_error_scaled);
    syst -> AddText(tmp);

    syst -> Draw();
    
    def.Print("jet_energy_scale_plots/"+bin_str+".png");

    return 0;
}

void    getScalingFactorsCharm(TString histo_version, unsigned bin, Float_t & scaling_factor, Float_t & scaling_factor_err) {

    // lovely hardcodes
    TString year;
    if (with0304p) {
        year = "0405e06e07p";
    } else {
        year = "05e06e07p";
    }
    TString CN_version_short = "v02";

    TString XMLfilename;
    if (etcut4_2) {
        XMLfilename = "results.full.forCHARM"+histo_version+"."+year+"."+CN_version_short+".true05e06e0607p.xml";
    } else {
        XMLfilename = "results.full.forCHARM.ET5"+histo_version+"."+year+"."+CN_version_short+".true05e06e0607p.xml";
    }

    TCrossSection   cCrossSection(XMLfilename);

    if (!isBeauty) {
        scaling_factor = cCrossSection.getCrossSectionBin(bin).get_k_c();
        scaling_factor_err = cCrossSection.getCrossSectionBin(bin).get_k_c_err();
    } else {
        scaling_factor = cCrossSection.getCrossSectionBin(bin).get_k_b();
        scaling_factor_err = cCrossSection.getCrossSectionBin(bin).get_k_b_err();
    }
}
