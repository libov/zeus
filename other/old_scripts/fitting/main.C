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

//___________________________ I N P U T ____________________________//
const TString				FileName="HERAII_basic_substr.root";
const TString				HistogramName="h2_signal";
// Fit range (the first non-zero bin is 14)
const Int_t					MinBin=18;
const Int_t					MaxBin=127;
// Constraints of mass and width of f0(1710) (taking into account PDG error)
const bool					constraint_f0_width=true;
const bool					constraint_f0_mass=false;
// other consraints
const bool					constraint_a2_f2_width=true;
const Double_t				a2_f2_width=0.1;
const Double_t				a2_f2_width_error=0.02;
// Initial areas of resonances
const	Double_t				f2prime_initial_area=0.5*8000.0;
const	Double_t				a2_f2_initial_area=0.5*2*2000.0;
const Double_t				f0980_initial_area=30;
// Initial ratio f0/f2prime
const	Double_t				ratio_initial=0.9;
// Options for the fit function
const	bool					interference=false;
const	bool					threshold_bg=false;
const Int_t					polinom_order=2; // in threshold function
const	bool					include_f0_980=false;
const bool					use_phase_space_f0_980=false;
// This can imrove the fit if it doesn't converge,
// (lowers normalization of initial background function by this factor)
const Double_t				initial_bg_correction=1.05;
//__________________________________________________________________//

//_________________________ OTHER GLOBALS __________________________//
// PDG parameters for f0(1710) ...
const Double_t				f0_width_PDG=0.137;
const Double_t				f0_width_error_PDG=0.008;
const Double_t				f0_mass_PDG=1.718*(1-0.006);
const Double_t				f0_mass_error_PDG=0.007;
// ...and for f0=(980)
const	Double_t				mK0=0.497648;
const	Double_t				mf0=0.98;
const	Double_t				Gf0=0.05;
// path to histograms (always unchanged)
const TString path="/data/zenith226a/libov/results/K0sK0s_hist/";
//	create pointer to file with histograms
TFile *f2 = new TFile(path+FileName);
//	get histogram
TH1F *hmain = (TH1F*)f2->Get(HistogramName);
// minimal chi2
Double_t 			chi2Min = 1000;
// other
Int_t					nbins=hmain->GetNbinsX();
Double_t 			bin_width=(5.0-0.8)/nbins;
const Double_t		LowerEdge=hmain->GetXaxis()->GetBinLowEdge(MinBin);
const Double_t		UpperEdge=hmain->GetXaxis()->GetBinUpEdge(MaxBin);
Int_t					ndof=MaxBin-MinBin+1-12;
Double_t				par[25];
Double_t				par_err[25];
Int_t					counter=1;				// for object names
TMinuit *minuit = new TMinuit(25);
bool					DrawResonancesSeparately=false;
int					ResonanceToDraw=0;
//__________________________________________________________________//

