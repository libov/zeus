//__________________________________________________________________//
// Fit K0sK0s invariant mass spectrum                               //
// using full Minuit in ROOT                                        //
// Libov Vladyslav, March 2009                                      //
//__________________________________________________________________//
#include "TMinuit.h"
#include "TMath.h"
#include "TMatrixD.h"
#include <stdlib>
#include <canvas.cxx>

using namespace std;
bool				areas_same=false;
Double_t			delta_value[25];
Double_t			chi2Min_value[25];
//___________________________ I N P U T ____________________________//
const TString				FileName="HERAII_basic_substr.root";
const TString				HistogramName="h2_signal";

//const TString				FileName="jet_test.root";
//const TString				HistogramName="h2";
//const TString				HistogramName="h_jetnonAS";

		TString				HistogramTitle="";

/*const TString				FileName="L3_data.root";
const TString				HistogramName="h_L3";*/

//TString				HistogramTitle="Incoherent. Single peak for f_{2}(1270)/a_{2}(1320)";
//TString				HistogramTitle="Incoherent. f_{2}(1270) and a_{2}(1320) constrained to PDG";
//TString				HistogramTitle="Incoherent. f_{2}(1270) and a_{2}(1320) free";
//TString				HistogramTitle="Coherent. Coherence factors fixed, #beta_{12}=#beta_{13}=#beta_{23}=1";
//TString				HistogramTitle="Coherent. #beta_{12}=#beta_{13}=#beta_{23} free ";
//TString				HistogramTitle="Coherent. #beta_{12}, #beta_{13}, #beta_{23} free ";
//TString				HistogramTitle="Coherent. #beta_{12} free, #beta_{13}=#beta_{23}=0 ";
//TString				HistogramTitle="Coherent. coefficients from #gamma#gamma, +5, -3, +2 ";
//TString				HistogramTitle="Coherent.  #beta_{13} free, #beta_{12}=#beta_{23}=0 ";
//TString				HistogramTitle="Coherent.  #beta_{13}=1, #beta_{12}=#beta_{23}=0 ";

// Fit range (the first non-zero bin is 14)
const Int_t					MinBin=21;
const Int_t					MaxBin=127;
/*const Int_t				MinBin=1;
const Int_t					MaxBin=52;*/
// Constraints on resonance parameters (PDG)
		bool					constraint_f2_1270_mass=true;
		bool					constraint_f2_1270_width=true;
		bool					constraint_a2_1320_mass=true;
		bool					constraint_a2_1320_width=true;
		bool					constraint_f2_1525_mass=true;
		bool					constraint_f2_1525_width=false;
		bool					constraint_f0_1710_mass=false;
		bool					constraint_f0_1710_width=false;
const bool					use_coefficients=false;
		bool					im_part=false;

//const Double_t				mass_correction=(1.0000-0.006);
const Double_t				mass_correction=1.0000;
// Initial areas of resonances
	Double_t					f2_1270_area_start=2000;//f2_1270_area_start=1771;
	Double_t					a2_1320_area_start=2000;//a2_1320_area_start=3345;
	Double_t					f2_1525_area_start=9000;//f2_1525_area_start=10075;
	Double_t					f0980_initial_area=50;
const	Double_t				ratio_initial=0.;ratio_initial=0.7;	// Initial ratio f0/f2prime


/*f2_1270_area_start=60886;
a2_1320_area_start=43238;
f2_1525_area_start=12411;*/

/*f2_1270_area_start=3800;
a2_1320_area_start=8400;
f2_1525_area_start=20612;*/
f2_1270_area_start=1453;
a2_1320_area_start=3600;
f2_1525_area_start=10000;



// deltas
//const Double_t				delta1_start=2.656;
//const Double_t				delta2_start=0.116;

//const Double_t				delta1_start=0;
//const Double_t				delta2_start=3.14;

const Double_t				delta1_start=0.;
const Double_t				delta2_start=0.;

// Interference options
const	bool					SINGLE_PEAK_a2f2=true;		// in case of single peak, f2 is zero and a2 is 																		// fitted
const Double_t				beta12_start=1.;
const Double_t				beta13_start=1.;
const Double_t				beta23_start=1.;
const bool					fix_beta12=true;
const bool					fix_beta13=true;
const bool					fix_beta23=true;
const bool					fix_delta1=true;
const bool					fix_delta2=true;

const bool					all_coherence_factors_SAME=false;
// Options for the fit function
const	bool					threshold_bg=false;
const Int_t					polinom_order=2; 	// in threshold function
const	bool					include_f0_980=false;
const bool					use_phase_space_f0_980=false;
const bool					quadratic_bg=false;
// This can imrove the fit if it doesn't converge,
// (lowers normalization of initial background function by this factor)
const Double_t				initial_bg_correction=1.05;

//_________________________ OTHER GLOBALS __________________________//
// __  PDG parameters __
// f2(1270)
const 	Double_t			mass_f2_1270_PDG=1.2751;
const 	Double_t			width_f2_1270_PDG=0.185;
const 	Double_t			mass_f2_1270_PDG_error=0.0012;
const 	Double_t			width_f2_1270_PDG_error=0.0029;
// a2(1320)
const 	Double_t			mass_a2_1320_PDG=1.3183;
const 	Double_t			width_a2_1320_PDG=0.107;
const 	Double_t			mass_a2_1320_PDG_error=0.0006;
const 	Double_t			width_a2_1320_PDG_error=0.005;
// f2(1525)
			Double_t			mass_f2_1525_PDG=1.525;
								//mass_f2_1525_PDG=1.515;
const 	Double_t			width_f2_1525_PDG=0.073;
const 	Double_t			mass_f2_1525_PDG_error=0.00005;
const 	Double_t			width_f2_1525_PDG_error=0.006;
// f0(1710)
const 	Double_t			mass_f0_1710_PDG=1.695;mass_f0_1710_PDG=1.724;//mass_f0_1710_PDG=1.767;
const 	Double_t			width_f0_1710_PDG=0.137;//width_f0_1710_PDG=0.187;
const 	Double_t			mass_f0_1710_PDG_error=0.007;
const 	Double_t			width_f0_1710_PDG_error=0.008;
//
const	Double_t				mK0=0.497648;
const	Double_t				mf0=0.98;
const	Double_t				Gf0=0.05;

