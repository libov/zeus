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

	//TChain *myChain=new TChain("resonance");
	TChain *myChain=new TChain("orange");
	// PATH to NTUPLES

//----------------
myChain->Add("/data/zenith224c/gmuon/RUNS/data_05e_v2007a/data/data_05e_52258_52259_01.root");
//myChain->Add("/data/zenith224c/gmuon/RUNS/data_05e_v2007a/data/data_05e_52260_52283_01.root");


//input


//-----------------
	// V0lite
	myChain->SetBranchStatus("*",0);
	myChain->SetBranchAddress("Nv0lite",&Nv0lite);

	cout<<"Evaluating number of events..."<<endl;
	nevents=myChain->GetEntries();
	//nevents=100;
	cout<<nevents<<" events in this chain"<<endl;
	TH1F *h=new TH1F("h","",80,0,80);
	for (int k=0;k<nevents;k++)
	{
		myChain->GetEntry(k);
		h->Fill(Nv0lite);
	}
	TFile *f1 =new TFile("test.root","recreate");

	h->Write();
	f1->Close();
	cout<<"Done!!!"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

