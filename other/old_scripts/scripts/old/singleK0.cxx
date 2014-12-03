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
void singleK0()
{
	Float_t		bin_width=1.5;
	Int_t		goa=0,
			nevents=0,
			Nv0lite=0,
			Sincand=0,
			Tt1_id[50],
			Tt2_id[50],
			Tq1[50],
			Tq2[50],
			Trk_ntracks=0,
			Trk_id[300],
			Runnr=0;
	Float_t		Tinvmass_k0[50],
			Tinvmass_lambda[50],
			Tinvmass_alambda[50],
			Tinvmass_ee[50],
			Tsecvtx_collin3[50],
			Tsecvtx_collin2[50],
			Tsecvtx[50][3],
			Siq2el[10],
			Siyel[10],
			Siyjb[10],
			reso_mass=0,
			Tp1[50][3],
			Tp2[50][3],
			Tpk[50][3];
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300],
			Trk_type[300],
			Tt1_layinn[50],
			Tt1_layout[50];


	Float_t		//reso_mass=0,
			//Siq2el[10],
			//Siyel[10],
			//Siyjb[10],
			Sizuhmom[4][10],
			Sicalpos[3][10],
			Sisrtpos[2][10],
			Sisrtene[10],
			Siecorr[3][10],
			Sith[10];


	TChain *myChain=new TChain("resonance");
	//TChain *myChain=new TChain("tr");

	//myChain->Add("/data/zenith226a/libov/data/2005RTfit/*.root");
	//myChain->Add("/data/zenith220a/aushev/nt_07pRP/rp07*");
	//myChain->Add("/data/zenith226a/libov/data/2006/*.root");
	//myChain->Add("/data/zenith226a/libov/data/HERAII_oncemore/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2006p_oncemore/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2006pRTfit/*.root");
	myChain->Add("/data/zenith226a/libov/data/2007RTfit/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2007/*.root");

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
	myChain->SetBranchAddress("Tt1_layinn",Tt1_layinn);
	myChain->SetBranchAddress("Tt1_layout",Tt1_layout);
	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_type",Trk_type);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	//Sira, Si_kin, ...
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

	Float_t		histRangeLow=450,
			histRangeUp=542,
			histRange=histRangeUp-histRangeLow;
	Int_t 		nbins=(Int_t)histRange/bin_width;
	bin_width=(Float_t)histRange/nbins;
	cout<<bin_width<<" "<<nbins<<endl;


	TH1F *hinv_base=new TH1F("hinv_base","k0s invariant mass (1.5 MeV/bin)",nbins,histRangeLow,histRangeUp);
	TH1F *hyel=new TH1F("hyel","Yel",100,-0.5,1.5);
	TH1F *hyjb=new TH1F("hyjb","Yjb",100,-0.5,1.5);
	TH1F *h1=new TH1F("h1","485 -> 510.4",150,0.8,5);
	TH1F *h2=new TH1F("h2","485 -> 510.4",150,0.8,5);
	TH1F *hdebug=new TH1F("hdebug","",20,0,20);
	TH1F *hdebug1=new TH1F("hdebug1","",20,0,20);
	TH1F *hdebug2=new TH1F("hdebug2","",20,0,20);
	TH1F *ha=new TH1F("ha","angle between two K0s ",100,0,180);
	TH1F *hfake=new TH1F("hfake","",150,0.8,5);
	TH1F *hinv1=new TH1F("hinv1","K0s",60,450,552);

	TH1F *hlayinn=new TH1F("hlayinn","Inner superlayer",20,0,20);
	TH1F *hlayout=new TH1F("hlayout","Outer superlayer",20,0,20);
	TH1F *hdif=new TH1F("hdif","Outer-Inner",20,0,20);


	//gStyle->SetOptFit(1111);

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);

		// DIS event selection


		hdebug->Fill(1);
		if (Siq2el[0]<1) continue;
		hdebug->Fill(2);
			// E-pz calculation
			float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   			float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   			float EminPz_Evt  = Empz_e + Empz_had;
		if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;
		hdebug->Fill(3);

		float x_srtd=Sicalpos[0][0];
   		float y_srtd=Sicalpos[0][1];
   		if (Sisrtene[0]>0)
		{
      			x_srtd=Sisrtpos[0][0];
      			y_srtd=Sisrtpos[0][1];
    		}
		if (TMath::Abs(x_srtd)<12)
		{
			if (TMath::Abs(y_srtd)<6) continue;
		}
		hdebug->Fill(4);
		if (Siyel[0]>0.95) continue;
		hdebug->Fill(5);
		if (Siyjb[0]<0.01) continue;
		hdebug->Fill(6);
		Int_t	cand_k0=0,
			list_k0[30];

		for(Int_t j=0;j<Nv0lite;j++)
		{

			hlayinn->Fill(Tt1_layinn[j]);
			hlayout->Fill(Tt1_layout[j]);
			hdif->Fill(Tt1_layout[j]-Tt1_layinn[j]);
			hdebug1->Fill(1);
			Daughter 	t1(Tp1[j][0],Tp1[j][1],Tp1[j][2]);
			Daughter 	t2(Tp2[j][0],Tp2[j][1],Tp2[j][2]);
			Mother		K0s_cand(t1,t2);

			Float_t 	p1=t1.GetP();
			Float_t 	p2=t2.GetP();
			Float_t 	mass_pi_p=0;

			if (p1>p2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (p1<p2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}

			//h2d->Fill(1000*Tinvmass_k0[j],1000*mass_pi_p);
			hdebug1->Fill(2);
			if (Tsecvtx_collin2[j]>0.1) continue;
			hdebug1->Fill(3);
			if (mass_pi_p<1.125) continue;
			hdebug1->Fill(4);
			if (Tinvmass_ee[j]<0.05) continue;
			hdebug1->Fill(5);
			if ((K0s_cand.GetPt_m())<0.3) continue;
			hdebug1->Fill(6);
			bool itake=true;
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
			hdebug1->Fill(7);
			//if (Tsecvtx_collin3[j]>0.2) continue;
			hdebug1->Fill(8);
			if (TMath::Abs(K0s_cand.GetEta_m())>1.75) continue;
			hdebug1->Fill(9);
			list_k0[cand_k0]=j;
			cand_k0++;


		}

		if(cand_k0<2) continue;
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t K0_id=list_k0[k];
			Daughter 	t1(Tp1[K0_id][0],Tp1[K0_id][1],Tp1[K0_id][2]);
			Daughter 	t2(Tp2[K0_id][0],Tp2[K0_id][1],Tp2[K0_id][2]);
			Mother		K0s_cand(t1,t2);
			hinv_base->Fill((K0s_cand.GetMass_m(4,4))*1000);
		}

	}



	//TFile *f1 =new TFile("/data/zenith226a/libov/results/mostrecent/K0s_2006.root","recreate");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/recent/K0s_2007aushev.root","recreate");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/mostrecent/K0s_2006pnoRTfit.root","recreate");
	TFile *f1 =new TFile("/data/zenith226a/libov/results/mostrecent/K0s_2007RTfit.root","recreate");
	//h1->Write();
	hinv_base->Write();
	//hinv1->Write();
	hdebug->Write();
	hdebug1->Write();
	hdebug2->Write();
	//ha->Write();
	hlayinn->Write();
	hlayout->Write();
	hdif->Write();
	f1->Close();
	cout<<"OK"<<endl;

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	singleK0();
	return 0;
}
#endif
