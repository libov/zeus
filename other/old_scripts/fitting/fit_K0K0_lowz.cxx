#include<canvas.cxx>
#include<TMath.h>

/*
// commented if f0(980) is condsidered
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

	Double_t 	q=x[0]-2*0.497672;
	//Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]); //polinom*exp
	//Double_t 	pow=1.0000;  // simple exp


	Double_t 	xx=TMath::Power(x[0],2);

	Double_t 	m1=TMath::Power(par[3],2);
	Double_t	g1=TMath::Power(par[4],2);
	Double_t 	bw1=par[5]/(TMath::Power((xx-m1),2)+g1*m1);

	Double_t 	m2=TMath::Power(par[6],2);
	Double_t	g2=TMath::Power(par[7],2);
	Double_t 	bw2=par[8]/(TMath::Power((xx-m2),2)+g2*m2);

	Double_t 	m3=TMath::Power(par[9],2);
	Double_t	g3=TMath::Power(par[10],2);
	Double_t 	bw3=par[11]/(TMath::Power((xx-m3),2)+g3*m3);
	return par[0]*exp*pow+bw1+bw2+bw3;
}*/
Double_t bw_interference(Double_t *x,Double_t *par)
{
	// for function description
	// see "Incl. K0sK0s Resonance Production" paper:
	// arXiv:0806.0807

	//BACKGROUND, see function "bg()"
	//par[0]    c
	//par[1]
	//par[2]

	//par[3]    M1
	//par[4]    G1
	//par[5]    M2
	//par[6]    G2
	//par[7]    M3
	//par[8]    G3
	//par[9]    M4
	//par[10]   G4

	//par[11]   a
	//par[12]   b


	Double_t	ReBW1=0,
			ReBW2=0,
			ReBW3=0,
			ReBW4=0,
			ImBW1=0,
			ImBW2=0,
			ImBW3=0,
			ImBW4=0;




}

Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=par[2]/((x2-m2)*(x2-m2)+m2*g2);
	return bw;
}

Double_t bg(Double_t *x,Double_t *par)
{
	// Background function: polinom at K0sK0s threshold, fall-off exponent far from the threshold
	// par[0] - constant
	// par[1] - slope
	// par[2] - power
	Double_t 	q=x[0]-2*0.497672;
	if (q<0) return 0;
	//Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]); // exp*pol
	//pow=1.00000; //simple exp
	return par[0]*pow*exp;
}

Double_t exp(Double_t *x,Double_t *par)
{
	// Simple background function: fall-off exponent
	// par[0] - constant
	// par[1] - exponent slope

	//Double_t 	q=x[0]-2*0.497672;
	Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	return par[0]*exp;
}
//---------------------------------------------------------------------------
// The following functions added in order to fit bump an the threshold
Double_t f0(Double_t *x,Double_t *par)
{
	//	par[0] - normalization of the signal
	//	par[1] - mass (peak position for the underlying BW !!!)
	//	par[2] - width (of the underlying BW !!!)

	Double_t	m=x[0];
	Double_t	ph_space=0,
			bw=0;
	//Double_t	mK0=0.497648;
	Double_t	mK0=0.497672;
	Double_t	mf0=par[1];
	Double_t	Gf0=par[2];

	// phase space correction
	ph_space=par[0]*sqrt((1-4*(mK0/m)*(mK0/m)));

	// breit-wigner
	Double_t	mf0_sq=mf0*mf0;
	bw=(mf0_sq*Gf0)/((mf0_sq-m*m)*(mf0_sq-m*m)+mf0_sq*Gf0*Gf0);

	if (m>2*mK0)
	{
		return (bw*ph_space);
	}
	else
		return 0;

}
// modified fit function -> f0(980)
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
	// par[9]=peak position a2/f2 states
	// par[10]=FWHM
	// par[11]=Constant

	// f0(980): bw*(phase space)
	// par[12]=peak position f(980) state
	// par[13]=FWHM
	// par[14]=Constant
	Double_t 	q=x[0]-2*0.497672;
	if (q<0) return 0;
	//Double_t 	q=x[0];
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]); //polinom*exp
	//Double_t 	pow=1.0000;  // simple exp

	Double_t 	xx=TMath::Power(x[0],2);

	Double_t 	m1=TMath::Power(par[3],2);
	Double_t	g1=TMath::Power(par[4],2);
	Double_t 	bw1=par[5]/(TMath::Power((xx-m1),2)+g1*m1);

	Double_t 	m2=TMath::Power(par[6],2);
	Double_t	g2=TMath::Power(par[7],2);
	Double_t 	bw2=par[8]/(TMath::Power((xx-m2),2)+g2*m2);

	Double_t 	m3=TMath::Power(par[9],2);
	Double_t	g3=TMath::Power(par[10],2);
	Double_t 	bw3=par[11]/(TMath::Power((xx-m3),2)+g3*m3);
	// f0(980) modification
	Double_t	m=x[0];
	Double_t	ph_space=0,
			bw=0;
	Double_t	mK0=0.497672;
	Double_t	mf0=par[12];
	Double_t	Gf0=par[13];
	Double_t	f0=0;
	// phase space correction
	ph_space=par[14]*sqrt((1-4*(mK0/m)*(mK0/m)));

	// breit-wigner
	Double_t	mf0_sq=mf0*mf0;
	bw=(mf0_sq*Gf0)/((mf0_sq-m*m)*(mf0_sq-m*m)+mf0_sq*Gf0*Gf0);
	if (m>2*mK0)
	{
		f0=bw*ph_space;
		//f0=0;

	}
	else
	{
		f0=0;
	}

	return par[0]*exp*pow+bw1+bw2+bw3+f0;
}


