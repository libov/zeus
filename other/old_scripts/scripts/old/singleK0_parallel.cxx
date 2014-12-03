#include <myParticle.cxx>
#include <motherParticle.cxx>

int main(Float_t bin_width=1.5)
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

	TChain *myChain=new TChain("resonance");
	//myChain->Add("/data/zenith226a/libov/data/2004/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2005/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2006/*.root");
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

	Float_t	histRangeLow=440,
		histRangeUp=550,
		histRange=histRangeUp-histRangeLow;
	Int_t nbins=(Int_t)(histRangeUp-histRangeLow)/bin_width;
	bin_width=(Float_t)(histRangeUp-histRangeLow)/nbins;
	cout<<"hist  bin  width   nbins"<<endl;
	cout<<"hinv_base: "<<bin_width<<"  "<<nbins<<endl;
	cout<<"hinv_1:    "<<histRange/(nbins/2)<<"  "<<nbins/2<<endl;
	cout<<"hinv_2:    "<<histRange/(nbins*2)<<"  "<<nbins*2<<endl;
	cout<<"hinv_3:    "<<histRange/(nbins*1.5)<<"  "<<nbins*1.5<<endl;
	cout<<"hinv_4:    "<<histRange/(nbins/1.5)<<"  "<<nbins/1.5<<endl;

	TH1F *hinv_base=new TH1F("hinv_base","k0s invariant mass (1.5 MeV/bin)",nbins,histRangeLow,histRangeUp);
	TH1F *hinv_1=new TH1F("hinv_1","k0s invariant mass (3 MeV/bin)",(Int_t)nbins/2,histRangeLow,histRangeUp);
	TH1F *hinv_2=new TH1F("hinv_2","k0s invariant mass (0.75 MeV/bin)",2*nbins,histRangeLow,histRangeUp);
	TH1F *hinv_3=new TH1F("hinv_3","k0s invariant mass (1 MeV/bin)",(Int_t)(1.5*nbins),histRangeLow,histRangeUp);
	TH1F *hinv_4=new TH1F("hinv_4","k0s invariant mass (2.26 MeV/bin)",(Int_t)nbins/1.5,histRangeLow,histRangeUp);

	TH1F *hinv0=new TH1F("hinv0","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv1=new TH1F("hinv1","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv2=new TH1F("hinv2","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv3=new TH1F("hinv3","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv4=new TH1F("hinv4","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv5=new TH1F("hinv5","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv6=new TH1F("hinv6","k0s invariant mass",nbins,histRangeLow,histRangeUp);
	TH1F *hinv7=new TH1F("hinv7","k0s invariant mass",nbins,histRangeLow,histRangeUp);

	TH2F *h2d=new TH2F("h2d","yo",50,200,800,40,1050,1400);
	TH1F *hdebug=new TH1F("hdebug","Debug Histogram",20,0,20);
	gStyle->SetOptFit(1111);

	for(Int_t i=0;i<nevents;i++)
	{
		if (goa==5000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
			continue;
        	}
        	goa++;
		myChain->GetEntry(i);
		for(Int_t j=0;j<Nv0lite;j++)
		{
			//cuts here applied in parallel - in order to take into account possible cuts correlations
			//during their optimization
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
			h2d->Fill(1000*Tinvmass_k0[j],1000*mass_pi_p);
			hdebug->Fill(0);
			hinv0->Fill((K0s_cand.GetMass())*1000);
			if (Tsecvtx_collin2[j]<0.1)
			{
				hdebug->Fill(1);
				hinv1->Fill((K0s_cand.GetMass())*1000);
			}
			if (mass_pi_p>1.125)
			{
				hdebug->Fill(2);
				hinv2->Fill((K0s_cand.GetMass())*1000);
			}
			if (Tinvmass_ee[j]>0.05)
			{
				hdebug->Fill(3);
				hinv3->Fill((K0s_cand.GetMass())*1000);
			}
			if ((K0s_cand.GetPt())>0.3)
			{
				hdebug->Fill(4);
				hinv4->Fill((K0s_cand.GetMass())*1000);
			}
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
			if ((take1!=1)&&(take2!=1))
			{
				hdebug->Fill(5);
				hinv5->Fill((K0s_cand.GetMass())*1000);
			}
			if (Tsecvtx_collin3[j]<0.2)
			{
				hdebug->Fill(6);
				hinv6->Fill((K0s_cand.GetMass())*1000);
			}
			if (TMath::Abs(K0s_cand.GetEta())<1.5)
			{
				hdebug->Fill(7);
				hinv7->Fill((K0s_cand.GetMass())*1000);
			}

			//here cuts are applied consequently - to get clean signal
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
			if (TMath::Abs(K0s_cand.GetEta())>1.5) continue;
			hinv_base->Fill((K0s_cand.GetMass())*1000);
			hinv_1->Fill((K0s_cand.GetMass())*1000);
			hinv_2->Fill((K0s_cand.GetMass())*1000);
			hinv_3->Fill((K0s_cand.GetMass())*1000);
			hinv_4->Fill((K0s_cand.GetMass())*1000);

		}
	}


	//TFile f1("part_05_CutEval.root","new");
	//TFile *f1 =new TFile("fullest_eta1_5_04.root","new");
	//TFile *f1 =new TFile("05_eta15_corr1.003.root","new");
	TFile *f1 =new TFile("full_07.root","new");

	hinv_base->Write();
	hinv_1->Write();
	hinv_2->Write();
	hinv_3->Write();
	hinv_4->Write();
	hinv0->Write();
	hinv1->Write();
	hinv2->Write();
	hinv3->Write();
	hinv4->Write();
	hinv5->Write();
	hinv6->Write();
	hinv7->Write();
	hdebug->Write();
	f1->Close();

	cout<<"OK"<<endl;
	return 0;
}
