
/**********************************************************************************
 * Statistics WS at DESY                                                          *
 * mean of W boson mass                                                           *
 * correlation between measurements are not taken into account                    *
 * Author: Martin Goebel                                                          *
 **********************************************************************************/
#include "TMinuit.h"
#include "TMath.h"
#include <stdlib>

using namespace std;

// include NuTeV?
Bool_t inclNuTeV = kTRUE;

// measurements and corresponding errors 
//                    CDF-I   D0-I    CDF-II  LEP-II  NuTeV
Double_t val_MW[] = { 80.436, 80.478, 80.413, 80.376, 80.136 };
Double_t err_MW[] = {  0.081,  0.083,  0.048,  0.033,  0.084 };

// number of measurements (values)
Int_t nVals = 0;

// minimal chi2
Double_t chi2Min = 1000;

void AverageMW()
{
   // include NuTeV?
   if( inclNuTeV ) nVals = 5;
   else            nVals = 4;

   // number of parameters
   const int npar = 1;
   
   // create minuit pointer
   TMinuit *minuit = new TMinuit( npar );
   
   // set FCN function
   minuit->SetFCN( &fcn );
 
   // -1=quiet, 0=normal, 1=verbose
   minuit->SetPrintLevel( 0 );

   // start values
   Double_t startVal = 80;
   Double_t fitStep  = 0.1;
   Double_t limitMin = 70;
   Double_t limitMax = 90;
   minuit->DefineParameter( 0, "MW", startVal, fitStep, limitMin, limitMax);

   // minimize with MIGRAD
   Int_t ierr = 0;
   Double_t args[2];
   args[0] = 0; // maximum function calls (0=default)
   args[1] = 0; // tolerance at minimum (0=default)
   minuit->mnexcm( "MIGrad", args, 2, ierr );
   if ( ierr != 0 )
      cout << "Warning: Maybe fit didn't converge!" << endl;

   // fit results
   Double_t fitval_MW[1], fiterr_MW[1]; 
   minuit->GetParameter( 0, fitval_MW[0], fiterr_MW[0] );

   cout << "\n\n*************************************************" << endl;
   cout << "          chi2Min = " << chi2Min  << endl;
   cout << "          n_dof   = " << nVals-1  << endl;
   cout << "          p-value = " << TMath::Prob(chi2Min, nVals-1)  << endl;
   cout << "          MW      = " << fitval_MW[0] << " +- " << fiterr_MW[0] << endl;
   cout << "*************************************************" << endl;

   // make plot
   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   TCanvas* c = new TCanvas( "c", "Mean of W boson mass", 0, 0, 850, 500 );
   c->SetGridy();
   TH2F *frame = new TH2F("frame", "Mean of W boson mass", 1, 80, 80.6, 5, 0, 5. );
   frame->SetLineColor(0);
   frame->SetTickLength(0,"Y");
   frame->SetXTitle("M_{W} [GeV]");  
   frame->GetYaxis()->CenterLabels( 1 );
   frame->GetYaxis()->SetNdivisions( frame->GetNbinsY()+10, 1 );
   frame->GetYaxis()->SetBinLabel( 1, "" ); // no labels
   frame->Draw();
   
   // make labels
   MakeLabels(frame);
   
   // draw fit value
   DrawFitValue( frame, fitval_MW[0], fiterr_MW[0] );
      
   // draw measurements
   for( Int_t i=0; i<5; i++ ){
      DrawMeasurement( frame, 4-i, val_MW[i], err_MW[i] ); 
   }

   // Redraw axis
   frame->Draw("sameaxis");
   
}

// Computation of chi2
void fcn(Int_t& npars, Double_t* grad, Double_t& f, Double_t fitPars[], Int_t iflag)
{
   // Evaluate the minimisation function ----------------------------------------------------
   //
   //  Input parameters:
   //    npars:   number of currently variable parameters
   //             CAUTION: this is not (necessarily) the dimension of the fitPars vector !
   //    fitPars: array of (constant and variable) parameters
   //    iflag:   indicates what is to be calculated
   //    grad:    array of gradients
   //
   //  Output parameters:
   //    f:       the calculated function value.
   //    grad:    the (optional) vector of first derivatives).
   // ---------------------------------------------------------------------------------------
   
   Double_t chi2 = 0;

   for( Int_t ipar=0; ipar<nVals; ipar++ ){
      chi2 += TMath::Power( (val_MW[ipar] - fitPars[0]) / err_MW[ipar], 2 );
   }
  
   // save minimum chi2
   if (chi2 < chi2Min) chi2Min = chi2;

   f = chi2;
}          

