//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                  April 2008                  //
//                                              //
//                                              //
//////////////////////////////////////////////////

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
			Trk_id[300],
			Tt1_layout[80],
			Tt2_layout[80];
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
			Siprob[10],
			Trk_px[300],
			Trk_py[300],
			Trk_pz[300];
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


	Float_t		Xvtx=0,
			Yvtx=0,
			Zvtx=0;

	TChain *myChain=new TChain("resonance");
	// PATH to NTUPLES

	myChain->Add("/data/zenith226a/libov/data/2004_stt/*.root");


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
	myChain->SetBranchAddress("Tt1_layout",Tt1_layout);
	myChain->SetBranchAddress("Tt2_layout",Tt2_layout);

	// Tracking, Trk_vtx
	myChain->SetBranchAddress("Trk_ntracks",&Trk_ntracks);
	myChain->SetBranchAddress("Trk_id",Trk_id);
	myChain->SetBranchAddress("Trk_prim_vtx",Trk_prim_vtx);
	myChain->SetBranchAddress("Trk_sec_vtx",Trk_sec_vtx);
	myChain->SetBranchAddress("Trk_vtx",Trk_vtx);
	myChain->SetBranchAddress("Trk_px",Trk_px);
	myChain->SetBranchAddress("Trk_py",Trk_py);
	myChain->SetBranchAddress("Trk_pz",Trk_pz);
	//Vertex
	myChain->SetBranchAddress("Xvtx",&Xvtx);
	myChain->SetBranchAddress("Yvtx",&Yvtx);
	myChain->SetBranchAddress("Zvtx",&Zvtx);
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
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;


	TH1F *hpolar=new TH1F("hpolar","Polar track multiplicity distribution",200,-5,5);
//------ Loop over events -------//
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<"  Runnr:"<<Runnr<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);

		for (int k=0;k<Trk_ntracks;k++)
		{
			Daughter	t1(Trk_px[k],Trk_py[k],Trk_pz[k]);
			Float_t		eta=t1.GetEta();
			hpolar->Fill(eta);
		}
	}
//------- End of events loop ---------///

	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/forward.root","recreate");
	hpolar->Write();
	f2->Close();
	cout<<"Done!!!"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif

