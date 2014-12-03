//////////////////////////////////////////////////
//////////////  K0s    analysis  /////////////////
//////////////    with short     /////////////////
//////////////      trees        /////////////////
//////////////     (part2)       /////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////
//////////                             ///////////
////////// Part2: analysis using trees ///////////
//////////                             ///////////
//////////////////////////////////////////////////
//                                              //
//   1. Reading data from small trees           //
//   2. Selection                               //
//   3. Further Analysis and plotting           //
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
	//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/04/test_0.root");
	//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/MC_HERAI_DJ_ARI/1.root");
	//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/heraI/00p_new/*.root");
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/MEPS/*.root");

	Int_t		nv0=0,		// number K0s candidates that passed soft selection
				id1[80],	// id of the first track
				id2[80],	// id of the second track
				runnr=0,	// number of run
				is1_sec[80],	// =1 if 1st track flagged as secondary
				is2_sec[80],	// =1 if 2nd track flagged as secondary
				is1_prim[80],	// =1 if 1st track flagged as primary
				is2_prim[80],	// =1 if 2nd track flagged as primary
				sincand,	// Number of Sinistra electron candidates
				layout1[80],	//outer superlayer of 1st pion
				layout2[80];	//outer superlayer of 2nd pion;
	Float_t		p1[80][3],	// momenta of 1st track
				p2[80][3],	// momenta of 2bd track
				coll2[80],	// collinearity angle 2D
				coll3[80],	// collinearity angle 3D
					q2el,		// Q^2 from electron method (1st Sinistra candidate)
				yel,		// y from electron method (1st Sinistra candidate)
			yjb,		// y from Jaquet-Blondel method (1st Sinistra candidate)
			box_x,		// x position of scattered electron
			box_y,		// y position of electron
			e_pz,		// E-pz calculated both from hadronic system and electron
			siprob,		// probability of 1st Sinistra candidate
			mass_lambda[80],// invariant mass assuming proton(larger momenuma) and pion
			mass_ee[80];	// invariant mass assuming electron and positron


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

	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<" events here"<<endl;

	Float_t		//corr=1.005;
			corr=1.00000;
	//K0s analysis histograms
	TH2F *hAP_before=new TH2F("hAP_before","Armenteros-Podolanski",100,-1,1,100,0,0.3);
	TH2F *hAP_after=new TH2F("hAP_after","Armenteros-Podolanski",100,-1,1,100,0,0.3);
	TH1F *hinv_K0s=new TH1F("hinv_K0s","orange cuts+pt",60,450,552);
	TH1F *hinv_lambda=new TH1F("hinv_lambda","Lambda inv mass",200,1000,1400);
	TH1F *hq2el=new TH1F("hq2el","K0s Q^{2}_{el} distribution",50,0,100);
	TH1F *hsincand=new TH1F("hsincand","Number of Sinistra candidates",5,0,5);
	TH2F *hdalitz=new TH2F("hdalitz","Dalitz plot",400,200,800,400,1050,1400);


	TH1F *hdebug_k0=new TH1F("hdebug_k0","",10,0,10);
	TH1F *h_nv0_before=new TH1F("h_nv0_before","",30,0,30);
	TH1F *h_nv0_after=new TH1F("h_nv0_after","",30,0,30);

	Double_t convert=180/TMath::Pi();
	Double_t phi=0;
	Int_t 	goa=0,year=0,err=0;
	Float_t reso_mass=0;
	for (Int_t i=0;i<nevents;i++)
	{

		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		hsincand->Fill(sincand);
		hq2el->Fill(q2el);

		//if (q2el<2.0) continue;
		//if (yjb<0.04) continue;
		//////////////////////////////////////////////////

		// momenta scaling

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
		//if (corr!=corr_2005) cout<<"ERROR!!!"<<endl;

		corr=1.000000;

		h_nv0_before->Fill(nv0);
		//K0s cand selection
		//if (nv0<2) continue;
		Int_t	nv0_pass=0;
		for(Int_t k=0;k<nv0;k++)
		{
			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);

			//cout<<corr<<endl;
			Mother K0s_cand(t1,t2);
			hAP_before->Fill(K0s_cand.Get_AP_alpha_m(),K0s_cand.Get_AP_pt_m());

			//if ((is1_sec[k]!=1)||(is2_sec[k]!=1)) continue;
			hdebug_k0->Fill(0);
			//if ((is1_prim[k]==1)||(is2_prim[k]==1)) continue;

			hdebug_k0->Fill(1);
			if ((layout1[k]<3)||(layout2[k]<3)) continue;
			hdebug_k0->Fill(2);
			//if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
			hdebug_k0->Fill(3);

			//cout<<is1_prim[k]<<" "<<is2_prim[k]<<" "<<is1_sec[k]<<" "<<is2_sec[k]<<endl;

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

			hdalitz->Fill(1000*K0s_cand.GetMass_m(4,4),1000*mass_pi_p);
			//if (coll2[k]>0.12) continue;
			hdebug_k0->Fill(4);
			//if (coll3[k]>0.24) continue;
			hdebug_k0->Fill(5);
			//if(K0s_cand.GetMass_m(4,4)>0.475) continue;
			//cout<<mass_pi_p<<" "<<mass_lambda[k]<<endl;
			//if(mass_pi_p<1.121) continue;
			hdebug_k0->Fill(6);

			/*
			//K0s phi calculating
			if( K0s_cand.GetPx_m()>=0) phi=convert*acos((K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if( K0s_cand.GetPx_m()<0) phi=180-convert*acos(((-1)*K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if (K0s_cand.GetPy_m()<=0)
			{
				phi=360-phi;
			}
			*/

			//if(K0s_cand.GetPt_m()<0.3) continue;  //.3        .25     .2
			//if (TMath::Abs(K0s_cand.GetEta_m())>1.75) continue;// 1.75    1.6
			//if (coll3[k]>0.24) continue; // comment                .24

			//if ((K0s_cand.GetMass_m(4,4)<0.47)||(K0s_cand.GetMass_m(4,4)>0.526)) continue;
			//if ((K0s_cand.GetMass_m(4,4)<0.481)||(K0s_cand.GetMass_m(4,4)>0.515)) continue;

			//if (mass_ee[k]<0.05) continue;
			hdebug_k0->Fill(7);

			hinv_lambda->Fill(1000*mass_pi_p);
			hinv_K0s->Fill(1000*K0s_cand.GetMass_m(4,4));

			hAP_after->Fill(K0s_cand.Get_AP_alpha_m(),K0s_cand.Get_AP_pt_m());
			//if ((K0s_cand.GetMass_m(4,4)<0.4777)||(K0s_cand.GetMass_m(4,4)>0.5177)) continue;
			nv0_pass++;
		}
		h_nv0_after->Fill(nv0_pass);
	}


//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/temporary/K0s_anal_V0lite.root","recreate");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/temporary/00p_new.root","recreate");
TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MEPS.root","recreate");


	hAP_before->Write();
	hAP_after->SetMarkerColor(4);
	hAP_after->Write();
	hinv_K0s->Write();
	hinv_lambda->Write();
	hdalitz->Write();
	hdebug_k0->Write();
	h_nv0_before->Write();
	h_nv0_after->Write();
	//hq2el->Write();
	//hsincand->Write();

	f1->Close();
	cout<<err<<" errors"<<endl;
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

