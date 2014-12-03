#include<canvas.cxx>
#include<TMath.h>

Double_t integrate(Double_t pos, Double_t width)
{
	TF1 *func=new TF1("func",rel_breit_wigner,1.05,2.3,3);
	func->SetParameters(pos,width,1);
	Double_t	integral=func->Integral(1.05,2.3);
	return integral;

	
}
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
	// par[0] -> par[2] BACKGROUND, see function "bg()"

	// 1st Breit-Wigner
	//par[3]=peak position f(1525) state
	//par[4]=FWHM
	//par[5]=constant

	// 2nd Breit-Wigner
	// par[6]=peak position f(1710) state
	// par[7]=FWHM
	// par[8]=Constant

	// 3rd Breit-Wigner
	// par[9]=peak position for f2/a2 interference
	// par[10]=FWHM
	// par[11]=Constant
/*
	// ----------  Simple bg --------- //
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]);
	Double_t	bg=par[0]*exp*pow;
	// ------------------------------- //
*/
	Double_t	xx=0;
	xx=x[0]*x[0];
	// ----------  hardcore  --------- //
	Double_t	mKK=2*0.497672;
	Double_t	lim=2.7-mKK;
	Double_t 	q=x[0]-mKK;
	if (q<0) return 0;

	Double_t	q2=q*q;
	Double_t	q3=q*q*q;
	Double_t	q4=q*q*q*q;
	Double_t	q5=q*q*q*q*q;

	Double_t	pol2=par[21]*q;
	//cout<<par[21]<<endl;
	Double_t	c=1/par[21];
	Double_t	e=exp(par[21]*lim);
	Double_t	I0=c*((lim**0)*e-1);
	Double_t	I1=c*((lim**1)*e-I0);
	Double_t	I2=c*((lim**2)*e-2*I1);
	Double_t	I3=c*((lim**3)*e-3*I2);
	Double_t	I4=c*((lim**4)*e-4*I3);
	Double_t	I5=c*((lim**5)*e-5*I4);

	Double_t	s=0;
	//par[14]=0;
	//par[15]=0;
	par[12]=0;
	for (int kk=13;kk<16;kk++) s=s+par[kk];
		
	Double_t	f0=par[12]/I0;
	Double_t	f1=par[13]*q/I1;
	Double_t	f2=par[14]*q2/I2;	
	Double_t	f3=par[15]*q3/I3;
	//Double_t	f3=(1-s)*q3/I3;
	Double_t	f4=(1-s)*q4/I4;
	//Double_t	f2=par[14]*(q2/I2+q4/I4);
	

	//Double_t	f3=(par[3]+par[4])(q3/I3+q4/I4);
	//Double_t	f4=(1-s)*q4/I4;
	//Double_t	f4=0;

	//Double_t	f5=(1-s)*q5/I5;
	Double_t	f5=0;
	Double_t	bg=par[20]*(f0+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
	// ------------------------------- //


	// -------  Breit-Wigners -------- //
	Double_t 	m1=TMath::Power(par[3],2);
	Double_t	g1=TMath::Power(par[4],2);
	Double_t	c1=integral(par[3],par[4]);
	Double_t 	bw1=1/(c1*(TMath::Power((xx-m1),2)+g1*m1));
	
	Double_t 	m2=TMath::Power(par[6],2);
	Double_t	g2=TMath::Power(par[7],2);
	Double_t	c2=integral(par[6],par[7]);
	Double_t 	bw2=1/(c2*(TMath::Power((xx-m2),2)+g2*m2));
	
	Double_t 	m3=TMath::Power(par[9],2);
	Double_t	g3=TMath::Power(par[10],2);
	Double_t	c3=integral(par[9],par[10]);
	Double_t 	bw3=par[11]/(c3*(TMath::Power((xx-m3),2)+g3*m3));
	// ------------------------------- //
		
	//return par[0]*exp*pow+par[5]*((1-par[8])*bw1+par[8]*bw2)+bw3;
	//bg=0;
	return bg+par[5]*bw1+par[8]*bw2+bw3;
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
	//Double_t	c=1;	
	Double_t bw=par[2]/(c*((x2-m2)*(x2-m2)+m2*g2));
	

	
	return bw;
}

