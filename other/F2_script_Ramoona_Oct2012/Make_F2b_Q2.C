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

void Make_F2b_Q2(){

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

  TCanvas *c_f2b = new TCanvas("c_f2b","c_f2b",10,10,500,700);
  c_f2b->cd();

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

  // dummy histogram for F2b plot
  TH1F *h_f2b=new TH1F("h_f2b","",NBins,bins);
  h_f2b->GetXaxis()->SetRangeUser(2,3000);
  h_f2b->GetYaxis()->SetRangeUser(-0.01,0.23);
  //h_f2b->SetTitle("HERA");
  h_f2b->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
  h_f2b->GetYaxis()->SetTitle("F_{2}^{b#bar{b}} + 0.03 i");
  h_f2b->GetYaxis()->SetNdivisions(512);
  //h_f2b->GetYaxis()->DoDecimal();
  h_f2b->Draw("hist");

  //Draw theory curves
  Float_t xmy[8] = {0.00013, 0.0002, 0.0005, 0.0013, 0.002, 0.005, 0.013, 0.032};
  const char* xvalue[8] = {"xeq00013", "xeq0002", "xeq0005", "xeq0013", "xeq002", "xeq005", "xeq013", "xeq032"};
  Int_t shift[8] = {7, 6, 5, 4, 3, 2, 1, 0};
  Float_t q2min[8] = {1.9, 3.9, 7.9, 11, 11, 30, 80, 100};
  Float_t q2max[8] = {8.1, 16.1, 45.5, 100, 135.1, 257, 725, 3000};

  //***************
  // ZEUS-S+HVQDIS  .. CHANGED TO HERAPDF
  //***************
  
  TGraphAsymmErrors* zeuss_gr_dummy = new TGraph(24);
  zeuss_gr_dummy->SetLineColor(7);
  zeuss_gr_dummy->SetFillColor(7);
  zeuss_gr_dummy->SetLineWidth(1);
  zeuss_gr_dummy->SetLineStyle(1);
  zeuss_gr_dummy->SetMarkerColor(kBlack);

  TGraphAsymmErrors* zeuss_graph[8];
  for (Int_t i=0; i < 8; i++){
    //zeuss_graph[i] = ZEUS_S(xmy[i], shift[i], q2min[i], q2max[i]);
    zeuss_graph[i] = HERAPDF(xmy[i], shift[i], q2min[i], q2max[i]);
    zeuss_graph[i]->SetFillColor(7);
    zeuss_graph[i]->SetLineColor(7);
    zeuss_graph[i]->SetLineStyle(1);
    zeuss_graph[i]->SetMarkerColor(kBlack);
    zeuss_graph[i]->SetMarkerSize(0.2);
    zeuss_graph[i]->Draw("same,E3");
  }

  //***************
  // CTEQ 
  //***************
  
  TGraph* cteq_gr_dummy = new TGraph(24);
  cteq_gr_dummy->SetLineColor(kMagenta);
  cteq_gr_dummy->SetFillColor(kOrange);
  cteq_gr_dummy->SetLineWidth(2);
  cteq_gr_dummy->SetLineStyle(1);
  cteq_gr_dummy->SetMarkerColor(kMagenta);

  TGraph* cteq_graph[8];
  for (Int_t i=0; i < 8; i++){
    cteq_graph[i] = CTEQ(xmy[i], q2min[i], q2max[i]);
    cteq_graph[i]->SetFillColor(kMagenta);
    cteq_graph[i]->SetLineColor(kMagenta);
    cteq_graph[i]->SetLineStyle(1);
    cteq_graph[i]->SetLineWidth(2);
    cteq_graph[i]->SetMarkerColor(kMagenta);
    cteq_graph[i]->SetMarkerSize(0.2);
    cteq_graph[i]->Draw("same,C");
  }

 
  //************
  // ABKM NNLO 
  //************

  TGraph* abkm_gr_dummy = new TGraph(60);
  abkm_gr_dummy->SetLineColor(8);
  abkm_gr_dummy->SetLineWidth(3);
  abkm_gr_dummy->SetLineStyle(2);
  abkm_gr_dummy->SetMarkerColor(8);

  TGraph* abkm_graph[8];
  for (Int_t i=0; i < 8; i++){
    abkm_graph[i] = ABKM(xvalue[i], shift[i], q2min[i], q2max[i]);
    abkm_graph[i]->SetLineColor(8);
    abkm_graph[i]->SetMarkerColor(8);
    abkm_graph[i]->SetMarkerSize(0.2);
    abkm_graph[i]->SetLineWidth(3);
    abkm_graph[i]->SetLineStyle(2);
    abkm_graph[i]->Draw("same,C");
  }

  //*********************************
  // ABKM NNLO (from OPENQCDRAD code)
  //*********************************

  TGraph* abkm_my_gr_dummy = new TGraph(60);
  abkm_my_gr_dummy->SetLineColor(kBlack);
  abkm_my_gr_dummy->SetLineWidth(1);
  abkm_my_gr_dummy->SetLineStyle(1);
  abkm_my_gr_dummy->SetMarkerColor(kBlack);

  TGraph* abkm_my_graph[8];
  for (Int_t i=0; i < 8; i++){
    abkm_my_graph[i] = ABKM_MY(xmy[i], shift[i], q2min[i], q2max[i]);
    abkm_my_graph[i]->SetLineColor(kBlack);
    abkm_my_graph[i]->SetMarkerColor(kBlack);
    abkm_my_graph[i]->SetMarkerSize(0.2);
    abkm_my_graph[i]->SetLineWidth(1);
    abkm_my_graph[i]->SetLineStyle(1);
    //abkm_my_graph[i]->Draw("same,C");
  }

  //**********
  // MSTW NLO 
  //**********

  TGraph* mstw_gr_dummy = new TGraph(24);
  mstw_gr_dummy->SetLineColor(kRed);
  mstw_gr_dummy->SetLineWidth(2);
  mstw_gr_dummy->SetLineStyle(7);
  mstw_gr_dummy->SetMarkerColor(kRed);

  TGraph* mstw_graph[8];
  for (Int_t i=0; i < 8; i++){
    mstw_graph[i] = MSTW(xvalue[i], shift[i], q2min[i], q2max[i]);
    mstw_graph[i]->SetLineColor(kRed);
    mstw_graph[i]->SetLineWidth(2);
    mstw_graph[i]->SetLineStyle(7);
    mstw_graph[i]->SetMarkerColor(kRed);
    mstw_graph[i]->SetMarkerSize(0.2);
    mstw_graph[i]->Draw("same,C");
  }

  //************
  // MSTW NNLO 
  //************
  
  TGraph* mstw_nnlo_gr_dummy = new TGraph(24);
  mstw_nnlo_gr_dummy->SetLineColor(kBlue);
  mstw_nnlo_gr_dummy->SetLineWidth(2);
  mstw_nnlo_gr_dummy->SetLineStyle(3);
  mstw_nnlo_gr_dummy->SetMarkerColor(kBlue);

  TGraph* mstw_nnlo_graph[8];
  for (Int_t i=0; i < 8; i++){
    mstw_nnlo_graph[i] = MSTW_NNLO(xvalue[i], shift[i], q2min[i], q2max[i]);
    mstw_nnlo_graph[i]->SetLineColor(kBlue);
    mstw_nnlo_graph[i]->SetLineWidth(2);
    mstw_nnlo_graph[i]->SetLineStyle(3);
    mstw_nnlo_graph[i]->SetMarkerColor(kBlue);
    mstw_nnlo_graph[i]->SetMarkerSize(0.2);
    mstw_nnlo_graph[i]->Draw("same,C");
  }

  //************
  // JR09 NNLO 
  //************
  
  TGraph* jr09_gr_dummy = new TGraph(24);
  jr09_gr_dummy->SetLineColor(kBlack);
  jr09_gr_dummy->SetLineWidth(1);
  jr09_gr_dummy->SetLineStyle(1);
  jr09_gr_dummy->SetMarkerColor(kBlack);

  TGraph* jr09_graph[8];
  for (Int_t i=0; i < 8; i++){
    jr09_graph[i] = JR09(xvalue[i], shift[i], q2min[i], q2max[i]);
    jr09_graph[i]->SetLineColor(kBlack);
    jr09_graph[i]->SetLineWidth(1);
    jr09_graph[i]->SetLineStyle(1);
    jr09_graph[i]->SetMarkerColor(kBlack);
    jr09_graph[i]->SetMarkerSize(0.2);
    jr09_graph[i]->Draw("same,C");
  }

  //Draw data points

  //*************************************************
  // H1  vtx  -  DESY-09-096  (H1 inclusive analysis)
  //*************************************************

  // Read values from table and then create a graph
  ifstream DESY_09_096;
  
  DESY_09_096.open("DATA/F2b_DESY_09_096.dat");

  TGraphAsymmErrors *incvtx_h1=new TGraphAsymmErrors(12);
  TGraphAsymmErrors *incvtx1_h1=new TGraphAsymmErrors(12);

  Int_t shift_h1[12] = {6, 6, 5, 5, 4, 4, 2, 2, 1, 1, 0, 0};

  for (Int_t i =1; i <=12; i++) {
    Float_t q2_h1, x_h1, f2_h1, stat_h1, tot_h1;
    DESY_09_096 >> q2_h1 >> x_h1 >> f2_h1 >> stat_h1 >> tot_h1;
    
    //cout << q2_h1 << "  "<< x_h1 << "  "<< f2_h1 << "  "<< stat_h1 << "  "<< tot_h1 << endl;
    
    incvtx_h1->SetPoint(i-1, q2_h1, (f2_h1 +  0.03*shift_h1[i-1]));
    incvtx_h1->SetPointError(i-1,0,0,stat_h1,stat_h1);
    incvtx1_h1->SetPoint(i-1, q2_h1, (f2_h1 +  0.03*shift_h1[i-1]));
    incvtx1_h1->SetPointError(i-1,0,0,tot_h1,tot_h1);
    
  }
  
  incvtx_h1->SetMarkerStyle(21);
  incvtx_h1->SetMarkerColor(kGreen+2);
  incvtx_h1->SetMarkerSize(1);
  incvtx1_h1->SetMarkerSize(0.8);
  incvtx1_h1->SetMarkerStyle(21);
  incvtx1_h1->SetMarkerColor(kGreen+2);
  incvtx_h1->SetLineWidth(2);
  incvtx1_h1->SetLineWidth(2);
  incvtx1_h1->Draw("E,Z,same");
  incvtx_h1->Draw("EP,same");
   
  DESY_09_096.close();

  //***********************************************
  // ZEUS  b->mu  -  DESY-09-056  (Massimo Corradi)
  //***********************************************
  
  // Read values from table and then create a graph
  ifstream DESY_09_056;
  
  DESY_09_056.open("DATA/F2b_DESY_09_056.dat");

  TGraphAsymmErrors *btomu_mc=new TGraphAsymmErrors(8);
  TGraphAsymmErrors *btomu1_mc=new TGraphAsymmErrors(8);

  Int_t shift_mc[8] = {5, 4, 3, 2, 3, 2, 1, 0};

  for (Int_t i =1; i <=8; i++) {
    Float_t q2_mc, x_mc, f2_mc, stat_mc, sysup_mc, sysdo_mc;
    DESY_09_056 >> q2_mc >> x_mc >> f2_mc >> stat_mc >> sysup_mc >> sysdo_mc;
    
    //cout << q2_mc << "  "<< x_mc << "  "<< f2_mc << "  "<< stat_mc << "  "<< sysup_mc << "  "<< sysdo_mc <<  endl;
    Float_t totup_mc = TMath::Sqrt(stat_mc*stat_mc + sysup_mc*sysup_mc);
    Float_t totdo_mc = TMath::Sqrt(stat_mc*stat_mc + sysdo_mc*sysdo_mc);
    
    //cout  << x_mc << "  " << shift_mc[i-1] << "  " << f2_mc << "  " << (f2_mc + 0.03*shift_mc[i-1]) << endl;
    btomu_mc->SetPoint(i-1, q2_mc, (f2_mc +  0.03*shift_mc[i-1]));
    btomu_mc->SetPointError(i-1,0,0,stat_mc,stat_mc);
    btomu1_mc->SetPoint(i-1, q2_mc, (f2_mc +  0.03*shift_mc[i-1]));
    btomu1_mc->SetPointError(i-1,0,0,totdo_mc,totup_mc);
    
  }
  
  btomu_mc->SetMarkerStyle(24);
  btomu_mc->SetMarkerColor(kBlack);
  btomu_mc->SetMarkerSize(1);
  btomu1_mc->SetMarkerSize(0.8);
  btomu1_mc->SetMarkerStyle(24);
  btomu1_mc->SetLineWidth(2);
  btomu_mc->SetLineWidth(2);
  btomu1_mc->Draw("E,Z,same");
  btomu_mc->Draw("EP,same");
   
  DESY_09_056.close();

  //***********************************************
  // ZEUS  b->mu  -  DESY-10-047  (Benjamin Kahle)
  //***********************************************

  // Read values from table and then create a graph
  ifstream DESY_10_047;
  
  DESY_10_047.open("DATA/F2b_DESY_10_047.dat");

  TGraphAsymmErrors *btomu_bk=new TGraphAsymmErrors(11);
  TGraphAsymmErrors *btomu1_bk=new TGraphAsymmErrors(11);

  Int_t shift_bk[11] = {7, 7, 6, 5, 5, 3, 3, 2, 3, 2, 1};

  for (Int_t i =1; i <=11; i++) {
    Float_t q2_bk, x_bk, f2_bk, stat_bk, sysup_bk, sysdo_bk, extup_bk, extdo_bk;
    DESY_10_047 >> q2_bk >> x_bk >> f2_bk >> stat_bk >> sysup_bk >> sysdo_bk >> extup_bk >> extdo_bk;
    
    //cout << q2_bk << "  "<< x_bk << "  "<< f2_bk << "  "<< stat_bk << "  "<< sysup_bk << "  "<< sysdo_bk << "  "<< extup_bk << "  "<< extdo_bk << endl;

    Float_t totup_bk = TMath::Sqrt(stat_bk*stat_bk + sysup_bk*sysup_bk + extup_bk*extup_bk);
    Float_t totdo_bk = TMath::Sqrt(stat_bk*stat_bk + sysdo_bk*sysdo_bk + extdo_bk*extdo_bk);
    
    btomu_bk->SetPoint(i-1, q2_bk, (f2_bk +  0.03*shift_bk[i-1]));
    btomu_bk->SetPointError(i-1,0,0,stat_bk,stat_bk);
    btomu1_bk->SetPoint(i-1, q2_bk, (f2_bk +  0.03*shift_bk[i-1]));
    btomu1_bk->SetPointError(i-1,0,0,totdo_bk,totup_bk);
    
  }
  
  btomu_bk->SetMarkerStyle(26);
  btomu_bk->SetMarkerColor(kBlack);
  btomu1_bk->SetMarkerSize(0.8);
  btomu_bk->SetMarkerSize(1);
  btomu1_bk->SetLineWidth(2);
  btomu_bk->SetLineWidth(2);
  btomu1_bk->SetMarkerStyle(26);
  btomu1_bk->Draw("E,Z,same");
  btomu_bk->Draw("EP,same");
   
  DESY_10_047.close();


  //************************************************
  // ZEUS  b->e  -  DESY-11-005  (Ramoona/Markus)
  //************************************************

  // Read values from table and then create a graph
  ifstream DESY_11_005;
  
  DESY_11_005.open("DATA/F2b_DESY_11_005_swim.dat");

  TGraphAsymmErrors *btoe_rs=new TGraphAsymmErrors(9);
  TGraphAsymmErrors *btoe1_rs=new TGraphAsymmErrors(9);

  Int_t shift_rs[9] = {6, 4, 5, 4, 2, 3, 2, 1, 1};

  for (Int_t i =1; i <=9; i++) {
    Float_t q2_rs, x_rs, f2_rs, stat_rs, errup_rs, errdo_rs;
    DESY_11_005 >> q2_rs >> x_rs >> f2_rs >> stat_rs >> errup_rs >> errdo_rs;
    
    //cout << q2_rs << "  "<< x_rs << "  "<< f2_rs << "  "<< stat_rs << "  "<< errup_rs << "  "<< errdo_rs << endl;
    
    Float_t totup_rs = TMath::Sqrt(stat_rs*stat_rs + errup_rs*errup_rs);
    Float_t totdo_rs = TMath::Sqrt(stat_rs*stat_rs + errdo_rs*errdo_rs);

    btoe_rs->SetPoint(i-1, q2_rs, (f2_rs +  0.03*shift_rs[i-1]));
    btoe_rs->SetPointError(i-1,0,0,stat_rs,stat_rs);
    btoe1_rs->SetPoint(i-1, q2_rs, (f2_rs +  0.03*shift_rs[i-1]));
    btoe1_rs->SetPointError(i-1,0,0,totdo_rs,totup_rs);
    
  }
  
  btoe_rs->SetMarkerStyle(25);
  btoe_rs->SetMarkerColor(kBlue);
  btoe1_rs->SetMarkerStyle(25);
  btoe1_rs->SetMarkerSize(0.8);
  btoe_rs->SetMarkerSize(1);
  btoe1_rs->SetMarkerColor(kBlue);
  btoe1_rs->SetLineWidth(2);
  btoe_rs->SetLineWidth(2);
  btoe1_rs->Draw("E,Z,same");
  btoe_rs->Draw("EP,same");
   
  DESY_11_005.close();

  //************************************************
  // ZEUS  f2bc  -  DESY-11-xxx  (Philipp Roloff)
  //************************************************

  // Read values from table and then create a graph
  ifstream ZEUS_VERTEX;
  
  ZEUS_VERTEX.open("DATA/F2b_ZEUS_VERTEX.dat");

  TGraphAsymmErrors *incvtx_pr=new TGraphAsymmErrors(17);
  TGraphAsymmErrors *incvtx1_pr=new TGraphAsymmErrors(17);

  Int_t shift_pr[17] = {7, 6, 5, 5, 5, 5, 4, 3, 2, 4, 3, 2, 2, 1, 0, 1, 0};

  for (Int_t i =1; i <=17; i++) {
    Float_t q2_pr, x_pr, f2b_pr, stat_pr, syst_up, syst_down, extrap_up, extrap_down, totup_pr, totdo_pr;
    ZEUS_VERTEX >> q2_pr >> x_pr >> f2b_pr >> stat_pr >> syst_up >> syst_down >> extrap_up >> extrap_down;

    totup_pr = sqrt(stat_pr*stat_pr + syst_up*syst_up + extrap_up*extrap_up);
    totdo_pr = sqrt(stat_pr*stat_pr + syst_down*syst_down + extrap_down*extrap_down);
    
    // cout << q2_pr << "  "<< x_pr << "  "<< f2b_pr << "  "<< stat_pr << "  "<< syst_up << "  " << syst_down << "  " << extrap_up << "  " << extrap_down << endl;
    
    incvtx_pr->SetPoint(i-1, q2_pr, (f2b_pr +  0.03*shift_pr[i-1]));
    incvtx_pr->SetPointError(i-1,0,0,stat_pr,stat_pr);
    incvtx1_pr->SetPoint(i-1, q2_pr, (f2b_pr +  0.03*shift_pr[i-1]));
    incvtx1_pr->SetPointError(i-1,0,0,totdo_pr,totup_pr);
    
  }
  
  incvtx_pr->SetMarkerStyle(20);
  incvtx_pr->SetMarkerColor(kBlack);
  incvtx1_pr->SetMarkerStyle(20);
  incvtx_pr->SetMarkerSize(1.1);
  incvtx1_pr->SetMarkerSize(0.8);
  incvtx_pr->SetLineWidth(2);
  incvtx1_pr->SetLineWidth(2);
  incvtx1_pr->SetMarkerColor(kRed);
  incvtx1_pr->Draw("E,Z,same");
  incvtx_pr->Draw("EP,same");
   
  ZEUS_VERTEX.close();

  //draw legend
  TLegend *leg_f2b = new TLegend(0.4959677,0.7752976,0.8387097,0.9494048,NULL,"brNDC");
  leg_f2b->SetBorderSize(0);
  leg_f2b->SetTextFont(62);
  leg_f2b->SetTextSize(0.02827381);
  leg_f2b->SetLineColor(1);
  leg_f2b->SetLineStyle(1);
  leg_f2b->SetLineWidth(1);
  leg_f2b->SetFillColor(19);
  leg_f2b->SetFillStyle(0);
  leg_f2b->AddEntry(incvtx_pr,"ZEUS vtx 354 pb^{-1}","P");
  leg_f2b->AddEntry(btoe_rs,"ZEUS e 363 pb^{-1}","P");
  leg_f2b->AddEntry(btomu_bk,"ZEUS #mu 114 pb^{-1}","P");
  leg_f2b->AddEntry(btomu_mc,"ZEUS #mu+vtx 126 pb^{-1}","P");
  leg_f2b->AddEntry(incvtx_h1,"H1 vtx 246 pb^{-1}","P");

  leg_f2b->Draw("ndc,same");

  TLegend *leg_f2b1 = new TLegend(0.6471774,0.5327381,0.9133065,0.7559524,NULL,"brNDC");
  leg_f2b1->SetBorderSize(0);
  leg_f2b1->SetTextFont(62);
  leg_f2b1->SetTextSize(0.02827381);
  leg_f2b1->SetLineColor(1);
  leg_f2b1->SetLineStyle(1);
  leg_f2b1->SetLineWidth(1);
  leg_f2b1->SetFillColor(19);
  leg_f2b1->SetFillStyle(0);
  leg_f2b1->AddEntry(zeuss_gr_dummy,"HERAPDF 1.5","F");
  leg_f2b1->AddEntry(abkm_gr_dummy,"ABKM NNLO","L");
  //leg_f2b1->AddEntry(abkm_my_gr_dummy,"ABKM NNLO (my)","L");
  leg_f2b1->AddEntry(mstw_gr_dummy,"MSTW08 NLO","L");
  leg_f2b1->AddEntry(mstw_nnlo_gr_dummy,"MSTW08 NNLO","L");
  leg_f2b1->AddEntry(cteq_gr_dummy,"CTEQ6.6 NLO","L");
  leg_f2b1->AddEntry(jr09_gr_dummy,"JR09","L");
  leg_f2b1->Draw("ndc,same");

  //draw lines for x values
  TLine *l_x1 = new TLine(1.9, 0.03,1000,0.03);
  l_x1->SetLineColor(kBlack);
  l_x1->SetLineWidth(1);
  l_x1->SetLineStyle(1);
  l_x1->Draw("same");
  TLine *l_x2 = new TLine(2, 0.06,100,0.06);
  l_x2->SetLineColor(kBlack);
  l_x2->SetLineWidth(1);
  l_x2->SetLineStyle(1);
  l_x2->Draw("same");
  TLine *l_x3 = new TLine(2, 0.09,100,0.09);
  l_x3->SetLineColor(kBlack);
  l_x3->SetLineWidth(1);
  l_x3->SetLineStyle(1);
  l_x3->Draw("same");
  TLine *l_x4 = new TLine(2, 0.12,50,0.12);
  l_x4->SetLineColor(kBlack);
  l_x4->SetLineWidth(1);
  l_x4->SetLineStyle(1);
  l_x4->Draw("same");
  TLine *l_x5 = new TLine(2, 0.15,50,0.15);
  l_x5->SetLineColor(kBlack);
  l_x5->SetLineWidth(1);
  l_x5->SetLineStyle(1);
  l_x5->Draw("same");
  TLine *l_x6 = new TLine(2, 0.18,20,0.18);
  l_x6->SetLineColor(kBlack);
  l_x6->SetLineWidth(1);
  l_x6->SetLineStyle(1);
  l_x6->Draw("same");
  TLine *l_x7 = new TLine(2, 0.21,20,0.21);
  l_x7->SetLineColor(kBlack);
  l_x7->SetLineWidth(1);
  l_x7->SetLineStyle(1);
  l_x7->Draw("same");

  //write text for x shift values
  TLatex t_x0;
  //t_x0.SetTextAlign(23);
  t_x0.SetTextAngle(0);
  t_x0.SetTextSize(0.035);
  t_x0.DrawLatex(2.5,0.003, "x=0.032 i=0");
  TLatex t_x1;
  t_x1.SetTextAngle(0);
  t_x1.SetTextSize(0.035);
  t_x1.DrawLatex(2.5,0.022, "x=0.013 i=1");
  TLatex t_x2;
  t_x2.SetTextAngle(0);
  t_x2.SetTextSize(0.035);
  t_x2.DrawLatex(2.5,0.052, "x=0.005 i=2");
  TLatex t_x3;
  t_x3.SetTextAngle(0);
  t_x3.SetTextSize(0.035);
  t_x3.DrawLatex(2.5,0.082, "x=0.002 i=3");
  TLatex t_x4;
  t_x4.SetTextAngle(0);
  t_x4.SetTextSize(0.035);
  t_x4.DrawLatex(2.5,0.112, "x=0.0013 i=4");
  TLatex t_x5;
  t_x5.SetTextAngle(0);
  t_x5.SetTextSize(0.035);
  t_x5.DrawLatex(2.5,0.142, "x=0.0005 i=5");
  TLatex t_x6;
  t_x6.SetTextAngle(0);
  t_x6.SetTextSize(0.035);
  t_x6.DrawLatex(2.5,0.172, "x=0.0002 i=6");
  TLatex t_x7;
  t_x7.SetTextAngle(0);
  t_x7.SetTextSize(0.035);
  t_x7.DrawLatex(2.5,0.202, "x=0.00013 i=7");

  gPad->SetLogx();
  c_f2b->SaveAs("Plots/F2b_q2.eps");
  c_f2b->SaveAs("Plots/F2b_q2.root");
  c_f2b->SaveAs("Plots/F2b_q2.C");
}
//______________________________________________________________________________

