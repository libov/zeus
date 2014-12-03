//////////////////////////////////////////////////
//////////////  K0s    analysis  /////////////////
///////////// with tracking block ////////////////
//////////////////////////////////////////////////
//
//
//
//
// Libov Vladyslav
// Kiev National University
// November 2007
//
//
#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TVector3.h>
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
			Trk_id[300];
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
	Int_t		Nk0s=0,
			Nk0s_ctd=0,
			Nlambda=0;

	Float_t		P1[20][3],
			P2[20][3];

	Float_t		Trk_px[300],
			Trk_py[300],
			Trk_pz[300],
			Trk_charge[300];

	Int_t		Trk_nvert,
			Vtx_id[120],
			Vtx_prim[120];
	Float_t		Vtx_x[120],
			Vtx_y[120],
			Vtx_z[120];
	Float_t		V0_x,
			V0_y,
			V0_z;
	Float_t		X0,Y0,Z0;
	Int_t		Trk_layinner[300],
			Trk_layouter[300];

	Float_t		Prim_vtx[3],
			Sec_vtx[20][3];

	Float_t		Pk0s[20][3];
	Int_t		MC=0;
	Float_t		Xvtx=0,
			Yvtx=0,
			Zvtx=0;

	TChain *myChain=new TChain("resonance");



	MC=1;
	/*myChain->Add("/data/zenith226a/libov/data/MC_1.root");
	myChain->Add("/data/zenith226a/libov/data/MC_2.root");
	myChain->Add("/data/zenith226a/libov/data/MC_3.root");
	myChain->Add("/data/zenith226a/libov/data/MC_4.root");
	myChain->Add("/data/zenith226a/libov/data/MC_5.root");
	myChain->Add("/data/zenith226a/libov/data/MC_6.root");
	myChain->Add("/data/zenith226a/libov/data/MC_7.root");*/

	//myChain->Add("/data/zenith226a/libov/data/MCfinW/test004/*.root");
	//myChain->Add("/data/zenith226a/libov/data/MCfinW/test/my_mc_test.root");
	myChain->Add("/data/zenith226a/libov/data/MCfinW/test/mc_test.root");

	///myChain->Add("/data/zenith226a/libov/data/07pRP_no2K0s_restr/*.root");

	/*myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_0.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_1.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_2.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_3.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_4.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_5.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_6.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_7.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_8.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_9.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_10.root");*/

	/*
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_0.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_1.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_2.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_3.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_4.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_5.root");
	*/


	myChain->SetBranchAddress("Runnr",&Runnr);
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

	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	myChain->SetBranchAddress("Trk_vtx",Trk_vtx);
	myChain->SetBranchAddress("Trk_px",Trk_px);
	myChain->SetBranchAddress("Trk_py",Trk_py);
	myChain->SetBranchAddress("Trk_pz",Trk_pz);
	myChain->SetBranchAddress("Trk_charge",Trk_charge);
	myChain->SetBranchAddress("Trk_layouter",Trk_layouter);
	myChain->SetBranchAddress("Trk_layinner",Trk_layinner);

	//Trk_vert
	myChain->SetBranchAddress("Trk_nvert",&Trk_nvert);
	myChain->SetBranchAddress("Vtx_id",Vtx_id);
	myChain->SetBranchAddress("Vtx_prim",Vtx_prim);
	myChain->SetBranchAddress("Vtx_x",Vtx_x);
	myChain->SetBranchAddress("Vtx_y",Vtx_y);
	myChain->SetBranchAddress("Vtx_z",Vtx_z);
	//Vertex
	myChain->SetBranchAddress("Xvtx",&Xvtx);
	myChain->SetBranchAddress("Yvtx",&Yvtx);
	myChain->SetBranchAddress("Zvtx",&Zvtx);

	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	TH1F *hdebug_dis=new TH1F("hdebug_dis","",10,0,10);
	TH1F *hdebug_k0=new TH1F("hdebug_k0","",10,0,10);

	TH1F *hinv_K0s=new TH1F("hinv_K0s","K^{0}_{s} inv mass",60,450,552);
	TH1F *hinv_Lambda=new TH1F("hinv_Lambda","Lambda inv mass",100,1050,1300);
	TH2F *hAP=new TH2F("hAP","Armenteros-Podolanski",100,-1,1,100,0,0.3);
	TH1F *hcoll2=new TH1F("hcoll2","collinearity 2d",100,0,3);
	TH1F *hcoll3=new TH1F("hcoll3","collinearity 3d",100,0,3);

	TH2F *hprim=new TH2F("hprim","XY of primary vertex reco",400,-1,2,400,-1,0.4);
	TH2F *hsec1=new TH2F("hsec1","",500,-40,40,500,-40,40);
	TH2F *hsec2=new TH2F("hsec2","",500,-40,40,500,-40,40);
	TH1F *hzvert=new TH1F("hzvert","Z of prim vert",100,-50,50);

	TH2F *hdalitz=new TH2F("hdalitz","",400,200,800,400,1050,1400);

	TH1F *hinner=new TH1F("hinner","inner layer",10,0,10);
	TH1F *houter=new TH1F("houter","outer layer",10,0,10);

	TH1F *hdlen=new TH1F("hdlen","reco decay length(lab)",100,0,20);
	TH1F *hctau=new TH1F("hctau","reco decay length(rest)",100,0,20);

	TH1F *h=new TH1F("h","K0sK0s in DIS",200,1.6,1.8);
	TH1F *h1=new TH1F("h1","K0sK0s in DIS",280,1.6,1.8);
	TH1F *h2=new TH1F("h2","K0sK0s in DIS",150,1.6,1.8);

	Int_t 		err=0;
	Int_t		tot_l=0,
			tot_k=0,
			tot_k_branch=0,
			tot_k_new=0,
			tot_l_new=0;
	Int_t 		mat=0;
	Int_t		wrong_vtx=0;
	Int_t		no_vtx=0;
	Int_t		ev_pass_DIS=0;

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;

		Int_t		cand_k0=0;
		Float_t		p[130][3];

		myChain->GetEntry(i);

		//------DIS event selection------//

		hdebug_dis->Fill(0);
		//if (Sincand<1) continue;
		hdebug_dis->Fill(1);
		//if (Siq2el[0]<1) continue;				// Q^2>1 GeV^2
		hdebug_dis->Fill(2);
		// E-pz calculation
		float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   		float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   		float EminPz_Evt  = Empz_e + Empz_had;
		//if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;	// 38 < E-pz < 60 GeV
		hdebug_dis->Fill(3);
		// electron position calculation (box cut)
		float x_srtd=Sicalpos[0][0];				// position of electron in calorimeter
   		float y_srtd=Sicalpos[0][1];
   		if (Sisrtene[0]>0)
		{
      			x_srtd=Sisrtpos[0][0];				// position of electron in SRDT
      			y_srtd=Sisrtpos[0][1];
    		}
		if (TMath::Abs(x_srtd)<12)		//box cut: electron required to be outside 12x6 cm^2 box
		{
			//if (TMath::Abs(y_srtd)<6) continue;
		}
		hdebug_dis->Fill(4);
		//if (Siyel[0]>0.95) continue;				// y from electron method < 0.95
		hdebug_dis->Fill(5);
		//if (Siyjb[0]<0.01) continue;				// y from Jacquet-Blondel method > 0.01
		hdebug_dis->Fill(6);

		ev_pass_DIS++;
		// inner/outer superlayer number
		for (int j=0;j<Trk_ntracks;j++)
		{
			if (Trk_sec_vtx[j]!=1) continue;
			hinner->Fill(Trk_layinner[j]);
			houter->Fill(Trk_layouter[j]);
		}

		//  reconstructed primary vertex coordinates:
		X0=0;
		Y0=0;
		Z0=0;
		int ll=0;
		for (int c1=0;c1<Trk_nvert;c1++)
		{
			if (Vtx_prim[c1]==1)
			{
				X0=Vtx_x[c1];
				Y0=Vtx_y[c1];
				Z0=Vtx_z[c1];
				ll++;
			}
		}
		if (ll==0) no_vtx++;
		if (ll>1) wrong_vtx++;
		if (ll!=1) continue;
		hprim->Fill(X0,Y0);
		hzvert->Fill(Z0);

		//loop over RECONSTRUCTED tracks(TRACKING block) : K0s reconstruction
		for (int j=0;j<Trk_ntracks-1;j++)
		{
			if (Trk_sec_vtx[j]!=1) continue;
			//if (Trk_layouter[j]<3) continue;
			for(int k=j;k<Trk_ntracks;k++)
			{
				if (Trk_sec_vtx[k]!=1) continue;
				if (Trk_vtx[j]!=Trk_vtx[k]) continue;
				//if (Trk_layouter[k]<3) continue;
				if (Trk_charge[k]*Trk_charge[j]>0) continue;
				int hh=0;
				for (int c1=0;c1<Trk_nvert;c1++)
				{
					if ((Vtx_id[c1]==Trk_vtx[j])&&(Vtx_prim[c1]!=1))
					{
						V0_x=Vtx_x[c1];
						V0_y=Vtx_y[c1];
						V0_z=Vtx_z[c1];
						hh++;
					}
				}
				if (hh>1) cout<<"ERRORR!!!!!!!!!!!!!!!!!! "<<hh<<endl;
				Double_t	dlenx=V0_x-X0,
						dleny=V0_y-Y0,
						dlenz=V0_z-Z0;
				Double_t	dlen=sqrt(dlenx*dlenx+dleny*dleny+dlenz*dlenz),
						dlen2=sqrt(dlenx*dlenx+dleny*dleny);

				//dlenx=(-1)*dlenx;
				//dleny=(-1)*dleny;

				Daughter 	t1(Trk_px[j],Trk_py[j],Trk_pz[j]);
				Daughter 	t2(Trk_px[k],Trk_py[k],Trk_pz[k]);

				hdebug_k0->Fill(1);
				if ((Trk_layouter[k]<3)||(Trk_layouter[j]<3)) continue;
				hdebug_k0->Fill(2);
				if ((t1.GetPt()<0.1)||(t2.GetPt()<0.1)) continue;
				hdebug_k0->Fill(3);
				Mother		K0(t1,t2);
				Double_t	scal3=dlenx*K0.GetPx_m()+dleny*K0.GetPy_m()+dlenz*K0.GetPz_m(),
						scal2=dlenx*K0.GetPx_m()+dleny*K0.GetPy_m();

				Double_t	coll3d=acos(scal3/(dlen*K0.GetP_m())) ,
						coll2d=acos(scal2/(dlen2*K0.GetPt_m()));
				hcoll2->Fill(coll2d);
				hcoll3->Fill(coll3d);

				hsec1->Fill(V0_x,V0_y);
				if (coll3d>0.24) continue;
				if (coll2d>0.12) continue;
				//if (coll3d>0.5) continue;
				//if (coll2d>0.5) continue;
				hsec2->Fill(V0_x,V0_y);

				Float_t pabs1=t1.GetP();
				Float_t pabs2=t2.GetP();
				Float_t mass_pi_p=0;
				if (pabs1>pabs2)  //first track proton(antiproton); second track pion_minus(pion_plus)
				{
					mass_pi_p=K0.GetMass_m(6,4);
				}
				if (pabs1<pabs2) //first track pion_minus(pion_plus); first track proton(antiproton);
				{
					mass_pi_p=K0.GetMass_m(4,6);
				}
				hdalitz->Fill(1000*K0.GetMass_m(4,4),1000*mass_pi_p);

				if (K0.GetMass_m(3,3)<0.05) continue;
				if (mass_pi_p>1.121) hinv_K0s->Fill(1000*K0.GetMass_m(4,4));
				if (K0.GetMass_m(4,4)<0.475) hinv_Lambda->Fill(1000*mass_pi_p);
				if (mass_pi_p<1.121) continue;
				hAP->Fill(K0.Get_AP_alpha_m(),K0.Get_AP_pt_m());

				Double_t	beta=0,
						gamma=0,
						p2=0;
				p2=K0.GetP_m()*K0.GetP_m();
				beta=sqrt(p2/(0.497*0.497+p2));
				gamma=1/sqrt(1-beta*beta);
				hdlen->Fill(dlen);
				hctau->Fill(dlen/gamma);


				p[cand_k0][0]=K0.GetPx_m();
				p[cand_k0][1]=K0.GetPy_m();
				p[cand_k0][2]=K0.GetPz_m();
				cand_k0++;
			}
		}

		/*if (cand_k0<2) continue;
		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{


				Float_t		px1=p[k][0],
						py1=p[k][1],
						pz1=p[k][2],

						px2=p[l][0],
						py2=p[l][1],
						pz2=p[l][2];
				Daughter K0s_cand1(px1,py1,pz1);
				Daughter K0s_cand2(px2,py2,pz2);
				Mother K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);

				h->Fill(reso_mass);
				h1->Fill(reso_mass);
				h2->Fill(reso_mass);
			}
		}*/
	}

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_TRACKING.root","recreate");


	hinv_K0s->Write();
	hinv_Lambda->Write();
	hdalitz->Write();
	hcoll2->Write();
	hcoll3->Write();
	hAP->Write();
	hsec1->Write();
	hsec2->Write();
	hinner->Write();
	houter->Write();
	hprim->Write();
	hzvert->Write();
	hdlen->Write();
	hctau->Write();
	hdebug_dis->Write();
	hdebug_k0->Write();

	h->Write();
	h1->Write();
	h2->Write();
	f1->Close();
	cout<<no_vtx<<" events where no prim vtx"<<endl;
	cout<<wrong_vtx<<" events where more than one prim vtx"<<endl;
	cout<<ev_pass_DIS<<" events passed DIS selection"<<endl;
	cout<<"Done."<<endl;

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

