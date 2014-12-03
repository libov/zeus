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

void q2()
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
			reso_mass=0,
			Tp1[50][3],
			Tp2[50][3],
			Tpk[50][3],
			corr=0,
			Siq2el[10],
			Sixel[10],
			Siyel[10],
			Siq2jb[10],
			Sixjb[10],
			Siyjb[10],
			Siq2da[10],
			Sixda[10],
			Siyda[10],
			Sizuhmom[4][10],
			Sicalpos[3][10],
			Sisrtpos[2][10],
			Sisrtene[10],
			Siecorr[3][10],
			Sith[10],
			Zvtx;
	Int_t 		Trk_prim_vtx[300],
			Trk_sec_vtx[300],
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

	Int_t		Npart,
			Part_id[300],
			Part_prt[300],
			Mcmatquality[300],
			Mcmatfmckin_id[300],
			Mcmattype[300];
	Float_t		Part_p[300][4],
			Mcmatpx[300],
			Mcmatpy[300],
			Mcmatpz[300];



	TChain *myChain=new TChain("resonance");
	// PATH to NTUPLES
	//myChain->Add("/data/zenith226a/libov/to_test/v0lite_testsample/*.root");
	//myChain->Add("/data/zenith226a/libov/data/2007pRP/*.root");
	//myChain->Add("/data/zenith226a/libov/to_test/control/*.root");
	//myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_test.root");
	//myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_TRUE.root");
	myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_TRUE_1.root");
	myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_TRUE_2.root");
	myChain->Add("/data/zenith226a/libov/to_test/v0_mini07pRPMC_TRUE_3.root");


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
	myChain->SetBranchAddress("Zvtx",&Zvtx);
	//Sira, Si_kin
	myChain->SetBranchAddress("Sincand",&Sincand);
	myChain->SetBranchAddress("Siq2el",Siq2el);
	myChain->SetBranchAddress("Siyel",Siyel);
	myChain->SetBranchAddress("Sixel",Sixel);
	myChain->SetBranchAddress("Siq2jb",Siq2jb);
	myChain->SetBranchAddress("Sixjb",Sixjb);
	myChain->SetBranchAddress("Siyjb",Siyjb);
	myChain->SetBranchAddress("Siq2da",Siq2da);
	myChain->SetBranchAddress("Sixda",Sixda);
	myChain->SetBranchAddress("Siyda",Siyda);
	myChain->SetBranchAddress("Sizuhmom",Sizuhmom);
	myChain->SetBranchAddress("Siecorr",Siecorr);
	myChain->SetBranchAddress("Sith",Sith);
	myChain->SetBranchAddress("Sicalpos",Sicalpos);
	myChain->SetBranchAddress("Sisrtpos",Sisrtpos);
	myChain->SetBranchAddress("Sisrtene",Sisrtene);
	//FMCkin
	myChain->SetBranchAddress("Npart",&Npart);
	myChain->SetBranchAddress("Part_id",Part_id);
	myChain->SetBranchAddress("Part_prt",Part_prt);
	myChain->SetBranchAddress("Part_p",Part_p);
	//TrkMcMat
	myChain->SetBranchAddress("Mcmatquality",Mcmatquality);
	myChain->SetBranchAddress("Mcmatfmckin_id",Mcmatfmckin_id);
	myChain->SetBranchAddress("Mcmattype",Mcmattype);
	myChain->SetBranchAddress("Mcmatpx",Mcmatpx);
	myChain->SetBranchAddress("Mcmatpy",Mcmatpy);
	myChain->SetBranchAddress("Mcmatpz",Mcmatpz);


	// Event
	myChain->SetBranchAddress("Runnr",&Runnr);

	nevents=myChain->GetEntries();
	cout<<nevents<<" events in this chain"<<endl;

	TH1F *q2el=new TH1F("q2el","",20,1,20);


	TH1F *hdebug=new TH1F("hdebug","Debug: DIS selection",20,0,20);
	TH1F *hdebug1=new TH1F("hdebug1","Debug: Matching",20,0,20);
	TH1F *hdebug2=new TH1F("hdebug2","Debug: true",20,0,20);
	TH1F *hdebug3=new TH1F("hdebug3","TRUE K0s",20,0,20);
	TH1F *hdebug4=new TH1F("hdebug4","TEMP",20,0,20);
	TH1F *hinv1=new TH1F("hinv1","K0s",200,250,1000);
	TH1F *hinv2=new TH1F("hinv2","K0s",200,250,1000);
	TH1F *hinv3=new TH1F("hinv3","K0s",200,250,1000);
	if (nevents>100000) nevents=300000;
	Int_t Nv0lite_true=0;
	for(int i=0;i<nevents;i++)
	{
		if (goa==10000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		//cout<<"EVENT "<<i<<"; "<<Npart<<" particles on true level"<<endl;
		for (int k=0;k<Npart-1;k++)
		{
			//cout<<"Fid "<<Part_id[k]<<"; k= "<<k<<"; "<<Part_prt[k]<<" :"<<endl;;
			hdebug4->Fill(1);
			Nv0lite_true=0;
			if (Part_prt[k]==62) Nv0lite_true++;
			if ((Part_prt[k]==54)||(Part_prt[k]==55))
			{
				//cout<<"Fid "<<Part_id[k]<<"; k= "<<k<<"; "<<Part_prt[k]<<" :"<<endl;;

				hdebug4->Fill(2);
				for (int l=k+1;l<Npart;l++)
				{
					if ((Part_prt[l]==54)||(Part_prt[l]==55))
					{
						//cout<<"        l= "<<l<<"; "<<Part_prt[l]<<"; sum: "<<Part_prt[k]+Part_prt[l]<<endl;
					}

					if ((Part_prt[k]+Part_prt[l])==109)
					{
						hdebug4->Fill(3);
						Double_t	p1x=Part_p[k][0],
								p1y=Part_p[k][1],
								p1z=Part_p[k][2],
								p2x=Part_p[l][0],
								p2y=Part_p[l][1],
								p2z=Part_p[l][2];

						Daughter true1(p1x,p1y,p1z);
						Daughter true2(p2x,p2y,p2z);
						Mother K0s_cand_true(true1,true2);
						hinv3->Fill(1000*K0s_cand_true.GetMass_m(4,4));
					}

				}
			}
		}
		hdebug3->Fill(Nv0lite_true);

		hdebug->Fill(1);
		if (Nv0lite<1) continue;
		hdebug->Fill(2);
		/*if (Sincand<=0) continue;
		hdebug->Fill(3);
		if (Siq2el[0]<1.0) continue;
		hdebug->Fill(4);
		if ((TMath::Abs(Zvtx))>52.0) continue;
		hdebug->Fill(5);
		if (Siecorr[0][2]<8.5) continue;
		hdebug->Fill(6);

		if (Siq2el[0]>20) continue;
		hdebug->Fill(7);*/
		//if (Siq2el[0]>300) continue;
		//hdebug->Fill(8);
		//cout<<i<<" event, "<<Npart<<" here"<<endl;

		/*for (int k=0;k<Trk_ntracks;k++)
		{
			cout<<k<<" "<<Part_id[k]<<" "<<Part_prt[k]<<" "<<endl;
		}*/

		for (int j=0;j<Nv0lite;j++)
		{
			Daughter t1(Tp1[j][0],Tp1[j][1],Tp1[j][2]);
			Daughter t2(Tp2[j][0],Tp2[j][1],Tp2[j][2]);
			Mother K0s_cand(t1,t2);
			hinv1->Fill(1000*K0s_cand.GetMass_m(4,4));

			hdebug1->Fill(1);
			Int_t 	id1=Tt1_id[j];
			Int_t 	id2=Tt1_id[j];
			Int_t 	f_id1=Mcmatfmckin_id[id1],
				f_id2=Mcmatfmckin_id[id2];
			if ((Mcmatquality[id1]==(-9999))||(Mcmatquality[id2]==(-9999))) continue;
			hdebug1->Fill(2);
			if ((Mcmatquality[id1]==(-1))||(Mcmatquality[id2]==(-1))) continue;
			hdebug1->Fill(3);

			if (((f_id1==54)||(f_id2==55))||((f_id1==54)||(f_id2==55)))
			{
				hdebug1->Fill(5);
				hinv2->Fill(1000*K0s_cand.GetMass_m(4,4));
			}

		}




  		//hdebug->Fill(1);
		//if (Siq2el[0]<1) continue;						// Q^2>1 GeV^2
		//hdebug->Fill(2);
		// E-pz calculation
		/*float Empz_had = Sizuhmom[0][3] - Sizuhmom[0][2];
   		float Empz_e = Siecorr[0][2]*(1-TMath::Cos( Sith[0] ));
   		float EminPz_Evt  = Empz_e + Empz_had;
		if ((EminPz_Evt<38)||(EminPz_Evt>60)) continue;				// 38 < E-pz < 60 GeV
		//hdebug->Fill(3);
		// electron position calculation (box cut)
		float x_srtd=Sicalpos[0][0];						// position of electron in calorimeter
   		float y_srtd=Sicalpos[0][1];
   		if (Sisrtene[0]>0)
		{
      			x_srtd=Sisrtpos[0][0];						// position of electron in SRDT
      			y_srtd=Sisrtpos[0][1];
    		}
		if (TMath::Abs(x_srtd)<12)						// box cut: electron required to be outside 12x6 cm^2 box
		{
			if (TMath::Abs(y_srtd)<6) continue;
		}
		//hdebug->Fill(4);
		if (Siyel[0]>0.95) continue;						// y from electron method < 0.95
		//hdebug->Fill(5);
		if (Siyjb[0]<0.01) continue;						// y from Jacquet-Blondel method > 0.01
		//hdebug->Fill(6);*/



	}

	// histograms normalising
	Double_t norm=1.0;
	Double_t scale=0;



	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/TRUE_DET_comp.root","recreate");

	hdebug->Write();
	hdebug1->Write();
	hdebug2->Write();
	hdebug3->Write();
	hdebug4->Write();//delete me
	hinv1->Write();
	hinv2->Write();
	hinv3->Write();

	f2->Close();
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	q2();
	return 0;
}
#endif
