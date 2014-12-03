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
myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root");


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


	// histograms
	TH1F *h_f0mass=new TH1F("h_f0mass","",5000,999.95,1000.05);
	TH1F *h_f0mass_reco=new TH1F("h_f0mass_reco","",5000,999.95,1000.05);
	TH1F *h_fmcprt=new TH1F("h_fmcprt","",2500,0,2500);
	TH1F *h_delta_eta=new TH1F("h_delta_eta","",100,-2,2);
	TH1F *h_delta_phi=new TH1F("h_delta_phi","",100,-2,2);

	TH1F *h_phi1=new TH1F("h_phi1","",10000,-2,101);
	TH1F *h_phi2=new TH1F("h_phi2","",10000,-2,101);
	TH1F *h_phi1_min=new TH1F("h_phi1_min","",10000,-2,101);
	TH1F *h_phi2_min=new TH1F("h_phi2_min","",10000,-2,101);
	TH1F *h_dv0min=new TH1F("h_dv0min","",10000,-2,101);

	cout<<"Evaluating number of events..."<<endl;
	Int_t	nevents=0;
	//nevents=myChain->GetEntries();
	//nevents=26078430;
	nevents=100;
	cout<<nevents<<" events in this chain"<<endl;
	int goa=0;
	Int_t	nf0=0;
	Int_t	nf0K0K0=0;
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
			// in case of f0(980)
			//cout<<"@@@ "<<z<<endl;
			if (fmcprt[z]!=81) continue;

			nf0++;
			//cout<<"found f0 with true mass "<<mass[z]<<endl;

			Int_t	dghtr1=0,
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

			dghtr1=temp[0];
			dghtr2=temp[1];
			if (NumberOfDaughters==0) continue;
			//cout<<"Has "<<NumberOfDaughters<<" daughters:"<<endl;
			//cout<<"id(temp[])     id(ntuple)     fmcprt"<<endl;
			for (int ddd=0;ddd<NumberOfDaughters;ddd++)
			{
				//cout<<ddd<<"               "<<temp[ddd]<<"                "<<fmcprt[temp[ddd]]<<endl;
			}


			// skip if of f0 not decayed into two neutral kaons
			if ((fmcprt[dghtr1]!=62)||(fmcprt[dghtr2]!=62)||(NumberOfDaughters!=2)) continue;
			//cout<<"Found f0->K0sK0s"<<endl;
			nf0K0K0++;
			Daughter K1(px[dghtr1],py[dghtr1],pz[dghtr1]);
			Daughter K2(px[dghtr2],py[dghtr2],pz[dghtr2]);
			Mother f0(K1,K2);
			Float_t f0mass=f0.GetMass_m(5,5);

			Double_t	etaK1=K1.GetEta(),
					etaK2=K2.GetEta();
			Double_t	phiK1=K1.GetPhi(),
					phiK2=K2.GetPhi();
			h_delta_eta->Fill(etaK1-etaK2);
			h_delta_phi->Fill(phiK1-phiK2);

			Int_t	pion_idK1[4];  // IDs of daughter pions of K1
			Int_t	pion_idK2[4];  // IDs of daughter pions of K2
			Int_t	nr_pi1=0;
			Int_t	nr_pi2=0;
			Int_t	fmckinK1=fmckin_id[dghtr1];
			Int_t	fmckinK2=fmckin_id[dghtr2];

			// loping over true particles to find charged daughters of
			// kaons from f0
			for (int i=0;i<ntrue;i++)
			{
				Int_t 	mum_i=daug_of[i];
				Int_t	fmcprt_i=fmcprt[i];

				if ((mum_i==fmckinK1)&&((fmcprt_i==54)||(fmcprt_i==55)))
				{
					pion_idK1[nr_pi1]=i;
					nr_pi1++;
				}
				if ((mum_i==fmckinK2)&&((fmcprt_i==54)||(fmcprt_i==55)))
				{
					pion_idK2[nr_pi2]=i;
					nr_pi2++;
				}
			}

			//cout<<"1st K0s has "<<nr_pi1<<" charged daughters; 2nd: "<<nr_pi2<<endl;

			if ((nr_pi1!=2)||(nr_pi2!=2)) continue;
			//cout<<"Found f0->2K0s->4pi "<<f0mass<<endl;
			h_f0mass->Fill(1000*f0mass);
			nf04pi++;

			// true pions
			Int_t	pi1K1_id=pion_idK1[0];
			Int_t	pi2K1_id=pion_idK1[1];
			Int_t	pi1K2_id=pion_idK2[0];
			Int_t	pi2K2_id=pion_idK2[1];

			Daughter	pi1K1(px[pi1K1_id],py[pi1K1_id],pz[pi1K1_id]);
			Daughter	pi2K1(px[pi2K1_id],py[pi2K1_id],pz[pi2K1_id]);
			Daughter	pi1K2(px[pi1K2_id],py[pi1K2_id],pz[pi1K2_id]);
			Daughter	pi2K2(px[pi2K2_id],py[pi2K2_id],pz[pi2K2_id]);

			// Now try to match true pions from K0s to reconstructed ones
			Double_t	dv0min=99;
			Double_t	dmin=99;
			Int_t		matchedK01=-1;
			Int_t		matchedK02=-1;

			// looping over reconstructed K0s candidates and matching to FIRST
			// true K0s  (K1 in our variables convention)
			//cout<<"Matching first true K0"<<endl;
			for (int n=0;n<nv0;n++)
			{
				Daughter pi1n(p1[n][0],p1[n][1],p1[n][2]);
				Daughter pi2n(p2[n][0],p2[n][1],p2[n][2]);


				// pi1K1<->pi1n, pi2K1<->pi2n (11, 22)
				Double_t	phi11=pi1K1.GetPhi()-pi1n.GetPhi();
				Double_t	phi22=pi2K1.GetPhi()-pi2n.GetPhi();
				Double_t	eta11=pi1K1.GetEta()-pi1n.GetEta();
				Double_t	eta22=pi2K1.GetEta()-pi2n.GetEta();
				Double_t	p11=pi1K1.GetP()-pi1n.GetP();
				Double_t	p22=pi2K1.GetP()-pi2n.GetP();
				// pi1K1<->pi2n, pi2K1<->pi1n (12, 21)
				Double_t	phi12=pi1K1.GetPhi()-pi2n.GetPhi();
				Double_t	phi21=pi2K1.GetPhi()-pi1n.GetPhi();
				Double_t	eta12=pi1K1.GetEta()-pi2n.GetEta();
				Double_t	eta21=pi2K1.GetEta()-pi1n.GetEta();
				Double_t	p12=pi1K1.GetP()-pi2n.GetP();
				Double_t	p21=pi2K1.GetP()-pi1n.GetP();

				Double_t	d_comb_min=100;
				Double_t	d11_22=0,
						d12_21=0;
		d11_22=sqrt(phi11*phi11+phi22*phi22+eta11*eta11+eta22*eta22+p11*p11+p22*p22);
		d12_21=sqrt(phi12*phi12+phi21*phi21+eta12*eta12+eta21*eta21+p12*p12+p21*p21);

				if (d11_22<d12_21)
				{
					d_comb_min=d11_22;
				}
				if (d11_22>d12_21)
				{
					d_comb_min=d12_21;
				}
				//cout<<"reco K0 Nr "<<n<<" : "<<d11_22<<" "<<d12_21<<" "<<endl;

				if (d_comb_min<dv0min)
				{
					dv0min=d_comb_min;
				}

				if (dv0min<=0.2) matchedK01=n;
			}

			//h_dv0min->Fill(dv0min);

			//------------------------------------------------//
			// looping over reconstructed K0s candidates and matching to SECOND
			// true K0s  (K2 in our variables convention)
			dv0min=99;
			for (int n=0;n<nv0;n++)
			{
				Daughter pi1n(p1[n][0],p1[n][1],p1[n][2]);
				Daughter pi2n(p2[n][0],p2[n][1],p2[n][2]);

				//11, 22
				Double_t	phi11=pi1K2.GetPhi()-pi1n.GetPhi();
				Double_t	phi22=pi2K2.GetPhi()-pi2n.GetPhi();
				Double_t	eta11=pi1K2.GetEta()-pi1n.GetEta();
				Double_t	eta22=pi2K2.GetEta()-pi2n.GetEta();
				Double_t	p11=pi1K2.GetP()-pi1n.GetP();
				Double_t	p22=pi2K2.GetP()-pi2n.GetP();
				//12, 21
				Double_t	phi12=pi1K2.GetPhi()-pi2n.GetPhi();
				Double_t	phi21=pi2K2.GetPhi()-pi1n.GetPhi();
				Double_t	eta12=pi1K2.GetEta()-pi2n.GetEta();
				Double_t	eta21=pi2K2.GetEta()-pi1n.GetEta();
				Double_t	p12=pi1K2.GetP()-pi2n.GetP();
				Double_t	p21=pi2K2.GetP()-pi1n.GetP();

				Double_t	d_comb_min=100;
				Double_t	d11_22=0,
								d12_21=0;
		d11_22=sqrt(phi11*phi11+phi22*phi22+eta11*eta11+eta22*eta22+p11*p11+p22*p22);
		d12_21=sqrt(phi12*phi12+phi21*phi21+eta12*eta12+eta21*eta21+p12*p12+p21*p21);

				if (d11_22<d12_21)
				{
					d_comb_min=d11_22;
				}
				if (d11_22>d12_21)
				{
					d_comb_min=d12_21;
				}
				//cout<<d11_22<<" "<<d12_21<<" "<<endl;

				if (d_comb_min<dv0min)
				{
					dv0min=d_comb_min;
				}

				if (dv0min<=0.2) matchedK02=n;
			}
			//------------------------------------//

			//cout<<"Matching results: "<<matchedK01<<" "<<matchedK02<<endl;
			if ((matchedK01>0)&&(matchedK02>0)&&(matchedK01!=matchedK02))
			{
				match++;
			}
			if (matchedK01>0)
			{
				cout<<"matched K1, "<<endl;
			Daughter	match_pi1(p1[matchedK01][0],p1[matchedK01][1],p1[matchedK01][2]);
			Daughter	match_pi2(p2[matchedK01][0],p2[matchedK01][1],p2[matchedK01][2]);
				Mother		match_K1(match_pi1,match_pi2);
				cout<<"Reco Mass is "<<1000*match_K1.GetMass_m(4,4)<<endl;
			}
			if (matchedK02>0)
			{
				cout<<"matched K2, "<<endl;
			Daughter	match_pi1(p1[matchedK02][0],p1[matchedK02][1],p1[matchedK02][2]);
			Daughter	match_pi2(p2[matchedK02][0],p2[matchedK02][1],p2[matchedK02][2]);
				Mother		match_K2(match_pi1,match_pi2);
				cout<<"Reco Mass is "<<1000*match_K2.GetMass_m(4,4)<<endl;
			}



		}



	}





	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/fmcprt_v2.root","recreate");
	h_fmcprt->Write();
	h_f0mass->Write();
	//h_f0mass1->Write();
	h_delta_eta->Write();
	h_delta_phi->Write();
	//---

	h_phi1->Write();
	h_phi2->Write();

	h_phi1_min->Write();
	h_phi2_min->Write();
	h_dv0min->Write();
	h_f0mass_reco->Write();


	f2->Close();
	cout<<nf0<<" f0(980)"<<endl;
	cout<<nf0K0K0<<" f0(980)->K0K0"<<endl;
	cout<<nf04pi<<" f0(980)->K0K0->4pi"<<endl;
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



