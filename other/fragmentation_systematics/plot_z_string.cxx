// ROOT includes
#include <TFile.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>

#include <iostream>

// main function
int plot_z_string() {

    // cosmetics
    gStyle -> SetOptStat(0);

    // settings
    TString    VARIABLE = "string";
    bool       scale = true;
    bool       isCharm = true;

    TString PATH = "/data/zenith226a/libov/data/other/fragmentation_systematics/histograms";

    // open ROOT files
    TFile   *f_default;
    TFile   *f_peterson_0052;
    TFile   *f_peterson_0062;
    TFile   *f_peterson_0072;
    TFile   *f_actual;

    // this is for CHARM
    if (isCharm) {
        f_default = new TFile (PATH+"/charm/analysis.mc04v02ecpz424.f15643.ccbar.rg30.q2g1.5.bgf.full.forCHARM.DEFAULT.root", "read");	
        f_peterson_0052 = new TFile (PATH+"/charm/analysis.mc04v02ecpz424.f15643.ccbar.rg30.q2g1.5.bgf.full.forCHARM.PETERSON_0052.root", "read");	
        f_peterson_0062 = new TFile (PATH+"/charm/analysis.mc04v02ecpz424.f15643.ccbar.rg30.q2g1.5.bgf.full.forCHARM.PETERSON_0062.root", "read");	
        f_peterson_0072 = new TFile (PATH+"/charm/analysis.mc04v02ecpz424.f15643.ccbar.rg30.q2g1.5.bgf.full.forCHARM.PETERSON_0072.root", "read");

        f_actual = new TFile (PATH+"/charm/analysis.mc06ev02eccbar.rg30.q2g1.5.bgf.full.forCHARM.FRAGMENTATION.DEFAULT.root", "read");
    } else {

        // this is for beauty
        f_default = new TFile (PATH+"/beauty/analysis.mc04v02ecpz424.f13695.rgap3.nc.b.q2g1..full.forCHARMRGAP.DEFAULT.root", "read");	
        f_peterson_0052 = new TFile (PATH+"/beauty/analysis.mc04v02ecpz424.f13695.rgap3.nc.b.q2g1..full.forCHARMRGAP.PETERSON_00026.root", "read");	
        f_peterson_0062 = new TFile (PATH+"/beauty/analysis.mc04v02ecpz424.f13695.rgap3.nc.b.q2g1..full.forCHARMRGAP.PETERSON_00041.root", "read");	
        f_peterson_0072 = new TFile (PATH+"/beauty/analysis.mc04v02ecpz424.f13695.rgap3.nc.b.q2g1..full.forCHARMRGAP.PETERSON_00056.root", "read");

        f_actual = new TFile (PATH+"/beauty/analysis.mc05v02e.rgap3.nc.b.q2g1.e..full.forCHARMFRAGMENTATION.DEFAULT.root", "read");
    }

    // get relevant histograms
    TH1F *h_z_peterson_0052 = (TH1F*) f_peterson_0052 -> Get ("bin1/z_true_"+VARIABLE);
    TH1F *h_z_peterson_0062 = (TH1F*) f_peterson_0062 -> Get ("bin1/z_true_"+VARIABLE);
    TH1F *h_z_peterson_0072 = (TH1F*) f_peterson_0072 -> Get ("bin1/z_true_"+VARIABLE);
    TH1F *h_z_actual = (TH1F*) f_actual -> Get ("bin1/z_true_"+VARIABLE);
    // not used, just as a cross-check
    TH1F *h_z_default = (TH1F*) f_default -> Get ("bin1/z_true_"+VARIABLE);

    // cosmetics
    // binning
    h_z_peterson_0052 -> Rebin(5);
    h_z_peterson_0062 -> Rebin(5);
    h_z_peterson_0072 -> Rebin(5);
    h_z_actual -> Rebin(5);
    h_z_default -> Rebin(5);

    // line properties
    h_z_peterson_0052 -> SetLineColor(2);
    h_z_peterson_0062 -> SetLineColor(3);
    h_z_peterson_0072 -> SetLineColor(4);
    h_z_actual -> SetLineColor(1);
    h_z_default -> SetLineColor(5);

    h_z_peterson_0052 -> SetLineWidth(2);
    h_z_peterson_0062 -> SetLineWidth(2);
    h_z_peterson_0072 -> SetLineWidth(2);
    h_z_actual -> SetLineWidth(2);
    h_z_default -> SetLineWidth(2);

    h_z_peterson_0052 -> SetLineStyle(10);
    h_z_peterson_0062 -> SetLineStyle(3);
    h_z_peterson_0072 -> SetLineStyle(9);

    TCanvas * c1 = new TCanvas ("c1", "", 0, 0, 700, 700);
    TCanvas * c2 = new TCanvas ("c2", "", 0, 0, 700, 700);

    if (scale) {
        Double_t integral_default = h_z_default -> Integral();
        Double_t integral_peterson_0052 = h_z_peterson_0052 -> Integral();
        Double_t integral_peterson_0062 = h_z_peterson_0062 -> Integral();
        Double_t integral_peterson_0072 = h_z_peterson_0072 -> Integral();
        Double_t integral_actual =  h_z_actual -> Integral();

        h_z_peterson_0052 -> Scale (integral_peterson_0062 / integral_peterson_0052 );
        h_z_peterson_0072 -> Scale (integral_peterson_0062 / integral_peterson_0072 );
        h_z_default -> Scale (integral_peterson_0062 / integral_default );
        h_z_actual -> Scale (integral_peterson_0062 / integral_actual );
    }

    c1 -> cd();
    h_z_peterson_0052 -> Draw("HIST");
    h_z_peterson_0062 -> Draw("HISTsame");
    h_z_peterson_0072 -> Draw("HISTsame");
    h_z_actual -> Draw("HISTsame");
    //h_z_default -> Draw("HISTsame");

    gPad -> SetLeftMargin(0.15);
    h_z_peterson_0052 -> SetAxisRange(0, 0.99, "X");
    h_z_peterson_0052 -> SetXTitle("z_{hadr}");
    h_z_peterson_0052 -> SetYTitle("Entries");
    h_z_peterson_0052 -> SetTitleSize(0.05, "X");
    h_z_peterson_0052 -> SetTitleSize(0.05, "Y");
    h_z_peterson_0052 -> SetTitleOffset(1.6, "Y");
    h_z_peterson_0052 -> SetTitleOffset(0.9, "X");

    c2 -> cd();

    TH1F * h_z_peterson_0052_div = (TH1F *)h_z_peterson_0052 -> Clone();
    TH1F * h_z_peterson_0072_div = (TH1F *)h_z_peterson_0072 -> Clone();
    TH1F * h_z_default_div = (TH1F *)h_z_default -> Clone();
    TH1F * h_z_peterson_0062_div = (TH1F *)h_z_peterson_0062 -> Clone("reweighting");
    TH1F * h_z_actual_div = (TH1F *)h_z_actual -> Clone();

    h_z_peterson_0052_div -> Divide(h_z_actual_div);
    h_z_peterson_0072_div -> Divide(h_z_actual_div);
    h_z_default_div -> Divide(h_z_actual_div);
    h_z_peterson_0062_div -> Divide(h_z_actual_div);
    h_z_actual_div -> Divide(h_z_actual_div);

    h_z_peterson_0052_div -> Draw("HIST");
    h_z_peterson_0062_div -> Draw("HISTsame");
    h_z_peterson_0072_div -> Draw("HISTsame");
    h_z_actual_div -> Draw("HISTsame");
    //h_z_default_div -> Draw("HISTsame");

    gPad -> SetLeftMargin(0.15);
    h_z_peterson_0052_div -> SetYTitle("MC / Bowler");
    h_z_peterson_0052_div -> SetAxisRange(0, 2.8, "Y");

    TLegend * legend = new TLegend(0.2, 0.7, 0.55, 0.95);
    legend -> AddEntry(h_z_actual, "Bowler (default)", "l");
    if (isCharm) {
        legend -> AddEntry(h_z_peterson_0052, "Peterson, #epsilon = 0.052", "l");
        legend -> AddEntry(h_z_peterson_0062, "Peterson, #epsilon = 0.062", "l");
        legend -> AddEntry(h_z_peterson_0072, "Peterson, #epsilon = 0.072", "l");
    } else {
        legend -> AddEntry(h_z_peterson_0052, "Peterson, #epsilon = 0.0026", "l");
        legend -> AddEntry(h_z_peterson_0062, "Peterson, #epsilon = 0.0041", "l");
        legend -> AddEntry(h_z_peterson_0072, "Peterson, #epsilon = 0.0056", "l");
    }
    c1 -> cd();
    legend -> SetFillColor(0);
    legend -> Draw("same");

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c1 -> Print(PLOTS_PATH+"/z_string.eps");
    c2 -> Print(PLOTS_PATH+"/z_string_ratio.eps");

//     TFile * output_file = new TFile ("bowler_to_peterson_zstring_BEAUTY.root", "recreate");
//     h_z_peterson_0062_div -> SetDirectory(output_file);
//     h_z_peterson_0062_div -> Write();
//     output_file -> Close();
    return 0;
}
