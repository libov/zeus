//////////////////////////////////////////////////
//////////////                   /////////////////
//////////////   K0s   analysis  /////////////////
//////////////    with V0lite    /////////////////
//////////////                   /////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                August 2008                   //
//                                              //
//                                              //
//////////////////////////////////////////////////
//////////                             ///////////
//////////  Combining into double K0s  ///////////
//////////                             ///////////
//////////////////////////////////////////////////
//                                              //
//   1. Reading data from small trees           //
//   2. Event & K0s selection                   //
//   3. Combining into K0s and writing          //
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
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/test/07p_PHP_DIS.root");

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
	TH1F *h1=new TH1F("h1","K0sK0s in DIS",200,0.8,5);
	TH1F *h2=new TH1F("h2","K0sK0s in DIS",280,0.8,5);
	TH1F *h3=new TH1F("h3","K0sK0s in DIS",150,0.8,5);
	TH1F *hK0_mass=new TH1F("hK0_mass","Invariant mass, N (K^{0}_{S})>=2",60,450,552);
	TH1F *hK0_n1=new TH1F("hK0_n1","Number of K^{0}_{S} before selection (V0lite)",70,0,70);
	TH1F *hK0_n2=new TH1F("hK0_n2","Number of K^{0}_{S} after selection",70,0,70);
	TH1F *hd1=new TH1F("hd1","debug1 (K^{0}_{S} selection)",20,0,20);




	Double_t convert=180/TMath::Pi();
	Double_t phi=0;
	Int_t 	goa=0,year=0,err=0;
	Float_t reso_mass=0;

	for (Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		Int_t	cand_k0=0,
			list_k0[30];
		/*hd1->Fill(1);
		if (sincand<1) continue;
		hd1->Fill(2);
		if (siprob<0.9) continue;
		hd1->Fill(3);
		if (q2el<1.0) continue;
		hd1->Fill(4);
		if (yjb<0.01) continue;
		hd1->Fill(5);
		if (yel>0.95) continue;
		hd1->Fill(6);
		if ((box_x<12)&&(box_y<6)) continue;
		hd1->Fill(7);
		*/
	/*
		// ----- momenta scaling ------ //
		year=0;
		if  ((Runnr>=low_2004)&&(Runnr<=up_2004)) year=2004;
		if  ((Runnr>=low_2005)&&(Runnr<=up_2005)) year=2005;
		if  ((Runnr>=low_2006)&&(Runnr<=up_2006)) year=2006;
		if  ((Runnr>=low_2006p)&&(Runnr<=up_2006p)) year=2010;
		if  ((Runnr>=low_2007)&&(Runnr<=up_2007)) year=2007;

		switch (year)
		{
			case 2004: corr=corr_2004; break;
			case 2005: corr=corr_2005; break;
			case 2006: corr=corr_2006e; break;
			case 2007: corr=corr_2007; break;
			case 2010: corr=corr_2006p; break;
			case 0: {corr=1.00000; err++;} break;
		}
	*/
		corr=1.000000;
		//------ K0s cand selection -------//
		hK0_n1->Fill(nv0);
		for(Int_t k=0;k<nv0;k++)
		{

			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
			hd1->Fill(1);
			if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
			hd1->Fill(2);
			if ((layout1[k]<3)||(layout2[k]<3)) continue;
			hd1->Fill(3);

			Mother K0s_cand(t1,t2);

			//if ((is1_sec[k]!=1)||(is2_sec[k]!=1)) continue;
			if ((is1_prim[k]==1)||(is2_prim[k]==1)) continue;
			hd1->Fill(4);

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
			}				//my    Sergei    Barbi
			if(mass_pi_p<1.121) continue; //1.125        1.121
			hd1->Fill(5);

			if (coll2[k]>0.12) continue;  //.1              .12
			hd1->Fill(6);

		/*
			if( K0s_cand.GetPx_m()>=0) phi=convert*acos((K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if( K0s_cand.GetPx_m()<0) phi=180-convert*acos(((-1)*K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if (K0s_cand.GetPy_m()<=0)
			{
				phi=360-phi;
			}
		*/
			if(K0s_cand.GetPt_m()<0.3) continue;  //.3        .25     .2
			hd1->Fill(7);
			if (TMath::Abs(K0s_cand.GetEta_m())>1.75) continue;// 1.75    1.6
			hd1->Fill(8);
			if (coll3[k]>0.24) continue; // comment                .24
			hd1->Fill(9);
			//if ((K0s_cand.GetMass_m(4,4)<0.4777)||(K0s_cand.GetMass_m(4,4)>0.5177)) continue;
			if ((K0s_cand.GetMass_m(4,4)<0.481)||(K0s_cand.GetMass_m(4,4)>0.515)) continue;
			hd1->Fill(10);
			list_k0[cand_k0]=k;
			cand_k0++;
		}

		//K0s combining
		hK0_n2->Fill(cand_k0);
		if (cand_k0<2) continue;
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t id=list_k0[k];
			Daughter t1temp(corr*p1[id][0],corr*p1[id][1],corr*p1[id][2]);
			Daughter t2temp(corr*p2[id][0],corr*p2[id][1],corr*p2[id][2]);
			Mother K0s_candtemp(t1temp,t2temp);
			hK0_mass->Fill(1000*K0s_candtemp.GetMass_m(4,4));
		}

		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{

				Int_t 		k01=list_k0[k],
						k02=list_k0[l];
				Int_t 		id1k=id1[k01],
						id2k=id2[k01],
						id1l=id1[k02],
						id2l=id2[k02];

				if ((id1k==id1l)||(id1k==id2l)||(id2k==id1l)||(id2k==id2l)) continue;

				Float_t		px1=corr*(p1[k01][0]+p2[k01][0]),
						py1=corr*(p1[k01][1]+p2[k01][1]),
						pz1=corr*(p1[k01][2]+p2[k01][2]),

						px2=corr*(p1[k02][0]+p2[k02][0]),
						py2=corr*(p1[k02][1]+p2[k02][1]),
						pz2=corr*(p1[k02][2]+p2[k02][2]);
				Daughter K0s_cand1(px1,py1,pz1);
				Daughter K0s_cand2(px2,py2,pz2);
				Mother K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);

				h1->Fill(reso_mass);
				h2->Fill(reso_mass);
				h3->Fill(reso_mass);
			}
		}
	}

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/heraII.root","recreate");

	h1->Write();
	h2->Write();
	h3->Write();
	hK0_n1->Write();
	hK0_n2->Write();
	hK0_mass->Write();
	hd1->Write();

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

