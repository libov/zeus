#include <TH1F.h>
#include <TRandom3.h>
#include <TStyle.h>

#include <iostream>
using namespace std;

Int_t       N_POINTS=10000000;
Double_t    Sigma = 0.36;   // default PYTHIA

int random_test () {

    TH1F    * hpx = new TH1F("","", 1000, -10, 10);
    TH1F    * hpy = new TH1F("","", 1000, -10, 10);
    TH1F    * hpT = new TH1F("","", 1000, -10, 10);
    TH1F    * hmT = new TH1F("","", 1000, -10, 10);

    TRandom3 rand;

    for (int i=0; i<N_POINTS; i++) {
        if (i % 100000 == 0) cout << " Processing " << i << endl;
        Double_t    px = rand.Gaus(0, Sigma);
        Double_t    py = rand.Gaus(0, Sigma);
        Double_t    pT = sqrt(px*px + py*py);
        Double_t    mT = sqrt(2.01*2.01 + pT*pT);
        
        hpx -> Fill(px);
        hpy -> Fill(py);
        hpT -> Fill(pT);
        hmT -> Fill(mT);
    }

    //hpx -> Draw();
    hpy -> SetLineColor(kRed);
    //hpy -> Draw("same");
    hpT -> SetLineColor(kBlue);
    //hpT -> Draw();

    hmT -> Draw();

    //hpx -> Fit("gaus", "+", "", -5, 5);
    gStyle->SetOptFit(1);
    
    return 0;
}