TGraphAsymmErrors* ZEUS_S(Float_t xmy, Int_t shift, Float_t q2min, Float_t q2max){

  ifstream zeuss_file;
  char *filename = ("ZEUS_S/F2b_zeuss_curves.dat");
  cout << filename << endl;
  zeuss_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraphAsymmErrors *zeuss_gr=new TGraphAsymmErrors(nbins);

  for (Int_t i =1; i <=48; i++) {
    Float_t q2, xx, f2b, f2bup, f2bdo;
  
    zeuss_file >> q2 >> xx >> f2b >> f2bup >> f2bdo;
    //cout << q2 << "  " << xx << "  "<< f2b << "  "<< f2bup << "  "<< f2bdo << endl;
    
    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 << "  x_my =  " << xtmp << "  "<< f2b << "  " << nbins << endl;
	zeuss_gr->SetPoint(nbins-1, q2, f2b + (0.03*shift));
	zeuss_gr->SetPointError(nbins-1, 0, 0, (f2b+(0.03*shift))-(f2bdo+(0.03*shift)), (f2bup+(0.03*shift))-(f2b+(0.03*shift)));
      }
    }
  }
  zeuss_file.close();
  
  return zeuss_gr;

}
//______________________________________________________________________________

TGraphAsymmErrors* HERAPDF(Float_t xmy, Int_t shift, Float_t q2min, Float_t q2max){

  ifstream herapdf_file;
  char *filename = ("HERAPDF/F2_herapdf.txt");
  cout << filename << endl;
  herapdf_file.open(filename);

  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp;

  TGraphAsymmErrors *herapdf_gr=new TGraphAsymmErrors(nbins);
    cout << q2min << " " << q2max << endl;
  for (Int_t i =1; i <=64; i++) {
    Float_t q2, xx, f2b, f2bup, f2bdo;
  
    herapdf_file >> q2 >> xx >> f2b >> f2bup >> f2bdo;
    //cout << q2 << "  " << xx << "  "<< f2b << "  "<< f2bup << "  "<< f2bdo << endl;

    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
        cout << q2 << "  " << xx << "  "<< f2b << "  "<< f2bup << "  "<< f2bdo << endl;
	nbins++;
	//cout << "q2_my = " << q2 << "  x_my =  " << xtmp << "  "<< f2b << "  " << nbins << endl;
	herapdf_gr->SetPoint(nbins-1, q2, f2b + (0.03*shift));
	herapdf_gr->SetPointError(nbins-1, 0, 0, (f2b+(0.03*shift))-(f2bdo+(0.03*shift)), (f2bup+(0.03*shift))-(f2b+(0.03*shift)));
      }
    }
  }
  herapdf_file.close();
  
  return herapdf_gr;

}
//______________________________________________________________________________

