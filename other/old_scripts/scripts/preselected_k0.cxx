//***************************************************
//  27.02.2008
//
//***************************************************
{

  gROOT->Reset();
  gROOT->SetStyle("Plain");
TCanvas *au1 = new TCanvas("au1","ZEUS",5,85,600,400);

TChain * nt_tracks=new TChain("ntK0");
//nt_tracks->Add("nt_K0/test50kev.root");
nt_tracks->Add("/data/zenith220a/aushev/Phys_analysis/K0K0_PQ/K0_BATCH/test_10kev.root");

Float_t range0=400.0, range1=600.0;
Float_t gaus_range0=485.0, gaus_range1=510.0;
Int_t nch=70;
Float_t calcoef=1.0;
calcoef = (range1 - range0)/nch;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
au1->Divide(2,1);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Char_t cut1[1000];
sprintf(cut1,"theta1>40&&theta1<140&&angle_rp<3&&layout1>3&&layout2>3");
//&&theta2>40&&theta2<140&&angle_rp<10&&trk_nvert>1&&trk_nvert<15&&Ncand_K0<15&&PrimZ<30&&PrimZ>-30&&dlen2<20&&ctau<13.0&&dlen3<30&&layout1>1&&layout2>1&&vtxChi2<20&&vtxChi2<50
//>>>>>>>>>>>
au1->cd(1);

TH1F * h_m = new TH1F("h_m"," Mass K0", nch , range0, range1);
h_m->SetLineColor(1);
h_m->SetMinimum(0);
h_m->GetXaxis()->SetTitle("Entries ");
h_m->GetYaxis()->SetTitle("mass ");
nt_tracks->Draw("1000*massK0>>h_m",cut1,"");

//

//............. Fit .....................
f_sum1= new TF1("f_sum1","gaus(0) + pol1(3)",400.,600.);
f_sum1->SetParameters(10000.0,497.,5.0);
f_sum1->SetLineColor(2);
h_m->Fit("f_sum1","R");

 Float_t xx = f_sum1->GetParameter(1);
 Float_t e_xx = f_sum1->GetParError(1);
// cout<<"Mass= " << xx <<"  +-"<<e_xx<<endl;
cout<<"Mass shift= " << xx -497.648 <<"  +-"<<e_xx<<endl;
Float_t wid = f_sum1->GetParameter(2);
Float_t widErr = f_sum1->GetParError(2);
cout<<"Mass resolution= " <<wid<<"  +-"<< widErr <<endl;

f_g= new TF1("f_g","gaus(0)",gaus_range0,gaus_range1);
Double_t par[5];
f_sum1->GetParameters(par);
f_g->SetParameters(&par[0]);
 f_g->SetLineColor(5);
 f_g->Draw("same");
 Float_t sumpeak=0;
sumpeak=f_g->Integral(gaus_range0,gaus_range1)/calcoef;
cout<<"peak sum= " <<sumpeak <<endl;

//>>>>>>>>>>>
au1->cd(2);

TH2F * h_theta_P_K0 = new TH2F("h_theta_P_K0","", 100 , -1.0, 1.0, 100, 0.0, 0.35);
h_theta_P_K0->SetMarkerStyle(20);
h_theta_P_K0->SetMarkerSize(0.3);
h_theta_P_K0->SetMarkerColor(3);
h_theta_P_K0->GetXaxis()->SetTitle("alpha ");
h_theta_P_K0->GetYaxis()->SetTitle("Track Pt to K0");
nt_tracks->Draw("Pt_to_K0:alpha>>h_theta_P_K0",cut1,"");

//nt_tracks->Draw("vtxChi2:1000*massK0>>h_theta_P_K0",cut1,"contz");
//contz

}

