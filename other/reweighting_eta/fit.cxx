#include <TFile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TH1F.h>
#include <TF1.h>

#include <iostream>
using namespace std;

void fit() {

    TFile * file = new TFile ("scaling_factors_2.29.8/charm/etajet.root", "read");
    TCanvas * canv = (TCanvas*) file -> Get("CrossSection.etajetresults.full.forCHARM2.29.8.0405e06e07p.v02.true05e06e0607p.xml");
    TPad * subpad = (TPad*) canv -> GetListOfPrimitives() -> At (0);
    TH1F * histo = (TH1F*) subpad -> GetPrimitive("etajet");
    
    histo -> Fit("pol2");

    TCanvas * c = new TCanvas ();
    c -> cd();
    subpad -> Draw();

    TF1 * fcn = new TF1 ("fcn", "pol2(0)", -1.6, 2.2);
    fcn -> SetParameters(0.93704002, 0.10910299, 0.071548273);
    //fcn -> SetParameters(1.16371, 0.135495, 0.0888558);
    fcn -> SetLineColor(kBlue);
    fcn -> Draw("");
    cout << fcn -> Integral(-1.6, 2.2) / (2.2+1.6)<< endl;
    
}