// Background + peak (bw times phase space)
Double_t f0_bg(Double_t *x,Double_t *par)
{
	//	par[0] - normalization of the signal
	//	par[1] - mass (peak position for the underlying BW !!!)
	//	par[2] - width (of the underlying BW !!!)

	//	par[3] - power in bg function
	//	par[4] - normalization of bg

	Double_t	m=x[0];
	Double_t	ph_space=0,
			bw=0;
	//Double_t	mK0=0.497648;
	Double_t	mK0=0.497672;
	Double_t	mf0=par[1];
	Double_t	Gf0=par[2];

	// phase space correction
	ph_space=par[0]*sqrt((1-4*(mK0/m)*(mK0/m)));

	// breit-wigner
	Double_t	mf0_sq=mf0*mf0;
	bw=(mf0_sq*Gf0)/((mf0_sq-m*m)*(mf0_sq-m*m)+mf0_sq*Gf0*Gf0);

	// background
	Double_t	pow=par[3];
	//Double_t	bg=par[2]*(TMath::Exp((m-2*mK0)*pow)-1);
	Double_t	bg=par[4]*(TMath::Power((m-2*mK0),pow));

	if (m>2*mK0)
	{
		return (bw*ph_space+bg);
	}
	else
		return 0;

}
//-----------------------------------------------------------------//

int main()
{
	cout<<TMath::Pi()<<endl;

	// ------ INPUT -------- //


TFile *f1 =new TFile("/data/zenith226a/libov/results/plots/05e06p07p.root");
TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_5");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/plots/05e06p07p_280.root");
//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_5_280");


	// ----------------------//

	// -----------  I N I T I A L I Z A T I O N ----------------- //
	gStyle->SetOptFit(0000);
	CreateCanvas();
	Double_t par[15];
	htemp2->Sumw2();
	htemp2->SetMarkerStyle(20);
	htemp2->GetYaxis()->SetTitleOffset(1.3);
	TFile *out=new TFile("/data/zenith226a/libov/results/K0sK0s_hist/heraII_fit.root","recreate");
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
	//TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1,2.7,12);
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,0.99,2.5,15);
	//TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.2,2.5,15);
	fsum->SetLineColor(2);
	fsum->SetParName(0,"BG::Constant");
	fsum->SetParName(1,"BG::exp slope");
	fsum->SetParName(2,"BG::Power(optional)");
	fsum->SetParName(3,"BW1::peak position");
	fsum->SetParName(4,"BW1::FWHM");
	fsum->SetParName(5,"BW1::constant");
	fsum->SetParName(6,"BW2::peak position");
	fsum->SetParName(7,"BW2::FWHM");
	fsum->SetParName(8,"BW2::constant");
	fsum->SetParName(9,"BW3::peak position");
	fsum->SetParName(10,"BW3::FWHM");
	fsum->SetParName(11,"BW3::constant");
	fsum->SetParName(12,"f0::peak position");
	fsum->SetParName(13,"f0::FWHM");
	fsum->SetParName(14,"f0::constant");


	TF1 *fbg1=new TF1("fbg1",bg,1.1,2.5,3);

	TF1 *fexp=new TF1("fexp",exp,1.2,2.5,2);
	fexp->SetLineColor(4);
	htemp2->Fit("fexp","NQR");
	fexp->GetParameters(&par[0]);

	par[2]=0.5;
	cout<<par[0]<<" "<<par[1]<<" "<<par[2]<<endl;

	fbg1->SetParameters(&par[0]);
	//fbg1->SetParameter(3,0.95);
	fbg1->SetLineColor(7);
	//fbg1->Draw("same");
	htemp2->Fit("fbg1","NR+");
	fbg1->GetParameters(&par[0]);

	// initials
	par[0]=par[0]/1.05;

	par[3]=1.5;	fsum->SetParLimits(3, 1.49,1.51);
	par[4]=0.07;
	par[5]=3;

	par[6]=1.68;	fsum->SetParLimits(6, 1.67,1.69);
	par[7]=0.25;
	par[8]=25;

	par[9]=1.39;	fsum->SetParLimits(9, 1.38,1.4);
	par[10]=0.05;	fsum->SetParLimits(10,0,0.13);
	par[11]=0.5;

	par[12]=0.98;
	par[13]=0.05;	fsum->SetParLimits(13,0,0.1);
	par[14]=1300;

	//par[12]=0.95;
	//par[13]=0.1;
	//par[14]=1700;    // hk0k0_5_280

	// constants must be positive
	fsum->SetParameters(&par[0]);
	fsum->SetParLimits(5,0,5000000);
	fsum->SetParLimits(8,0,5000000);
	fsum->SetParLimits(11,0,5000000);
	fsum->SetParLimits(14,0,5000000);

	// no signal
