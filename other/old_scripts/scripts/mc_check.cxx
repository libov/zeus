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

	TChain *myChain=new TChain("resonance");
	// PATH to NTUPLES
	myChain->Add("/data/zenith226a/libov/myOrange/job003/run/test_ztt.root");
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
	myChain->SetBranchAddress("Cal_et",&Cal_et);
	// Beam, spot
	myChain->SetBranchAddress("Bspt_prog",&Bspt_prog);
	myChain->SetBranchAddress("Bspt_x",&Bspt_x);
	myChain->SetBranchAddress("Bspt_y",&Bspt_y);
	myChain->SetBranchAddress("Bspt_z",&Bspt_z);

	// FMCKIN block
	Int_t	nPart=0;
	Int_t	Part_id[10];
	Int_t	Part_prt[10];
	Float_t	Part_p[10][4];
	myChain->SetBranchAddress("nPart",&nPart);
	myChain->SetBranchAddress("Part_id",Part_id);
	myChain->SetBranchAddress("Part_prt",Part_prt);
	myChain->SetBranchAddress("Part_p",Part_p);
	//-----------------------------------------

	cout<<"Evaluating number of events..."<<endl;
	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	for (int k=0;k<nevents;k++)
	{


	}



}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

