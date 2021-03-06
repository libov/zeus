#include <TFile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1F.h>
#include <TF1.h>

#include <iostream>
using namespace std;

void fit(TString version="2.29.8", bool draw_variations = true) {

    TFile * file = new TFile ("scaling_factors_"+version+"/charm/etajet.root", "read");
    TCanvas * canv = (TCanvas*) file -> Get("CrossSection.etajetresults.full.forCHARM"+version+".0405e06e07p.v02.true05e06e0607p.xml");
    TPad * subpad = (TPad*) canv -> GetListOfPrimitives() -> At (0);
    TH1F * histo = (TH1F*) subpad -> GetPrimitive("etajet");
    histo -> SetYTitle("data/MC");
    histo -> SetTitleOffset(1.0, "X");
    histo -> SetTitleOffset(1.0, "Y");
    histo -> SetLabelSize(0.06, "X");
    histo -> SetLabelSize(0.06, "Y");

    histo -> Fit("pol2");

    TCanvas * c = new TCanvas ();
    c -> cd();
    subpad -> Draw();
    subpad -> cd();

    gPad -> SetBottomMargin(0.16);
    gPad -> SetRightMargin(0.05);
    gPad -> SetTopMargin(0.05);
    gPad -> SetLeftMargin(0.15);

    TF1 * fcn_up = new TF1 ("fcn_up", "pol2(0)", -1.6, 2.2);
    fcn_up -> SetParameters(1.16371, 0.135495, 0.15);
    fcn_up -> SetLineColor(kRed);
    fcn_up -> SetLineStyle(7);

    TF1 * fcn_down = new TF1 ("fcn_down", "pol2(0)", -1.6, 2.2);
    fcn_down -> SetParameters(1.16371, 0.135495, 0.05);
    fcn_down -> SetLineColor(kRed);
    fcn_down -> SetLineStyle(10);

    if (draw_variations) {
        fcn_up -> Draw("same");
        fcn_down -> Draw("same");
    }
}
