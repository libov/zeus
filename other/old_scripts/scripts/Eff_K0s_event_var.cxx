//////////////////////////////////////////////////
//////////////   K0s   analysis  /////////////////
//////////////    with V0lite    /////////////////
//////////////      (part2)      /////////////////
//////////////    theta -- pT    /////////////////
//////////////    double distr   /////////////////
//						//
//	    Last Modify: 22.07.2008		//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////
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
	// -------------------  I N P U T  -------------------------//
	Float_t		low_theta_cut=40.0,
			up_theta_cut=140.0;
	bool		MC=false;
	bool		DATA=false;

	//MC=true;
	DATA=true;

	if (DATA)
	{
		//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/00p_new/*.root");
		myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/05e_newVAR/*.root");

	}
	if (MC)
	{
		//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/DJAN9900p/*.root");
		myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root");
	}
	// ---------------------------------------------------------//


	Int_t		nv0=0,		// number K0s candidates that passed soft selection
			id1[80],	// id of the first track
			id2[80],	// id of the second track
			runnr=0,	// number of run
			is1_sec[80],	// =1 if 1st track flagged as secondary
			is2_sec[80],	// =1 if 2nd track flagged as secondary
			is1_prim[80],	// =1 if 1st track flagged as primary
			is2_prim[80],	// =1 if 2nd track flagged as primary
			sincand,	// Number of Sinistra electron candidates
			layout1[80],	// outer superlayer of the 1st track
			layout2[80];	// outer superlayer of the 2nd track
	Float_t		p1[80][3],	// momenta of the 1st track
			p2[80][3],	// momenta of the 2nd track
			coll2[80],	// collinearity angle 2D
			coll3[80],	// collinearity angle 3D
			q2el,		// Q^2 from electron method (1st Sinistra candidate)
			yel,		// y from electron method (1st Sinistra candidate)
			yjb,		// y from Jaquet-Blondel method (1st Sinistra candidate)
			box_x,		// x position of scattered electron
			box_y,		// y position of electron
			e_pz,		// E-pz calculated both from hadronic system and electron
			siprob,		// probability of 1st Sinistra candidate
			mass_lambda[80],// invariant mass assuming pion and
					//proton (for track with larger momentum)
			mass_ee[80];	// invariant mass assuming electron and positron
	Float_t		xvtx=0,		// coordinates of primary vertex; 0 if none
			yvtx=0,		//
			zvtx=0;		//

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
	const Float_t	corr_2004=1.0055,
			corr_2005=1.008,
			corr_2006e=1.008,
			corr_2006p=1.006,
			corr_2007=1.0055;
	Int_t		Is_used[300];

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
	myChain->SetBranchAddress("q2el",&q2el);
	myChain->SetBranchAddress("yel",&yel);
	myChain->SetBranchAddress("yjb",&yjb);
	myChain->SetBranchAddress("box_x",&box_x);
	myChain->SetBranchAddress("box_y",&box_y);
	myChain->SetBranchAddress("e_pz",&e_pz);
	myChain->SetBranchAddress("siprob",&siprob);
	myChain->SetBranchAddress("sincand",&sincand);
	myChain->SetBranchAddress("mass_lambda",mass_lambda);
	myChain->SetBranchAddress("mass_ee",mass_ee);
	myChain->SetBranchAddress("runnr",&runnr);
	myChain->SetBranchAddress("layout1",layout1);
	myChain->SetBranchAddress("layout2",layout2);
	myChain->SetBranchAddress("xvtx",&xvtx);
	myChain->SetBranchAddress("yvtx",&yvtx);
	myChain->SetBranchAddress("zvtx",&zvtx);

	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<" events here"<<endl;

	TH1F *hdebug_k0=new TH1F("hdebug_k0","",10,0,10);
	TH1F *hdebug_ev=new TH1F("hdebug_ev","",10,0,10);
	TH1F *ht=new TH1F("ht","",100,0,0.5);
	TH1F *hq=new TH1F("hq","",100,0,25);
	TH1F *hq1=new TH1F("hq1","",100,0,25);
	// event variables
	TH1F *h_e_pz=new TH1F("h_e_pz","",100,0,100);
	TH1F *h_zvtx=new TH1F("h_zvtx","",100,-35,35);
	TH1F *h_yjb=new TH1F("h_yjb","",100,0,1);

	Float_t		//corr=1.005;
			corr=1.00000;
	Double_t 	convert=180/TMath::Pi();
	Double_t	phi=0;
	Int_t		goa=0,
			year=0,
			err=0;
	Float_t 	reso_mass=0;
	Float_t		step_th=(up_theta_cut-low_theta_cut)/48,
			step_pt=(2.0-0.4)/64,
			step_pt_slow=(0.4-0.06)/68;
	Float_t		theta_low,
			theta_up,
			pt_low,
			pt_up,
			pt_slow_low,
			pt_slow_up;



	for (Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);

		hdebug_ev->Fill(0);
		hq1->Fill(q2el);
		if (sincand==0) q2el=0;
		hq->Fill(q2el);
		//if (q2el<5.0) continue;
		hdebug_ev->Fill(1);
		//if (yel<0.02) continue;
		hdebug_ev->Fill(2);
		//if (yel>0.9) continue;
		hdebug_ev->Fill(3);

		if (TMath::Abs(zvtx)>30) continue;
		hdebug_ev->Fill(4);
		Float_t	xy=0;
		//xy=sqrt((xvtx-1.9)*(xvtx-1.9)+(yvtx-0.2)*(yvtx-0.2));
		//if (xy>1.2) continue;

		hdebug_ev->Fill(5);


		//// momenta scaling /////////////////////////////
		year=0;
		if  ((runnr>=low_2004)&&(runnr<=up_2004)) year=2004;
		if  ((runnr>=low_2005)&&(runnr<=up_2005)) year=2005;
		if  ((runnr>=low_2006)&&(runnr<=up_2006)) year=2006;
		if  ((runnr>=low_2006p)&&(runnr<=up_2006p)) year=2010;
		if  ((runnr>=low_2007)&&(runnr<=up_2007)) year=2007;
		switch (year)
		{
			case 2004: corr=corr_2004; break;
			case 2005: corr=corr_2005; break;
			case 2006: corr=corr_2006e; break;
			case 2007: corr=corr_2007; break;
			case 2010: corr=corr_2006p; break;
			case 0: {corr=1.00000; err++;} break;
		}
		////////////////////////////////////////////////////
		//cout<<xvtx<<" "<<yvtx<<" "<<zvtx<<endl;
		corr=1.000000;
		//K0s cand selection
		//if (nv0<2) continue;
		for(Int_t k=0;k<nv0;k++)
		{
			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
			Mother K0s_cand(t1,t2);


			//if ((is1_sec[k]!=1)||(is2_sec[k]!=1)) continue;
			//if ((is1_prim[k]==1)||(is2_prim[k]==1)) continue;

			hdebug_k0->Fill(1);
			if ((layout1[k]<3)||(layout2[k]<3)) continue;
			hdebug_k0->Fill(2);
			Double_t	pt1=t1.GetPt(),
					pt2=t2.GetPt();

			ht->Fill(pt2);

			//if (pt1<0.1) cout<<"pt1="<<pt1<<endl;
			//if (pt2<0.1) cout<<"pt2="<<pt2<<endl;

			//if ((pt1<0.06)||(pt2<0.06)) continue;
			if ((pt1<0.1)||(pt2<0.1)) continue;
			hdebug_k0->Fill(3);

		/*
			//lambda/alambda mass calculating
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
		*/
			//if (coll2[k]>0.12) continue;
			//if (coll3[k]>0.24) continue;
			//if(mass_pi_p<1.121) continue;
			//if (mass_ee[k]<0.05) continue;

			Float_t		pt=K0s_cand.GetPt_m();
			Float_t		theta=K0s_cand.GetTheta_m();
			Float_t		mk0=K0s_cand.GetMass_m(4,4);

			Double_t	pt_slow=0;
			Double_t	pt_fast=0;

			if ((pt1>0.4)&&(pt2<0.4))
			{
				pt_slow=pt2;
				pt_fast=pt1;
			}
			else if ((pt1<0.4)&&(pt2>0.4))
			{
				pt_slow=pt1;
				pt_fast=pt2;
			}
			else
				continue;

			hdebug_k0->Fill(4);
			if ((pt<0.4)||(pt>2)) continue;
			hdebug_k0->Fill(5);
			if ((theta<low_theta_cut)||(theta>up_theta_cut)) continue;
			hdebug_k0->Fill(6);

			// filing histograms with event variables
			h_e_pz->Fill(e_pz);
			h_zvtx->Fill(zvtx);
			h_yjb->Fill(yjb);
		}
	}


//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/theta_dependence/MC_ARI_MEPS/60_120.root","recreate");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/heraI/00p_new/40_140.root","recreate");
char	name[256];
Int_t	temp=sprintf(name,"ev_var_%d_%d.root",(Int_t)low_theta_cut,(Int_t)up_theta_cut);
TFile *f1 =new TFile(name,"recreate");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/heraI/DJAN9900p/30_150.root","recreate");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/CommNtup/Data05e/40_140.root","recreate");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_efficiency/CommNtup/MCdijetPHPv2/120_150.root","recreate");



	h_e_pz->Write();
	h_zvtx->Write();
	h_yjb->Write();
	hdebug_k0->Write();
	hdebug_ev->Write();
	hq1->Write();
	hq->Write();
	ht->Write();
	f1->Close();
	cout<<err<<" errors"<<endl;
	cout<<f1->GetName()<<" created"<<endl;
	if (MC) cout<<"this is MC"<<endl;
	if (DATA) cout<<"this is Data"<<endl;
	cout<<"low_theta_cut: "<<low_theta_cut<<endl;
	cout<<"up_theta_cut: "<<up_theta_cut<<endl;
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

