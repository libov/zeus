// macro runs through all ntuples and create a small tree easy to analyse.
// variables are described below, "VARIABLES DEFINITION"
// type path to ntuples and name of out root tree
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

void doubleK0_HERAII()
{
	Int_t		goa=0,
			nevents=0,
			Nv0lite=0,
			Sincand=0,
			Tt1_id[50],
			Tt2_id[50],
			Tq1[50],
			Tq2[50],
			Trk_ntracks=0,
			Trk_id[300];
	Float_t		Tinvmass_k0[50],
			Tinvmass_lambda[50],
			Tinvmass_alambda[50],
			Tinvmass_ee[50],
			Tsecvtx_collin3[50],
			Tsecvtx_collin2[50],
			Tsecvtx[50][3],
			reso_mass=0,
			Tp1[50][3],
			Tp2[50][3],
			Tpk[50][3],
			corr=0,
			Siq2el[10],
			Siyel[10],
			Siyjb[10],
			Sizuhmom[4][10],
			Sicalpos[3][10],
			Sisrtpos[2][10],
			Sisrtene[10],
			Siecorr[3][10],
			Sith[10];
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300],
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


	TChain *myChain=new TChain("resonance");
	// PATH to NTUPLES
	//myChain->Add("/data/zenith226a/libov/data/2004RTfit/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2005RTfit/*.root");
	myChain->Add("/data/zenith226a/libov/data/2004RTfit/*.root");
	myChain->Add("/data/zenith226a/libov/data/HERAII_oncemore/*.root");  // No rtfit; 2007a orange(not test003); only 2005 yet.
	myChain->Add("/data/zenith226a/libov/data/2006/*.root");
	myChain->Add("/data/zenith226a/libov/data/2006pRTfit/*.root");
	myChain->Add("/data/zenith226a/libov/data/2007/*.root");


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
	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
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
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;


	//gStyle->SetOptFit(1111);

	Float_t		histRangeLow=450,
			histRangeUp=542,
			histRange=histRangeUp-histRangeLow,
			bin_width=1.5;
	Int_t 		nbins=(Int_t)histRange/bin_width;
	bin_width=(Float_t)histRange/nbins;
	cout<<bin_width<<" "<<nbins<<endl;
	TH1F *hinv_base=new TH1F("hinv_base",">=2 K0s",nbins,histRangeLow,histRangeUp);
	TH1F *h=new TH1F("h","K0sK0s",300,0.8,5);
	TH1F *hdebug=new TH1F("hdebug","",20,0,20);
	// TREE VARIABLES DEFINITION
	// these variables are written to tree once and are further analysed in order to save time
	Int_t		nv0=0,		// number K0s candidates that passed soft selection
			id1[10],	// id of the first track
			id2[10],	// id of the second track
			runnr=0;	// number of run
	Float_t		p1[10][3],	// momenta of 1st track
			p2[10][3],	// momenta of 2bd track
			coll2[10],	// collinearity angle 2D
			coll3[10];	// collinearity angle 3D
	TTree *tree = new TTree("resonance","K0sK0s in DIS");
	tree->Branch("nv0",&nv0,"nv0/I");
	tree->Branch("p1",p1,"p1[nv0][3]/F");
	tree->Branch("p2",p2,"p2[nv0][3]/F");
	tree->Branch("coll2",coll2,"coll2[nv0]/F");
	tree->Branch("coll3",coll3,"coll3[nv0]/F");
	tree->Branch("id1",id1,"id1[nv0]/I");
	tree->Branch("id2",id2,"id2[nv0]/I");
	tree->Branch("runnr",&runnr,"runnr/I");



	Int_t err=0;

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		/*//////////////////////////////////////////////////
		year=0;
		if  ((Runnr>=low_2004)&&(Runnr<=up_2004)) year=2004;
		if  ((Runnr>=low_2005)&&(Runnr<=up_2005)) year=2005;
		if  ((Runnr>=low_2006)&&(Runnr<=up_2006)) year=2006;
		if  ((Runnr>=low_2006p)&&(Runnr<=up_2006p)) year=2006;
		if  ((Runnr>=low_2007)&&(Runnr<=up_2007)) year=2007;

		switch (year)
		{
			case 2004: corr=corr_2004; break;
			case 2005: corr=corr_2005; break;
			case 2006: corr=corr_2006; break;
			case 2007: corr=corr_2007; break;
			case 0: {corr=1; err++;} break;\begin{itemize}
		}
		*////////////////////////////////////////////////////


	//------DIS event selection------//
		hdebug->Fill(1);
		if (Siq2el[0]<1) continue;						// Q^2>1 GeV^2
		hdebug->Fill(2);
		// E-pz calculation
		float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   		float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   		float EminPz_Evt  = Empz_e + Empz_had;
		if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;				// 38 < E-pz < 60 GeV
		hdebug->Fill(3);
		// electron position calculation (box cut)
		float x_srtd=Sicalpos[0][0];						// position of electron in calorimeter
   		float y_srtd=Sicalpos[0][1];
   		if (Sisrtene[0]>0)
		{
      			x_srtd=Sisrtpos[0][0];						// position of electron in SRDT
      			y_srtd=Sisrtpos[0][1];
    		}
		if (TMath::Abs(x_srtd)<12)						// box cut: electron required to be outside 12x6 cm^2 box
		{
			if (TMath::Abs(y_srtd)<6) continue;
		}
		hdebug->Fill(4);
		if (Siyel[0]>0.95) continue;						// y from electron method < 0.95
		hdebug->Fill(5);
		if (Siyjb[0]<0.01) continue;						// y from Jacquet-Blondel method > 0.01
		hdebug->Fill(6);


	//------K0s selection------//
		Int_t	cand_k0=0,
			list_k0[30];
		if (Nv0lite<=1) continue;
		for(Int_t j=0;j<Nv0lite;j++)
		{
			Daughter t1(Tp1[j][0],Tp1[j][1],Tp1[j][2]);
			Daughter t2(Tp2[j][0],Tp2[j][1],Tp2[j][2]);

			Mother K0s_cand(t1,t2);

			Float_t p1=t1.GetP();
			Float_t p2=t2.GetP();
			Float_t mass_pi_p=0;

			if (p1>p2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (p1<p2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}
			//if (Tsecvtx_collin2[j]>0.1) continue;
			if (mass_pi_p<1.116) continue;
			if (Tinvmass_ee[j]<0.05) continue;
			//if ((K0s_cand.GetPt_m())<0.3) continue;
			Int_t 		take1=1,
					take2=1;
			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == Tt1_id[j])
				{
					take1=Trk_prim_vtx[n];
					continue;
				}
                		if (idx == Tt2_id[j])
				{
					take2=Trk_prim_vtx[n];
					continue;
				}
        		}
       			if ((take1==1)||(take2==1)) continue;
			//if (Tsecvtx_collin3[j]>0.2) continue;
			//if (TMath::Abs(K0s_cand.GetEta_m())>2.25) continue;
			//if ((K0s_cand.GetMass_m(4,4)<0.45)||(K0s_cand.GetMass_m(4,4)>0.9504)) continue;
			list_k0[cand_k0]=j;
			cand_k0++;
		} //end k0 selection
		if (cand_k0<2) continue;
		nv0=cand_k0;
		Int_t id=0;
		for(Int_t k=0;k<cand_k0;k++)
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
		}
		runnr=Runnr;
		tree->Fill();
	/*
	//------K0s combining------//
		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{
				Int_t 		k01=list_k0[k],
						k02=list_k0[l];
				Int_t 		id1=Tt1_id[k01],
						id2=Tt2_id[k01],
						id3=Tt1_id[k02],
						id4=Tt2_id[k02];
				if ((id1==id3)||(id1==id4)||(id2==id3)||(id2==id4)) continue;
				Daughter K0s_cand1(corr*Tpk[k01][0],corr*Tpk[k01][1],corr*Tpk[k01][2]);
				Daughter K0s_cand2(corr*Tpk[k02][0],corr*Tpk[k02][1],corr*Tpk[k02][2]);
				Mother K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);
				h2->Fill(reso_mass);
			}
		}
	*/
	}


	tree->Print();
	// CHOOSE OUT ROOT TREE NAME
	TFile *f2 =new TFile("/data/zenith226a/libov/results/mostrecent/HERAII_all_05oncemore.root","recreate");
	tree->Write();
	f2->Close();

	cout<<"Yo!"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	doubleK0_HERAII();
	return 0;
}
#endif

