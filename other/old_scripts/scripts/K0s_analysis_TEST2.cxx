//////////////////////////////////////////////////
//////////////  K0s    analysis  /////////////////
//////////////////////////////////////////////////
//
//
//
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

void soft_K0K0_HERAII()
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
			Nlambda=0,
			Npart=0,
			Part_id[1000],
			Part_prt[1000],
			Mcmatquality[1000],
			Mcmatmother_prt[1000];
	Float_t		Part_p[1000][4];
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

	TChain *myChain=new TChain("resonance");




	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_0.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_1.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_2.root");
	myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_3.root");

	/*myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_0.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_1.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_2.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_3.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_4.root");
	myChain->Add("/data/zenith226a/libov/data/2005RP/v0_mini05RP_5.root");*/

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

	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;
	TH1F *hinv_K0s_true=new TH1F("hinv_K0s_true","K^{0}_{s} inv mass",100,497.6,497.7);
	TH1F *hinv_K0s_reco=new TH1F("hinv_K0s_reco","K^{0}_{s} inv mass",100,300,700);
	TH1F *hinv_K0s_track=new TH1F("hinv_K0s_track","K^{0}_{s} inv mass",100,450,552);
	TH1F *hinv_Lambda_track=new TH1F("hinv_Lambda_track","Lambda inv mass",100,1050,1300);
	TH2F *hAP=new TH2F("hAP","Armenteros-Podolanski",100,-1,1,100,0,0.3);
	TH1F *hcoll2=new TH1F("hcoll2","collinearity 2d",100,0,3);
	TH1F *hcoll3=new TH1F("hcoll3","collinearity 3d",100,0,3);
	/*TH2F *hprim=new TH2F("hprim","Primary vertex distr",200,-8,6,200,-4,4);
	TH2F *hsec=new TH2F("hsec","V0 sec vertex distr",200,-8,6,200,-4,4);*/

	TH2F *hprim_true=new TH2F("hprim_true","Primary vertex true",400,1.6,2,400,0,0.4);
	TH2F *hprim_reco=new TH2F("hprim_reco","Primary vertex reco",400,1.6,2,400,0,0.4);
	TH2F *hsec1=new TH2F("hsec1","",400,-20,20,400,-20,20);
	TH2F *hsec2=new TH2F("hsec2","",400,-20,20,400,-20,20);

	TH2F *hprim_comp=new TH2F("hprim_comp","Primary vertex difference",400,-0.3,0.3,400,-0.1,0.1);

	TH2F *hinv_2d=new TH2F("hinv_2d","",400,200,800,400,1050,1400);

	TH1F *hzvert_true=new TH1F("hzvert_true","Z of prim vert",100,-50,50);
	TH1F *hzvert_comp=new TH1F("hzvert_comp","Z of prim vert: true-reco",100,-5,5);

	TH1F *hinner=new TH1F("hinner","inner layer",10,0,10);
	TH1F *houter=new TH1F("houter","outer layer",10,0,10);
	TH1F *hdlen_true=new TH1F("hdlen_true","true decay length(lab)",100,0,20);
	TH1F *hctau_true=new TH1F("hctau_true","true decay length(rest)",100,0,20);

	TH1F *hdlen_reco=new TH1F("hdlen_reco","reco decay length(lab)",100,0,20);
	TH1F *hctau_reco=new TH1F("hctau_reco","reco decay length(rest)",100,0,20);

	Int_t 		err=0;
	Int_t		tot_l=0,
			tot_k=0,
			tot_k_branch=0,
			tot_k_new=0,
			tot_l_new=0;
	Int_t 		mat=0;
	Int_t		wrong_vtx=0;

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		//cout<<"event "<<i<<", "<<Nk0s_ctd<<" true ctd k0s"<<endl;

		// inner/outer superlayer number
		for (int j=0;j<Trk_ntracks;j++)
		{
			if (Trk_sec_vtx[j]!=1) continue;
			hinner->Fill(Trk_layinner[j]);
			houter->Fill(Trk_layouter[j]);
		}

		//  reconstructed primary vertex
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
		if (ll!=1)
		{
			wrong_vtx++;
			//cout<<"No prim vtx!"<<endl;
			//cout<<Trk_nvert<<" total vertices"<<endl;
			for (int c1=0;c1<Trk_nvert;c1++)
			{
				//cout<<Vtx_prim[c1]<<" "<<Vtx_x[c1]<<" "<<Vtx_y[c1]<<" "<<Vtx_z[c1]<<endl;
			}

		}

		// comparison of true/reco prim vertex
		hprim_true->Fill(Prim_vtx[0],Prim_vtx[1]);
		hprim_reco->Fill(X0,Y0);
		hprim_comp->Fill(X0-Prim_vtx[0],Y0-Prim_vtx[1]);
		hzvert_true->Fill(Prim_vtx[2]);
		hzvert_comp->Fill(Z0-Prim_vtx[2]);
		//loop over RECONSTRUCTED tracks(TRACKING block) : K0s reconstruction
		for (int j=0;j<Trk_ntracks-1;j++)
		{
			if (Trk_sec_vtx[j]!=1) continue;
			if (Trk_layouter[j]<3) continue;
			for(int k=j;k<Trk_ntracks;k++)
			{
				if (Trk_sec_vtx[k]!=1) continue;
				if (Trk_vtx[j]!=Trk_vtx[k]) continue;
				if (Trk_layouter[k]<3) continue;
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

				Daughter 	t1(Trk_px[j],Trk_py[j],Trk_pz[j]);
				Daughter 	t2(Trk_px[k],Trk_py[k],Trk_pz[k]);
				Mother		K0(t1,t2);
				Double_t	scal3=dlenx*K0.GetPx_m()+dleny*K0.GetPy_m()+dlenz*K0.GetPz_m(),
						scal2=dlenx*K0.GetPx_m()+dleny*K0.GetPy_m();

				Double_t	coll3d=acos(scal3/(dlen*K0.GetP_m())) ,
						coll2d=acos(scal2/(dlen2*K0.GetPt_m()));
				hcoll2->Fill(coll2d);
				hcoll3->Fill(coll3d);

				//if (coll3d>0.3) continue;
				hsec1->Fill(V0_x,V0_y);
				if (coll2d>0.1) continue;

				//hAP->Fill(K0.Get_AP_alpha_m(),K0.Get_AP_pt_m());

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
				hinv_2d->Fill(1000*K0.GetMass_m(4,4),1000*mass_pi_p);
				//if (K0.GetMass_m(3,3)<0.05) continue;
				if (mass_pi_p>1.121) hinv_K0s_track->Fill(1000*K0.GetMass_m(4,4));
				if (K0.GetMass_m(4,4)<0.475) hinv_Lambda_track->Fill(1000*mass_pi_p);
				//if (mass_pi_p<1.121) continue;
				hAP->Fill(K0.Get_AP_alpha_m(),K0.Get_AP_pt_m());
				Double_t	beta=0,
						gamma=0,
						p2=0;
				p2=K0.GetP_m()*K0.GetP_m();
				beta=sqrt(p2/(0.497*0.497+p2));
				gamma=1/sqrt(1-beta*beta);
				hdlen_reco->Fill(dlen);
				hctau_reco->Fill(dlen/gamma);
			}
		}

		// loop over true K0s decays into CTD region

		for(int f=0;f<Nk0s_ctd;f++)
		{
			Float_t 	px_1=P1[f][0];
			Float_t 	py_1=P1[f][1];
			Float_t 	pz_1=P1[f][2];
			Float_t		px_2=P2[f][0];
			Float_t 	py_2=P2[f][1];
			Float_t 	pz_2=P2[f][2];

			//pz_1=0;
			Float_t		dlenx_true=Prim_vtx[0]-Sec_vtx[f][0],
					dleny_true=Prim_vtx[1]-Sec_vtx[f][1],
					dlenz_true=Prim_vtx[2]-Sec_vtx[f][2];
			if (Sec_vtx[f][2]<-1000) cout<<Sec_vtx[f][2]<<"aaaaaaaaaaaa"<<endl;
			//cout<<Sec_vtx[f][0]<<" "<<Sec_vtx[f][1]<<" "<<Sec_vtx[f][2]<<" "<<endl;
			//cout<<dlenx_true<<" "<<dleny_true<<" "<<dlenz_true<<" "<<endl;
			Float_t		dlen_true=sqrt(dlenx_true*dlenx_true+dleny_true*dleny_true+dlenz_true*dlenz_true),
					dlen2_true=sqrt(dlenx_true*dlenx_true+dleny_true*dleny_true);



			//cout<<dlen_true<<" "<<dlen2_true<<endl;

			Daughter 	t1(px_1,py_1,pz_1);
			Daughter 	t2(px_2,py_2,pz_2);
			Mother		K0(t1,t2);
			hinv_K0s_true->Fill(1000*K0.GetMass_m(4,4));
			Double_t	beta=0,
					gamma=0,
					p2=0;
			p2=K0.GetP_m()*K0.GetP_m();
			beta=sqrt(p2/(0.497*0.497+p2));
			gamma=1/sqrt(1-beta*beta);
			hdlen_true->Fill(dlen_true);
			hctau_true->Fill(dlen_true/gamma);

			Double_t	scal3_true=0,
					scal2_true=0;
			scal3_true=dlenx_true*K0.GetPx_m()+dleny_true*K0.GetPy_m()+dlenz_true*K0.GetPz_m();
			scal2_true=dlenx_true*K0.GetPx_m()+dleny_true*K0.GetPy_m();
			//cout<<"scal: "<<scal3_true<<" "<<scal2_true<<endl;
			//cout<<"prod: "<<K0.GetP_m()*dlen_true<<" "<<K0.GetPt_m()*dlen2_true <<endl;
			//cout<<"rat: "<<scal3_true/(dlen_true*(K0.GetP_m()))<<" -- "<<scal2_true/(dlen2_true*(K0.GetPt_m()))<<endl;
			Float_t		coll3d_true=acos(scal3_true/(dlen_true*K0.GetP_m())) ,
					coll2d_true=acos(scal2_true/(dlen2_true*K0.GetPt_m()));

			//cout<<coll2d_true<<" "<<coll3d_true<<endl;

			TVector3 v1(dlenx_true,dleny_true,dlenz_true);
			TVector3 v2(K0.GetPx_m(),K0.GetPy_m(),K0.GetPz_m());
			//cout<<v1.Angle(v2)<<" @ "<<coll3d_true<<endl;

			//hcoll2->Fill(coll2d_true);
			//hcoll3->Fill(coll3d_true);
			Double_t	eta1=t1.GetEta(),
					eta2=t2.GetEta();
			Double_t	phi1=t1.GetPhi(),
					phi2=t2.GetPhi();
			//cout<<K0.GetMass_m(4,4)<<" "<<t1.GetEta()<<" "<<t2.GetEta()<<endl;
			//cout<<"true CTD K0s "<<f<<endl;
			Int_t	mat1=-1,mat2=-1;
			Double_t	delta1min=9999,
					delta2min=9999;
			for (int g=0;g<Trk_ntracks;g++)
			{
				Daughter t(Trk_px[g],Trk_py[g],Trk_pz[g]);
				Double_t	eta=t.GetEta();
				Double_t	phi=t.GetPhi();
				Double_t	delta_eta1=eta1-eta;
				Double_t	delta_phi1=phi1-phi;
				Double_t	delta_eta2=eta2-eta;
				Double_t	delta_phi2=phi2-phi;
				Double_t	delta1=0,
						delta2=0;
				delta1=sqrt(delta_eta1*delta_eta1+delta_phi1*delta_phi1);
				delta2=sqrt(delta_eta2*delta_eta2+delta_phi2*delta_phi2);
				if ((delta1<0.03)&&(delta1<delta1min))
				{
					delta1min=delta1;
					mat1=g;
				}
				if ((delta2<0.03)&&(delta2<delta2min))
				{
					delta2min=delta2;
					mat2=g;
				}
			}
			if ((mat1>=0)&&(mat2>=0))
			{
				Daughter reco1(Trk_px[mat1],Trk_py[mat1],Trk_pz[mat1]);
				Daughter reco2(Trk_px[mat2],Trk_py[mat2],Trk_pz[mat2]);
				Mother	K0_reco(reco1,reco2);
				mat++;
				//cout<<K0_reco.GetMass_m(4,4)<<endl;
				hinv_K0s_reco->Fill(1000*K0_reco.GetMass_m(4,4));
			}

		}



		//if(Nlambda!=1)continue;
