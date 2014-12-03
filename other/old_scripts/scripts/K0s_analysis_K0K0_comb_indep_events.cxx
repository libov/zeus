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
//////////    Combining      K0sK0s    ///////////
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
#include <TVector3.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif
void analysis()
{
	cout<<"Hi gangsta"<<endl;
	TChain *myChain=new TChain("resonance");

//-------------------  I N P U T -------------------//

//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/MEPS/*.root");

myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/05ev3/*.root");
myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/06pv1/*.root");
myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/07pv1/*.root");
//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/04/*.root");



//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root");

//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/MC_ARI_NCDIS_MARCELLO/*.root");
//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCbeautyPHP05v1/*.root");
//--------------------------------------------------//


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
	Int_t		event;		// event number
	Int_t		ntracks;	// number of tracks quoted in Tracking block

	Float_t		bspt_x,		// beam spot X
			bspt_y,		// beam spot y
			bspt_z;		// beam spot z  ??
	Float_t		secvtx[20][3];	// position of secondary vertex from V0lite
					// (given by Vxlite function there)
	Float_t		dlen2[20],	// decay length (2D) given by V0lite
			dlen3[20];	// decay length (3D) given by V0lite

	Float_t		zvtx;		// Z-coordinate of primary vertex

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
/*	myChain->SetBranchAddress("njet",&njet);
	myChain->SetBranchAddress("etjet",etjet);
	myChain->SetBranchAddress("etajet",etajet);
	myChain->SetBranchAddress("phijet",phijet);
*/
	myChain->SetBranchAddress("event",&event);
	myChain->SetBranchAddress("ntracks",&ntracks);

	/*myChain->SetBranchAddress("bspt_x",&bspt_x);
	myChain->SetBranchAddress("bspt_y",&bspt_y);
	myChain->SetBranchAddress("bspt_z",&bspt_z);

	myChain->SetBranchAddress("secvtx",secvtx);*/

	myChain->SetBranchAddress("dlen2",dlen2);
	myChain->SetBranchAddress("dlen3",dlen3);
	myChain->SetBranchAddress("zvtx",&zvtx);


	//Int_t nevents=myChain->GetEntries();
	Int_t	nevents=20000;
	//cout<<nevents<<" events here"<<endl;

	Float_t		//corr=1.005;
			corr=1.00000;
	TH1F *h1=new TH1F("h1","ZEUS",200,0.8,5);
	TH1F *h2=new TH1F("h2","ZEUS",280,0.8,5);
	TH1F *h3=new TH1F("h3","ZEUS",150,0.8,5);
	TH1F *hK0_mass=new TH1F("hK0_mass","Invariant mass, N (K^{0}_{S})>=2",60,450,552);
	TH1F *hK0_mass1=new TH1F("hK0_mass1","Invariant mass, N (K^{0}_{S})>=2",200,250,1000);
	TH1F *hK0_massK1=new TH1F("hK0_massK1","Invariant mass, N (K^{0}_{S})>=2",200,250,1000);
	TH1F *hK0_massK2=new TH1F("hK0_massK2","Invariant mass, N (K^{0}_{S})>=2",200,250,1000);
	TH1F *hK0_n1=new TH1F("hK0_n1","Number of K^{0}_{S} before selection (V0lite)",70,0,70);
	TH1F *hK0_n2=new TH1F("hK0_n2","Number of K^{0}_{S} after selection",70,0,70);
	TH1F *hd1=new TH1F("hd1","debug1: K^{0}_{S} selection",20,0,20);
	TH1F *hd2=new TH1F("hd2","debug2: K^{0}_{S}K^{0}_{S} combining",20,0,20);

	TH1F *h_njet=new TH1F("h_njet","Number of jets (kT A)",20,0,20);

	TH1F *h_delta=new TH1F("h_delta","delta",100,0,10);
	TH1F *h_d_ab=new TH1F("h_d_ab","",100,0,10);

	TH1F *h_jetAS=new TH1F("h_jetAS","K0sK0s associated with jets",150,0.8,5);

	TH1F *h_delta_dlen2=new TH1F("h_delta_dlen2","Difference ",150,0,50);
	TH1F *h_delta_dlen3=new TH1F("h_delta_dlen3","Difference ",150,0,50);
	TH1F *h_delta_dlen3_raw=new TH1F("h_delta_dlen3_raw","Difference ",150,0,50);

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
	TH1F *hk0k0_12=new TH1F("hk0k0_12","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",150,0.8,5);
	TH1F *hk0k0_2=new TH1F("hk0k0_2","0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",150,0.8,5);
	TH1F *hk0k0_3=new TH1F("hk0k0_3","0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",150,0.8,5);
	TH1F *hk0k0_4=new TH1F("hk0k0_4","0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",150,0.8,5);
	TH1F *hk0k0_5=new TH1F("hk0k0_5","0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",150,0.8,5);
// 15 MeV/bin   (280 bins)
TH1F *hk0k0_1_280=new TH1F("hk0k0_1_280","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",280,0.8,5);

TH1F *hk0k0_2_280=new TH1F("hk0k0_2_280","0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",280,0.8,5);

	TH1F *hk0k0_12_280=new TH1F("hk0k0_12_280","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.25",280,0.8,5);

	TH1F *hk0k0_3_280=new TH1F("hk0k0_3_280","0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",280,0.8,5);
	TH1F *hk0k0_4_280=new TH1F("hk0k0_4_280","0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",280,0.8,5);
	TH1F *hk0k0_5_280=new TH1F("hk0k0_5_280","0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",280,0.8,5);

	TH1F *hk0k0_45_280=new TH1F("hk0k0_45_280","0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",280,0.8,5);

	TH1F *hk0k0_45=new TH1F("hk0k0_45","0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",150,0.8,5);

//////////////////
TH1F *hk0k0_d_ab1=new TH1F("hk0k0_d_ab1","delta>0",150,0.8,5);
TH1F *hk0k0_d_ab2=new TH1F("hk0k0_d_ab2","delta>0.1",150,0.8,5);
TH1F *hk0k0_d_ab3=new TH1F("hk0k0_d_ab3","delta>0.3",150,0.8,5);
TH1F *hk0k0_d_ab4=new TH1F("hk0k0_d_ab4","delta>0.5",150,0.8,5);
TH1F *hk0k0_d_ab5=new TH1F("hk0k0_d_ab5","delta>0",150,0.8,5);
/////////////

TH1F *hddlen3_1=new TH1F("hddlen3_1","delta dlen3 >0",150,0.8,5);
TH1F *hddlen3_2=new TH1F("hddlen3_2","delta dlen3 >0.5",150,0.8,5);
TH1F *hddlen3_3=new TH1F("hddlen3_3","delta dlen3 >1",150,0.8,5);
TH1F *hddlen3_4=new TH1F("hddlen3_4","delta dlen3 >2",150,0.8,5);

TH1F *hzvtx=new TH1F("hzvtx","Z_{vtx}",150,-100,100);



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

	TH1F *h_dlen3 =new TH1F("h_dlen3","",300,0,50);
	TH1F *h_dlen2 =new TH1F("h_dlen2","",300,0,50);
	TH1F *h_dlen3_raw =new TH1F("h_dlen3_raw","",300,0,50);

	TH1F *h_f0_pt =new TH1F("h_f0_pt","",300,0,7);
	TH1F *h_angle =new TH1F("h_angle","angle between two K0s",300,0,6);



	Double_t convert=180/TMath::Pi();
	Double_t phi=0;
	Int_t 	goa=0,year=0,err=0;
	Float_t reso_mass=0;
	Double_t	a1=0,
			a2=0,
			a3=0,
			a6=0;
	//nevents=2000;
	cout<<"looping..."<<endl;
	for (Int_t i=0;i<nevents-1;i++)
	{
  		if (goa==100)
        	{
        		cout<<"i= "<<i<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		//if ((zvtx>30)||(zvtx<(-30))) continue;
		hzvtx->Fill(zvtx);
		Int_t	cand_k0_i=0,
			list_k0_i[30];


		for(Int_t k=0;k<nv0;k++)
		{

			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
			hd1->Fill(1);
			a1++;
			if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
			//if ((t1.GetPt()<0.14)||(t2.GetPt()<0.14)) continue;
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
			//if (((layout1[k]-layinn1[k])<7)||((layout2[k]-layinn2[k])<7)) continue;
			//if ((is1_sec[k]!=1)||(is2_sec[k]!=1)) continue;
			hd1->Fill(12);
			if (mass_ee[k]<0.05) continue;
			hd1->Fill(13);

			Float_t		gamma=0;

			gamma=sqrt(1+TMath::Power((K0s_cand.GetP_m()/0.49762),2));
			h_dlen3->Fill(dlen3[k]/gamma);
			h_dlen2->Fill(dlen2[k]);
			h_dlen3_raw->Fill(dlen3[k]);
			//cout<<"--- "<<dlen3[k]<<endl;
			//if (dlen2[k]<3) continue;
			list_k0_i[cand_k0_i]=k;
			hd1->Fill(14);
			cand_k0_i++;
		}

		if (cand_k0_i<1) continue;
		for (Int_t j=i;j<nevents;j++)
		{
			Int_t	cand_k0_j=0,
				list_k0_j[30];

			corr=1.000000;

			myChain->GetEntry(j);
			//------ K0s cand selection -------//

			for(Int_t k=0;k<nv0;k++)
			{

				Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
				Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
				hd1->Fill(1);
				a1++;
				if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
				//if ((t1.GetPt()<0.14)||(t2.GetPt()<0.14)) continue;
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
				Float_t 	mass_pi_p=0;
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
				//if (((layout1[k]-layinn1[k])<7)||((layout2[k]-layinn2[k])<7)) continue;
				//if ((is1_sec[k]!=1)||(is2_sec[k]!=1)) continue;
				hd1->Fill(12);
				if (mass_ee[k]<0.05) continue;
				hd1->Fill(13);

				Float_t		gamma=0;

				gamma=sqrt(1+TMath::Power((K0s_cand.GetP_m()/0.49762),2));
				h_dlen3->Fill(dlen3[k]/gamma);
				h_dlen2->Fill(dlen2[k]);
				h_dlen3_raw->Fill(dlen3[k]);
				//cout<<"--- "<<dlen3[k]<<endl;
				//if (dlen2[k]<3) continue;
				list_k0_j[cand_k0_j]=k;
				hd1->Fill(14);
				cand_k0_j++;
			}

			//K0s combining
			if (cand_k0_j<1) continue;
			//cout<<"i= "<<i<<";  j= "<<j<<endl;
			for(Int_t k=0;k<cand_k0_i;k++)
			{
				for(Int_t l=0;l<cand_k0_j;l++)
				{
					Int_t 		k01=list_k0_i[k],
							k02=list_k0_j[l];
					myChain->GetEntry(i);
					Int_t 		id1k=id1[k01],
							id2k=id2[k01];

					Float_t		px1=corr*(p1[k01][0]+p2[k01][0]),
							py1=corr*(p1[k01][1]+p2[k01][1]),
							pz1=corr*(p1[k01][2]+p2[k01][2]);

					myChain->GetEntry(j);
					Int_t		id1l=id1[k02],
							id2l=id2[k02];

					Float_t		px2=corr*(p1[k02][0]+p2[k02][0]),
							py2=corr*(p1[k02][1]+p2[k02][1]),
							pz2=corr*(p1[k02][2]+p2[k02][2]);
					hd2->Fill(1);
					hd2->Fill(2);
					if ((id1k==id2k)||(id1l==id2l)) continue;

					hd2->Fill(3);
					//cout<<runnr<<endl;



					Daughter K0s_cand1(px1,py1,pz1);
					Daughter K0s_cand2(px2,py2,pz2);

					Mother K0sK0s(K0s_cand1,K0s_cand2);
					reso_mass=K0sK0s.GetMass_m(5,5);

					h1->Fill(reso_mass);
					h2->Fill(reso_mass);
					h3->Fill(reso_mass);
					/*
					Float_t		K0sK0s_et=0;

					K0sK0s_et=K0sK0s.GetEt_m();
					hcal_et->Fill(cal_et);
					Float_t		ratio=K0sK0s_et/cal_et;
					hratio_et->Fill(ratio);

					Float_t	f0pt=K0sK0s.GetPt_m();
					//h_f0_pt->Fill(f0pt);

					//angle between two K0s
					TVector3 k1(px1,py1,pz1);
					TVector3 k2(px2,py2,pz2);
					Double_t angle=k1.Angle(k2);
					h_angle->Fill(angle);

					Float_t		delta_dlen2=dlen2[k01]-dlen2[k02];
					h_delta_dlen2->Fill(delta_dlen2);

					if ((ratio>0)&&(ratio<0.125))
					{
						hk0k0_45->Fill(reso_mass);
						hk0k0_45_280->Fill(reso_mass);
					}

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
					if (ratio>0.25)
					{
						hk0k0_12->Fill(reso_mass);
						hk0k0_12_280->Fill(reso_mass);

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
					}*/
				}
			}
		}
	}

	TFile *f1 =new TFile("05e06p07p_COMMNTUP_indep.root","recreate");

	h1->Write();
	h2->Write();
	h3->Write();
	/*hK0_n1->Write();
	hK0_n2->Write();
	hK0_mass->Write();
	hK0_mass1->Write();
	hK0_massK1->Write();
	hK0_massK2->Write();
	hd1->Write();
	hd2->Write();*/
/*	for (int k=0;k<12;k++)
	{
		cout<<"Bin "<<k<<" : "<<hd1->GetBinContent(k)<<endl;
	}
	cout<<a1<<" "<<a2<<" "<<a3<<" "<<a6<<endl;
*/
/*
	hcal_et->Write();
	hratio_et->Write();

	hk0k0_1->Write();
	hk0k0_2->Write();
	hk0k0_3->Write();
	hk0k0_4->Write();
	hk0k0_5->Write();
	hk0k0_45->Write();

	hk0k0_1_280->Write();
	hk0k0_2_280->Write();
	hk0k0_3_280->Write();
	hk0k0_4_280->Write();
	hk0k0_5_280->Write();
	hk0k0_45_280->Write();

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

	h_delta->Write();

	h_jetAS->Write();
	h_d_ab->Write();

	hk0k0_d_ab1->Write();
	hk0k0_d_ab2->Write();
	hk0k0_d_ab3->Write();
	hk0k0_d_ab4->Write();

	h_delta_dlen3->Write();
	h_delta_dlen3_raw->Write();

	h_delta_dlen2->Write();

	h_dlen2->Write();
	h_dlen3->Write();
	h_dlen3_raw->Write();

	hddlen3_1->Write();
	hddlen3_2->Write();
	hddlen3_3->Write();
	hddlen3_4->Write();

	h_f0_pt->Write();
	h_angle->Write();

	hzvtx->Write();

	hk0k0_12->Write();
*/
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

