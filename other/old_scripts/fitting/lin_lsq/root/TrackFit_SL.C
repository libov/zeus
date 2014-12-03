/**********************************************************************************
* Statistics WS at DESY                                                          *
* Track rphi fit a la ZEUS/H1 using                                              *
* straight line fit (neglecting track curvature in magnetic field)               *         
* y = p0*x + p1                                                                  *
* Authors: Martin Goebel (straight line fit)                                     *
*          Olaf Behnke -> providing the detector hits for track fit              *
*                         3 Si hits and 60 driftchamber hits                     *
**********************************************************************************/
#include <stdlib>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLine.h"
#include "TMath.h"
#include "TFile.h"

const Double_t xmin = 0.;
const Double_t xmax = 79.;

using namespace std;

void TrackFit_SL()
{
   // make fit box nice
   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(1111);
   gStyle->SetStatX(0.46);
   gStyle->SetStatY(0.94);
   gStyle->SetStatW(0.17);
 
   TCanvas* c = new TCanvas( "c", "Parabola Fit", 0, 0, 750, 900 );
   //c->Divide(1,2);

   // get and draw data
   c->cd(1);
   TGraphErrors *data = MakeDataPoints();
   data->SetMarkerStyle(21);
   data->SetMarkerColor(2);
   data->SetLineWidth(2);
   data->SetLineColor(2);
   data->Draw("ap");

   // define parabola function
   TF1 *func = new TF1("func", "[0]+[1]*x+[2]*x*x", xmin, xmax );
   
   // do fit
   // R = entire range, + = add to list of functions
   data->Fit("func", "R+"); 

   TFile* _file=new TFile("t1.root","RECREATE");
   data->Write();
   _file->Close();



   //Double_t p0, p1, errp0, errp1, corr;
   //Double_t covMatrix[2][2];
   // get values and errors for p0 and p1
   //gMinuit->GetParameter(0, p0, errp0);
   //gMinuit->GetParameter(1, p1, errp1);
   // get covariance matrix
   //gMinuit->mnemat(&covMatrix[0][0], 2);
   
   // compute correlation between p0 and p1
   //Double_t corr = covMatrix[1][0]/(errp0*errp1);

   // compute error on y; error depends on x
   //TF1 *y_err = new TF1( "y_err", "TMath::Sqrt( [0]*[0]*x*x + [1]*[1] + 2*[2]*x )", xmin, xmax );
   //y_err->SetParameter( 0, errp0 );
   //y_err->SetParameter( 1, errp1 );
   //y_err->SetParameter( 2, covMatrix[1][0] );

   // draw 1sigma error band
   //TF1 *error1 = new TF1("error1", "func + y_err", xmin, xmax );
   //error1->SetLineWidth(1);
   //error1->Draw("same");
   
   // TF1 *error2 = new TF1("error1", "func - y_err", xmin, xmax );
   //error2->SetLineWidth(1);
   //error2->Draw("same");
   

   // ----------------- draw 1sigma error ellipse -------------------
   
   //c->cd(2);
   //TH2F *frame = new TH2F("frame", "error ellipse", 
   //                       1, p0-1.25*errp0, p0+1.25*errp0, 
   //                       1, p1-1.25*errp1, p1+1.25*errp1 );
  //frame->SetXTitle("p0");
  //   frame->SetYTitle("p1");
  //  frame->Draw();

  // draw error lines
  //  TLine *p0_line = new TLine( p0 - errp0, p1, p0 + errp0, p1 );
  // p0_line->SetLineColor(2);
  // p0_line->SetLineWidth(2);
  // p0_line->Draw();
  // TLine *p1_line = new TLine( p0, p1 - errp1, p0, p1 + errp1 );
  // p1_line->SetLineColor(2);
  // p1_line->SetLineWidth(2);
  // p1_line->Draw();
   
   // set 1 sigma contour
// gMinuit->SetErrorDef(1);
   // get contour (100 points)
// TGraph *err_ellipse = (TGraph*)gMinuit->Contour(80);
//  err_ellipse->SetLineWidth(3);
//  err_ellipse->Draw("l");

//  TLatex *text = new TLatex(p0+0.55*errp0, p1+1.02*errp1, Form("corr = %1.3f", corr) );
//  text->AppendPad();
   
}

// make data points
TGraphErrors *MakeDataPoints()
{
   // number of points
   const Int_t N = 63;
   
   // define points
   Double_t xVal[N] = { 2.5, 5.0, 10.0, 20.0, 21.0, 22.0, 23.0, 24.0, 
                      25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 
                      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 
                      41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0, 
                      49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 
                      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 
                      65.0, 66.0, 67.0, 68.0, 69.0, 70.0, 71.0, 72.0, 
                      73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0 };
   Double_t yVal[N] = { 2.142353, 2.575711, 4.254489, 6.790986, 6.562398, 7.989841, 7.837969, 9.008738,
                        8.592565, 9.351840, 6.346825, 9.358918, 9.670995, 9.898638, 10.85227, 11.32824,
                       11.30381, 11.11347, 12.07551, 10.93279, 12.53607, 11.95980, 12.66182, 12.89014,
                       12.75710, 14.01188, 13.09588, 14.38289, 14.59383, 14.58946, 16.02164, 15.55319,
                       15.79959, 15.94668, 16.21776, 17.33392, 16.69662, 17.27315, 17.20920, 18.32050,
                       18.52464, 19.12691, 20.83206, 18.65296, 20.08082, 20.47804, 19.54355, 20.93350,
                       21.27516, 22.64465, 21.08777, 21.91001, 21.65703, 21.52690, 22.53116, 26.06668,
                       23.03161, 23.02786, 23.44547, 23.88371, 23.75449, 25.71625, 25.01982};
   Double_t xErr[N] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   //  Double_t yErr[N] = { 1.0, 0.1, 0.1, 0.5, 0.5, 0.5, 0.5, 0.5,
   //                     0.5, 0.5, 5.0, 0.5, 0.5, 0.5, 0.5, 0.5, 
   //                     0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
   //                     0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
   //                     0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
   //                     0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
   //                     0.5, 5., 0.5, 0.5, 0.5, 0.5, 0.5, 5.,
   //                     0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};     
   
      Double_t yErr[N] = { 0.1, 0.1, 0.1, 0.5, 0.5, 0.5, 0.5, 0.5,
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
                          0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}; 
   //
   // create graph
   return new TGraphErrors( N, xVal, yVal, xErr, yErr );
}
