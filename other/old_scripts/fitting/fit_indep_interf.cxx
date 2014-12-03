#include<canvas.cxx>
#include<TMath.h>
bool 	add_incoherent=false;
Double_t	integral(Double_t m, Double_t G)
{
	Double_t	a=(m**4)+(m**2)*(G**2);
	Double_t	b=(-2)*(m**2);
	Double_t	c=1.0000;

	if ((a/c)<=0)	cout<<"Disaster!!! a/c<= "<<a/c<<endl;

	Double_t	q=(a/c)**(0.2500);
	Double_t	cos_alpha=(-0.5)*b/(sqrt(a*c));
	Double_t	sin_alpha=sqrt(1-cos_alpha**2);
	Double_t	cos_halfalpha=sqrt(0.50*(1+cos_alpha));

	//Double_t	pi=TMath::Pi();
	Double_t	pi=3.14159;
	Double_t	integral=(pi*cos_halfalpha)/(2*c*(q**3)*sin_alpha);
	//cout<<integral<<endl;
	return integral;
}
Double_t rel_breit_wigner_bg(Double_t *x,Double_t *par)
{

	//-------------------------------------------------//
	// for function description                        //
	// see paper "Incl. K0sK0s Resonance Production"   //
	// arXiv:0806.0807                                 //
	//-------------------------------------------------//

	Double_t			M[5],
						G[5];
	Double_t			a=0,
						b=0,
						c=0;

	Double_t			alpha=0;
	Double_t			beta=0;
	Double_t			gamma=0;

	//Parameters of background function bg()

	//par[1]
	//par[2]

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
	c=par[0];    	// c

	Double_t		ReBW[5],	// Real part of ith peak
					ImBW[5],	// Imaginary part of ith peak
					den[5];		// denominator of ith peak

	Double_t	m=x[0];		// function variable

	// each bw-function calculation
	for (int i=1;i<5;i++)
	{
		Double_t		temp1=0,
						temp2=0;
		temp1=M[i]**2-m**2;
		temp2=M[i]*sqrt(G[i]);
		den[i]=temp1**2+(M[i]*G[i])**2;
		ReBW[i]=(temp1*temp2)/den[i];
		ImBW[i]=temp2*M[i]*G[i]/den[i];
	}

	Double_t		ReTensor=0,
					ImTensor=0;

	Double_t		ReX=par[14];
	Double_t		ImX=par[15];

	//Double_t		Re_beta=par[14];
	//Double_t		Re_gamma=par[15];

	Double_t			Re_beta=5+ReX;
						//Re_beta=ReX;
	Double_t			Im_beta=ImX;

	Double_t		   Re_gamma=-3+ReX;
						//Re_gamma=ReX;
	Double_t			Im_gamma=ImX;

	Double_t			Re_delta=2+ReX;
						//Re_delta=ReX;
	Double_t			Im_delta=ImX;

	Im_delta=0;

	ReTensor=Re_beta*ReBW[1]-Im_beta*ImBW[1]+Re_gamma*ReBW[2]-Im_gamma*ImBW[2]+Re_delta*ReBW[3]-Im_delta*ImBW[3];

ImTensor=Re_beta*ImBW[1]+Im_beta*ReBW[1]+Re_gamma*ImBW[2]+Im_gamma*ReBW[2]+Re_delta*ImBW[3]+Im_delta*ReBW[3];

	//cout<<ReTensor<<endl;
	//cout<<ImTensor<<endl;
	// background
	Double_t	bg=0;
	bg=TMath::Exp(par[1]*(m))*TMath::Power(m,par[2]);

	// Total fit function
	Double_t	total=0;
	total=a*(ReTensor**2+ImTensor**2)+b*(ReBW[4]**2+ImBW[4]**2)+c*bg;


	//_________
	if (add_incoherent)
	{
		Double_t		x2=x[0]**2;

		Double_t 	m2_1=TMath::Power(M[1],2);
		Double_t		g2_1=TMath::Power(G[1],2);

		Double_t 	m2_2=TMath::Power(M[2],2);
		Double_t		g2_2=TMath::Power(G[2],2);

		Double_t 	m2_3=TMath::Power(M[3],2);
		Double_t		g2_3=TMath::Power(G[3],2);

		//Double_t		c1=integral(M[1],G[1]);
		//Double_t		c2=integral(M[2],G[2]);
		//Double_t		c3=integral(M[3],G[3]);

		//cout<<c1<<" "<<c2<<" "<<c3<<endl;

		/*Double_t 	bw1=1/(c1*(TMath::Power((x2-m2_1),2)+g2_1*m2_1));
		Double_t 	bw2=1/(c2*(TMath::Power((x2-m2_2),2)+g2_2*m2_2));
		Double_t 	bw3=1/(c3*(TMath::Power((x2-m2_3),2)+g2_3*m2_3));*/

		Double_t 	bw1=1/((TMath::Power((x2-m2_1),2)+g2_1*m2_1));
		Double_t 	bw2=1/((TMath::Power((x2-m2_2),2)+g2_2*m2_2));
		Double_t 	bw3=1/((TMath::Power((x2-m2_3),2)+g2_3*m2_3));

		//par[16]=0;
		//cout<<"&&& "<<par[16]*(bw1+bw2+bw3)<<endl;
		total=total+(par[16]**2)*(bw1+bw2+bw3);
	}


	//_________

	return total;
	//---------------
	//Double_t	bin_width=par[12];

	//return par[0]*exp*pow+bin_width*(par[5]*bw1+par[8]*bw2+par[11]*bw3);
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
	//Double_t	bin_width=par[3];
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

//Double_t exp(Double_t *x,Double_t *par)

int main()
{
	// ---------------------------- I N P U T  ------------------------- //
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/06eGR1_v2008a1_.root");
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_substr.root");
	TH1F *htemp2 = (TH1F*)f1->Get("h2_signal");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root");
	//TH1F *htemp2 = (TH1F*)f1->Get("h2");

	// ------------------------------------------------------------------//

	// --------------  I N I T I A L I Z A T I O N ----------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas("canv_default");
	Double_t par[20];
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
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1	,2.7,18);
	fsum->SetLineColor(2);
	fsum->SetParName(0,"BG::Constant (c)");
	fsum->SetParName(1,"BG::exp slope");
	fsum->SetParName(2,"BG::Power(optional)");
	fsum->SetParName(3,"f2(1270)::peak position");
	fsum->SetParName(4,"f2(1270)::FWHM");
	fsum->SetParName(5,"a2(1320)::peak position");
	fsum->SetParName(6,"a2(1320)::FWHM");
	fsum->SetParName(7,"f2(1525)::peak position");
	fsum->SetParName(8,"f2(1525)::FWHM");
	fsum->SetParName(9,"f0(1710)::peak position");
	fsum->SetParName(10,"f0(1710)::FWHM");
	fsum->SetParName(11,"a");
	fsum->SetParName(12,"b");

	fsum->SetParName(13,"alpha");
	fsum->SetParName(14,"ReX");
	fsum->SetParName(15,"ImX");
	fsum->SetParName(16,"area");
	fsum->SetParName(17,"Im_gamma");

	Double_t			mass_f2_1270_PDG=1.2751;
	Double_t			width_f2_1270_PDG=0.185;
	Double_t			mass_a2_1320_PDG=1.3183;
	Double_t			width_a2_1320_PDG=0.107;
	Double_t			mass_f2_1525_PDG=1.525;
	Double_t			width_f2_1525_PDG=0.073;

	// ------------------------------------------------------------------//

	// ------- Initial fitting (background parameters estimation) -------//
	TF1 *fbg1=new TF1("fbg1",bg,1.1,2.7,3);
	TF1 *fexp=new TF1("fexp",exp,1.2,2.7,2);
	fexp->SetLineColor(4);
	// estimation of exponent slope
	htemp2->Fit("fexp","NQR");
	fexp->GetParameters(&par[0]);
	par[2]=0.5;
	fbg1->SetParameters(&par[0]);
	fbg1->SetLineColor(7);
	// estimate all bg parameters
	htemp2->Fit("fbg1","NR+");
	fbg1->GetParameters(&par[0]);
	par[0]=par[0]/1.05;

	// --- set initial resonance parameters --- //

	//par[3]=mass_f2_1270_PDG*(1-0.006);
	par[3]=mass_f2_1270_PDG;
	par[4]=width_f2_1270_PDG;
	//par[5]=mass_a2_1320_PDG*(1-0.006);
	par[5]=mass_a2_1320_PDG;
	par[6]=width_a2_1320_PDG;
	par[7]=mass_f2_1525_PDG;
	par[8]=width_f2_1525_PDG;

	par[9]=1.695;
	par[10]=0.137;

	// --- fixing/limits --- //

	//par[11]=15;
	//par[11]=10*25;
	par[11]=10;	par[11]=11.27;
	par[12]=50;par[12]=55.69;

	par[13]=5;

	par[14]=1;
	par[15]=1;

	par[16]=0;
	par[17]=0;

	fsum->SetParameters(&par[0]);

	for (int kk=3;kk<9; kk++)
	{
		//if ((kk!=7)&&(kk!=3)&&(kk!=5))
		if ((kk!=7)&&(kk!=8))
		//if ((kk!=7))
		fsum->FixParameter(kk,par[kk]);
	}

	par[14]=0;
	par[15]=0;
	fsum->FixParameter(14,par[14]);
	fsum->FixParameter(15,par[15]);


	//fsum->FixParameter(16,par[16]);

	fsum->FixParameter(17,par[17]);

	fsum->SetParLimits(16,0,10000);
	//fsum->SetParLimits(8,0,10000);

	fsum->FixParameter(13,par[13]);
	fsum->FixParameter(9,par[9]);
	fsum->FixParameter(10,par[10]);

	//f
	fsum->SetParLimits(11,0,10000);
	//fsum->FixParameter(12,bin_width);

	//-- fitting --//
	fsum->SetLineColor(2);
	fsum->Draw("same");
	htemp2->Fit("fsum","NQR+");
	htemp2->Fit("fsum","NQR+");
	//htemp2->Fit("fsum","R+");

	fsum->ReleaseParameter(14);
	fsum->ReleaseParameter(15);
	htemp2->Fit("fsum","R+");

	fsum->GetParameters(&par[0]);

	// ----------------------   R E S U L T S   ------------------------ //

	cout<<"*******************************************************"<<endl;
	gMinuit->mnmatu(1);
	//gMinuit->mnimpr();
	cout<<"*******************************************************"<<endl;

	TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	fbg->Draw("same");

	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2.10,4);
	fbw1->SetParameters(par[3],par[4],((5+par[14])**2+par[15]**2)*par[11]);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,4);
	fbw2->SetParameters(par[5],par[6],((-3+par[14])**2+par[15]**2)*par[11]);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,4);
	fbw3->SetParameters(par[7],par[8],((2+par[14])**2+par[15]**2)*par[11]);
	fbw3->Draw("same");

	TF1 *fbw4=new TF1("fbw4",rel_breit_wigner,0,10,4);
	fbw4->SetParameters(par[9],par[10],par[12]);
	fbw4->Draw("same");


	Double_t		f2_1525_integral=fbw3->Integral(par[7]-4*par[8],par[7]+4*par[8]);
	cout<<"f2_1525_integral= "<<f2_1525_integral/bin_width<<endl;

	Double_t		f0_1710_integral=fbw4->Integral(par[9]-4*par[10],par[9]+4*par[10]);
	cout<<"f0_1710_integral= "<<f0_1710_integral/bin_width<<endl;

	cout<<"Ratio: "<<f0_1710_integral/f2_1525_integral<<endl;



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

	//-------------------------------------------------------------------//
	pt = new TPaveText(0.15,0.22,0.5,0.5,"brNDC");
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
	cout<<"******************"<<endl;
	cout<<(fbw4->Integral(0,10))/(fbw3->Integral(0,10))<<endl;


	TF1 *fsignal=new TF1("fsignal",rel_breit_wigner_bg,1.05,2.7,18);
	fsignal->SetLineColor(9);
	par[0]=0;
	fsignal->SetParameters(&par[0]);
	fsignal->Draw("same");


