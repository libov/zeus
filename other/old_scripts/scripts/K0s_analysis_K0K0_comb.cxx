//////////////////////////////////////////////////
//////////////                   /////////////////
//////////////   K0s   analysis  /////////////////
//////////////    with V0lite    /////////////////
//////////////                   /////////////////
//////////////////////////////////////////////////
//                                              //
//                                              //
//               Libov Vladyslav                //
//      T.S. National University of Kiev        //
//                August 2008                   //
//                                              //
//                                              //
//////////////////////////////////////////////////
//////////                             ///////////
//////////    Combining      K0sK0s    ///////////
//////////                             ///////////
//////////////////////////////////////////////////
//                                              //
//   1. Reading data from small trees           //
//   2. Event & K0s selection                   //
//   3. Combining into K0s and writing          //
//                                              //
//////////////////////////////////////////////////
#ifndef __CINT__
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TMath.h>
#include <TFile.h>
#include <TROOT.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>
using namespace std;
#include<Daughter.h>
#include<Mother.h>
#endif
void include_sample(TChain *myChain,TString path_to_sample)
{
	myChain->Add(path_to_sample);
	cout<<path_to_sample<<endl;
}
void analysis()
{
// -------------------------   CUTS ---------------------------//
	// -- variables declaring
	Double_t		TrackPtMIN=0;
	Int_t			TrackType=0;		// 1 = secondary, 2 = not primary
	Double_t		ProtonPionMassMIN=0;
	Double_t		collinearity2DMAX=0;
	Double_t		collinearity3DMAX=0;
	Double_t		K0sPtMIN=0;
	Double_t		K0sAbsEtaMAX=0;
	Int_t			InnerLayoutMAX=1;
	Int_t			OuterLayoutMIN=3;
	Double_t		ElectronPositronMassMIN=0;
	Double_t		K0sMassMIN=0;
	Double_t		K0sMassMAX=0;
	string		RootFileName;
	Int_t			Dis=0;							// 0 = inclusive, 1 = Dis
	Int_t			Include_05ev3=0;
	Int_t			Include_05ev3_new=0;
	Int_t			Include_06pv1=0;
	Int_t			Include_07pv1=0;
	Int_t			Include_06eGR1=0;
	Int_t			Include_04pGR1=0;
	Int_t			Include_MEPS=0;
	Int_t			Include_MCdijetPHPv2=0;
	Int_t			Include_MCbeautyPHP05v1=0;
	Int_t			Include_HERAII_new=0;
	Int_t			ProcessAllEvents=1;				// 1 = process all events;
															// 0 = process <ProcessEvents> events.
	Int_t			ProcessEvents=100;
	Int_t			Sidebins=0;							// 1=use sidebins; other - signal.
	Double_t		ZVertexMIN=-1000;
	Double_t		ZVertexMAX=1000;

	// -- reading numerical values from file
	ifstream 	myfile("control.cards",ios::in);
	string 		variable;
	string 		value;

	while (!myfile.eof())
	{
		myfile>>variable>>value;
		if (variable=="TrackPtMIN") TrackPtMIN=atof(value.data());
		if (variable=="TrackType") TrackType=atoi(value.data());
		if (variable=="ProtonPionMassMIN") ProtonPionMassMIN=atof(value.data());
		if (variable=="collinearity2DMAX") collinearity2DMAX=atof(value.data());
		if (variable=="collinearity3DMAX") collinearity3DMAX=atof(value.data());
		if (variable=="K0sPtMIN") K0sPtMIN=atof(value.data());
		if (variable=="K0sAbsEtaMAX") K0sAbsEtaMAX=atof(value.data());
		if (variable=="InnerLayoutMAX") InnerLayoutMAX=atoi(value.data());
		if (variable=="OuterLayoutMIN") OuterLayoutMIN=atoi(value.data());
		if (variable=="ElectronPositronMassMIN") ElectronPositronMassMIN=atof(value.data());
		if (variable=="K0sMassMIN") K0sMassMIN=atof(value.data());
		if (variable=="K0sMassMAX") K0sMassMAX=atof(value.data());
		if (variable=="RootFileName") RootFileName=value;
		if (variable=="Dis") Dis=atoi(value.data());
		if (variable=="Include_05ev3") Include_05ev3=atoi(value.data());
		if (variable=="Include_05ev3_new") Include_05ev3_new=atoi(value.data());
		if (variable=="Include_06pv1") Include_06pv1=atoi(value.data());
		if (variable=="Include_07pv1") Include_07pv1=atoi(value.data());
		if (variable=="Include_06eGR1") Include_06eGR1=atoi(value.data());
		if (variable=="Include_04pGR1") Include_04pGR1=atoi(value.data());
		if (variable=="Include_MEPS") Include_MEPS=atoi(value.data());
		if (variable=="Include_MCdijetPHPv2") Include_MCdijetPHPv2=atoi(value.data());
		if (variable=="Include_MCbeautyPHP05v1") Include_MCbeautyPHP05v1=atoi(value.data());
		if (variable=="Include_HERAII_new") Include_HERAII_new=atoi(value.data());
		if (variable=="ProcessAllEvents") ProcessAllEvents=atoi(value.data());
		if (variable=="ProcessEvents") ProcessEvents=atoi(value.data());
		if (variable=="Sidebins") Sidebins=atoi(value.data());
		if (variable=="ZVertexMIN") ZVertexMIN=atof(value.data());
		if (variable=="ZVertexMAX") ZVertexMAX=atof(value.data());
	}
	cout<<"**********   ANALYSIS CUTS   **********"<<endl;

	cout<<"TrackPtMIN = "<<TrackPtMIN<<endl;
	cout<<"TrackType = "<<TrackType<<endl;
	cout<<"ProtonPionMassMIN = "<<ProtonPionMassMIN<<endl;
	cout<<"collinearity2DMAX = "<<collinearity2DMAX<<endl;
	cout<<"collinearity3DMAX = "<<collinearity3DMAX<<endl;
	cout<<"K0sPtMIN = "<<K0sPtMIN<<endl;
	cout<<"K0sAbsEtaMAX = "<<K0sAbsEtaMAX<<endl;
	cout<<"InnerLayoutMAX = "<<InnerLayoutMAX<<endl;
	cout<<"OuterLayoutMIN = "<<OuterLayoutMIN<<endl;
	cout<<"ElectronPositronMassMIN = "<<ElectronPositronMassMIN<<endl;
	cout<<"K0sMassMIN = "<<K0sMassMIN<<endl;
	cout<<"K0sMassMAX = "<<K0sMassMAX<<endl;
	cout<<"RootFileName = "<<RootFileName<<endl;

	cout<<"***************************************"<<endl;
//-------------------------------------------------------------//

//-------------------  Adding files to be analyzed -------------------//
	TChain *myChain=new TChain("resonance");
	TString		path="/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/";
	TString		path_05ev3=path+"COMMON_NTUPLES/05ev3/*.root";
	TString		path_06pv1=path+"COMMON_NTUPLES/06pv1/*.root";
	TString		path_07pv1=path+"COMMON_NTUPLES/07pv1/*.root";
	TString		path_06eGR1=path+"zfiles/06eGR1/*.root";
	TString		path_04pGR1=path+"zfiles/04pGR1/*.root";
	TString		path_MEPS=path+"zfiles/MEPS/*.root";
	TString		path_MCdijetPHPv2=path+"COMMON_NTUPLES/MCdijetPHPv2/*.root";
	TString		path_MCbeautyPHP05v1=path+"COMMON_NTUPLES/MCbeautyPHP05v1/*.root";
	TString		path_HERAII_new=path+"HERAII/*.root";

	cout<<"*****   Samples to be analyzed:   *****"<<endl;

	if (Include_05ev3==1)		include_sample(myChain,path_05ev3);
	if (Include_HERAII_new==1)		include_sample(myChain,path_HERAII_new);
	if (Include_06pv1==1)		include_sample(myChain,path_06pv1);
	if (Include_07pv1==1)		include_sample(myChain,path_07pv1);
	if (Include_06eGR1==1)		include_sample(myChain,path_06eGR1);
	if (Include_04pGR1==1)		include_sample(myChain,path_04pGR1);
	if (Include_MEPS==1)		include_sample(myChain,path_MEPS);
	if (Include_MCdijetPHPv2==1)	include_sample(myChain,path_MCdijetPHPv2);
	if (Include_MCbeautyPHP05v1==1)	include_sample(myChain,path_MCbeautyPHP05v1);
	cout<<"***************************************"<<endl;

//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/k0eff/MC_ARI_NCDIS_MARCELLO/*.root");
//myChain->Add("/data/zenith226a/libov/data/05GR1_comntup/*.root");
//myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/06pv1/*.root");
//--------------------------------------------------------------------------------------//


//--------------   Variables and branches   -------------------//

	Int_t			nv0=0,		// number K0s candidates that passed soft selection
					id1[80],	// id of the first track
					id2[80],	// id of the second track
					runnr=0,	// number of run
					is1_sec[80],	// =1 if 1st track flagged as secondary
				is2_sec[80],	// =1 if 2nd track flagged as secondary
				is1_prim[80],	// =1 if 1st track flagged as primary
				is2_prim[80],	// =1 if 2nd track flagged as primary
				sincand,	// Number of Sinistra electron candidates
				layout1[80],	//outer superlayer of 1st pion
				layout2[80],	//outer superlayer of 2nd pion;
				layinn1[80],	//inner superlayer of 1st pion
				layinn2[80];	//inner superlayer of 2nd pion
	Float_t	p1[80][3],	// momenta of 1st track
				p2[80][3],	// momenta of 2nd track
				coll2[80],	// collinearity angle 2D
				coll3[80],	// collinearity angle 3D
				q2el,		// Q^2 from electron method (1st Sinistra candidate)
				yel,		// y from electron method (1st Sinistra candidate)
				yjb,		// y from Jaquet-Blondel method (1st Sinistra candidate)
				box_x,		// x position of scattered electron
				box_y,		// y position of electron
				e_pz,		// E-pz calculated both from hadronic system and electron
				siprob,		// probability of 1st Sinistra candidate
				mass_lambda[80],// invariant mass assuming proton(larger momenuma) and pion
				mass_ee[80];	// invariant mass assuming electron and positron
	Int_t		tlt[6][16];	// 3rd-level trigger: tlt[m][k]
					// m=3 SPP, m=4 DIS ...   k=1 bit 1 (e.g. HPP01) k=2 bit 2
	Float_t		cal_et;		// Transverse energy of the event

	Int_t		njet=0;		// Number of jets (kT jet finder A)
	Float_t	etjet[20],	// Transverse energy of jets
				etajet[20],	// eta of jets
				phijet[20];	// phi of jets
	Int_t		event;		// event number
	Int_t		ntracks;	// number of tracks quoted in Tracking block

	Float_t	bspt_x,		// beam spot X
				bspt_y,		// beam spot y
				bspt_z;		// beam spot z  ??
	Float_t	secvtx[20][3];	// position of secondary vertex from V0lite
					// (given by Vxlite function there)
	Float_t	dlen2[20],	// decay length (2D) given by V0lite
				dlen3[20];	// decay length (3D) given by V0lite

	Float_t	zvtx;		// Z-coordinate of primary vertex

	Float_t		cal_empz;

	myChain->SetBranchAddress("nv0",&nv0);
	myChain->SetBranchAddress("p1",p1);
	myChain->SetBranchAddress("p2",p2);
	myChain->SetBranchAddress("coll2",coll2);
	myChain->SetBranchAddress("coll3",coll3);
	myChain->SetBranchAddress("id1",id1);
	myChain->SetBranchAddress("id2",id2);
	myChain->SetBranchAddress("is1_sec",is1_sec);
	myChain->SetBranchAddress("is2_sec",is2_sec);
	myChain->SetBranchAddress("is1_prim",is1_prim);
	myChain->SetBranchAddress("is2_prim",is2_prim);
	myChain->SetBranchAddress("q2el",&q2el);
	myChain->SetBranchAddress("yel",&yel);
	myChain->SetBranchAddress("yjb",&yjb);
	myChain->SetBranchAddress("box_x",&box_x);
	myChain->SetBranchAddress("box_y",&box_y);
	myChain->SetBranchAddress("e_pz",&e_pz);
	myChain->SetBranchAddress("siprob",&siprob);
	myChain->SetBranchAddress("sincand",&sincand);
	myChain->SetBranchAddress("mass_lambda",mass_lambda);
	myChain->SetBranchAddress("mass_ee",mass_ee);
	myChain->SetBranchAddress("runnr",&runnr);
	myChain->SetBranchAddress("layout1",layout1);
	myChain->SetBranchAddress("layout2",layout2);
	myChain->SetBranchAddress("layinn1",layinn1);
	myChain->SetBranchAddress("layinn2",layinn2);
	myChain->SetBranchAddress("cal_et",&cal_et);
	myChain->SetBranchAddress("event",&event);
	myChain->SetBranchAddress("ntracks",&ntracks);
	myChain->SetBranchAddress("bspt_x",&bspt_x);
	myChain->SetBranchAddress("bspt_y",&bspt_y);
	myChain->SetBranchAddress("bspt_z",&bspt_z);
	myChain->SetBranchAddress("secvtx",secvtx);
	myChain->SetBranchAddress("dlen2",dlen2);
	myChain->SetBranchAddress("dlen3",dlen3);
	myChain->SetBranchAddress("zvtx",&zvtx);


	myChain->SetBranchAddress("njet",&njet);
	myChain->SetBranchAddress("etjet",etjet);
	myChain->SetBranchAddress("etajet",etajet);
	myChain->SetBranchAddress("phijet",phijet);

	myChain->SetBranchAddress("cal_empz",&cal_empz);

	//myChain->SetBranchAddress("tlt",tlt);


//-------------------------------------------------------------//
const Int_t 		start_04p=47010,
						end_04p=51245,
						start_05e=52244,
						end_05e=57123,
						start_06e=58181,
						end_06e=59947,
						start_06p=60005,
						end_06p=61746,
						start_07p=61747,
						end_07p=62638;
//----------------------- booking histograms ------------------//
	Float_t		//corr=1.005;
			corr=1.00000;
	TH1F *h1=new TH1F("h1","ZEUS",200,0.8,5);
	TH1F *h2=new TH1F("h2","ZEUS",280,0.8,5);
	TH1F *h3=new TH1F("h3","ZEUS",150,0.8,5);
	TH1F *h2_pt1=new TH1F("h2_pt1","p_{T}(K^{0}_{S}K^{0}_{S})>1.0 GeV",280,0.8,5);
	TH1F *h2_pt2=new TH1F("h2_pt2","p_{T}(K^{0}_{S}K^{0}_{S})>2.0 GeV",280,0.8,5);

	TH1F *hK0_mass=new TH1F("hK0_mass","Invariant mass, N (K^{0}_{S})>=2",60,450,552);
	TH1F *hK0_mass1=new TH1F("hK0_mass1","Invariant mass, N (K^{0}_{S})>=2",200,250,1000);
	TH1F *hK0_massK1=new TH1F("hK0_massK1","Invariant mass, N (K^{0}_{S})>=2",200,250,1000);
	TH1F *hK0_massK2=new TH1F("hK0_massK2","Invariant mass, N (K^{0}_{S})>=2",200,250,1000);
	TH1F *hK0_n1=new TH1F("hK0_n1","Number of K^{0}_{S} before selection (V0lite)",70,0,70);
	TH1F *hK0_n2=new TH1F("hK0_n2","Number of K^{0}_{S} after selection",70,0,70);
	TH1F *hd1=new TH1F("hd1","debug1: K^{0}_{S} selection",20,0,20);
	TH1F *hd2=new TH1F("hd2","debug2: K^{0}_{S}K^{0}_{S} combining",20,0,20);
	TH1F *h_mass_pi_p=new TH1F("h_mass_pi_p","#Lambda",200,1000,1300);

	TH1F *hLambda_before=new TH1F("hLambda_before","#Lambda 's, before n(K0s)>=4 cut",70,0,70);
	TH1F *hLambda_after=new TH1F("hLambda_after","#Lambda 's, after n(K0s)>=4 cut",70,0,70);


	TH1F *h_njet=new TH1F("h_njet","Number of jets (kT A)",20,0,20);

	TH1F *h_delta=new TH1F("h_delta","delta",100,0,10);
	TH1F *h_d_ab=new TH1F("h_d_ab","",100,0,10);

	TH1F *h_jetAS=new TH1F("h_jetAS","K0sK0s associated with jets",280,0.8,5);
	TH1F *h_jetnonAS=new TH1F("h_jetnonAS","K0sK0s non-associated with jets",280,0.8,5);

	TH1F *h_delta_dlen2=new TH1F("h_delta_dlen2","Difference ",150,0,50);
	TH1F *h_delta_dlen3=new TH1F("h_delta_dlen3","Difference ",150,0,50);
	TH1F *h_delta_dlen3_raw=new TH1F("h_delta_dlen3_raw","Difference ",150,0,50);

	TH1F *h_ntracks=new TH1F("h_ntracks","ntracks ",500,0,500);

	//triggers

	TH1F *exo=new TH1F("exo","EXO TLT fired ",16,1,17);
	TH1F *muo=new TH1F("muo","MUO TLT fired ",16,1,17);
	TH1F *vtx=new TH1F("vtx","vtx TLT fired ",16,1,17);
	TH1F *hfm=new TH1F("hfm","hfm TLT fired ",16,1,17);
	TH1F *hfl=new TH1F("hfl","hfl TLT fired ",16,1,17);
	TH1F *dis=new TH1F("dis","DIS TLT fired ",16,1,17);
	TString zdef="E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}";
	TString	name="";

	//calorimeter
TH1F *hcal_et=new TH1F("hcal_et","Total transverse energy in calorimeter, E_{T}^{event}  for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<1",100,0,100);
TH1F *hk0k0_et=new TH1F("hk0k0_et","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<1",100,0,20);
	TH1F *hratio_et=new TH1F("hratio_et","E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}",100,0,1);

//////////////////
TH1F *hk0k0_d_ab1=new TH1F("hk0k0_d_ab1","delta>0",150,0.8,5);
TH1F *hk0k0_d_ab2=new TH1F("hk0k0_d_ab2","delta>0.1",150,0.8,5);
TH1F *hk0k0_d_ab3=new TH1F("hk0k0_d_ab3","delta>0.3",150,0.8,5);
TH1F *hk0k0_d_ab4=new TH1F("hk0k0_d_ab4","delta>0.5",150,0.8,5);
TH1F *hk0k0_d_ab5=new TH1F("hk0k0_d_ab5","delta>0",150,0.8,5);
/////////////

TH1F *hddlen3_1=new TH1F("hddlen3_1","delta dlen3 >0",150,0.8,5);
TH1F *hddlen3_2=new TH1F("hddlen3_2","delta dlen3 >0.5",150,0.8,5);
TH1F *hddlen3_3=new TH1F("hddlen3_3","delta dlen3 >1",150,0.8,5);
TH1F *hddlen3_4=new TH1F("hddlen3_4","delta dlen3 >2",150,0.8,5);

TH1F *hzvtx=new TH1F("hzvtx","Z_{vtx}",150,-100,100);

TH1F *h2z_0=new TH1F("h2z_0","0.00<z<0.07",280,0.8,5);
TH1F *h2z_1=new TH1F("h2z_1","0.07<z<0.100",280,0.8,5);
TH1F *h2z_2=new TH1F("h2z_2","0.100<z<0.150",280,0.8,5);
TH1F *h2z_3=new TH1F("h2z_3","0.150<z<1.000",280,0.8,5);


	TH1F *hcal_et_1=new TH1F("hcal_et_1","Total transverse energy in calorimeter, E_{T}^{event} for E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",100,0,100);
	TH1F *hcal_et_2=new TH1F("hcal_et_2","Total transverse energy in calorimeter, E_{T}^{event} for 0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",100,0,100);
	TH1F *hcal_et_3=new TH1F("hcal_et_3","Total transverse energy in calorimeter, E_{T}^{event} for 0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",100,0,100);
	TH1F *hcal_et_4=new TH1F("hcal_et_4","Total transverse energy in calorimeter, E_{T}^{event} for 0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",100,0,100);
	TH1F *hcal_et_5=new TH1F("hcal_et_5","Total transverse energy in calorimeter, E_{T}^{event} for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",100,0,100);

	TH1F *hk0k0_et_1=new TH1F("hk0k0_et_1","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}>0.5",100,0,20);
	TH1F *hk0k0_et_2=new TH1F("hk0k0_et_2","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0.25<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.5",100,0,20);
	TH1F *hk0k0_et_3=new TH1F("hk0k0_et_3","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0.125<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.25",100,0,20);
	TH1F *hk0k0_et_4=new TH1F("hk0k0_et_4","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0.05<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.125",100,0,20);
	TH1F *hk0k0_et_5=new TH1F("hk0k0_et_5","Transverse energy of K^{0}_{S}K^{0}_{S}, E_{T}^{K^{0}_{S}K^{0}_{S}} for 0<E_{T}^{K^{0}_{S}K^{0}_{S}}/E_{T}^{event}<0.05",100,0,20);

	TH1F *h_dlen3 =new TH1F("h_dlen3","",300,0,50);
	TH1F *h_dlen2 =new TH1F("h_dlen2","",300,0,50);
	TH1F *h_dlen3_raw =new TH1F("h_dlen3_raw","",300,0,50);

	TH1F *h_f0_pt =new TH1F("h_f0_pt","",300,0,7);
	TH1F *h_angle =new TH1F("h_angle","angle between two K0s",300,0,6);

	TH1F *heta_1 =new TH1F("heta_1","#eta<0",150,0.8,5);
	TH1F *heta_2 =new TH1F("heta_2","0<#eta",150,0.8,5);
	TH1F *heta_1a =new TH1F("heta_1a","-1.5<#eta<0",150,0.8,5);
	TH1F *heta_2a =new TH1F("heta_2a","0<#eta<1.5",150,0.8,5);
	///TH1F *heta_1 =new TH1F("heta_1","#eta<0",150,0.8,5);

	TH1F *h_thetastar =new TH1F("h_thetastar","",50,-3.2,3.2);
	TH1F *h_costhetastar =new TH1F("h_costhetastar","",50,-1,1);
	TH1F *h_costhetastar_k0 =new TH1F("h_costhetastar_k0","",50,-1,1);

	TH1F *h_costhetastar_f2prime =new TH1F("h_costhetastar_f2prime","",50,-1,1);
	TH1F *h_costhetastar_bg =new TH1F("h_costhetastar_bg","",50,-1,1);

	TH1F *h_cal_empz =new TH1F("h_cal_empz","",100,0,100);
	TH1F *h_empz_rel =new TH1F("h_empz_rel","",100,0,1);

	TH1F *h2zempz_0=new TH1F("h2zempz_0","0.00<z_empz<0.10",280,0.8,5);
	TH1F *h2zempz_1=new TH1F("h2zempz_1","0.10<z_empz<1.00",280,0.8,5);


	TH1F	*h_number_of_KK_pairs =new TH1F("h_number_of_KK_pairs","",10,0,10);
	Int_t	number_of_KK_pairs=0;


	TH1F *h_eta_KK =new TH1F("h_eta_KK","",30,-2,2);
	TH1F *h_pT_KK =new TH1F("h_pT_KK","",30,0,5);

	TH1F *hK0_04p=new TH1F("hK0_04p","",60,450,552);
	TH1F *hK0_05e=new TH1F("hK0_05e","",60,450,552);
	TH1F *hK0_06e=new TH1F("hK0_06e","",60,450,552);
	TH1F *hK0_06p=new TH1F("hK0_06p","",60,450,552);
	TH1F *hK0_07p=new TH1F("hK0_07p","",60,450,552);

	TH1F *h_k0inv_total=new TH1F("h_k0inv_total","",60,450,552);
	TH1F *htest=new TH1F("htest","",60,400,602);
//---------------------------------------------------------------------------------//
	bool	year_04p=false;
	bool	year_05e=false;
	bool	year_06e=false;
	bool	year_06p=false;
	bool	year_07p=false;

	Double_t convert=180/TMath::Pi();
	Double_t phi=0;
	Int_t 	goa=0,year=0,err=0;
	Float_t reso_mass=0;
	Double_t	a1=0,
			a2=0,
			a3=0,
			a6=0;
	Int_t		nevents=0;
	TH1F *hk0_current_hist;

	if (ProcessAllEvents==1)
	{
		nevents=myChain->GetEntries();
		cout<<nevents<<" events here"<<endl;
	}
	if (ProcessAllEvents==0)
	{
		nevents=ProcessEvents;
		cout<<nevents<<" events requested"<<endl;
	}

	for (Int_t i=0;i<nevents;i++)
	{
		number_of_KK_pairs=0;
		if (goa==100000)
        	{
        		cout<<i<<" events processed"<<endl;
			goa=0;
		}
        	goa++;
		myChain->GetEntry(i);
		year_04p=false;
		year_05e=false;
		year_06e=false;
		year_06p=false;
		year_07p=false;

		year_04p=((runnr>=start_04p)&&(runnr<=end_04p));
		year_05e=((runnr>=start_05e)&&(runnr<=end_05e));
		year_06e=((runnr>=start_06e)&&(runnr<=end_06e));
		year_06p=((runnr>=start_06p)&&(runnr<=end_06p));
		year_07p=((runnr>=start_07p)&&(runnr<=end_07p));

		if (year_04p) hk0_current_hist=hK0_04p;
		if (year_05e) hk0_current_hist=hK0_05e;
		if (year_06e) hk0_current_hist=hK0_06e;
		if (year_06p) hk0_current_hist=hK0_06p;
		if (year_07p) hk0_current_hist=hK0_07p;

		if ((zvtx>ZVertexMAX)||(zvtx<ZVertexMIN)) continue;
		hzvtx->Fill(zvtx);
		Int_t	cand_k0=0,
		list_k0[30];
		if (Dis==1)
		{
			hd1->Fill(1);
			if (sincand<1) continue;
			hd1->Fill(2);
			if (siprob<0.9) continue;
			hd1->Fill(3);
			if (q2el<1.0) continue;
			hd1->Fill(4);
			if (yjb<0.01) continue;
			hd1->Fill(5);
			if (yel>0.95) continue;
			hd1->Fill(6);
			if ((box_x<12)&&(box_y<6)) continue;
			hd1->Fill(7);
		}
		h_cal_empz->Fill(cal_empz);
	/*
		// ----- momenta scaling ------ //
		year=0;
		if  ((Runnr>=low_2004)&&(Runnr<=up_2004)) year=2004;
		if  ((Runnr>=low_2005)&&(Runnr<=up_2005)) year=2005;
		if  ((Runnr>=low_2006)&&(Runnr<=up_2006)) year=2006;
		if  ((Runnr>=low_2006p)&&(Runnr<=up_2006p)) year=2010;
		if  ((Runnr>=low_2007)&&(Runnr<=up_2007)) year=2007;

		switch (year)
		{
			case 2004: corr=corr_2004; break;
			case 2005: corr=corr_2005; break;
			case 2006: corr=corr_2006e; break;
			case 2007: corr=corr_2007; break;
			case 2010: corr=corr_2006p; break;
			case 0: {corr=1.00000; err++;} break;
		}
	*/
		corr=1.000000;
		//------ K0s cand selection -------//
		hK0_n1->Fill(nv0);
		Int_t			NLambda=0;
		for(Int_t k=0;k<nv0;k++)
		{

			Daughter t1(corr*p1[k][0],corr*p1[k][1],corr*p1[k][2]);
			Daughter t2(corr*p2[k][0],corr*p2[k][1],corr*p2[k][2]);
			hd1->Fill(1);
			a1++;
			if ((t1.GetPt()<TrackPtMIN)||(t2.GetPt()<TrackPtMIN)) continue;
			hd1->Fill(2);
			a2++;
			if ((layout1[k]<OuterLayoutMIN)||(layout2[k]<OuterLayoutMIN)) continue;
			hd1->Fill(3);
			if ((layinn1[k]>InnerLayoutMAX)||(layinn2[k]>InnerLayoutMAX)) continue;
			hd1->Fill(11);
			a3++;

			Mother K0s_cand(t1,t2);
			Bool_t		TrackType_accept=false; // if true  - accept K0s cand
			switch (TrackType)
			{
				case 1: TrackType_accept=((is1_sec[k]==1)&&(is2_sec[k]==1)); break;
				case 2: TrackType_accept=((is1_prim[k]!=1)&&(is2_prim[k]!=1)); break;
			}
			if (!TrackType_accept) continue;
			hd1->Fill(4);

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
			/*if (K0s_cand.GetMass_m(4,4)<0.475)
			{
				h_mass_pi_p->Fill(1000*mass_pi_p);
			}

			if(mass_pi_p<ProtonPionMassMIN) continue;*/
			hd1->Fill(5);
			if (coll2[k]>collinearity2DMAX) continue;
			if (coll3[k]>collinearity3DMAX) continue;
			hd1->Fill(6);
			a6++;

			if(K0s_cand.GetPt_m()<K0sPtMIN) continue;
			hd1->Fill(7);
			if (TMath::Abs(K0s_cand.GetEta_m())>K0sAbsEtaMAX) continue;
			hd1->Fill(8);

			hd1->Fill(9);

			hd1->Fill(10);

			//if (((layout1[k]-layinn1[k])<7)||((layout2[k]-layinn2[k])<7)) continue;
			//if ((is1_sec[k]!=1)||(is2_sec[k]!=1)) continue;



			hd1->Fill(12);
			if (mass_ee[k]<ElectronPositronMassMIN) continue;
			hd1->Fill(13);

			if (K0s_cand.GetMass_m(4,4)<0.475)
			{
				h_mass_pi_p->Fill(1000*mass_pi_p);
				if ((mass_pi_p>1.105)&&(mass_pi_p<1.125)) NLambda++;
			}

			if (mass_pi_p<ProtonPionMassMIN) continue;

			Float_t		gamma=0;

			gamma=sqrt(1+TMath::Power((K0s_cand.GetP_m()/0.49762),2));
			h_dlen3->Fill(dlen3[k]/gamma);
			h_dlen2->Fill(dlen2[k]);
			h_dlen3_raw->Fill(dlen3[k]);
			//cout<<"--- "<<dlen3[k]<<endl;
			//if (dlen2[k]<3) continue;

			Double_t		K0s_mass=K0s_cand.GetMass_m(4,4);
			Bool_t		K0s_signal=((K0s_mass>K0sMassMIN)&&(K0s_mass<K0sMassMAX));

			//hk0_current_hist->Fill(1000*K0s_mass);
			h_k0inv_total->Fill(1000*K0s_mass);

			if (Sidebins!=1)
			{
				if (!K0s_signal) continue;
			}

			if (Sidebins==1)
			{
				Bool_t		K0s_rside=((K0s_mass>0.5577)&&(K0s_mass<0.5777));
				Bool_t		K0s_lside=((K0s_mass>0.4177)&&(K0s_mass<0.4377));
				Bool_t		K0s_side=(K0s_rside||K0s_lside);

				if (!(K0s_signal||K0s_side)) continue;
			}

			list_k0[cand_k0]=k;
			hd1->Fill(14);
			cand_k0++;




			/*
			if( K0s_cand.GetPx_m()>=0) phi=convert*acos((K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if( K0s_cand.GetPx_m()<0) phi=180-convert*acos(((-1)*K0s_cand.GetPx_m())/(K0s_cand.GetPt_m()));
			if (K0s_cand.GetPy_m()<=0)
			{
				phi=360-phi;
			}
		*/
		}

		//K0s combining
		hK0_n2->Fill(cand_k0);
		hLambda_before->Fill(NLambda);
		if (cand_k0<2) continue;
		hLambda_after->Fill(NLambda);
		for(Int_t k=0;k<cand_k0;k++)
		{
			Int_t id=list_k0[k];
			Daughter t1temp(corr*p1[id][0],corr*p1[id][1],corr*p1[id][2]);
			Daughter t2temp(corr*p2[id][0],corr*p2[id][1],corr*p2[id][2]);
			Mother K0s_candtemp(t1temp,t2temp);
			Double_t		K0s_mass=K0s_candtemp.GetMass_m(4,4);
			hK0_mass->Fill(1000*K0s_mass);
			hK0_mass1->Fill(1000*K0s_mass);
		}
		h_ntracks->Fill(ntracks);
		bool			acc=true;
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
				if ((id1k==id2k)||(id1l==id2l)) continue;
				hd2->Fill(3);
				number_of_KK_pairs++;

				Float_t		px1=corr*(p1[k01][0]+p2[k01][0]),
								py1=corr*(p1[k01][1]+p2[k01][1]),
								pz1=corr*(p1[k01][2]+p2[k01][2]),

								px2=corr*(p1[k02][0]+p2[k02][0]),
								py2=corr*(p1[k02][1]+p2[k02][1]),
								pz2=corr*(p1[k02][2]+p2[k02][2]);

				Daughter 	K0s_cand1(px1,py1,pz1);
				Daughter 	K0s_cand2(px2,py2,pz2);

				// Sidebins

				if (Sidebins==1)
				{
					Daughter		K1_pi1(p1[k01][0],p1[k01][1],p1[k01][2]);
					Daughter		K1_pi2(p2[k01][0],p2[k01][1],p2[k01][2]);
					Daughter		K2_pi1(p1[k02][0],p1[k02][1],p1[k02][2]);
					Daughter		K2_pi2(p2[k02][0],p2[k02][1],p2[k02][2]);
					Mother		K0s1(K1_pi1,K1_pi2);
					Mother		K0s2(K2_pi1,K2_pi2);
					Double_t		K0s1_mass=K0s1.GetMass_m(4,4);
					Double_t		K0s2_mass=K0s2.GetMass_m(4,4);
					htest->Fill(1000*K0s1_mass);
					htest->Fill(1000*K0s2_mass);

					Bool_t		K0s1_signal=((K0s1_mass>K0sMassMIN)&&(K0s1_mass<K0sMassMAX));
					Bool_t		K0s2_signal=((K0s2_mass>K0sMassMIN)&&(K0s2_mass<K0sMassMAX));

					if ((K0s1_signal)&&(K0s2_signal)) continue;
				}



				Mother 		K0sK0s(K0s_cand1,K0s_cand2);
				reso_mass=K0sK0s.GetMass_m(5,5);

				h1->Fill(reso_mass);
				h2->Fill(reso_mass);
				h3->Fill(reso_mass);

				if (K0sK0s.GetPt_m()>1.) h2_pt1->Fill(reso_mass);
				if (K0sK0s.GetPt_m()>2.) h2_pt2->Fill(reso_mass);

				//_____________________________________________//
				//angle between two K0s
				/*TVector3 k1(px1,py1,pz1);
				TVector3 k2(px2,py2,pz2);
				Double_t angle=k1.Angle(k2);
				//if (reso_mass<1.1) h_angle->Fill(angle);
				//if (angle<0.15)	continue;*/
				//_____________________________________________//


				// _____________for zevis ________________//
			/*	if ((reso_mass<1.55)&&(reso_mass>1.45))
				{
					cout<<"*********************************"<<endl;
					cout<<endl;
					cout<<"Run: "<<runnr<<" Event: "<<event<<endl;
					if (acc)
					{
						cout<<cand_k0<<" K0s here"<<endl;
						cout<<NLambda<<" Lambdas here"<<endl;
					}
					acc=false;
					cout<<"Kaon "<<k01<<endl;
					cout<<"	pi1: "<<id1[k01]<<": "<<p1[k01][0]<<""<<p1[k01][1]<<" "<<p1[k01][2]<<endl;
					cout<<"	pi2: "<<id2[k01]<<" "<<p2[k01][0]<<" "<<p2[k01][1]<<" "<<p2[k01][2]<<endl;
					cout<<"coll2= "<<coll2[k01]<<endl;
					cout<<"coll3= "<<coll3[k01]<<endl;
					cout<<"M(K)= "<<K0s_test.GetMass_m(4,4)<<endl;
					cout<<"secvtx: "<<secvtx[k01][0]<<" "<<secvtx[k01][1]<<" "<<secvtx[k01][2]<<endl;
					cout<<is1_prim[k01]<<" "<<is2_prim[k01]<<endl;
					cout<<"Kaon "<<k02<<endl;
					cout<<"	pi1: "<<id1[k02]<<" "<<p1[k02][0]<<" "<<p1[k02][1]<<" "<<p1[k02][2]<<endl;
					cout<<"	pi2: "<<id2[k02]<<" "<<p2[k02][0]<<" "<<p2[k02][1]<<" "<<p2[k02][2]<<endl;
					cout<<"coll2= "<<coll2[k02]<<endl;
					cout<<"coll3= "<<coll3[k02]<<endl;
					cout<<"M(K)= "<<K0s_test1.GetMass_m(4,4)<<endl;
					cout<<"secvtx: "<<secvtx[k02][0]<<" "<<secvtx[k02][1]<<" "<<secvtx[k02][2]<<endl;
					cout<<is1_prim[k02]<<" "<<is2_prim[k02]<<endl;
					cout<<"M(KK)= "<<reso_mass<<endl;
					cout<<endl;
				}
			*/


				//_________ Et  stuff _________//
				Float_t		K0sK0s_et=0;
				K0sK0s_et=K0sK0s.GetEt_m();
				hcal_et->Fill(cal_et);
				Float_t		ratio=K0sK0s_et/cal_et;
				hratio_et->Fill(ratio);

				Float_t	f0pt=K0sK0s.GetPt_m();
				//h_f0_pt->Fill(f0pt);
				if (reso_mass<1.2)
				{
					h_f0_pt->Fill(f0pt);
				}

				Float_t		delta_dlen2=dlen2[k01]-dlen2[k02];
				h_delta_dlen2->Fill(delta_dlen2);


				if (ratio>0.5)
				{
					hcal_et_1->Fill(cal_et);
					hk0k0_et_1->Fill(K0sK0s_et);

				}
				if ((ratio>0.25)&&(ratio<0.5))
				{
					hcal_et_2->Fill(cal_et);
					hk0k0_et_2->Fill(K0sK0s_et);
				}
				if ((ratio>0.125)&&(ratio<0.25))
				{
					hcal_et_3->Fill(cal_et);
					hk0k0_et_3->Fill(K0sK0s_et);
				}
				if ((ratio>0.05)&&(ratio<0.125))
				{
					hcal_et_4->Fill(cal_et);
					hk0k0_et_4->Fill(K0sK0s_et);
				}
			/*	if ((ratio>0)&&(ratio<0.05))
				//if (true)
				{
					//-------
				Float_t		gamma1=0,
						gamma2=0;

			gamma1=sqrt(1+TMath::Power((K0s_cand1.GetP()/0.49762),2));
			gamma2=sqrt(1+TMath::Power((K0s_cand2.GetP()/0.49762),2));
			Float_t		delta_dlen3=0;
			//cout<<gamma1<<" ** "<<gamma2<<endl;
			delta_dlen3=TMath::Abs((dlen3[k01]/gamma1)-(dlen3[k02]/gamma2));				h_delta_dlen3->Fill(delta_dlen3);
			if (delta_dlen3>0) hddlen3_1->Fill(reso_mass);
			if (delta_dlen3>0.5) hddlen3_2->Fill(reso_mass);
			if (delta_dlen3>1) hddlen3_3->Fill(reso_mass);
			if (delta_dlen3>2) hddlen3_4->Fill(reso_mass);
			//Float_t		delta_dlen2=dlen2[k01]-dlen2[k02];
			//h_delta_dlen2->Fill(delta_dlen2);
			//cout<<dlen3[k01]<<endl;
			//cout<<dlen3[k02]<<endl;
			h_delta_dlen3_raw->Fill(TMath::Abs(dlen3[k01]-dlen3[k02]));
				//-------


					hk0k0_5->Fill(reso_mass);
					hk0k0_5_280->Fill(reso_mass);
					hcal_et_5->Fill(cal_et);
					hk0k0_et_5->Fill(K0sK0s_et);
					//if ((1.025<reso_mass)&&(reso_mass<1.06))

					// ___________________ "matching" _______________________//
					// 'a'-configuration
					Float_t	x1a=(p1[k01][0]-p1[k02][0]);
					Float_t	y1a=(p1[k01][1]-p1[k02][1]);
					Float_t	z1a=(p1[k01][2]-p1[k02][2]);
					Float_t	x2a=(p2[k01][0]-p2[k02][0]);
					Float_t	y2a=(p2[k01][1]-p2[k02][1]);
					Float_t	z2a=(p2[k01][2]-p2[k02][2]);
					// 'b'-configuration
					Float_t	x1b=(p1[k01][0]-p2[k02][0]);
					Float_t	y1b=(p1[k01][1]-p2[k02][1]);
					Float_t	z1b=(p1[k01][2]-p2[k02][2]);
					Float_t	x2b=(p2[k01][0]-p1[k02][0]);
					Float_t	y2b=(p2[k01][1]-p1[k02][1]);
					Float_t	z2b=(p2[k01][2]-p1[k02][2]);

					Float_t		delta_a=0,
									delta_b=0;
									delta_a=sqrt(x1a*x1a+y1a*y1a+z1a*z1a+x2a*x2a+y2a*y2a+z2a*z2a);
									delta_b=sqrt(x1b*x1b+y1b*y1b+z1b*z1b+x2b*x2b+y2b*y2b+z2b*z2b);

					Float_t		min=0;
					if (delta_a<delta_b) min=delta_a;
					if (delta_b<delta_a) min=delta_b;
					h_d_ab->Fill(min);
					if (min>0) hk0k0_d_ab1->Fill(reso_mass);
					if (min>0.1) hk0k0_d_ab2->Fill(reso_mass);
					if (min>0.3) hk0k0_d_ab3->Fill(reso_mass);
					if (min>0.5) hk0k0_d_ab4->Fill(reso_mass);
					// __________________________________________________  //

					/*if (reso_mass<1.08)
					{
						cout<<"Run: "<<runnr<<" ; Event: "<<event<<endl;
						cout<<"Mass: "<<reso_mass<<endl;
						cout<<"Tot nr of tracks: "<<ntracks<<endl;
						cout<<"Pions from 1st Kaon:"<<endl;
						cout<<id1k<<" :"<<endl;
						cout<<"layout= "<<layout1[k01]<<endl;
						cout<<"layinn= "<<layinn1[k01]<<endl;
						cout<<"px= "<<p1[k01][0]<<endl;
						cout<<"py= "<<p1[k01][1]<<endl;
						cout<<"pz= "<<p1[k01][2]<<endl;
	cout<<"pt= "<<sqrt(p1[k01][0]*p1[k01][0]+p1[k01][1]*p1[k01][1])<<endl;
	cout<<"p= "<<sqrt(p1[k01][0]*p1[k01][0]+p1[k01][1]*p1[k01][1]+p1[k01][2]*p1[k01][2])<<endl;

						cout<<id2k<<" :"<<endl;
						cout<<"layout= "<<layout2[k01]<<endl;
						cout<<"layinn= "<<layinn2[k01]<<endl;
						cout<<"px= "<<p2[k01][0]<<endl;
						cout<<"py= "<<p2[k01][1]<<endl;
						cout<<"pz= "<<p2[k01][2]<<endl;
	cout<<"pt= "<<sqrt(p2[k01][0]*p2[k01][0]+p2[k01][1]*p2[k01][1])<<endl;
	cout<<"p= "<<sqrt(p2[k01][0]*p2[k01][0]+p2[k01][1]*p2[k01][1]+p2[k01][2]*p2[k01][2])<<endl;

						cout<<"Pions from 2nd Kaon:"<<endl;
						cout<<id1l<<" :"<<endl;
						cout<<"layout= "<<layout1[k02]<<endl;
						cout<<"layinn= "<<layinn1[k02]<<endl;
						cout<<"px= "<<p1[k02][0]<<endl;
						cout<<"py= "<<p1[k02][1]<<endl;
						cout<<"pz= "<<p1[k02][2]<<endl;
	cout<<"pt= "<<sqrt(p1[k02][0]*p1[k02][0]+p1[k02][1]*p1[k02][1])<<endl;
	cout<<"p= "<<sqrt(p1[k02][0]*p1[k02][0]+p1[k02][1]*p1[k02][1]+p1[k02][2]*p1[k02][2])<<endl;

						cout<<id2l<<" :"<<endl;
						cout<<"layout= "<<layout2[k02]<<endl;
						cout<<"layinn= "<<layinn2[k02]<<endl;
						cout<<"px= "<<p2[k02][0]<<endl;
						cout<<"py= "<<p2[k02][1]<<endl;
						cout<<"pz= "<<p2[k02][2]<<endl;
	cout<<"pt= "<<sqrt(p2[k02][0]*p2[k02][0]+p2[k02][1]*p2[k02][1])<<endl;
	cout<<"p= "<<sqrt(p2[k02][0]*p2[k02][0]+p2[k02][1]*p2[k02][1]+p2[k02][2]*p2[k02][2])<<endl;

					}*/

			//	}*/

				if ((ratio>0.00)&&(ratio<0.07))		h2z_0->Fill(reso_mass);
				if ((ratio>0.07)&&(ratio<0.100))		h2z_1->Fill(reso_mass);
				if ((ratio>0.100)&&(ratio<0.150))	h2z_2->Fill(reso_mass);
				if ((ratio>0.150)&&(ratio<1.00))		h2z_3->Fill(reso_mass);

				//_____________________________________________________//
				//     E-pz stuff
				Double_t		KK_empz=K0sK0s.GetE_m(5,5)-K0sK0s.GetPz_m();
				Double_t		z_empz=KK_empz/cal_empz;
				h_empz_rel->Fill(z_empz);
				if ((z_empz>0.)&&(z_empz<0.10))	h2zempz_0->Fill(reso_mass);
				if ((z_empz>0.1)&&(z_empz<1.0))	h2zempz_1->Fill(reso_mass);
				//_____________________________________________________//


				Double_t	eta=K0sK0s.GetEta_m();
				if (eta<0) heta_1->Fill(reso_mass);
				if (eta>0) heta_2->Fill(reso_mass);
				if ((eta>-1.5)&&(eta<0)) heta_1a->Fill(reso_mass);
				if ((eta>0)&&(eta<1.5)) heta_2a->Fill(reso_mass);

				h_eta_KK->Fill(eta);
				Double_t	pT=K0sK0s.GetPt_m();
				h_pT_KK->Fill(pT);

				h_njet->Fill(njet);
				Float_t		delta=0,
								delta_phi=0,
								delta_eta=0;
				Float_t		delta_min=999999;
				for (int jet=0;jet<njet;jet++)
				{
					delta_eta=etajet[jet]-(K0sK0s.GetEta_m());
					delta_phi=phijet[jet]-(K0sK0s.GetPhi_m());
					delta=sqrt(delta_eta*delta_eta+delta_phi*delta_phi);
					//cout<<delta<<endl;
					if (delta<delta_min) delta_min=delta;
				}
				h_delta->Fill(delta_min);
				if (delta_min<2)
				{
					h_jetAS->Fill(reso_mass);
				}
				if (delta_min>3)
				{
					h_jetnonAS->Fill(reso_mass);
				}


				// trigger defining
		/*
				for (int k=0;k<16;k++)
					if (tlt[0][k]==1) exo->Fill(k+1);
				for (int k=0;k<16;k++)
					if (tlt[1][k]==1) muo->Fill(k+1);
				for (int k=0;k<16;k++)
					if (tlt[2][k]==1) vtx->Fill(k+1);
				for (int k=0;k<16;k++)
					if (tlt[3][k]==1) hfm->Fill(k+1);
				for (int k=0;k<16;k++)
					if (tlt[4][k]==1) hfl->Fill(k+1);
				for (int k=0;k<16;k++)
					if (tlt[5][k]==1) dis->Fill(k+1);
				//for (int k=0;k<16;k++)
				//	if (tlt[6-1][k]==1) exo->Fill(k+1);

		*/


			}
		}

		h_number_of_KK_pairs->Fill(number_of_KK_pairs);
	}

	TFile *f1 =new TFile(RootFileName.data(),"recreate");

	h_eta_KK->Write();
	h_pT_KK->Write();

	h1->Write();
	h2->Write();
	h2_pt1->Write();
	h2_pt2->Write();
	h3->Write();
	hK0_n1->Write();
	hK0_n2->Write();
	hK0_mass->Write();
	hK0_mass1->Write();
	hK0_massK1->Write();
	hK0_massK2->Write();
	hd1->Write();
	hd2->Write();
	for (int k=0;k<12;k++)
	{
		cout<<"Bin "<<k<<" : "<<hd1->GetBinContent(k)<<endl;
	}
	cout<<a1<<" "<<a2<<" "<<a3<<" "<<a6<<endl;

	exo->Write();
	muo->Write();
	vtx->Write();
	hfm->Write();
	hfl->Write();
	dis->Write();

	hcal_et->Write();
	hratio_et->Write();

	hk0k0_et_1->Write();
	hk0k0_et_2->Write();
	hk0k0_et_3->Write();
	hk0k0_et_4->Write();
	hk0k0_et_5->Write();


	hcal_et_1->Write();
	hcal_et_2->Write();
	hcal_et_3->Write();
	hcal_et_4->Write();
	hcal_et_5->Write();

	h_njet->Write();

	h_delta->Write();

	h_jetAS->Write();
	h_jetnonAS->Write();
	h_d_ab->Write();

	hk0k0_d_ab1->Write();
	hk0k0_d_ab2->Write();
	hk0k0_d_ab3->Write();
	hk0k0_d_ab4->Write();

	h_delta_dlen3->Write();
	h_delta_dlen3_raw->Write();

	h_delta_dlen2->Write();

	h_dlen2->Write();
	h_dlen3->Write();
	h_dlen3_raw->Write();

	hddlen3_1->Write();
	hddlen3_2->Write();
	hddlen3_3->Write();
	hddlen3_4->Write();

	h_f0_pt->Write();
	h_angle->Write();

	hzvtx->Write();



	h2z_0->Write();
	h2z_1->Write();
	h2z_2->Write();
	h2z_3->Write();

	heta_1->Write();
	heta_2->Write();
	heta_1a->Write();
	heta_2a->Write();
	h_ntracks->Write();

	h_number_of_KK_pairs->Write();

	h_mass_pi_p->Write();

	hLambda_before->Write();
	hLambda_after->Write();

	hK0_04p->Write();
	hK0_05e->Write();
	hK0_06e->Write();
	hK0_06p->Write();
	hK0_07p->Write();

	h_k0inv_total->Write();

	h_thetastar->Write();
	h_costhetastar->Write();

	h_costhetastar_f2prime->Write();
	h_costhetastar_bg->Write();

	h_costhetastar_k0->Write();

	h_cal_empz->Write();
	h_empz_rel->Write();

	h2zempz_0->Write();
	h2zempz_1->Write();

	htest->Write();

	cout<<err<<" errors"<<endl;
	cout<<f1->GetName()<<" created"<<endl;
	f1->Close();
	cout<<"OK"<<endl;
}
#ifndef __CINT__
int main(int argc, char **argv)
{
	analysis();
	return 0;
}
#endif
//_______________________________________________________________//
/*
				// _______ David's suggestions_____________________//

				Double_t		betax=(-1)*K0sK0s.GetPx_m()/K0sK0s.GetP_m();
				Double_t		betay=(-1)*K0sK0s.GetPy_m()/K0sK0s.GetP_m();
				Double_t		betaz=(-1)*K0sK0s.GetPz_m()/K0sK0s.GetP_m();

				Double_t		K0sK0s_p=K0sK0s.GetP_m();
				Double_t		K0sK0s_E=sqrt((K0sK0s.GetP_m())*(K0sK0s.GetP_m())+K0sK0s.GetMass_m(5,5)*K0sK0s.GetMass_m(5,5));

				Double_t		beta=K0sK0s_p/K0sK0s_E;
				TVector3		beta_vect(beta*betax,beta*betay,beta*betaz);

		TLorentzVector		K0s1_LorVect(K0s_cand1.GetPx(),K0s_cand1.GetPy(),K0s_cand1.GetPz(),
												K0s_cand1.GetEnergy(5));

		TLorentzVector		K0s2_LorVect(K0s_cand2.GetPx(),K0s_cand2.GetPy(),K0s_cand2.GetPz(),
												K0s_cand2.GetEnergy(5));

				K0s1_LorVect.Boost(beta_vect);
				K0s2_LorVect.Boost(beta_vect);

				TVector3		K0s1_rest=K0s1_LorVect.Vect();
				TVector3		K0s2_rest=K0s2_LorVect.Vect();
				//cout<<K0s1_rest.Angle(K0s2_rest)<<endl;

				TVector3	K0sK0s_v3(K0sK0s.GetPx_m(),K0sK0s.GetPy_m(),K0sK0s.GetPz_m());
				Double_t		thetastar=K0sK0s_v3.Angle(K0s1_rest);
				Double_t		costhetastar=cos(thetastar);
				h_thetastar->Fill(thetastar);
				h_costhetastar->Fill(costhetastar);
				if ((reso_mass<1.55)&&(reso_mass>1.45)) h_costhetastar_f2prime->Fill(costhetastar);

				if ((reso_mass>2.)&&(reso_mass<3.)) h_costhetastar_bg->Fill(costhetastar);
				//___________ TEST the same for K0s ___________//
				Daughter		pi1(p1[k01][0],p1[k01][1],p1[k01][2]);
				Daughter		pi2(p2[k01][0],p2[k01][1],p2[k01][2]);
				Mother		K0s_test(pi1,pi2);

				Daughter		pi11(p1[k02][0],p1[k02][1],p1[k02][2]);
				Daughter		pi21(p2[k02][0],p2[k02][1],p2[k02][2]);
				Mother		K0s_test1(pi11,pi21);

				Double_t		betaxK0s=(-1)*K0s_test.GetPx_m()/K0s_test.GetP_m();
				Double_t		betayK0s=(-1)*K0s_test.GetPy_m()/K0s_test.GetP_m();
				Double_t		betazK0s=(-1)*K0s_test.GetPz_m()/K0s_test.GetP_m();

				Double_t		K0s_test_p=K0s_test.GetP_m();
Double_t		K0s_test_E=sqrt(K0s_test_p*K0s_test_p+K0s_test.GetMass_m(4,4)*K0s_test.GetMass_m(4,4));

				Double_t		betaK0s=K0s_test_p/K0s_test_E;
				TVector3		betaK0s_vect(betaK0s*betaxK0s,betaK0s*betayK0s,betaK0s*betazK0s);


TLorentzVector		pi1_LorVect(pi1.GetPx(),pi1.GetPy(),pi1.GetPz(),
												pi1.GetEnergy(4));

TLorentzVector		pi2_LorVect(pi2.GetPx(),pi2.GetPy(),pi2.GetPz(),
												pi2.GetEnergy(4));

				pi1_LorVect.Boost(betaK0s_vect);
				pi2_LorVect.Boost(betaK0s_vect);

				TVector3		pi1_rest=pi1_LorVect.Vect();
				TVector3		pi2_rest=pi2_LorVect.Vect();
				TVector3	K0s_v3(K0s_test.GetPx_m(),K0s_test.GetPy_m(),K0s_test.GetPz_m());

				//cout<<pi1_rest.Angle(pi2_rest)<<endl;

				Double_t		thetastar_pi1=K0s_v3.Angle(pi1_rest);
				Double_t		thetastar_pi2=K0s_v3.Angle(pi2_rest);
				Double_t		thetastar_pi=0;
				if (thetastar_pi1<3.15159/2) thetastar_pi=thetastar_pi1;
				if (thetastar_pi2<3.15159/2) thetastar_pi=thetastar_pi2;
				//thetastar_pi=thetastar_pi1;
				//cout<<thetastar_pi1<<" "<<thetastar_pi2<<endl;
				Double_t		costhetastar_k0=cos(thetastar_pi);

				h_costhetastar_k0->Fill(costhetastar_k0);
*/
//_______________________________________________________________//
