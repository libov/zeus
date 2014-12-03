//////////////////////////////////////////////////
//////////////   K0s   analysis  /////////////////
//////////////    with V0lite    /////////////////
//////////////      (part1)      /////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////
//////////                             ///////////
////////// Part1: peparing small trees ///////////
//////////                             ///////////
//////////////////////////////////////////////////
//                                              //
//   1. Event selection                         //
//   2. K0s selection (loose)                   //
//   3. Writing data to small tree              //
//      easy to analyze                         //
//                                              //
//////////////////////////////////////////////////
//  Modified 05 September: add true info
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
	Int_t		goa=0,
			nevents=0,
			Nv0lite=0;

	// This is for standard FMCKIN block in orange

	Int_t		Npart,			// number of true particles
			Part_prt[1000],		// Particle code FMCPRT
			Part_id[1000];		// Particle ID


	TChain *myChain=new TChain("orange");

gSystem->Load("libzio.so");
gSystem->Load("libdcap.so");
//------------------------------------------------------------------------------------------//
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0074.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0075.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0076.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0077.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0078.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0079.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0080.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0081.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0082.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0083.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0084.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0085.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0086.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0087.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0088.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0089.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0090.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0091.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0092.root");
myChain->Add("zeus://acs/mc/ntup/05/v01/dijetPHP/root/dwxe25.f13548.lfres.e0506.uncut_0093.root");
//input

//------------------------------------------------------------------------------------------//

	// FMCKIN (Standard orange block)
	myChain->SetBranchAddress("Npart",&Npart);
	myChain->SetBranchAddress("Part_prt",&Part_prt);
	myChain->SetBranchAddress("Part_id",&Part_id);

	cout<<"Calculating number of events..."<<endl;
	nevents=myChain->GetEntries();
	//nevents=10000;
	cout<<nevents<<" events in this chain..."<<endl;

	// TREE VARIABLES DEFINITION

	Int_t		ntrue=0,	//  Number of stored (e.g. those survived pT cut)
					//  FMCKIN particles
			fmcprt[50];	//  FMCPRT

	Int_t		fmckin_id[50];	// FMCKIN ID of the particle
	Float_t		px[50],	// px of the particle
			py[50],	// py of the particle
			pz[50];	// pz of the particle
	//-------------------------------------------------------------------------------------------//
	Int_t		err=0;
	Int_t		with_V0=0,
			ev_pass_DIS=0;
	TH1F *hdebug=new TH1F("hdebug","",10,0,10);

	TTree *tree=new TTree("resonance","FMCKIN block ORANGE");

	tree->Branch("ntrue",&ntrue,"ntrue/I");

//------ Loop over events -------//

	char	name[256];
	Int_t	file_num=0;
	bool	fire;
	cout<<"Start looping..."<<endl;
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;

		myChain->GetEntry(i);

		bool		kshort=false,
				pi_plus=false,
				pi_minus=false,
				pi=false,
				f0_980=false,
				a0_980=false,
				f2_1270=false,
				a2=false,
				f2_1525=false,
				f0_1590=false,
				a0=false,
				daug_of_kshort=false;
		ntrue=0;

		for (int k=0;k<Npart;k++)
		{
			// particle (index k) identification
			kshort=false,
			pi_plus=false;
			pi_minus=false;
			pi=false;
			f0_980=false;
			a0_980=false;
			f2_1270=false;
			a2=false;
			f2_1525=false;
			f0_1590=false;

			kshort=(Part_prt[k]==62);
			pi_plus=(Part_prt[k]==54);
			pi_minus=(Part_prt[k]==55);
			pi=(pi_plus||pi_minus);
			f0_980=(Part_prt[k]==81);
			a0_980=(Part_prt[k]==84);
			f2_1270=(Part_prt[k]==93);
			a2=(Part_prt[k]==101);
			f2_1525=(Part_prt[k]==105);
			f0_1590=(Part_prt[k]==107);

			if (f0_980||f2_1270||a2||f2_1525||f0_1590||a0_980)
			{
				fmcprt[ntrue]=Part_prt[k];
				ntrue++;
			}
		}

		tree->Fill();

	}
//------- End of events loop ---------//

	tree->Print();

Int_t temp=sprintf(name,"batch23.root");//output


	TFile *f2 =new TFile(name,"recreate");
	cout<<"File created"<<endl;
	tree->Write();
	cout<<"Tree wrote"<<endl;
	f2->Close();
	cout<<"File Closed"<<endl;
	delete tree;
	cout<<"Tree deleted, O.K.!"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif
