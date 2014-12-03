#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TFile.h>
#include <TROOT.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif
void analysis()
{
	TChain *myChain=new TChain("resonance");
	//myChain->Add("/data/zenith226a/libov/data/PHPtemp/v0_test004_06pRP_40_1.root");
	myChain->Add("/data/zenith226a/libov/data/PHPtemp/*.root");

	Int_t	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain;"<<endl;

	Int_t	Tltw[14];

	myChain->SetBranchAddress("Tltw", Tltw);
z
	TH1F *hpp1_fired=new TH1F("hpp1_fired","HPP TLT fired ",16,1,17);
	TH1F *hpp1_taken=new TH1F("hpp1_taken","HPP TLT taken",16,1,17);

	TH1F *hpp2_fired=new TH1F("hpp2_fired","HPP TLT fired",16,17,33);
	TH1F *hpp2_taken=new TH1F("hpp2_taken","HPP TLT taken",16,16,33);

	Bool_t 	HPP;
	Int_t	goa=0;


	for (int i=0;i<100000;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;

		myChain->GetEntry(i);
		Int_t	trig=0;
		for (int k=0;k<16;k++)
		{
			HPP = (Bool_t)(Tltw[4-1] & (1 << k) );
			if (HPP)
			{
				hpp1_fired->Fill(k+1);
				trig++;
			}

			HPP = (Bool_t)(Tltw[12-1] & (1 << k) );
			if (HPP)
			{
				hpp2_fired->Fill(k+1+16);
				trig++;
			}
			//if (trig>1) cout<<trig<<endl;
		}
		for (int k=16;k<32;k++)
		{
			HPP = (Bool_t)(Tltw[5-1] & (1 << k));
			if (HPP) hpp1_taken->Fill(k+1-16);

			HPP = (Bool_t)(Tltw[12-1] & (1 << k));
			if (HPP) hpp2_taken->Fill(k+1);
		}
	}

	TFile f1("/data/zenith226a/libov/results/K0sK0s_hist/trigger/1.root","recreate");

	hpp1_fired->Write();
	hpp1_taken->Write();


	hpp2_fired->Write();
	hpp2_taken->Write();

	f1.Close();
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif
