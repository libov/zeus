#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <TROOT.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif

void test1()
{
	Int_t		nv0=0,		// number K0s candidates that passed soft selection
			id1[10],	// id of the first track
			id2[10];	// id of the second track
	Float_t		p1[10][3],	// momenta of 1st track
			p2[10][3],	// momenta of 2bd track
			coll2[10],	// collinearity angle 2D
			coll3[10];	// collinearity angle 3D

	TChain *myChain=new TChain("resonance");
	//myChain->Add("/data/zenith226a/libov/results/mostrecent/HERAII_2005RTfit.root");
	myChain->Add("/data/zenith226a/libov/results/mostrecent/HERAII_2005noRTfit.root");
	myChain->SetBranchAddress("nv0",&nv0);
	myChain->SetBranchAddress("id1",id1);
	myChain->SetBranchAddress("id2",id2);
	myChain->SetBranchAddress("p1",p1);
	myChain->SetBranchAddress("p2",p2);
	myChain->SetBranchAddress("coll2",coll2);
	myChain->SetBranchAddress("coll3",coll3);
	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<" events here"<<endl;
	TH1F *h=new TH1F("h","K0s",100,440,550);
	TH1F *hdebug1=new TH1F("hdebug1","",20,0,20);
	TH1F *hdebug2=new TH1F("hdebug2","",20,0,20);
	Int_t goa=0;
	for (int i=0;i<nevents;i++)
	{
		myChain->GetEntry(i);

		if (goa==1000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		for(int j=0;j<nv0;j++)
		{
			Daughter t1(p1[j][0],p1[j][1],p1[j][2]);
			Daughter t2(p2[j][0],p2[j][1],p2[j][2]);
			Mother K0s_cand(t1,t2);
			hdebug1->Fill(1);
			Float_t 	p1=t1.GetP();
			Float_t 	p2=t2.GetP();
			Float_t 	mass_pi_p=0;

			if (p1>p2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (p1<p2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}
			hdebug1->Fill(2);
			if (coll2[j]>0.1) continue;
			hdebug1->Fill(3);
			if (mass_pi_p<1.125) continue;
			hdebug1->Fill(4);
			//if (Tinvmass_ee[j]<0.05) continue;
			hdebug1->Fill(5);
			if ((K0s_cand.GetPt_m())<0.3) continue;
			hdebug1->Fill(6);
			if (coll3[j]>0.2) continue;
			hdebug1->Fill(7);
			if (TMath::Abs(K0s_cand.GetEta_m())>1.5) continue;
			hdebug1->Fill(8);
			h->Fill(1000*K0s_cand.GetMass_m(4,4));
		}

	}
	h->Draw();
	TFile *f =new TFile("/data/zenith226a/libov/results/mostrecent/HERAII_2005noRTfit_hist.root","recreate");
	h->Write();
	hdebug1->Write();
	f->Close();

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	test1();
	return 0;
}
#endif
