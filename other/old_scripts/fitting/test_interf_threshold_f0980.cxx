#include<canvas.cxx>
#include<TMath.h>
Double_t	integral(Double_t m, Double_t G)
{
	Double_t	a=(m**4)+(m**2)*(G**2);
	Double_t	b=(-2)*(m**2);
	Double_t	c=1.0000;

	Double_t	q=(a/c)**(0.2500);
	Double_t	cos_alpha=(-0.5)*b/(sqrt(a*c));
	Double_t	sin_alpha=sqrt(1-cos_alpha**2);
	Double_t	cos_halfalpha=sqrt(0.50*(1+cos_alpha));

	Double_t	pi=TMath::Pi();
	Double_t	integral=(pi*cos_halfalpha)/(2*c*(q**3)*sin_alpha);

	return integral;
}
Double_t rel_breit_wigner_bg(Double_t *x,Double_t *par)
{

	//-------------------------------------------------//
	// for function description                        //
	// see paper "Incl. K0sK0s Resonance Production"   //
	// arXiv:0806.0807                                 //
	//-------------------------------------------------//

	Double_t		M[5],
					G[5];
	Double_t		a=0,
					b=0,
					c=0;

	// Parameters of bw-functions
	M[1]=par[3];	// M1
	G[1]=par[4];	// G1
	M[2]=par[5];	// M2
	G[2]=par[6];	// G2
	M[3]=par[7];	// M3
	G[3]=par[8];	// G3
	M[4]=par[9];	// M4
	G[4]=par[10];	// G4

	a=par[11];	// a
	b=par[12];	// b

	Double_t	ReBW[5],	// Real part of ith peak
				ImBW[5],	// Imaginary part of ith peak
				den[5];		// denominator of ith peak

	Double_t	m=x[0];		// function variable

	// each bw-function calculation
	for (int i=1;i<5;i++)
	{
		Double_t	temp1=0,
				temp2=0;
		temp1=M[i]**2-m**2;
		temp2=M[i]*sqrt(G[i]);
		den[i]=temp1**2+(M[i]*G[i])**2;
		ReBW[i]=(temp1*temp2)/den[i];
		ImBW[i]=temp2*M[i]*G[i]/den[i];
	}

	Double_t		ReTensor=0,
					ImTensor=0;
	ReTensor=5*ReBW[1]-3*ReBW[2]+par[22]*2*ReBW[3];
	ImTensor=5*ImBW[1]-3*ImBW[2]+par[22]*2*ImBW[3];

	// background
	Double_t		bg=0;
	Double_t		mKK=2*0.497672;
	Double_t 	q=x[0]-mKK;
	if (q<0) 	bg=0;
	Double_t		q2=q**2;
	Double_t		q3=q**3;
	Double_t		q4=q**4;
	Double_t		q5=q**5;

	Double_t		pol2=par[13]*q;

	Double_t		f1=par[15]*q;
	Double_t		f2=par[16]*q2;
	Double_t		f3=par[17]*q3;
	Double_t		f4=par[18]*q4;
	Double_t		f5=par[19]*q5;

	bg=(TMath::Power(q,par[21]*par[21]))*par[20]*(1+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
	//-------------//

	Double_t		x2=x[0]*x[0];
	Double_t 	m4=TMath::Power(par[0],2);
	Double_t		g4=TMath::Power(par[1],2);
	//Double_t		c4=integral(par[0],par[1]);
	Double_t		c4=1.00000;
	//cout<<"integral= "<<c4<<endl;
	Double_t 	bw4=1/(c4*(TMath::Power((x2-m4),2)+g4*m4));

	// Total fit function
	Double_t	total=0;
	total=a*(ReTensor**2+ImTensor**2)+b*(ReBW[4]**2+ImBW[4]**2)+0.015*par[2]*bw4+bg;

	return total;

}
Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	//Double_t	c=integral(par[0],par[1]);
	Double_t	bin_width=par[3];
	Double_t	c=1.0000;


	//Double_t bw=bin_width*par[2]/(c*((x2-m2)*(x2-m2)+m2*g2));
	Double_t bw=par[2]*(m2*par[1])/((x2-m2)*(x2-m2)+m2*g2);

	return bw;
}
Double_t bg(Double_t *x,Double_t *par)
{
	// Background function: polinom at K0sK0s threshold, fall-off exponent far from the threshold
	// par[0] - constant
	// par[1] - slope
	// par[2] - power
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]);
	return par[0]*pow*exp;
}
Double_t exp(Double_t *x,Double_t *par)
{
	// Simple background function: fall-off exponent
	// par[0] - constant
	// par[1] - exponent slope

	//Double_t 	q=x[0]-2*0.497672;
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*q);
	return par[0]*exp;
}