TGraph* JR09(const char* xvalue, Int_t shift, Float_t q2min, Float_t q2max){

  ifstream jr09_file;
  char *filename = Form("JR09/F2b_JR09_%s.dat", xvalue);
  cout << filename << endl;
  jr09_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
 
  TGraph *jr09_gr=new TGraph(nbins);

  for (Int_t i =1; i <=11; i++) {
    Float_t xx, q2, f2b, err;
  
    jr09_file >> xx >> q2 >> f2b >> err;
    //cout << xx << "  " << q2 << "  "<< f2b << "  "<< err << endl;
    
    if (q2 >= q2min && q2 <= q2max){
      nbins++;
      //cout << "q2_my = " << q2 <<"  "<< f2b << "  " << nbins << endl;
      jr09_gr->SetPoint(nbins-1, q2, f2b + (0.03*shift));
    }
  }
  jr09_file.close();
  
  return jr09_gr;
}
//______________________________________________________________________________

TGraph* ABKM(const char* xvalue, Int_t shift, Float_t q2min, Float_t q2max){

  ifstream abkm_file;
  char *filename = Form("ABKMF2B/f2bb_%s_ffn3_nnlo", xvalue);
  cout << filename << endl;
  abkm_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
   
  TGraph *abkm_gr=new TGraph(nbins);

  for (Int_t i =1; i <=60; i++) {
    Float_t q2, f2, err;
  
    abkm_file >> q2 >> f2 >> err;
    //cout << q2 <<"  "<< f2 <<"  "<< err << "  "<< nbins << endl;
    
    if (q2 >= q2min && q2 <= q2max){
      nbins++;
      //cout << "q2_my = " << q2 <<"  "<< f2 <<"  "<< err << "  " << nbins << endl;
      abkm_gr->SetPoint(nbins-1, q2, f2 + (0.03*shift));
    }
  }
  abkm_file.close();
  
  return abkm_gr;
}

