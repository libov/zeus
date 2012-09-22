#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <TText.h>
#include <TLine.h>

#include <iostream>

// settings
TString     variable = "significance";
TString     bin = "bin3";
bool        gSame=false;

//TString     binning = "smearing.studies";
TString     binning = "full.forCHARM";
//TString     binning = "full";
int         rebin = 1;

bool    highest_eta (TString str) {
    if ((str == "2.24.15") || (str == "2.24.16") || (str == "2.24.17") || (str == "2.24.18")|| (str == "2.24.19")) return true;
    return false;
}

void plot(TString version, TString type) {

    gStyle -> SetOptStat(0);

    TString     HISTO_PATH = getenv("HISTO_PATH");

    TFile * f;

    if ( highest_eta(version) ) binning = "highest.eta";
    if ( highest_eta(version) ) bin="bin1";


    f = new TFile (HISTO_PATH+"/merged."+binning+version+".0405e06e07p.scaled.root", "read");

    TH1F * h_data = (TH1F*) f -> Get(bin+"/"+variable+"/data");
    TH1F * h_mc = (TH1F*) f -> Get(bin+"/"+variable+"/mc");

    h_data -> Rebin(rebin);
    h_mc -> Rebin(rebin);

    TH1F * h_ratio = (TH1F*) h_data -> Clone("ratio");

    h_ratio -> Divide(h_mc);

    h_ratio -> SetYTitle("#frac{data}{MC}");
    h_ratio -> SetXTitle("S=L_{xy}/#sigma(L_{xy})");

    if (gSame) h_ratio -> Draw("same");
    else  h_ratio -> Draw();
    h_ratio -> SetAxisRange(0.8, 1.3 ,"Y");
    h_ratio -> SetMarkerStyle(21);
    h_ratio -> SetMarkerSize(0.7);
    h_ratio -> SetMarkerColor(kRed);
    if (gSame) h_ratio -> SetMarkerColor(kBlue);

    TLine * line = new TLine (-20, 1, 20, 1);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line -> Draw();

    TPaveText *pt = new TPaveText(-6, 0.8, 6, 0.85,"br");
    pt->SetFillColor(19);
    TText *text = pt->AddText(type);
    pt->Draw();

    TString     outfile = version+".png";
    //gROOT -> GetListOfCanvases() -> Print (outfile.Data());
}

void plot2(TString version1, TString version2, TString type) {

    gStyle -> SetOptStat(0);

    TString     HISTO_PATH = getenv("HISTO_PATH");
    
    TFile * f1;
    TFile * f2;

    TString binning1 = binning;
    TString binning2 = binning;
    
    if ( highest_eta(version1) ) binning1 = "highest.eta";
    if ( highest_eta(version2) ) binning2 = "highest.eta";

    TString bin1 = bin;
    TString bin2 = bin;

    if ( highest_eta(version1) ) bin1="bin1";
    if ( highest_eta(version2) ) bin2="bin1";

    f1 = new TFile (HISTO_PATH+"/merged."+binning1+version1+".0405e06e07p.scaled.root", "read");
    f2 = new TFile (HISTO_PATH+"/merged."+binning2+version2+".0405e06e07p.scaled.root", "read");

    TH1F * h1;
    TH1F * h2;

    h1 = (TH1F*) f1 -> Get(bin1+"/"+variable+"/mc");
    h2 = (TH1F*) f2 -> Get(bin2+"/"+variable+"/mc");

    h1-> Rebin(rebin);
    h2-> Rebin(rebin);

    TH1F * h_ratio = (TH1F*) h1 -> Clone("ratio");
    h_ratio -> Divide(h2);
    h_ratio -> SetYTitle("#frac{MC smeared}{MC unsmeared}");
    h_ratio -> SetXTitle("S=L_{xy}/#sigma(L_{xy})");


    if (gSame) h_ratio -> Draw("same");
    else  h_ratio -> Draw();
    h_ratio -> SetAxisRange(0.8, 1.3 ,"Y");
    h_ratio -> SetMarkerStyle(20);

    TLine * line = new TLine (-20, 1, 20, 1);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line -> Draw();

    TPaveText *pt = new TPaveText(-6, 0.8, 6, 0.9,"br");
    pt->SetFillColor(19);
    TText *text = pt->AddText(type);
    pt->Draw("same");
}

// main function
int plot_data_vs_MC(Int_t   bin_nr=4) {

    char tmp[256];
    sprintf (tmp, "%d", bin_nr);
    TString title(tmp);
    bin = "bin"+title;

/*    plot("2.24.5", "");
    gSame = true;
    plot2("2.24.16", "2.24.5", "");*/
    //plot("2.24.17", "");

//     plot("2.24.4", "");
//     gSame = true;
//     plot2("2.24.5", "2.24.4", "");
//     plot("2.24.5", "bin"+title);
    TString eta;
    if (bin_nr==2) eta = "-1.6 < #eta < -1.1";
    if (bin_nr==3) eta = "-1.1 < #eta < -0.8";
    if (bin_nr==4) eta = "-0.8 < #eta < -0.5";
    if (bin_nr==5) eta = "-0.5 < #eta < -0.2";
    if (bin_nr==6) eta = "-0.2 < #eta < 0.1";
    if (bin_nr==7) eta = "0.1 < #eta < 0.4";
    if (bin_nr==8) eta = "0.4 < #eta < 0.7";
    if (bin_nr==9) eta = "0.7 < #eta < 1.0";
    if (bin_nr==10) eta = "1.0 < #eta < 1.3";
    if (bin_nr==11) eta = "1.3 < #eta < 1.6";
    if (bin_nr==12) eta = "1.6 < #eta < 2.2";

    // before the correction
    //plot("2.21.1", eta);
    
    // after the correction (dlen shift)
    plot("2.25.1", eta);
    //plot("2.26.1", "2.26.1, bin"+title);
    
    
    return 0;
}

