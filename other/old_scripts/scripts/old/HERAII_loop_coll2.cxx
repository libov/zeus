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
void HERAII()
{

	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/results/mostrecent/HERAII_without05.root");
	myChain->Add("/data/zenith226a/libov/results/mostrecent/HERAII_2005noRTfit.root");
	//myChain->Add("/data/zenith226a/libov/results/mostrecent/HERAII_all_05oncemore.root");
	Int_t		nv0=0,		// number K0s candidates that passed soft selection
			id1[10],	// id of the first track
			id2[10];	// id of the second track
	Float_t		p1[10][3],	// momenta of 1st track
			p2[10][3],	// momenta of 2nd track
			coll2[10],	// collinearity angle 2D
			coll3[10];	// collinearity angle 3D
	Float_t		angle=0,
			cos_angle=0;
	myChain->SetBranchAddress("nv0",&nv0);
	myChain->SetBranchAddress("p1",p1);
	myChain->SetBranchAddress("p2",p2);
	myChain->SetBranchAddress("coll2",coll2);
	myChain->SetBranchAddress("coll3",coll3);
	myChain->SetBranchAddress("id1",id1);
	myChain->SetBranchAddress("id2",id2);
	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<" events here"<<endl;

	Float_t		corr=1.005;
	TH1F *h=new TH1F("h","K0sK0s",200,0.8,5);
	TH1F *hd1=new TH1F("hd1","debug1",20,0,20);
	TH1F *hd2=new TH1F("hd2","debug2",20,0,20);
	TH1F *ha=new TH1F("ha","angle between two K0s ",100,0,180);
	TH1F *hfake=new TH1F("hfake","",200,0.8,5);
	TH1F *hinv_base=new TH1F("hinv_base",">=2 K0s",60,450,552);
	TH1F *hinv1=new TH1F("hinv1","K0s",60,450,552);
	Int_t goa=0;
	Float_t reso_mass=0;
	for (Int_t i=0;i<nevents;i++)
	{
		myChain->GetEntry(i);
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		Int_t	cand_k0=0,
			list_k0[30];

		//K0s cand selection
		for(Int_t k=0;k<nv0;k++)
		{
			hd1->Fill(1);
			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
			Mother K0s_cand(t1,t2);
			Float_t pabs1=t1.GetP();
			Float_t pabs2=t2.GetP();
			Float_t mass_pi_p=0;
			if (pabs1>pabs2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (pabs1<pabs2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}
			if(mass_pi_p<1.125) continue;
			hd1->Fill(2);
			if(K0s_cand.GetPt_m()<0.3) continue;
			hd1->Fill(3);
			if (TMath::Abs(K0s_cand.GetEta_m())>1.5) continue;
			hd1->Fill(4);
			if (coll2[k]>0.1) continue;
			hd1->Fill(5);
			hinv1->Fill(1000*K0s_cand.GetMass_m(4,4));
			if ((K0s_cand.GetMass_m(4,4)<0.485)||(K0s_cand.GetMass_m(4,4)>0.5103)) continue;
			hd1->Fill(6);
			list_k0[cand_k0]=k;
			cand_k0++;
		}

		//K0s combining
		if (cand_k0<2) continue;
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t id=list_k0[k];
			Daughter t1temp(corr*p1[id][0],corr*p1[id][1],corr*p1[id][2]);
			Daughter t2temp(corr*p2[id][0],corr*p2[id][1],corr*p2[id][2]);
			Mother K0s_candtemp(t1temp,t2temp);
			hinv_base->Fill(1000*K0s_candtemp.GetMass_m(4,4));
		}
		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{

				Int_t 		k01=list_k0[k],
						k02=list_k0[l];
				Int_t 		id1k=id1[k01],
						id2k=id2[k01],
						id1l=id1[k02],
						id2l=id2[k02];
				hd2->Fill(1);
				if ((id1k==id1l)||(id1k==id2l)||(id2k==id1l)||(id2k==id2l)) continue;
				hd2->Fill(2);
				Float_t		px1=corr*(p1[k01][0]+p2[k01][0]),
						py1=corr*(p1[k01][1]+p2[k01][1]),
						pz1=corr*(p1[k01][2]+p2[k01][2]),

						px2=corr*(p1[k02][0]+p2[k02][0]),
						py2=corr*(p1[k02][1]+p2[k02][1]),
						pz2=corr*(p1[k02][2]+p2[k02][2]);
				Daughter K0s_cand1(px1,py1,pz1);
				Daughter K0s_cand2(px2,py2,pz2);
				cos_angle=(px1*px2+py1*py2+pz1*pz2)/(sqrt((px1*px1+py1*py1+pz1*pz1)*(px2*px2+py2*py2+pz2*pz2)));
				angle=acos(cos_angle);
				ha->Fill(angle*57);
				Mother K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);
				if (cos_angle>0.98)
				{
					hfake->Fill(reso_mass);
					continue;
				}
				hd2->Fill(3);
    				h->Fill(reso_mass);
			}
		}
	}
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/mostrecent/K0sK0s_HERAIIcos092.root","recreate");
	TFile *f1 =new TFile("/data/zenith226a/libov/results/mostrecent/K0sK0s_HERAIIcos098.root","recreate");
	h->Write();
	hd1->Write();
	hd2->Write();
	ha->Write();
	hinv_base->Write();
	hinv1->Write();
	f1->Close();
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	HERAII();
	return 0;
}
#endif

