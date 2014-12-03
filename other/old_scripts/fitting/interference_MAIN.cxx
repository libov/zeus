#include<canvas.cxx>
#include<TMath.h>
bool			same_coherence=false;
bool			fully_incoherent=false;
bool			full_coherence=false;
bool			correct_mass=false;
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
	//____________________
	Double_t			M[5],
						G[5];
	// Parameters of bw-functions
	M[1]=par[3];		// M1
	G[1]=par[4];		// G1
	M[2]=par[5];		// M2
	G[2]=par[6];		// G2
	M[3]=par[7];		// M3
	G[3]=par[8];		// G3
	M[4]=par[9];		// M4
	G[4]=par[10];		// G4

	Double_t			bg_ampl=par[0];    		// c

	Double_t		ReBW[5],							// Real part of ith peak
					ImBW[5],							// Imaginary part of ith peak
					den[5];							// denominator of ith peak

	Double_t		m=x[0];							// function variable

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

	Double_t			alpha[4];
	alpha[1]=par[11];
	alpha[2]=par[12];
	alpha[3]=par[13];

	Double_t			delta1=par[14];
	Double_t			delta2=par[15];

	Double_t			coh_fact_12=par[16];
	Double_t			coh_fact_13=par[17];
	Double_t			coh_fact_23=par[18];

	if		(same_coherence)
	{
		coh_fact_13=coh_fact_12;
		coh_fact_23=coh_fact_12;
	}

	Double_t			f0_1710_ampl=par[19];			// b

	Double_t		incoherent=0;
	for (int k=1;k<4;k++)
	{
		incoherent+=(alpha[k]**2)*(ReBW[k]**2+ImBW[k]**2);
	}
	Double_t		coherent=0;

	Double_t		interf_12=0;
	Double_t		interf_13=0;
	Double_t		interf_23=0;

	interf_12+=2*alpha[1]*alpha[2]*cos(delta1-delta2)*(ReBW[1]*ReBW[2]+ImBW[1]*ImBW[2]);
	interf_12+=2*alpha[1]*alpha[2]*sin(delta1-delta2)*(ReBW[1]*ImBW[2]-ReBW[2]*ImBW[1]);
	interf_12=interf_12*coh_fact_12;

	interf_13+=2*alpha[1]*alpha[3]*cos(delta1)*(ReBW[1]*ReBW[3]+ImBW[1]*ImBW[3]);
	interf_13+=2*alpha[1]*alpha[3]*sin(delta1)*(ReBW[1]*ImBW[3]-ReBW[3]*ImBW[1]);
	interf_13=interf_13*coh_fact_13;

	interf_23+=2*alpha[2]*alpha[3]*cos(delta2)*(ReBW[2]*ReBW[3]+ImBW[2]*ImBW[3]);
	interf_23+=2*alpha[2]*alpha[3]*sin(delta2)*(ReBW[2]*ImBW[3]-ReBW[3]*ImBW[2]);
	interf_23=interf_23*coh_fact_23;

	Double_t			interference=0;
	interference=interf_12+interf_13+interf_23;

	/*coherent=2*alpha[1]*alpha[2]*cos(delta1-delta2)*(ReBW[1]*ReBW[2]+ImBW[1]*ImBW[2]);
	coherent+=2*alpha[1]*alpha[3]*cos(delta1)*(ReBW[1]*ReBW[3]+ImBW[1]*ImBW[3]);
	coherent+=2*alpha[2]*alpha[3]*cos(delta2)*(ReBW[2]*ReBW[3]+ImBW[2]*ImBW[3]);

	coherent+=2*alpha[1]*alpha[2]*sin(delta1-delta2)*(ReBW[1]*ImBW[2]-ReBW[2]*ImBW[1]);
	coherent+=2*alpha[1]*alpha[3]*sin(delta1)*(ReBW[1]*ImBW[3]-ReBW[3]*ImBW[1]);
	coherent+=2*alpha[2]*alpha[3]*sin(delta2)*(ReBW[2]*ImBW[3]-ReBW[3]*ImBW[2]);*/

	// background
	Double_t	bg=0;
	bg=TMath::Exp(par[1]*(m))*TMath::Power(m,par[2]);

	Double_t	total=0;
	total=incoherent+interference+f0_1710_ampl*(ReBW[4]**2+ImBW[4]**2)+bg_ampl*bg;
	//____________________
	return total;
}
Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	Double_t 	x2=x[0]*x[0];
	Double_t 	m2=par[0]**2;
	Double_t 	g2=par[1]**2;
	Double_t bw=par[2]*(m2*par[1])/((x2-m2)**2+m2*g2);
	return bw;
}
Double_t bg(Double_t *x,Double_t *par)
{
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]);
	return par[0]*pow*exp;
}
Double_t exp(Double_t *x,Double_t *par)
{
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*q);
	return par[0]*exp;
}

