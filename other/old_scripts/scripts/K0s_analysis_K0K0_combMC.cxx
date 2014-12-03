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
	myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root");

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
			layout2[80],	//outer superlayer of 2nd pion;
			layinn1[80],	//inner superlayer of 1st pion
			layinn2[80];	//inner superlayer of 2nd pion

	Float_t		p1[80][3],	// momenta of 1st track
			p2[80][3],	// momenta of 2nd track
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
	Int_t		tlt[6][16];	// 3rd-level trigger: tlt[m][k]
					// m=3 SPP, m=4 DIS ...   k=1 bit 1 (e.g. HPP01) k=2 bit 2

	Float_t		cal_et;		// Transverse energy of the event

	Int_t		njet=0;		// Number of jets (kT jet finder A)
	Float_t		etjet[20],	// Transverse energy of jets
			etajet[20],	// eta of jets
			phijet[20];	// phi of jets
	Int_t		ntrue=0,	//  Number of stored (e.g. those survived pT cut)
					//  FMCKIN particles
			fmcprt[50];	//  FMCPRT
	Float_t		mass[50];	//  mass
	Int_t		daug_of[50];	//  Daughter f
	Int_t		fmckin_id[50];	//  Daughter f
	Float_t		px[50],	//  Px of particle
			py[50],	//  Py
			pz[50];	//  Pz

	Float_t		secvtx[20][3];	// position of secondary vertex from V0lite
					// (given by Vxlite function there)
	Float_t		dlen2[20],	// decay length (2D) given by V0lite
			dlen3[20];	// decay length (3D) given by V0lite


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
	myChain->SetBranchAddress("layinn1",layinn1);
	myChain->SetBranchAddress("layinn2",layinn2);
	//myChain->SetBranchAddress("tlt",tlt);
	myChain->SetBranchAddress("cal_et",&cal_et);
	myChain->SetBranchAddress("njet",&njet);
	myChain->SetBranchAddress("etjet",etjet);
	myChain->SetBranchAddress("etajet",etajet);
	myChain->SetBranchAddress("phijet",phijet);

	myChain->SetBranchAddress("ntrue",&ntrue);
	myChain->SetBranchAddress("fmcprt",fmcprt);
	myChain->SetBranchAddress("mass",mass);
	myChain->SetBranchAddress("daug_of",daug_of);
	myChain->SetBranchAddress("fmckin_id",fmckin_id);
	myChain->SetBranchAddress("px",px);
	myChain->SetBranchAddress("py",py);
	myChain->SetBranchAddress("pz",pz);


	myChain->SetBranchAddress("secvtx",secvtx);

	myChain->SetBranchAddress("dlen2",dlen2);
	myChain->SetBranchAddress("dlen3",dlen3);



	Float_t		//corr=1.005;
			corr=1.00000;
	TH1F *h1=new TH1F("h1","K0sK0s in DIS",200,0.8,5);
	TH1F *h2=new TH1F("h2","K0sK0s in DIS",280,0.8,5);
	TH1F *h3=new TH1F("h3","K0sK0s in DIS",150,0.8,5);
	TH1F *hK0_mass=new TH1F("hK0_mass","Invariant mass, N (K^{0}_{S})>=2",60,450,552);
	TH1F *hK0_n1=new TH1F("hK0_n1","Number of K^{0}_{S} before selection (V0lite)",70,0,70);
	TH1F *hK0_n2=new TH1F("hK0_n2","Number of K^{0}_{S} after selection",70,0,70);
	TH1F *hd1=new TH1F("hd1","debug1: K^{0}_{S} selection",20,0,20);
	TH1F *hd2=new TH1F("hd2","debug2: K^{0}_{S}K^{0}_{S} combining",20,0,20);

	TH1F *h_njet=new TH1F("h_njet","Number of jets (kT A)",20,0,20);

	TH1F *h_deltajet=new TH1F("h_deltajet","delta K0sK0s<->jet",100,0,10);

	TH1F *hdelta1=new TH1F("hdelta1","Min Delta for ",100,0,1);
	TH1F *hdelta2=new TH1F("hdelta2","delta",100,0,1);
	TH1F *hdelta=new TH1F("hdelta","delta",100,0,1);

	TH1F *h_jetAS=new TH1F("h_jetAS","K0sK0s associated with jets",150,0.8,5);

	TH1F *h_k0k0_numb=new TH1F("h_k0k0_numb","Number of K0K0 pairs",6,0,6);
	TH1F *h_candk0=new TH1F("h_candk0","Number of K0 passed through cuts",6,0,6);

	TH1F *h_delta_dlen2=new TH1F("h_delta_dlen2","Difference ",150,0,50);
	TH1F *h_delta_dlen3=new TH1F("h_delta_dlen3","Difference ",150,0,50);

	//triggers

	TH1F *exo=new TH1F("exo","EXO TLT fired ",16,1,17);
	TH1F *muo=new TH1F("muo","MUO TLT fired ",16,1,17);
	TH1F *vtx=new TH1F("vtx","vtx TLT fired ",16,1,17);
	TH1F *hfm=new TH1F("hfm","hfm TLT fired ",16,1,17);
	TH1F *hfl=new TH1F("hfl","hfl TLT fired ",16,1,17);
	TH1F *dis=new TH1F("dis","DIS TLT fired ",16,1,17);

	//calorimeter