/*
	fsum->FixParameter(5,0);
	fsum->FixParameter(8,0);
	fsum->FixParameter(11,0);
	//fsum->FixParameter(14,0);
*/
	//fsum->FixParameter(8,0);
/*
	// additional constraints on norm constants
	fsum->SetParLimits(5,0,50);
	fsum->SetParLimits(8,0,50);
	fsum->SetParLimits(11,0,50);
	fsum->SetParLimits(14,0,50);
*/

	fsum->Draw("same");
	//htemp2->Fit("fsum","R+");

	fsum->GetParameters(&par[0]);

	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1.05,2.3,3);
	fbw1->SetParameters(par[3],par[4],par[5]);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,1.05,2.3,3);
	fbw2->SetParameters(par[6],par[7],par[8]);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,1.05,2.3,3);
	fbw3->SetParameters(par[9],par[10],par[11]);
	fbw3->Draw("same");

	TF1 *fbg=new TF1("fbg",bg,0.99,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	fbg->Draw("same");

	TF1 *ff0=new TF1("ff0",f0,0.7,1.7,5);
	ff0->SetParameters(par[14],par[12],par[13]);
	ff0->SetLineColor(7);
	ff0->SetLineWidth(3);
	ff0->Draw("same");


	TF1 *f0_bw=new TF1("f0_bw",rel_breit_wigner,0.7,1.7,3);
	f0_bw->SetParameters(par[12],par[13],par[14]);
	f0_bw->SetLineColor(8);
	f0_bw->SetLineStyle(3);
	f0_bw->SetLineWidth(2);
	f0_bw->Draw("same");

		/*Double_t 	mass_1525=par[3],
				FWHM_1525=par[4],
				mass_1710=par[6],
				FWHM_1710=par[7];
		cout<<mass_1525<<" "<<FWHM_1525<<" "<<mass_1710<<" "<<FWHM_1710<<endl;
		Double_t 	area_1525=1000*(fbw1->Integral(mass_1525-3*FWHM_1525,mass_1525+3*FWHM_1525))/bin_width,
				area_1710=1000*(fbw2->Integral(mass_1710-3*FWHM_1710,mass_1710+3*FWHM_1710))/bin_width;
		Double_t	bg_1525=1000*(fbg->Integral(mass_1525-3*FWHM_1525,mass_1525+3*FWHM_1525))/bin_width,
				bg_1710=1000*(fbg->Integral(mass_1710-3*FWHM_1710,mass_1710+3*FWHM_1710))/bin_width;
		Double_t	area_1525_err=par[5]/(fsum->GetParError(5));
		Double_t	area_1710_err=par[8]/(fsum->GetParError(8));


		//cout<<"1525: "<<area_1525<<" events; "<<"S/B: "<<area_1525/bg_1525<<endl;
		//cout<<"1710: "<<area_1710<<" events; "<<"S/B: "<<area_1710/bg_1710<<endl;
		cout<<area_1525_err<<"; "<<area_1710_err<<endl;


		*/


		/*pt = new TPaveText(0.25,0.6,0.55,0.85,"brNDC");
   		pt->SetFillColor(0);
		char result[256];
		text = pt->AddText("Number of Candidates: ");
		n=sprintf(result,"f'_{2}(1525): %d #pm %d (%2.2f #sigma)",(Int_t)area_1525,area_1525/area_1525_err,area_1525_err);
		text = pt->AddText(result);
		n=sprintf(result,"f_{0}(1710): %d #pm %d (%2.2f #sigma)",(Int_t)area_1710,area_1710/area_1710_err,area_1710_err);
		text = pt->AddText(result);
		n=sprintf(result,"#chi^{2} /ndf= %2.2f",fsum->GetChisquare()/fsum->GetNDF());
		text = pt->AddText(result);
		pt->Draw("same");*/
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
