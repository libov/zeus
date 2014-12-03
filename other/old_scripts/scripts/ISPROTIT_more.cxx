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
	/*for (Int_t i=0;i<nfiles+1;i++)
	{
		new(a[i]) TTree("resonance","K0sK0s in DIS");
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
		((TTree *)a.At(i))->Branch("is2_prim",is2_prim,"is2_prim[nv0]/I");
		((TTree *)a.At(i))->Branch("runnr",&runnr,"runnr/I");
		((TTree *)a.At(i))->Branch("q2el",&q2el,"q2el/F");
		((TTree *)a.At(i))->Branch("yel",&yel,"yel/F");
		((TTree *)a.At(i))->Branch("yjb",&yel,"yjb/F");
		((TTree *)a.At(i))->Branch("siprob",&siprob,"siprob/F");
		((TTree *)a.At(i))->Branch("sincand",&sincand,"sincand/I");
		((TTree *)a.At(i))->Branch("box_x",&box_x,"box_x/F");
		((TTree *)a.At(i))->Branch("box_y",&box_y,"box_y/F");
		((TTree *)a.At(i))->Branch("e_pz",&e_pz,"e_pz/F");
		((TTree *)a.At(i))->Branch("mass_lambda",mass_lambda,"mass_lambda[nv0]/F");
		((TTree *)a.At(i))->Branch("mass_ee",mass_ee,"mass_ee[nv0]/F");
		((TTree *)a.At(i))->Branch("layout1",layout1,"layout1[nv0]/I");
		((TTree *)a.At(i))->Branch("layout2",layout2,"layout2[nv0]/I");
		((TTree *)a.At(i))->Branch("layinn1",layinn1,"layinn1[nv0]/I");
		((TTree *)a.At(i))->Branch("layinn2",layinn2,"layinn2[nv0]/I");
		//((TTree *)a.At(i))->Branch("tlt",tlt,"tlt[6][16]/I");
		((TTree *)a.At(i))->Branch("xvtx",&xvtx,"xvtx/F");
		((TTree *)a.At(i))->Branch("yvtx",&yvtx,"yvtx/F");
		((TTree *)a.At(i))->Branch("zvtx",&zvtx,"zvtx/F");
		((TTree *)a.At(i))->Branch("cal_et",&cal_et,"cal_et/F");
		//((TTree *)a.At(i))->Branch("njet",&njet,"njet/I");
		//((TTree *)a.At(i))->Branch("etjet",&etjet,"etjet[njet]/F");
		//((TTree *)a.At(i))->Branch("etajet",&etajet,"etajet[njet]/F");
		//((TTree *)a.At(i))->Branch("phijet",&phijet,"phijet[njet]/F");
		((TTree *)a.At(i))->Branch("event",&event,"event/I");
		((TTree *)a.At(i))->Branch("ntracks",&ntracks,"ntracks/I");
		((TTree *)a.At(i))->Branch("bspt_x",&bspt_x,"bspt_x/F");
		((TTree *)a.At(i))->Branch("bspt_y",&bspt_y,"bspt_y/F");
		((TTree *)a.At(i))->Branch("bspt_z",&bspt_z,"bspt_z/F");
		((TTree *)a.At(i))->Branch("secvtx",secvtx,"secvtx[nv0][3]/F");
		((TTree *)a.At(i))->Branch("dlen2",dlen2,"dlen2[nv0]/F");
		((TTree *)a.At(i))->Branch("dlen3",dlen3,"dlen3[nv0]/F");
	}*/

	TTree *tree=new TTree("resonance","K0s");
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
	//tree->Branch("njet",&njet,"njet/I");
	//tree->Branch("etjet",&etjet,"etjet[njet]/F");
	//tree->Branch("etajet",&etajet,"etajet[njet]/F");
	//tree->Branch("phijet",&phijet,"phijet[njet]/F");
	tree->Branch("event",&event,"event/I");
	tree->Branch("ntracks",&ntracks,"ntracks/I");
	tree->Branch("bspt_x",&bspt_x,"bspt_x/F");
	tree->Branch("bspt_y",&bspt_y,"bspt_y/F");
	tree->Branch("bspt_z",&bspt_z,"bspt_z/F");
	tree->Branch("secvtx",secvtx,"secvtx[nv0][3]/F");
	tree->Branch("dlen2",dlen2,"dlen2[nv0]/F");
	tree->Branch("dlen3",dlen3,"dlen3[nv0]/F");

