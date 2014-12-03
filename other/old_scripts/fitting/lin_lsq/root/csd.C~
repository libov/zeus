/**********************************************************************************
 * Statistics WS at DESY                                                          *
 * chi^2 distributin and p-value                                                  *
 * Author: Martin Goebel                                                          *
 **********************************************************************************/
#include "TMath.h"
#include "TString.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TF1.h"
#include <iostream>

using namespace std;

// define number of degree of freedom and chi^2 for p-value calcultion
const Int_t n_dof = 13;
const Double_t chi2 = 16.3;

void ChiSquareDistribution()
{
   // some sefintions for plotting
   gStyle->SetOptTitle(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   gStyle->SetPadTopMargin(0.07);
   gStyle->SetTitleW(.3);
   gStyle->SetTitleH(.05);
   gStyle->SetTitleY(1);
   gStyle->SetTitleX(0.1);

   TCanvas* c = new TCanvas( "c", "chi^2 Distribution", 0, 0, 1200, 800 );
   c->Divide(2,2);

   // ---------- chi^2 distribution for n_dof=1,2,3,4,5 -------------
   c->cd(1);
   // create and draw frame
   TH2F *frame1 = new TH2F("frame1", "#chi^{2} distribution", 1, 0, 15, 1, 0, 0.5 );
   frame1->SetXTitle("#chi^{2}");
   frame1->Draw();
   
   // create legend
   Float_t x0 = 0.62, dx = 0.20;
   Float_t y0 = 0.60, dy = 0.30;
   TLegend* legend = new TLegend( x0, y0, x0 + dx, y0 + dy );
   
   // loop over chi^2 distributions
   TF1 *chi2dist[5];
   for(Int_t indof = 1; indof < 6; indof++){
      chi2dist[indof-1] = new TF1( Form("chi2dist_%i",indof), chi2Dist, 0, 15, 1 );
      chi2dist[indof-1]->SetParameter(0, indof);
      chi2dist[indof-1]->SetLineColor(indof);
      chi2dist[indof-1]->Draw("same");
      legend->AddEntry(chi2dist[indof-1], Form("n_{dof}=%i",indof), "l");
   }
   // draw legend
   legend->Draw();
   frame1->Draw("sameaxis");
  
   // ---------- chi^2 distribution for n_dof=10,20,30,40,50 ----------
   c->cd(2);
   // create and draw frame
   TH2F *frame2 = new TH2F("frame2", "#chi^{2} distribution", 1, 0, 80, 1, 0, 0.1 );
   frame2->SetXTitle("#chi^{2}");
   frame2->Draw();

   // legend
   legend = new TLegend( x0, y0, x0 + dx, y0 + dy );
   
   // loop over chi^2 distributions
   for(Int_t indof = 1; indof < 6; indof++){
      chi2dist[indof-1] = new TF1("rchi2dist_10*" + 10*indof, chi2Dist, 0, 80, 1);
      chi2dist[indof-1]->SetParameter(0, 10.*indof);
      chi2dist[indof-1]->SetLineColor(indof);
      chi2dist[indof-1]->Draw("same");
      legend->AddEntry(chi2dist[indof-1], Form("n_{dof}=%i",10*indof), "l");
   }
   // draw legend
   legend->Draw();
   frame2->Draw("sameaxis");

   // ---------- chi^2/n_dof distribution for n_dof=1,2,3,4,5 ---------
   c->cd(3);
   // create and draw frame
   TH2F *frame3 = new TH2F("frame3", "#chi^{2}/n_{dof} distribution", 1, 0, 3, 1, 0, 0.5 );
   frame3->SetXTitle("#chi^{2}/n_{dof}");
   frame3->Draw();
   
   // legend
   legend = new TLegend( x0, y0, x0 + dx, y0 + dy );
   
   // loop over chi^2/n_dof distributions
   TF1 *chi2OverNdist[5];
   for(Int_t indof = 1; indof < 6; indof++){
      chi2OverNdist[indof-1] = new TF1( Form("chi2OverNdist_%i",indof), chi2OverNdofDist, 0, 6, 1 );
      chi2OverNdist[indof-1]->SetParameter(0, indof);
      chi2OverNdist[indof-1]->SetLineColor(indof);
      chi2OverNdist[indof-1]->Draw("same");
      legend->AddEntry(chi2OverNdist[indof-1], Form("n_{dof}=%i",indof), "l");
   }
   // draw legend
   legend->Draw();
   frame3->Draw("sameaxis"); 
 
   // ---------- chi^2/n_dof distribution for n_dof=10,20,30,40,50 ----
   c->cd(4);
   // create and draw frame
   TH2F *frame4 = new TH2F("frame4", "#chi^{2}/n_{dof} distribution", 1, 0, 3, 1, 0, 0.1 );
   frame4->SetXTitle("#chi^{2}/n_{dof}");
   frame4->Draw();
   
   // legend
   legend = new TLegend( x0, y0, x0 + dx, y0 + dy );
      
   // loop over chi^2/n_dof distributions
   for(Int_t indof = 1; indof < 6; indof++){
      chi2OverNdist[indof-1] = new TF1( Form("chi2OverNdist_%i",10*indof), chi2OverNdofDist, 0, 6, 1 );
      chi2OverNdist[indof-1]->SetParameter(0, 10*indof);
      chi2OverNdist[indof-1]->SetLineColor(indof);
      chi2OverNdist[indof-1]->Draw("same");
      legend->AddEntry(chi2OverNdist[indof-1], Form("n_{dof}=%i",10*indof), "l");
   }  
   // draw legend
   legend->Draw();
   frame4->Draw("sameaxis");
   
   // -------------------- calculation of p-value ---------------------
   TCanvas* c2 = new TCanvas( "c2", "p-value", 0, 0, 1200, 400 );
   c2->Divide(2,1);
   
   // -------------------- chi^2 distribution -------------------------
   c2->cd(1);
   // create function
   TF1 *chi2pvalue = new TF1( "chi2pvalue", chi2Dist, 0, 100, 1 );
   chi2pvalue->SetParameter(0, n_dof);
   Double_t max = chi2pvalue->GetMaximum(0,1000);
  
   // create and draw frame
   TH2F *frame5 = new TH2F("frame5", "#chi^{2}: p-value", 1, 0, 3*n_dof, 1, 0, max );
   frame5->SetXTitle("#chi^{2}");
   frame5->Draw();
   
   // draw distribution
   chi2pvalue->Draw("same");

   // draw p-value (integral) area, from chi^2 to infinitty (here: 10000)
   TF1 *chi2Integral = new TF1( "chi2Integral", chi2Dist, chi2, 10000, 1 );
   chi2Integral->SetParameter(0, n_dof);
   chi2Integral->SetFillColor(2);
   chi2Integral->SetFillStyle(3004);
   chi2Integral->Draw("same");

   // compute integral
   Double_t pvalue = chi2pvalue->Integral(chi2, 10000);
   // compute also Prob-value, should be the same
   Double_t prob   = TMath::Prob(chi2, n_dof);

   // draw legend
   TLatex *text1 = new TLatex(0.6*frame5->GetXaxis()->GetXmax(),0.88*max,
                              Form("#chi^{2}/n_{dof} = %3.1f / %i", chi2, n_dof));
   TLatex *text2 = new TLatex(0.6*frame5->GetXaxis()->GetXmax(),0.78*max,
                              Form("p-value = %1.3f", pvalue));
   TLatex *text3 = new TLatex(0.6*frame5->GetXaxis()->GetXmax(),0.68*max,
                              Form("Prob(.) = %1.3f", prob));
   
   text1->AppendPad();
   text2->SetTextColor(2);
   text2->AppendPad();
   text3->AppendPad();
 
   // re-draw axes
   frame5->Draw("sameaxis");

   // -------------------- chi^2/n_dof distribution --------------------
   c2->cd(2);
   // create function
   TF1 *chi2OverNpvalue = new TF1( "chi2OverNpvalue", chi2OverNdofDist, 0, 100, 1 );
   chi2OverNpvalue->SetParameter(0, n_dof);
      
   // create and draw frame
   TH2F *frame6 = new TH2F("frame6", "#chi^{2}/n_{dof}: p-value", 1, 0, 3, 1, 0, max );
   frame6->SetXTitle("#chi^{2}/n_{dof}");
   frame6->Draw();
   
   // draw distribution
   chi2OverNpvalue->Draw("same");

   // draw p-value (integral) area, from chi^2/n_dof to infinitty (here: 100)
   TF1 *chi2OverNIntegral = new TF1( "chi2OverNIntegral", chi2OverNdofDist, chi2/n_dof, 100, 1 );
   chi2OverNIntegral->SetParameter(0, n_dof);
   chi2OverNIntegral->SetFillColor(2);
   chi2OverNIntegral->SetFillStyle(3004);
   chi2OverNIntegral->Draw("same");

   // draw legend
   text1 = new TLatex(0.6*frame6->GetXaxis()->GetXmax(),0.88*max,
                              Form("#chi^{2}/n_{dof} = %3.1f / %i", chi2, n_dof));
   text2 = new TLatex(0.6*frame6->GetXaxis()->GetXmax(),0.78*max,
                              Form("p-value = %1.3f", pvalue));
   text3 = new TLatex(0.6*frame6->GetXaxis()->GetXmax(),0.68*max,
                              Form("Prob(.) = %1.3f", prob));
   
   text1->AppendPad();
   text2->SetTextColor(2);
   text2->AppendPad();
   text3->AppendPad();
   
   // re-draw axes
   frame6->Draw("sameaxis");
   
}

// chi^2 distribution is function of chi^2 and n_dof
Double_t chi2Dist(Double_t *x, Double_t *par)
{
   Double_t ndof = par[0];
   Double_t chi2 = x[0];

   return 1./( TMath::Power(2.,ndof/2.)*TMath::Gamma(ndof/2.) )
      *TMath::Power(chi2,ndof/2.-1)*TMath::Exp(-chi2/2.);
}

// chi^2/n_dof distribution is function of chi^2 and n_dof
Double_t chi2OverNdofDist(Double_t *x, Double_t *par)
{
   Double_t ndof = par[0];
   Double_t chi2 = x[0]*ndof;

   return 1./( TMath::Power(2.,ndof/2.)*TMath::Gamma(ndof/2.) )
      *TMath::Power(chi2,ndof/2.-1)*TMath::Exp(-chi2/2.);
}