Double_t bg(Double_t *x,Double_t *par)
{
	// Background function: polinom at K0sK0s threshold, fall-off exponent far from the threshold
	// par[0] - constant
	// par[1] - slope
	// par[2] - power
	//Double_t 	q=x[0]-2*0.497672;
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]); // exp*pol
	return par[0]*pow*exp;
}
Double_t bg_hard(Double_t *x,Double_t *par)
{
	// ----------  hardcore  --------- //
	Double_t	mKK=2*0.497672;
	Double_t	lim=2.7-mKK;
	Double_t 	q=x[0]-mKK;
	if (q<0) return 0;

	Double_t	q2=q*q;
	Double_t	q3=q*q*q;
	Double_t	q4=q*q*q*q;
	Double_t	q5=q*q*q*q*q;

	Double_t	pol2=par[21]*q;
	//cout<<par[21]<<endl;
	Double_t	c=1/par[21];
	Double_t	e=exp(par[21]*lim);
	Double_t	I0=c*((lim**0)*e-1);
	Double_t	I1=c*((lim**1)*e-I0);
	Double_t	I2=c*((lim**2)*e-2*I1);
	Double_t	I3=c*((lim**3)*e-3*I2);
	Double_t	I4=c*((lim**4)*e-4*I3);
	Double_t	I5=c*((lim**5)*e-5*I4);

	Double_t	s=0;
	//par[14]=0;
	//par[15]=0;
	par[12]=0;
	for (int kk=13;kk<16;kk++) s=s+par[kk];
		
	Double_t	f0=par[12]/I0;
	Double_t	f1=par[13]*q/I1;
	Double_t	f2=par[14]*q2/I2;	
	Double_t	f3=par[15]*q3/I3;
	//Double_t	f3=(1-s)*q3/I3;
	Double_t	f4=(1-s)*q4/I4;
	//Double_t	f2=par[14]*(q2/I2+q4/I4);
	

	//Double_t	f3=(par[3]+par[4])(q3/I3+q4/I4);
	//Double_t	f4=(1-s)*q4/I4;
	//Double_t	f4=0;

	//Double_t	f5=(1-s)*q5/I5;
	Double_t	f5=0;
	Double_t	bg=par[20]*(f0+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
	// ------------------------------- //
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
	// ------ INPUT -------- //
	TFile *f1 =new TFile("~/Libov/05e06p07p/0000834233/05e06p07p_COMMNTUP.root");
	//TH1F *htemp2 = (TH1F*)f1->Get("h2");
	//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_3_280");
	TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_3");
	// ----------------------//

	// -----------  I N I T I A L I Z A T I O N --------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas();
	Double_t par[25];
	htemp2->SetTitle("ZEUS");
	htemp2->Sumw2();
	htemp2->SetMarkerStyle(20);
	htemp2->GetYaxis()->SetTitleOffset(1.3);
	TFile *out=new TFile("~/Libov/heraII_fit.root","recreate");
	Int_t	nbins=htemp2->GetNbinsX();
	cout<<nbins<<" bins"<<endl;
	Float_t 	bin_width=0;
	bin_width=(5000.0-800)/nbins;
	cout<<"bin_width: "<<bin_width<<" MeV"<<endl;
	char Ytitle[25];
	Int_t n=0;
	n=sprintf(Ytitle,"Combinations/ %2.0f MeV",bin_width);
	cout<<Ytitle<<endl;
	htemp2->SetYTitle(Ytitle);
	htemp2->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
	htemp2->GetXaxis()->SetRangeUser(0.95,3);
	htemp2->Draw();
	// -------------------------------------------------------------//
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,0.9,2.7,22);
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

	// ------- Initial fitting (background parameters estimation) -------//
/*	TF1 *fbg1=new TF1("fbg1",bg,1.1,2.5,3);
	TF1 *fexp=new TF1("fexp",exp,1.2,2.5,2);
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
*/
	// ------- Initial fitting (hardcore background parameters estimation) -------//
	
	par[12]=0.07;
	par[13]=0.6;
	par[14]=-0.6;
	par[15]=1.3;

	par[20]=7000;
	par[21]=-1.6;
		
	TF1 *fbg1=new TF1("fbg1",bg_hard,0.994,2.7,22);
	for (int k=0;k<12;k++)
	fbg1->FixParameter(k,0);
	fbg1->SetParameters(&par[0]);
	htemp2->Fit("fbg1","R+");
	fbg1->GetParameters(&par[0]);
	//par[0]=par[0]/1.05;

	// ---
	par[3]=1.511;
	par[4]=0.07;
	par[5]=20;	
par[5]=130;
//par[5]=1.86*130;
//par[5]=230;

	par[6]=1.695;
	par[7]=0.15;
	par[8]=40;	
par[8]=110;
//par[8]=1.86*110;
//par[8]=0.52;
	par[9]=1.3;
	par[10]=0.08;
	par[11]=8;	
par[11]=50;

	
	//fsum->SetParLimits(5,0,300);
	//fsum->SetParLimits(8,0,300);
	//fsum->SetParLimits(11,0,300);
	//fsum->SetParLimits(8,0,1);
	

	// fixing/limits 

	fsum->FixParameter(3,1.523);
	fsum->FixParameter(4,0.076);
	//fsum->FixParameter(5,340);	
//fsum->FixParameter(6,1.686);
//fsum->FixParameter(7,0.156);
	fsum->FixParameter(9,1.304);
	fsum->FixParameter(10,0.103);
	//fsum->FixParameter(3,1.523);
	//fsum->FixParameter(4,0.071);
	fsum->FixParameter(6,1.692);
	fsum->FixParameter(7,0.125);
	//fsum->FixParameter(9,1.304);
	//fsum->FixParameter(10,0.061);

	fsum->FixParameter(0,0);
	fsum->FixParameter(1,0);
	fsum->FixParameter(2,0);

	fsum->FixParameter(16,0);
	fsum->FixParameter(17,0);
	fsum->FixParameter(18,0);
	fsum->FixParameter(19,0);
	
	//par[12]=0.07;
	//par[13]=0.6;
	//par[14]=-0.6;
	//par[15]=1.3;

	//par[20]=7000;
	//par[21]=-1.6;
	

	fsum->SetParameters(&par[0]);
	//cout<<"@@: "<<par[21]<<endl;
	//fsum->Draw("same");
	htemp2->Fit("fsum","R+");
	fsum->GetParameters(&par[0]);
	//cout<<"@@@@: "<<par[21]<<endl;

	// -----   R E S U L T S   ----- // 

	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2.10,3);
	fbw1->SetParameters(par[3],par[4],par[5]);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,3);
	fbw2->SetParameters(par[6],par[7],par[8]);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,3);
	fbw3->SetParameters(par[9],par[10],par[11]);
	fbw3->Draw("same");

	TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	//fbg->Draw("same");
	
	TF1 *fbgh=new TF1("fbgh",bg_hard,0.994,2.3,22);
	fbgh->SetParameters(&par[0]);
	fbgh->SetLineColor(3);
	fbgh->Draw("same");

