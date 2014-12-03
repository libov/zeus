#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TVector3.h>
#include <TVector2.h>
#include <TROOT.h>
//#include <canvas.cxx>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
using namespace std;
#include<K0s_fit.h>
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
	c1->Divide(48,64);

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_Olaf.root");

	ofstream myfile;
  	myfile.open ("k0_da.txt");

	Int_t	counter=0;

	TH2F *htheta_vs_pt=new TH2F("htheta_vs_pt","",48,30,150,64,0.4,2);

	for (Int_t bin_th=0;bin_th<48;bin_th++)
	{
		for (Int_t bin_pt=0;bin_pt<64;bin_pt++)
		{
			counter++;
			char 	hist[50];
			Int_t 	n=sprintf(hist,"hinv_K0s_%d_%d",bin_th,bin_pt);
			TH1F *htemp = (TH1F*)f1->Get(hist);
			//K0s_fit		temp(htemp);
			K0s_fit *temp=new K0s_fit(htemp);
			temp->Fit();
			Int_t	K0=(Int_t)temp->GetK0cand();
			cout<<hist<<" "<<counter<<": "<<K0<<endl;;
			c1->cd(counter);
			temp->Draw();
			temp->Draw_fsum();
			temp->Draw_fbg();
			temp->Draw_Signal();

			myfile << bin_th+1<<"   "<<bin_pt+1<<"   "<<K0<<endl;
			if (K0<10000) htheta_vs_pt->SetBinContent(bin_th+1,bin_pt+1,K0);

		}
	}

	//f1->Close();
  	//myfile.close();

	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/PROBA.root","recreate");
	c1->Write();
	htheta_vs_pt->Write();
	f2->Close();

	f1->Close();
  	myfile.close();
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	anal();
	return 0;
}
#endif

