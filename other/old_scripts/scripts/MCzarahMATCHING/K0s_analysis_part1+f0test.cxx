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
//  Modified 05 September: add true info
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

	Float_t		Trk_px[300],
			Trk_py[300],
			Trk_pz[300];



	Float_t		Xvtx=0,
			Yvtx=0,
			Zvtx=0;

	Int_t		Tltw[14];
	Float_t		Cal_et=0;

	Int_t		Kt_njet_a=0;
	Float_t		Kt_etjet_a[20],
			Kt_etajet_a[20],
			Kt_phijet_a[20];

	Int_t		Fmck_nstor=0,		//  Number of stored (e.g. those survived pT cut)
						//  FMCKIN particles
			Fmck_prt[500],		//  particle code FMCPRT
			Fmck_daug[500];		//  Daughter of
	Float_t		Fmck_m[500];		//  particle mass
	Int_t		Fmck_id[500];		//  particle FMCKIN ID
	Float_t		Fmck_px[500],		//  particle px
			Fmck_py[500],		//  particle py
			Fmck_pz[500];		//  particle pz

	Float_t		Mcmatquality[300];
	Int_t		Mcmatfmckin_id[300];

	//TChain *myChain=new TChain("resonance");
	TChain *myChain=new TChain("orange");
	// PATH to NTUPLES
