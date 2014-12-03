//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//               September 2008                 //
//                                              //
//                                              //
//////////////////////////////////////////////////

// ***********************************************
// *  Working with true variables (MyMiniNtuples)*
// ***********************************************
#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TMath.h>
#include <TSystem.h>
#include <iostream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif

void analysis()
{
	TChain *myChain=new TChain("resonance");
	//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root",26078430);
//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root");

myChain->Add("/data/zenith226a/libov/scripts/mc_TEST_output.root");


	// Variables declaring
	// true
	Int_t			ntrue=0,				//  Number of stored (e.g. those survived pT cut)
											//  FMCKIN particles
					fmcprt[50];			//  FMCPRT code
	Float_t		mass[5000];			//  mass
	Int_t			daug_of[5000];		//  Daughter f
	Int_t			fmckin_id[5000];	//  Daughter f
	Float_t		px[5000],			//  Px of particle
					py[5000],			//  Py
					pz[5000];			//  Pz

	// K0s
	Int_t			nv0=0;				// number K0s candidates that passed soft selection
	Float_t		p1[80][3],			// momenta of 1st track
					p2[80][3];			// momenta of 2nd track

	Float_t		coll2[80];
	Int_t			is1_prim[80];
	Int_t			is2_prim[80];
	// branches

	//	Additional true block (Common Ntuples only)
	myChain->SetBranchAddress("ntrue",&ntrue);
	myChain->SetBranchAddress("fmcprt",fmcprt);
	myChain->SetBranchAddress("mass",mass);
	myChain->SetBranchAddress("daug_of",daug_of);
	myChain->SetBranchAddress("fmckin_id",fmckin_id);
	myChain->SetBranchAddress("px",px);
	myChain->SetBranchAddress("py",py);
	myChain->SetBranchAddress("pz",pz);

	//	Reconstructed K0 (from MyMiniNtuple)
	myChain->SetBranchAddress("nv0",&nv0);
	myChain->SetBranchAddress("p1",p1);
	myChain->SetBranchAddress("p2",p2);
	myChain->SetBranchAddress("coll2",coll2);
	myChain->SetBranchAddress("is1_prim",is1_prim);
	myChain->SetBranchAddress("is2_prim",is2_prim);


	// histograms
	TH1F *h_fmcprt=new TH1F("h_fmcprt","",2500,0,2500);

	TH1F *hphi=new TH1F("hphi","",10000,-2,101);
	TH1F *heta=new TH1F("heta","",10000,-2,101);
	TH1F *hp=new TH1F("hp","",10000,-2,101);

	TH1F *h_dv0min=new TH1F("h_dv0min","",10000,-2,101);
	//_________________
	TH1F *hinv_K0s_true=new TH1F("hinv_K0s_true","K^{0}_{s} inv mass",100,496,499);
	TH1F *hinv_K0s_reco=new TH1F("hinv_K0s_reco","K^{0}_{s} inv mass",100,270,700);
	TH1F *hinv_K0s_reco_all=new TH1F("hinv_K0s_reco_all","K^{0}_{s} inv mass",100,270,700);
	TH1F *hinv_K0s_reco_nonK0s=new TH1F("hinv_K0s_reco_nonK0s","K^{0}_{s} inv mass",100,270,700);
	TH1F *hcoll2_reco_nonK0s=new TH1F("hcoll2_reco_nonK0s","",100,0,3.14);
	TH1F *hcoll2_reco=new TH1F("hcoll2_reco","",100,0,3.14);
	//_________________

	cout<<"Evaluating number of events..."<<endl;
	Int_t	nevents=0;
	nevents=myChain->GetEntries();
	//nevents=26078430;
	//nevents=100000;
	cout<<nevents<<" events in this chain"<<endl;
	int goa=0;
	Int_t	nK0=0;
	Int_t	nK0pipi_charged=0;
	Int_t	nf04pi=0;
	Int_t	match=0;
	for (int k=0;k<nevents;k++)
	{
		if (goa==100000)
      {
      	cout<<k<<" events processed"<<endl;
			goa=0;
		}

		goa++;
		myChain->GetEntry(k);
		//cout<<k<<" "<<ntrue<<endl;
		for (int z=0;z<ntrue;z++)
		{

			h_fmcprt->Fill(fmcprt[z]);
			// 62=K0s
			if (fmcprt[z]!=62) continue;
			nK0++;
			//cout<<"found f0 with true mass "<<mass[z]<<endl;

			Int_t		dghtr1=0,
						dghtr2=0,
						temp[5],
						NumberOfDaughters=0;

			for (int j=0;j<ntrue;j++)
			{
				if (daug_of[j]==fmckin_id[z])
				{
					temp[NumberOfDaughters]=j;
					NumberOfDaughters++;
				}
			}

			if (NumberOfDaughters==0) continue;
			if (NumberOfDaughters!=2) cout<<"CATASTROPHA VEKA !!!!!!!!!!!!!!!!!!"<<endl;
			if (NumberOfDaughters!=2) continue;
			dghtr1=temp[0];
			dghtr2=temp[1];

			bool 	dghtr1_pi_plus=(fmcprt[dghtr1]==54);
			bool 	dghtr1_pi_minus=(fmcprt[dghtr1]==55);
			bool 	dghtr2_pi_plus=(fmcprt[dghtr2]==54);
			bool 	dghtr2_pi_minus=(fmcprt[dghtr2]==55);
			//
			if (!((dghtr1_pi_plus && dghtr2_pi_minus)||(dghtr2_pi_plus && dghtr1_pi_minus))) continue;
			nK0pipi_charged++;

			Daughter true_pi1(px[dghtr1],py[dghtr1],pz[dghtr1]);
			Daughter true_pi2(px[dghtr2],py[dghtr2],pz[dghtr2]);

			Mother true_K0(true_pi1,true_pi2);

			Float_t K0_true_mass=true_K0.GetMass_m(4,4);
			hinv_K0s_true->Fill(1000*K0_true_mass);

			//if ((TMath::Abs(true_pi1.GetEta())>1.75)||(TMath::Abs(true_pi2.GetEta())>1.75)) continue;

			// Now match true pions from K0s to reconstructed ones
			Double_t	dv0min=1000;
			Double_t	dmin=1000;
			Int_t		matchedK0=-1;
			Int_t		bla=0;

			// loop over reconstructed-K0s and match to true-K0s
			for (int n=0;n<nv0;n++)
			{
				if ((is1_prim[n]==1)||(is2_prim[n]==1)) continue;
				Daughter reco_pi1n(p1[n][0],p1[n][1],p1[n][2]);
				Daughter reco_pi2n(p2[n][0],p2[n][1],p2[n][2]);
				Mother	K0temp(reco_pi1n,reco_pi2n);
				hinv_K0s_reco_all->Fill(1000*K0temp.GetMass_m(4,4));

				// pi1K1<->pi1n, pi2K1<->pi2n (11, 22)
				Double_t	phi11=true_pi1.GetPhi()-reco_pi1n.GetPhi();
				Double_t	phi22=true_pi2.GetPhi()-reco_pi2n.GetPhi();
				Double_t	eta11=true_pi1.GetEta()-reco_pi1n.GetEta();
				Double_t	eta22=true_pi2.GetEta()-reco_pi2n.GetEta();
				Double_t	p11=true_pi1.GetP()-reco_pi1n.GetP();
				Double_t	p22=true_pi2.GetP()-reco_pi2n.GetP();

				// pi1K1<->pi2n, pi2K1<->pi1n (12, 21)
				Double_t	phi12=true_pi1.GetPhi()-reco_pi2n.GetPhi();
				Double_t	phi21=true_pi2.GetPhi()-reco_pi1n.GetPhi();
				Double_t	eta12=true_pi1.GetEta()-reco_pi2n.GetEta();
				Double_t	eta21=true_pi2.GetEta()-reco_pi1n.GetEta();
				Double_t	p12=true_pi1.GetP()-reco_pi2n.GetP();
				Double_t	p21=true_pi2.GetP()-reco_pi1n.GetP();

				Double_t		d_comb_min=1000;
				Double_t		d11_22=0,
								d12_21=0;
				d11_22=sqrt(phi11*phi11+phi22*phi22+eta11*eta11+eta22*eta22+p11*p11+p22*p22);
				d12_21=sqrt(phi12*phi12+phi21*phi21+eta12*eta12+eta21*eta21+p12*p12+p21*p21);

				Double_t			delta_px_11=TMath::Power(p1[n][0]-px[dghtr1],2);
				Double_t			delta_py_11=TMath::Power(p1[n][1]-py[dghtr1],2);
				Double_t			delta_pz_11=TMath::Power(p1[n][2]-pz[dghtr1],2);

				Double_t			delta_px_22=TMath::Power(p2[n][0]-px[dghtr2],2);
				Double_t			delta_py_22=TMath::Power(p2[n][1]-py[dghtr2],2);
				Double_t			delta_pz_22=TMath::Power(p2[n][2]-pz[dghtr2],2);

				Double_t			delta_px_12=TMath::Power(p1[n][0]-px[dghtr2],2);
				Double_t			delta_py_12=TMath::Power(p1[n][1]-py[dghtr2],2);
				Double_t			delta_pz_12=TMath::Power(p1[n][2]-pz[dghtr2],2);

				Double_t			delta_px_21=TMath::Power(p2[n][0]-px[dghtr1],2);
				Double_t			delta_py_21=TMath::Power(p2[n][1]-py[dghtr1],2);
				Double_t			delta_pz_21=TMath::Power(p2[n][2]-pz[dghtr1],2);

				Double_t			delta_11_22=delta_px_11+delta_py_11+delta_pz_11;
									delta_11_22+=delta_px_22+delta_py_22+delta_pz_22;
									delta_11_22=sqrt(delta_11_22);

				Double_t			delta_12_21=delta_px_12+delta_py_12+delta_pz_12;
									delta_12_21+=delta_px_21+delta_py_21+delta_pz_21;
									delta_12_21=sqrt(delta_12_21);


				/*if (d11_22<d12_21)
				{
					d_comb_min=d11_22;
					hp->Fill(p11*p11+p22*p22);
					heta->Fill(eta11*eta11+eta22*eta22);
					hphi->Fill(phi11*phi11+phi22*phi22);
				}
				if (d11_22>=d12_21)
				{
					d_comb_min=d12_21;
				}*/

				if (delta_11_22<delta_12_21)
				{
					d_comb_min=delta_11_22;
					/*hp->Fill(p11*p11+p22*p22);
					heta->Fill(eta11*eta11+eta22*eta22);
					hphi->Fill(phi11*phi11+phi22*phi22);*/
				}
				if (delta_11_22>=delta_12_21)
				{
					d_comb_min=delta_12_21;
				}
				//cout<<"reco K0 Nr "<<n<<" : "<<d11_22<<" "<<d12_21<<" "<<endl;

				if (d_comb_min<dv0min)
				{
					dv0min=d_comb_min;
				}
				//cout<<dv0min<<endl;
				if (dv0min<=0.05)
				{
					matchedK0=n;
				}
				if(d_comb_min<=0.05) bla++;
			}
			//if (bla>1) cout<<"assssssssssssssssssssssssssssssssssssssssssssssss"<<endl;
			//if (bla>1) continue;
			h_dv0min->Fill(dv0min);




			//------------------------------------------------//


			//cout<<"Matching results: "<<matchedK01<<" "<<matchedK02<<endl;

			if (matchedK0>=0)
			{
				match++;
				//cout<<"matched K0, "<<endl;
				Daughter		match_pi1(p1[matchedK0][0],p1[matchedK0][1],p1[matchedK0][2]);
				Daughter		match_pi2(p2[matchedK0][0],p2[matchedK0][1],p2[matchedK0][2]);
				Mother		match_K1(match_pi1,match_pi2);
				Double_t		K0massreco=1000*match_K1.GetMass_m(4,4);
				//cout<<"Reco Mass is "<<1000*match_K1.GetMass_m(4,4)<<endl;
				//cout<<"True mass= "<<1000*K0_true_mass<<endl;
				hinv_K0s_reco->Fill(K0massreco);
				if ((K0massreco-497.6)<20)
				{
					hcoll2_reco->Fill(coll2[matchedK0]);
				}
				if ((K0massreco-497.6)>=20)
				{
					//hcoll2_reco_nonK0s->Fill(coll2[matchedK0]);
				}

			}
			if (matchedK0<0)
			{
				for (int k=0;k<nv0;k++)
				{
						hcoll2_reco_nonK0s->Fill(coll2[k]);
						Daughter		pi1(p1[k][0],p1[k][1],p1[k][2]);
						Daughter		pi2(p2[k][0],p2[k][1],p2[k][2]);
						Mother		K0temp1(pi1,pi2);
						hinv_K0s_reco_nonK0s->Fill(1000*K0temp1.GetMass_m(4,4));

				}
			}


		}



	}





	//TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/fmcprt_v3.root","recreate");

	TFile *f2 =new TFile("/data/zenith226a/libov/mc_test_nocoll.root","recreate");
	h_fmcprt->Write();

	//---

	h_dv0min->Write();


	//___________
	hinv_K0s_true->Write();
	hinv_K0s_reco->Write();
	hinv_K0s_reco_all->Write();
	hcoll2_reco->Write();
	hcoll2_reco_nonK0s->Write();
	hinv_K0s_reco_nonK0s->Write();

	hphi->Write();
	heta->Write();
	hp->Write();


	f2->Close();
	cout<<nK0<<" true K0s"<<endl;
	cout<<nK0pipi_charged<<" K0s->pi+pi-"<<endl;

	cout<<"matched: "<<match<<endl;
	cout<<"ready"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif



