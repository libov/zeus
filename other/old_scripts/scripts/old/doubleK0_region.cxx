// K0sK0s analysing...
// Libov Vladyslav
// Kiev National University
// 05.11.2007
#include <myParticle.cxx>
#include <motherParticle.cxx>
#include <motherParticleNew.cxx>

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
			Tpk[50][3];
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300],
			Runnr=0,
			corr=0,
			year=0;
	const Int_t 	low_2004=47010,
			up_2004=51245,
			low_2005=52244,
			up_2005=57123,
			low_2006=58181,
			up_2006=59947,
			low_2007=61747,
			up_2007=62638,
			corr_2004=1.005,
			corr_2005=1.009,
			corr_2006=1.0077,
			corr_2007=1.0065;
	Float_t 	eta_bin[10]; 	// 1st bin: eta_bin[0]<eta<eta_bin[1];
					// 2nd bin: eta_bin[1]<eta<eta_bin[2];  and so on...

	eta_bin[0]=-3;
	eta_bin[1]=-0.5;
	eta_bin[2]=0.5;
	eta_bin[3]=3;


	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/data/2004/*.root");
	myChain->Add("/data/zenith226a/libov/data/2005/*.root");
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
	//Sira, Si_kin
	myChain->SetBranchAddress("Sincand",&Sincand);
	myChain->SetBranchAddress("Siq2el",Siq2el);
	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);
	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	TFile *f1 =new TFile("histograms.root/K0sK0s_eta_region_new_stat.root","new");
	gStyle->SetOptFit(1111);

	TClonesArray 	h1("TH1F",5),
			h2("TH1F",5),
			h3("TH1F",5);
	for(Int_t i=0;i<3;i++)
	{
		char t[30];
		sprintf(t,"h1_%d",i);
		new(h1[i]) TH1F(t,"K0sK0s  0.47<M(K0s)<0.5254  28.6 Mev/bin",150,0.8,5);
		sprintf(t,"h2_%d",i);
		new(h2[i]) TH1F(t,"K0sK0s  0.475<M(K0s)<0.5204  28.6 Mev/bin",150,0.8,5);
		sprintf(t,"h3_%d",i);
		new(h3[i]) TH1F(t,"K0sK0s  0.48<M(K0s)<0.5154  28.6 Mev/bin",150,0.8,5);
	}
	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==500000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
			continue;
        	}
        	goa++;
		myChain->GetEntry(i);
		if  ((Runnr>=low_2004)&&(Runnr<=up_2004)) year=2004;
		if  ((Runnr>=low_2005)&&(Runnr<=up_2005)) year=2005;
		if  ((Runnr>=low_2006)&&(Runnr<=up_2006)) year=2006;
		if  ((Runnr>=low_2007)&&(Runnr<=up_2007)) year=2007;

		switch (year)
		{
			case 2004: corr=corr_2004; break;
			case 2005: corr=corr_2005; break;
			case 2006: corr=corr_2006; break;
			case 2007: corr=corr_2007; break;
			case 0: {corr=1; cout<<"Error!!!!!!!!!!!! Run is UNKNOWN!!!!!!!!!!"<<endl;} break;
		}


		Int_t	cand_k0=0,
			list_k0[30];
		for(Int_t z=0;z<30;z++) list_k0[z]=0;

		// K0s selecting
		if (Nv0lite<=1) continue;
		for(Int_t j=0;j<Nv0lite;j++)
		{
			myParticle K0s_cand(corr*Tpk[j][0],corr*Tpk[j][1],corr*Tpk[j][2],Tinvmass_k0[j],1);
			myParticle t1(corr*Tp1[j][0],corr*Tp1[j][1],corr*Tp1[j][2],0,1);
			myParticle t2(corr*Tp2[j][0],corr*Tp2[j][1],corr*Tp2[j][2],0,1);
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
			if (Tsecvtx_collin2[j]>0.12) continue;
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
			//if (TMath::Abs(K0s_cand.GetEta())>1.5) continue;
			if ((K0s_cand.GetMass()<0.47)||(K0s_cand.GetMass()>0.5254)) continue;
			list_k0[cand_k0]=j;
			cand_k0++;
		} //end k0 selecting

		//k0 combining
  		for(Int_t k=0;k<cand_k0-1;k++)
		{
			for(Int_t l=k+1;l<cand_k0;l++)
			{
				Int_t 	k01=list_k0[k],
					k02=list_k0[l];
				Int_t 	id1=Tt1_id[k01],
					id2=Tt2_id[k01],
					id3=Tt1_id[k02],
					id4=Tt2_id[k02];
				//if ((Tsecvtx_collin2[k01]>collin2_cut)||(Tsecvtx_collin2[k02]>collin2_cut)) continue;
				if ((id1==id3)||(id1==id4)||(id2==id3)||(id2==id4)) continue;
				myParticle K0s_cand1(corr*Tpk[k01][0],corr*Tpk[k01][1],corr*Tpk[k01][2],Tinvmass_k0[k01],1);
				myParticle K0s_cand2(corr*Tpk[k02][0],corr*Tpk[k02][1],corr*Tpk[k02][2],Tinvmass_k0[k02],1);
				motherParticleNew K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);
				for(Int_t bin=0;bin<3;bin++)
				{
					if (((K0sK0s.GetEta_m())>eta_bin[bin])&&((K0sK0s.GetEta_m())<eta_bin[bin+1]))
					{
						((TH1F *)h1.At(bin))->Fill(reso_mass);
						if ((K0s_cand1.GetMass()<0.475)||(K0s_cand1.GetMass()>0.5204)) continue;
						if ((K0s_cand2.GetMass()<0.475)||(K0s_cand2.GetMass()>0.5204)) continue;
						((TH1F *)h2.At(bin))->Fill(reso_mass);
						if ((K0s_cand1.GetMass()<0.48)||(K0s_cand1.GetMass()>0.5154)) continue;
						if ((K0s_cand2.GetMass()<0.48)||(K0s_cand2.GetMass()>0.5154)) continue;
						((TH1F *)h3.At(bin))->Fill(reso_mass);
					}
				}

			}
		}
	}


	for(int i=0;i<3;i++)
	{
		((TH1F *)h1.At(i))->Write();
		((TH1F *)h2.At(i))->Write();
		((TH1F *)h3.At(i))->Write();
	}


	f1->Close();
	cout<<"OK"<<endl;
	return 0;
}
