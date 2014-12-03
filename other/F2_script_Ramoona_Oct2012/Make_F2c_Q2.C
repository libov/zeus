#include <iostream>
#include <TCanvas>
#include <TH2>
#include <TFile.h>
#include "TLine.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TAxisEditor.h"
#include "TGraphAsymmErrors.h"

//extern "C" void f2qcdfine_(Float_t &);

void Make_F2c_Q2(){

    // Style
   gROOT->SetStyle("Plain");
   gStyle->SetFuncWidth(1);
   gStyle->SetFuncColor(4);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetCanvasDefH(500);
   gStyle->SetCanvasDefW(500);
   gStyle->SetPadTickX(kTRUE);
   gStyle->SetPadTickY(kTRUE);
   gStyle->SetStatX(1.00);
   gStyle->SetStatY(1.00);
   gStyle->SetStatH(0.1);
   gStyle->SetStatW(0.19);
   gStyle->SetOptStat(000000);
   gStyle->SetOptFit(0000000);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.20);
   gStyle->SetPadRightMargin(0.05);
   gStyle->SetPadTopMargin(0.03);
   gStyle->SetFrameLineWidth(2);
   gStyle->SetTitleOffset(1.73,"Y");
   gStyle->SetTitleOffset(1.0,"X");
   gStyle->SetTitleSize(0.05,"Y");
   gStyle->SetTitleSize(0.05,"X");
   gStyle->SetLabelSize(0.04,"Y");
   gStyle->SetLabelOffset(0.00001,"X");
   gStyle->SetLabelOffset(0.012,"Y");
   //gStyle->SetCenterTitle(); 
   //gStyle->SetNdivisions();
 
   gStyle->SetErrorX(0);

  // Binning for differential cross sections
  Int_t Nq2bins = 100;

  TCanvas *c_f2c = new TCanvas("c_f2c","c_f2c",10,10,500,700);
  c_f2c->cd();

  // set bin ranges for logarithmic scales on likelihood function
  const Int_t NBins=100; 
  Float_t Min=0.1;
  Float_t Max=5000;
  Double_t bins[100+1];
  Double_t nmag = TMath::Log10(Max) - TMath::Log10(Min);

  for ( Int_t i = 0; i <= NBins; i++ ) {
    Double_t x = TMath::Log10(Min) + i*nmag/NBins;
    bins[i] = TMath::Power(10, x);
  }

  // dummy histogram for F2c plot
  TH1F *h_f2c=new TH1F("h_f2c","",NBins,bins);
  h_f2c->GetXaxis()->SetRangeUser(1,3500);
  h_f2c->GetYaxis()->SetRangeUser(0,2.5);
  //h_f2c->SetTitle("HERA");
  h_f2c->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
  h_f2c->GetYaxis()->SetTitle("F_{2}^{c#bar{c}} + 0.3 i");
  h_f2c->GetYaxis()->SetNdivisions(512);
  //h_f2c->GetYaxis()->DoDecimal();
  h_f2c->Draw("hist");

  //Draw theory curves
  Float_t xmy[8] = {0.00013, 0.0002, 0.0005, 0.0013, 0.002, 0.005, 0.013, 0.032};
  const char* xvalue[8] = {"xeq00013", "xeq0002", "xeq0005", "xeq0013", "xeq002", "xeq005", "xeq013", "xeq032"};
  Int_t shift[8] = {7, 6, 5, 4, 3, 2, 1, 0};
  Float_t q2min[8] = {1.9, 3.9, 7.9, 11, 11, 30, 80, 200};
  Float_t q2max[8] = {8.1, 16.1, 45.5, 64.1, 135.1, 257, 725, 3000};
  //const char* fname[5] = {"abkm", "jr09", "mstw08", "ct10", "nn21"};
  
  //***************************************
  // FFNS predictions from OPENQCDRAD code
  //***************************************

  //************
  // ABKM NNLO 
  //************

  TGraph* abkm_my_gr_dummy = new TGraph(60);
  abkm_my_gr_dummy->SetLineColor(8);
  abkm_my_gr_dummy->SetLineWidth(3);
  abkm_my_gr_dummy->SetLineStyle(2);
  abkm_my_gr_dummy->SetMarkerColor(8);

  TGraph* abkm_my_graph[8];
  for (Int_t i=0; i < 8; i++){
    abkm_my_graph[i] = FFNS_F2c("abkm", xmy[i], shift[i], q2min[i], q2max[i], "nnlo");
    abkm_my_graph[i]->SetLineColor(8);
    abkm_my_graph[i]->SetMarkerColor(8);
    abkm_my_graph[i]->SetMarkerSize(0.2);
    abkm_my_graph[i]->SetLineWidth(3);
    abkm_my_graph[i]->SetLineStyle(2);
    abkm_my_graph[i]->Draw("same,C");
  }

  //************
  // MSTW08 NNLO 
  //************

  TGraph* mstw_nnlo_gr_dummy = new TGraph(60);
  mstw_nnlo_gr_dummy->SetLineColor(kBlue);
  mstw_nnlo_gr_dummy->SetLineWidth(2);
  mstw_nnlo_gr_dummy->SetLineStyle(3);
  mstw_nnlo_gr_dummy->SetMarkerColor(kBlue);

  TGraph* mstw_nnlo_graph[8];
  for (Int_t i=0; i < 8; i++){
    mstw_nnlo_graph[i] = MSTW_NNLO(xmy[i], shift[i], q2min[i], q2max[i]);
    mstw_nnlo_graph[i]->SetLineColor(kBlue);
    mstw_nnlo_graph[i]->SetMarkerColor(kBlue);
    mstw_nnlo_graph[i]->SetMarkerSize(0.2);
    mstw_nnlo_graph[i]->SetLineWidth(2);
    mstw_nnlo_graph[i]->SetLineStyle(3);
    mstw_nnlo_graph[i]->Draw("same,C");
  }

  //************
  // MSTW NLO 
  //************

  TGraph* mstw_gr_dummy = new TGraph(60);
  mstw_gr_dummy->SetLineColor(kRed);
  mstw_gr_dummy->SetLineWidth(2);
  mstw_gr_dummy->SetLineStyle(7);
  mstw_gr_dummy->SetMarkerColor(kRed);

  TGraph* mstw_graph[8];
  for (Int_t i=0; i < 8; i++){
    mstw_graph[i] = MSTW(xmy[i], shift[i], q2min[i], q2max[i]);
    mstw_graph[i]->SetLineColor(kRed);
    mstw_graph[i]->SetMarkerColor(kRed);
    mstw_graph[i]->SetMarkerSize(0.2);
    mstw_graph[i]->SetLineWidth(2);
    mstw_graph[i]->SetLineStyle(7);
    mstw_graph[i]->Draw("same,C");
  }

  //************
  // JR09 NNLO 
  //************

  TGraph* jr09_gr_dummy = new TGraph(60);
  jr09_gr_dummy->SetLineColor(kBlack);
  jr09_gr_dummy->SetLineWidth(1);
  jr09_gr_dummy->SetLineStyle(1);
  jr09_gr_dummy->SetMarkerColor(kBlack);

  TGraph* jr09_graph[8];
  for (Int_t i=0; i < 8; i++){
    jr09_graph[i] = JR09(xmy[i], shift[i], q2min[i], q2max[i]);
    jr09_graph[i]->SetLineColor(kBlack);
    jr09_graph[i]->SetMarkerColor(kBlack);
    jr09_graph[i]->SetMarkerSize(0.2);
    jr09_graph[i]->SetLineWidth(1);
    jr09_graph[i]->SetLineStyle(1);
    jr09_graph[i]->Draw("same,C");
  }


  //************
  // GJR08 NNLO 
  //************

  TGraph* gjr08_gr_dummy = new TGraph(60);
  gjr08_gr_dummy->SetLineColor(kCyan+1);
  gjr08_gr_dummy->SetLineWidth(1);
  gjr08_gr_dummy->SetLineStyle(1);
  gjr08_gr_dummy->SetMarkerColor(kCyan+1);

  TGraph* gjr08_graph[8];
  for (Int_t i=0; i < 8; i++){
    gjr08_graph[i] = GJR08(xmy[i], shift[i], q2min[i], q2max[i]);
    gjr08_graph[i]->SetLineColor(kCyan+1);
    gjr08_graph[i]->SetMarkerColor(kCyan+1);
    gjr08_graph[i]->SetMarkerSize(0.2);
    gjr08_graph[i]->SetLineWidth(1);
    gjr08_graph[i]->SetLineStyle(1);
    gjr08_graph[i]->Draw("same,C");
  }

  //************
  // NN21 NLO 
  //************

  TGraph* nn21_gr_dummy = new TGraph(60);
  nn21_gr_dummy->SetLineColor(kGreen+2);
  nn21_gr_dummy->SetLineWidth(2);
  nn21_gr_dummy->SetLineStyle(5);
  nn21_gr_dummy->SetMarkerColor(kGreen+2);

  TGraph* nn21_graph[8];
  for (Int_t i=0; i < 8; i++){
    nn21_graph[i] = NN21(xmy[i], shift[i], q2min[i], q2max[i]);
    nn21_graph[i]->SetLineColor(kGreen+2);
    nn21_graph[i]->SetMarkerColor(kGreen+2);
    nn21_graph[i]->SetMarkerSize(0.2);
    nn21_graph[i]->SetLineWidth(2);
    nn21_graph[i]->SetLineStyle(5);
    //nn21_graph[i]->Draw("same,C");
  }

  
  //************
  // NN21 NNLO 
  //************

  TGraph* nn21_nnlo_gr_dummy = new TGraph(60);
  nn21_nnlo_gr_dummy->SetLineColor(kOrange+2);
  nn21_nnlo_gr_dummy->SetLineWidth(2);
  nn21_nnlo_gr_dummy->SetLineStyle(5);
  nn21_nnlo_gr_dummy->SetMarkerColor(kOrange+2);

  TGraph* nn21_nnlo_graph[8];
  for (Int_t i=0; i < 8; i++){
    nn21_nnlo_graph[i] = NN21_NNLO(xmy[i], shift[i], q2min[i], q2max[i]);
    nn21_nnlo_graph[i]->SetLineColor(kOrange+2);
    nn21_nnlo_graph[i]->SetMarkerColor(kOrange+2);
    nn21_nnlo_graph[i]->SetMarkerSize(0.2);
    nn21_nnlo_graph[i]->SetLineWidth(2);
    nn21_nnlo_graph[i]->SetLineStyle(5);
    nn21_nnlo_graph[i]->Draw("same,C");
  }

  //Draw data points

  TLegend *leg_f2c1 = new TLegend(0.6048387,0.7247024,0.9395161,0.9375,NULL,"brNDC");
  leg_f2c1->SetBorderSize(0);
  leg_f2c1->SetTextFont(62);
  leg_f2c1->SetTextSize(0.02827381);
  leg_f2c1->SetLineColor(1);
  leg_f2c1->SetLineStyle(1);
  leg_f2c1->SetLineWidth(1);
  leg_f2c1->SetFillColor(19);
  leg_f2c1->SetFillStyle(0);
  leg_f2c1->AddEntry(abkm_my_gr_dummy,"ABKM NNLO","L");
  leg_f2c1->AddEntry(mstw_gr_dummy,"MSTW08 NLO","L");
  leg_f2c1->AddEntry(mstw_nnlo_gr_dummy,"MSTW08 NNLO","L");
  //leg_f2c1->AddEntry(ct10_gr_dummy,"CT10 NLO","L");
  //leg_f2c1->AddEntry(nn21_gr_dummy,"NN21 NLO","L");
  leg_f2c1->AddEntry(nn21_nnlo_gr_dummy,"NN21 NNLO","L");
  leg_f2c1->AddEntry(gjr08_gr_dummy,"GJR08 NLO","L");
  leg_f2c1->AddEntry(jr09_gr_dummy,"JR09 NNLO","L");
  leg_f2c1->Draw("ndc,same");

  TLegend *leg_f2c2 = new TLegend(0.6370968,0.6026786,0.8508065,0.703869,NULL,"brNDC");
  ci = TColor::GetColor("#0000cc");
  leg_f2c2->SetTextColor(ci);
  leg_f2c2->SetTextFont(62);
  leg_f2c2->SetTextSize(0.0295858);
  leg_f2c2->SetLineColor(1);
  leg_f2c2->SetLineStyle(1);
  leg_f2c2->SetLineWidth(1);
  leg_f2c2->SetFillColor(0);
  leg_f2c2->SetFillStyle(0);
  leg_f2c2->SetBorderSize(0);
  leg_f2c2->AddEntry("","OPENQCDRAD","");
  leg_f2c2->AddEntry("","3 flavor FFNS","");
  leg_f2c2->AddEntry("","scale = #sqrt{Q^{2}+4m_{c}^{2}}","");
  //leg_f2c2->Draw("ndc,same");

  //draw lines for x values
  TLine *l_x1 = new TLine(1, 0.4,1000,0.4);
  l_x1->SetLineColor(kBlack);
  l_x1->SetLineWidth(1);
  l_x1->SetLineStyle(1);
  l_x1->Draw("same");
  TLine *l_x2 = new TLine(1, 0.7,500,0.7);
  l_x2->SetLineColor(kBlack);
  l_x2->SetLineWidth(1);
  l_x2->SetLineStyle(1);
  l_x2->Draw("same");
  TLine *l_x3 = new TLine(1, 0.98,100,0.98);
  l_x3->SetLineColor(kBlack);
  l_x3->SetLineWidth(1);
  l_x3->SetLineStyle(1);
  l_x3->Draw("same");
  TLine *l_x4 = new TLine(1, 1.3,50,1.3);
  l_x4->SetLineColor(kBlack);
  l_x4->SetLineWidth(1);
  l_x4->SetLineStyle(1);
  l_x4->Draw("same");
  TLine *l_x5 = new TLine(1, 1.6,30,1.6);
  l_x5->SetLineColor(kBlack);
  l_x5->SetLineWidth(1);
  l_x5->SetLineStyle(1);
  l_x5->Draw("same");
  TLine *l_x6 = new TLine(1, 1.88,15,1.88);
  l_x6->SetLineColor(kBlack);
  l_x6->SetLineWidth(1);
  l_x6->SetLineStyle(1);
  l_x6->Draw("same");
  TLine *l_x7 = new TLine(1, 2.13,8,2.13);
  l_x7->SetLineColor(kBlack);
  l_x7->SetLineWidth(1);
  l_x7->SetLineStyle(1);
  l_x7->Draw("same");

  //write text for x shift values
  TLatex t_x0;
  t_x0.SetTextAngle(0);
  t_x0.SetTextSize(0.03);
  t_x0.DrawLatex(1.3,0.06, "x=0.032 i=0");
  TLatex t_x1;
  t_x1.SetTextAngle(0);
  t_x1.SetTextSize(0.03);
  t_x1.DrawLatex(1.3,0.32, "x=0.013 i=1");
  TLatex t_x2;
  t_x2.SetTextAngle(0);
  t_x2.SetTextSize(0.03);
  t_x2.DrawLatex(1.3,0.62, "x=0.005 i=2");
  TLatex t_x3;
  t_x3.SetTextAngle(0);
  t_x3.SetTextSize(0.03);
  t_x3.DrawLatex(1.3,0.91, "x=0.002 i=3");
  TLatex t_x4;
  t_x4.SetTextAngle(0);
  t_x4.SetTextSize(0.03);
  t_x4.DrawLatex(1.3,1.22, "x=0.0013 i=4");
  TLatex t_x5;
  t_x5.SetTextAngle(0);
  t_x5.SetTextSize(0.03);
  t_x5.DrawLatex(1.3,1.52, "x=0.0005 i=5");
  TLatex t_x6;
  t_x6.SetTextAngle(0);
  t_x6.SetTextSize(0.03);
  t_x6.DrawLatex(1.3,1.8, "x=0.0002 i=6");
  TLatex t_x7;
  t_x7.SetTextAngle(0);
  t_x7.SetTextSize(0.03);
  t_x7.DrawLatex(1.1,2.05, "x=0.00013 i=7");

  gPad->SetLogx();
  //gPad->SetLogy();
  c_f2c->SaveAs("Plots/F2c_q2.eps");
  c_f2c->SaveAs("Plots/F2c_q2.root");
  c_f2c->SaveAs("Plots/F2c_q2.C");
}

