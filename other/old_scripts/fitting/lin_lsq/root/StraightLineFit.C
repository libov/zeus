
/**********************************************************************************
 * Statistics WS at DESY                                                          *
 * straight line fit                                                              *
 * y = p0*x + p1                                                                  *
 * Author: Martin Goebel                                                          *
 **********************************************************************************/
#include <stdlib>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLine.h"
#include "TMath.h"

//const Double_t xmin = -10.;
//const Double_t xmax =  10.;
const Double_t xmin = -4.;
const Double_t xmax =  8.;

using namespace std;

void StraightLineFit()
{
   // make fit box nice
   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(1111);
   gStyle->SetStatX(0.46);
   gStyle->SetStatY(0.94);
   gStyle->SetStatW(0.17);
 
   TCanvas* c = new TCanvas( "c", "Straight Line Fit", 0, 0, 750, 900 );
   c->Divide(1,2);

   // get and draw data
   c->cd(1);
   TGraphErrors *data = MakeDataPoints();
   data->SetMarkerStyle(21);
   data->SetMarkerColor(2);
   data->SetLineWidth(2);
   data->SetLineColor(2);
   data->Draw("ap");

   // define linear function
   TF1 *func = new TF1("func", "[0]*x+[1]", xmin, xmax );
   
   // do fit
   // R = entire range, + = add to list of functions
   data->Fit("func", "R+"); 
   // gMinuit->FixParameter(1);
   data->Fit("func", "R+"); 

   Double_t p0, p1, errp0, errp1, corr;
   Double_t covMatrix[2][2];
   // get values and errors for p0 and p1
   gMinuit->GetParameter(0, p0, errp0);
   gMinuit->GetParameter(1, p1, errp1);
   // get covariance matrix
   gMinuit->mnemat(&covMatrix[0][0], 2);
   
   // compute correlation between p0 and p1
   Double_t corr = covMatrix[1][0]/(errp0*errp1);

   // compute error on y; error depends on x
   TF1 *y_err = new TF1( "y_err", "TMath::Sqrt( [0]*[0]*x*x + [1]*[1] + 2*[2]*x )", xmin, xmax );
   y_err->SetParameter( 0, errp0 );
   y_err->SetParameter( 1, errp1 );
   y_err->SetParameter( 2, covMatrix[1][0] );

   // draw 1sigma error band
   TF1 *error1 = new TF1("error1", "func + y_err", xmin, xmax );
   error1->SetLineWidth(1);
   //error1->Draw("same");
   error1->Draw();
   
   TF1 *error2 = new TF1("error1", "func - y_err", xmin, xmax );
   error2->SetLineWidth(1);
   error2->Draw("same");
   data->Draw("same");   

   // ----------------- draw 1sigma error ellipse -------------------
   
   c->cd(2);
   TH2F *frame = new TH2F("frame", "error ellipse", 
                          1, p0-1.25*errp0, p0+1.25*errp0, 
                          1, p1-1.25*errp1, p1+1.25*errp1 );
   frame->SetXTitle("p0");
   frame->SetYTitle("p1");
   frame->Draw();

   // draw error lines
   TLine *p0_line = new TLine( p0 - errp0, p1, p0 + errp0, p1 );
   p0_line->SetLineColor(2);
   p0_line->SetLineWidth(2);
   p0_line->Draw();
   TLine *p1_line = new TLine( p0, p1 - errp1, p0, p1 + errp1 );
   p1_line->SetLineColor(2);
   p1_line->SetLineWidth(2);
   p1_line->Draw();
   
   // set 1 sigma contour
   gMinuit->SetErrorDef(1);
   // get contour (100 points)
   TGraph *err_ellipse = (TGraph*)gMinuit->Contour(80);
   err_ellipse->SetLineWidth(3);
   err_ellipse->Draw("l");

   TLatex *text = new TLatex(p0+0.55*errp0, p1+1.02*errp1, Form("corr = %1.3f", corr) );
   text->AppendPad();
   
}

// make data points
TGraphErrors *MakeDataPoints()
{
   // number of points
   const Int_t N = 5;
   
   // define points
   Double_t xVal[N] = {0., 1.0, 2.0, 3.0, 4.0 };
   //  Double_t xVal[N] = { 0., 5., 6., 7., 8. };
   Double_t yVal[N] = { -4., 1.4, 1.5, 3.7, 4.1 };
   Double_t xErr[N] = { 0.0, 0.0, 0.0, 0.0, 0.0 }; // no error in x-direction
   // Double_t yErr[N] = { 0.5, 0.2, 1.0, 0.5 };
   Double_t yErr[N] = { 0.0001, 0.5, 0.5, 0.5, 0.5 };
     
   // create graph
   return new TGraphErrors( N, xVal, yVal, xErr, yErr );
}
