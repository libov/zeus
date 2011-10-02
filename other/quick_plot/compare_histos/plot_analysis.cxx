#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLine.h>

// choose a variable
//TString     variable = "significance_massbin3_mirrored";
//TString     variable = "significance_massbin2_mirrored";
//TString     variable = "significance_massbin1_mirrored";
//TString     variable = "significance";
//TString     variable = "vtxsec_multi";
//TString     variable = "kt_etjet_b";
//TString     variable = "vtxsec_mass";
//TString     variable = "zvtx";

// which versions to compare
TString     h1_version = "2.29.3";
TString     h2_version = "2.25.1";

// which binning files
TString     h1_binning = "full.forCHARM";
TString     h2_binning = "full.forCHARM";

// which sample

// version v06
//TString     sample="analysis.data06ev06a.";
//TString     sample="analysis.mc06ev06b.06e.q4.ari_.";
//TString     sample="analysis.mc06ev06b.bbbar.rg30.q2g1.bgf.";
//TString     sample="analysis.mc06ev06b.ccbar.rg30.q2g1.5.bgf.";
//TString     sample="analysis.mc06ev06b.rgap3.nc.ccdir.e.q2g4.";

// version v02
//TString     sample = "analysis.data06ev02d.";
//TString     sample = "analysis.mc05v02e.rgap3.nc.c.q2g1.5.";
//TString     sample = "analysis.mc05v02e.rgap3.nc.c.q2g4.";
TString     sample = "analysis.mc07pv02e.0607p.q4.ari_.";

int plot_analysis(TString variable = "significance", TString  bin="bin1") {

    // environment
    TString     HISTO_PATH = getenv("HISTO_PATH");
    
    // files with histograms
    TFile * f1 = new TFile (HISTO_PATH+"/"+sample+h1_binning+h1_version+".root", "read");
    TFile * f2 = new TFile (HISTO_PATH+"/"+sample+h2_binning+h2_version+".root", "read");

    // histograms
    TH1F * h1 = (TH1F*) f1 -> Get(bin+"/"+variable);
    TH1F * h2 = (TH1F*) f2 -> Get(bin+"/"+variable);

    // histogram settings
    h1 -> SetMarkerColor(kRed);
    h1 -> SetMarkerStyle(21);

    h2 -> SetMarkerColor(kBlue);
    h2 -> SetMarkerStyle(22);

    // create a canvas
    TCanvas * c1 = new TCanvas("c1", "", 1000, 800);
    c1 -> Divide(1, 2);

    // plot histograms
    c1 -> cd(1);
    gPad -> SetPad(0, 0.2, 1, 1);

    h1 -> Draw();
    h2 -> Draw("same");

    TLegend * leg = new TLegend (0.8,0.7,0.95,0.8);
    leg -> SetHeader(sample+"; "+ variable);
    leg -> AddEntry(h1, h1_version, "p");
    leg -> AddEntry(h2, h2_version, "p");
    leg -> Draw("same");

    // and ratio plot
    c1 -> cd(2);
    gPad -> SetPad(0, 0, 1, 0.2);
    TH1F * ratio = (TH1F*) h1 -> Clone("ratio");
    ratio -> Divide (h2);
    ratio -> SetAxisRange(0.9, 1.1, "Y");
    ratio -> Draw();

    TLine * line = new TLine (-100,1,100,1);
    line -> Draw();

    return 0;
}
