//////////////////////////////////////////////////
//////////////   K0s   analysis  /////////////////
//////////////    with V0lite    /////////////////
//////////////      (part1)      /////////////////
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
////////// Part1: peparing small trees ///////////
//////////                             ///////////
//////////////////////////////////////////////////
//                                              //
//   1. Event selection                         //
//   2. K0s selection (loose)                   //
//   3. Writing data to small tree              //
//      easy to analyze                         //
//                                              //
//////////////////////////////////////////////////

#ifndef __CINT__
#include <TChain.h>
#include <TMath.h>
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
			Sincand=0,
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
			Tinvmass_lambda[80],
			Tinvmass_alambda[80],
			Tinvmass_ee[80],
			Tsecvtx_collin3[80],
			Tsecvtx_collin2[80],
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
	Int_t 		Trk_prim_vtx[1200],
			Trk_sec_vtx[1200],
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
	Int_t		Eventnr=0;
	Int_t		ntracks;

	Int_t		Bspt_prog;	// 0 if no bspt info; 1 - b.spot (GAF);
					// 2 - b.spot (BSGAFLD)
	Float_t		Bspt_x,		// beam spot X
			Bspt_y,		// beam spot Y
			Bspt_z;		// beam spot Z  ??
	Float_t		Tsecvtx[80][3];	// position of secondary vertex from V0lite
					// (given by Vxlite function there)
	Float_t		Tsecvtx_dlen2[80],	// decay length (3D)
			Tsecvtx_dlen3[80];	// decay length (2D)
        //int 		prim111;
	Int_t	list_k0[180];
	TChain *myChain=new TChain("resonance");
	//TChain *myChain=new TChain("orange");
	// PATH to NTUPLES
 	myChain->Add("/data/zenith226a/libov/data/MCdijet9600/*.root");

//---------------------//
//input
//---------------------//

//--------------------------------------------------------------------------//
	myChain->SetBranchStatus("*",0);

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
	myChain->SetBranchAddress("Tt1_layout",Tt1_layout);
	myChain->SetBranchAddress("Tt2_layout",Tt2_layout);
	myChain->SetBranchAddress("Tt1_layinn",Tt1_layinn);
	myChain->SetBranchAddress("Tt2_layinn",Tt2_layinn);

	myChain->SetBranchAddress("Tsecvtx",Tsecvtx_dlen2);
	myChain->SetBranchAddress("Tsecvtx_dlen2",Tsecvtx_dlen2);
	myChain->SetBranchAddress("Tsecvtx_dlen3",Tsecvtx_dlen3);

	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	myChain->SetBranchAddress("Trk_vtx",Trk_vtx);
	// Primary Vertex
	myChain->SetBranchAddress("Xvtx",&Xvtx);
	myChain->SetBranchAddress("Yvtx",&Yvtx);
	myChain->SetBranchAddress("Zvtx",&Zvtx);
	// Sira, Si_kin
	myChain->SetBranchAddress("Sincand",&Sincand);
	myChain->SetBranchAddress("Siq2el",Siq2el);
	myChain->SetBranchAddress("Siyel",Siyel);
	myChain->SetBranchAddress("Siyjb",Siyjb);
	myChain->SetBranchAddress("Sizuhmom",Sizuhmom);
	myChain->SetBranchAddress("Siecorr",Siecorr);
	myChain->SetBranchAddress("Sith",Sith);
	myChain->SetBranchAddress("Sicalpos",Sicalpos);
	myChain->SetBranchAddress("Sisrtpos",Sisrtpos);
	myChain->SetBranchAddress("Sisrtene",Sisrtene);
	myChain->SetBranchAddress("Siprob",Siprob);
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	myChain->SetBranchAddress("Eventnr",&Eventnr);
	// CAL block - calorimeter info
	//myChain->SetBranchAddress("Cal_et",&Cal_et);
	// Beam, spot
	myChain->SetBranchAddress("Bspt_prog",&Bspt_prog);
	myChain->SetBranchAddress("Bspt_x",&Bspt_x);
	myChain->SetBranchAddress("Bspt_y",&Bspt_y);
	myChain->SetBranchAddress("Bspt_z",&Bspt_z);
	//
	// ktJETSA_A
/*
	myChain->SetBranchAddress("Kt_njet_a",&Kt_njet_a);
	myChain->SetBranchAddress("Kt_etjet_a",Kt_etjet_a);
	myChain->SetBranchAddress("Kt_etajet_a",Kt_etajet_a);
	myChain->SetBranchAddress("Kt_phijet_a",Kt_phijet_a);
*/

	// Trigger stuff
	//myChain->SetBranchAddress("Tltw", Tltw);
