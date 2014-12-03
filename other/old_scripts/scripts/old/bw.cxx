Double_t breit_wigner_exp(Double_t *x,Double_t *par)
{
	// 1st Breit-Wigner
	// par[0]=peak position f(1525) meson
	// par[1]=HWHM
	// par[4]=Constant
	// 2st Breit-Wigner
	// par[5]=peak position 1750 meson
	// par[7]=HWHM
	//par[6]=constant

	// exponential C*exp(-Ax)
	//par[2]=A
	//par[3]=C
	Double_t exp=par[3]*TMath::Exp((-1)*par[2]*x[0]);
	Double_t bw1=par[4]*(par[1]/TMath::Pi())/((x[0]-par[0])*(x[0]-par[0])+par[1]*par[1]);
	Double_t bw2=par[6]*(par[7]/TMath::Pi())/((x[0]-par[5])*(x[0]-par[5])+par[7]*par[7]);

	return exp+bw1+bw2;

}

Double_t breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=HWHM
	// par[2]=Constant

	Double_t bw=par[2]*(par[1]/TMath::Pi())/((x[0]-par[0])*(x[0]-par[0])+par[1]*par[1]);


	return bw;

}

Double_t exp(Double_t *x,Double_t *par)
{
	// par[0]=slope
	// par[1]=constant
	return par[1]*TMath::Exp((-1)*par[0]*x[0]);
}
int main()
{
		TFile *f1 =new TFile("DoubleK0s.root");
		TH1F *htemp = (TH1F*)f1->Get("hdouble1");
		//rebinning
		TH1F *htemp2=new TH1F("htemp2","K0sK0s  0.48<M(K0s)<0.512   28.6 Mev/bin",150,0.8,5);
		for(int j=1;j<150;j++) htemp2->SetBinContent(j,(htemp->GetBinContent(2*j)+htemp->GetBinContent(2*j-1)));
		htemp2->Draw();
		gStyle->SetOptFit(1111);
		TF1 *fsum=new TF1("fsum",breit_wigner_exp,1.2,1.9,8);
		fsum->SetParameters(1.525,0.03,1,2000,5,1.750,5,0.03);
		//fsum->SetParameters(1.525,30,1,100,100);
		fsum->SetParNames("Mean1","HWHM1","exp slope","Constant_exp","Constant_bw1","Mean2","Constant_bw2","HWHM2");
		fsum->SetLineColor(2);
		fsum->SetLineWidth(2);
		//fsum->Draw("same");
		htemp2->Fit("fsum","R+");
		//fsum->GetParameters(&par[0]);
		//fpol1->SetParameters(&par[5]);
		Double_t par[10];
		fsum->GetParameters(&par[0]);
		TF1 *fbw1=new TF1("fbw1",breit_wigner,1.2,1.9,3);
		fbw1->SetParameters(par[0],par[1],par[4]);
		fbw1->Draw("same");

		TF1 *fbw2=new TF1("fbw2",breit_wigner,1.2,1.9,3);
		fbw2->SetParameters(par[5],par[7],par[6]);
		fbw2->Draw("same");

		TF1 *fexp=new TF1("fexp",exp,1.2,1.9,2);
		fexp->SetParameters(par[2],par[3]);
		fexp->SetLineColor(7);
		fexp->SetLineStyle(7);
		fexp->Draw("same");

		Double_t 	area_1525=(fbw1->Integral(1.400,1.626))/0.026,
				area_1710=(fbw1->Integral(1.500,1.84))/0.026;
		cout<<area_1525<<" "<<area_1710<<endl;

	return 0;
}
