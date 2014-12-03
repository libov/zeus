// Building K0s mass spectra from MyMiniNtuples
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//            National University of Kiev       //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////

#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TSystem.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif

void analysis()
{
	Int_t		goa=0,
			nevents=0;

	Int_t		nv0=0,		// number K0s candidates that passed soft selection
			id1[80],	// id of the first track
			id2[80],	// id of the second track
			runnr=0,	// number of run
			is1_sec[80],	// =1 if 1st track flagged as secondary
			is2_sec[80],	// =1 if 2nd track flagged as secondary
			is1_prim[80],	// =1 if 1st track flagged as primary
			is2_prim[80],	// =1 if 2nd track flagged as primary
			layout1[80],	//outer superlayer of 1st pion
			layout2[80],	//outer superlayer of 2nd pion;
			layinn1[80],	//inner superlayer of 1st pion
			layinn2[80];	//inner superlayer of 2nd pion

	Float_t		p1[80][3],	// momenta of 1st track
			p2[80][3],	// momenta of 2nd track
			coll2[80],	// collinearity angle 2D
			coll3[80],	// collinearity angle 3D
			mass_ee[80];	// e+e- inv mass
	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/05e_newVAR/*.root");

	myChain->SetBranchAddress("nv0",&nv0);
	myChain->SetBranchAddress("p1",p1);
	myChain->SetBranchAddress("p2",p2);
	myChain->SetBranchAddress("coll2",coll2);
	myChain->SetBranchAddress("coll3",coll3);
	myChain->SetBranchAddress("id1",id1);
	myChain->SetBranchAddress("id2",id2);
	myChain->SetBranchAddress("is1_sec",is1_sec);
	myChain->SetBranchAddress("is2_sec",is2_sec);
	myChain->SetBranchAddress("is1_prim",is1_prim);
	myChain->SetBranchAddress("is2_prim",is2_prim);
	myChain->SetBranchAddress("runnr",&runnr);
	myChain->SetBranchAddress("layout1",layout1);
	myChain->SetBranchAddress("layout2",layout2);
	myChain->SetBranchAddress("layinn1",layinn1);
	myChain->SetBranchAddress("layinn2",layinn2);
	myChain->SetBranchAddress("mass_ee",mass_ee);


//------------------------------------------------------------------------------------------//
	cout<<"here"<<endl;
	nevents=1000000;
	//nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	Int_t 		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);
	TH1F *h_V0lite=new TH1F("h_V0lite","K^{0}_{S} Invariant mass, V0lite",500,250,750);
	TH1F *h_V0liteNOREJ=new TH1F("h_V0liteNOREJ","K^{0}_{S} Invariant mass, V0lite (photon conersion rejection)",500,250,750);
	TH1F *h_V0lite_SL3=new TH1F("h_V0lite_SL3","K^{0}_{S} Invariant mass, V0lite +SL3",500,250,750);
	TH1F *h_V0lite_SL5=new TH1F("h_V0lite_SL5","K^{0}_{S} Invariant mass, V0lite +SL5",500,250,750);
	TH1F *h_V0lite_SL7=new TH1F("h_V0lite_SL7","K^{0}_{S} Invariant mass, V0lite +SL7",500,250,750);
	TH1F *hd_V0lite=new TH1F("hd_V0lite","",10,0,10);

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);


		Int_t		Nr_of_slayers1=0,
				Nr_of_slayers2=0;
		//cout<<nv0<<endl;
		for (int k=0;k<nv0;k++)
		{
  			hd_V0lite->Fill(1);
			if ((layinn1[k]>1)||(layinn2[k]>1)) continue;
			hd_V0lite->Fill(2);
			if ((layout1[k]<3)||(layout1[k]<3)) continue;
			hd_V0lite->Fill(3);

			Daughter t1(p1[k][0],p1[k][1],p1[k][2]);
			Daughter t2(p2[k][0],p2[k][1],p2[k][2]);
			Mother	K0(t1,t2);
			Float_t		mass=1000*K0.GetMass_m(4,4);
			//cout<<mass<<endl;
			h_V0liteNOREJ->Fill(mass);
			if (mass_ee[k]<0.05) continue;
			hd_V0lite->Fill(4);
			h_V0lite->Fill(mass);

			Nr_of_slayers1=layout1[k]-layinn1[k]+1;
			Nr_of_slayers2=layout2[k]-layinn2[k]+1;
			if ((Nr_of_slayers1<3)||(Nr_of_slayers2<3)) continue;
			hd_V0lite->Fill(5);
			h_V0lite_SL3->Fill(mass);
			if ((Nr_of_slayers1<5)||(Nr_of_slayers2<5)) continue;
			hd_V0lite->Fill(6);
			h_V0lite_SL5->Fill(mass);
			if ((Nr_of_slayers1<7)||(Nr_of_slayers2<7)) continue;
			hd_V0lite->Fill(7);
			h_V0lite_SL7->Fill(mass);
		}

	}

TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_SLcut_05COMNTUP_conver_rej.root","recreate");

	h_V0lite->Write();
	h_V0lite_SL3->Write();
	h_V0lite_SL5->Write();
	h_V0lite_SL7->Write();
	hd_V0lite->Write();

	f1->Close();

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

