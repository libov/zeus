#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TFile.h>
#include <TROOT.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif
Double_t as_db_gaus_pol1(Double_t *x,Double_t *par)
{
	// This is double gaussian with one of them assymetric(with 2 different sigma for <mean and >mean regions)
	// Parameters:
	//gaus 1:	par[0] - constant
	//		par[1] - mass
	//		par[2] - sigma
	//gaus 2:	par[3] - constant
	//		par[1] - mass
	//		par[4] - sigma(left)
	//		par[7] - sigma(right)
	//polynom	par[5] - A
	// (A+Bx)	par[6] - B
	Double_t 	gaus1=0,
			gaus2left=0,
			gaus2right=0,
			pol1=0;
	gaus1=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gaus2left=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[4]*par[4]));
	gaus2right=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[7]*par[7]));
	pol1=par[5]+par[6]*x[0];
	if(x[0]<=par[1]) return gaus1+gaus2left+pol1;
	if(x[0]>par[1]) return gaus1+gaus2right+pol1;
}

Double_t asymmetric_gaus(Double_t *x,Double_t *par)
{
	// This is asymmetric gaussian
	// par[0] - constant; par[1] - mean (mass); par[2] - left sigma; par[3] - right sigma;
	Double_t	gausleft=0,
			gausright=0;

	gausleft=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gausright=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[3]*par[3]));
	if (x[0]<=par[1]) return gausleft;
	if (x[0]>par[1]) return gausright;
}