//__________________________________________________________________//
void main()
{
	cout<<"_______________________________________________________________________________"<<endl;
	cout<<"___________________                                           _________________"<<endl;
	cout<<"___________________ This is MEGA fitter of K0sK0s spectrum :) _________________"<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	cout<<endl;
	cout<<"Number of bins in the histogram: "<<nbins<<endl;
	cout<<"Histogram bin width: "<<bin_width<<endl;;
	cout<<"Fit range: "<<LowerEdge<<"  -->  "<<UpperEdge<<endl;

	CreateCanvas();
	//----- Histogram settings -----//
	hmain->SetTitle("ZEUS");
	hmain->Sumw2();
	hmain->SetMarkerStyle(20);
	hmain->GetYaxis()->SetTitleOffset(1.3);
	char Ytitle[25];
	Int_t n=sprintf(Ytitle,"Combinations/ %1.3f GeV",bin_width);
	hmain->SetYTitle(Ytitle);
	hmain->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
	hmain->GetXaxis()->SetRangeUser(0.95,3);
	hmain->GetYaxis()->SetLabelSize(0.03);
	//------------------------------//
	hmain->Draw();


	minuit->SetFCN(&fcn);
	TString ParName[25]=	{	"Norm","Exp slope","Power",
									"coef Linear","coef Quadr",0,0,0,0,0,
				 			 		"a2/f2 mass","a2/f2 width",
							 		"f2' mass", "f2' width",
							 		"f0 mass","f0 width",
							 		"a2/f2 area","f2' area", "Ratio",
									0,0,0,0,0,
							 		"Bin Width"};
	Double_t startVal[25]= {	11520/11.2,-2.59,0.12,
									1.985,3.326,0,0,0,0,0,
	//Double_t startVal[25]= {	1000,-3,1.5,
	//								1,1,0,0,0,0,0,
									1.307,0.1,
									1.5,0.06,
									1.69,0.15,
									0,0,ratio_initial,
									1.047,0.05,0,0,0,
									0.015};	// N.B. areas are initially set to zero -
									 			// we want to estimate bg parameters first
	Double_t fitStep[25] = {	0.01,0.001,0.001,
									0.01,0.01,0.01,0.01,0.01,0.01,0.01,
									0.01,0.01,
									0.10,0.01,
									0.001,0.001,
									0.01,0.01,0.01,
									0.01,0.01,0.01,0.01,0.01,
									0.10};
	Double_t limitMin[25]={	0,0,0,
									0,0,0,0,0,0,0,
									0,0,
									0,0,
									0,0,
									0,0,0,
									0,0,0,0,0,
									0};
	Double_t limitMax[25]={	0,0,0,
									0,0,0,0,0,0,0,
									0	,0,
									0,0,
									0,0,
									200000,0,0,
									0,0,0,0,0,
									0};

	for (int i=0;i<25;i++)
		minuit->DefineParameter(i,ParName[i],startVal[i],fitStep[i],limitMin[i],limitMax[i]);

	// fix all parameters except background ones
	for (int i=0;i<25;i++)
		minuit->FixParameter(i);
	// in case of simple bg
	minuit->Release(0);
	minuit->Release(1);
	minuit->Release(2);
	// threshold function - release also polinom coefficients
	if (threshold_bg)
	{
		for (int k=3; k<(3+polinom_order); k++)
			minuit->Release(k);
	}
	// estimate background parameters
	minuit->Migrad();
	minuit->Migrad();
	GetParametersMinuit();

	par[0]=par[0]/initial_bg_correction;	// correct initial background normalization,
														// try this if fit doesn't converge
	minuit->DefineParameter(0,ParName[0],par[0],fitStep[0],limitMin[0],limitMax[0]);
	// Draw initial background function
	DrawFunction(4,3,1);  	// DrawFunction(Int_t color, Int_t style, Int_t width)

	// now release resonance parameters
	for (int i=10;i<19;i++)
		minuit->Release(i);

	// set chi2Min to large number again
	chi2Min = 1000;

	// set start values for areas
	startVal[16]=a2_f2_initial_area;			// area of a2/f2
	startVal[17]=f2prime_initial_area;		// area of f2'
	minuit->DefineParameter(16,ParName[16],startVal[16],fitStep[16],limitMin[16],limitMax[16]);
	minuit->DefineParameter(17,ParName[17],startVal[17],fitStep[17],limitMin[17],limitMax[17]);

	if (include_f0_980)
	{
		startVal[21]=f0980_initial_area;		// area of f0(980)
		minuit->DefineParameter(21,ParName[21],startVal[21],fitStep[21],limitMin[21],limitMax[21]);
		minuit->Release(21);
		if (!use_phase_space_f0_980)  // (?) fix f0(980) mass and width
		{
			minuit->Release(20);
			minuit->Release(19);
		}
	}

	// Draw initial total function
	GetParametersMinuit();
	DrawFunction(4,3,1);  	// DrawFunction(Int_t color, Int_t style, Int_t width)

	minuit->Migrad();
	minuit->Migrad();
	cout<<"Call mnimpr()"<<endl;
	minuit->mnimpr();
	cout<<"Call mnseek()"<<endl;
	minuit->mnseek();
	//minuit->mnerrs();

	GetParametersMinuit();

	// draw function after fit
	DrawFunction(2,1,3);

	cout<<"Chi2 min: "<<chi2Min<<endl;
	cout<<"ndof: "<<ndof<<endl;
	cout<<"chi2/ndof: "<<chi2Min/ndof<<endl;

	// set areas to zero again to draw background
	par[16]=0;
	par[17]=0;
	par[21]=0;
	DrawFunction(3,1,3);

	// draw signal
	GetParametersMinuit();
	par[0]=0;
	DrawFunction(4,1,3);

	// draw TPaveText's with main results
	DrawPaveText();
	// draw f2prime(1525)
	GetParametersMinuit();
	TF1 *f1=new TF1 ("f1",BreitWigner,1,2,3);
	f1->SetParameters(par[10],par[11],par[16]);
	f1->Draw("same");
	cout<<"Integral1= "<<f1->Integral(par[10]-10*par[11],par[10]+10*par[11])/bin_width<<endl;

	TF1 *f2=new TF1 ("f2",BreitWigner,1,2,3);
	f2->SetParameters(par[12],par[13],par[17]);
	f2->Draw("same");
	cout<<"Integral2= "<<f2->Integral(par[12]-10*par[13],par[12]+10*par[13])/bin_width<<endl;

	TF1 *f3=new TF1 ("f3",BreitWigner,1,2,3);
	f3->SetParameters(par[14],par[15],par[17]*par[18]);
	f3->Draw("same");
	cout<<"Integral3= "<<f3->Integral(par[14]-10*par[15],par[14]+10*par[15])/bin_width<<endl;






	/*
	// scanning
	Int_t	out=minuit->Command("SCAN 5 50");
	cout<<"scan res= "<<out<<endl;
	TGraph *gr = (TGraph*)gMinuit->GetPlot();
	gr->Draw("al");
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

	// compute chi2
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
	if (constraint_f0_width)	chi2=chi2+((par[15]-f0_width_PDG)**2)/(f0_width_error_PDG**2);
	if (constraint_f0_mass)		chi2=chi2+((par[14]-f0_mass_PDG)**2)/(f0_mass_error_PDG**2);
	if (constraint_a2_f2_width) chi2=chi2+((par[11]-a2_f2_width)**2)/(a2_f2_width_error**2);
	// save minimum chi2
	if (chi2 < chi2Min) chi2Min = chi2;
	f = chi2;
}
//__________________________________________________________________//
Double_t	FitFunction(Double_t *x,Double_t *par)
{
	Double_t 	x2=TMath::Power(x[0],2);

	Double_t 	m1=TMath::Power(par[10],2);
	Double_t		g1=TMath::Power(par[11],2);
	Double_t		c1=integral(par[10],par[11]);
	Double_t 	bw1=1/(c1*(TMath::Power((x2-m1),2)+g1*m1));

	Double_t 	m2=TMath::Power(par[12],2);
	Double_t		g2=TMath::Power(par[13],2);
	Double_t		c2=integral(par[12],par[13]);
	Double_t 	bw2=1/(c2*(TMath::Power((x2-m2),2)+g2*m2));

	Double_t 	m3=TMath::Power(par[14],2);
	Double_t		g3=TMath::Power(par[15],2);
	Double_t		c3=integral(par[14],par[15]);
	Double_t 	bw3=1/(c3*(TMath::Power((x2-m3),2)+g3*m3));


 	Double_t		signal=bin_width*(par[16]*bw1+par[17]*(bw2+par[18]*bw3));
	if (include_f0_980)
	{
		signal=signal+f0_980(x, par);
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
	Double_t 	m4=TMath::Power(par[19],2);
	Double_t		g4=TMath::Power(par[20],2);
	Double_t		c4=integral(par[19],par[20]);
	Double_t 	bw4=1/(c4*(TMath::Power((x2-m4),2)+g4*m4));
	return 		par[21]*bw4;
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
	Double_t		f0=par[21]*bw*ph_space;
	return		f0;
	//-------------------
}

//	calculation of Breit-Wigner function integral using analytical ansatz from Ryzhik
Double_t	integral(Double_t m, Double_t G)
{
	Double_t	a=(m**4)+(m**2)*(G**2);
	Double_t	b=(-2)*(m**2);
	Double_t	c=1.0000;

	Double_t	q=TMath::Power((a/c),0.2500);
	Double_t	cos_alpha=(-0.5)*b/(sqrt(a*c));
	Double_t	sin_alpha=sqrt(1-cos_alpha**2);
	Double_t	cos_halfalpha=sqrt(0.50*(1+cos_alpha));

	Double_t	pi=TMath::Pi();
	Double_t	integral=(pi*cos_halfalpha)/(2*c*(q**3)*sin_alpha);

	return integral;
}
//__________________________________________________________________//
void DrawPaveText()
{
	TPaveText *pt = new TPaveText(0.15,0.22,0.4,0.5,"brNDC");
	char result[256];
	Int_t	n=sprintf(result,"#chi^{2}/ndf=%3.1f/%3i=%1.2f",chi2Min,ndof,chi2Min/ndof);
	text = pt->AddText(result);
	n=sprintf(result,"Ratio f_{0}/f'_{2}= %2.2f #pm %2.2f ",par[18],par_err[18]);
	text = pt->AddText(result);
	if (constraint_f0_width==true)
	{
		n=sprintf(result,"f_{0} width= %2.3f #pm %1.3f (CONSTRAINED)",par[15],par_err[15]);
	}
	if (constraint_f0_width==false)
	{
		n=sprintf(result,"f_{0} width= %2.3f #pm %1.3f (FREE)",par[15],par_err[15]);
	}
	text = pt->AddText(result);
	if (constraint_f0_mass==true)
	{
		n=sprintf(result,"f_{0} mass = %2.3f #pm %1.3f (CONSTRAINED)",par[14],par_err[14]);
	}
	if (constraint_f0_mass==false)
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
}
//__________________________________________________________________//
void DrawFunction(Int_t	color=4, Int_t	style=1,Int_t width=3)
{
	TString name="fsum";
	name+=counter;
	TF1 *fsum=new TF1(name,FitFunction,LowerEdge,UpperEdge,25);
	fsum->SetParameters(par);
	fsum->SetLineColor(color);
	fsum->SetLineWidth(width);
	fsum->SetLineStyle(style);
	fsum->Draw("same");
	cout<<name<<endl;
	counter++;
}
//__________________________________________________________________//
// saves fit parameters from MINUIT to par[] array
void	GetParametersMinuit()
{
	for (int k=0; k<25;k++)
	minuit->GetParameter(k, par[k],par_err[k]);
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