TH1F *hcal_et=new TH1F("hcal_et","Total transverse energy in calorimeter, E_{T}^{event}  for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<1",100,0,100);
TH1F *hk0k0_et=new TH1F("hk0k0_et","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<1",100,0,20);
	TH1F *hratio_et=new TH1F("hratio_et","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}",100,0,1);
// 28 MeV/bin
	TH1F *hk0k0_1=new TH1F("hk0k0_1","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",150,0.8,5);
	TH1F *hk0k0_2=new TH1F("hk0k0_2","0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",150,0.8,5);
	TH1F *hk0k0_3=new TH1F("hk0k0_3","0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",150,0.8,5);
	TH1F *hk0k0_4=new TH1F("hk0k0_4","0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",150,0.8,5);
	TH1F *hk0k0_5=new TH1F("hk0k0_5","0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",150,0.8,5);
// 15 MeV/bin   (280 bins)
TH1F *hk0k0_1_280=new TH1F("hk0k0_1_280","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",280,0.8,5);
	TH1F *hk0k0_2_280=new TH1F("hk0k0_2_280","0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",280,0.8,5);
	TH1F *hk0k0_3_280=new TH1F("hk0k0_3_280","0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",280,0.8,5);
	TH1F *hk0k0_4_280=new TH1F("hk0k0_4_280","0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",280,0.8,5);
	TH1F *hk0k0_5_280=new TH1F("hk0k0_5_280","0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",280,0.8,5);



	TH1F *hcal_et_1=new TH1F("hcal_et_1","Total transverse energy in calorimeter, E_{T}^{event} for E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",100,0,100);
	TH1F *hcal_et_2=new TH1F("hcal_et_2","Total transverse energy in calorimeter, E_{T}^{event} for 0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",100,0,100);
	TH1F *hcal_et_3=new TH1F("hcal_et_3","Total transverse energy in calorimeter, E_{T}^{event} for 0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",100,0,100);
	TH1F *hcal_et_4=new TH1F("hcal_et_4","Total transverse energy in calorimeter, E_{T}^{event} for 0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",100,0,100);
	TH1F *hcal_et_5=new TH1F("hcal_et_5","Total transverse energy in calorimeter, E_{T}^{event} for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",100,0,100);

	TH1F *hk0k0_et_1=new TH1F("hk0k0_et_1","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",100,0,20);
	TH1F *hk0k0_et_2=new TH1F("hk0k0_et_2","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",100,0,20);
	TH1F *hk0k0_et_3=new TH1F("hk0k0_et_3","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",100,0,20);
	TH1F *hk0k0_et_4=new TH1F("hk0k0_et_4","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",100,0,20);
	TH1F *hk0k0_et_5=new TH1F("hk0k0_et_5","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",100,0,20);

	//true
	TH1F *h_f0mass=new TH1F("h_f0mass","",300,990,1010);
	TH1F *h_fmcprt=new TH1F("h_fmcprt","",2500,0,2500);
	TH1F *h_delta_eta=new TH1F("h_delta_eta","",100,-2,2);
	TH1F *h_delta_phi=new TH1F("h_delta_phi","",100,-2,2);

	Double_t convert=180/TMath::Pi();
	Double_t phi=0;
	Int_t 	goa=0,year=0,err=0;
	Float_t reso_mass=0;
	Double_t	a1=0,
			a2=0,
			a3=0,
			a6=0;
	//Int_t 	nevents=myChain->GetEntries();
	//Int_t		nevents=26078430;
	Int_t		nevents=10000000;
	cout<<nevents<<" events here"<<endl;
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
			a1++;
			if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
			hd1->Fill(2);
			a2++;
			if ((layout1[k]<3)||(layout2[k]<3)) continue;
			hd1->Fill(3);
			a3++;

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
			a6++;

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
			if ((K0s_cand.GetMass_m(4,4)<0.4777)||(K0s_cand.GetMass_m(4,4)>0.5177)) continue;
			//if ((K0s_cand.GetMass_m(4,4)<0.481)||(K0s_cand.GetMass_m(4,4)>0.515)) continue;
			hd1->Fill(10);
			if ((layinn1[k]>1)||(layinn2[k]>1)) continue;
			hd1->Fill(11);
			list_k0[cand_k0]=k;
			cand_k0++;
		}

		//K0s combining
		hK0_n2->Fill(cand_k0);
		if (cand_k0<2) continue;
		h_candk0->Fill(cand_k0);
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t id=list_k0[k];
			Daughter t1temp(corr*p1[id][0],corr*p1[id][1],corr*p1[id][2]);
			Daughter t2temp(corr*p2[id][0],corr*p2[id][1],corr*p2[id][2]);
			Mother K0s_candtemp(t1temp,t2temp);
			hK0_mass->Fill(1000*K0s_candtemp.GetMass_m(4,4));
		}
		Int_t	k0k0_numb=0;
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
				hd2->Fill(1);
				if ((id1k==id1l)||(id1k==id2l)||(id2k==id1l)||(id2k==id2l)) continue;
				hd2->Fill(2);
				if ((id1k==id2k)||(id1l==id2l)) continue;
				hd2->Fill(3);
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

				k0k0_numb++;

				Float_t		K0sK0s_et=0;

				K0sK0s_et=K0sK0s.GetEt_m();
				hcal_et->Fill(cal_et);
				Float_t		ratio=K0sK0s_et/cal_et;
				hratio_et->Fill(ratio);

				Double_t	eta_K0s_cand1=K0s_cand1.GetEta(),
						eta_K0s_cand2=K0s_cand2.GetEta();
				Double_t	phi_K0s_cand1=K0s_cand1.GetPhi(),
						phi_K0s_cand2=K0s_cand2.GetPhi();

				h_delta_eta->Fill(eta_K0s_cand1-eta_K0s_cand2);
				h_delta_phi->Fill(phi_K0s_cand1-phi_K0s_cand2);

				if (ratio>0.5)
				{
					hk0k0_1->Fill(reso_mass);
					hk0k0_1_280->Fill(reso_mass);
					hcal_et_1->Fill(cal_et);
					hk0k0_et_1->Fill(K0sK0s_et);

				}
				if ((ratio>0.25)&&(ratio<0.5))
				{
					hk0k0_2->Fill(reso_mass);
					hk0k0_2_280->Fill(reso_mass);
					hcal_et_2->Fill(cal_et);
					hk0k0_et_2->Fill(K0sK0s_et);
				}
				if ((ratio>0.125)&&(ratio<0.25))
				{
					hk0k0_3->Fill(reso_mass);
					hk0k0_3_280->Fill(reso_mass);
					hcal_et_3->Fill(cal_et);
					hk0k0_et_3->Fill(K0sK0s_et);
				}
				if ((ratio>0.05)&&(ratio<0.125))
				{
					hk0k0_4->Fill(reso_mass);
					hk0k0_4_280->Fill(reso_mass);
					hcal_et_4->Fill(cal_et);
					hk0k0_et_4->Fill(K0sK0s_et);
				}
				if ((ratio>0)&&(ratio<0.05))
				{


					hk0k0_5->Fill(reso_mass);
					hk0k0_5_280->Fill(reso_mass);
					hcal_et_5->Fill(cal_et);
				h_delta_dlen3->Fill(TMath::Abs(dlen3[k01]-dlen3[k02]));
					hk0k0_et_5->Fill(K0sK0s_et);
				}
				h_njet->Fill(njet);


				/*for (int z=0;z<ntrue;z++)
				{

				}*/


				// attempt to match true f0->K0sK0s to reconstructed K0s

			/*
				for (int z=0;z<ntrue;z++ )
				{
					h_fmcprt->Fill(fmcprt[z]);
					if (fmcprt[z]!=81) continue;
					cout<<mass[z]<<" "<<daug_of[z]<<" "<<fmckin_id[z]<<endl;
					Int_t	dghtr1=0,
						dghtr2=0,
						temp[2],
						ll=0;

					for (int j=0;j<ntrue;j++)
					{
						if (daug_of[j]==fmckin_id[z])
						{
							temp[ll]=j;
							ll++;
						}
					}
					cout<<ll<<endl;
					dghtr1=temp[0];
					dghtr2=temp[1];

					if ((fmcprt[dghtr1]!=62)||(fmcprt[dghtr2]!=62)||(ll!=2)) continue;

					Daughter K1(px[dghtr1],py[dghtr1],pz[dghtr1]);
					Daughter K2(px[dghtr2],py[dghtr2],pz[dghtr2]);

					//cout<<dghtr1<<" "<<dghtr2<<endl;
					//cout<<px[dghtr1]<<" "<<py[dghtr1]<<" "<<pz[dghtr1]<<endl;

					Mother f0(K1,K2);
					Float_t f0mass=f0.GetMass_m(5,5);
					cout<<"Found f0->K0sK0s, f0 mass "<<f0mass<<endl;
					h_f0mass->Fill(1000*f0mass);
					//matched=false;
					Double_t	etaK1=K1.GetEta(),
							etaK2=K2.GetEta();
					Double_t	phiK1=K1.GetPhi(),
							phiK2=K2.GetPhi();
					Int_t		mat1=-1,
							mat2=-1;
					Double_t	delta1min=9999,
							delta2min=9999;
					Double_t	delta_eta11=etaK1-etaK0cand1;
					Double_t	delta_phi11=phiK1-phiK0cand1;
					Double_t	delta_eta22=etaK2-etaK0cand2;
					Double_t	delta_phi22=phiK2-phiK0cand2;

					Double_t	delta_eta12=etaK1-etaK0cand2;
					Double_t	delta_phi12=phiK1-phiK0cand2;
					Double_t	delta_eta21=etaK2-etaK0cand1;
					Double_t	delta_phi21=phiK2-phiK0cand1;


					Double_t	delta11=0,
							delta22=0,
							delta12=0,
							delta21=0;
					delta11=sqrt(delta_eta11*delta_eta11+delta_phi11*delta_phi11);
					delta22=sqrt(delta_eta22*delta_eta22+delta_phi22*delta_phi22);

					delta12=sqrt(delta_eta12*delta_eta12+delta_phi12*delta_phi12);
					delta21=sqrt(delta_eta21*delta_eta21+delta_phi21*delta_phi21);

					Double_t	delta1=0,
							delta2=0;

					delta1=sqrt(delta11*delta11+delta22*delta22);
					delta2=sqrt(delta12*delta12+delta21*delta21);

					Double_t	delta=0;

					if (delta1<delta2) delta=delta1;
					if (delta1>delta2) delta=delta2;

					hdelta1->Fill(delta1);
					hdelta2->Fill(delta2);
					hdelta->Fill(delta);
				}

			*/

			}


		}
		h_k0k0_numb->Fill(k0k0_numb);

	}


		TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_MC_v2.2.root","recreate");


	h1->Write();
	h2->Write();
	h3->Write();
	hK0_n1->Write();
	hK0_n2->Write();
	hK0_mass->Write();
	hd1->Write();
	hd2->Write();


	for (int k=0;k<12;k++)
	{
		cout<<"Bin "<<k<<" : "<<hd1->GetBinContent(k)<<endl;
	}
	cout<<a1<<" "<<a2<<" "<<a3<<" "<<a6<<endl;

	exo->Write();
	muo->Write();
	vtx->Write();
	hfm->Write();
	hfl->Write();
	dis->Write();

	hcal_et->Write();
	hratio_et->Write();

	hk0k0_1->Write();
	hk0k0_2->Write();
	hk0k0_3->Write();
	hk0k0_4->Write();
	hk0k0_5->Write();

	hk0k0_1_280->Write();
	hk0k0_2_280->Write();
	hk0k0_3_280->Write();
	hk0k0_4_280->Write();
	hk0k0_5_280->Write();

	hk0k0_et_1->Write();
	hk0k0_et_2->Write();
	hk0k0_et_3->Write();
	hk0k0_et_4->Write();
	hk0k0_et_5->Write();


	hcal_et_1->Write();
	hcal_et_2->Write();
	hcal_et_3->Write();
	hcal_et_4->Write();
	hcal_et_5->Write();

	h_njet->Write();

	h_deltajet->Write();

	h_jetAS->Write();

	h_fmcprt->Write();
	h_f0mass->Write();

	hdelta1->Write();
	hdelta2->Write();
	hdelta->Write();

	h_k0k0_numb->Write();
	h_candk0->Write();

	h_delta_eta->Write();
	h_delta_phi->Write();

	h_delta_dlen3->Write();

	cout<<err<<" errors"<<endl;
	cout<<f1->GetName()<<" created"<<endl;
	f1->Close();
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

