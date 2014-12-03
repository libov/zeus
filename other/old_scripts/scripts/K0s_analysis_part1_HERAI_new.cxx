//////////////////////////////////////////////////
//////////////   K0s   analysis  /////////////////
//////////////  with K0s finder  /////////////////
///////////  using tracking block  ///////////////
//////////////      (part1)      /////////////////
//////////////      {HERAI}      /////////////////
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
//   2. K0s selection                           //
//   3. Writing data to small tree              //
//      easy to analyze                         //
//                                              //
//////////////////////////////////////////////////
// new files (my latest K0 finder)
#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
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
			//Tt1_id[80],
			//Tt2_id[80],
			Tq1[80],
			Tq2[80],
			Trk_ntracks=0,
			Trk_id[300],
			Tt1_layout[80],
			Tt2_layout[80];
	Float_t		Tsecvtx[80][3],
			reso_mass=0,
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
			Siprob[10],
			Trk_px[300],
			Trk_py[300],
			Trk_pz[300];
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

	/*Int_t		Nv0=0,
			V0trk1_id[40],
                 	V0trk2_id[40];
	Float_t		V0p3[40][3],
                 	V0the[40],
                 	V0eta[40],
                 	Mpipi[40],
                 	Mpropi[40],
                 	Charge_pro[40],
                 	Mee[40],
                 	V0trk1_the[40],
                 	V0trk1_eta[40],
                 	V0trk2_the[40],
                 	V0trk2_eta[40],
                 	V0dlen[40],
                 	V0colang[40];*/

	Int_t		Nv0psy=0,
			T1_id[40],
			T2_id[40];
	Float_t		P1[40][3],
			P2[40][3],
			V0coll2d[40],
			V0coll3d[40];

	TChain *myChain=new TChain("resonance");
	// PATH to NTUPLES


	//myChain->Add("/data/zenith226a/libov/data/heraI_new/*.root");
	myChain->Add("/data/zenith226a/libov/data/MCtemp/*.root");


	/*
	// M.Barbi finder variables
	myChain->SetBranchAddress("Nv0",&Nv0);
	myChain->SetBranchAddress("V0trk1_id",V0trk1_id);
	myChain->SetBranchAddress("V0trk2_id",V0trk2_id);
	myChain->SetBranchAddress("V0trk1_the",V0trk1_the);
	myChain->SetBranchAddress("V0trk2_the",V0trk2_the);
	myChain->SetBranchAddress("V0trk1_eta",V0trk1_eta);
	myChain->SetBranchAddress("V0trk2_eta",V0trk2_eta);
	myChain->SetBranchAddress("V0p3",V0p3);
	myChain->SetBranchAddress("V0colang",V0colang);
	myChain->SetBranchAddress("V0dlen",V0dlen);
	myChain->SetBranchAddress("V0the",V0the);
	myChain->SetBranchAddress("V0eta",V0eta);
	myChain->SetBranchAddress("Mpipi",Mpipi);
	myChain->SetBranchAddress("Mpropi",Mpropi);
	myChain->SetBranchAddress("Charge_pro",Charge_pro);
	myChain->SetBranchAddress("Mee",Mee);
	*/
	myChain->SetBranchAddress("Nv0psy",&Nv0psy);
	myChain->SetBranchAddress("P1",P1);
	myChain->SetBranchAddress("P2",P2);
	myChain->SetBranchAddress("T1_id",T1_id);
	myChain->SetBranchAddress("T2_id",T2_id);
	myChain->SetBranchAddress("V0coll2d",V0coll2d);
	myChain->SetBranchAddress("V0coll3d",V0coll3d);
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
	myChain->SetBranchAddress("Siecorr",Siecorr);
	myChain->SetBranchAddress("Sith",Sith);
	myChain->SetBranchAddress("Sicalpos",Sicalpos);
	myChain->SetBranchAddress("Sisrtpos",Sisrtpos);
	myChain->SetBranchAddress("Sisrtene",Sisrtene);
	myChain->SetBranchAddress("Siprob",Siprob);
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	nevents=myChain->GetEntries();
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
			layout2[80];	//outer superlayer of 2nd pion

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
	Float_t		xvtx=0,		// coordinates of primary vertex; 0 if none
			yvtx=0,		//
			zvtx=0;		//

	TTree *tree = new TTree("resonance","K0sK0s in DIS");
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
	tree->Branch("xvtx",&xvtx,"xvtx/F");
	tree->Branch("yvtx",&yvtx,"yvtx/F");
	tree->Branch("zvtx",&zvtx,"zvtx/F");

	Int_t 		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;

		myChain->GetEntry(i);
	//------DIS event selection------//
		hdebug->Fill(1);
		//if (Siq2el[0]<1) continue;					// Q^2>1 GeV^2
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

	//------K0s selection------//
		Int_t	cand_k0=0,
			list_k0[80];
		if (Nv0psy<1) continue;
		with_V0++;
		//this loop is now sensless but it will become necessary if we restrict to at least 2K0s
		for(Int_t j=0;j<Nv0psy;j++)
		{

			Daughter t1(P1[j][0],P1[j][1],P1[j][2]);
			Daughter t2(P2[j][0],P2[j][1],P2[j][2]);
			Mother K0s_cand(t1,t2);
			Float_t p1=t1.GetP();
			Float_t p2=t2.GetP();
			Float_t mass_pi_p=0;
			if (p1>=p2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
				//if(Tq1[j]>0) cout<<"Lambda"<<endl;
				//if(Tq1[j]<0) cout<<"ALambda"<<endl;
			}
			if (p1<p2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
				//if(Tq1[j]>0) cout<<"ALambda"<<endl;
				//if(Tq1[j]<0) cout<<"Lambda"<<endl;
			}
			//cout<<mass_pi_p<<" "<<Tinvmass_lambda[j]<<" "<<Tinvmass_alambda[j]<<endl;
			//if (mass_pi_p<1.116) continue;
			//mass_lambda=mass_pi_p;
			//mass_ee=Tinvmass_ee[j];
			//if (Tinvmass_ee[j]<0.05) continue;
			Int_t 		take1=1,
					take2=1;
		/*	for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == V0trk1_id[j])
				{
					take1=Trk_prim_vtx[n];
					continue;
				}
                		if (idx == V0trk2_id[j])
				{
					take2=Trk_prim_vtx[n];
					continue;
				}
        		}
		*/
       			//if ((take1==1)||(take2==1)) continue;
			list_k0[cand_k0]=j;
			cand_k0++;
		} //end k0 selection


		if (cand_k0!=Nv0psy) cout<<"ERRRRRRROOOOOOOOOOOOORRRRRRRRR!!!!!!!!"<<endl;
		if (cand_k0<1) continue;
		nv0=cand_k0;
		if (nv0>60) cout<<nv0<<endl;
		Int_t id=0;
	//---- Tree filling -----//
		for(Int_t k=0;k<nv0;k++)
		{
			id=list_k0[k];

			coll2[k]=V0coll2d[id];
			coll3[k]=V0coll3d[id];

			Int_t 	t1_prim=1,
				t2_prim=1,
				t1_sec=0,
				t2_sec=0,
				t1_vertex_id=-1,
				t2_vertex_id=-1;
			id1[k]=T1_id[id];
			id2[k]=T2_id[id];
			p1[k][0]=P1[id][0];
			p1[k][1]=P1[id][1];
			p1[k][2]=P1[id][2];

			p2[k][0]=P2[id][0];
			p2[k][1]=P2[id][1];
			p2[k][2]=P2[id][2];


			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == id1[k])
				{
					t1_prim=Trk_prim_vtx[n];
					t1_sec=Trk_sec_vtx[n];
					t1_vertex_id=Trk_vtx[n];
					continue;
				}
                		if (idx == id2[k])
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

			Daughter temp1(p1[k][0],p1[k][1],p1[k][2]);
			Daughter temp2(p2[k][0],p2[k][1],p2[k][2]);
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
			//mass_ee[k]=Tinvmass_ee[id];
			layout1[k]=Tt1_layout[id];
			layout2[k]=Tt2_layout[id];

		}

		runnr=Runnr;

		q2el=Siq2el[0];
		yel=Siyel[0];
		yjb=Siyjb[0];
		sincand=Sincand;
		if (Sincand>0) siprob=Siprob[0];
		if (Sincand==0) siprob=0;
		box_x=x_srtd;
		box_y=y_srtd;
		e_pz=EminPz_Evt;
		xvtx=Xvtx;
		yvtx=Yvtx;
		zvtx=Zvtx;

		tree->Fill();


	}


	tree->Print();
	// CHOOSE ROOT TREE NAME (out)
	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/MC_HERAI_DJ_ARI/1.root","recreate");
	tree->Write();
	f2->Close();
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

