#include<canvas.cxx>
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
	Double_t 	q=x[0]-2*0.497672;
	Double_t 	exp=TMath::Exp(par[1]*(q));
	Double_t	pow=TMath::Power(q,par[2]); //polinom*exp
	//Double_t 	pow=1.0000;  // simple exp
	Double_t 	xx=TMath::Power(x[0],2);

	Double_t 	m1=TMath::Power(par[3],2);
	Double_t	g1=TMath::Power(par[4],2);
	Double_t 	bw1=xx*par[5]/(TMath::Power((xx-m1),2)+g1*m1);

	Double_t 	m2=TMath::Power(par[6],2);
	Double_t	g2=TMath::Power(par[7],2);
	Double_t 	bw2=xx*par[8]/(TMath::Power((xx-m2),2)+g2*m2);

	Double_t 	m3=TMath::Power(par[9],2);
	Double_t	g3=TMath::Power(par[10],2);
	Double_t 	bw3=xx*par[11]/(TMath::Power((xx-m3),2)+g3*m3);

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

	Double_t bw=x2*par[2]/((x2-m2)*(x2-m2)+m2*g2);
	return bw;
}

Double_t bg(Double_t *x,Double_t *par)
{
	// Background function: polinom at K0sK0s threshold, fall-off exponent far from the threshold
	// par[0] - constant
	// par[1] - slope
	Double_t 	q=x[0]-2*0.497672;
	Double_t 	exp=TMath::Exp(par[1]*q);
	Double_t	pow=TMath::Power(q,par[2]); // exp*pol
	//pow=1.00000; //simple exp
	return par[0]*pow*exp;
}

Double_t exp(Double_t *x,Double_t *par)
{
	// Simple background function: fall-off exponent
	// par[0] - constant
	// par[1] - polinom power
	// par[2] - exponent slope

	Double_t 	q=x[0]-2*0.497672;
	Double_t 	exp=TMath::Exp(par[1]*(q));
	return par[0]*exp;
}


int main()
{


		gStyle->SetOptFit(1111);
		CreateCanvas();
		Double_t par[15];

		TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/04-07_track_type_test.root");
		TH1F *htemp2 = (TH1F*)f1->Get("h");
		htemp2->Sumw2();
		//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/K0K0_HERAI.root");
		//TH1F *htemp1 = (TH1F*)f1->Get("h1");
		//htemp1->Sumw2();
		//htemp2->Add(htemp1);
		htemp2->SetMarkerStyle(20);
		htemp2->GetYaxis()->SetTitleOffset(1.3);

		Int_t nbins=htemp2->GetNbinsX();
		cout<<nbins<<" bins"<<endl;
		Float_t 	bin_width=0;
		bin_width=(5000.0-800)/nbins;
		cout<<"bin_width: "<<bin_width<<" MeV"<<endl;;
		char Ytitle[25];
		Int_t n=0;
		n=sprintf(Ytitle,"Combinations/ %2.0f MeV",bin_width);
		cout<<Ytitle<<endl;
		htemp2->SetYTitle(Ytitle);
		htemp2->SetXTitle("M(K^{0}_{S}K^{0}_{S}), GeV");
		htemp2->GetXaxis()->SetRangeUser(1.1,3);
		htemp2->Draw();

		TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.05,2.3,12);
		//TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1,2.3,15);
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


		TF1 *fbg1=new TF1("fbg1",bg,1.05,2.3,3);
		//par[0]=100000;
		par[0]=3650;
		//par[1]=-4;
		par[2]=0.3; // in case of simple background
		par[1]=-1.5;
		fbg1->SetParameters(&par[0]);
		htemp2->Fit("fbg1","QNR");
		fbg1->GetParameters(&par[0]);

		par[0]=par[0]/1.05;

		par[3]=1.500;
		par[4]=0.07;
		par[5]=1.5;

		par[6]=1.7;
		par[7]=0.2;
		par[8]=10;

		par[9]=1.31;
		par[10]=0.05;
		par[11]=1;

		/*par[12]=1.27;
		par[13]=0.05;
		par[14]=0.5;*/

		fsum->SetParameters(&par[0]);
		//fsum->SetParLimits(0,100000,170000);

		//try to fix parameters values according to results from photoproduction
		fsum->SetParameter(3,1.523);
		fsum->FixParameter(3,1.523);
		fsum->FixParameter(4,0.076);
		fsum->FixParameter(6,1.695);
		fsum->FixParameter(7,0.105);
		fsum->FixParameter(9,1.304);
		fsum->FixParameter(10,0.061);


		fsum->SetLineColor(2);
		//fsum->Draw("same");
		htemp2->Fit("fsum","R+");

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

		TF1 *fbg=new TF1("fbg",bg,1.05,2.3,3);
		fbg->SetParameters(par[0],par[1],par[2]);
		fbg->SetLineColor(3);
		fbg->Draw("same");

		Double_t 	mass_1525=par[3],
				FWHM_1525=par[4],
				mass_1710=par[6],
				FWHM_1710=par[7];
		cout<<mass_1525<<" "<<FWHM_1525<<" "<<mass_1710<<" "<<FWHM_1710<<endl;
		Double_t 	area_1525=1000*(fbw1->Integral(mass_1525-3*FWHM_1525,mass_1525+3*FWHM_1525))/bin_width,
				area_1710=1000*(fbw2->Integral(mass_1710-3*FWHM_1710,mass_1710+3*FWHM_1710))/bin_width;
		Double_t	bg_1525=1000*(fbg->Integral(mass_1525-3*FWHM_1525,mass_1525+3*FWHM_1525))/bin_width,
				bg_1710=1000*(fbg->Integral(mass_1710-3*FWHM_1710,mass_1710+3*FWHM_1710))/bin_width;
		cout<<"1525: "<<area_1525<<" events; "<<"S/B: "<<area_1525/bg_1525<<endl;
		cout<<"1710: "<<area_1710<<" events; "<<"S/B: "<<area_1710/bg_1710<<endl;
		cout<<"!!!  N_1525/N_1710= "<<area_1525/area_1710<<endl;



		pt = new TPaveText(0.25,0.6,0.55,0.85,"brNDC");
   		pt->SetFillColor(0);
		char result[25];
		text = pt->AddText("Number of Candidates: ");
		n=sprintf(result,"f'_{2}(1525): %d",(Int_t)area_1525);
		text = pt->AddText(result);
		n=sprintf(result,"f_{0}(1710): %d",(Int_t)area_1710);
		text = pt->AddText(result);
		pt->Draw("same");

		return 0;
}