const Double_t				f0_1500_mass=1.505;
const Double_t				f0_1500_width=0.109;
const bool					include_f0_1500=false;
const Double_t				f0_1500_initial_area=200;

const Double_t				f0_1370_mass=1.505;
const Double_t				f0_1500_width=0.109;
// path to histograms (always unchanged)
const TString path="/data/zenith226a/libov/results/K0sK0s_hist/";
//const TString path="";
//	create pointer to file with histograms, get histogram
TFile *f2 = new TFile(path+FileName);
TH1F *hmain = (TH1F*)f2->Get(HistogramName);
Double_t 			chi2Min = 1000;
Int_t					nbins=hmain->GetNbinsX();
Double_t 			bin_width=(5.0-0.8)/nbins;//bin_width=0.03;
const Double_t		LowerEdge=hmain->GetXaxis()->GetBinLowEdge(MinBin);
const Double_t		UpperEdge=hmain->GetXaxis()->GetBinUpEdge(MaxBin);
Int_t					npoints=MaxBin-MinBin+1;
Int_t					ndof=0;
Double_t				par[31];
Double_t				par_err[31];
Int_t					counter=1;				// used for object names
TMinuit *minuit = new TMinuit(31);

	TString ParName[31]=	{	"Bg: Norm","Bg: Exp slope","Bg: Power",
									"coef Linear","coef Quadr","","","","","",
				 			 		"f_{2}(1270) mass","f_{2}(1270) width",
									"a_{2}(1320) mass","a_{2}(1320) width",
							 		"f_{2}'(1525) mass", "f_{2}'(1525) width",
							 		"f_{0}(1710) mass","f_{0}(1710) width",
									"f_{2}(1270) area","a_{2}(1320) area","f_{2}(1525) area",
									"#delta_{1}","#delta_{2}",
									"coherence factor #beta_{12}","coherence factor #beta_{13}","coherence factor #beta_{23}",
									"Ratio f_{0}(1710)/f_{2}(1525)",
									"f_{0}(980) mass","f_{0}(980) width","f_{0}(980) norm",
									"f_{0}(1500) area"
							 	};
	Double_t startVal[31]= {	11520/11.2,-2.59,0.12,  // bg
	//Double_t startVal[31]= {	2,0.1,0.01,					// bg for L3 (set quadratic_bg=true)
									1.985,3.326,0,0,0,0,0,		// bg
									mass_f2_1270_PDG*mass_correction,width_f2_1270_PDG,
									mass_a2_1320_PDG*mass_correction,width_a2_1320_PDG,
									mass_f2_1525_PDG*mass_correction,width_f2_1525_PDG,
									mass_f0_1710_PDG*mass_correction,width_f0_1710_PDG,
									0,0,0,			// areas
									0,0,				// delta1,delta2
									0,0,0,			// coherence factors
									0,					// ratio f0(1710)/f2(1525)
									1.047,0.05,0,	// f0(980) parameters
									0					// f0(1500) area
								 };					// N.B. areas are initially set to zero -
									 					// we want to estimate bg parameters first
	Double_t fitStep[31] = {	0.01,0.001,0.001,
									0.01,0.01,0.01,0.01,0.01,0.01,0.01,
									0.01,0.01,
									0.01,0.01,
									0.10,0.01,
									0.01,0.01,
									0.01,0.01,0.01,
									0.01,0.01,
									0.01,0.01,0.01,
									0.10,0.1,0.1,0.1,
									0.1};
	Double_t limitMin[31]={	0,0,0,
									0,0,0,0,0,0,0,
									0,0,
									0,0,
									0,0,
									0,0,
									0,0,0,
									-3.14159,-3.14159,
									-0.000001,-0.000001,-0.000001
									0,
									0,0,0,
									0.001
								};
	Double_t limitMax[31]={	0,0,0,
									0,0,0,0,0,0,0,
									0,0,
									0,0.3,
									0,0,
									0,0,
									0,0,0,
									3.14159,3.14159,
									1.0001,1.0001,1.0001
									0,
									0,0,0,
									1000.
								};
	bool		Fixed[31];
// ________ other golbals _______//
// -- from FitFunction()
/*Double_t			M[5],
					G[5];
Double_t			ReBW[5],		// Real part of ith peak
					ImBW[5],		// Imaginary part of ith peak
					den[5];		// denominator of ith peak
Double_t			m=0;							// function variable
Double_t			temp1=0,
					temp2=0;
Double_t			alpha[4];
Double_t			delta1=0;
Double_t			delta2=0;
Double_t			coh_fact_12=0;
Double_t			coh_fact_13=0;
Double_t			coh_fact_23=0;
Double_t			f0_1710_ampl=0;
Double_t			incoherent=0;
Double_t			coherent=0;

Double_t			interf_12=0;
Double_t			interf_13=0;
Double_t			interf_23=0;

Double_t			interference=0;
Double_t			signal=0;*/
// -- BackgroundFunction_simple

//_______________________________//

