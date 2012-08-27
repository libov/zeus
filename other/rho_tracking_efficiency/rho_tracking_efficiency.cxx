#include <iostream>

#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLine.h>

// input data
const TString   BINNING = "tracking";
const TString   HISTO_VERSION = "rho.v35";
const TString   REMARK = ".0405e06e07p";
const TString   BIN = "bin1";
const TString   OUTPUT_FILENAME = "pion_pt_reweighting_histo";

// other global constants
TString   HISTO_PATH;
TString   FILENAME;
TFile*    file;

void helper2(TString variable);

void rho_tracking_efficiency() {

    HISTO_PATH = getenv("HISTO_PATH");
    FILENAME = "merged." + BINNING + HISTO_VERSION + REMARK + ".root";
    file = new TFile(HISTO_PATH + "/" + FILENAME, "read");

    helper2("pt");
    helper2("phi");
    helper2("theta");
}

void helper2(TString variable) {

    TCanvas * c1 = new TCanvas();
    c1 -> Divide(2,2);

    // data: ratio ztt/(ztt+msa) for pion pt
    TH1F * pi_pt_ZTTMSA_data = (TH1F*) file -> Get(BIN+"/pi_"+variable+"_ZTTMSA/data");
    TH1F * pi_pt_MSA_data = (TH1F*) file -> Get(BIN+"/pi_"+variable+"_MSA/data");
    TH1F * pi_pt_ratio_data = (TH1F*) pi_pt_MSA_data -> Clone("pi_"+variable+"_ratio_data");
    pi_pt_ratio_data -> Sumw2();
    pi_pt_ratio_data -> Divide(pi_pt_ZTTMSA_data);
    c1 -> cd(1);
    pi_pt_ratio_data -> Draw();
    pi_pt_ratio_data -> SetAxisRange(0, 0.03, "Y"); 

    // mc: ratio ztt/(ztt+msa) for pion pt
    TH1F * pi_pt_ZTTMSA_mc = (TH1F*) file -> Get(BIN+"/pi_"+variable+"_ZTTMSA/rho");
    TH1F * pi_pt_MSA_mc= (TH1F*) file -> Get(BIN+"/pi_"+variable+"_MSA/rho");
    TH1F * pi_pt_ratio_mc = (TH1F*) pi_pt_MSA_mc -> Clone("pi_"+variable+"_ratio_mc");
    pi_pt_ratio_mc -> Sumw2();
    pi_pt_ratio_mc -> Divide(pi_pt_ZTTMSA_mc);
    c1 -> cd(2);
    pi_pt_ratio_mc -> Draw();
    pi_pt_ratio_mc -> SetAxisRange(0, 0.03, "Y");

    // double ratio: data/mc for pion pt
    TH1F * pi_pt_ratio = (TH1F*)pi_pt_ratio_data -> Clone("pi_"+variable+"_ratio");
    pi_pt_ratio -> Sumw2();
    pi_pt_ratio -> Divide(pi_pt_ratio_mc);
    c1 -> cd(3);
    pi_pt_ratio -> Draw();
    pi_pt_ratio -> SetAxisRange(0, 2, "Y");
    TLine * line = new TLine(0, 1, 5, 1);
    line -> Draw("same");
    line -> SetLineStyle(2);

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c1 -> Print(PLOTS_PATH + "/" + BINNING+HISTO_VERSION+REMARK+BIN+"_"+variable+".eps");
}

void pt_theta_reweighting_v1() {

    HISTO_PATH = getenv("HISTO_PATH");
    FILENAME = "merged." + BINNING + HISTO_VERSION + REMARK + ".root";
    file = new TFile(HISTO_PATH + "/" + FILENAME, "read");

    TString FILENAME1 = "analysis.mc07pv06b.f8196.rho_." + BINNING + HISTO_VERSION + ".root";
    TString FILENAME2 = "analysis.data06pv06a." + BINNING + HISTO_VERSION + ".root";

    TFile   *f1 = new TFile(HISTO_PATH + "/" + FILENAME1, "read");
    TFile   *f2 = new TFile(HISTO_PATH + "/" + FILENAME2, "read");

    TH1F * h_mc = (TH1F*) f1 -> Get("fMc_pt_theta_pi");    
    TH1F * h_data = (TH1F*) f2 -> Get("fMc_pt_theta_pi");

    TH1F * h_ratio = (TH1F *) h_data -> Clone ("ratio");
    h_ratio -> Divide(h_mc);
    h_ratio -> Draw();
}

void helper1(TCanvas * c, TString bin, int pad1, TString variable) {
    TH1F * h_mc = (TH1F*) file -> Get(bin+"/pi_"+variable+"_ZTT/rho");
    TH1F * h_data = (TH1F*) file -> Get(bin+"/pi_"+variable+"_ZTT/data");
    c -> cd(pad1);
    h_mc -> Draw("hist");
    h_data -> Draw("same");
    h_mc -> SetFillColor(kYellow);

    c -> cd (++pad1);
    TH1F * h_ratio = (TH1F *) h_data -> Clone ("ratio");
    h_ratio -> Divide(h_mc);
    h_ratio -> Draw();
    h_ratio -> SetAxisRange(0, 5, "Y");

    TLine * line = new TLine(0, 1, 5, 1);
    line -> Draw("same");
    line -> SetLineStyle(2);
}

void pt_theta_reweighting_v2() {

    TCanvas * c = new TCanvas();
    c -> Divide (4,4);

    HISTO_PATH = getenv("HISTO_PATH");
    FILENAME = "merged." + BINNING + HISTO_VERSION + REMARK + ".root";
    file = new TFile(HISTO_PATH + "/" + FILENAME, "read");

    helper1(c, "bin1", 1, "pt");
    helper1(c, "bin2", 3, "pt");
    helper1(c, "bin3", 5, "pt");
    helper1(c, "bin4", 7, "pt");
    helper1(c, "bin5", 9, "pt");
    helper1(c, "bin6", 11, "pt");
    helper1(c, "bin7", 13, "pt");
}

void store_reweighting_histo () {
    HISTO_PATH = getenv("HISTO_PATH");
    FILENAME = "merged." + BINNING + HISTO_VERSION + REMARK + ".root";
    file = new TFile(HISTO_PATH + "/" + FILENAME, "read");

    TH1F * h_mc = (TH1F*) file -> Get(BIN+"/pi_pt_ZTT/rho");
    TH1F * h_data = (TH1F*) file -> Get(BIN+"/pi_pt_ZTT/data");
    TH1F * h_ratio = (TH1F *) h_data -> Clone ("ratio");
    h_ratio -> Divide(h_mc);

    TString DATABASE_PATH = getenv("DATABASE_PATH");
//  Note: commented out so that it's not overwritten by chance
//     TFile * file_out = new TFile (DATABASE_PATH + "/" + OUTPUT_FILENAME + ".root", "recreate");
//     file_out -> cd();
//     h_ratio -> Write();
//     file_out -> Close();

}

void phi_theta_reweighting_v2() {

    TCanvas * c = new TCanvas();
    c -> Divide (4,4);

    HISTO_PATH = getenv("HISTO_PATH");
    FILENAME = "merged." + BINNING + HISTO_VERSION + REMARK + ".root";
    file = new TFile(HISTO_PATH + "/" + FILENAME, "read");

    helper1(c, "bin1", 1, "phi");
    helper1(c, "bin2", 3, "phi");
    helper1(c, "bin3", 5, "phi");
    helper1(c, "bin4", 7, "phi");
    helper1(c, "bin5", 9, "phi");
    helper1(c, "bin6", 11, "phi");
    helper1(c, "bin7", 13, "phi");
}

