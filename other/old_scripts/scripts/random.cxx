// Generating random momenta
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//            National University of Kiev       //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////

#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
#include <TRandom3.h>
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
	//TF1 *uniform=new TF1("")
	TRandom		*uni=new TRandom();
	TRandom3	*uni3=new TRandom3();
	TH1F *h_uni=new TH1F("h_uni","",100,0,6);
	TH1F *h_inv=new TH1F("h_inv","",5000,250,750);
	TH1F *h_p1=new TH1F("h_p1","",100,0,5);
	TH1F *h_p1calc=new TH1F("h_p1calc","",100,0,5);

	Double_t	minp=0.1,
			maxp=5,
			mintheta=0,
			maxtheta=TMath::Pi(),
			minphi=0,
			maxphi=2*TMath::Pi();
	Double_t	tau=1;
	Int_t	goa=0;
	for (int k=0;k<1000000;k++)
	{
		//h_uni->Fill(uni->Uniform(0.1,5));
		//Double_t	p1=uni->Uniform(minp,maxp),
		//		p2=uni->Uniform(minp,maxp);

		if (goa==100000)
        	{
        		cout<<k<<" events processed"<<endl;
			goa=0;
		}
		goa++;
		Double_t	p1=uni->Exp(tau),
				p2=uni->Exp(tau);
		if ((p1<0.1)||(p2<0.1)) continue;

		Double_t	theta1=uni->Uniform(mintheta,maxtheta),
				phi1=uni->Uniform(minphi,maxphi),
				theta2=uni->Uniform(mintheta,maxtheta),
				phi2=uni->Uniform(minphi,maxphi);

		Double_t	px1=p1*(TMath::Cos(theta1))*(TMath::Cos(phi1)),
				py1=p1*(TMath::Cos(theta1))*(TMath::Sin(phi1)),
				pz1=p1*(TMath::Sin(theta1));
		Double_t	px2=p2*(TMath::Cos(theta2))*(TMath::Cos(phi2)),
				py2=p2*(TMath::Cos(theta2))*(TMath::Sin(phi2)),
				pz2=p2*(TMath::Sin(theta2));

		Daughter	t1(px1,py1,pz1),
				t2(px2,py2,pz2);
		h_p1->Fill(p1);
		//h_p1calc->Fill(t1.GetP());
		Mother		K0(t1,t2);
		h_inv->Fill(1000*K0.GetMass_m(4,4));
	}

	//cout<<uni->Exp(1)<<endl;
	TFile *frandom=new TFile("/data/zenith226a/libov/results/K0sK0s_hist/random.root","recreate");
	//h_uni->Write();
	h_inv->Write();
	h_p1->Write();
	//h_p1calc->Write();
	frandom->Close();

}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

