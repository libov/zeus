// a small script to reweight ET distribution, V. Libov, DESY, 19 March 2011

// ROOT includes
#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>

// my includes
//#include <THistogram.h>

// global variable: name of the database file where
// weighting factors will be stored;
// here just for better visibility
// NOTE: depending on the chosen storage method (ROOT histo or XML)
// the extension will be different (.root or .xml respectively);
// the location stays the same: $DATABASE_PATH
TString     et_reweighting_dbase = "ET_reweighting_LF";

// main function
//int main() {
int reweight_et() {

    TString HISTO_PATH = getenv("HISTO_PATH");
    TFile *file = new TFile (HISTO_PATH + "/merged.full.forCHARM2.1scaled.root");
    
    TH1F * histo_DATA = (TH1F*) file -> Get("bin1/kt_etjet_b/data");
    TH1F * histo_LF = (TH1F*) file -> Get("bin1/kt_etjet_b/light");
    TH1F * histo_BEAUTY = (TH1F*) file -> Get("bin1/kt_etjet_b/beauty");
    TH1F * histo_CHARM = (TH1F*) file -> Get("bin1/kt_etjet_b/charm");
    TH1F * histo_MC = (TH1F*) file -> Get("bin1/kt_etjet_b/mc");

    histo_LF -> SetLineColor(kRed);
    histo_BEAUTY -> SetLineColor(kBlue);
    histo_CHARM -> SetLineColor(kGreen);
    histo_MC -> SetLineColor(kYellow);

    histo_DATA -> SetMarkerStyle(20);
    histo_MC -> SetLineWidth(2);

    histo_DATA -> Draw();
    histo_LF -> Draw("sameHIST");
    histo_BEAUTY -> Draw("sameHIST");
    histo_CHARM -> Draw("sameHIST");
    histo_MC -> Draw("sameHIST");

    gROOT -> GetListOfCanvases()->Print("00_before_reweighting.png");

    // histogram to keep data with substracted beauty and charm
    TH1F * histo_substr = (TH1F*) histo_DATA -> Clone("histo_substr");
    histo_substr -> Add(histo_BEAUTY, -1);
    histo_substr -> Add(histo_CHARM, -1);
    histo_substr -> Draw();
    gROOT -> GetListOfCanvases()->Print("01_data_subst_b_c.png");

    histo_substr -> Divide(histo_LF);
    histo_substr -> Draw();
    gROOT -> GetListOfCanvases()->Print("02_weighting_function.png");

    TH1F *  histo_LF_reweighted = (TH1F*) histo_LF -> Clone("03_LF_reweighted");
    histo_LF_reweighted -> Multiply(histo_substr);
    histo_LF_reweighted -> Draw();
    gROOT -> GetListOfCanvases()->Print("03_LF_reweighted.png");

    TH1F * histo_MC_reweighted = (TH1F*) histo_LF_reweighted -> Clone("mc_reweighted");
    histo_MC_reweighted -> Add(histo_BEAUTY);
    histo_MC_reweighted -> Add(histo_CHARM);

    histo_LF_reweighted -> SetLineColor(kRed);
    histo_MC_reweighted -> SetLineColor(kYellow);

    histo_DATA -> Draw();
    histo_LF_reweighted -> Draw("sameHIST");
    histo_BEAUTY -> Draw("sameHIST");
    histo_CHARM -> Draw("sameHIST");
    histo_MC_reweighted -> Draw("sameHIST");
    
    gROOT -> GetListOfCanvases()->Print("04_after_reweighting.png");

   

    // now store the reweighting function in order to not bothering with parametrization, doing simple
    // bin-by-bin correction, hence storing simply a weighting factor for each bin to an XML file
    // NOTE: this assumes that binning in ET distribution is the same all the time

    // TH1F variant
    TString DATABASE_PATH = getenv("DATABASE_PATH");
    
    TFile   * out_file = new TFile (DATABASE_PATH+"/"+et_reweighting_dbase+".root", "recreate");
    out_file -> cd();
    histo_substr -> SetDirectory(gDirectory);
    histo_substr -> Write();
    out_file -> Close();

    /*
    // XML variant
    // open the file; the filename is given at the beginning of this file
    THistogram  weighting_histogram(XML_et_reweighting_dbase);
    
    // write a structure to the same file
    weighting_histogram.WriteXMLfile(XML_et_reweighting_dbase);
    */


    

    // finished successfully
    return 0;
}