void HERAII()
{

	TChain *myChain=new TChain("resonance");

	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/2004.root");
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/2005RP.root");
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/2006eRP.root");
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/2007pRP.root");
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/2006pRP.root");

	Int_t		nv0=0,          // number K0s candidates that passed soft selection
			id1[10],        // id of the first track
			id2[10],        // id of the second track
			Runnr;          // Run number
	Float_t		p1[10][3],	// momenta of 1st track
			p2[10][3],	// momenta of 2nd track
			coll2[10],	// collinearity angle 2D
			coll3[10];	// collinearity angle 3D

	Float_t		angle=0,        // angle between K0s
			cos_angle=0;    // cos of this angle

	const Int_t 	low_2004=47010,
			up_2004=51245,
			low_2005=52244,
			up_2005=57123,
			low_2006=58181,
			up_2006=59947,
			low_2006p=60005,
			up_2006p=61746,
			low_2007=61747,
			up_2007=62638;
	const Float_t	corr_2004=1.005,
			corr_2005=1.009,
			corr_2006=1.0077,
			corr_2007=1.0065;

	myChain->SetBranchAddress("nv0",&nv0);
	myChain->SetBranchAddress("p1",p1);
	myChain->SetBranchAddress("p2",p2);
	myChain->SetBranchAddress("coll2",coll2);
	myChain->SetBranchAddress("coll3",coll3);
	myChain->SetBranchAddress("id1",id1);
	myChain->SetBranchAddress("id2",id2);
	myChain->SetBranchAddress("runnr",&Runnr);

	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<" events here"<<endl;

	Float_t		//corr=1.005;
			corr=1.00000;
	TH1F *h=new TH1F("h","K0sK0s in DIS",200,0.8,5);
	TH1F *h1=new TH1F("h1","K0sK0s in DIS",280,0.8,5);
	TH1F *h_eta1II=new TH1F("h_eta1II","K0sK0s",200,0.8,5);
	TH1F *h_eta2II=new TH1F("h_eta2II","K0sK0s",200,0.8,5);
	TH1F *h_eta3II=new TH1F("h_eta3II","K0sK0s",200,0.8,5);
	TH1F *hd1=new TH1F("hd1","debug1",20,0,20);
	TH1F *hd2=new TH1F("hd2","debug2",20,0,20);
	TH1F *ha=new TH1F("ha","angle between two K0s ",100,0,180);
	TH1F *hfake=new TH1F("hfake","",280,0.8,5);
	TH1F *hinv_base=new TH1F("hinv_base",">=2 K0s",60,450,552);
	TH1F *hinv1=new TH1F("hinv1","K0s",60,450,552);
	TH1F *hphi=new TH1F("phi","azimutal K0s angle distr",100,0,360);
	TH2F *hpxpy=new TH2F("px_vs_py","K0s: Px vs Py",50,-1,1,50,-1,1);

	//**************************************************************************
	TH1F *myobject;
	TClonesArray a("TH1F",20);
	new(a[1]) TH1F("pt1","K0s inv mass",60,450,552);
	new(a[2]) TH1F("pt2","K0s inv mass",60,450,552);
	new(a[3]) TH1F("pt3","K0s inv mass",60,450,552);
	new(a[4]) TH1F("pt4","K0s inv mass",60,450,552);
	new(a[5]) TH1F("pt5","K0s inv mass",60,450,552);
	new(a[6]) TH1F("pt6","K0s inv mass",60,450,552);
	new(a[7]) TH1F("pt7","K0s inv mass",60,450,552);
	new(a[8]) TH1F("pt8","K0s inv mass",60,450,552);
	new(a[9]) TH1F("pt9","K0s inv mass",60,450,552);
	new(a[10]) TH1F("pt10","K0s inv mass",60,450,552);
	new(a[11]) TH1F("pt11","K0s inv mass",60,450,552);
	new(a[12]) TH1F("pt12","K0s inv mass",60,450,552);
	new(a[13]) TH1F("pt13","K0s inv mass",60,450,552);
	new(a[14]) TH1F("pt14","K0s inv mass",60,450,552);
	new(a[15]) TH1F("pt15","K0s inv mass",60,450,552);
	new(a[16]) TH1F("pt16","K0s inv mass",60,450,552);
	new(a[17]) TH1F("pt17","K0s inv mass",60,450,552);
	new(a[18]) TH1F("pt18","K0s inv mass",60,450,552);
	new(a[19]) TH1F("pt19","K0s inv mass",60,450,552);
	new(a[20]) TH1F("pt20","K0s inv mass",60,450,552);
	new(a[21]) TH1F("pt21","K0s inv mass",60,450,552);
	new(a[22]) TH1F("pt22","K0s inv mass",60,450,552);
	new(a[23]) TH1F("pt23","K0s inv mass",60,450,552);
	new(a[24]) TH1F("pt24","K0s inv mass",60,450,552);
	new(a[25]) TH1F("pt25","K0s inv mass",60,450,552);
	new(a[26]) TH1F("pt26","K0s inv mass",60,450,552);
	new(a[27]) TH1F("pt27","K0s inv mass",60,450,552);
	new(a[28]) TH1F("pt28","K0s inv mass",60,450,552);
	new(a[29]) TH1F("pt29","K0s inv mass",60,450,552);
	new(a[30]) TH1F("pt30","K0s inv mass",60,450,552);

	//***************************************************************************

	Double_t convert=180/TMath::Pi();
	Double_t phi=0;
	Int_t 	goa=0,year=0,err=0;
	Float_t reso_mass=0;
	for (Int_t i=0;i<nevents;i++)
	{
		myChain->GetEntry(i);
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		Int_t	cand_k0=0,
			list_k0[30];

		//////////////////////////////////////////////////
		// momenta correction
		/*year=0;
		if  ((Runnr>=low_2004)&&(Runnr<=up_2004)) year=2004;
		if  ((Runnr>=low_2005)&&(Runnr<=up_2005)) year=2005;
		if  ((Runnr>=low_2006)&&(Runnr<=up_2006)) year=2006;
		if  ((Runnr>=low_2006p)&&(Runnr<=up_2006p)) year=2006;
		if  ((Runnr>=low_2007)&&(Runnr<=up_2007)) year=2007;

		switch (year)
		{
			case 2004: corr=corr_2004; break;
			case 2005: corr=corr_2005; break;
			case 2006: corr=corr_2006; break;
			case 2007: corr=corr_2007; break;
			case 0: {corr=1.00000; err++;} break;
		}*/
		////////////////////////////////////////////////////

		//K0s cand selection
		for(Int_t k=0;k<nv0;k++)
		{
			hd1->Fill(1);
			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
			Mother K0s_cand(t1,t2);
			Float_t pabs1=t1.GetP();
			Float_t pabs2=t2.GetP();
			Float_t mass_pi_p=0;
			if (pabs1>pabs2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (pabs1<pabs2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}
			if (coll2[k]>0.12) continue;  //.1              .12
			if(mass_pi_p<1.121) continue; //1.121        1.121
			hd1->Fill(2);
			if( K0s_cand.GetPx_m()>=0) phi=convert*acos((K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if( K0s_cand.GetPx_m()<0) phi=180-convert*acos(((-1)*K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if (K0s_cand.GetPy_m()<=0)
			{
				phi=360-phi;
			}
			if (K0s_cand.GetPt_m()<0.25) continue;  //.3        .25
			hd1->Fill(3);
			if (TMath::Abs(K0s_cand.GetEta_m())>1.6) continue;// 1.75    1.6
			hd1->Fill(4);
			hd1->Fill(5);
			hpxpy->Fill(K0s_cand.GetPx_m(),K0s_cand.GetPy_m());
			//if (coll3[k]>0.24) continue; // comment                .24
			hd1->Fill(6);
			hinv1->Fill(1000*K0s_cand.GetMass_m(4,4));
			//if ((K0s_cand.GetMass_m(4,4)<0.481)||(K0s_cand.GetMass_m(4,4)>0.5177)) continue;   //.4777 .5177       0.481  0.515
			hphi->Fill(phi);
			hd1->Fill(7);
			list_k0[cand_k0]=k;
			cand_k0++;
		}
		//K0s combining
		if (cand_k0<2) continue;
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t id=list_k0[k];
			Daughter t1temp(corr*p1[id][0],corr*p1[id][1],corr*p1[id][2]);
			Daughter t2temp(corr*p2[id][0],corr*p2[id][1],corr*p2[id][2]);
			Mother K0s_candtemp(t1temp,t2temp);
			/*Float_t pabs1=t1temp.GetP();
			Float_t pabs2=t2temp.GetP();
			Float_t mass_pi_p=0;
			if (pabs1>pabs2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_candtemp.GetMass_m(6,4);
			}
			if (pabs1<pabs2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_candtemp.GetMass_m(4,6);
			}
			*/
			hinv_base->Fill(1000*K0s_candtemp.GetMass_m(4,4));
			for(int u=1;u<31;u++)
			{
				if (coll3[id]<(0.05+0.01*u)) ((TH1F *)a.At(u))->Fill(1000*K0s_candtemp.GetMass_m(4,4));
			}
		}
	}
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/temporary.root","recreate");

	h->Write();
	h1->Write();
	hpxpy->Write();
	hd1->Write();
	hd2->Write();
	ha->Write();
	hinv_base->Write();
	hinv1->Write();
	h_eta1II->Write();
	h_eta2II->Write();
	h_eta3II->Write();
	hphi->Write();
	hfake->Write();

	//************************************************************************************************
	Double_t 	signal[50],
			s_to_b[500];
	for(int u=1;u<31;u++)
	{
		myobject=((TH1F *)a.At(u));

		Float_t		histRangeLow=450,
				histRangeUp=552,
				histRange=histRangeUp-histRangeLow,
				bin_width=histRange/60;
		//gStyle->SetOptFit(1111);
		myobject->GetYaxis()->SetTitle("MeV");
		myobject->GetYaxis()->SetTitle("Entries");
		TF1 *fgaus=new TF1("fgaus","gaus",483,507);
		fgaus->SetLineWidth(2);
		TF1 *fpol1=new TF1("fpol1","pol1",histRangeLow,histRangeUp);
		fpol1->SetLineWidth(2);
		Double_t par[10];
		myobject->Fit("fgaus","NR");
		myobject->Fit("fpol1","NR");
		Double_t 	init_const1=0,
				init_const2=0,
				init_sigma1=0,
				init_sigma2=0,
				init_mass=0,
				init_A=0,
				init_B=0;

		fgaus->GetParameters(&par[0]);
		fpol1->GetParameters(&par[3]);
		init_const1=par[0];
		init_const2=par[0]/3;
		init_mass=par[1];
		init_sigma1=par[2]/2;
		init_sigma2=2*par[2];
		init_A=par[3];
		init_B=par[4];

		TF1 *fsum=new TF1("fsum",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
		fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
		fsum->SetParNames("Constant1","Mass","Sigma1","Constant2","LeftSigma2","A","B","Rightsigma2");
		fsum->SetLineColor(2);
		fsum->SetLineWidth(2);
		//fsum->Draw("same");
		myobject->Fit("fsum","R+");
		fsum->GetParameters(&par[0]);
		fpol1->SetParameters(&par[5]);
		Double_t 	range_low=par[1]-25,
				range_up=par[1]+25;
		Double_t	Signal=0,
				Background=0,
				K0cand=0;

		Signal=fsum->Integral(range_low,range_up)/bin_width;
		Background=fpol1->Integral(range_low,range_up)/bin_width;
		K0cand=Signal-Background;
		cout<<"Histo number "<<u<<": "<<K0cand/Signal<<" <--> "<<K0cand<<endl;
		signal[u-1]=K0cand;
		s_to_b[u-1]=K0cand/Signal;
		TF1 *fgaus1=new TF1("fgaus1","gaus",histRangeLow,histRangeUp);
		TF1 *fgaus2=new TF1("fgaus2",asymmetric_gaus,histRangeLow,histRangeUp,4);
		fgaus1->SetLineWidth(2);
		fgaus2->SetLineWidth(2);
		fgaus1->SetParameters(par[0],par[1],par[2]);
		fgaus2->SetParameters(par[3],par[1],par[4],par[7]);
		fgaus1->Draw("same");
		fgaus2->Draw("same");
		TF1 *fline=new TF1("fline","pol1",histRangeLow,histRangeUp);
		fline->SetParameters(par[5],par[6]);
		fline->SetLineColor(7);
		fline->SetLineStyle(7);
		fline->Draw("same");
		myobject->Write();
		cout<<"OK"<<endl;
	}

	/*for(int u=1;u<11;u++)
	{
		cout<<signal[u-1]<<endl;
		Int_t ssd=(int)sign[u-1];
		cout<<ssd<<"   ssssss"<<endl;
		hpt->SetBinContent(u,ssd);
	}
	hpt->Write();*/

	Double_t cut[50];
	for(int u=0;u<30;u++) {cut[u]=0.05+0.01*u;  cout<<"x["<<u<<"]="<<cut[u]<<"; y1["<<u<<"]="<<signal[u]<<"; y["<<u<<"]="<<s_to_b[u]<<";"<<endl;}


	/*TGraph *compare = new TGraph(19,cut,signal);
	compare->SetMarkerStyle(7);
	compare->Draw("ap");
	compare->Write();*/
	//**************************************************************************************************


	f1->Close();
	cout<<err<<" errors"<<endl;
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	HERAII();
	return 0;
}
#endif

