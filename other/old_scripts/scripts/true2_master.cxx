//////////////////////////////////////////////////
//////////////  MC K0s analysis: /////////////////
//////////////  true quantities, /////////////////
//////////////  track matching,  /////////////////
//////////////     and so on     /////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////
//                                              //
// This script loops over true                  //
// CTD K0s and matches them                     //
// to tracks from TRACKING,                     //
// so you can compare true/reconstructed        //
// quantities                                   //
//                                              //
//////////////////////////////////////////////////
#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TVector3.h>
#include <TVector2.h>
#include <TROOT.h>
#include <TMath.h>
#include <iostream>
#include <TSystem.h>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif

void analysis()
{
	Int_t			goa=0,
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
	const Int_t low_2004=47010,
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
	Int_t			Nk0s=0,
					Nk0s_ctd=0,
					Nlambda=0,
					Npart=0,
					Part_id[1000],
					Part_prt[1000],
					Mcmatquality[1000],
					Mcmatmother_prt[1000];
	Float_t		Part_p[1000][4];
	Float_t		P1[50][3],
					P2[50][3];

	Float_t		Trk_px[300],
					Trk_py[300],
					Trk_pz[300],
					Trk_charge[300];

	Int_t			Trk_nvert,
					Vtx_id[120],
					Vtx_prim[120];
	Float_t		Vtx_x[120],
					Vtx_y[120],
					Vtx_z[120];
	Float_t		V0_x,
					V0_y,
					V0_z;
	Float_t		X0,
					Y0,
					Z0;
	Int_t			Trk_layinner[300],
					Trk_layouter[300];

	Float_t		Prim_vtx[3],
					Sec_vtx[50][3];

	Float_t		Pk0s[50][3];
	Float_t		Xvtx=0,
					Yvtx=0,
					Zvtx=0;
	TChain *myChain=new TChain("resonance");

	//myChain->Add("/data/zenith226a/libov/data/MCfinW/test004/*.root");
	//myChain->Add("/data/zenith226a/libov/myOrange/job003/run/*.root");
	//myChain->Add("/data/zenith226a/libov/data/MCfinW/test/my_mc_test.root");
	//myChain->Add("/data/zenith226a/libov/data/MCfinW/test/mc_test.root");
	//TChain *myChain=new TChain("orange");
	// PATH to NTUPLES

	//gSystem->Load("libzio.so");
	//gSystem->Load("libdcap.so");
//------------------------------------------------------------------------------------------//
//myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwwe25.f13548.lfdir.e0506.uncut_0001.root");

myChain->Add("/data/zenith226a/libov/myOrange/job003/run/mc_TEST.root");

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
	//MCpsy
	myChain->SetBranchAddress("Nk0s",&Nk0s);
	myChain->SetBranchAddress("Nk0s_ctd",&Nk0s_ctd);
	myChain->SetBranchAddress("P1",P1);
	myChain->SetBranchAddress("P2",P2);
	myChain->SetBranchAddress("Prim_vtx",Prim_vtx);
	myChain->SetBranchAddress("Sec_vtx",Sec_vtx);
	myChain->SetBranchAddress("Pk0s",Pk0s);

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
	//nevents=100;
	cout<<nevents<<" events in this chain"<<endl;


	TH1F *hinv_K0s_true=new TH1F("hinv_K0s_true","K^{0}_{s} inv mass",100,496,499);
	TH1F *hinv_K0s_reco=new TH1F("hinv_K0s_reco","K^{0}_{s} inv mass",100,270,700);
	TH1F *hinv_nonK0s_reco=new TH1F("hinv_nonK0s_reco","K^{0}_{s} inv mass",100,270,700);
	TH2F *hAP_true=new TH2F("hAP_true","Armenteros-Podolanski",100,-1,1,100,0,0.3);
	TH2F *hAP_reco=new TH2F("hAP_reco","Armenteros-Podolanski",100,-1,1,100,0,0.3);
	TH1F *hcoll2_true=new TH1F("hcoll2_true","TRUE 2d collinearity ",100,0,0.01);
	TH1F *hcoll3_true=new TH1F("hcoll3_true","TRUE 3d collinearity ",100,0,3.15);
	TH1F *hcoll2_mat=new TH1F("hcoll2_mat","RECO 2d collinearity FOR MATCHED",100,0,3.15);
	TH1F *hcoll2_nonK0s=new TH1F("hcoll2_nonK0s","",100,0,3.15);
	TH1F *hcoll3_mat=new TH1F("hcoll3_mat","RECO 3d collinearity FOR MATCHED",100,0,3.15);

	TH1F *h_delta_min=new TH1F("h_delta_min","",10000,-2,101);
	TH1F *h_min_comb=new TH1F("h_min_comb","",10000,-2,101);

	TH1F *h_comp_prim_x=new TH1F("h_comp_prim_x","X of primary vertex: X^{prim}_{reco}-X^{prim}_{true}",200,-1,1);
	TH1F *h_comp_prim_y=new TH1F("h_comp_prim_y","Y of primary vertex: Y^{prim}_{reco}-Y^{prim}_{true}",200,-1,1);
	TH1F *h_comp_prim_z=new TH1F("h_comp_prim_z","Z of primary vertex: Z^{prim}_{reco}-Z^{prim}_{true}",200,-1,1);

	TH1F *h_comp_sec_x=new TH1F("h_comp_sec_x","X of secondary vertex: X^{sec}_{reco}-X^{sec}_{true}",200,-1,1);
	TH1F *h_comp_sec_y=new TH1F("h_comp_sec_y","Y of secondary vertex: Y^{sec}_{reco}-Y^{sec}_{true}",200,-1,1);
	TH1F *h_comp_sec_z=new TH1F("h_comp_sec_z","Z of secondary vertex: Z^{sec}_{reco}-Z^{sec}_{true}",200,-1,1);

	Int_t		tot_K0s=0;
	Int_t 		mat=0;
	Int_t		no_vtx=0;
	Bool_t		matched;
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100)
      {
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
				goa=0;
		}
       goa++;
		myChain->GetEntry(i);

		//if (Sincand<1) continue;
		/*X0=0;
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
		if (ll==1) continue;
		*/
		if ((Xvtx==0)&&(Yvtx==0)&&(Zvtx==0))
		{
			no_vtx++;
			continue;
		}
		h_comp_prim_x->Fill(Xvtx-Prim_vtx[0]);
		h_comp_prim_y->Fill(Yvtx-Prim_vtx[1]);
		h_comp_prim_z->Fill(Zvtx-Prim_vtx[2]);
		// loop over true K0s decays into CTD region

		for(int f=0;f<Nk0s_ctd;f++)
		{
			tot_K0s++;

			Float_t 			px_1=P1[f][0];
			Float_t 			py_1=P1[f][1];
			Float_t 			pz_1=P1[f][2];
			Float_t			px_2=P2[f][0];
			Float_t 			py_2=P2[f][1];
			Float_t 			pz_2=P2[f][2];

			Float_t			dlenx=Sec_vtx[f][0]-Prim_vtx[0],
								dleny=Sec_vtx[f][1]-Prim_vtx[1],
								dlenz=Sec_vtx[f][2]-Prim_vtx[2];

			//TVector3 dlen3(1)*dlenx,(-1)*dleny,dlenz);
			//TVector3 dlen2((-1)*dlenx,(-1)*dleny,0);

			TVector3 dlen3(dlenx,dleny,dlenz);
			TVector3 dlen2(dlenx,dleny,0);

			//Daughter 	t1((-1)*px_1,(-1)*py_1,pz_1);
			//Daughter 	t2((-1)*px_2,(-1)*py_2,pz_2);

			Daughter 	t1(px_1,py_1,pz_1);
			Daughter 	t2(px_2,py_2,pz_2);

			Mother		K0(t1,t2);
			TVector3 	mom3(K0.GetPx_m(),K0.GetPy_m(),K0.GetPz_m());
			TVector3 	mom2(K0.GetPx_m(),K0.GetPy_m(),0);

			Float_t		coll3=dlen3.Angle(mom3),
							coll2=dlen2.Angle(mom2);

			hcoll2_true->Fill(coll2);
			hcoll3_true->Fill(coll3);

			hinv_K0s_true->Fill(1000*K0.GetMass_m(4,4));
			hAP_true->Fill(K0.Get_AP_alpha_m(),K0.Get_AP_pt_m());

			// track matching
			matched=false;
			Double_t		eta1=t1.GetEta(),
							eta2=t2.GetEta();
			Double_t		phi1=t1.GetPhi(),
							phi2=t2.GetPhi();

			Double_t		delta_min=9999;
			Double_t		min_comb=9999;
			Int_t			matchedK0=-1;

			for (int k=0;k<Nv0lite;k++)
			{

				Int_t 		prim1=1,
								prim2=1;

				for (Int_t n=0; n<Trk_ntracks; n++)
				{
					unsigned int idx=Trk_id[n];
					if (idx == Tt1_id[k])
					{
						prim1=Trk_prim_vtx[n];
						continue;
					}
               if (idx == Tt2_id[k])
					{
						prim2=Trk_prim_vtx[n];
						continue;
					}
        		}
				//cout<<prim1<<" "<<prim2<<endl;
				if ((prim1==1)||(prim2==1)) continue;

				Daughter 	reco_pi1n(Tp1[k][0],Tp1[k][1],Tp1[k][2]);
				Daughter 	reco_pi2n(Tp2[k][0],Tp2[k][1],Tp2[k][2]);

				Double_t		delta_px_11=TMath::Power(px_1-Tp1[k][0],2);
				Double_t		delta_py_11=TMath::Power(py_1-Tp1[k][1],2);
				Double_t		delta_pz_11=TMath::Power(pz_1-Tp1[k][2],2);

				Double_t		delta_px_22=TMath::Power(px_2-Tp2[k][0],2);
				Double_t		delta_py_22=TMath::Power(py_2-Tp2[k][1],2);
				Double_t		delta_pz_22=TMath::Power(pz_2-Tp2[k][2],2);

				Double_t		delta_px_12=TMath::Power(px_1-Tp2[k][0],2);
				Double_t		delta_py_12=TMath::Power(py_1-Tp2[k][1],2);
				Double_t		delta_pz_12=TMath::Power(pz_1-Tp2[k][2],2);

				Double_t		delta_px_21=TMath::Power(px_2-Tp1[k][0],2);
				Double_t		delta_py_21=TMath::Power(py_2-Tp1[k][1],2);
				Double_t		delta_pz_21=TMath::Power(pz_2-Tp1[k][2],2);

Double_t		delta_11_22=sqrt(delta_px_11+delta_py_11+delta_pz_11+delta_px_22+delta_py_22+delta_pz_22);
Double_t		delta_12_21=sqrt(delta_px_12+delta_py_12+delta_pz_12+delta_px_21+delta_py_21+delta_pz_21);


				if (delta_11_22<delta_12_21)
				{
					min_comb=delta_11_22;
				}
				if (delta_11_22>=delta_12_21)
				{
					min_comb=delta_12_21;
				}

				if (min_comb<delta_min)
				{
					delta_min=min_comb;
				}

				if (delta_min<=0.05)
				{
					matchedK0=k;
				}
				h_min_comb->Fill(min_comb);
				if(min_comb>0.5)
				{
					hinv_nonK0s_reco->Fill(1000*Tinvmass_k0[k]);
					if ((1000*Tinvmass_k0[matchedK0]-497.6)<20) continue;
					hcoll2_nonK0s->Fill(Tsecvtx_collin2[k]);
				}
			}
			h_delta_min->Fill(delta_min);

			if (matchedK0<0) continue;
			hinv_K0s_reco->Fill(1000*Tinvmass_k0[matchedK0]);

			if ((1000*Tinvmass_k0[matchedK0]-497.6)>20) continue;
			hcoll2_mat->Fill(Tsecvtx_collin2[matchedK0]);
			hcoll3_mat->Fill(Tsecvtx_collin3[matchedK0]);


		}
	}

	TFile *f1 =new TFile("/data/zenith226a/libov/K0s_anal_TRUE.root","recreate");

	hinv_K0s_true->Write();
	hinv_K0s_reco->Write();
	hcoll2_true->Write();
	hcoll3_true->Write();
	hcoll2_mat->Write();
	hcoll2_nonK0s->Write();
	hcoll3_mat->Write();
	hAP_reco->Write();
	hAP_true->Write();
	h_delta_min->Write();
	h_min_comb->Write();
	hinv_nonK0s_reco->Write();

	f1->Close();
	cout<<mat<<" matched of "<<tot_K0s<<endl;
	cout<<no_vtx<<" events rejected because of bad vertex( "<<100*((Float_t)no_vtx)/nevents<<" %)"<<endl;
	cout<<"Done!!!"<<endl;

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