gSystem->Load("libzio.so");
gSystem->Load("libdcap.so");
//------------------------------------------------------------------------------------------//
//input
//------------------------------------------------------------------------------------------//

	// V0lite
	//myChain->SetBranchStatus("*",0);
	myChain->SetBranchAddress("Nv0lite",&Nv0lite);
	//myChain->SetBranchAddress("Tinvmass_k0",Tinvmass_k0);
	//myChain->SetBranchAddress("Tinvmass_lambda",Tinvmass_lambda);
	//myChain->SetBranchAddress("Tinvmass_alambda",Tinvmass_alambda);
	myChain->SetBranchAddress("Tinvmass_ee",Tinvmass_ee);
	myChain->SetBranchAddress("Tsecvtx_collin3",Tsecvtx_collin3);
	myChain->SetBranchAddress("Tsecvtx_collin2",Tsecvtx_collin2);
	myChain->SetBranchAddress("Tpk",Tpk);
	myChain->SetBranchAddress("Tp1",Tp1);
	myChain->SetBranchAddress("Tp2",Tp2);
	//myChain->SetBranchAddress("Tq1",Tq1);
	//myChain->SetBranchAddress("Tq2",Tq2);
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
	myChain->SetBranchAddress("Trk_px",Trk_px);
	myChain->SetBranchAddress("Trk_py",Trk_py);
	myChain->SetBranchAddress("Trk_pz",Trk_pz);
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
	//myChain->SetBranchAddress("Siecorr",Siecorr);
	//myChain->SetBranchAddress("Sith",Sith);
	myChain->SetBranchAddress("Sicalpos",Sicalpos);
	myChain->SetBranchAddress("Sisrtpos",Sisrtpos);
	myChain->SetBranchAddress("Sisrtene",Sisrtene);
	myChain->SetBranchAddress("Siprob",Siprob);
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	//myChain->SetBranchAddress("Eventnr",&Eventnr);


	// CAL block - calorimeter info
	myChain->SetBranchAddress("Cal_et",&Cal_et);
	// ktJETSA_A
	myChain->SetBranchAddress("Kt_njet_a",&Kt_njet_a);
	myChain->SetBranchAddress("Kt_etjet_a",Kt_etjet_a);
	myChain->SetBranchAddress("Kt_etajet_a",Kt_etajet_a);
	myChain->SetBranchAddress("Kt_phijet_a",Kt_phijet_a);

	// FMCKIN (common ntuple additional block)
	myChain->SetBranchAddress("Fmck_nstor",&Fmck_nstor);
	myChain->SetBranchAddress("Fmck_prt",Fmck_prt);
	myChain->SetBranchAddress("Fmck_m",Fmck_m);
	myChain->SetBranchAddress("Fmck_daug",Fmck_daug);
	myChain->SetBranchAddress("Fmck_id",Fmck_id);
	myChain->SetBranchAddress("Fmck_px",Fmck_px);
	myChain->SetBranchAddress("Fmck_py",Fmck_py);
	myChain->SetBranchAddress("Fmck_pz",Fmck_pz);
	//
	myChain->SetBranchAddress("Mcmatquality",Mcmatquality);
	myChain->SetBranchAddress("Mcmatfmckin_id",Mcmatfmckin_id);


	// Trigger stuff
	//myChain->SetBranchAddress("Tltw", Tltw);


	cout<<"Calculating number of events..."<<endl;
	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain..."<<endl;

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
	Int_t		ntrue=0,	//  Number of stored (e.g. those survived pT cut)
					//  FMCKIN particles
			fmcprt[50],	//  FMCPRT
			daug_of[50];	//  Daughter of
	Float_t		mass[50];	//  mass
	Int_t		fmckin_id[50];	// FMCKIN ID of the particle
	Float_t		px[50],		// px of the particle
			py[50],		// py of the particle
			pz[50];		// pz of the particle
	Int_t		match[50];	// zttrhl or vctrhl id of the corresponding track if matched
					// -1 if not matched
	Float_t		px_mat[50],	// momentum for matched particle, -1 if not matched
			py_mat[50],	//
			pz_mat[50];
	Float_t		mat_qual[50];	// quality of matching
	//-------------------------------------------------------------------------------------------//
	Int_t 		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);
	cout<<"Start add branches"<<endl;
	TTree *tree=new TTree("resonance","K0sK0s");
	tree->Branch("nv0",&nv0,"nv0/I");
	tree->Branch("p1",p1,"p1[nv0][3]/F");
	tree->Branch("p2",p2,"p2[nv0][3]/F");
	tree->Branch("coll2",coll2,"coll2[nv0]/F");
	tree->Branch("coll3",coll3,"coll3[nv0]/F");
	tree->Branch("id1",id1,"id1[nv0]/I");
	tree->Branch("id2",id2,"id2[nv0]/I");
	tree->Branch("is1_sec",is1_sec,"is1_sec[nv0]/I");
	tree->Branch("is2_sec",is2_sec,"is2_sec[nv0]/I");
	tree->Branch("is1_prim",is1_prim,"is1_prim[nv0]/I");
	tree->Branch("is2_prim",is2_prim,"is2_prim[nv0]/I");
	tree->Branch("runnr",&runnr,"runnr/I");
	tree->Branch("q2el",&q2el,"q2el/F");
	tree->Branch("yel",&yel,"yel/F");
	tree->Branch("yjb",&yel,"yjb/F");
	tree->Branch("siprob",&siprob,"siprob/F");
	tree->Branch("sincand",&sincand,"sincand/I");
	tree->Branch("box_x",&box_x,"box_x/F");
	tree->Branch("box_y",&box_y,"box_y/F");
	tree->Branch("e_pz",&e_pz,"e_pz/F");
	tree->Branch("mass_lambda",mass_lambda,"mass_lambda[nv0]/F");
	tree->Branch("mass_ee",mass_ee,"mass_ee[nv0]/F");
	tree->Branch("layout1",layout1,"layout1[nv0]/I");
	tree->Branch("layout2",layout2,"layout2[nv0]/I");
	tree->Branch("layinn1",layinn1,"layinn1[nv0]/I");
	tree->Branch("layinn2",layinn2,"layinn2[nv0]/I");
	//tree->Branch("tlt",tlt,"tlt[6][16]/I");
	tree->Branch("xvtx",&xvtx,"xvtx/F");
	tree->Branch("yvtx",&yvtx,"yvtx/F");
	tree->Branch("zvtx",&zvtx,"zvtx/F");
	tree->Branch("cal_et",&cal_et,"cal_et/F");
	tree->Branch("njet",&njet,"njet/I");
	tree->Branch("etjet",&etjet,"etjet[njet]/F");
	tree->Branch("etajet",&etajet,"etajet[njet]/F");
	tree->Branch("phijet",&phijet,"phijet[njet]/F");
	tree->Branch("ntrue",&ntrue,"ntrue/I");
	tree->Branch("fmcprt",&fmcprt,"fmcprt[ntrue]/I");
	tree->Branch("mass",&mass,"mass[ntrue]/F");
	tree->Branch("daug_of",&daug_of,"daug_of[ntrue]/I");
	tree->Branch("fmckin_id",&fmckin_id,"fmckin_id[ntrue]/I");
	tree->Branch("px",&px,"px[ntrue]/F");
	tree->Branch("py",&py,"py[ntrue]/F");
	tree->Branch("pz",&pz,"pz[ntrue]/F");
	tree->Branch("match",&match,"match[ntrue]/I");
	tree->Branch("px_mat",&px_mat,"px_mat[ntrue]/F");
	tree->Branch("py_mat",&py_mat,"py_mat[ntrue]/F");
	tree->Branch("pz_mat",&pz_mat,"pz_mat[ntrue]/F");

