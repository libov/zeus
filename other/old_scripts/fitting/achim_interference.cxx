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

	Double_t			M[5],
						G[5];
	Double_t			b=0,
						c=0;

	// Parameters of bw-functions
	M[1]=par[3];		// M1
	G[1]=par[4];		// G1
	M[2]=par[5];		// M2
	G[2]=par[6];		// G2
	M[3]=par[7];		// M3
	G[3]=par[8];		// G3
	M[4]=par[9];		// M4
	G[4]=par[10];		// G4

	b=par[12];			// b
	c=par[0];    		// c

	Double_t		ReBW[5],	// Real part of ith peak
					ImBW[5],	// Imaginary part of ith peak
					den[5];		// denominator of ith peak

	Double_t		m=x[0];		// function variable

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

	Double_t		alpha[4];
	alpha[1]=par[14];
	alpha[2]=par[15];
	alpha[3]=par[16];

	/*Double_t		beta[4];
	beta[1]=par[17];
	beta[2]=par[18];
	beta[3]=par[19];

	Double_t		gamma[4];
	gamma[1]=par[20];
	gamma[2]=par[21];
	gamma[3]=par[22];*/

	Double_t		delta1=par[23];
	Double_t		delta2=par[24];

	Double_t		coherence_factor=par[25];


	Double_t		incoherent=0;
	for (int k=1;k<4;k++)
	{
		incoherent+=(alpha[k]**2)*(ReBW[k]**2+ImBW[k]**2);
	}
	Double_t		coherent=0;

	/*coherent=2*beta[1]*(ReBW[1]*ReBW[2]+ImBW[1]*ImBW[2]);
	coherent+=2*beta[2]*(ReBW[1]*ReBW[3]+ImBW[1]*ImBW[3]);
	coherent+=2*beta[3]*(ReBW[2]*ReBW[3]+ImBW[2]*ImBW[3]);

	coherent+=2*gamma[1]*(ReBW[1]*ImBW[2]-ReBW[2]*ImBW[1]);
	coherent+=2*gamma[2]*(ReBW[1]*ImBW[3]-ReBW[3]*ImBW[1]);
	coherent+=2*gamma[3]*(ReBW[2]*ImBW[3]-ReBW[3]*ImBW[2]);*/

	coherent=2*alpha[1]*alpha[2]*cos(delta1-delta2)*(ReBW[1]*ReBW[2]+ImBW[1]*ImBW[2]);
	coherent+=2*alpha[1]*alpha[3]*cos(delta1)*(ReBW[1]*ReBW[3]+ImBW[1]*ImBW[3]);
	coherent+=2*alpha[2]*alpha[3]*cos(delta2)*(ReBW[2]*ReBW[3]+ImBW[2]*ImBW[3]);

	coherent+=2*alpha[1]*alpha[2]*sin(delta1-delta2)*(ReBW[1]*ImBW[2]-ReBW[2]*ImBW[1]);
	coherent+=2*alpha[1]*alpha[3]*sin(delta1)*(ReBW[1]*ImBW[3]-ReBW[3]*ImBW[1]);
	coherent+=2*alpha[2]*alpha[3]*sin(delta2)*(ReBW[2]*ImBW[3]-ReBW[3]*ImBW[2]);




	// background
	Double_t	bg=0;
	bg=TMath::Exp(par[1]*(m))*TMath::Power(m,par[2]);

	// Total fit function
	Double_t	total=0;
	total=incoherent+coherence_factor*coherent+b*(ReBW[4]**2+ImBW[4]**2)+c*bg;

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
	Double_t 	x2=x[0]*x[0];
	Double_t 	m2=par[0]**2;
	Double_t 	g2=par[1]**2;

	Double_t	c=1.0000;


	Double_t bw=par[2]*(m2*par[1])/((x2-m2)**2+m2*g2);

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
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight.root");
	//TH1F *htemp2 = (TH1F*)f1->Get("h2");

	// ------------------------------------------------------------------//

	// --------------  I N I T I A L I Z A T I O N ----------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas("canv_default");
	Double_t par[30];
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
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1	,2.7,26);
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
	fsum->SetParName(12,"f0(1710) amplitude");

	fsum->SetParName(14,"alpha 1");
	fsum->SetParName(15,"alpha 2");
	fsum->SetParName(16,"alpha 3");

	fsum->SetParName(17,"beta 1");
	fsum->SetParName(18,"beta 2");
	fsum->SetParName(19,"beta 3");

	fsum->SetParName(20,"gamma 1");
	fsum->SetParName(21,"gamma 2");
	fsum->SetParName(22,"gamma 3");

	fsum->SetParName(23,"delta1");
	fsum->SetParName(24,"delta2");
	fsum->SetParName(25,"coherence factor");



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

	par[3]=mass_f2_1270_PDG*(1-0.006);
	par[4]=width_f2_1270_PDG;
	par[5]=mass_a2_1320_PDG*(1-0.006);
	par[6]=width_a2_1320_PDG;
	par[7]=mass_f2_1525_PDG*(1-0.006);
	par[8]=width_f2_1525_PDG;

	par[9]=1.695;
	par[10]=0.137;

	// --- fixing/limits --- //

	//par[11]=15;
	par[11]=0;
	par[13]=0;

	par[12]=50;



	par[14]=5;
	par[15]=5;
	par[16]=10;

	par[17]=0;fsum->FixParameter(17,par[17]);
	par[18]=0;fsum->FixParameter(18,par[18]);
	par[19]=0;fsum->FixParameter(19,par[19]);
	par[20]=0;fsum->FixParameter(20,par[20]);
	par[21]=0;fsum->FixParameter(21,par[21]);
	par[22]=0;fsum->FixParameter(22,par[22]);

	par[23]=0;//fsum->FixParameter(23,par[23]);
	par[24]=0;//fsum->FixParameter(24,par[24]);
	//par[25]=1;//fsum->FixParameter(25,par[25]);
	par[25]=0;
	fsum->SetParLimits(25,0,1);

	fsum->SetParameters(&par[0]);

	for (int kk=3;kk<9; kk++)
	{
		if ((kk!=7)&&(kk!=8))
		fsum->FixParameter(kk,par[kk]);
	}

	//fsum->FixParameter(9,par[9]); // f0 mass
	//fsum->FixParameter(10,par[10]); // f0 width



	//fsum->FixParameter(17,par[17]);
	//fsum->FixParameter(18,par[18]);
	//fsum->FixParameter(19,par[19]);

	//fsum->FixParameter(20,par[20]);
	//fsum->FixParameter(21,par[21]);
	//fsum->FixParameter(22,par[22]);



	//fsum->SetParLimits(5,0,10000);
	//fsum->SetParLimits(8,0,10000);

	fsum->FixParameter(11,par[11]);
	fsum->FixParameter(13,par[13]);



	//f
	//fsum->SetParLimits(11,0,10000);
	//fsum->FixParameter(12,bin_width);

	//-- fitting --//
	fsum->SetLineColor(2);
	fsum->Draw("same");
	htemp2->Fit("fsum","NQR+");
	htemp2->Fit("fsum","NQR+");
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
	fbw1->SetParameters(par[3],par[4],(par[14]**2));
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,4);
	fbw2->SetParameters(par[5],par[6],(par[15]**2));
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,4);
	fbw3->SetParameters(par[7],par[8],(par[16]**2));
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
	//cout<<(fbw4->Integral(0,10))/(fbw3->Integral(0,10))<<endl;


	TF1 *fsignal=new TF1("fsignal",rel_breit_wigner_bg,1.05,2.7,26);
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