//__________________________________________________________________//
void K0K0_FITTER()
{
	cout<<"________________________________________________________________________________"<<endl;
	cout<<"_________________                                              _________________"<<endl;
	cout<<"_________________ Welcome to MEGA fitter of K0sK0s spectrum :) _________________"<<endl;
	cout<<"________________________________________________________________________________"<<endl;
	cout<<endl;
	cout<<"Number of bins in the histogram: "<<nbins<<endl;
	cout<<"Histogram bin width: "<<bin_width<<endl;;
	cout<<"Fit range: "<<LowerEdge<<"  -->  "<<UpperEdge<<endl;

	CreateCanvas();
	//----- Histogram settings -----//
	//hmain->SetTitle("ZEUS");
	hmain->SetTitle(HistogramTitle);
	hmain->Sumw2();
	hmain->SetMarkerStyle(20);
	hmain->GetYaxis()->SetTitleOffset(1.3);
	char Ytitle[25];
	Int_t n=sprintf(Ytitle,"Combinations/ %1.3f GeV",bin_width);
	hmain->SetYTitle(Ytitle);
	hmain->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
	hmain->GetXaxis()->SetRangeUser(0.95,3);
	//hmain->GetYaxis()->SetRangeUser(-500,9000);
	hmain->GetYaxis()->SetLabelSize(0.03);
	hmain->Draw();
	//------------------------------//

	minuit->SetFCN(&fcn);
	//minuit->SetPrintLevel(0);

	for (int ii=0;ii<31;ii++)	Fixed[ii]=false;

	for (int i=0;i<31;i++)
		minuit->DefineParameter(i,ParName[i],startVal[i],fitStep[i],limitMin[i],limitMax[i]);

	// ______________  Background estimation  __________________//
	// fix all parameters except background ones
	for (int i=0;i<31;i++)
		Fix(i);

	// in case of simple bg
	Release(0);
	Release(1);
	Release(2);

	// -- For threshold function release also polinom coefficients
	if (threshold_bg)
	{
		for (int k=3; k<(3+polinom_order); k++)
			Release(k);
	}
	// -- For L3 quadratic background
	if (quadratic_bg)	Fix(0);
	// -- Estimate background parameters
	minuit->Migrad();
	minuit->Migrad();
	GetParametersMinuit();

	par[0]=par[0]/initial_bg_correction;	// correct initial background normalization,
														// try this if fit doesn't converge
	minuit->DefineParameter(0,ParName[0],par[0],fitStep[0],limitMin[0],limitMax[0]);

	if (quadratic_bg)
	{
		par[1]=par[1]/3;
		minuit->DefineParameter(1,ParName[1],par[1],fitStep[1],limitMin[1],limitMax[1]);
	}

	// -- Draw initial background function
	DrawFunction(4,3,1);  	// DrawFunction(Int_t color, Int_t style, Int_t width)

	// _________________  Resonance inclusion  ___________________//
	// __  Setting free parameters, definition of start values ___//
	// release ALL resonance parameters, coherence factors, etc. (except f0(980), f0(1500))
	for (int i=10;i<27;i++)
		Release(i);

	// set chi2Min to large number again
	chi2Min = 1000;

	if (SINGLE_PEAK_a2f2)		// in case of this option f2 is zero, a2 is treated as sum of f2/a2
	{
		f2_1270_area_start=0;
	}
	// -- set start values for areas
	startVal[18]=f2_1270_area_start;
	startVal[19]=a2_1320_area_start;
	startVal[20]=f2_1525_area_start;		//startVal[20]=70;

	startVal[21]=delta1_start;
	startVal[22]=delta2_start;

	startVal[23]=beta12_start;
	startVal[24]=beta13_start;
	startVal[25]=beta23_start;

	startVal[26]=ratio_initial;		// start value for f0(1710)/f2(1525) ratio

	// resonance parameters (par[10]->par[17]) were already defined

	// alpha1, alpha2, alpha3
 	minuit->DefineParameter(18,ParName[18],startVal[18],fitStep[18],limitMin[18],limitMax[18]);
 	minuit->DefineParameter(19,ParName[19],startVal[19],fitStep[19],limitMin[19],limitMax[19]);
 	minuit->DefineParameter(20,ParName[20],startVal[20],fitStep[20],limitMin[20],limitMax[20]);
	//delta1, delta2
 	minuit->DefineParameter(21,ParName[21],startVal[21],fitStep[21],limitMin[21],limitMax[21]);
 	minuit->DefineParameter(22,ParName[22],startVal[22],fitStep[22],limitMin[22],limitMax[22]);
	// coherence factors
	minuit->DefineParameter(23,ParName[23],startVal[23],fitStep[23],limitMin[23],limitMax[23]);
	minuit->DefineParameter(24,ParName[24],startVal[24],fitStep[24],limitMin[24],limitMax[24]);
	minuit->DefineParameter(25,ParName[25],startVal[25],fitStep[25],limitMin[25],limitMax[25]);
	// f01710)
	minuit->DefineParameter(26,ParName[26],startVal[26],fitStep[26],limitMin[26],limitMax[26]);

	if(SINGLE_PEAK_a2f2)
	{
		constraint_f2_1270_mass=false;		// set to false so that no terms in chi2 and
		constraint_f2_1270_width=false;		// no additional n.d.o.f.
		Fix(10);  									// however fix them (m, G of f2(1270))
		Fix(11);
		Fix(18);										// fix area of f2(1270) to zero (defined above)
		constraint_a2_1320_mass=false;		// a2 (treated as f2/a2) should be free
		constraint_a2_1320_width=false;
	}

	// fix delta on request
	if (fix_delta1) Fix(21);
	if (fix_delta2) Fix(22);

	// fix coherence factors on request
	if (fix_beta12) Fix(23);
	if (fix_beta13) Fix(24);
	if (fix_beta23) Fix(25);

	if (use_coefficients)
	{

		startVal[18]=1.000;
		ParName[18]="Correction to f_{2}(1525) amplitude";
		minuit->DefineParameter(18,ParName[18],startVal[18],fitStep[18],limitMin[18],limitMax[18]);
		Fix(18);

		ParName[19]="Imaginary part";
		startVal[19]=0;
		minuit->DefineParameter(19,ParName[19],startVal[19],fitStep[19],limitMin[19],limitMax[19]);
		Fix(19);

		if (im_part)
		{
			startVal[26]=1500.;
			ParName[26]="Area of f_{0}(1710)";
			minuit->DefineParameter(26,ParName[26],startVal[26],fitStep[26],limitMin[26],limitMax[26]);

			startVal[20]=15;
			ParName[20]="total norm";
			minuit->DefineParameter(20,ParName[20],startVal[20],fitStep[20],limitMin[20],limitMax[20]);

			Release(19);

		}

		//
		Release(26);
	}

	// include f0(980) on request
	if (include_f0_980)
	{
		startVal[29]=f0980_initial_area;		// area of f0(980)
		minuit->DefineParameter(29,ParName[29],startVal[29],fitStep[29],limitMin[29],limitMax[29]);
		Release(29);
		if (!use_phase_space_f0_980)  		// (?) fix f0(980) mass and width
		{
			Release(27);
			Release(28);
		}
	}

	if(include_f0_1500)
	{
		Release(30);
		startVal[30]=f0_1500_initial_area;
		cout<<limitMax[21]<<endl;
		cout<<"************************* "<<limitMin[30]<<" **** "<<limitMax[30]<<endl;
		//minuit->DefineParameter(30,ParName[30],startVal[30],fitStep[30],limitMin[30],limitMax[30]);
		minuit->DefineParameter(30,ParName[30],startVal[30],fitStep[30],0,10000);
		//Fix(30);
	}

	if (areas_same)
	{
		Fix(18);
		Fix(19);
	}
	//______________________________________________________________//

	// -- Draw initial total function
	GetParametersMinuit();
	DrawFunction(4,3,1);  	// DrawFunction(Int_t color, Int_t style, Int_t width)

	// -- Perform minimization --

	//Fix(26);
		//Fix(16);
		//Fix(17);

	chi2Min=1000;
	minuit->Migrad();
	chi2Min=1000;
	minuit->Migrad();
	chi2Min=1000;
	minuit->Migrad();


		/*constraint_f2_1270_mass=false;
		constraint_f2_1270_width=false;
		constraint_a2_1320_mass=false;
		constraint_a2_1320_width=false;
		chi2Min=1000;
		minuit->Migrad();

		constraint_f0_1710_width=true;
		chi2Min=1000;
		minuit->Migrad();*/


	/*Release(18);
	Release(19);
	Release(20);
	chi2Min=1000;
	minuit->Migrad();
	*/


	/*chi2Min=1000;
	minuit->DefineParameter(22,ParName[22],1*0.35,fitStep[22],limitMin[22],limitMax[22]);
	minuit->Migrad();*/

/*
	for (int kkk=0;kkk<21;kkk++)
	{
		cout<<"-----------------   Fitting with new DELTA2    ----------------------"<<endl;
		delta_value[kkk]=-3.1+kkk*0.30;
		cout<<"------------------- delta2= "<<delta_value[kkk]<<" -------------------"<<endl;
		chi2Min=1000;
		minuit->DefineParameter(22,ParName[22],delta_value[kkk],fitStep[22],limitMin[22],limitMax[22]);
		Fix(22);
		minuit->Migrad();
		minuit->Migrad();
		chi2Min_value[kkk]=chi2Min;
		cout<<"CHI2= "<<chi2Min_value[kkk]<<endl;
		cout<<"-------------------------- END of FITTING ----------------------------"<<endl;
	}
*/


	//	cout<<"Call mnimpr()"<<endl;
	//	minuit->mnimpr();
	//	cout<<"Call mnseek()"<<endl;
	//	minuit->mnseek();
	//	cout<<"Call mnerrs()"<<endl;
	//	minuit->mnerrs();


	//_______________________________________________//

	//	release/fix something and repeat fit

	// im_part=true;
	// minuit->Migrad();

	//_______________________________________________//
	/*constraint_f2_1270_mass=false;
	constraint_f2_1270_width=false;
	constraint_a2_1320_mass=false;
	constraint_a2_1320_width=false;
	constraint_f2_1525_mass=false;
	constraint_f2_1525_width=false;
	constraint_f0_1710_mass=false;
	constraint_f0_1710_width=false;
	minuit->Migrad();*/
	/*chi2Min=1000.;
	constraint_f0_1710_width=false;
	minuit->Migrad();*/


	//______________ R E S U L T S___________________//

	// --draw total function after fit
	GetParametersMinuit();
	DrawFunction(2,1,3);

	// set resonance areas to zero to draw background
	par[18]=0;
	par[19]=0;
	par[20]=0;

	par[23]=0;
	par[24]=0;
	par[25]=0;

	par[26]=0;
	par[29]=0;
	par[30]=0;
	DrawFunction(3,1,3);

	// -- draw signal without background
	GetParametersMinuit();
	par[0]=0;
	DrawFunction(4,1,3);

	GetParametersMinuit();

	// -- calculate number of degrees of freedom
	Int_t		nparameters=0;
	for (int k=0;k<31;k++)
	{
		if (!Fixed[k])	nparameters++;
	}
	ndof=npoints-nparameters;
	if (constraint_f2_1270_mass)	ndof++;
	if (constraint_f2_1270_width)	ndof++;
	if (constraint_a2_1320_mass)	ndof++;
	if (constraint_a2_1320_width)	ndof++;
	if (constraint_f2_1525_mass)	ndof++;
	if (constraint_f2_1525_width)	ndof++;
	if (constraint_f0_1710_mass)	ndof++;
	if (constraint_f0_1710_width)	ndof++;

	cout<<"Chi2 min: "<<chi2Min<<endl;
	cout<<"ndof: "<<ndof<<endl;
	cout<<"chi2/ndof: "<<chi2Min/ndof<<endl;

	DrawPaveText();		// draw TPaveText's with main results
	// -- draw states separately
	GetParametersMinuit();
	TF1 *f1;
	TF1 *f2;
	TF1 *f3;

	if (use_coefficients)
	{
		f1=new TF1 ("f1",BreitWigner,1,2,3);
		f2=new TF1 ("f2",BreitWigner,1,2,3);
		f3=new TF1 ("f3",BreitWigner,1,2,3);
		f1->SetParameters(par[10],par[11],par[20]*(25./4.));
		f2->SetParameters(par[12],par[13],par[20]*(9./4.));
		f3->SetParameters(par[14],par[15],par[20]);
	}
	else
	{
		f1=new TF1 ("f1",BreitWigner,1,2,3);
		f2=new TF1 ("f2",BreitWigner,1,2,3);
		f3=new TF1 ("f3",BreitWigner,1,2,3);
		f1->SetParameters(par[10],par[11],par[18]);
		f2->SetParameters(par[12],par[13],par[19]);
		f3->SetParameters(par[14],par[15],par[20]);
	}

	TF1 *f4=new TF1 ("f4",BreitWigner,1,2,3);
	f4->SetParameters(par[16],par[17],par[26]*par[20]);

	f1->Draw("same");
	cout<<"Integral1= "<<f1->Integral(par[10]-3*par[11],par[10]+3*par[11])/bin_width<<endl;

	f2->Draw("same");
	cout<<"Integral2= "<<f2->Integral(par[12]-3*par[13],par[12]+3*par[13])/bin_width<<endl;

	f3->Draw("same");
	cout<<"Integral3= "<<f3->Integral(par[14]-3*par[15],par[14]+3*par[15])/bin_width<<endl;

	f4->Draw("same");
	cout<<"Integral4= "<<f4->Integral(par[16]-3*par[17],par[16]+3*par[17])/bin_width<<endl;


	if (include_f0_1500)
	{
		TF1 *f_1500=new TF1 ("f_1500",BreitWigner,1,2,3);
		f_1500->SetParameters(f0_1500_mass,f0_1500_width,par[30]);
		f_1500->Draw("same");
	}

	// pull distribution
	/*
	TF1 *fsum=new TF1("fsum",FitFunction,0.995,3,31);
	fsum->SetParameters(par);
	TH1F *hpull=new TH1F("hpull","",280,0.8,5);
	for(int bin=20;bin<148;bin++)
	{
		Double_t			error=hmain->GetBinError(bin);
		Double_t			bin_content=hmain->GetBinContent(bin);
		Double_t			bin_center=hmain->GetBinCenter(bin);
		Double_t			fitted_value=fsum->Eval(bin_center);
		Double_t			deviation=fitted_value-bin_content;
		hpull->SetBinContent(bin,deviation);
		hpull->SetBinError(bin,error);
	}
	hpull->Draw("same");
	*/


	// scanning
/*
	Int_t	out=minuit->Command("SCAN 23 50");
	cout<<"scan res= "<<out<<endl;
	if (out==0)		//  if scanning is successfull draw result
	{
		TGraph *gr = (TGraph*) minuit->GetPlot();
		gr->Draw("al");
	}
*/

	/*
	// 1sigma and 2sigma contour plotting
	minuit->SetErrorDef(2);
	TGraph* cont1=(TGraph*) minuit->Contour(30,7,8);
	cont1->Draw("AL");
	minuit->SetErrorDef(1);
	TGraph* cont2=(TGraph*) minuit->Contour(30,7,8);
	cont2->Draw("Lsame");
	*/
/*
	cout<<"************************************************************"<<endl;
	cout<<"************************************************************"<<endl;
	cout<<"************************************************************"<<endl;
	for (int kkk=0;kkk<21;kkk++)
	{

		cout<<delta_value[kkk]<<" -- "<<chi2Min_value[kkk]<<endl;
	}
	cout<<"************************************************************"<<endl;
	cout<<"************************************************************"<<endl;
	cout<<"************************************************************"<<endl;
*/
}
//__________________________________________________________________//

