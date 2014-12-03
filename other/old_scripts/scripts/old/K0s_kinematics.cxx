#include <Daughter.cxx>
#include <Mother.cxx>

int main()
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
			Siq2el[10],
			reso_mass=0,
			Tp1[50][3],
			Tp2[50][3],
			Tpk[50][3],
			Trk_px[300],
			Trk_py[300],
			Trk_pz[300];
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300];

	//initializating
	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/data/2004/*.root");
	myChain->Add("/data/zenith226a/libov/data/2005new/*.root");
	myChain->Add("/data/zenith226a/libov/data/2006/*.root");
	myChain->Add("/data/zenith226a/libov/data/2007/*.root");


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
	myChain->SetBranchAddress("Trk_px",Trk_px);
	myChain->SetBranchAddress("Trk_py",Trk_py);
	myChain->SetBranchAddress("Trk_pz",Trk_pz);
	//Sira, Si_kin
	myChain->SetBranchAddress("Sincand",&Sincand);
	myChain->SetBranchAddress("Siq2el",Siq2el);

	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	//histograms declaring
	Float_t		histRangeLow=440,
			histRangeUp=550,
			histRange=histRangeUp-histRangeLow;
	Float_t 	bin_width=1.5;
	Int_t 		nbins=(Int_t)histRange/bin_width;
	bin_width=(Float_t)histRange/nbins;
 	cout<<"hist  bin_width   nbins"<<endl;
	cout<<"hinv_base: "<<bin_width<<"  "<<nbins<<endl;
	TH1F *hinv_base=new TH1F("hinv_base","K0s invariant mass (1.5 MeV/bin)",nbins,histRangeLow,histRangeUp);
	TH1F *hpt=new TH1F("hpt","transverse momenta distribution",100,0,10);
	TH1F *heta=new TH1F("heta","pseudorapidity distribution",50,-4,4);
	gStyle->SetOptFit(1111);

	//main loop
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==1000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
	       	}
        	goa++;
		myChain->GetEntry(i);
		for(Int_t j=0;j<Nv0lite;j++)
		{
			Daughter t1(Tp1[j][0],Tp1[j][1],Tp1[j][2]);
			Daughter t2(Tp2[j][0],Tp2[j][1],Tp2[j][2]);
			Mother K0s_cand(t1,t2);
			//cuts
			Float_t p1=t1.GetP();
			Float_t p2=t2.GetP();
			Float_t mass_pi_p=0;

			if (p1>p2)  //first track proton(antiproton); second track pion_minus(pion_plus)
			{
				mass_pi_p=K0s_cand.GetMass_m(6,4);
			}
			if (p1<p2) //first track pion_minus(pion_plus); first track proton(antiproton);
			{
				mass_pi_p=K0s_cand.GetMass_m(4,6);
			}
			if (Tsecvtx_collin2[j]>0.1) continue;
			if (Tsecvtx_collin3[j]>0.2) continue;
			if (mass_pi_p<1.125) continue;
			if (Tinvmass_ee[j]<0.05) continue;
			bool itake=true;
			Int_t 		take1=1,
					take2=1;
			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (idx == Tt1_id[j])
				{
					take1=Trk_prim_vtx[n];
					continue;
				}
                		if (idx == Tt2_id[j])
				{
					take2=Trk_prim_vtx[n];
					continue;
				}
        		}
       			if ((take1==1)||(take2==1)) continue;
			if ((K0s_cand.GetMass_m(4,4)<0.47)||(K0s_cand.GetMass_m(4,4)>0.5254)) continue;
			//histograms filling
			heta->Fill(K0s_cand.GetEta_m());
			hpt->Fill(1.005*K0s_cand.GetPt_m());
			hinv_base->Fill(1000*K0s_cand.GetMass_m(4,4));
		}
	}



	TFile *f1 =new TFile("/data/zenith226a/libov/results/recent/K0s_kinematics_fullsample.root","new");
	heta->Write();
	hpt->Write();
	hinv_base->Draw();
	f1->Close();
	cout<<"OK"<<endl;
	return 0;
}