//______________________________________________________________________________

TGraph* ABKM_MY(Float_t xmy, Int_t shift, Float_t q2min, Float_t q2max){

  //just for testing some output (obtained from code philipp sent around)
  ifstream abkm_my_file;
  char *filename = ("ABKMF2B/abkm_my_fix_alpha.dat");
  cout << filename << endl;
  abkm_my_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;
   
  TGraph *abkm_my_gr=new TGraph(nbins);

  for (Int_t i =1; i <=1600; i++) {
    Float_t q2, xx, f2b1, f2b2;
    //  first column: momentum transferred in GeV^2, second column: x, third column: 3-flavour FFNS value of F_2^bb at the NNLO, 4-th column: the same at NLO

    abkm_my_file >> q2 >> xx >> f2b1 >> f2b2;
    //cout << q2 <<"  "<< xx << "  " << f2b1 <<"  "<< f2b2 << "  "<< nbins << endl;
    
    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	nbins++;
	//cout << "q2_my = " << q2 <<"  "<< xx << "  " << f2b1 <<"  "<< f2b2 << "  " << nbins << endl;
	abkm_my_gr->SetPoint(nbins-1, q2, f2b1 + (0.03*shift));
      }
    }
  }
  abkm_my_file.close();
  
  return abkm_my_gr;
}
//______________________________________________________________________________

