#include <TFile.h>
#include <TH1F.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include <TMath.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>

#include <iostream>
using namespace std;

// globals
TString PLOTS_PATH;
TString PATH_SCALING_FACTORS;
Float_t INCLUSIVE_SCALING_FACTOR = 1.28703; // this is to normalize reweighting parameters (further normalization is
                                            // deduced after the 1st trial run)

// part two: doing a smooth function fit + bin averaged value
// arrays to store point coordinates and values
const unsigned  NPOINTS = 22;
Double_t     et[NPOINTS];
Double_t     logQ2[NPOINTS];
Double_t     k_factor[NPOINTS];
Double_t     et_err[NPOINTS];
Double_t     logQ2_err[NPOINTS];
Double_t     k_factor_err[NPOINTS];

unsigned    COUNTER = 0;    // counts entry in the arrays for g_q2_et

// this is for getting the histograms to calculate bin averaged values
const TString FILENAME = "/merged.ETQ2.v22.29.16.0405e06e07p.root";
// const TString FILENAME = "/merged.ETQ2.v22.29.17.0405e06e07p.root";
TFile * file;

TH1F * getHisto(TString filename_base) {
    TFile * file = new TFile (PATH_SCALING_FACTORS+"/"+filename_base+".root", "read");
    TString canvas_name = "CrossSection."+filename_base+"results.ETQ2.v22.29.16.0405e06e07p.v02.true05e06e0607p.xml";
//     TString canvas_name = "CrossSection."+filename_base+"results.ETQ2.v22.29.17.0405e06e07p.v02.true05e06e0607p.xml";
    TCanvas * canv = (TCanvas*) file -> Get(canvas_name);
    TPad * subpad = (TPad*) canv -> GetListOfPrimitives() -> At (0);
    TH1F * histo = (TH1F*) subpad -> GetPrimitive(filename_base);

    return histo;
}

void plot(TString basename, TCanvas * canv, int pad) {
    TH1F * h = getHisto(basename);
    canv -> cd (pad);   // important to do this after the histogram is got, so that current directory
                        // is changed to the canvas
    h -> Draw();
/*    h -> Fit("pol1", "q");
    TF1 * fcn = h -> GetFunction("pol1");
    cout << fcn -> GetParameter (0)/INCLUSIVE_SCALING_FACTOR << " + " << fcn -> GetParameter (1)/INCLUSIVE_SCALING_FACTOR << " * x" << endl;*/
}

void fillArray(TString filename_base) {
    TH1F *h = getHisto(filename_base);
    for (int i = 1; i <= h-> GetNbinsX(); i++){
        // helpers
        char tmp[256];
        sprintf (tmp,"bin%i", COUNTER+2);   // here we rely on proper order of the function call
        TString bin(tmp);
        // get an et histogram and get it's mean (i.e. what we call bin averaged value)
        TH1F * et_histo = (TH1F*) file -> Get(bin+"/truejetet/charm");
        cout << "et: " << et_histo -> GetMean() << " vs " << h -> GetBinCenter(i) << endl;
        et[COUNTER] = et_histo -> GetMean();
        //et[COUNTER] = h -> GetBinCenter(i);
        // get also  q2 histo
        TH1F * q2_histo = (TH1F*) file -> Get(bin+"/Mc_q2/charm");
        if (filename_base=="q2_et_1") logQ2[COUNTER] = TMath::Log10(7.5);
        else if (filename_base=="q2_et_2") logQ2[COUNTER] = TMath::Log10(15);
        else if (filename_base=="q2_et_3") logQ2[COUNTER] = TMath::Log10(30);
        else if (filename_base=="q2_et_4") logQ2[COUNTER] = TMath::Log10(55);
        else if (filename_base=="q2_et_5") logQ2[COUNTER] = TMath::Log10(95);
        else if (filename_base=="q2_et_6") logQ2[COUNTER] = TMath::Log10(560);
        else {
            cout << "such filename not supported!" << endl;
            abort();
        }
        cout << "q2: " << TMath::Log10(q2_histo -> GetMean()) << " vs " << logQ2[COUNTER] << endl;

        logQ2[COUNTER] = TMath::Log10(q2_histo -> GetMean());

        k_factor[COUNTER] = h -> GetBinContent(i);
        k_factor_err[COUNTER] = h -> GetBinError(i);
        logQ2_err[COUNTER] = 0;
        et_err[COUNTER] = 0;
        cout << logQ2[COUNTER] << " " << et[COUNTER] << endl;
        COUNTER++;
    }
}

