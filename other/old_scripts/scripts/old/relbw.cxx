Double_t rel_breit_wigner_exp(Double_t *x,Double_t *par)
{
	// 1st Breit-Wigner
	// par[0]=peak position f(1525) meson
	// par[1]=FWHM
	// par[4]=Constant
	// 2st Breit-Wigner
	// par[5]=peak position 1750 meson
	// par[7]=FWHM
	//par[6]=constant
	//3rd bw
	//par[8]=peak position 1320/1270
	//par[9]=constant
	//par[10]=FWHM
	// exponential C*exp(-Ax)
	//par[2]=A
	//par[3]=C
	Double_t exp=TMath::Power((x[0]-1),par[8])*par[3]*TMath::Exp((-1)*par[2]*x[0]*x[0]);
	Double_t bw1=x[0]*x[0]*par[4]/((x[0]*x[0]-par[0]*par[0])*(x[0]*x[0]-par[0]*par[0])+par[1]*par[1]*x[0]*x[0]);
	Double_t bw2=x[0]*x[0]*par[6]/((x[0]*x[0]-par[5]*par[5])*(x[0]*x[0]-par[5]*par[5])+par[7]*par[7]*x[0]*x[0]);
	//Double_t bw3=x[0]*x[0]*par[9]/((x[0]*x[0]-par[8]*par[8])*(x[0]*x[0]-par[8]*par[8])+par[10]*par[10]*x[0]*x[0]);

	return exp+bw1+bw2;

}

Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=HWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=x2*par[2]/((x2-m2)*(x2-m2)+x2*g2);
	return bw;
}
Double_t rel_breit_wigner_bg(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=HWHM
	// par[2]=Constant
	//par[3]=slo
	//par[4]=con
	//par[5]=pow
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=x2*par[2]/((x2-m2)*(x2-m2)+x2*g2);
	Double_t exp=TMath::Power((x[0]-1),par[5])*par[4]*TMath::Exp((-1)*par[3]*x[0]*x[0]);
	return bw+exp;
}


Double_t exp(Double_t *x,Double_t *par)
{
	// par[0]=slope
	// par[1]=constant
	return TMath::Power((x[0]-1),par[2])*par[1]*TMath::Exp((-1)*par[0]*x[0]*x[0]);
}
int main()
{
		TFile *f1=new TFile("/data/zenith226a/libov/results/recent/K0sK0s_HERAII.root");

		TH1F *htemp2 = (TH1F*)f1->Get("h");
		htemp2->Draw();
		gStyle->SetOptFit(1111);
		Double_t par[15];
		/*TF1 *fsum=new TF1("fsum",rel_breit_wigner_exp,1.1,2.5,9);//11);
		fsum->SetParameters(1.525,0.03,1,15000,0.5,1.650,0.5,0.03,3);//1.3,0.5,0.03);

		fsum->SetParNames("Mean1","FWHM1","exp slope","Constant_exp","Constant_bw1","Mean2","Constant_bw2","FWHM2","power");//"Mean3","Constant_bw3","FWHM3");
		fsum->SetLineColor(2);
		//fsum->SetLineWidth(2);
		//fsum->Draw("same");
		htemp2->Fit("fsum","R");
		//fsum->GetParameters(&par[0]);
		//fpol1->SetParameters(&par[5]);
		fsum->GetParameters(&par[0]);
		TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1,2.3,3);
		fbw1->SetParameters(par[0],par[1],par[4]);
		fbw1->Draw("same");

		TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,1,2.3,3);
		fbw2->SetParameters(par[5],par[7],par[6]);
		fbw2->Draw("same");
		//TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,1,2.3,3);
		//fbw3->SetParameters(par[8],par[10],par[9]);
		//fbw3->Draw("same");*/

		par[2]=1;
		par[3]=5000;
		par[8]=3;
		TF1 *fexp=new TF1("fexp",exp,1.1,2,3);
		fexp->SetParameters(par[2],par[3],par[8]);
		fexp->SetLineColor(7);
		fexp->SetLineStyle(7);
		//fexp->Draw("same");
		htemp2->Fit("fexp","R");
		fexp->GetParameters(&par[0]);

		TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.1,2,6);
		fsum->SetParameters(1.3,0.03,0.1,par[0],par[1],par[2]);
		fsum->Draw("same");
		//htemp2->Fit("fsum","R");
		fsum->GetParameters(&par[0]);

		TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1,2.3,3);
		fbw1->SetParameters(par[0],par[1],par[2]);
		fbw1->Draw("same");
		/*Double_t 	area_1525=(fbw1->Integral(1.400,1.626))/0.0286,
				area_1710=(fbw1->Integral(1.500,1.84))/0.0286;
		cout<<area_1525<<" "<<area_1710<<endl;*/



		return 0;
}