//------ Loop over events -------//

	bool	fire;
	//nevents=500001;
	//file_num=18;
	cout<<"Starting loop"<<endl;
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;
		mill++;
		//if ((mill==500000)||(i==(nevents-1)))
		if ((mill==1000)||(i==(nevents-1)))
		{
			//((TTree *)a.At(file_num))->Print();
			//tree->Print();
			cout<<"writing tree..."<<endl;
			tree->Write();
			//tree->Reset();
			//((TTree *)a.At(file_num))->Write();
			//hdebug->Write();
			delete tree;
			f2->Close();
			//delete f2;

			//tree->Print();
			//------- output -------//
			file_num++;
			temp=sprintf(name,"%d.root",file_num);
			cout<<"name = "<<name<<endl;
			TFile *f2 =new TFile(name,"recreate");
			f2->cd();
                        tree=new TTree("resonance","K0s");
			tree->Branch("nv0",&nv0,"nv0/I");
			cout<<"deleted tree"<<endl;
			//----------new tree---//

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
	//tree->Branch("njet",&njet,"njet/I");
	//tree->Branch("etjet",&etjet,"etjet[njet]/F");
	//tree->Branch("etajet",&etajet,"etajet[njet]/F");
	//tree->Branch("phijet",&phijet,"phijet[njet]/F");
	tree->Branch("event",&event,"event/I");
	tree->Branch("ntracks",&ntracks,"ntracks/I");
	tree->Branch("bspt_x",&bspt_x,"bspt_x/F");
	tree->Branch("bspt_y",&bspt_y,"bspt_y/F");
	tree->Branch("bspt_z",&bspt_z,"bspt_z/F");
	tree->Branch("secvtx",secvtx,"secvtx[nv0][3]/F");
	tree->Branch("dlen2",dlen2,"dlen2[nv0]/F");
	tree->Branch("dlen3",dlen3,"dlen3[nv0]/F");

			//-----end new tree-------//
			//---------------------//

			//cout<<"created new file"<<endl;
			//tree->Write();

			//cout<<"event nr "<<i<<"; "<<file_num<<" "<<name<<endl;
			//delete ((TTree *)a.At(file_num));
			//cout<<"deleted tree .at("<<file_num<<");"<<endl;
			mill=0;
		}

		cout<<i<<endl;
		myChain->GetEntry(i);
	//------DIS event selection------//
		hdebug->Fill(1);
		//if (Siq2el[0]<1) continue;		// Q^2>1 GeV^2
		hdebug->Fill(2);
		// E-pz calculation
		float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   		float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   		float EminPz_Evt  = Empz_e + Empz_had;
		//if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;			// 38 < E-pz < 60 GeV
		hdebug->Fill(3);
		// electron position calculation (box cut)
		float x_srtd=Sicalpos[0][0];		// position of electron in calorimeter
   		float y_srtd=Sicalpos[0][1];
   		if (Sisrtene[0]>0)
		{
      			x_srtd=Sisrtpos[0][0];		// position of electron in SRDT
      			y_srtd=Sisrtpos[0][1];
    		}
		if (TMath::Abs(x_srtd)<12)		// box cut: electron required to be outside 12x6 cm^2 box
		{
			//if (TMath::Abs(y_srtd)<6) continue;
		}
		hdebug->Fill(4);
		//if (Siyel[0]>0.95) continue;		// y from electron method < 0.95
		hdebug->Fill(5);
		//if (Siyjb[0]<0.01) continue;		// y from Jacquet-Blondel method > 0.01
		hdebug->Fill(6);

		ev_pass_DIS++;
	//------ (soft) K0s selection------//
		Int_t	cand_k0=0,
			list_k0[180];

		if (Nv0lite<1) continue;
		with_V0++;
		if (Nv0lite>75) cout<<"Yooooooooo:   "<<Nv0lite<<endl;

		//this loop is now sensless but it will become necessary if we restrict to at least 2K0s
		for(Int_t j=0;j<Nv0lite;j++)
		{
			Daughter t1(Tp1[j][0],Tp1[j][1],Tp1[j][2]);
			Daughter t2(Tp2[j][0],Tp2[j][1],Tp2[j][2]);
			if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
			if ((Tt1_layout[j]<3)||(Tt2_layout[j]<3)) continue;
			Mother K0s_cand(t1,t2);
			//cout<<mass_pi_p<<" "<<Tinvmass_lambda[j]<<" "<<Tinvmass_alambda[j]<<endl;
			//if (mass_pi_p<1.116) continue;
			//mass_lambda=mass_pi_p;
			//mass_ee=Tinvmass_ee[j];
			//if (Tinvmass_ee[j]<0.05) continue;

			Int_t 		prim1=1,
					prim2=1;
			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == Tt1_id[j])
				{
					prim1=Trk_prim_vtx[n];
					continue;
				}
                		if (idx == Tt2_id[j])
				{
					prim2=Trk_prim_vtx[n];
					continue;
				}
        		}
       			if ((prim1==1)||(prim2==1)) continue;
			list_k0[cand_k0]=j;
			cand_k0++;
		} //end k0 selection

		if (Trk_ntracks>295) cout<<Trk_ntracks<<endl;

		if (cand_k0<1) continue;
		nv0=cand_k0;
		cout<<"nv0: "<<nv0<<endl;
		if (nv0>75) cout<<nv0<<endl;
		Int_t id=0;
	//---- Tree filling -----//
		for(Int_t k=0;k<nv0;k++)
		{
			id=list_k0[k];
			p1[k][0]=Tp1[id][0];
			p1[k][1]=Tp1[id][1];
			p1[k][2]=Tp1[id][2];
			p2[k][0]=Tp2[id][0];
			p2[k][1]=Tp2[id][1];
			p2[k][2]=Tp2[id][2];
			coll2[k]=Tsecvtx_collin2[id];
			coll3[k]=Tsecvtx_collin3[id];
			id1[k]=Tt1_id[id];
			id2[k]=Tt2_id[id];
			Int_t 	t1_prim=1,
				t2_prim=1,
				t1_sec=0,
				t2_sec=0,
				t1_vertex_id=-1,
				t2_vertex_id=-1;
			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == Tt1_id[id])
				{
					t1_prim=Trk_prim_vtx[n];
					t1_sec=Trk_sec_vtx[n];
					t1_vertex_id=Trk_vtx[n];
					continue;
				}
                		if (idx == Tt2_id[id])
				{
					t2_prim=Trk_prim_vtx[n];
					t2_sec=Trk_sec_vtx[n];
					t2_vertex_id=Trk_vtx[n];
					continue;
				}
        		}
			is1_sec[k]=t1_sec;
			is2_sec[k]=t2_sec;
			is1_prim[k]=t1_prim;
			is2_prim[k]=t2_prim;

			Daughter temp1(Tp1[id][0],Tp1[id][1],Tp1[id][2]);
			Daughter temp2(Tp2[id][0],Tp2[id][1],Tp2[id][2]);
			Mother K0s_candtemp(temp1,temp2);
			Float_t ptemp1=temp1.GetP();
			Float_t ptemp2=temp2.GetP();
			Float_t mass_pi_ptemp=0;
			if (ptemp1>ptemp2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_ptemp=K0s_candtemp.GetMass_m(6,4);
			}
			if (ptemp1<ptemp2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_ptemp=K0s_candtemp.GetMass_m(4,6);
			}
			mass_lambda[k]=mass_pi_ptemp;
			mass_ee[k]=Tinvmass_ee[id];
			layout1[k]=Tt1_layout[id];
			layout2[k]=Tt2_layout[id];
			layinn1[k]=Tt1_layinn[id];
			layinn2[k]=Tt2_layinn[id];
			secvtx[k][0]=Tsecvtx[id][0];
			secvtx[k][1]=Tsecvtx[id][1];
			secvtx[k][2]=Tsecvtx[id][2];
			dlen2[k]=Tsecvtx_dlen2[id];
			dlen3[k]=Tsecvtx_dlen3[id];
		}

		runnr=Runnr;
		event=Eventnr;
		ntracks=Trk_ntracks;

		if (Sincand>0)
		{
			q2el=Siq2el[0];
			siprob=Siprob[0];
		}
		if (Sincand==0)
		{
			q2el=0;
			siprob=0;
		}
		sincand=Sincand;
		//cout<<Sincand<<" "<<Siyel[0]<<" "<<Siyjb[0]<<endl;
		yel=Siyel[0];
		yjb=Siyjb[0];
		box_x=x_srtd;
		box_y=y_srtd;
		e_pz=EminPz_Evt;
		//cal_et=Cal_et;
	/*
		// trigger defining
		for (int m=0;m<6;m++)
		{

			for (int k=0;k<16;k++)
			{
				fire = (Bool_t)(Tltw[m+6-1] & (1 << k) );
				//tlt[m][k]=2;
				tlt[m][k]=0;
				if (fire)
				{
					tlt[m][k]=1;
					//cout<<m<<", bit"<<k+1<<" fired"<<endl;
				}
			}
		}
	*/
		xvtx=Xvtx;
		yvtx=Yvtx;
		zvtx=Zvtx;

		if (Bspt_prog>0)
		{
			bspt_x=Bspt_x;
			bspt_y=Bspt_y;
			bspt_z=Bspt_z;
		}
		else
		{
			bspt_x=-1;
			bspt_y=-1;
			bspt_z=-1;
		}

		/*
		njet=Kt_njet_a;
		for (int jet=0;jet<njet;jet++)
		{
			etjet[jet]=Kt_etjet_a[jet];
			etajet[jet]=Kt_etajet_a[jet];
			phijet[jet]=Kt_phijet_a[jet];
		}
		*/
		//((TTree *)a.At(file_num))->Fill();
		//tree->Print();
		//cout<<"filling"<<endl;
		tree->Fill();
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