/*
	//---------------------------------------------------//


	CreateCanvas("canv_free");
	TCanvas *canv1=gROOT->FindObject("canv_free");
	canv1->cd();

	TF1 *fsum1=new TF1("fsum1",rel_breit_wigner_bg,1.05,2.7,16);
	fsum1->SetParameters(&par[0]);
	htemp2->Draw();
	fsum1->SetLineColor(6);
	fsum1->SetParName(0,"BG::Constant (c)");
	fsum1->SetParName(1,"BG::exp slope");
	fsum1->SetParName(2,"BG::Power(optional)");
	fsum1->SetParName(3,"f2(1270)::peak position");
	fsum1->SetParName(4,"f2(1270)::FWHM");
	fsum1->SetParName(5,"a2(1320)::peak position");
	fsum1->SetParName(6,"a2(1320)::FWHM");
	fsum1->SetParName(7,"f2(1525)::peak position");
	fsum1->SetParName(8,"f2(1525)::FWHM");
	fsum1->SetParName(9,"f0(1710)::peak position");
	fsum1->SetParName(10,"f0(1710)::FWHM");
	fsum1->SetParName(11,"a");
	fsum1->SetParName(12,"b");

	fsum1->SetParName(13,"alpha");
	fsum1->SetParName(14,"beta");
	fsum1->SetParName(15,"gamma");

	htemp2->Fit("fsum1","R+");
		fsum1->GetParameters(&par[0]);

	// ----------------------   R E S U L T S   ------------------------ //

	cout<<"*******************************************************"<<endl;
	gMinuit->mnmatu(1);
	//gMinuit->mnimpr();
	cout<<"*******************************************************"<<endl;

	TF1 *fbg1=new TF1("fbg1",bg,1.05,2.3,3);
	fbg1->SetParameters(par[0],par[1],par[2]);
	fbg1->SetLineColor(3);
	fbg1->Draw("same");

	TF1 *fbw1f=new TF1("fbw1f",rel_breit_wigner,0,2.10,4);
	fbw1f->SetParameters(par[3],par[4],par[11]);
	fbw1f->Draw("same");

	TF1 *fbw2f=new TF1("fbw2f",rel_breit_wigner,0,10,4);
	fbw2f->SetParameters(par[5],par[6],(par[14]**2)*par[11]);
	fbw2f->Draw("same");

	TF1 *fbw3f=new TF1("fbw3f",rel_breit_wigner,0,10,4);
	fbw3f->SetParameters(par[7],par[8],(par[15]**2)*par[11]);
	fbw3f->Draw("same");
//
	TF1 *fbw4f=new TF1("fbw4f",rel_breit_wigner,0,10,4);
	fbw4f->SetParameters(par[9],par[10],par[12]);
	fbw4f->Draw("same");


	Double_t		f2_1525_integralf=fbw3f->Integral(par[7]-3*par[8],par[7]+3*par[8]);
	cout<<"f2_1525_integralf= "<<f2_1525_integralf<<endl;

	Double_t		f0_1710_integralf=fbw3f->Integral(par[9]-3*par[10],par[9]+3*par[10]);
	cout<<"f0_1710_integralf= "<<f0_1710_integralf<<endl;

	cout<<"Ratio: "<<f0_1710_integralf/f2_1525_integralf<<endl;

*/


	return 0;
}
