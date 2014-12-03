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
void doubleK0_HERAI()
{
	Int_t		goa=0,
			nevents=0,
			Nv0=0,
			Sincand=0,
			T1_vctrhl[20],
			T2_vctrhl[20],
			Tq1[50],
			Tq2[50],
			Trk_ntracks=0,
			Trk_id[300];

	Float_t		Invmass_k0[20],
			Invmass_lambda[20],
			Invmass_alambda[20],
			Invmass_ee[20],
			Tsecvtx_collin3=0,
			Tsecvtx_collin2=0,
			Tsecvtx[50][3],
			reso_mass=0,
			P1_x[20],
			P1_y[20],
			P1_z[20],
			P2_x[20],
			P2_y[20],
			P2_z[20],
			Secvtx_x[20],
			Secvtx_y[20],
			Secvtx_z[20],
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



	TChain *myChain=new TChain("resonance");
	//myChain->Add("/data/zenith226a/libov/data/96_99/*.root");
	myChain->Add("/data/zenith226a/libov/data/HERAIv2007a/*.root");

	// V0
	myChain->SetBranchAddress("Nv0",&Nv0);
	myChain->SetBranchAddress("Invmass_k0",Invmass_k0);
	myChain->SetBranchAddress("Invmass_lambda",Invmass_lambda);
	myChain->SetBranchAddress("Invmass_alambda",Invmass_alambda);
	myChain->SetBranchAddress("Invmass_ee",Invmass_ee);
	myChain->SetBranchAddress("P1_x",P1_x);
	myChain->SetBranchAddress("P1_y",P1_y);
	myChain->SetBranchAddress("P1_z",P1_z);
	myChain->SetBranchAddress("P2_x",P2_x);
	myChain->SetBranchAddress("P2_y",P2_y);
	myChain->SetBranchAddress("P2_z",P2_z);
	myChain->SetBranchAddress("T1_vctrhl",T1_vctrhl);
	myChain->SetBranchAddress("T2_vctrhl",T2_vctrhl);
	myChain->SetBranchAddress("Secvtx_x",Secvtx_x);
	myChain->SetBranchAddress("Secvtx_y",Secvtx_y);
	myChain->SetBranchAddress("Secvtx_z",Secvtx_z);
	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
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


	//gStyle->SetOptFit(1111);

	Float_t		histRangeLow=450,
			histRangeUp=542,
			histRange=histRangeUp-histRangeLow,
			bin_width=1.5;
	Int_t 		nbins=(Int_t)histRange/bin_width;
	bin_width=(Float_t)histRange/nbins;
	cout<<bin_width<<" "<<nbins<<endl;

	TH1F *hinv_base=new TH1F("hinv_base",">=2 K0s",nbins,histRangeLow,histRangeUp);
	TH1F *h1=new TH1F("h1","470 -> 525.4",150,0.8,5);
	TH1F *h2=new TH1F("h2","480 -> 515.4",150,0.8,5);
	TH1F *hdebug=new TH1F("hdebug","",20,0,20);
	TH1F *hdebug1=new TH1F("hdebug1","",20,0,20);
	TH1F *hdebug2=new TH1F("hdebug2","",20,0,20);

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		Int_t	cand_k0=0,
			list_k0[30];

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

		// K0s selectingtechno party
		if (Nv0<=1) continue;  // at least two V0s required
		hdebug->Fill(7);
		for(Int_t j=0;j<Nv0;j++)
		{
			hdebug1->Fill(1);
			Daughter t1(P1_x[j],P1_y[j],P1_z[j]);
			Daughter t2(P2_x[j],P2_y[j],P2_z[j]);
			Mother K0s_cand(t1,t2);
			Float_t p1=t1.GetP();
			Float_t p2=t2.GetP();
			Float_t mass_pi_p=0;

			//cout<<p1<<" "<<p2<<" "<<K0s_cand.GetPx_m()<<" ";
			if (p1>p2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (p1<p2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}
			//cout<<mass_pi_p<<endl;
			if (mass_pi_p<1.120) continue;
			hdebug1->Fill(2);
			if (Invmass_ee[j]<0.05) continue;
			hdebug1->Fill(3);
			if ((K0s_cand.GetPt_m())<0.15) continue;
			hdebug1->Fill(4);
			Int_t 		take1=1,
					take2=1;
			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == T1_vctrhl[j])
				{
					take1=Trk_prim_vtx[n];
					continue;
				}
                		if (idx == T2_vctrhl[j])
				{
					take2=Trk_prim_vtx[n];
					continue;
				}
        		}
       			if ((take1==1)||(take2==1)) continue;
			hdebug1->Fill(5);
			if (TMath::Abs(K0s_cand.GetEta_m())>2) continue;
			hdebug1->Fill(6);
			Float_t 	px=K0s_cand.GetPx_m(),
					py=K0s_cand.GetPy_m(),
					pz=K0s_cand.GetPz_m(),
					p=K0s_cand.GetP_m(),
					x=Secvtx_x[j],
					y=Secvtx_y[j],
					z=Secvtx_z[j],
					r=sqrt(x*x+y*y+z*z);

			Tsecvtx_collin3=acos((x*px+y*py+z*pz)/(p*r));
			Tsecvtx_collin2=acos((x*px+y*py)/sqrt((x*x+y*y)*(px*px+py*py)));
			//if (Tsecvtx_collin2>0.1) continue;
			//hdebug1->Fill(7);
			//if (Tsecvtx_collin3>0.2) continue;
			//hdebug1->Fill(8);
			//if ((K0s_cand.GetMass_m(4,4)<0.48)||(K0s_cand.GetMass_m(4,4)>0.5154)) continue;
			hdebug1->Fill(9);
			list_k0[cand_k0]=j;
			cand_k0++;

		} //end k0 selecting

		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t 	id=list_k0[k];
			Daughter tt1(P1_x[id],P1_y[id],P1_z[id]);
			Daughter tt2(P2_x[id],P2_y[id],P2_z[id]);
			Mother K0s(tt1,tt2);
			hinv_base->Fill(1000*K0s.GetMass_m(4,4));
		}
		//K0s combining
		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{
				Int_t 		k01=list_k0[k],
						k02=list_k0[l];
				Int_t 		id1=T1_vctrhl[k01],
						id2=T2_vctrhl[k01],
						id3=T1_vctrhl[k02],
						id4=T2_vctrhl[k02];
				hdebug2->Fill(1);
				if ((id1==id3)||(id1==id4)||(id2==id3)||(id2==id4)) continue;
				hdebug2->Fill(2);
				Daughter K0s_cand1(P1_x[k01]+P2_x[k01],P1_y[k01]+P2_y[k01],P1_z[k01]+P2_z[k01]);
				Daughter K0s_cand2(P1_x[k02]+P2_x[k02],P1_y[k02]+P2_y[k02],P1_z[k02]+P2_z[k01]);
				Mother K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);
				//cout<<reso_mass<<endl;
				h1->Fill(reso_mass);
			}
		}
	}

	TFile *f1 =new TFile("/data/zenith226a/libov/results/recent/K0sK0sHERAIv2007a_1.root","recreate");
	h1->Write();
	hinv_base->Write();
	hdebug->Write();
	hdebug1->Write();
	hdebug2->Write();
	f1->Close();
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	doubleK0_HERAI();
	return 0;
}
#endif

