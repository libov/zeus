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
void doubleK0_HERAI_fdr()
{
	Int_t		goa=0,
			nevents=0,
			Sincand=0,
			T1_vctrhl[20],
			T2_vctrhl[20],
			Tq1[50],
			Tq2[50],
			Trk_ntracks=0,
			Trk_id[300];

	Float_t		reso_mass=0,
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
			<TFile.h>
#include <TROOT.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif
void doubleK0_HERAI_fdr()
{
	Int_t		goa=0,
			nevents=0,
			Sincand=0,
			T1_vctrhl[20],
			T2_vctrhl[20],
			Tq1[50],
			Tq2[50],
			Trk_ntracks=0,
			Trk_id[300];

	Float_t		reso_mass=0,
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
	myChain->Add("/data/zenith226a/libov/data/old/HERAIv2007a_fdr/*.root");

	// myv0
	Int_t		Nv0=0,
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
               k0_cand=0;



	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/data/old/HERAIv2007a_fdr/*.root");

	// myv0
	Int_t		Nv0=0,
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
                 	V0colang[40];

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
	// histograms
	TH1F *hinv_base=new TH1F("hinv_base",">=2 K0s",nbins,histRangeLow,histRangeUp);
	TH1F *h1=new TH1F("h1","K0sK0s in DIS",200,0.8,5);
	TH1F *h2=new TH1F("h2","K0sK0s in DIS",280,0.8,5);
	TH1F *h3=new TH1F("h3","K0sK0s in DIS",150,0.8,5);
	TH1F *hdebug=new TH1F("hdebug","",20,0,20);
	TH1F *hdebug1=new TH1F("hdebug1","",20,0,20);
	TH1F *hdebug2=new TH1F("hdebug2","",20,0,20);
	TH1F *hcount=new TH1F("hcount","",20,0,20);
	TH1F *ha=new TH1F("ha","angle between two K0s ",100,0,180);
	TH1F *hfake=new TH1F("hfake","",150,0.8,5);
	TH1F *hinv1=new TH1F("hinv1","K0s",60,450,552);
	TH1F *hdelta=new TH1F("hdelta","relative difference of pion squared momenta",50,0,2);
	TH1F *hdelta1=new TH1F("hdelta1","difference of K0s pt",50,0,5);

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

		// K0s selecting
		if (Nv0<=1) continue;  // at least two V0s required
		hdebug->Fill(7);
		for(Int_t j=0;j<Nv0;j++)
		{
			hdebug1->Fill(1);
			if (Mpropi[j]<1.125) continue;
			hdebug1->Fill(2);
			if (Mee[j]<0.05) continue;
			hdebug1->Fill(3);
			if (sqrt(V0p3[j][0]*V0p3[j][0]+V0p3[j][1]*V0p3[j][1])<0.3) continue;
			hdebug1->Fill(4);
			Int_t 		take1=1,
					take2=1;
			for (Int_t n=0; n<Trk_ntracks; n++)
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
       			if ((take1==1)||(take2==1)) continue;
			hdebug1->Fill(5);
			if (TMath::Abs(V0eta[j])>1.5) continue;
			hdebug1->Fill(6);

			if (V0colang[j]>0.3) continue;
			hdebug1->Fill(7);
			hinv1->Fill(1000*Mpipi[j]);
			//if ((Mpipi[j]<0.47)||(Mpipi[j]>0.526)) continue;
			//if ((Mpipi[j]<0.4777)||(Mpipi[j]>0.5177)) continue;
			if ((Mpipi[j]<0.481)||(Mpipi[j]>0.515)) continue;
			hdebug1->Fill(8);
			list_k0[cand_k0]=j;
			cand_k0++;

		} //end k0 selecting
		if(cand_k0<2) continue;
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t 	id=list_k0[k];
			hinv_base->Fill(1000*Mpipi[id]);
		}
		//K0s combining
		Int_t count=0;
		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{
				Int_t 		k01=list_k0[k],
						k02=list_k0[l];
				Int_t 		id1=V0trk1_id[k01],
						id2=V0trk2_id[k01],
						id3=V0trk1_id[k02],
						id4=V0trk2_id[k02];
				hdebug2->Fill(1);
				if ((id1==id3)||(id1==id4)||(id2==id3)||(id2==id4)) continue;
				hdebug2->Fill(2);
				Daughter K0s_cand1(V0p3[k01][0],V0p3[k01][1],V0p3[k01][2]);
				Daughter K0s_cand2(V0p3[k02][0],V0p3[k02][1],V0p3[k02][2]);
				Mother K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);
				count++;
				Float_t		px1=V0p3[k01][0],
						py1=V0p3[k01][1],
						pz1=V0p3[k01][2],

						px2=V0p3[k02][0],
						py2=V0p3[k02][1],
						pz2=V0p3[k02][2];


				Double_t cos_angle=(px1*px2+py1*py2+pz1*pz2)/(sqrt((px1*px1+py1*py1+pz1*pz1)*(px2*px2+py2*py2+pz2*pz2)));
				Double_t angle=acos(cos_angle);
				ha->Fill(angle*57);
				//if (cos_angle>0.98)
				//{
				//	hfake->Fill(reso_mass);
				//	continue;
				//}
				hdebug2->Fill(3);
				Double_t 	pt_K1=0,   //1st K0s mom proj onto K0sK0s flight direction
						pt_K2=0,   // smae for 2nd K0s
						p_K1=0,
						p_K2=0,
						p_f=0,
						scal_fact=0;

				p_K1=K0s_cand1.GetP();
				p_K2=K0s_cand2.GetP();
				p_f=K0sK0s.GetP_m();
				scal_fact=K0s_cand1.GetPx()*K0sK0s.GetPx_m()+K0s_cand1.GetPy()*K0sK0s.GetPy_m()+K0s_cand1.GetPy()*K0sK0s.GetPy_m();

				pt_K1=p_K1*sqrt(1-scal_fact*scal_fact/(p_f*p_f*p_K1*p_K1));
scal_fact=K0s_cand2.GetPx()*K0sK0s.GetPx_m()+K0s_cand2.GetPy()*K0sK0s.GetPy_m()+K0s_cand2.GetPy()*K0sK0s.GetPy_m();
				pt_K2=p_K2*sqrt(1-scal_fact*scal_fact/(p_f*p_f*p_K2*p_K2));
				//hdelta1->Fill(TMath::Abs(pt_K1-pt_K2));
				//if ((K0sK0s.GetEta_m()<(-1.5))||(K0sK0s.GetEta_m()>1.5)) continue;
				//if (K0sK0s.GetEta_m()>(-1)) continue;
				//if (K0sK0s.GetP_m()<0.5) continue;
				hdelta1->Fill(TMath::Abs(pt_K1-pt_K2));
				//if ((pt_K1-pt_K2)>1) continue;

				Double_t	beta=0,
						gamma=0,
						delta=0,
						delta_max=0,
						p2=0,
						pK0s_cms=0,
						a1,a2,a3,
						mK0sK0s;
				p2=K0sK0s.GetP_m()*K0sK0s.GetP_m();
				delta=TMath::Abs(K0s_cand1.GetP()*K0s_cand1.GetP()-K0s_cand2.GetP()*K0s_cand2.GetP());

				mK0sK0s=1.71;
				beta=sqrt(p2/(mK0sK0s*mK0sK0s+p2));
				gamma=1/sqrt(1-beta*beta);
				pK0s_cms=sqrt(mK0sK0s*mK0sK0s/4-0.497*0.497);
				delta_max=2*mK0sK0s*pK0s_cms*gamma*gamma*beta;
				a1=delta_max;
				hdelta->Fill(delta/delta_max);
				//if ((delta/delta_max)>1.0) continue;
				//if ((K0sK0s.GetEta_m()<(-1.5))||(K0sK0s.GetEta_m()>1.5)) continue;
				//if (K0sK0s.GetEta_m()>(-1)) continue;

				//if (K0sK0s.GetP_m()<0.5) continue;

				h1->Fill(reso_mass);
				h2->Fill(reso_mass);
				h3->Fill(reso_mass);

			}
		}
		hcount->Fill(count);
	}

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0K0_HERAI.root","recreate");
	h1->Write();
	h2->Write();
	h3->Write();
	hinv_base->Write();
	hinv1->Write();
	hdebug->Write();
	hdebug1->Write();
	hdebug2->Write();
	hcount->Write();
	ha->Write();

	hdelta->Write();
	hdelta1->Write();

	f1->Close();
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	doubleK0_HERAI_fdr();
	return 0;
}
#endif