int main(Double_t	f2mass=1.268, Double_t	a2mass=1.257)
{
	// ---------------------------- I N P U T  ------------------------- //
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight.root");
TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/hk0k0_substr.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e06p07p_COMMNTUP_lower_bg_cuts.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e06p07p_COMMNTUP_lower_bg_secvtx.root");
	//TH1F *htemp2 = (TH1F*)f1->Get("hsignal");
	TH1F *htemp2 = (TH1F*)f1->Get("h2");
	//TH1F *htemp2 = (TH1F*)f1->Get("h1");
	//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_3");
	// ------------------------------------------------------------------//

	// --------------  I N I T I A L I Z A T I O N ----------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas("canv_default");
	Double_t par[35];
	htemp2->SetTitle("ZEUS");
	htemp2->Sumw2();
	htemp2->SetMarkerStyle(20);
	htemp2->GetYaxis()->SetTitleOffset(1.3);
	TFile *out=new TFile("/data/zenith226a/libov/fitting/heraII_fit.root","recreate");
	Int_t	nbins=htemp2->GetNbinsX();
	cout<<nbins<<" bins"<<endl;
	Float_t 	bin_width=0;
	bin_width=(5.0-0.8)/nbins;
	cout<<"bin_width: "<<bin_width<<" GeV"<<endl;
	char Ytitle[25];
	Int_t n=0;
	n=sprintf(Ytitle,"Combinations/ %1.3f GeV",bin_width);
	cout<<Ytitle<<endl;
	htemp2->SetYTitle(Ytitle);
	htemp2->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
	htemp2->GetXaxis()->SetRangeUser(0.95,3);
	htemp2->Draw();
	// ------------------//
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,0.995,2.7,23);
	fsum->SetLineColor(2);
	fsum->SetParName(0,"f0(980) mass");
	fsum->SetParName(1,"f0(980) width");
	fsum->SetParName(2,"f0(980) area");
	fsum->SetParName(3,"BW1::peak position");
	fsum->SetParName(4,"BW1::FWHM");
	fsum->SetParName(5,"BW2::peak position");
	fsum->SetParName(6,"BW2::FWHM");
	fsum->SetParName(7,"BW3::peak position");
	fsum->SetParName(8,"BW3::FWHM");
	fsum->SetParName(9,"BW4::peak position");
	fsum->SetParName(10,"BW4::FWHM");
	fsum->SetParName(11,"a");
	fsum->SetParName(12,"b");

	// ------------------------------------------------------------------//

	// ------- Initial fitting (background parameters estimation) -------//
	TF1 *fexp=new TF1("fexp",exp,1.2,2.7,2);
	fexp->SetLineColor(4);
	// estimation of exponent slope
	htemp2->Fit("fexp","NQR");
	fexp->GetParameters(&par[0]);

	TF1 *fbg1=new TF1("fbg1",rel_breit_wigner_bg,0.994,2.7,23);

	// initials for the background
	par[13]=par[1];
	par[20]=par[0];
	par[21]=1;

	par[15]=1;
	par[16]=1;

	for (int k=17;k<20;k++)  				// currently unused
	{
		par[k]=0;
		fbg1->FixParameter(k,par[k]);
	}

	par[14]=0;									// currently unused
	fbg1->FixParameter(14,par[14]);
	// fix resonance parameters, areas to zero.
	par[0]=1.01;
	par[1]=0.06;
	par[2]=0;

	par[3]=f2mass;
	par[4]=0.176;

	par[5]=a2mass;
	par[6]=0.114;

	par[7]=1.512;
	par[8]=0.083;

	par[9]=1.695;
	par[10]=0.13;

	par[11]=0;
	par[12]=0;

	for (int k=0;k<13;k++)
		fbg1->FixParameter(k,par[k]);

	par[22]=0;
	fbg1->FixParameter(22,par[22]);

	fbg1->SetParameters(&par[0]);
	fbg1->SetLineColor(7);
	// estimate all bg parameters
	htemp2->Fit("fbg1","NQR");

	fbg1->GetParameters(&par[0]);
	par[20]=par[20]/1.05;

	// --- fixing/limits --- //
	fbg1->SetParameters(&par[0]);
	fbg1->Draw("same");

	par[2]=400;
	par[11]=13;
	par[12]=50;
	par[22]=1.5;

	fsum->SetParameters(&par[0]);

	//fsum->FixParameter(2,par[2]);

	//fsum->FixParameter(3,par[3]);
	//fsum->FixParameter(4,par[4]);
	//fsum->FixParameter(5,par[5]);
	//fsum->FixParameter(6,par[6]);

	//fsum->FixParameter(13,par[13]);

	//fsum->SetParLimits(5,0,10000);
	//fsum->SetParLimits(8,0,10000);
	//fsum->SetParLimits(11,0,10000);
	//fsum->FixParameter(12,bin_width);

	//-- fitting --//

	//fsum->Draw("same");
	htemp2->Fit("fsum","NQR");
	htemp2->Fit("fsum","NQR");
	htemp2->Fit("fsum","R+");
	fsum->GetParameters(&par[0]);
	par[2]=0;
	par[11]=0;
	par[12]=0;
	TF1 *fbg2=new TF1("fbg2",rel_breit_wigner_bg,0.994,2.7,22);
	fbg2->SetParameters(&par[0]);
	fbg2->SetLineColor(30);
	fbg2->Draw("same");

	// ----------------------   R E S U L T S   ------------------------ //

	cout<<"*******************************************************"<<endl;
	gMinuit->mnmatu(1);
	//gMinuit->mnimpr();
	cout<<"*******************************************************"<<endl;