//______________________________________________________________________________

TGraph* FFNS_F2c(const char* fname, Float_t xmy, Int_t shift, Float_t q2min, Float_t q2max, Option_t *option){

  //F2c values obtained from OPENQCDRAD code - 3 flavor FFNS - scale=Q2+4m2

  TString opt = option;
  opt.ToLower();

  ifstream ffns_f2c_file;
  char *filename = Form("%s_my.dat", fname);
  cout << filename << endl;
  ffns_f2c_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;
   
  TGraph *ffns_f2c_gr=new TGraph(nbins);
  TGraph *ffns_f2c_gr_nnlo=new TGraph(nbins);

  for (Int_t i =1; i <=240; i++) {
    Float_t q2, xx, f2c1, f2c2;
    //  first column: momentum transferred in GeV^2, second column: x, third column: 3-flavour FFNS value of F_2^cc at the NNLO, 4-th column: the same at NLO

    ffns_f2c_file >> q2 >> xx >> f2c1 >> f2c2;
    //cout << q2 <<"  "<< xx << "  " << f2c1 <<"  "<< f2c2 << "  "<< nbins << endl;
    
    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< xx << "  " << f2c1 <<"  "<< f2c2 << "  " << nbins << endl;
	//ffns_f2c_gr->SetPoint(nbins-1, q2, f2c2*TMath::Power(2, shift));
	//ffns_f2c_gr_nnlo->SetPoint(nbins-1, q2, f2c1*TMath::Power(2, shift));

	ffns_f2c_gr->SetPoint(nbins-1, q2, f2c2 + (0.3*shift));
	ffns_f2c_gr_nnlo->SetPoint(nbins-1, q2, f2c1 + (0.3*shift));
      }
    }
  }
  ffns_f2c_file.close();
  
  if ( opt.Contains("nnlo") ) {
    return ffns_f2c_gr_nnlo;
  }else 
    return ffns_f2c_gr;
}
//______________________________________________________________________________