TGraph* MSTW(const char* xvalue, Int_t shift, Float_t q2min, Float_t q2max){

  ifstream mstw_file;
  char *filename = Form("MSTW/output.nlo.grid.%s.dat", xvalue);
  cout << filename << endl;
  mstw_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
 
  TGraph *mstw_gr=new TGraph(nbins);

  for (Int_t i =1; i <=24; i++) {
    Float_t q2, xx, f2, fl, f2c, flc, f2b, flb;
  
    mstw_file >> q2 >> xx >> f2 >> fl >> f2c >> flc >> f2b >> flb;
    //cout << q2 << "  " << xx << "  "<< f2 << "  "<< fl << "  "<< f2c << "  "<< flc << "  "<< f2b << "  "<< flb << endl;
    
    if (q2 >= q2min && q2 <= q2max){
      nbins++;
      //cout << "q2_my = " << q2 <<"  "<< f2b << "  " << nbins << endl;
      mstw_gr->SetPoint(nbins-1, q2, f2b + (0.03*shift));
    }
  }
  mstw_file.close();
  
  return mstw_gr;
}

//______________________________________________________________________________

TGraph* MSTW_NNLO(const char* xvalue, Int_t shift, Float_t q2min, Float_t q2max){

  ifstream mstw_nnlo_file;
  char *filename = Form("MSTW/output.nnlo.grid.%s.dat", xvalue);
  cout << filename << endl;
  mstw_nnlo_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
 
  TGraph *mstw_nnlo_gr=new TGraph(nbins);

  for (Int_t i =1; i <=24; i++) {
    Float_t q2, xx, f2, fl, f2c, flc, f2b, flb;
  
    mstw_nnlo_file >> q2 >> xx >> f2 >> fl >> f2c >> flc >> f2b >> flb;
    //cout << q2 << "  " << xx << "  "<< f2 << "  "<< fl << "  "<< f2c << "  "<< flc << "  "<< f2b << "  "<< flb << endl;
    
    if (q2 >= q2min && q2 <= q2max){
      nbins++;
      //cout << "q2_my = " << q2 <<"  "<< f2b << "  " << nbins << endl;
      mstw_nnlo_gr->SetPoint(nbins-1, q2, f2b + (0.03*shift));
    }
  }
  mstw_nnlo_file.close();
  
  return mstw_nnlo_gr;
}

//______________________________________________________________________________

TGraph* CTEQ(Float_t xmy, Float_t q2min, Float_t q2max){

  ifstream cteq_file;
  char *filename = ("CTEQ/F2b_cteq.dat");
  cout << filename << endl;
  cteq_file.open(filename);

  Float_t q2min, q2max;
  Int_t shift;
  Int_t nbins =0;
  Float_t xtmp, xmy;

  TGraph *cteq_gr=new TGraph(nbins);

  for (Int_t i =1; i <=3992; i++) {
    Float_t xx, q2, f2b;
  
    cteq_file >> xx >> q2 >> f2b;
    //cout << xx << "  " << q2 << "  "<< f2b << endl;
    
    xtmp = xx;
    if (xtmp == xmy) {
      if (q2 >= q2min && q2 <= q2max){
	//cout << "x_my = " << xtmp << "  q2_my =  " << q2 << "  "<< f2b << "  " << nbins << endl;
	nbins++;
	cteq_gr->SetPoint(nbins-1, q2, f2b);
      }
    }
  }
  cteq_file.close();
  
  return cteq_gr;

}