//-----------------------------------------------------------------//
	cout<<"Evaluating number of events..."<<endl;
	//nevents=myChain->GetEntries();
	nevents=10000;
	//nevents=20000000;
	//nevents=10;
	cout<<nevents<<" events in this chain"<<endl;

	// TREE VARIABLES DEFINITION
	// these variables are written to tree for further analysis
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
			layout2[80],	//outer superlayer of 2nd pion
			layinn1[80],	//inner superlayer of 1st pion
			layinn2[80];	//inner superlayer of 2nd pion

	Float_t		p1[80][3],	// momenta of 1st track
			p2[80][3],	// momenta of 2nd track
			coll2[80],	//  angle 2D
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
					// m=3 SPP, m=4 DIS ...   k=1 bit 1 (e.g. HPP01) k=2 bit 2 ..
	Float_t		xvtx=0,		// coordinates of primary vertex; 0 if none
			yvtx=0,		//
			zvtx=0;		//

	Float_t		cal_et=0;	// Transverse Energy =SUM(CALTRU_E*sin(thetai))

	Int_t		njet=0;		// Number of jets (kT jet finder A)
	Float_t		etjet[20],	// Transverse energy of jets
			etajet[20],	// eta of jets
			phijet[20];	// phi of jets
	Int_t		event;		// event number

	Float_t		bspt_x,		// beam spot X
			bspt_y,		// beam spot y
			bspt_z;		// beam spot z  ??
	Float_t		secvtx[80][3];	// position of secondary vertex from V0lite
					// (given by Vxlite function there)
	Float_t		dlen2[80],	// decay length (2D) given by V0lite
			dlen3[80];	// decay length (3D) given by V0lite
//-----------------------------------------------------------------//
	Int_t 		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);

	Int_t	nfiles=0;
	//nfiles=nevents/500000+1;
	nfiles=nevents/1000+1;
	cout<<nfiles<<" files"<<endl;
	Int_t 	mill=0;
	char	name[256];
	Int_t	file_num=0;
	Int_t temp=0;
	temp=sprintf(name,"%d.root",file_num);
	TFile *f2 =new TFile(name,"recreate");
	cout<<name<<" created"<<endl;
	//TFile *f2 =new TFile("bla-bla.root","recreate");
	//TClonesArray a("TTree",25);

	//TTree *tree=new TTree("resonance","K0s");
	//tree->Branch("nv0",&nv0,"nv0/I");

	//tree->Branch("p1",p1,"p1[nv0][3]/F");
	/*tree->Branch("p2",p2,"p2[nv0][3]/F");
	tree->Branch("coll2",coll2,"coll2[nv0]/F");
	tree->Branch("coll3",coll3,"coll3[nv0]/F");*/

	bool	fire;
	for(Int_t i=0;i<nevents;i++)
	{
		mill++;
		if ((mill==1000)||(i==(nevents-1)))
		{
			//((TTree *)a.At(file_num))->Print();
			//tree->Print();
			//cout<<"writing tree..."<<endl;
			//tree->Write();
			//tree->Reset();
			cout<<"123123"<<endl;
			//tree->Print();
			cout<<"123123 123123"<<endl;
			//tree->Write();
			//delete tree;
			cout<<"123123 123123 123123"<<endl;
			//((TTree *)a.At(file_num))->Write();
			//cout<<"closing file..."<<endl;
			//delete tree;
			//hdebug->Write();
			cout<<"closing file"<<endl;

			f2->Close();

			//delete f2;
			//f2=NULL;
			cout<<"deleting tree"<<endl;

			//delete f2;
			cout<<"deleted tree"<<endl;
			//
			//tree->Clear();
			//tree->Print();
			//------- output -------//
			file_num++;
			sprintf(name,"%d.root",file_num);
			cout<<name<<endl;
			TFile *f2 =new TFile(name,"recreate");
			f2->cd();
                      //  tree=new TTree("resonance","K0s");
			//tree->Branch("nv0",&nv0,"nv0/I");

	//tree->Branch("p1",p1,"p1[nv0][3]/F");
	/*tree->Branch("p2",p2,"p2[nv0][3]/F");
	tree->Branch("coll2",coll2,"coll2[nv0]/F");
	tree->Branch("coll3",coll3,"coll3[nv0]/F");*/

			mill=0;
		}

		myChain->GetEntry(i);

		if (Nv0lite<1) continue;
		nv0=Nv0lite;
		for (int kk=0;kk<nv0;kk++)
		{
			p1[kk][0]=0.1;
			p1[kk][1]=0.2;
			p1[kk][2]=0.3;
		}
		for (int kk=0;kk<nv0;kk++)
		{
			p2[kk][0]=0.01;
			p2[kk][1]=0.02;
			p2[kk][2]=0.03;
		}

		//nv0=i;
		//cout<<"nv0: "<<nv0<<endl;
		//((TTree *)a.At(file_num))->Fill();
		//cout<<"filling"<<endl;
		//tree->Fill();
		//cout<<"post-filled"<<endl;
		//f2->Print();
		//tree->Print();
		//cout<<"filled"<<endl;


	}

//------- End of events loop ---------//
	////f2->Close();
	//delete ((TTree *)a.At(file_num));

	cout<<ev_pass_DIS<<" events passed DIS selection"<<endl;
	cout<<with_V0<<" events with at least 1 V0"<<endl;
	cout<<"Done!!!"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

