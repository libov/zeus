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
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_Olaf.root");


	TH1F *htemp = (TH1F*)f1->Get("hinv_K0s_47_55");
	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/TEMPSHIT.root","recreate");
	K0s_fit *temp=new K0s_fit(htemp);
	temp->Fit();
	temp->Draw();
	temp->Draw_fsum();
	temp->Draw_fbg();
	temp->Draw_Signal();
	temp->Print();
	c1->Write();
	f2->Close();
	f1->Close();



}
#ifndef __CINT__
int main(int argc, char **argv)
{
	anal();
	return 0;
}
#endif