TGraph* MSTW(Float_t xmy,Int_t shift, Float_t q2min, Float_t q2max){

  ifstream mstw_file;
  char *filename = ("MSTW/mstw08_nlo.dat");
  cout << filename << endl;
  mstw_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *mstw_gr=new TGraph(nbins);

  for (Int_t i =1; i <=200; i++) {
    Float_t xx, q2, f2c, f2cup, f2cdo;
  
    mstw_file >> xx >> q2 >> f2c >> f2cup >> f2cdo;
    //cout << xx << "  " << q2 << "  "<< f2c << "  "<< f2cup << "  "<< f2cdo << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< f2c << "  " << nbins << endl;
	mstw_gr->SetPoint(nbins-1, q2, f2c + (0.3*shift));
      }
    }
  }
  mstw_file.close();
  
  return mstw_gr;
}

//______________________________________________________________________________

TGraph* MSTW_NNLO(Float_t xmy,Int_t shift, Float_t q2min, Float_t q2max){

  ifstream mstw_nnlo_file;
  char *filename = ("MSTW/mstw08_nnlo.dat");
  cout << filename << endl;
  mstw_nnlo_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *mstw_nnlo_gr=new TGraph(nbins);

  for (Int_t i =1; i <=200; i++) {
    Float_t xx, q2, f2c, f2cup, f2cdo;
  
    mstw_nnlo_file >> xx >> q2 >> f2c >> f2cup >> f2cdo;
    //cout << xx << "  " << q2 << "  "<< f2c << "  "<< f2cup << "  "<< f2cdo << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< f2c << "  " << nbins << endl;
	mstw_nnlo_gr->SetPoint(nbins-1, q2, f2c + (0.3*shift));
      }
    }
  }
  mstw_nnlo_file.close();
  
  return mstw_nnlo_gr;
}