//------ Loop over events -------//

	char	name[256];
	Int_t	file_num=0;
	bool	fire;
	cout<<"Start looping..."<<endl;
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;
		//cout<<"Getting entry "<<i<<" ..."<<endl;
		myChain->GetEntry(i);


		bool		kshort=false,
				pi_plus=false,
				pi_minus=false,
				pi=false,
				f0980=false,
				daug_of_kshort=false;
		ntrue=0;

		for (int k=0;k<Fmck_nstor;k++)
		{
			// particle k identification
			kshort=false;
			pi_plus=false;
			pi_minus=false;
			f0980=false;
			daug_of_kshort=false;
			bool	fromf0=false;

			kshort=(Fmck_prt[k]==62);
			pi_plus=(Fmck_prt[k]==54);
			pi_minus=(Fmck_prt[k]==55);
			pi=(pi_plus||pi_minus);
			f0980=(Fmck_prt[k]==81);


			
			if (pi)
			{
				Int_t	parent_fmckin=0;
				parent_fmckin=Fmck_daug[k];	// Fmckin id of mother of k
				//cout<<"Parent of pi+/pi-: "<<parent_fmckin<<endl;
				Int_t	K0s=0;
				for (int jj=0;jj<Fmck_nstor;jj++)
				{
					//cout<<Fmck_id[jj]<<endl;
					if (Fmck_id[jj]!=parent_fmckin) continue;	// skip if not mother of k
					//cout<<Fmck_prt[jj]<<endl;
					// now jj is index of mother of particle k
					daug_of_kshort=(Fmck_prt[jj]==62);
					K0s=jj;
					//cout<<"Parent of pi+/pi-: "<<parent_fmckin<<endl;
					break;
				}
				if (!daug_of_kshort) continue;
				//cout<<"pi from K0s"<<endl;
				// now K0s is Fmck (not Fmckin) id of kaon mother of charged pion
				// check mother of this kaon
				Int_t	mother_of_K0s=0;
				mother_of_K0s=Fmck_daug[K0s]; // this FMCKIN id of mother of K0s
				for (int c1=0;c1<Fmck_nstor;c1++)
				{
					if (Fmck_id[c1]!=mother_of_K0s) continue;
					//now c1 points to mother of K0s
					//cout<<Fmck_prt[c1]<<endl;
					if (Fmck_prt[c1]!=81) continue; // consider only f0(980)
					fromf0=true;
					break;
				}
			}
			//if (pi) cout<<"found charged pion"<<endl;
			if (pi&&fromf0)
			{
				cout<<"found charged pion from f0 decay!!! "<<endl;
				fmcprt[ntrue]=Fmck_prt[k];
				mass[ntrue]=Fmck_m[k];
				daug_of[ntrue]=Fmck_daug[k];
				fmckin_id[ntrue]=Fmck_id[k];
				px[ntrue]=Fmck_px[k];
				py[ntrue]=Fmck_py[k];
				pz[ntrue]=Fmck_pz[k];
				match[ntrue]=-1;
				px_mat[ntrue]=-1;
				py_mat[ntrue]=-1;
				pz_mat[ntrue]=-1;
				mat_qual[ntrue]=-9999;
				for (int c2=0;c2<Trk_ntracks;c2++)
				{
					if (Fmck_id[k]==Mcmatfmckin_id[c2])
					{
						match[ntrue]=Trk_id[c2];//zttrhl or vctrhl id of the track
						px_mat[ntrue]=Trk_px[c2];
						py_mat[ntrue]=Trk_py[c2];
						pz_mat[ntrue]=Trk_pz[c2];
						mat_qual[ntrue]=Mcmatquality[c2];
					}
				}
				ntrue++;
			}

		}

		tree->Fill();

	}
//------- End of events loop ---------//

	tree->Print();

//output



	TFile *f2 =new TFile(name,"recreate");
	cout<<"File created"<<endl;
	tree->Write();
	cout<<"Tree wrote"<<endl;
	f2->Close();
	cout<<"File Closed"<<endl;
	delete tree;
	cout<<"Tree deleted, O.K.!"<<endl;


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
//STOP

