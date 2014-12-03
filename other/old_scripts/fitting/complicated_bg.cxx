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
	Double_t	bg=0;
	Double_t	mKK=2*0.497672;
	Double_t	lim=4-mKK;
	Double_t 	q=x[0]-mKK;
	if (q<0) bg=0;
	Double_t	q2=q**2;
	Double_t	q3=q**3;
	Double_t	q4=q**4;
	Double_t	q5=q**5;

	Double_t	pol2=par[13]*q;

	Double_t	c=1/par[13];
	Double_t	e=exp(par[13]*lim);
	Double_t	I0=c*((lim**0)*e-1);
	Double_t	I1=c*((lim**1)*e-I0);
	Double_t	I2=c*((lim**2)*e-2*I1);
	Double_t	I3=c*((lim**3)*e-3*I2);
	Double_t	I4=c*((lim**4)*e-4*I3);
	Double_t	I5=c*((lim**5)*e-5*I4);

	/*Double_t	I0=1.000;
	Double_t	I1=1.000;
	Double_t	I2=1.000;
	Double_t	I3=1.000;
	Double_t	I4=1.000;
	Double_t	I5=1.000;
	Double_t	I6=1.000;*/

	//Double_t	s=0;
	//for (int kk=0;kk<5;kk++) s=s+par[kk];
	//s=s+par[2];

	Double_t	f0=par[14]/I0;
	Double_t	f1=par[15]*q/I1;
	Double_t	f2=par[16]*q2/I2;
	Double_t	f3=par[17]*q3/I3;
	//Double_t	f3=(1-s)*q3/I3;
	Double_t	f4=par[18]*q4/I4;
	//Double_t	f2=par[2]*(q2/I2+q4/I4);

	//Double_t	f3=(par[3]+par[4])(q3/I3+q4/I4);
	//Double_t	f4=(1-s)*q4/I4;
	//Double_t	f4=0;

	//Double_t	f5=(1-s)*q5/I5;
	Double_t	f5=par[19]*q5/I5;
	//if (use==0) f5=0;
	bg=(TMath::Power(q,par[21]*par[21]))*par[20]*(f0+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
	//return bg;

	Double_t 	x2=TMath::Power(x[0],2);

	Double_t 	m1=TMath::Power(par[3],2);
	Double_t	g1=TMath::Power(par[4],2);
	Double_t	c1=integral(par[3],par[4]);
	Double_t 	bw1=1/(c1*(TMath::Power((x2-m1),2)+g1*m1));

	Double_t 	m2=TMath::Power(par[6],2);
	Double_t	g2=TMath::Power(par[7],2);
	Double_t	c2=integral(par[6],par[7]);
	Double_t 	bw2=1/(c2*(TMath::Power((x2-m2),2)+g2*m2));

	Double_t 	m3=TMath::Power(par[9],2);
	Double_t	g3=TMath::Power(par[10],2);
	Double_t	c3=integral(par[9],par[10]);
	Double_t 	bw3=1/(c3*(TMath::Power((x2-m3),2)+g3*m3));

	Double_t	bin_width=par[12];

	//return par[0]*exp*pow+bin_width*(par[5]*bw1+par[8]*bw2+par[11]*bw3);
	return bg+bin_width*(par[5]*bw1+par[5]*par[8]*bw2+par[11]*bw3);
}
Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t	c=integral(par[0],par[1]);
	Double_t	bin_width=par[3];

	Double_t bw=bin_width*par[2]/(c*((x2-m2)*(x2-m2)+m2*g2));

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
Double_t	bg_compl(Double_t *x,Double_t *par)
{
	Double_t	bg=0;
	Double_t	mKK=2*0.497672;
	Double_t	lim=4-mKK;
	Double_t 	q=x[0]-mKK;
	if (q<0) bg=0;
	Double_t	q2=q**2;
	Double_t	q3=q**3;
	Double_t	q4=q**4;
	Double_t	q5=q**5;

	Double_t	pol2=par[13]*q;

	Double_t	c=1/par[13];
	Double_t	e=exp(par[13]*lim);
	Double_t	I0=c*((lim**0)*e-1);
	Double_t	I1=c*((lim**1)*e-I0);
	Double_t	I2=c*((lim**2)*e-2*I1);
	Double_t	I3=c*((lim**3)*e-3*I2);
	Double_t	I4=c*((lim**4)*e-4*I3);
	Double_t	I5=c*((lim**5)*e-5*I4);

	//Double_t	s=0;
	//for (int kk=0;kk<5;kk++) s=s+par[kk];
	//s=s+par[2];

	Double_t	f0=par[14]/I0;
	Double_t	f1=par[15]*q/I1;
	Double_t	f2=par[16]*q2/I2;
	Double_t	f3=par[17]*q3/I3;
	//Double_t	f3=(1-s)*q3/I3;
	Double_t	f4=par[18]*q4/I4;
	//Double_t	f2=par[2]*(q2/I2+q4/I4);

	//Double_t	f3=(par[3]+par[4])(q3/I3+q4/I4);
	//Double_t	f4=(1-s)*q4/I4;
	//Double_t	f4=0;

	//Double_t	f5=(1-s)*q5/I5;
	Double_t	f5=par[19]*q5/I5;
	//if (use==0) f5=0;
	//par[21]=0;
	bg=(TMath::Power(q,par[21]*par[21]))*par[20]*(f0+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
	//cout<<bg<<endl;
	return bg;

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

int main()
{
	Double_t	fix_f0_mass=false;
	Double_t	fix_f0_width=false;
	Double_t	fix_ratio=false;
	// ---------------------------- I N P U T  ------------------------- //
TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root");
	//TH1F *htemp2 = (TH1F*)f1->Get("hsignal");
	TH1F *htemp2 = (TH1F*)f1->Get("h2");
	//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_3");
	// ------------------------------------------------------------------//

	// --------------  I N I T I A L I Z A T I O N ----------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas();
	Double_t par[25];
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
	//TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.07,2.7,13);
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,0.995,2.7,22);
	fsum->SetLineColor(2);
	fsum->SetParName(0,"BG::Constant");
	fsum->SetParName(1,"BG::exp slope");
	fsum->SetParName(2,"BG::Power(optional)");
	fsum->SetParName(3,"BW1::peak position");
	fsum->SetParName(4,"BW1::FWHM");
	fsum->SetParName(5,"BW1::Area");
	fsum->SetParName(6,"BW2::peak position");
	fsum->SetParName(7,"BW2::FWHM");
	fsum->SetParName(8,"BW2::Area");
	fsum->SetParName(9,"BW3::peak position");
	fsum->SetParName(10,"BW3::FWHM");
	fsum->SetParName(11,"BW3::Area");
	fsum->SetParName(12,"bin_width");
	// ------------------------------------------------------------------//
	Float_t		corr=11.2;
	//corr=3.0;
	//corr=10.0;
	//corr=7.0;
	corr=5.7;
	// ------- Initial fitting (background parameters estimation) -------//
	/*TF1 *fbg1=new TF1("fbg1",bg,1.1,2.7,3);
	TF1 *fexp=new TF1("fexp",exp,1.2,2.7,2);
	fexp->SetLineColor(4);
	// estimation of exponent slope
	htemp2->Fit("fexp","R");
	fexp->GetParameters(&par[0]);
	par[2]=0.5;
	fbg1->SetParameters(&par[0]);
	fbg1->SetLineColor(7);
	// estimate all bg parameters
	htemp2->Fit("fbg1","R+");
	fbg1->GetParameters(&par[0]);
	par[20]=par[0]/1.05;

	par[21]=par[2];
	par[13]=par[1];*/

	par[0]=0;
	par[1]=0;
	par[2]=0;


	TF1 *fbg_init=new TF1("fbg_init",rel_breit_wigner_bg,0.995,2.7,22);

	par[3]=1.511;
	par[4]=0.07;
	par[5]=0;

	par[6]=1.7;
	par[7]=0.13;
	//par[8]=6200;
	par[8]=0.9;

	par[9]=1.3;
	par[10]=0.08;
	par[11]=0;

	par[12]=bin_width;

	par[20]=1;
	par[21]=0;
	par[13]=-3.855;
	par[14]=corr*237.4;
	par[15]=corr*1192;
	par[16]=corr*(-1851);
	par[17]=corr*4054;
	par[18]=corr*(-3538);
	par[19]=corr*1685;

	cout<<"&&&&&&&&&&&&&&&&&&&  fbginit parameters &&&&&&&&&&&&&&&&&&"<<endl;
	cout<<"par[13]= "<<par[13]<<endl;
	cout<<"par[20]= "<<par[20]<<endl;
	cout<<"par[21]= "<<par[21]<<endl;
	fbg_init->SetParameters(&par[0]);
	for (int kk=0;kk<13;kk++) fbg_init->FixParameter(kk,par[kk]);
	for(int k=14;k<20;k++)
	{
		if (k==14) continue;
		if (k==16) continue;
		//if (k==19) continue;
		fbg_init->FixParameter(k,par[k]);
	}
	cout<<"drawing fbg_init"<<endl;
	fbg_init->SetLineColor(3);
	htemp2->Fit("fbg_init","NQR+");
	gMinuit->mnmatu(1);
	fbg_init->GetParameters(&par[0]);
	par[5]=8000;
	par[11]=2000;
	fsum->SetParameters(&par[0]);
	fsum->FixParameter(0,par[0]);
	fsum->FixParameter(1,par[1]);
	fsum->FixParameter(2,par[2]);
	fsum->FixParameter(12,par[12]);

	for(int k=14;k<20;k++)
	{
		if (k==14) continue;
		if (k==15) continue;
		if (k==16) continue;
		if (k==17) continue;
		if (k==18) continue;
		if (k==19) continue;
		fsum->FixParameter(k,par[k]);
	}

	fsum->SetParLimits(5,0,20000);
	fsum->SetParLimits(11,0,20000);

	htemp2->Fit("fsum","R+");
		gMinuit->mnmatu(1);
	fsum->GetParameters(&par[0]);

	TF1 *fbg_c=new TF1("fbg_c",bg_compl,0.995,2.7,22);
	fbg_c->SetParameters(&par[0]);
	fbg_c->SetLineColor(4);
	fbg_c->Draw("same");

/*
	// --- set initial resonance parameters --- //
	par[3]=1.511;
	par[4]=0.07;
	par[5]=9000;

	par[6]=1.7;
	par[7]=0.13;
	//par[8]=6200;
	par[8]=0.9;

	par[9]=1.3;
	par[10]=0.08;
	par[11]=3000;

	par[12]=bin_width;


	//par[0]=154600;
	//par[1]=-2.624;
	//par[2]=3.234;

	Float_t		corr=11.2;
	//corr=3.0;
	//corr=10.0;
	//corr=7.0;
	corr=5.7;
	/*par[13]=-3.649;
	par[14]=corr*287.4;
	par[15]=corr*903.5;
	par[16]=corr*(-442.9);
	par[17]=corr*929.8;

	par[18]=0;
	par[19]=0;*/
/*
	par[13]=-3.855;
	par[14]=corr*237.4;
	par[15]=corr*1192;
	par[16]=corr*(-1851);
	par[17]=corr*4054;
	par[18]=corr*(-3538);
	par[19]=corr*1685;
	for(int k=14;k<20;k++)
	{
		if (k==14) continue;
		if (k==16) continue;
		//if (k==19) continue;
		fsum->FixParameter(k,par[k]);
	}

	par[20]=1;
	/*par[13]=-3.0;
	par[14]=corr*982.7;
	par[15]=corr*3012;
	par[16]=corr*(-1069);
	par[17]=corr*4329;
	par[18]=corr*(-2666);
	par[19]=corr*1650;*/

	// --- fixing/limits --- //
/*

	fsum->SetParameters(&par[0]);
	fsum->FixParameter(0,par[0]);
	fsum->FixParameter(1,par[1]);
	fsum->FixParameter(2,par[2]);
	//fsum->FixParameter(6,par[6]);
	//fsum->FixParameter(7,par[7]);
	fsum->FixParameter(9,par[9]);

	//fsum->FixParameter(18,par[18]);
	//fsum->FixParameter(19,par[19]);

	fsum->SetParLimits(5,0,200000);
	fsum->SetParLimits(8,0,200000);
	fsum->SetParLimits(11,0,200000);
	fsum->FixParameter(12,bin_width);



	//-- fitting --//

	fsum->Draw("same");
	//htemp2->Fit("fsum","R+");
	fsum->GetParameters(&par[0]);

	// ----------------------   R E S U L T S   ------------------------ //

	cout<<"*******************************************************"<<endl;
	gMinuit->mnmatu(1);
	//gMinuit->mnimpr();
	cout<<"*******************************************************"<<endl;

	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2.10,4);
	fbw1->SetParameters(par[3],par[4],par[5],bin_width);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,4);
	fbw2->SetParameters(par[6],par[7],par[5]*par[8],bin_width);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,4);
	fbw3->SetParameters(par[9],par[10],par[11],bin_width);
	fbw3->Draw("same");

	TF1 *fbg=new TF1("fbg",bg_compl,1.00,2.3,22);
	fbg->SetParameters(&par[0]);
	for (int k=0;k<13;k++)
	{
		fbg->FixParameter(k,0);
	}
	fbg->SetLineColor(3);
	fbg->Draw("same");

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
	
	//-------------------------------------------------------------------//
	TPaveText *pt = new TPaveText(0.15,0.22,0.4,0.5,"brNDC");
	char result[256];
	Double_t	chi2=fsum->GetChisquare();
	Double_t	NDF=fsum->GetNDF();
	n=sprintf(result,"#chi^{2}/ndf=%3.1f/%3i=%1.2f",chi2,NDF,chi2/NDF);
	text = pt->AddText(result);
	//n=sprintf(result,"Ratio= %2.2f #pm %2.2f",ratio,rat_err);
	n=sprintf(result,"Ratio f_{0}/f'_{2}= %2.2f #pm %2.2f ",par[8],fsum->GetParError(8));
	text = pt->AddText(result);
	if (fix_f0_width==true)
	{
		n=sprintf(result,"f_{0} width= %2.3f (FIXED)",par[7]);
	}
	if (fix_f0_width==false)
	{
		n=sprintf(result,"f_{0} width= %2.3f #pm %1.3f (FREE)",par[7],fsum->GetParError(7));
	}
	text = pt->AddText(result);
	if (fix_f0_mass==true)
	{
		n=sprintf(result,"f_{0} mass = %2.3f (FIXED)",par[6]);
	}
	if (fix_f0_mass==false)
	{
		n=sprintf(result,"f_{0} mass = %2.3f #pm %1.3f (FREE)",par[6],fsum->GetParError(6));
	}
	text = pt->AddText(result);
	n=sprintf(result,"f'_{2} mass = %1.3f #pm %1.3f" ,par[3],fsum->GetParError(3));
	text = pt->AddText(result);
	pt->SetFillColor(3);
	pt->Draw("same");
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

	return 0;
}
