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

	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]); //polinom*exp
	
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

	return par[0]*exp*pow+bin_width*par[8]*(par[5]*bw1+(1-par[5])*bw2)+par[11]*bin_width*bw3;
	//return par[0]*exp*pow+bin_width*par[8]*(bw1/(1+par[5])+bw2*par[5]/(1+par[5]))+par[11]*bin_width*bw3;
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
	// ---------------------------- I N P U T  ------------------------- //
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e06p07p_COMMNTUP.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e06p07p_COMMNTUP_lower_bg_secvtx.root");
	TH1F *htemp2 = (TH1F*)f1->Get("h2");
	//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_3");
	// ------------------------------------------------------------------//

	// --------------  I N I T I A L I Z A T I O N ----------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas();
	Double_t par[15];
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
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.07,2.7,13);
	fsum->SetLineColor(2);
	fsum->SetParName(0,"BG::Constant");
	fsum->SetParName(1,"BG::exp slope");
	fsum->SetParName(2,"BG::Power(optional)");
	fsum->SetParName(3,"BW1::peak position");
	fsum->SetParName(4,"BW1::FWHM");
	fsum->SetParName(5,"BW1::area fraction");
	fsum->SetParName(6,"BW2::peak position");
	fsum->SetParName(7,"BW2::FWHM");
	fsum->SetParName(8,"area f0+f2");
	fsum->SetParName(9,"BW3::peak position");
	fsum->SetParName(10,"BW3::FWHM");
	fsum->SetParName(11,"BW3::Area");
	fsum->SetParName(12,"bin_width");
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
	par[3]=1.511;
	par[4]=0.07;
	par[5]=9000;
	par[5]=0.5;
	//par[5]=0.8;


	par[6]=1.695;
	par[7]=0.15;
	par[8]=6200+7000;
	//par[8]=0.4;

	par[9]=1.3;
	par[10]=0.08;
	par[11]=3000;
	//par[11]=20000;

	par[12]=bin_width;

/*
	par[0]=133500;
	par[1]=-2.48;
	par[2]=3.006;
	par[3]=1.518;
	par[4]=0.09442;
	par[5]=9653.0/(9653+6536);
	par[6]=1.693;
	par[7]=0.1409;
	par[8]=9653+6536;
	par[9]=1.301;
	par[10]=0.1166;
	par[11]=4687;
*/


	// --- fixing/limits --- //

	fsum->SetParameters(&par[0]);
	//fsum->SetParLimits(5,0,10000);
	//fsum->SetParLimits(8,0,10000);
	//fsum->SetParLimits(11,0,10000);
	fsum->FixParameter(12,bin_width);

	//-- f i t t i n g --//

	//fsum->Draw("same");
	//htemp2->Fit("fsum","MR");
	htemp2->Fit("fsum","R");
	fsum->GetParameters(&par[0]);


	// ----------------------   R E S U L T S   ------------------------ //

	cout<<"*******************************************************"<<endl;
	gMinuit->mnmatu(1);
	//gMinuit->mnimpr();
	//gMinuit->mnimpr();
	cout<<"*******************************************************"<<endl;

	TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	fbg->Draw("same");



	Double_t	tot_area=par[8];
	Double_t	fraction=par[5];

	Double_t	tot_area_err=fsum->GetParError(8);
	Double_t	fraction_err=fsum->GetParError(5);

	Double_t	area_1525=0,
			area_1710=0;
	area_1525=fraction*tot_area;
	area_1710=(1-fraction)*tot_area;
	cout<<"Areas: "<<endl;
	cout<<"f2(1525): "<<area_1525<<endl;
	cout<<"f0(1710): "<<area_1710<<endl;

	Double_t	sign_1525=1/sqrt((tot_area_err/tot_area)**2+(fraction_err/fraction)**2);
	Double_t	sign_1710=1/sqrt((tot_area_err/tot_area)**2+(fraction_err/(1-fraction))**2);

	cout<<"Significance:"<<endl;
	cout<<"f2(1525): "<<sign_1525<<endl;
	cout<<"f0(1710): "<<sign_1710<<endl;

	Double_t	ratio=(1-par[5])/par[5];
	Double_t	rat_err=ratio*sqrt((1/sign_1525)**2+(1/sign_1710)**2);
	Double_t	rat_err_correct=fraction_err/(par[5]**2);
	cout<<"ratio= "<<ratio<<" +- "<<rat_err<<endl;
	cout<<"ratio= "<<ratio<<" +- "<<rat_err_correct<<endl;
	cout<<(1-par[5])/par[5]<<endl;


	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2.10,4);
	fbw1->SetParameters(par[3],par[4],area_1525,bin_width);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,0,10,4);
	fbw2->SetParameters(par[6],par[7],area_1710,bin_width);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,0,10,4);
	fbw3->SetParameters(par[9],par[10],par[11],bin_width);
	fbw3->Draw("same");


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
	n=sprintf(result,"Ratio= %2.2f #pm %2.2f",ratio,rat_err_correct);
	text = pt->AddText(result);
	pt->SetFillColor(3);
	pt->Draw("same");
	//-------------------------------------------------------------------//
	/*
	leg1 = new TLegend(0.55,0.55,0.89,0.89);
	leg1->AddEntry(htemp2,"ZEUS 0.5fb^-1","p");
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