int interference_MAIN()
{
	same_coherence=true;
	fully_incoherent=true;
	full_coherence=false;
	correct_mass=false;

	Double_t			mass_f2_1270_PDG=1.2751;
	Double_t			width_f2_1270_PDG=0.185;
	Double_t			mass_a2_1320_PDG=1.3183;
	Double_t			width_a2_1320_PDG=0.107;
	Double_t			mass_f2_1525_PDG=1.525;
	Double_t			width_f2_1525_PDG=0.073;
	Double_t			mass_f0_1710_PDG=1.717;
	Double_t			width_f0_1710_PDG=0.137;


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
	cout<<"MC-to-data-scale region: "<<endl;
	cout<<htemp2->GetBinLowEdge(80)<<endl;
	cout<<htemp2->GetBinLowEdge(147)<<endl;
	char Ytitle[25];
	Int_t n=0;
	n=sprintf(Ytitle,"Combinations/ %1.3f GeV",bin_width);
	cout<<Ytitle<<endl;
	htemp2->SetYTitle(Ytitle);
	htemp2->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
	htemp2->GetXaxis()->SetRangeUser(0.95,3);
	htemp2->GetYaxis()->SetRangeUser(-500,9000);
	htemp2->Draw();
	// ------------------//
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1,2.7,20);
	fsum->SetLineColor(2);
	fsum->SetParName(0,"BG: Constant");
	fsum->SetParName(1,"BG: Exponent slope");
	fsum->SetParName(2,"BG: Power");
	fsum->SetParName(3,"f_{2}(1270): peak position");
	fsum->SetParName(4,"f_{2}(1270): FWHM");
	fsum->SetParName(5,"a_{2}(1320): peak position");
	fsum->SetParName(6,"a_{2}(1320): FWHM");
	fsum->SetParName(7,"f_{2}(1525): peak position");
	fsum->SetParName(8,"f_{2}(1525): FWHM");
	fsum->SetParName(9,"f_{0}(1710)::peak position");
	fsum->SetParName(10,"f_{0}(1710)::FWHM");
	fsum->SetParName(11,"#alpha_{1} (f_{2}(1270))");
	fsum->SetParName(12,"#alpha_{2} (a_{2}(1320))");
	fsum->SetParName(13,"#alpha_{3} (f_{2}(1525))");
	fsum->SetParName(14,"#delta_{1}");
	fsum->SetParName(15,"#delta_{2}");
	fsum->SetParName(16,"coherence factor 12");
	fsum->SetParName(17,"coherence factor 13");
	fsum->SetParName(18,"coherence factor 23");
	fsum->SetParName(19,"f_{0}(1710) amplitude");


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

	Double_t		mass_correction=1.0000000;

	if (correct_mass) mass_correction=(1-0.006);

	par[3]=mass_f2_1270_PDG*mass_correction;
	par[4]=width_f2_1270_PDG;
	par[5]=mass_a2_1320_PDG*mass_correction;
	par[6]=width_a2_1320_PDG;
	par[7]=mass_f2_1525_PDG*mass_correction;
	par[8]=width_f2_1525_PDG;
	par[9]=mass_f0_1710_PDG*mass_correction;
	par[10]=width_f0_1710_PDG;

	par[11]=5;		fsum->SetParLimits(11,0,1000);				//alpha1
	par[12]=5;		fsum->SetParLimits(12,0,1000);				//alpha2
	par[13]=10;		fsum->SetParLimits(13,0,1000);				//alpha3

	par[14]=0;						//delta1
	par[15]=0;						//delta2

	par[16]=0;						//coh fact 12
	par[17]=0;						//coh fact 13
	par[18]=0;						//coh fact 23

	par[19]=50;			//f0(1710) amplitude

	//_______  coherence factors _________//
	fsum->SetParLimits(16,0,1);
	fsum->SetParLimits(17,0,1);
	fsum->SetParLimits(18,0,1);

	if (same_coherence)
	{
			fsum->FixParameter(17,par[17]);
			fsum->FixParameter(18,par[18]);
	}

	if (fully_incoherent)
	{
			fsum->FixParameter(14,par[14]);
			fsum->FixParameter(15,par[15]);
			fsum->FixParameter(16,par[16]);
			fsum->FixParameter(17,par[17]);
			fsum->FixParameter(18,par[18]);
	}

	if (full_coherence)
	{
		par[16]=1.000;
		fsum->FixParameter(16,par[16]);
	}



	//fsum->FixParameter(17,par[17]);
	//fsum->FixParameter(18,par[18]);
	TF1 *finit=new TF1("finit",rel_breit_wigner_bg,1.1,2.7,20);
	finit->SetParameters(&par[0]);
	fsum->SetParameters(&par[0]);

	//______ fixing resonance parameters _______//
	for (int kk=3;kk<9; kk++)
	{
		if ((kk!=7)&&(kk!=8))
		fsum->FixParameter(kk,par[kk]);
	}
	//fsum->FixParameter(9,par[9]); // f0 mass
	//fsum->FixParameter(10,par[10]); // f0 width
	//___________________________________________//


	//________________ fitting ________________//
	fsum->SetLineColor(2);
	fsum->Draw("same");

	htemp2->Fit("fsum","NQR+");
	htemp2->Fit("fsum","NQR+");
	htemp2->Fit("fsum","R+");

	fsum->GetParameters(&par[0]);
	//______________________________________________//

	// ----------------------   R E S U L T S   ------------------------ //

	cout<<"*******************************************************"<<endl;
	gMinuit->mnmatu(1);
	//gMinuit->mnimpr();
	cout<<"*******************************************************"<<endl;

	TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	fbg->Draw("same");
	//par[11]=7;
	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2.10,4);
	fbw1->SetParameters(par[3],par[4],(par[11]**2));
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,4);
	fbw2->SetParameters(par[5],par[6],(par[12]**2));
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,4);
	fbw3->SetParameters(par[7],par[8],(par[13]**2));
	fbw3->Draw("same");

	TF1 *fbw4=new TF1("fbw4",rel_breit_wigner,0,10,4);
	fbw4->SetParameters(par[9],par[10],par[19]);
	fbw4->Draw("same");


	Double_t		f2_1525_integral=fbw3->Integral(par[7]-4*par[8],par[7]+4*par[8]);
	cout<<"f2_1525_integral= "<<f2_1525_integral/bin_width<<endl;

	Double_t		f0_1710_integral=fbw4->Integral(par[9]-4*par[10],par[9]+4*par[10]);
	cout<<"f0_1710_integral= "<<f0_1710_integral/bin_width<<endl;

	cout<<"Ratio: "<<f0_1710_integral/f2_1525_integral<<endl;

	DrawPaveText(f0_1710_integral/f2_1525_integral);

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


	TF1 *fsignal=new TF1("fsignal",rel_breit_wigner_bg,1.05,2.7,20);
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


	//TFile *fMC =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijetPHPv2.root");
	TFile *fMC =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijet_basic_substr.root");
	TH1F *hMC = (TH1F*)fMC->Get("h2_signal");

	Double_t			scale_factor=(htemp2->Integral(80,280))/(hMC->Integral(80,280));
	hMC->Scale(scale_factor);
	//hMC->Draw("same");

	TH1F *hpull=new TH1F("hpull","",280,0.8,5);
	for(int bin=20;bin<148;bin++)
	{
		Double_t			error=htemp2->GetBinError(bin);
		Double_t			bin_content=htemp2->GetBinContent(bin);
		Double_t			bin_center=htemp2->GetBinCenter(bin);
		Double_t			fitted_value=fsum->Eval(bin_center);
		Double_t			deviation=fitted_value-bin_content;
		hpull->SetBinContent(bin,deviation);
		hpull->SetBinError(bin,error);
	}
	hpull->Draw("same");
	//_________________________//
	finit->SetLineColor(4);
	finit->SetLineStyle(3);
	finit->SetLineWidth(1);
	finit->Draw("same");

	return 0;
}

void DrawPaveText(Double_t rat)
{
	TPaveText *pt = new TPaveText(0.55,0.17,0.85,0.27,"brNDC");
	char result[256];

	Int_t	n=sprintf(result,"Ratio f_{0}/f'_{2}= %2.2f",rat);
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




