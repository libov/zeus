// Building K0s mass spectra from orange blocks
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
			nevents=0,
			Nv0lite=0,
			Nv0=0,
			Tt1_id[80],
			Tt2_id[80],
			Tq1[80],
			Tq2[80],
			Trk_ntracks=0,
			Trk_id[300],
			Tt1_layout[80],
			Tt2_layout[80],
			Tt1_layinn[80],
			Tt2_layinn[80];
	Float_t		Tinvmass_k0[80],
			Invmass_k0[80],
			Tinvmass_lambda[80],
			Tinvmass_alambda[80],
			Tinvmass_ee[80],
			Tsecvtx_collin3[80],
			Tsecvtx_collin2[80],
			Tsecvtx[80][3],
			reso_mass=0,
			Tp1[80][3],
			Tp2[80][3],
			Tpk[80][3],
			corr=0,
			Siq2el[10],
			Siyel[10],
			Siyjb[10],
			Sizuhmom[4][10],
			Sicalpos[3][10],
			Sisrtpos[2][10],
			Sisrtene[10],
			Siecorr[3][10],
			Sith[10],
			Siprob[10];
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300],
			Trk_vtx[300],
			Runnr=0,
			year=0,
			k0_cand=0;
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


	Float_t		Xvtx=0,
			Yvtx=0,
			Zvtx=0;

	Int_t		Tltw[14];
	Float_t		Cal_et=0;

	Int_t		Kt_njet_a=0;
	Float_t		Kt_etjet_a[20],
			Kt_etajet_a[20],
			Kt_phijet_a[20];

	Float_t		P1[40][3],
			P2[40][3];
	Int_t		Nv0psy=0;
	Int_t		T1_layinn[50],
			T2_layinn[50],
			T1_layout[50],
			T2_layout[50];


	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/data/00ptest/*.root");
//------------------------------------------------------------------------------------------//

	// V0lite
	myChain->SetBranchAddress("Nv0lite",&Nv0lite);
	myChain->SetBranchAddress("Tinvmass_k0",Tinvmass_k0);
	myChain->SetBranchAddress("Tt1_layinn",Tt1_layinn);
	myChain->SetBranchAddress("Tt2_layinn",Tt2_layinn);
	myChain->SetBranchAddress("Tt1_layout",Tt1_layout);
	myChain->SetBranchAddress("Tt2_layout",Tt2_layout);



	myChain->SetBranchAddress("Nv0",&Nv0);
	myChain->SetBranchAddress("Invmass_k0",Invmass_k0);
	myChain->SetBranchAddress("T1_layinn",T1_layinn);
	myChain->SetBranchAddress("T2_layinn",T2_layinn);
	myChain->SetBranchAddress("T1_layout",T1_layout);
	myChain->SetBranchAddress("T2_layout",T2_layout);


	myChain->SetBranchAddress("Nv0psy",&Nv0psy);
	myChain->SetBranchAddress("P1",P1);
	myChain->SetBranchAddress("P2",P2);
	//

	// Trigger stuff
	//myChain->SetBranchAddress("Tltw", Tltw);
	cout<<"here"<<endl;
	//nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	Int_t 		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);

	TH1F *h_V0lite=new TH1F("h_V0lite","K^{0}_{S} Invariant mass, V0lite",500,250,750);
	TH1F *h_V0=new TH1F("h_V0","K^{0}_{S} Invariant mass, V0",500,250,750);
	TH1F *h_V0psy=new TH1F("h_V0psy","K^{0}_{S} Invariant mass, V0psy",500,250,750);

	TH1F *h_V0lite_SL=new TH1F("h_V0lite_SL","K^{0}_{S} Invariant mass, V0lite +SL",500,250,750);
	TH1F *h_V0_SL=new TH1F("h_V0_SL","K^{0}_{S} Invariant mass, V0 +SL",500,250,750);

	char	name[256];

	TH1F *hd_V0lite=new TH1F("hd_V0lite","",10,0,10);
	TH1F *hd_V0=new TH1F("hd_V0","",10,0,10);

	nevents=1000000;
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);


		Int_t		Nr_of_slayers1=0,
				Nr_of_slayers2=0;
		for (int k=0;k<Nv0lite;k++)
		{
  			hd_V0lite->Fill(1);

			if ((Tt1_layinn[k]>1)||(Tt2_layinn[k]>1)) continue;
			hd_V0lite->Fill(2);
			if ((Tt1_layout[k]<3)||(Tt2_layout[k]<3)) continue;
			hd_V0lite->Fill(3);
			h_V0lite->Fill(1000*Tinvmass_k0[k]);

			Nr_of_slayers1=Tt1_layout[k]-Tt1_layinn[k]+1;
			Nr_of_slayers2=Tt2_layout[k]-Tt2_layinn[k]+1;
			if ((Nr_of_slayers1<7)||(Nr_of_slayers2<7)) continue;
			hd_V0lite->Fill(4);
			h_V0lite_SL->Fill(1000*Tinvmass_k0[k]);
		}

		for (int k=0;k<Nv0;k++)
		{
			hd_V0->Fill(1);
			h_V0->Fill(1000*Invmass_k0[k]);
			if ((T1_layinn[k]>1)||(T2_layinn[k]>1)) continue;
			hd_V0->Fill(2);
			if ((T1_layout[k]<3)||(T2_layout[k]<3)) continue;
			hd_V0->Fill(3);
			h_V0_SL->Fill(1000*Invmass_k0[k]);
		}

		/*for (int k=0;k<Nv0psy;k++)
		{
			Daughter	t1(P1[k][0],P1[k][1],P1[k][2]);
			Daughter	t2(P2[k][0],P2[k][1],P2[k][2]);
			Mother		K0(t1,t2);

			h_V0psy->Fill(1000*K0.GetMass_m(4,4));
		}*/




	}

TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_find_comp_00p.root","recreate");

	h_V0lite->Write();
	h_V0->Write();
	//h_V0psy->Write();

	h_V0lite_SL->Write();
	h_V0_SL->Write();

	hd_V0->Write();
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

