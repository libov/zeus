
#ifndef __CINT__
#include <iostream>
using namespace std;
//#include <K0s_fit.h>
#include<TH1F.h>
#include<TAxis.h>
#include<TF1.h>
#endif
//constructors, destructor
K0s_fit::K0s_fit()
{
}
K0s_fit::K0s_fit(TH1F * hinv_init)
{

	hinv=hinv_init;


}
K0s_fit::~K0s_fit()
{
}
void K0s_fit::Draw()
{
	hinv->Draw();
}

//-------------------  Fitting functions definitions   --------------------//

Double_t as(Double_t *x,Double_t *par)
{
	// This is double gaussian with one of them assymetric (with two
	// different sigma for <mean and >mean regions)
	// + linear function for the background
	// Parameters:
	//gaus 1:	par[0] - constant
	//		par[1] - mass
	//		par[2] - sigma
	//gaus 2:	par[3] - constant
	//		par[1] - mass
	//		par[4] - sigma(left)
	//		par[7] - sigma(right)
	//polynom	par[5] - A
	// (A+Bx)	par[6] - B
	Double_t 	gaus1=0,
			gaus2left=0,
			gaus2right=0,
			pol1=0;
	gaus1=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gaus2left=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[4]*par[4]));
	gaus2right=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[7]*par[7]));
	pol1=par[5]+par[6]*x[0];
	if(x[0]<=par[1]) return gaus1+gaus2left+pol1;
	if(x[0]>par[1]) return gaus1+gaus2right+pol1;
}
Double_t asymmetric_gaus(Double_t *x,Double_t *par)
{
	// This is asymmetric gaussian
	// par[0] - constant; par[1] - mean (mass); par[2] - left sigma; par[3] - right sigma;
	Double_t	gausleft=0,
			gausright=0;

	gausleft=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gausright=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[3]*par[3]));
	if (x[0]<=par[1]) return gausleft;
	if (x[0]>par[1]) return gausright;
}
//-------------------------------------------------------------------------//

//------------------------------ fitting ----------------------------------//
void K0s_fit::Fit()
{
	//----------------- Initialization ---------------//
	cout<<"*********    Fitting    **********"<<endl;
	cout<<endl;
	nbins=hinv->GetNbinsX();
	xaxis = hinv->GetXaxis();
	histRangeLow=xaxis->GetXmin();
	histRangeUp=xaxis->GetXmax();
	cout<<"Input histogram range: ["<<histRangeLow<<","<<histRangeUp<<"] MeV"<<endl;

	Double_t	histRange=histRangeUp-histRangeLow;
	bin_width=histRange/nbins;
	cout<<"Bin width: "<<bin_width<<" MeV"<<endl;

	fitRangeLow=430;
	fitRangeUp=560;
	cout<<"Fit range: ["<<fitRangeLow<<","<<fitRangeUp<<"] MeV"<<endl;
	xaxis->SetTitle("M(#pi^{+}#pi^{-}), MeV");
	hinv->GetYaxis()->SetTitle("Combinations/1.7 MeV");
	//------------------------------------------------//

	TF1 *fgaus=new TF1("fgaus","gaus",483,507);
	fpol1=new TF1("fpol1","pol1",fitRangeLow,fitRangeUp);
	hinv->Fit("fgaus","QNR");
	hinv->Fit("fpol1","QNR");
	Double_t 	init_const1=0,
			init_const2=0,
			init_sigma1=0,
			init_sigma2=0,
			init_mass=0,
			init_A=0,
			init_B=0;
	fgaus->GetParameters(&parameters[0]);
	fpol1->GetParameters(&parameters[3]);
	init_const1=parameters[0]/2; //1
	init_const2=parameters[0]/6; //3
	init_mass=parameters[1];
	init_sigma1=parameters[2]/2;
	init_sigma2=1.1*parameters[2];
	init_A=parameters[3];
	init_B=parameters[4];
	fsum=new TF1("fsum",as,fitRangeLow,fitRangeUp,8);
				fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
	fsum->SetParNames("Constant1","Mass","Sigma1","Constant2","LeftSigma2","A","B","Rightsigma2");
	fsum->SetLineColor(2);
	fsum->SetLineWidth(2);

	fsum->SetParLimits(1,494,501);
	fsum->SetParLimits(2,1,20);
	fsum->SetParLimits(4,1,20);
	fsum->SetParLimits(7,1,20);
	fsum->SetParLimits(0,0,100000000);
	fsum->SetParLimits(3,0,100000000);
	//cout<<fsum->GetParameter(1)<<endl;
	//fsum->Draw("same");
	//hinv->Fit("fsum","NQR+");
	hinv->Fit("fsum","QR+");

	fsum->GetParameters(&parameters[0]);
	fpol1->SetParameters(parameters[5],parameters[6]);

	//  Now draw other functions

	this->Draw_Signal_Bg();
	this->Print();
	cout<<"Number of K0 candidates: "<<this->GetK0cand()<<endl;
	cout<<endl;
	cout<<"*******************************"<<endl;
}
//-------------------------------------------------------------------------//
//drawings
void K0s_fit::Draw_fsum()
{
	fsum->Draw("same");
}
void K0s_fit::Draw_Signal_Bg()
{
	fgaus1=new TF1("fgaus1","gaus",fitRangeLow,fitRangeUp);
	fgaus2=new TF1("fgaus2",asymmetric_gaus,fitRangeLow,fitRangeUp,4);
	fgaus1->SetLineWidth(2);
	fgaus2->SetLineWidth(2);
	fgaus1->SetParameters(parameters[0],parameters[1],parameters[2]);
	fgaus2->SetParameters(parameters[3],parameters[1],parameters[4],parameters[7]);
	fgaus1->Draw("same");
	fgaus2->Draw("same");
	fline=new TF1("fline","pol1",fitRangeLow,fitRangeUp);
	fline->SetParameters(parameters[5],parameters[6]);
	fline->SetLineColor(7);
	fline->SetLineStyle(7);
	fline->Draw("same");
}
//fit results
Double_t K0s_fit::GetK0cand()
{
	Double_t 	range_low=parameters[1]-30,
			range_up=parameters[1]+30;
	Signal=fsum->Integral(range_low,range_up)/bin_width;
	Background=fpol1->Integral(range_low,range_up)/bin_width;
	K0cand=Signal-Background;
	return K0cand;
}

Double_t	K0s_fit::GetUpBand()
{
	UpBand=fsum->Integral(parameters[1]-60,parameters[1]-30)/bin_width;
	return	UpBand;
}
Double_t	K0s_fit::GetDownBand()
{
	DownBand=fsum->Integral(parameters[1]+30,parameters[1]+60)/bin_width;
	return	DownBand;
}
void K0s_fit::Print()
{
	cout<<"Constant1  Mass  Sigma1  Constant2  LeftSigma2  A  B  Rightsigma2"<<endl;
	for (Int_t k=0;k<8;k++)
	{
		cout<<parameters[k]<<"   ";
	}
	cout<<endl;
}

