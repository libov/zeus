#include <myParticle.cxx>
#include <motherParticle.cxx>

Double_t db_gaus_pol1(Double_t *x,Double_t *par)
{
	Double_t 	gaus1=0,
			gaus2=0,
			pol1=0;
	gaus1=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gaus2=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[4]*par[4]));
	pol1=par[5]+par[6]*x[0];
	return gaus1+gaus2+pol1;
}

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
	float		Trk_charge[300];

	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/data/2004/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2005/*.root");

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
	myChain->SetBranchAddress("Trk_charge",Trk_charge);
	//Sira, Si_kin
	myChain->SetBranchAddress("Sincand",&Sincand);
	myChain->SetBranchAddress("Siq2el",Siq2el);

	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;


	TH1F *hdouble=new TH1F("hdouble","K0s+pion_plus invariant mass spectra",180,0.5,2.5);
	gStyle->SetOptFit(1111);

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
			continue;
        	}
        	goa++;
		myChain->GetEntry(i);
		Int_t	cand_k0=0,
			list_k0[30];
		for(Int_t z=0;z<30;z++) list_k0[z]=0;

		// K0s selecting
		//if (Nv0lite<=1) continue;
		for(Int_t j=0;j<Nv0lite;j++)
		{
			myParticle K0s_cand(Tpk[j][0],Tpk[j][1],Tpk[j][2],Tinvmass_k0[j],1);
			myParticle t1(Tp1[j][0],Tp1[j][1],Tp1[j][2],0,1);
			myParticle t2(Tp2[j][0],Tp2[j][1],Tp2[j][2],0,1);
			Float_t p1=t1.GetP();
			Float_t p2=t2.GetP();
			Float_t mass_pi_p=0;
			if (p1>p2)
			{
				if (Tq1[j]>0) mass_pi_p=Tinvmass_lambda[j];
				if (Tq2[j]>0) mass_pi_p=Tinvmass_alambda[j];
			}
			if (p1<p2)
			{
				if (Tq1[j]>0) mass_pi_p=Tinvmass_alambda[j];
				if (Tq2[j]>0) mass_pi_p=Tinvmass_lambda[j];
			}
			if (Tsecvtx_collin2[j]>0.1) continue;
			if (mass_pi_p<1.125) continue;
			if (Tinvmass_ee[j]<0.05) continue;
			if ((K0s_cand.GetPt())<0.3) continue;
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
       			//if (itake == false) continue;
			if ((take1==1)||(take2==1)) continue;
			if (Tsecvtx_collin3[j]>0.2) continue;
			if (TMath::Abs(K0s_cand.GetEta())>1.2) continue;
			if ((K0s_cand.GetMass()<0.47)&&(K0s_cand.GetMass()>0.522)) continue;
			list_k0[cand_k0]=j;
			cand_k0++;
		} //end k0 selecting

		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t 	k0=list_k0[k];
			Int_t 	id1=Tt1_id[k0],
				id2=Tt2_id[k0];
			myParticle K0s_cand1(Tpk[k0][0],Tpk[k0][1],Tpk[k0][2],Tinvmass_k0[k0],1);
			for (Int_t n=0; n<Trk_ntracks; n++)
			{
				unsigned int idx=Trk_id[n];
				if (Trk_prim_vtx[n]==1)
				{
					if ((id1!=idx)&&(id2!=idx)&&(Trk_charge[n]==1))
						{
							myParticle pion_cand(Trk_px[n],Trk_py[n],Trk_pz[n],0,4);
							motherParticle *Kstar=new motherParticle(K0s_cand1,pion_cand);
							reso_mass=Kstar->GetMass_m();
							hdouble->Fill(reso_mass);
						}
				}

        		}
		}
	}
	hdouble->Draw();
	cout<<"OK"<<endl;
	return 0;
}