//______________________________________________________________________________

TGraph* JR09(Float_t xmy,Int_t shift, Float_t q2min, Float_t q2max){

  ifstream jr09_file;
  char *filename = ("JR09/jr09_nnlo.dat");
  cout << filename << endl;
  jr09_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *jr09_gr=new TGraph(nbins);

  for (Int_t i =1; i <=80; i++) {
    Float_t xx, q2, f2c;
  
    jr09_file >> xx >> q2 >> f2c;
    //cout << xx << "  " << q2 << "  "<< f2c << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< f2c << "  " << nbins << endl;
	jr09_gr->SetPoint(nbins-1, q2, f2c + (0.3*shift));
      }
    }
  }
  jr09_file.close();
  
  return jr09_gr;
}
//______________________________________________________________________________

TGraph* GJR08(Float_t xmy,Int_t shift, Float_t q2min, Float_t q2max){

  ifstream gjr08_file;
  char *filename = ("JR09/gjr08_nlo.dat");
  cout << filename << endl;
  gjr08_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *gjr08_gr=new TGraph(nbins);

  for (Int_t i =1; i <=80; i++) {
    Float_t xx, q2, f2c;
  
    gjr08_file >> xx >> q2 >> f2c;
    //cout << xx << "  " << q2 << "  "<< f2c << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< f2c << "  " << nbins << endl;
	gjr08_gr->SetPoint(nbins-1, q2, f2c + (0.3*shift));
      }
    }
  }
  gjr08_file.close();
  
  return gjr08_gr;
}