// Computation of chi2
void fcn(Int_t& npar, Double_t* grad, Double_t& f, Double_t par[], Int_t iflag)
{
   // Evaluate the minimisation function -------------------------------------
   //
   //  Input parameters:
   //    npar:    number of currently variable parameters
   //             CAUTION: this is not (necessarily) the dimension of the fitPars vector !
   //    par:     array of (constant and variable) parameters
   //    iflag:   indicates what is to be calculated
   //    grad:    array of gradients
   //
   //  Output parameters:
   //    f:       the calculated function value.
   //    grad:    the (optional) vector of first derivatives.
   // ------------------------------------------------------------------------

	// -- compute chi2
	Double_t chi2 = 0;
	for (int bin=MinBin;bin<MaxBin+1;bin++)
	{
		Double_t		BinContent=hmain->GetBinContent(bin);
		Double_t		BinError=hmain->GetBinError(bin);
		Double_t		BinCenter=hmain->GetXaxis()->GetBinCenter(bin);
		Double_t		FitFunctionValue=FitFunction(&BinCenter, par);
		Double_t		deviation=BinContent-FitFunctionValue;
		chi2=chi2+(deviation**2)/(BinError**2);
	}
	// -- constraints
	if (constraint_f2_1270_mass)	chi2+=((par[10]-mass_f2_1270_PDG)/(mass_f2_1270_PDG_error))**2;
	if (constraint_f2_1270_width)	chi2+=((par[11]-width_f2_1270_PDG)/(width_f2_1270_PDG_error))**2;
	if (constraint_a2_1320_mass)	chi2+=((par[12]-mass_a2_1320_PDG)/(mass_a2_1320_PDG_error))**2;
	if (constraint_a2_1320_width)	chi2+=((par[13]-width_a2_1320_PDG)/(width_a2_1320_PDG_error))**2;
	if (constraint_f2_1525_mass)	chi2+=((par[14]-mass_f2_1525_PDG)/(mass_f2_1525_PDG_error))**2;
	if (constraint_f2_1525_width)	chi2+=((par[15]-width_f2_1525_PDG)/(width_f2_1525_PDG_error))**2;
	if (constraint_f0_1710_mass)	chi2+=((par[16]-mass_f0_1710_PDG)/(mass_f0_1710_PDG_error))**2;
	if (constraint_f0_1710_width)	chi2+=((par[17]-width_f0_1710_PDG)/(width_f0_1710_PDG_error))**2;

	// -- save minimum chi2
	if (chi2 < chi2Min) chi2Min = chi2;
	f = chi2;
}
//__________________________________________________________________//
Double_t	FitFunction(Double_t *x,Double_t *par)
{
	//_______________
	// -- from FitFunction()
Double_t			M[5],
					G[5];
Double_t			ReBW[5],		// Real part of ith peak
					ImBW[5],		// Imaginary part of ith peak
					den[5];		// denominator of ith peak
Double_t			m=0;							// function variable
Double_t			temp1=0,
					temp2=0;
Double_t			alpha[4];
Double_t			delta1=0;
Double_t			delta2=0;
Double_t			coh_fact_12=0;
Double_t			coh_fact_13=0;
Double_t			coh_fact_23=0;
Double_t			f0_1710_ampl=0;
Double_t			incoherent=0;
Double_t			coherent=0;

Double_t			interf_12=0;
Double_t			interf_13=0;
Double_t			interf_23=0;

Double_t			interference=0;
Double_t			signal=0;

	//_______________
	// -- Parameters of bw-functions
	M[1]=par[10];		// f2(1270) mass
	G[1]=par[11];		// f2(1270) width
	M[2]=par[12];		// a2(1320) mass
	G[2]=par[13];		// a2(1320) width
	M[3]=par[14];		// f2(1525) mass
	G[3]=par[15];		// f2(1525) width
	M[4]=par[16];		// f0(1710) mass
	G[4]=par[17];		// f0(1710) width

	m=x[0];				// function variable

	for (int i=1;i<5;i++)
	{
		temp1=M[i]**2-m**2;
		temp2=M[i]*sqrt(G[i]);
		den[i]=temp1**2+(M[i]*G[i])**2;
		ReBW[i]=(temp1*temp2)/den[i];
		ImBW[i]=temp2*M[i]*G[i]/den[i];
	}

	alpha[1]=sqrt(par[18]*bin_width/((par[10]**2)*par[11]*integral(par[10],par[11])));
	alpha[2]=sqrt(par[19]*bin_width/((par[12]**2)*par[13]*integral(par[12],par[13])));
	alpha[3]=sqrt(par[20]*bin_width/((par[14]**2)*par[15]*integral(par[14],par[15])));

	if (areas_same)
	{
		alpha[1]=sqrt(par[20]*bin_width/((par[10]**2)*par[11]*integral(par[10],par[11])));
		alpha[2]=sqrt(par[20]*bin_width/((par[12]**2)*par[13]*integral(par[12],par[13])));
		alpha[3]=sqrt(par[20]*bin_width/((par[14]**2)*par[15]*integral(par[14],par[15])));
	}

	delta1=par[21];
	delta2=par[22];

	coh_fact_12=par[23];
	coh_fact_13=par[24];
	coh_fact_23=par[25];

	if		(all_coherence_factors_SAME)
	{
		coh_fact_13=coh_fact_12;
		coh_fact_23=coh_fact_12;
	}

	if (use_coefficients)
	{
		Double_t		Im=par[19];
		Double_t		f2prime_corr=par[18];
		//alpha[1]=sqrt(5**2+Im**2);
		//alpha[2]=(-1)*sqrt(3**2+Im**2);
		//f2_1525_area=sqrt(par[20]**2+par[19]**2);
		alpha[3]=f2prime_corr*sqrt(par[20]*bin_width/((par[14]**2)*par[15]*integral(par[14],par[15])));
		alpha[1]=alpha[3]*(5./2.);
		alpha[2]=(-1)*alpha[3]*(3./2.);

		delta1=atan(Im/5.);
		if ((delta1>3.1459/2)||(delta1<(-1)*3.1459/2)) cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		delta2=atan(Im/3.);
	}
	if (im_part)
	{
		Double_t		Im=par[19];
		alpha[1]=sqrt(par[20])*sqrt(5**2+Im**2);
		alpha[2]=(-1)*sqrt(par[20])*sqrt(3**2+Im**2);
		alpha[3]=sqrt(par[20])*sqrt(2**2+Im**2);

		delta1=atan(Im/5.)-atan(Im/2.);
		delta2=-atan(Im/3.)-atan(Im/2.);
	}

	f0_1710_ampl=sqrt(par[26]*par[20]*bin_width/((par[16]**2)*par[17]*integral(par[16],par[17])));
	if (im_part)
	{
		f0_1710_ampl=sqrt(par[26]*bin_width/((par[16]**2)*par[17]*integral(par[16],par[17])));
	}

	incoherent=0;
	for (int k=1;k<4;k++)
	{
		incoherent+=(alpha[k]**2)*(ReBW[k]**2+ImBW[k]**2);
	}
	coherent=0;

	interf_12=0;
	interf_13=0;
	interf_23=0;

	interf_12+=2*alpha[1]*alpha[2]*cos(delta1-delta2)*(ReBW[1]*ReBW[2]+ImBW[1]*ImBW[2]);
	interf_12+=2*alpha[1]*alpha[2]*sin(delta1-delta2)*(ReBW[1]*ImBW[2]-ReBW[2]*ImBW[1]);
	interf_12=interf_12*coh_fact_12;

	interf_13+=2*alpha[1]*alpha[3]*cos(delta1)*(ReBW[1]*ReBW[3]+ImBW[1]*ImBW[3]);
	interf_13+=2*alpha[1]*alpha[3]*sin(delta1)*(ReBW[1]*ImBW[3]-ReBW[3]*ImBW[1]);
	interf_13=interf_13*coh_fact_13;

	interf_23+=2*alpha[2]*alpha[3]*cos(delta2)*(ReBW[2]*ReBW[3]+ImBW[2]*ImBW[3]);
	interf_23+=2*alpha[2]*alpha[3]*sin(delta2)*(ReBW[2]*ImBW[3]-ReBW[3]*ImBW[2]);
	interf_23=interf_23*coh_fact_23;

	interference=0;
	interference=interf_12+interf_13+interf_23;
	signal=0;
	signal=incoherent+interference+(f0_1710_ampl**2)*(ReBW[4]**2+ImBW[4]**2);

	//____________________

 	//Double_t		signal=bin_width*(par[16]*bw1+par[17]*(bw2+par[18]*bw3));
	if (include_f0_980)
	{
		signal=signal+f0_980(x, par);
	}

	if (include_f0_1500)
	{
		signal=signal+f0_1500(x, par);
	}

	Double_t		bg=0;
	if (threshold_bg)
	{
		bg=BackgroundFunction_threshold(x, par);
	}
	else
	{
		bg=BackgroundFunction_simple(x, par);
	}
	if (quadratic_bg)
	{
		bg=par[1]*((x[0]-0.995)+par[2]*((x[0]-0.995)**2));
	}
	return bg+signal;
}
//____________________ Simple Background ___________________________//
Double_t	BackgroundFunction_simple(Double_t *x,Double_t *par)
{
	Double_t		q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*q);
	Double_t		pow=TMath::Power(q,par[2]);
	Double_t		bg=par[0]*exp*pow;
	return 		bg;
}
//________________ Background with threshold _______________________//
Double_t	BackgroundFunction_threshold(Double_t *x,Double_t *par)
{
	Double_t		bg=0;
	Double_t		mKK=2*0.497672;
	Double_t 	q=x[0]-mKK;
	if (q<0) 	bg=0;
	Double_t		q2=q**2;
	Double_t		q3=q**3;
	Double_t		q4=q**4;
	Double_t		q5=q**5;

	Double_t		pol2=par[1]*q;

	Double_t		f1=par[3]*q;
	Double_t		f2=par[4]*q2;
	Double_t		f3=par[5]*q3;
	Double_t		f4=par[6]*q4;
	Double_t		f5=par[7]*q5;

	bg=par[0]*TMath::Power(q,(par[2]**2))*(1+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
	return 		bg;
}
//____________________________ f0(980) _____________________________//
Double_t	f0_980(Double_t *x, Double_t *par)
{
	Double_t		f0_980=0;
	if (use_phase_space_f0_980)
	{
		f0_980=f0_980_phase_space(x, par);
	}
	else
	{
		f0_980=f0_980_bw(x, par);
	}
	return 		f0_980;
}
// -------  simple breit-wigner form  -------- //
Double_t	f0_980_bw(Double_t *x, Double_t *par)
{
	Double_t		x2=x[0]**2;
	Double_t 	m4=TMath::Power(par[27],2);
	Double_t		g4=TMath::Power(par[28],2);
	Double_t		c4=integral(par[27],par[28]);
	Double_t 	bw4=1/(c4*(TMath::Power((x2-m4),2)+g4*m4));
	return 		par[29]*bw4;
}
//__________________________________________________________________//
// -------  breit-wigner multiplied by phase-space factor  -------- //
Double_t	f0_980_phase_space(Double_t *x, Double_t *par)
{
	/*Double_t		x2=x[0]**2;
	Double_t 	m4=TMath::Power(par[19],2);
	Double_t		g4=TMath::Power(par[20],2);
	Double_t		c4=integral(par[19],par[20]);
	Double_t 	bw4=1/(c4*(TMath::Power((x2-m4),2)+g4*m4));*/
	//return 		par[21]*bw4;

	//-------------------
	Double_t		m=x[0];
	Double_t		ph_space=0,
					bw=0;
	//Double_t		Gf0=par[1];
	ph_space=TMath::Power((1-4*(mK0/m)*(mK0/m)),0.5);
	Double_t			mf0_sq=mf0*mf0;
	bw=(mf0_sq*sqrt(Gf0*Gf0))/((mf0_sq-m*m)**2+mf0_sq*(Gf0**2));
	Double_t		f0=par[29]*bw*ph_space;
	return		f0;
	//-------------------
}

//	calculation of Breit-Wigner function integral using analytical ansatz from Ryzhik
Double_t	integral(Double_t m, Double_t G)
{
	if (m==0) cout<<m<<endl;
	if (G==0) cout<<G<<endl;
	Double_t	a=(m**4)+(m**2)*(G**2);
	Double_t	b=(-2)*(m**2);
	Double_t	c=1.0000;
	if ((a/c)<=0)	cout<<"Disaster!!! a/c<= "<<a/c<<endl;
	Double_t	q=TMath::Power((a/c),0.2500);
	Double_t	cos_alpha=(-0.5)*b/(sqrt(a*c));
	Double_t	sin_alpha=sqrt(1-cos_alpha**2);
	Double_t	cos_halfalpha=sqrt(0.50*(1+cos_alpha));

	Double_t	pi=TMath::Pi();
	Double_t	integral=(pi*cos_halfalpha)/(2*c*(q**3)*sin_alpha);

	return integral;
}
//__________________________________________________________________//
void DrawFunction(Int_t	color=4, Int_t	style=1,Int_t width=3)
{
	TString name="fsum";
	name+=counter;
	TF1 *fsum=new TF1(name,FitFunction,LowerEdge,UpperEdge,31);
	fsum->SetParameters(par);
	fsum->SetLineColor(color);
	fsum->SetLineWidth(width);
	fsum->SetLineStyle(style);
	fsum->SetNpx(1000);
	fsum->Draw("same");
	cout<<name<<endl;
	counter++;
}
//__________________________________________________________________//
// saves fit parameters from MINUIT to par[] array
void	GetParametersMinuit()
{
	for (int k=0; k<31;k++)
	minuit->GetParameter(k, par[k], par_err[k]);
}
//__________________________________________________________________//
Double_t	BreitWigner(Double_t *x, Double_t *par)
{

	Double_t 	x2=TMath::Power(x[0],2);
	Double_t 	m2=TMath::Power(par[0],2);
	Double_t		g2=TMath::Power(par[1],2);
	Double_t		c=integral(par[0],par[1]);
	Double_t 	bw=1/(c*(TMath::Power((x2-m2),2)+g2*m2));

	return par[2]*bin_width*bw;
}
//__________________________________________________________________//
Double_t	BreitWignerSimple(Double_t *x, Double_t *par)
{


	Double_t 	x2=TMath::Power(x[0],2);
	Double_t 	m2=TMath::Power(par[0],2);
	Double_t		g2=TMath::Power(par[1],2);
	Double_t 	bw=1.0/(TMath::Power((x2-m2),2)+g2*m2);

	return par[2]*bw*m2*par[1];
}
//__________________________________________________________________//


//__________________________________________________________________//
void DrawPaveText()
{
	TPaveText *pt = new TPaveText(0.5672461,0.1008111,0.8984446,0.8991889,"brNDC");
	char str1[256];
	Int_t	n=sprintf(str1,"#chi^{2}/ndf=%3.1f/%3i=%1.2f",chi2Min,ndof,chi2Min/ndof);
	text = pt->AddText(str1);
	TString str2="";
	for(int k=0;k<31;k++)
	{
		str2=ParName[k];
		if ((SINGLE_PEAK_a2f2)&&(k==12)) str2="f_{2}(1270)/a_{2}(1320) mass";
		if ((SINGLE_PEAK_a2f2)&&(k==13)) str2="f_{2}(1270)/a_{2}(1320) width";
		n=sprintf(str1," = %1.3f #pm %1.3f ",par[k],par_err[k]);
		str2+=str1;
		if ((k==10)&&(constraint_f2_1270_mass)) str2+=" (constrained)";
		if ((k==11)&&(constraint_f2_1270_width)) str2+=" (constrained)";
		if ((k==12)&&(constraint_a2_1320_mass)) str2+=" (constrained)";
		if ((k==13)&&(constraint_a2_1320_width)) str2+=" (constrained)";
		if ((k==14)&&(constraint_f2_1525_mass)) str2+=" (constrained)";
		if ((k==15)&&(constraint_f2_1525_width)) str2+=" (constrained)";
		if ((k==16)&&(constraint_f0_1710_mass)) str2+=" (constrained)";
		if ((k==17)&&(constraint_f0_1710_width)) str2+=" (constrained)";
		if	(!Fixed[k])	text = pt->AddText(str2);
	}
	pt->Draw("same");
	TPaveText *pt1 = new TPaveText(0.42,0.71,0.52,0.77,"brNDC");
	pt1->SetFillColor(0);
	TString	f0="f_{0}(1710)";
	text = pt1->AddText(f0);
	pt1->Draw("same");

	TPaveText *pt2 = new TPaveText(0.35,0.81,0.45,0.87,"brNDC");
	pt2->SetFillColor(0);
	TString	f0="f'_{2}(1525)";
	text = pt2->AddText(f0);
	pt2->Draw("same");

	TPaveText *pt3 = new TPaveText(0.1537054,0.2688297,0.4611162,0.5955968,"brNDC");
	pt3->SetFillColor(0);
	n=sprintf(str1,"#chi^{2}/ndf=%3.1f/%3i=%1.2f",chi2Min,ndof,chi2Min/ndof);
	text = pt3->AddText(str1);
	n=sprintf(str1, "#frac{f_{0}(1710)}{f_{2}(1525)}=%1.2f ",par[26]);
	text = pt3->AddText(str1);

	pt3->Draw("same");

 	pt = new TPaveText(1.287023,8474.21,2.465957,9323.208,"br");
   pt->SetLineColor(0);
   text = pt->AddText("ZEUS");
   pt->Draw("same");


}
//_________________________________________________________________//
void	Fix(Int_t	i)
{
		minuit->FixParameter(i);
		Fixed[i]=true;
}
void	Release(Int_t	i)
{
		minuit->Release(i);
		Fixed[i]=false;
}
//__________________________________________________________________//
/*void DrawPaveText()
{
	TPaveText *pt = new TPaveText(0.15,0.22,0.4,0.5,"brNDC");
	char result[256];
	Int_t	n=sprintf(result,"#chi^{2}/ndf=%3.1f/%3i=%1.2f",chi2Min,ndof,chi2Min/ndof);
	text = pt->AddText(result);
	n=sprintf(result,"Ratio f_{0}/f'_{2}= %2.2f #pm %2.2f ",par[18],par_err[18]);
	text = pt->AddText(result);
	if (constraint_f0_1710_width==true)
	{
		n=sprintf(result,"f_{0} width= %2.3f #pm %1.3f (CONSTRAINED)",par[15],par_err[15]);
	}
	if (constraint_f0_1710_width==false)
	{
		n=sprintf(result,"f_{0} width= %2.3f #pm %1.3f (FREE)",par[15],par_err[15]);
	}
	text = pt->AddText(result);
	if (constraint_f0_1710_mass==true)
	{
		n=sprintf(result,"f_{0} mass = %2.3f #pm %1.3f (CONSTRAINED)",par[14],par_err[14]);
	}
	if (constraint_f0_1710_mass==false)
	{
		n=sprintf(result,"f_{0} mass = %2.3f #pm %1.3f (FREE)",par[14],par_err[14]);
	}
	text = pt->AddText(result);
	n=sprintf(result,"f'_{2} mass = %1.3f #pm %1.3f" ,par[12],par_err[12]);
	text = pt->AddText(result);
	pt->SetFillColor(3);
	pt->Draw("same");
	//-------------------------------------------------------------------//

	TPaveText *pt1 = new TPaveText(0.42,0.71,0.52,0.77,"brNDC");
	pt1->SetFillColor(0);
	TString	f0="f_{0}(1710)";
	text = pt1->AddText(f0);
	pt1->Draw("same");

	TPaveText *pt2 = new TPaveText(0.35,0.81,0.45,0.87,"brNDC");
	pt2->SetFillColor(0);
	TString	f0="f'_{2}(1525)";
	text = pt2->AddText(f0);
	pt2->Draw("same");
}*/
//____________________________ f0(1500) _____________________________//
Double_t	f0_1500(Double_t *x, Double_t *par)
{
	Double_t		x2=x[0]**2;
	Double_t 	m4=TMath::Power(f0_1500_mass,2);
	Double_t		g4=TMath::Power(f0_1500_width,2);
	Double_t		c4=integral(f0_1500_mass,f0_1500_width);
	Double_t 	bw4=1/(c4*(TMath::Power((x2-m4),2)+g4*m4));
	return 		par[30]*bw4*bin_width;
}
//__________________________________________________________________//
//__________________________________________________________________//
Double_t	scalars(Double_t *x, Double_t *par)
{
	//Double_t		f0_1500_,

}

//__________________________________________________________________//