//********************************************************************************************
// following functions are only needed for plotting
//********************************************************************************************

void MakeLabels( TH2F* frame )
{
   // write labels
   TString labels[] = { "CDF-I", "D0-I", "CDF-II", "LEP-II", "NuTeV" };

   TLatex* text = new TLatex;
   text->SetTextAlign( 32 );
   text->SetTextSize( frame->GetLabelSize( "Y" ) );
   Float_t dy = (frame->GetYaxis()->GetXmax() - frame->GetYaxis()->GetXmin())/5.;
   Float_t dx = frame->GetXaxis()->GetXmax() - frame->GetXaxis()->GetXmin();
   Float_t yy = frame->GetYaxis()->GetXmin() - 0.5*dy;
   for (Int_t i=5-1; i>=0; i--) {
      text->SetTextColor( 1 );
      text->DrawLatex( frame->GetXaxis()->GetXmin(), yy += dy, labels[i] + "  " );
   }
   
   frame->AppendPad();
}

void DrawMeasurement( TH1 *h, Int_t nbin, Double_t val, Double_t err )
{
   TAxis *axis   = h->GetYaxis();
   
   Double_t dy;
   Double_t x1,y1,x2,y2, ymin;
   
   Int_t i = nbin;
   
   ymin = axis->GetBinCenter(i)+1;
   dy   = axis->GetBinWidth(i);
   x1   = val - err;
   y1   = ymin - 0.05*dy;
   x2   = val + err;
   y2   = ymin + 0.05*dy;
  
   TLine* line = new TLine;
   TLine* lbar = new TLine;
   TLine* rbar = new TLine;
   TMarker* m2 = new TMarker( val, ymin, 20 );
   Int_t color = 1;
   line->SetLineColor( color );
   line->SetLineWidth( 2 );
   lbar->SetLineColor( color );
   lbar->SetLineWidth( 2 );
   rbar->SetLineColor( color );
   rbar->SetLineWidth( 2 );
   m2->SetMarkerColor( color );
   m2->SetMarkerSize( 1.2 );
   m2->SetMarkerStyle( 21 );
   
   line->DrawLine( x1, ymin, x2, ymin );
   lbar->DrawLine( x1, y1, x1, y2 );
   rbar->DrawLine( x2, y1, x2, y2 );
   m2->Draw();
}

void DrawFitValue( TH2* frame, Double_t mean, Double_t err )                     
{
   Int_t DarkColor  = TColor::GetColor( "#115000" );
   Int_t LightColor = TColor::GetColor( "#bdff66" );
  
   Double_t xmin = mean - err;
   Double_t xmax = mean + err;
   Double_t ymin = frame->GetYaxis()->GetXmin();
   Double_t ymax = frame->GetYaxis()->GetXmax();
   
   Double_t x[5] = { xmin, xmin, xmax, xmax, xmin };
   Double_t y[5] = { ymin, ymax, ymax, ymin, ymin };
   TGraph *box = new TGraph( 5, x, y );
   box->SetLineColor( DarkColor );
   box->SetFillColor( LightColor );
   box->Draw("F");                          
      
   TLine* louter = new TLine;
   TLine* linner = new TLine;
   louter->SetLineWidth( 1 );
   louter->SetLineColor( DarkColor );
   linner->SetLineWidth( 1 );
   linner->SetLineStyle( 3 );
   linner->SetLineColor( DarkColor );
     
   louter->DrawLine( xmin, ymin, xmin, ymax );
   louter->DrawLine( xmax, ymin, xmax, ymax );
   linner->DrawLine( mean, ymin, mean, ymax );
}
