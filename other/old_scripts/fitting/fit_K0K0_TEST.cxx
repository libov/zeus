#include<canvas.cxx>
Double_t bw_interference(Double_t *x,Double_t *par)
{
	//-------------------------------------------------//
	// for function description                        //
	// see "Incl. K0sK0s Resonance Production" paper,  //
	// arXiv:0806.0807                                 //
	//-------------------------------------------------//

	Double_t	M[5],
			G[5];
	Double_t	a=0,
			b=0,
			c=0;

	//Parameters of background function bg()
	c=par[0];    	// c
	//par[1]
	//par[2]

	// Parameters of bw-functions
	M[1]=par[3];	// M1	f2(1270)
	G[1]=par[4];	// G1	f2(1270)
	M[2]=par[5];	// M2	a2(1320)
	G[2]=par[6];	// G2	a2(1320)
	M[3]=par[7];	// M3	f2'(1525)
	G[3]=par[8];	// G3	f2'(1525)
	M[4]=par[9];	// M4	f0(1710)
	G[4]=par[10];	// G4	f0(1710)

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
		temp1=M[i]*M[i]-m*m;
		temp2=M[i]*sqrt(G[i]);
		den[i]=TMath::Power(temp1,2)+TMath::Power((M[i]*G[i]),2);
		ReBW[i]=(temp1*temp2)/den[i];
		ImBW[i]=temp2*M[i]*G[i]/den[i];
	}

	Double_t	ReTensor=0,
			ImTensor=0;
	ReTensor=5*ReBW[1]-3*ReBW[2]+2*ReBW[3];
	ImTensor=5*ImBW[1]-3*ImBW[2]+2*ImBW[3];


	// background
	Double_t	bg=0;
	bg=TMath::Exp(par[1]*(m))*TMath::Power(m,par[2]);

	// Total fit function
	Double_t	total=0;
	//b=0;
	total=a*(ReTensor*ReTensor+ImTensor*ImTensor)+b*(ReBW[4]*ReBW[4]+ImBW[4]*ImBW[4])+c*bg;

	return	total;

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



	/*Double_t 	q=0.5*(x[0]*x[0]-4*0.497672*0.497672);
	Double_t 	exp=TMath::Exp(par[2]*q+par[3]*q*q);
	Double_t	pow=TMath::Power((q/x[0]),par[1]);*/
	//Double_t 	q=x[0]-2*0.497672;
	Double_t 	q=x[0];
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
	//bw2=0;
	/*Double_t 	m4=TMath::Power(par[12],2);
	Double_t	g4=TMath::Power(par[13],2);
	Double_t 	bw4=xx*par[14]/(TMath::Power((xx-m4),2)+g4*xx);*/

	//bw1=0;
	//bw2=0;
	//bw3=0;

	return par[0]*exp*pow+bw1+bw2+bw3;
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
	//Double_t 	q=x[0]-2*0.497672;
	Double_t 	q=x[0];
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


int main()
{
	cout<<TMath::Pi()<<endl;

	// ------ INPUT -------- //
// ------ INPUT -------- //

	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/heraII.root");
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_v2.2.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_SUB.root");
	TH1F *htemp2 = (TH1F*)f1->Get("h3");
	//TH1F *htemp2 = (TH1F*)f1->Get("h_jetAS");
	//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_5");

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

/*
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1,2.7,12);
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
*/

	TF1 *fsum=new TF1("fsum",bw_interference,1.04,2.7,13);
	fsum->SetParName(0,"BG::Constant (c)");
	fsum->SetParName(1,"BG::exp slope");
	fsum->SetParName(2,"BG::Power");
	fsum->SetParName(3,"BW1::peak position");
	fsum->SetParName(4,"BW1::FWHM");
	fsum->SetParName(5,"BW2::peak position");
	fsum->SetParName(6,"BW2::FWHM");
	fsum->SetParName(7,"BW3::peak position");
	fsum->SetParName(8,"BW3::FWHM");
	fsum->SetParName(9,"BW4::peak position");
	fsum->SetParName(10,"BW4::FWHM");
	fsum->SetParName(11,"BW4::constant (a)");
	fsum->SetParName(12,"b");




	// -------------------------------------------------------------//


	TF1 *fbg1=new TF1("fbg1",bg,1.1,2.5,3);
	TF1 *fexp=new TF1("fexp",exp,1.2,2.5,2);
	fexp->SetLineColor(4);
	fbg1->SetLineColor(7);

	//htemp2->Fit("fexp","NQR");
	htemp2->Fit("fexp","NQR");
	fexp->GetParameters(&par[0]);

	par[2]=0.5;
	cout<<par[0]<<" "<<par[1]<<" "<<par[2]<<endl;
	par[0]=par[0]/1.3;
	fbg1->SetParameters(&par[0]);
	//fbg1->SetParameter(3,0.95);
	//fbg1->SetParameter(3,0);

	//fbg1->Draw("same");
	htemp2->Fit("fbg1","NQR+");
	fbg1->GetParameters(&par[0]);
	//par[0]=par[0]/1.05;
	par[0]=par[0]/1.05;
/*
	par[3]=1.511;
	par[4]=0.07;
	par[5]=10;

	par[6]=1.68;
	par[7]=0.25;
	par[8]=70;

	par[9]=1.31;
	par[10]=0.05;
	par[11]=1;
*/

/*
	par[3]=1.511;
	par[4]=0.07;
	par[5]=5;

	par[6]=1.68;
	par[7]=0.25;
	par[8]=20;

	par[9]=1.31;
	par[10]=0.05;
	par[11]=1;
*/


	/*par[3]=1.275;
	par[4]=0.185;

	par[5]=1.318;
	par[6]=0.107;*/

	par[5]=1.275;
	par[6]=0.185;

	par[3]=1.318;
	par[4]=0.107;

	par[7]=1.525;
	par[8]=0.073;

	par[9]=1.724;
	par[10]=0.137;

	par[11]=10;
	par[12]=50;


	fsum->SetParameters(&par[0]);
	fsum->SetLineColor(2);
	//fsum->FixParameter(8,0);

	//fsum->Draw("same");
	htemp2->Fit("fsum","R+");

	fsum->GetParameters(&par[0]);

	TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
	fbg->SetParameters(par[0],par[1],par[2]);
	fbg->SetLineColor(3);
	fbg->Draw("same");

	/*
	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1.05,2.3,3);
	fbw1->SetParameters(par[3],par[4],par[5]);
	fbw1->Draw("same");

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,1.05,2.3,3);
	fbw2->SetParameters(par[6],par[7],par[8]);
	fbw2->Draw("same");

	TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,1.05,2.3,3);
	fbw3->SetParameters(par[9],par[10],par[11]);
	fbw3->Draw("same");

	TF1 *fbw3=new TF1("fbw4",rel_breit_wigner,1.05,2.3,3);
	fbw3->SetParameters(par[9],par[10],par[11]);
	fbw3->Draw("same");


	*/

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

