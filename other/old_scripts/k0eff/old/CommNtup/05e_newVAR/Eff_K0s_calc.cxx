#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TVector3.h>
#include <TVector2.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
using namespace std;
#endif
void anal()
{
	TCanvas *c1 = new TCanvas("c1", "c1",14,31,700,500);
   	c1->Range(0.275,-234.806,5.525,2113.26);
   	c1->SetBorderSize(2);
   	c1->SetFrameFillColor(0);
	c1->SetFillColor(0);
   	c1->ToggleToolBar();
	c1->ToggleEventStatus();
	c1->ToggleEditor();
	c1->Divide(2,2);

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/re-run/05eDIS_DISON_QY.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/re-run/06pPHP_DISOFF.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/mcheraItest.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/theta_dependence/MC_ARI_MEPS/60_120.root");


//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/CommNtup/MCdijetPHPv2/40_140.root");

TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/CommNtup/Data05e/120_150.root");

	ofstream myfile;
	ofstream myfile1;
  	myfile.open ("/data/zenith226a/libov/k0eff/k0_da__00_xxxxxx.dat");
	myfile1.open ("/data/zenith226a/libov/k0eff/pi_da__00_xxxxxx.dat");

	Int_t	counter=0,
		counter1=0;

	TH2F *hsig=new TH2F("hsig","Background substracted K0",48,30,150,64,0.4,2);
	TH2F *hup=new TH2F("hup","Up sideband",48,30,150,64,0.4,2);
 	TH2F *hlow=new TH2F("hlow","Low sideband",48,30,150,64,0.4,2);
	TH2F *htot=new TH2F("htot","Total number",48,30,150,64,0.4,2);

	int n;
	Int_t	K0total_ptslow=0,
		K0total_ptvstheta=0;

	Int_t	signal[48][64];
	for (Int_t bin_th=0;bin_th<48;bin_th++)
	{
		for (Int_t bin_pt=0;bin_pt<64;bin_pt++)
		{
			counter++;
			char 	hist[50];
			Int_t 	n=sprintf(hist,"hinv_K0s_%d_%d",bin_th,bin_pt);
			TH1F *htemp = (TH1F*)f1->Get(hist);
			Int_t		K0=0,
					up=0,
					low=0,
					tot=0;

			for (int k=1;k<31;k++)
				low=low+(Int_t)htemp->GetBinContent(k);
			for (int k=31;k<91;k++)
				tot=tot+(Int_t)htemp->GetBinContent(k);
			for (int k=91;k<121;k++)
				up=up+(Int_t)htemp->GetBinContent(k);
			K0=tot-up-low;
			signal[bin_th][bin_pt]=K0;
			K0total_ptvstheta=K0total_ptvstheta+K0;
			cout<<hist<<" "<<counter<<": "<<low<<" "<<up<<" "<<tot<<" "<<K0<<endl;
			char string[40];
			n=sprintf(string,"%5d%5d%7d%7d%7d%7d",bin_th+1,bin_pt+1,tot,low,up,K0);
			myfile << string<<endl;

			hsig->SetBinContent(bin_th+1,bin_pt+1,K0);
			hup->SetBinContent(bin_th+1,bin_pt+1,up);
			hlow->SetBinContent(bin_th+1,bin_pt+1,low);
			htot->SetBinContent(bin_th+1,bin_pt+1,tot);
		}
	}

	for (Int_t bin_pt=0;bin_pt<68;bin_pt++)
	{
		counter1++;
		char 	hist[50];
		Int_t 	n=sprintf(hist,"hinv_K0s_%d",bin_pt);
		TH1F *htemp = (TH1F*)f1->Get(hist);

		Int_t		K0=0,
				up=0,
				low=0,
				tot=0;

		for (int k=1;k<31;k++)
			low=low+(Int_t)htemp->GetBinContent(k);
		for (int k=31;k<91;k++)
			tot=tot+(Int_t)htemp->GetBinContent(k);
		for (int k=91;k<121;k++)
			up=up+(Int_t)htemp->GetBinContent(k);
		K0=tot-up-low;
		K0total_ptslow=K0total_ptslow+K0;
		cout<<hist<<" "<<counter1<<": "<<low<<" "<<up<<" "<<tot<<" "<<K0<<endl;
		char string[40];
		n=sprintf(string,"%5d%7d%7d%7d%7d",bin_pt+1,tot,low,up,K0);
		myfile1 << string<<endl;
	}

	cout<<"Total number of K0 integrated over slow pion pt bins: "<<K0total_ptslow<<endl;
	cout<<"Total number of K0 integrated over  kaon pt vs theta bins: "<<K0total_ptvstheta<<endl;
	/*c1->cd(1); hsig->Draw("box");
	c1->cd(2); hlow->Draw("box");
	c1->cd(3); hup->Draw("box");
	c1->cd(4); htot->Draw("box");*/
TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/CommNtup/Data05e/ptVStheta/120_150.root","recreate");



	//c1->Write();
	hsig->Write();
	f2->Close();
	//------------------------ Kinematical distrbutions -----------------------------
TFile *f3 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/CommNtup/Data05e/other_distr/120_150.root","recreate");

	//--------- pT distributions ---------//
	TH1F *h_pt=new TH1F("h_pt","p_{T}(K_{0}) distribution",64,0.4,2);
	TH1F *h_pt_1=new TH1F("h_pt_1","p_{T}(K_{0}) distribution, 40<#theta<65",64,0.4,2);
	TH1F *h_pt_2=new TH1F("h_pt_2","p_{T}(K_{0}) distribution, 65<#theta<90",64,0.4,2);
	TH1F *h_pt_3=new TH1F("h_pt_3","p_{T}(K_{0}) distribution, 90<#theta<115",64,0.4,2);
	TH1F *h_pt_4=new TH1F("h_pt_4","p_{T}(K_{0}) distribution, 115<#theta<140",64,0.4,2);

	Int_t	tot_K0_1=0;
	Int_t	tot_K0_2=0;
	Int_t	theta1=0,
		theta2=0,
		theta3=0,
		theta4=0;

	for (Int_t bin_pt=0;bin_pt<64;bin_pt++)
	{

		theta1=0;
		theta2=0;
		theta3=0;
		theta4=0;
		for (Int_t bin_th=0;bin_th<12;bin_th++)
			theta1=theta1+signal[bin_th][bin_pt];
		for (Int_t bin_th=12;bin_th<24;bin_th++)
			theta2=theta2+signal[bin_th][bin_pt];
		for (Int_t bin_th=24;bin_th<36;bin_th++)
			theta3=theta3+signal[bin_th][bin_pt];
		for (Int_t bin_th=36;bin_th<48;bin_th++)
			theta4=theta4+signal[bin_th][bin_pt];

		Int_t	tot=0;
		tot=theta1+theta2+theta3+theta4;

		h_pt->SetBinContent(bin_pt+1,tot);
		h_pt_1->SetBinContent(bin_pt+1,theta1);
		h_pt_2->SetBinContent(bin_pt+1,theta2);
		h_pt_3->SetBinContent(bin_pt+1,theta3);
		h_pt_4->SetBinContent(bin_pt+1,theta4);

		tot_K0_1=tot_K0_1+tot;
	}

	//--------- theta distributions ---------//
	TH1F *h_th=new TH1F("h_th","#theta(K_{0}) distribution",48,40,140);
	TH1F *h_th_1=new TH1F("h_th_1","#theta(K_{0}) distribution, 0.4<p_{T}<0.8",48,40,140);
	TH1F *h_th_2=new TH1F("h_th_2","#theta(K_{0}) distribution, 0.8<p_{T}<1.2",48,40,140);
	TH1F *h_th_3=new TH1F("h_th_3","#theta(K_{0}) distribution, 1.2<p_{T}<1.6",48,40,140);
	TH1F *h_th_4=new TH1F("h_th_4","#theta(K_{0}) distribution, 1.6<p_{T}<2.0",48,40,140);

	Int_t	pt1=0,
		pt2=0,
		pt3=0,
		pt4=0;

	for (Int_t bin_th=0;bin_th<48;bin_th++)
	{
		pt1=0;
		pt2=0;
		pt3=0;
		pt4=0;

		for (Int_t bin_pt=0;bin_pt<16;bin_pt++)
			pt1=pt1+signal[bin_th][bin_pt];
		for (Int_t bin_pt=16;bin_pt<32;bin_pt++)
			pt2=pt2+signal[bin_th][bin_pt];
		for (Int_t bin_pt=32;bin_pt<48;bin_pt++)
			pt3=pt3+signal[bin_th][bin_pt];
		for (Int_t bin_pt=48;bin_pt<64;bin_pt++)
			pt4=pt4+signal[bin_th][bin_pt];

		Int_t	tot=0;
		tot=pt1+pt2+pt3+pt4;
		h_th_1->SetBinContent(bin_th+1,pt1);
		h_th_2->SetBinContent(bin_th+1,pt2);
		h_th_3->SetBinContent(bin_th+1,pt3);
		h_th_4->SetBinContent(bin_th+1,pt4);
		h_th->SetBinContent(bin_th+1,tot);

		tot_K0_2=tot_K0_2+tot;

	}

	h_pt->Write();
	h_pt_1->Write();
	h_pt_2->Write();
	h_pt_3->Write();
	h_pt_4->Write();
	h_th->Write();
	h_th_1->Write();
	h_th_2->Write();
	h_th_3->Write();
	h_th_4->Write();
	f3->Close();

	cout<<tot_K0_1<<" K0s in total"<<endl;
	cout<<tot_K0_2<<" K0s in total"<<endl;

	//----------------------------------------------------------------------------------------//

	f1->Close();
	myfile.close();
	myfile1.close();
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	anal();
	return 0;
}
#endif