/*
	TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	fbg->Draw("same");

	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2.10,4);
	fbw1->SetParameters(par[3],par[4],(5*par[11]),bin_width);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,4);
	fbw2->SetParameters(par[5],par[6],(3*par[11]),bin_width);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,4);
	fbw3->SetParameters(par[7],par[8],(4*par[11]),bin_width);
	fbw3->Draw("same");

	TF1 *fbw4=new TF1("fbw4",rel_breit_wigner,0,10,4);
	fbw4->SetParameters(par[9],par[10],par[12],bin_width);
	fbw4->Draw("same");
*/

/*
	Double_t	area_1525=0,
			area_1710=0;
	area_1525=par[5];
	area_1710=par[8];

	cout<<"Area (from parameters): "<<endl;
	cout<<"f2(1525): "<<area_1525<<endl;
	cout<<"f0(1710): "<<area_1710<<endl;

	Double_t	sign_1525=par[5]/(fsum->GetParError(5));
	Double_t	sign_1710=par[8]/(fsum->GetParError(8));
	cout<<"Significance:"<<endl;
	cout<<"f2(1525): "<<sign_1525<<endl;
	cout<<"f0(1710): "<<sign_1710<<endl;
	
	Double_t	ratio=par[8]/par[5];
	Double_t	rat_err=ratio*sqrt((1/sign_1525)**2+(1/sign_1710)**2);
	cout<<"ratio= "<<ratio<<" +- "<<rat_err<<endl;
*/
	//-------------------------------------------------------------------//
/*	pt = new TPaveText(0.15,0.22,0.5,0.5,"brNDC");
	pt->SetFillColor(0);
	char result[256];
	text = pt->AddText("Number of Candidates: ");
	n=sprintf(result,"f'_{2}(1525): %d (%2.2f #sigma)",(Int_t)area_1525,sign_1525);
	text = pt->AddText(result);
	n=sprintf(result,"f_{0}(1710): %d (%2.2f #sigma)",(Int_t)area_1710,sign_1710);
	text = pt->AddText(result);
	n=sprintf(result,"#chi^{2} /ndf= %2.2f",fsum->GetChisquare()/fsum->GetNDF());
	text = pt->AddText(result);
	n=sprintf(result,"Ratio= %2.2f #pm %2.2f",ratio,rat_err);
	text = pt->AddText(result);
	pt->SetFillColor(3);
	pt->Draw("same");*/
	//-------------------------------------------------------------------//
	/*
	leg1 = new TLegend(0.55,0.55,0.89,0.89);
	leg1->AddEntry(htemp2,"Zeus 0.5fb^-1","p");
	leg1->AddEntry(fsum,"3 Breit-Wigners+background","l");
	leg1->AddEntry(fbg,"Background","l");
	leg1->SetFillColor(0);
	leg1->Draw("same");
	*/
	//c1->Write();
	//f1->Close();
	//out->Close();
	//cout<<"******************"<<endl;
	//cout<<(fbw4->Integral(0,10))/(fbw3->Integral(0,10))<<endl;

	return 0;
}