//______________________________________________________________________________

TGraph* NN21(Float_t xmy,Int_t shift, Float_t q2min, Float_t q2max){

  ifstream nn21_file;
  char *filename = ("NNPDF/nn21_nlo.dat");
  cout << filename << endl;
  nn21_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *nn21_gr=new TGraph(nbins);

  for (Int_t i =1; i <=64; i++) {
    Float_t xx, q2, f2c, err;
  
    nn21_file >> xx >> q2 >> f2c >> err;
    //cout << xx << "  " << q2 << "  "<< f2c << err << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< f2c << "  " << nbins << endl;
	nn21_gr->SetPoint(nbins-1, q2, f2c + (0.3*shift));
      }
    }
  }
  nn21_file.close();
  
  return nn21_gr;
}

//______________________________________________________________________________

TGraph* NN21_NNLO(Float_t xmy,Int_t shift, Float_t q2min, Float_t q2max){

  ifstream nn21_nnlo_file;
  char *filename = ("NNPDF/nn21_nnlo.dat");
  cout << filename << endl;
  nn21_nnlo_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *nn21_nnlo_gr=new TGraph(nbins);

  for (Int_t i =1; i <=64; i++) {
    Float_t xx, q2, f2c, err;
  
    nn21_nnlo_file >> xx >> q2 >> f2c >> err;
    //cout << xx << "  " << q2 << "  "<< f2c << err << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< f2c << "  " << nbins << endl;
	nn21_nnlo_gr->SetPoint(nbins-1, q2, f2c + (0.3*shift));
      }
    }
  }
  nn21_nnlo_file.close();
  
  return nn21_nnlo_gr;
}
