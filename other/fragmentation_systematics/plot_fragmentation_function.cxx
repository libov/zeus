#include <TF1.h>
#include <TMath.h>
#include <TFile.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TLegend.h>

Double_t bowler(Double_t *x, Double_t *par) {

    // get function parameters
    Double_t    a = par[0];
    Double_t    b = par[1];
    Double_t    rQ = par[2];
    Double_t    m_hadr = par[3];
    Double_t    mQ = par[4];
    Double_t    pT_mean = par[5];
    Double_t    norm = par[6];

    // calculate transverse mass
    Double_t    mT = sqrt(m_hadr*m_hadr + pT_mean*pT_mean);

    // calculate function value
    Double_t    z = x[0];
    Double_t    f = norm*(1./(TMath::Power(z, 1.+rQ*b*mQ*mQ))) * TMath::Power(1.-z, a) * TMath::Exp((-1.)*b*mT*mT/z);

    return f;
}

Double_t peterson(Double_t *x, Double_t *par) {

    Double_t    eps = par[0];

    Double_t    z = x[0];

    Double_t    norm = par[1];

    Double_t    f = norm/(z * TMath::Power( ( 1. - (1./z) - (eps/(1-z)) ) , 2) );

    return f;
}

TF1 * plot_bowler() {

    // create a function
    TF1 * fcn = new TF1 ("bowler", bowler, 0, 1, 7);

    // settings specific for Bowler
    Double_t a = 0.3;
    Double_t b = 0.58;
    Double_t rQ = 1;
    Double_t m_hadr = 2.01;
    Double_t mQ = 1.5;
    Double_t pT_mean = 0.0;
    fcn -> SetParameters(a, b, rQ, m_hadr, mQ, pT_mean, 1);
    fcn -> SetParameter(6, 1./(fcn->Integral(0, 1)) );

    // cosmetics
    fcn -> SetLineColor(kBlack);
    fcn -> SetNpx(1000);

    fcn -> Draw("l");

    return fcn;
}

TF1 * plot_peterson(Double_t epsilon, unsigned color, unsigned style) {

    // for function-object name only - to allow multiple instances
    char tmp[256];
    sprintf(tmp, "%d", color);

    // create a function
    TF1 * fcn = new TF1 (tmp, peterson, 0, 1, 2);

    // set epsilon and the norm
    fcn -> SetParameters(epsilon, 1);
    fcn -> SetParameter(1, 1./(fcn->Integral(0, 1)));

    // cosmetics
    fcn -> SetLineColor(color);
    fcn -> SetLineStyle(style);

    fcn -> Draw("lsame");

    return fcn;
}

int plot_fragmentation_function () {

    // create a canvas
    TCanvas *c  = new TCanvas ("c","", 1200, 1200);
    gPad -> SetLeftMargin(0.12);

    // draw functions
    TF1 * bowler = plot_bowler();
    TF1 * peterson_1 = plot_peterson(0.052, 2, 10);
    TF1 * peterson_2 = plot_peterson(0.062, 3, 3);
    TF1 * peterson_3 = plot_peterson(0.072, 4, 9);

    // create a legend
    TLegend * legend = new TLegend (0.2, 0.6, 0.6, 0.95);
    legend -> AddEntry(bowler, "Bowler", "l");
    legend -> AddEntry(peterson_1, "Peterson, #epsilon = 0.052", "l");
    legend -> AddEntry(peterson_2, "Peterson, #epsilon = 0.062", "l");
    legend -> AddEntry(peterson_3, "Peterson, #epsilon = 0.072", "l");

    legend -> SetFillColor(0);
    legend -> Draw("same");

    // cosmetics
    TH1F * histo = bowler -> GetHistogram();
    histo -> SetAxisRange(0, 3.0,"Y");
    histo -> SetXTitle("z");
    histo -> SetYTitle("arbitrary units");
    histo -> SetTitleSize(0.05, "X");
    histo -> SetTitleSize(0.05, "Y");
    histo -> SetTitleOffset(1.1, "Y");

    // store the plot
    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c -> Print(PLOTS_PATH + "/fragmentation_functions.eps");

    return 0;
}