void merge_plots() {
    // set the globals
    PLOTS_PATH = getenv("PLOTS_PATH");
    //PATH_SCALING_FACTORS = PLOTS_PATH + "/27_19October2011/06_2.29.13_scaling_factors_charm";
    PATH_SCALING_FACTORS = PLOTS_PATH + "/27_19October2011/06a_2.29.16_scaling_factors_charm";
    //PATH_SCALING_FACTORS = PLOTS_PATH + "/29_23October2011/01_scaling_factors_2.29.17";
    file = new TFile (getenv("HISTO_PATH") + FILENAME, "read");

/*    // first try - separate straigh line fit for every q2 bin
    TCanvas * canv_scaling_factors = new TCanvas();
    canv_scaling_factors -> Divide (1,6);

    plot("q2_et_1", canv_scaling_factors, 6);
    plot("q2_et_2", canv_scaling_factors, 5);
    plot("q2_et_3", canv_scaling_factors, 4);
    plot("q2_et_4", canv_scaling_factors, 3);
    plot("q2_et_5", canv_scaling_factors, 2);
    plot("q2_et_6", canv_scaling_factors, 1);
    return;
*/
    // part two: doing a smooth function fit + bin averaged value
    // NOTE: IT IS IMPORTANT TO CALL THIS FUNCTION IN THE FOLLOWING ORDER:
    fillArray("q2_et_1");
    fillArray("q2_et_2");
    fillArray("q2_et_3");
    fillArray("q2_et_4");
    fillArray("q2_et_5");
    fillArray("q2_et_6");

    TCanvas * canv = new TCanvas();
    gStyle -> SetPalette(1);
    gStyle -> SetOptTitle(1);

    TGraph2DErrors * g_q2_et = new TGraph2DErrors (NPOINTS, et, logQ2, k_factor, et_err, logQ2_err, k_factor_err);
    g_q2_et -> SetTitle("scaling factors");

    TAxis * x = g_q2_et -> GetXaxis();
    TAxis * y = g_q2_et -> GetYaxis();
    TAxis * z = g_q2_et -> GetZaxis();
    x -> SetTitle ("E_{T}");
    y -> SetTitle ("LogQ^{2}");
    z -> SetTitle ("k");
    x -> SetTitleOffset (1.4);
    y -> SetTitleOffset (1.5);
    z -> SetRangeUser (1, 2);
    
    g_q2_et -> SetMarkerStyle(20);
    g_q2_et -> SetMarkerSize(1);
    //g_q2_et -> Draw("TRI1 p");
    g_q2_et -> Draw("colz");

    //TF2 * fcn = new TF2 ("fcn", "[0]+[3]*y+([1]+[2]*y)*x", 0, 30, 0, 3.5);
   //TF2 * fcn = new TF2 ("fcn", "[0]+([1]+[2]*y)*x", 0, 30, 0, 3.5);
    //TF2 * fcn = new TF2 ("fcn", "[0]+x-x+y-y", 0, 30, 0, 3.5);

   //TF2 * fcn = new TF2 ("fcn", "[0]+[1]*x + y-y", 0, 30, 0, 3.5);
    TF2 * fcn = new TF2 ("fcn", "[0]+[1]*x + [2]*y", 0, 30, 0, 3.5);
    TAxis * a1 = fcn -> GetXaxis();
    a1 -> SetRangeUser(5, 17.8);
    TAxis * a2 = fcn -> GetYaxis();
    a2 -> SetRangeUser(0.86, 2.56);

    
    TFitResultPtr res = g_q2_et -> Fit("fcn","RS");
    cout << "chi2: " << res -> Chi2() << endl;
    cout << "ndf: " << res -> Ndf() << endl;
    cout << "chi2/ndf: " << res -> Chi2() /res -> Ndf() << endl;

    TCanvas * canv3 = new TCanvas();
    fcn -> Draw("colz");
    fcn -> SetMarkerStyle(20);

    // now the ratio plot
    Double_t     ratio[NPOINTS];
    for (int i=0; i< NPOINTS; i++) {
        ratio[i] = k_factor[i] / fcn -> Eval(et[i], logQ2[i]);
    }

    TGraph2D * g_ratio = new TGraph2D (NPOINTS, et, logQ2, ratio);
    g_ratio -> SetTitle("data/fit");
    TCanvas * canv2 = new TCanvas();
    g_ratio -> SetMarkerStyle(20);
    g_ratio -> SetMarkerSize(1);
    g_ratio -> Draw("colz");
    TAxis * z1 = g_ratio -> GetZaxis();
    z1 -> SetRangeUser (0.5, 1.5);

    
}
