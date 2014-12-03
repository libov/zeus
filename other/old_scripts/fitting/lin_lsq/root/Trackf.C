/*************************************************************************
 * Statistics WS at DESY                                                 *
 * Repeated straight line track fits                                     *
 * Author: Olaf Behnke                                                   *
 *************************************************************************/
#include <stdlib>
#include "TGraphErrors.h"
#include  <TRandom1.h>
#include "TF1.h"
#include "TLine.h"
#include "TMath.h"

const Int_t Ntra=1000;
//const Int_t Ntra=1000;
const Int_t Ndet=10;
const Double_t yerr=0.02;
const Double_t yerr2=yerr*yerr;
const Double_t xmin = 0.5;
const Double_t xmax = xmin+Ndet;
const Double_t frac_noise=0.1;


void Trackf() {
// Random number initialisation
 TRandom *r1 = new TRandom1();

  // Book histo for fit chisquare and chisquare probability distributions
  TH1F *p0d    = new TH1F("p0d", "fitted p0",100, -0.2, 0.2);
  TH1F *chi2d  = new TH1F("chi2d", "chi2-distr.",100, 0., 5.*Ndet);
  TH1F *pchi2d = new TH1F("pchi2d", "prob(chi2) distr.",100, 0.,1.);

  // Book histo for fit chisquare and chisquare probability distributions
  // after iterating track fit with outlier rejection
  TH1F *p0d_iter    = new TH1F("p0d_iter", "fitted p0 iter",100, -0.2, 0.2);
  TH1F *chi2di_iter  = new TH1F("chi2d_iter", "chi2-distr. iter",100, 0., 5.*Ndet);
  TH1F *pchi2di_iter = new TH1F("pchi2d_iter", "prob(chi2) distr. iter",100, 0.,1.);


   gStyle->SetOptFit(1111);

  // Loop over track fits
  for ( Int_t itr=0; itr<Ntra; itr++){

  TH1F *a = new TH1F("a", "track",Ndet, xmin, xmax); 
  // Loop over detector hits
  for ( Int_t i=0; i<Ndet; i++){
 
  Double_t x;
  x = r1->Rndm(1);
  // Generate hits
  if (x>frac_noise) {
  x = r1->Gaus(0.,1.); // Signal hit
  }
  else {
  x = r1->Rndm(1); // Noise hit
  x = 10.*(-1.+2.*x); // Distribute noise hit over 10 sigma
  cout << "  Noise hit " << i+1 << " x = " << x << endl;
  }
  cout << "  i " << i+1 << " x  " << x << endl;
  a->SetBinContent(i+1,x*yerr);
  a->SetBinError(i+1,yerr);   
  }

  // Track fit with constant function
  TF1 *func = new TF1("func", "[0]", xmin, xmax );
  a->Fit("func");
  //cout << "chi2 = " << func->GetChisquare() << endl;
  Double_t p0   = func->GetParameter(0);
  Double_t chi2 = func->GetChisquare();
  Double_t pchi2 = func->GetProb();

  a->Draw();
  // if (pchi2>0.001) p0d->Fill(p0);
  p0d->Fill(p0);
  chi2d->Fill(chi2);
  pchi2d->Fill(pchi2);
  //cout << "  hello " << endl;

  // Second iteration
  // Loop over detector hits
  for ( Int_t i=0; i<Ndet; i++){
    // Get Hits back 
    x = a->GetBinContent(i+1);
    // cout << "2. iter  i = " << i+1 << "  x = " << x << endl;
    // Chisquare contribution of that hit  
    Double_t chi2_i = (p0-x)*(p0-x)/yerr2;
    // Downweight hits with large chisquare
    if (chi2_i>5) {
      //cout << "  Noise hit " << i+1 << " x = " << x << " chi2_i  " << chi2_i << endl;
       a->SetBinError(i+1,yerr*100);
    }
  }
  a->Fit("func");
  cout << "chi2 = " << func->GetChisquare() << endl;
  p0   = func->GetParameter(0);
  chi2 = func->GetChisquare();
  pchi2 = func->GetProb();    
  p0d_iter->Fill(p0);
  chi2d_iter->Fill(chi2);
  pchi2d_iter->Fill(pchi2);
  } 
}
