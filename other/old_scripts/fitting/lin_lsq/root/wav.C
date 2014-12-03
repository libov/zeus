
/**********************************************************************************
 * Statistics WS at DESY                                                          *
 * Determine world average of M(W)                                                *
 * by chisquare fit with a constant function                                      *
 * (and alternatively by calculating directly the weighted average)
 * Author: Olaf Behnke                                                            *
 **********************************************************************************/
#include <stdlib>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLine.h"
#include "TMath.h"

//const Double_t xmin = -4.;
//const Double_t xmax =  8.;

//using namespace std;


// M(W) measurements and corresponding errors
const Int_t N=5;
//                    CDF-I   D0-I    CDF-II  LEP-II  NuTeV
Float_t val_MW[N] = { 80.436, 80.478, 80.413, 80.376, 80.136 };
Float_t err_MW[N] = {  0.081,  0.083,  0.048,  0.033,  0.084 };


void wav()
{

  const Double_t xmin = 0.5;
  const Double_t xmax = xmin+N; 

  // Initialise weighted average:
  Double_t Gi = 0;
  Double_t Gsum = 0;
  Double_t Asum = 0;

  TH1F *mw = new TH1F("mw", "M(W)",N, xmin, xmax);

   // Fill histogram with measurements
  for ( Int_t i=0; i<N; i++){
   cout << "  i = " << i  << endl;
   cout << "  val = " << val_MW[i]  << endl;
   mw->SetBinContent(i+1,val_MW[i]);
   mw->SetBinError(i+1,err_MW[i]);
   // Weighted average: Accumulate info
   Gi = 1./err_MW[i]**2;
   Gsum += Gi;   
   Asum += Gi*val_MW[i];
  }
   // Weighted average: Obtain final result
  Double_t wav = Asum/Gsum;  
  Double_t wav_err = sqrt(1./Gsum);
  cout << "  wav = " << wav  << "+- " << wav_err << endl;  

  // Plot histogram
  // Histogram nice style
  mw->SetMarkerStyle(20);
  mw->SetMarkerColor(2);
  mw->SetLineWidth(2);
  mw->SetLineColor(2);
  mw->Draw("ap");
  mw-> SetMinimum(80.0);
  mw-> SetMaximum(80.8);
  mw->Draw();

 // Fit with constant function
  // make fit box nice
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  gStyle->SetStatX(0.46);
  gStyle->SetStatY(0.94);
  gStyle->SetStatW(0.17);
  TF1 *func = new TF1("func", "[0]", xmin, xmax );
  mw->Fit("func");
}