/*	//------DIS event selection------//
		hq2->Fill(Siq2el[0]);
		hdebug->Fill(1);
		//if (Siq2el[0]<1) continue;						// Q^2>1 GeV^2
		hdebug->Fill(2);
		// E-pz calculation
		float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   		float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   		float EminPz_Evt  = Empz_e + Empz_had;
		//if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;			// 38 < E-pz < 60 GeV
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
			//if (TMath::Abs(y_srtd)<6) continue;
		}
		hdebug->Fill(4);
		//if (Siyel[0]>0.95) continue;						// y from electron method < 0.95
		hdebug->Fill(5);
		//if (Siyjb[0]<0.01) continue;						// y from Jacquet-Blondel method > 0.01
		hdebug->Fill(6);
*/		//cout<<"event "<<i<<endl;
		//Int_t Nlambda=0;

		// attempt to find K0s->pipi by their daughters
		/*cout<<Npart<<" particles in fmckin block"<<endl;
		for (int z=0;z<Npart;z++)
		{
			cout<<Part_id[z]<<" "<<Part_prt[z]<<endl;
		}*/
		/*
		for (int j=0;j<Npart-1;j++)
		{
			if ((Part_prt[j]!=54)&&(Part_prt[j]!=55)) continue;
			for (int l=j;l<Npart;l++)
			{
				if ((Part_prt[j]+Part_prt[l])!=109) continue;
				Double_t px_1=Part_p[j][0];
				Double_t py_1=Part_p[j][1];
				Double_t pz_1=Part_p[j][2];
				Double_t px_2=Part_p[l][0];
				Double_t py_2=Part_p[l][1];
				Double_t pz_2=Part_p[l][2];

				Daughter t1(px_1,py_1,pz_1);
				Daughter t2(px_2,py_2,pz_2);

				Double_t	eta1=t1.GetEta(),
						eta2=t2.GetEta();
				//if ((abs(eta1)>1.75)||(abs(eta2)>1.75)) continue;
				Mother		K0(t1,t2);

				if (abs(1000*K0.GetMass_m(4,4)-497.7)<1)
				{
					tot_k_new++;
					//cout<<1000*K0.GetMass_m(4,4)<<endl;
				}
			}
		}
		// attempt to find Lambda->pi p by their daughters
		for (int j=0;j<Npart-1;j++)
		{
			if ((Part_prt[j]!=190)&&(Part_prt[j]!=55)) continue;
			for (int l=j;l<Npart;l++)
			{
				if ((Part_prt[j]+Part_prt[l])!=245) continue;

				Double_t px_1=Part_p[j][0];
				Double_t py_1=Part_p[j][1];
				Double_t pz_1=Part_p[j][2];
				Double_t px_2=Part_p[l][0];
				Double_t py_2=Part_p[l][1];
				Double_t pz_2=Part_p[l][2];

				Daughter t1(px_1,py_1,pz_1);
				Daughter t2(px_2,py_2,pz_2);
				Double_t	eta1=t1.GetEta(),
						eta2=t2.GetEta();

				if ((abs(eta1)>1.75)||(abs(eta2)>1.75)) continue;
				Mother		lambda(t1,t2);
				Float_t pabs1=t1.GetP();
				Float_t pabs2=t2.GetP();
				Float_t mass_pi_p=0;
				if (pabs1>pabs2)  //first track proton(antiproton); second track pion_minus(pion_plus)
				{
					mass_pi_p=lambda.GetMass_m(6,4);
				}
				if (pabs1<pabs2) //first track pion_minus(pion_plus); first track proton(antiproton);
				{
					mass_pi_p=lambda.GetMass_m(4,6);
				}

				if (abs(mass_pi_p-1.1156)<0.001)
				{
					tot_l_new++;

				}
			}
		}
		//only true K0s and lambda
		for (int j=0;j<Npart;j++)
		{

			if (Part_prt[j]==62)
			{
				Double_t E=Part_p[j][3];
				Double_t px=Part_p[j][0];
				Double_t py=Part_p[j][1];
				Double_t pz=Part_p[j][2];
				Daughter k0s(px,py,pz);
				//cout<<k0s.GetEnergy(1)<<" "<<E<<" "<<Part_p[j][4]<<endl;
				//cout<<k0s.GetEnergy(1)<<" "<<E<<" "<<sqrt(E*E-k0s.GetP()*k0s.GetP())<<" "<<Part_p[j][4]<<endl;
				Double_t eta=k0s.GetEta();
				//tot_k++;
				if (abs(eta)<=1.75) tot_k++;
			}
			if (Part_prt[j]==194)
			{
				Double_t E=Part_p[j][3];
				Double_t px=Part_p[j][0];
				Double_t py=Part_p[j][1];
				Double_t pz=Part_p[j][2];
				Daughter lambda(px,py,pz);
				//cout<<lambda.GetEnergy(3)<<" "<<E<<endl;
				Double_t eta=lambda.GetEta();
				if (abs(eta)<=1.75) continue;
				tot_l++;
				Int_t match=0;
				for (int k=0;k<Trk_ntracks;k++)
				{
					if ((Mcmatquality[k]==1)||(Mcmatquality[k]==(-1)))
						{
							match++;
							if (Mcmatmother_prt[k]==194) cout<<"matched"<<endl;
						}
				}
				//cout<<match<<" of "<<Trk_ntracks<<" of "<<Npart<<" tracks matched"<<endl;


			}
		}
		tot_k_branch=tot_k_branch+Nk0s_ctd;
		*/

	}

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0s_anal_comp_true_reco2.root","recreate");
	hinv_K0s_true->Write();
	hinv_K0s_reco->Write();
	hinv_K0s_track->Write();
	hinv_Lambda_track->Write();
	hinv_2d->Write();
	hcoll2->Write();
	hcoll3->Write();
	hAP->Write();
	hprim_true->Write();
	hprim_reco->Write();
	hsec1->Write();
	hsec2->Write();
	hinner->Write();
	houter->Write();
	hprim_comp->Write();
	hzvert_true->Write();
	hzvert_comp->Write();
	hdlen_true->Write();
	hctau_true->Write();
	hdlen_reco->Write();
	hctau_reco->Write();
	f1->Close();
	cout<<wrong_vtx<<" bad vertices"<<endl;
	//cout<<"sum true K0s: "<<tot_k<<endl;
	//cout<<"sum true pions with K0s mass pl/min 10: "<<tot_k_new<<endl;
	//cout<<"sum from filltrue: "<<tot_k_branch<<endl;
	//cout<<"lamdas with daughters: "<<tot_l_new<<endl;
	//cout<<"lambdas true: "<<tot_l<<endl;
	//cout<<mat<<" natches"<<endl;
	cout<<"Done!!!"<<endl;

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	soft_K0K0_HERAII();
	return 0;
}
#endif

