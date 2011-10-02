#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include <TPaveText.h>


TString     variable = "decay_length";
// Float_t     fit_range_low = -0.075;
// Float_t     fit_range_up = 0.075;
Float_t     fit_range_low = -0.2;
Float_t     fit_range_up = 0.2;


// TString     variable = "significance";
// Float_t     fit_range_low = -2;
// Float_t     fit_range_up = 2;

int significance_fit() {

    gStyle -> SetOptFit(1);
    
    TFile * f = new TFile("/data/zenith226a/libov/analysis/data/histo/merged.smearing.studies2.24.1.0405e06e07p.scaled.root", "read");
    //TFile * f = new TFile("/data/zenith226a/libov/analysis/data/histo/merged.smearing.studies2.24.4.0405e06e07p.scaled.root", "read");

    // bin1
    TCanvas * c1 = new TCanvas("c1", "bin1", 0, 0, 1000, 1000);
    c1 -> Divide(1,2);

    c1 -> cd(1);
    TH1F * h_bin1_data = (TH1F*) f->Get("bin1/"+variable+"/data");
    h_bin1_data -> Draw();
    h_bin1_data -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    TPaveText *pt1 = new TPaveText(-15.55588,439677.2,-9.175999,478471.9,"br");
    pt1->AddText("inclusive bin");
    pt1->Draw();

    c1 -> cd(2);
    TH1F * h_bin1_mc = (TH1F*) f->Get("bin1/"+variable+"/mc");
    h_bin1_mc -> Draw();
    h_bin1_mc -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    // bin2
    TCanvas * c2 = new TCanvas("c2", "bin2", 0, 0, 1000, 1000);
    c2 -> Divide(1,2);

    c2 -> cd(1);
    TH1F * h_bin2_data = (TH1F*) f->Get("bin2/"+variable+"/data");
    h_bin2_data -> Draw();
    h_bin2_data -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    TPaveText *pt2 = new TPaveText(-15.55588,439677.2,-9.175999,478471.9,"br");
    pt2->AddText("1.0 < #eta < 1.3");
    pt2->Draw("same");

    c2 -> cd(2);
    TH1F * h_bin2_mc = (TH1F*) f->Get("bin2/"+variable+"/mc");
    h_bin2_mc -> Draw();
    h_bin2_mc -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    // bin3
    TCanvas * c3 = new TCanvas("c3", "bin3", 0, 0, 1000, 1000);
    c3 -> Divide(1,2);

    c3 -> cd(1);
    TH1F * h_bin3_data = (TH1F*) f->Get("bin3/"+variable+"/data");
    h_bin3_data -> Draw();
    h_bin3_data -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    TPaveText *pt3 = new TPaveText(-15.55588,439677.2,-9.175999,478471.9,"br");
    pt3->AddText("1.3 < #eta < 1.6");
    pt3->Draw("same");

    c3 -> cd(2);
    TH1F * h_bin3_mc = (TH1F*) f->Get("bin3/"+variable+"/mc");
    h_bin3_mc -> Draw();
    h_bin3_mc -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    // bin4
    TCanvas * c4 = new TCanvas("c4", "bin4", 0, 0, 1000, 1000);
    c4 -> Divide(1,2);

    c4 -> cd(1);
    TH1F * h_bin4_data = (TH1F*) f->Get("bin4/"+variable+"/data");
    h_bin4_data -> Draw();
    h_bin4_data -> Fit("gaus", "", "", fit_range_low, fit_range_up);

    TPaveText *pt4 = new TPaveText(-15.55588,439677.2,-9.175999,478471.9,"br");
    pt4->AddText("1.6 < #eta < 2.2");
    pt4->Draw("same");

    c4 -> cd(2);
    TH1F * h_bin4_mc = (TH1F*) f->Get("bin4/"+variable+"/mc");
    h_bin4_mc -> Draw();
    h_bin4_mc -> Fit("gaus", "", "", fit_range_low, fit_range_up);


    return 0;
}
