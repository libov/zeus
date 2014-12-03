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

void q2()
{
	Int_t		goa=0,
			nevents=0,
			Nv0lite=0,
			Sincand=0,
			Tt1_id[50],
			Tt2_id[50],
			Tq1[50],
			Tq2[50],
			Trk_ntracks=0,
			Trk_id[300];
	Float_t		Tinvmass_k0[50],
			Tinvmass_lambda[50],
			Tinvmass_alambda[50],
			Tinvmass_ee[50],
			Tsecvtx_collin3[50],
			Tsecvtx_collin2[50],
			Tsecvtx[50][3],
			reso_mass=0,
			Tp1[50][3],
			Tp2[50][3],
			Tpk[50][3],
			corr=0,
			Siq2el[10],
			Sixel[10],
			Siyel[10],
			Siq2jb[10],
			Sixjb[10],
			Siyjb[10],
			Siq2da[10],
			Sixda[10],
			Siyda[10],
			Sizuhmom[4][10],
			Sicalpos[3][10],
			Sisrtpos[2][10],
			Sisrtene[10],
			Siecorr[3][10],
			Sith[10],
			Zvtx;
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300],
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


	TChain *myChain=new TChain("resonance");
	// PATH to NTUPLES
	myChain->Add("/data/zenith226a/libov/to_test/v0lite_testsample/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2007pRP/*.root");
	//myChain->Add("/data/zenith226a/libov/to_test/control/*.root");
	//myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_test.root");


	// V0lite
	myChain->SetBranchAddress("Nv0lite",&Nv0lite);
	myChain->SetBranchAddress("Tinvmass_k0",Tinvmass_k0);
	myChain->SetBranchAddress("Tinvmass_lambda",Tinvmass_lambda);
	myChain->SetBranchAddress("Tinvmass_alambda",Tinvmass_alambda);
	myChain->SetBranchAddress("Tinvmass_ee",Tinvmass_ee);
	myChain->SetBranchAddress("Tsecvtx_collin3",Tsecvtx_collin3);
	myChain->SetBranchAddress("Tsecvtx_collin2",Tsecvtx_collin2);
	myChain->SetBranchAddress("Tpk",Tpk);
	myChain->SetBranchAddress("Tp1",Tp1);
	myChain->SetBranchAddress("Tp2",Tp2);
	myChain->SetBranchAddress("Tq1",Tq1);
	myChain->SetBranchAddress("Tq2",Tq2);
	myChain->SetBranchAddress("Tt1_id",Tt1_id);
	myChain->SetBranchAddress("Tt2_id",Tt2_id);
	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	myChain->SetBranchAddress("Zvtx",&Zvtx);
	//Sira, Si_kin
	myChain->SetBranchAddress("Sincand",&Sincand);
	myChain->SetBranchAddress("Siq2el",Siq2el);
	myChain->SetBranchAddress("Siyel",Siyel);
	myChain->SetBranchAddress("Sixel",Sixel);
	myChain->SetBranchAddress("Siq2jb",Siq2jb);
	myChain->SetBranchAddress("Sixjb",Sixjb);
	myChain->SetBranchAddress("Siyjb",Siyjb);
	myChain->SetBranchAddress("Siq2da",Siq2da);
	myChain->SetBranchAddress("Sixda",Sixda);
	myChain->SetBranchAddress("Siyda",Siyda);
	myChain->SetBranchAddress("Sizuhmom",Sizuhmom);
	myChain->SetBranchAddress("Siecorr",Siecorr);
	myChain->SetBranchAddress("Sith",Sith);
	myChain->SetBranchAddress("Sicalpos",Sicalpos);
	myChain->SetBranchAddress("Sisrtpos",Sisrtpos);
	myChain->SetBranchAddress("Sisrtene",Sisrtene);
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	TH1F *q2el=new TH1F("q2el","",20,1,20);
	//TH1F *q2el=new TH1F("q2el","",20,20,300);
	TH1F *xel=new TH1F("xel","", 20,0,1);
	TH1F *yel=new TH1F("yel","", 20,0,1);

	TH1F *q2jb=new TH1F("q2jb","", 35,0,120);
	TH1F *xjb=new TH1F("xjb","", 20,0,1);
	TH1F *yjb=new TH1F("yjb","", 20,0,1);

	TH1F *q2da=new TH1F("q2da","", 35,0,120);
	TH1F *xda=new TH1F("xda","", 20,0,1);
	TH1F *yda=new TH1F("yda","", 20,0,1);

	TH1F *z=new TH1F("z","", 20,-50,50);

	TH1F *hdebug=new TH1F("hdebug","Debug: DIS selection",20,0,20);
	if (nevents>100000) nevents=300000;
	for(int i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		if (Nv0lite<1) continue;
		hdebug->Fill(1);
		if (Sincand<=0) continue;
		hdebug->Fill(2);
		if (Siq2el[0]<1.0) continue;
		hdebug->Fill(3);
		if ((TMath::Abs(Zvtx))>52.0) continue;
		hdebug->Fill(4);
		if (Siecorr[0][2]<8.5) continue;
		hdebug->Fill(5);

		if (Siq2el[0]>20) continue;
		hdebug->Fill(6);
		//if (Siq2el[0]>300) continue;
		//hdebug->Fill(7);




  		//hdebug->Fill(1);
		//if (Siq2el[0]<1) continue;						// Q^2>1 GeV^2
		//hdebug->Fill(2);
		// E-pz calculation
		float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   		float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   		float EminPz_Evt  = Empz_e + Empz_had;
		if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;				// 38 < E-pz < 60 GeV
		//hdebug->Fill(3);
		// electron position calculation (box cut)
		float x_srtd=Sicalpos[0][0];						// position of electron in calorimeter
   		float y_srtd=Sicalpos[0][1];
   		if (Sisrtene[0]>0)
		{
      			x_srtd=Sisrtpos[0][0];						// position of electron in SRDT
      			y_srtd=Sisrtpos[0][1];
    		}
		if (TMath::Abs(x_srtd)<12)						// box cut: electron required to be outside 12x6 cm^2 box
		{
			if (TMath::Abs(y_srtd)<6) continue;
		}
		//hdebug->Fill(4);
		if (Siyel[0]>0.95) continue;						// y from electron method < 0.95
		//hdebug->Fill(5);
		if (Siyjb[0]<0.01) continue;						// y from Jacquet-Blondel method > 0.01
		//hdebug->Fill(6);

		z->Fill(Zvtx);
		q2el->Fill(Siq2el[0]);
		xel->Fill(Sixel[0]);
		yel->Fill(Siyel[0]);

		q2jb->Fill(Siq2jb[0]);
		xjb->Fill(Sixjb[0]);
		yjb->Fill(Siyjb[0]);

		q2da->Fill(Siq2da[0]);
		xda->Fill(Sixda[0]);
		yda->Fill(Siyda[0]);

	}

	// histograms normalising
	Double_t norm=1.0;
	Double_t scale=0;
	//electron method
	//scale = norm/(q2el->Integral());
	//q2el->Sumw2();
	//q2el->Scale(scale);

	/*scale = norm/(xel->Integral());
	xel->Sumw2();
	xel->Scale(scale);

	scale = norm/(yel->Integral());
	yel->Sumw2();
	yel->Scale(scale);

	//jacquet-blondel method
	scale = norm/(q2jb->Integral());
	q2jb->Sumw2();
	q2jb->Scale(scale);

	scale = norm/(xjb->Integral());
	xjb->Sumw2();
	xjb->Scale(scale);

	scale = norm/(yjb->Integral());
	yjb->Sumw2();
	yjb->Scale(scale);

	//double-angle method
	scale = norm/(q2da->Integral());
	q2da->Sumw2();
	q2da->Scale(scale);

	scale = norm/(xda->Integral());
	xda->Sumw2();
	xda->Scale(scale);

	scale = norm/(yda->Integral());
	yda->Sumw2();
	yda->Scale(scale);

	scale=norm/(z->Integral());
	z->Sumw2();
	z->Scale(scale);*/


	//TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/event_var_MC.root","recreate");
	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/event_var_07pRP_K0s_not_req.root","recreate");
	q2el->Write();
	xel->Write();
	yel->Write();
	q2jb->Write();
	xjb->Write();
	yjb->Write();
	z->Write();
	hdebug->Write();

	f2->Close();
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	q2();
	return 0;
}
#endif
