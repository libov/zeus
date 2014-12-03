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
	Float_t	Tinvmass_k0[80],
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
	Int_t 	Trk_prim_vtx[300],
				Trk_sec_vtx[300],
				Trk_vtx[300],
				Runnr=0,
				year=0,
				k0_cand=0;
	const	Int_t 	low_2004=47010,
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

	Int_t			Tltw[14];
	Float_t		Cal_et=0;

	Int_t			Kt_njet_a=0;
	Float_t		Kt_etjet_a[20],
					Kt_etajet_a[20],
					Kt_phijet_a[20];
	Int_t			Fmck_nstor=0,		//  Number of stored (e.g. those survived pT cut)
											//  FMCKIN particles
					Fmck_prt[500],		//  particle code FMCPRT
					Fmck_daug[500];		//  Daughter of
	Float_t		Fmck_m[500];		//  particle mass

	//TChain *myChain=new TChain("resonance");
	TChain *myChain=new TChain("orange");
	// PATH to NTUPLES

	gSystem->Load("libzio.so");
	gSystem->Load("libdcap.so");
//------------------------------------------------------------------------------------------//
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0001.root");
/*myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0002.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0003.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0004.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0005.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0006.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0007.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0008.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0009.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0010.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0011.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0012.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0013.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0014.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0015.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0016.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0017.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0018.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0019.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0020.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0021.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0022.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0023.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0024.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0025.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0026.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0027.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0028.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0029.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0030.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0031.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0032.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0033.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0034.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0035.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0036.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0037.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0038.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0039.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0040.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0041.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0042.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0043.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0044.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0045.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0046.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0047.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0048.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0049.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0050.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0051.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0001.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0002.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0003.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0004.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0005.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0006.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0007.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0008.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0009.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0010.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0011.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0012.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0013.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0014.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0015.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0016.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0017.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0018.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0019.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0020.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0021.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0022.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0023.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0024.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0025.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0026.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0027.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0028.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0029.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0030.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0031.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0032.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0033.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0034.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0035.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0036.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0037.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0038.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0039.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0040.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0041.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0042.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0043.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0044.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0045.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0046.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0047.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0048.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0049.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0050.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0051.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0052.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0053.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0054.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0055.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0056.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0057.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0058.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0059.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0060.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0061.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0062.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0063.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0064.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0065.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0066.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0067.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0068.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0069.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0070.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0071.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0072.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0073.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0074.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0075.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0076.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0077.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0078.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0079.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0080.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0081.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0082.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0083.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0084.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0085.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0086.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0087.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0088.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0089.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0090.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0091.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0092.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0093.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0094.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0095.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0096.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0097.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0098.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0099.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0100.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0101.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0102.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0103.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0104.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0105.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0106.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0107.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0108.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0109.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0110.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0111.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0112.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0113.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0114.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0115.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0116.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0117.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0118.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0119.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0120.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0121.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0122.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0123.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0124.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0125.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0126.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0127.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0128.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0129.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0130.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0131.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0132.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0133.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0134.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0135.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0136.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0137.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0138.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0139.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0140.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0141.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0142.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0143.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0144.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0145.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0146.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0147.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0148.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfres.e0506.uncut_0149.root");*/
//------------------------------------------------------------------------------------------//

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


	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	myChain->SetBranchAddress("Trk_vtx",Trk_vtx);
	//Vertex
	myChain->SetBranchAddress("Xvtx",&Xvtx);
	myChain->SetBranchAddress("Yvtx",&Yvtx);
	myChain->SetBranchAddress("Zvtx",&Zvtx);
	//Sira, Si_kin
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
	// CAL block - calorimeter info
	myChain->SetBranchAddress("Cal_et",&Cal_et);
	// ktJETSA_A
	myChain->SetBranchAddress("Kt_njet_a",&Kt_njet_a);
	myChain->SetBranchAddress("Kt_etjet_a",Kt_etjet_a);
	myChain->SetBranchAddress("Kt_etajet_a",Kt_etajet_a);
	myChain->SetBranchAddress("Kt_phijet_a",Kt_phijet_a);

	// Trigger stuff
	//myChain->SetBranchAddress("Tltw", Tltw);


	myChain->SetBranchAddress("Fmck_nstor",&Fmck_nstor);
	myChain->SetBranchAddress("Fmck_prt",Fmck_prt);
	myChain->SetBranchAddress("Fmck_m",Fmck_m);
	myChain->SetBranchAddress("Fmck_daug",Fmck_daug);

	cout<<"Evaluating number of events..."<<endl;
	//nevents=myChain->GetEntries();
	nevents=100;
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

	Float_t	p1[80][3],	// momenta of 1st track
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

	Int_t		ntrue=0,	//  Number of stored (e.g. those survived pT cut)
					//  FMCKIN particles
			fmcprt[500],	//  FMCPRT
			daug_of[500];	//  Daughter of
	Float_t		mass[500];	//  mass

	//-------------------------------------------------------------------------------------------//
	Int_t 		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);

	Int_t	nfiles=0;
	nfiles=nevents/500000+1;
	cout<<nfiles<<" files"<<endl;
	TClonesArray a("TTree",25);
	for (Int_t i=0;i<nfiles+1;i++)
	{
		new(a[i]) TTree("resonance","K0sK0s");

		((TTree *)a.At(i))->Branch("ntrue",&ntrue,"ntrue/I");
		((TTree *)a.At(i))->Branch("fmcprt",&fmcprt,"fmcprt[ntrue]/I");
		((TTree *)a.At(i))->Branch("mass",&mass,"mass[ntrue]/I");
		((TTree *)a.At(i))->Branch("daug_of",&daug_of,"daug_of[ntrue]/I");
		((TTree *)a.At(i))->Branch("nv0",&nv0,"nv0/I");
		((TTree *)a.At(i))->Branch("p1",p1,"p1[nv0][3]/F");
		((TTree *)a.At(i))->Branch("p2",p2,"p2[nv0][3]/F");
		((TTree *)a.At(i))->Branch("coll2",coll2,"coll2[nv0]/F");
		((TTree *)a.At(i))->Branch("coll3",coll3,"coll3[nv0]/F");
		((TTree *)a.At(i))->Branch("id1",id1,"id1[nv0]/I");
		((TTree *)a.At(i))->Branch("id2",id2,"id2[nv0]/I");
		((TTree *)a.At(i))->Branch("is1_sec",is1_sec,"is1_sec[nv0]/I");
		((TTree *)a.At(i))->Branch("is2_sec",is2_sec,"is2_sec[nv0]/I");
		((TTree *)a.At(i))->Branch("is1_prim",is1_prim,"is1_prim[nv0]/I");
		((TTree *)a.At(i)) ->Branch("is2_prim",is2_prim,"is2_prim[nv0]/I");

	}
//------ Loop over events -------//
	Int_t 	mill=0;
	char	name[256];
	Int_t	file_num=0;
	bool	fire;
	int max=0;
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;

		if ((mill==500000)||(i==(nevents-1)))
		{
			Int_t temp=0;

			temp=sprintf(name,"test_%d.root",file_num);
			((TTree *)a.At(file_num))->Print();
			TFile *f2 =new TFile(name,"recreate");
			((TTree *)a.At(file_num))->Write();
			f2->Close();
			cout<<"event nr "<<i<<"; "<<file_num<<" "<<name<<endl;
			delete ((TTree *)a.At(file_num));
			mill=0;
			file_num++;
		}

		mill++;
		myChain->GetEntry(i);

		ntrue=Fmck_nstor;
		if (ntrue>max) max=ntrue;
		for (int k=0;k<ntrue;k++)
		{
			fmcprt[k]=Fmck_prt[k];
			mass[k]=Fmck_m[k];
			daug_of[k]=Fmck_daug[k];
		}



		((TTree *)a.At(file_num))->Fill();
	}
//------- End of events loop ---------//
	delete ((TTree *)a.At(file_num));
	cout<<"Amx number of tru particles: "<<max<<endl;
	cout<<"Done!!!"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

