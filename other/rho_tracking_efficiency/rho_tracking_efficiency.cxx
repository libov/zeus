#include <iostream>

#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TStyle.h>
#include <TPaveStats.h>

// settings - not changed often, hence implementing as constants, not passing as arguments
const TString   BINNING = "inclusive";
const TString   REMARK = ".0405e06e07p";
const TString   BIN = "bin1";
const Double_t  PT_STEP_POINT = 1.5;

// environment variables
const TString HISTO_PATH = getenv("HISTO_PATH");
const TString PLOTS_PATH = getenv("PLOTS_PATH");

// other global variables
TFile*    file;
TString   HISTO_VERSION;

// a step function
Double_t step_function (Double_t * x, Double_t * par) {
    if ( x[0] <= PT_STEP_POINT ) return par[0];
    if ( x[0] > PT_STEP_POINT ) return par[1];
}

// initializer
void Initialize() {
    TString   FILENAME = "merged." + BINNING + HISTO_VERSION + REMARK + ".root";
    file = new TFile(HISTO_PATH + "/" + FILENAME, "read");

    gStyle->SetErrorX(0);
    gStyle -> SetFrameBorderMode(0);
    gStyle -> SetOptStat(0);
    gStyle -> SetOptFit(1);
    gStyle -> SetPadLeftMargin(0.135);
    gStyle -> SetStatColor(0);
    Float_t right_margin = gStyle->GetPadRightMargin();
    Float_t top_margin = gStyle->GetPadTopMargin();
    gStyle -> SetStatX( 1 - right_margin );
    gStyle -> SetStatY( 1 - top_margin );
}

void cosmetics(TH1F* h, TString x_title, TString y_title) {
    h -> SetAxisRange(0, 0.03, "Y");
    h -> SetXTitle(x_title);
    h -> SetYTitle(y_title);
    h -> SetTitleOffset(1.35, "Y");
    h -> SetTitleSize(0.05, "Y");
    h -> SetMarkerStyle(20);
}

// a plotting routine - produces ratio and double ratio plots for a given variable
void make_plots(TString variable) {

    // x-axis title
    TString Xtitle;
    Float_t x_range_low;
    Float_t x_range_up;
    if (variable == "pt") {
        Xtitle = "track p_{T} (GeV)";
        x_range_low = 0;
        x_range_up = 5;
    } else if (variable == "phi") {
        Xtitle = "track #phi (rad)";
        x_range_low = -TMath::Pi();
        x_range_up = TMath::Pi();
    } else if (variable == "theta") {
        x_range_low = 0;
        x_range_up = TMath::Pi();
        Xtitle = "track #theta (rad)";
    }

    // create a canvas for the single ratio (R)
    TCanvas * c1 = new TCanvas("c1", "Ratio", 750, 350);
    c1 -> Divide(2,1);

    // data: ratio ztt/(ztt+msa)
    TH1F * pi_ZTTMSA_data = (TH1F*) file -> Get(BIN+"/pi_"+variable+"_ZTTMSA/data");
    TH1F * pi_MSA_data = (TH1F*) file -> Get(BIN+"/pi_"+variable+"_MSA/data");
    TH1F * pi_ratio_data = (TH1F*) pi_MSA_data -> Clone("pi_"+variable+"_ratio_data");
    pi_ratio_data -> Sumw2();
    pi_ratio_data -> Divide(pi_ZTTMSA_data);
    c1 -> cd(1);
    pi_ratio_data -> Draw();
    cosmetics(pi_ratio_data, Xtitle, "R_{DATA}");

    // mc: ratio ztt/(ztt+msa)
    TH1F * pi_ZTTMSA_mc = (TH1F*) file -> Get(BIN+"/pi_"+variable+"_ZTTMSA/rho");
    TH1F * pi_MSA_mc= (TH1F*) file -> Get(BIN+"/pi_"+variable+"_MSA/rho");
    TH1F * pi_ratio_mc = (TH1F*) pi_MSA_mc -> Clone("pi_"+variable+"_ratio_mc");
    pi_ratio_mc -> Sumw2();
    pi_ratio_mc -> Divide(pi_ZTTMSA_mc);
    c1 -> cd(2);
    pi_ratio_mc -> Draw();
    cosmetics(pi_ratio_mc, Xtitle, "R_{MC}");

    // create a canvas for the double ratio (epsilon)
    TCanvas * c2 = new TCanvas("c2", "Double Ratio", 700, 700);

    // double ratio: data/mc
    TH1F * pi_ratio = (TH1F*)pi_ratio_data -> Clone("pi_"+variable+"_ratio");
    pi_ratio -> Sumw2();
    pi_ratio -> Divide(pi_ratio_mc);
    c2 -> cd();
    pi_ratio -> Draw();
    pi_ratio -> SetAxisRange(0, 3.4, "Y");
    pi_ratio -> SetYTitle("#epsilon = R_{DATA}/R_{MC}");
    pi_ratio -> SetTitleOffset(1.2, "Y");
    pi_ratio -> SetXTitle(Xtitle);
    pi_ratio -> SetMarkerStyle(20);

    if ( variable == "theta" || variable == "phi") pi_ratio -> Fit("pol0", "", "", x_range_low, x_range_up );
    if ( variable == "pt" ) {

        TF1 * step_fcn = new TF1("step", step_function, x_range_low, x_range_up, 2);
        step_fcn -> SetParameters(1, 1);
        step_fcn -> SetNpx(10000);
        pi_ratio -> Fit("step");
    }

    c1 -> Print(PLOTS_PATH + "/" + BINNING+HISTO_VERSION+REMARK+BIN+"_"+variable+"_R.eps");
    c2 -> Print(PLOTS_PATH + "/" + BINNING+HISTO_VERSION+REMARK+BIN+"_"+variable+"_epsilon.eps"); 
}

// highest-level routine
void rho_tracking_efficiency(TString version="rho.v136") {

    HISTO_VERSION = version;
    Initialize();

    make_plots("pt");
    make_plots("phi");
    make_plots("theta");
}

// determines reweighting parameters
void reweighting (TString version, TString variable, TString fitfcn, Double_t low_x, Double_t up_x, TString xtitle, Double_t low_y, Double_t up_y) {

    TCanvas * c = new TCanvas();

    HISTO_VERSION = version;
    Initialize();

    TH1F * h_mc = (TH1F*) file -> Get(BIN+"/"+variable+"/rho");
    TH1F * h_data = (TH1F*) file -> Get(BIN+"/"+variable+"/data");
    TH1F * h_ratio = (TH1F *) h_data -> Clone ("ratio");
    h_ratio -> Divide(h_mc);

    h_ratio -> SetXTitle(xtitle);
    h_ratio -> SetAxisRange(low_y, up_y, "Y");
    h_ratio -> SetMarkerStyle(20);
    h_ratio -> SetYTitle("data/MC");
    gStyle -> SetStatColor(0);
    gStyle -> SetStatW(0.1);
    gStyle -> SetStatH(0.1);

    h_ratio -> Draw();

    h_ratio -> Fit(fitfcn, "", "", low_x, up_x);

    c -> Print(PLOTS_PATH + "/" + BINNING+HISTO_VERSION+REMARK+BIN+"_"+variable+".eps");
}

// highest-level routine for reweighting parameters determination
void all_reweightings() {
    reweighting("rho.v134", "rho_phi_classI", "pol6", -3.14, 3.14, "#phi(#rho), rad", 0.4, 2);
    reweighting("rho.v135", "cos_theta_star_classI", "pol2", -1, 1, "cos(#theta^{*})", 0, 7);
}