/*
	Double_t	int1=integral(par[3],par[4]);
	Double_t	int2=integral(par[6],par[7]);
	int1=par[5]/(0.001*bin_width);
	int2=par[8]/(0.001*bin_width);
	cout<<int1<<" &&& "<<int2<<endl;

	Double_t 	mass_1525=par[3],
			FWHM_1525=par[4],
			mass_1710=par[6],
			FWHM_1710=par[7];
	cout<<mass_1525<<" "<<FWHM_1525<<" "<<mass_1710<<" "<<FWHM_1710<<endl;
	Double_t 	area_1525=(fbw1->Integral(mass_1525-5*FWHM_1525,mass_1525+10*FWHM_1525))/(0.001*bin_width),
			area_1710=(fbw2->Integral(mass_1710-5*FWHM_1710,mass_1710+10*FWHM_1710))/(0.001*bin_width);
	Double_t	bg_1525=(fbg->Integral(mass_1525-5*FWHM_1525,mass_1525+10*FWHM_1525))/(0.001*bin_width),
			bg_1710=(fbg->Integral(mass_1710-5*FWHM_1710,mass_1710+10*FWHM_1710))/(0.001*bin_width);




	Double_t	sign_1525=par[5]/(fsum->GetParError(5));
	Double_t	sign_1710=par[8]/(fsum->GetParError(8));


cout<<"1525: "<<area_1525<<" events; "<<"S/B: "<<area_1525/bg_1525<<"; Significance: "<<sign_1525<<endl;
cout<<"1710: "<<area_1710<<" events; "<<"S/B: "<<area_1710/bg_1710<<"; Significance: "<<sign_1710<<endl;


	cout<<"RATI@ "<<par[8]/(1-par[8])<<endl;
	cout<<"ERROR "<<((1/(1-par[8]))**2)*(fsum->GetParError(8))<<endl;



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
		n=sprintf(result,"Ratio= %2.2f",area_1710/area_1525);
		text = pt->AddText(result);
		pt->SetFillColor(3);
		pt->Draw("same");
*/
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
/*	Double_t	ratio=area_1710/area_1525;

	Double_t	rat_err1=0;
	Double_t	area_1525_abs_err=area_1525/sign_1525;
	Double_t	area_1710_abs_err=area_1710/sign_1710;
	rat_err1=ratio*sqrt( ((1/area_1710)*area_1710_abs_err)**2 +((1/area_1525)*area_1525_abs_err)**2);
	Double_t	rat_err2=ratio*sqrt((1/sign_1525)**2+(1/sign_1710)**2);
	
	cout<<"f0(1710)/f2(1525)= "<<ratio<<endl;
	cout<<"NAIVE error = "<<rat_err1<<" = "<<rat_err2<<endl;

	gMinuit->mnmatu(1);

	cout<<"*************************************************************"<<endl;
	Double_t	ratio3=par[8]/par[5];
	Double_t	rat_err3=ratio3*sqrt((1/sign_1525)**2+(1/sign_1710)**2);
	cout<<"ratio: "<<ratio3<<" +- "<<rat_err3<<endl;
*/
		return 0;
}
