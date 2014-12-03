Double_t gaus(Double_t *x,Double_t *par)
{
	// left
	// par[0] - sum; par[1] - mean; par[2] - sigma;
	// right
	// par[3] - ratio; par[4] - mean; par[5] - sigma;
	Double_t	gaus1=0;
	Double_t	gaus2=0;

	Double_t	s=par[0];
	Double_t	r=par[3];

	Double_t	fact1=s/((1+r)*par[2]*sqrt(2*TMath::Pi()));
	Double_t	fact2=r*s/((1+r)*par[5]*sqrt(2*TMath::Pi()));

	gaus1=fact1*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gaus2=fact2*TMath::Exp((-0.5)*(x[0]-par[4])*(x[0]-par[4])/(par[5]*par[5]));

	return gaus1+gaus2;
}

Double_t gaus1(Double_t *x,Double_t *par)
{
	Double_t	bin_width=1/30.0;
	// This is gaussian
	// par[0] - area; par[1] - mean; par[2] - sigma;

	Double_t	gaus=0;
	Double_t	fact=par[0]/(par[2]*sqrt(2*TMath::Pi()));
	gaus=fact*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));

	return gaus;
}


int main()
{
	// ----- input -----///
	TFile *finp =new TFile("toy_norm.root");
	TH1F *h = (TH1F*)finp->Get("h");
	Double_t	bin_width=1/30.0;
	h->Draw();


	// ----- factor as parameter ---//

	// left gaus
	cout<<"left gaus"<<endl;
	TF1 *f=new TF1("f",gaus,-1,5,6);

	Double_t	par[6];
	par[0]=5000;
	par[1]=1;
	par[2]=0.5;

	par[3]=0.5;
	par[4]=3;
	par[5]=0.7;
	f->SetParameters(&par[0]);
	//f->Draw("same");
	h->Fit("f","R");

	f->GetParameters(&par[0]);
	Double_t	area=par[0]/((1+par[3])*bin_width),
			arear=par[0]*par[3]/((1+par[3])*bin_width);

	cout<<"Area1= "<<area<<endl;
	cout<<"Area1= "<<arear<<endl;
	//cout<<"Area1 error= "<<area/(par[0]/(f->GetParError(0)))<<endl;
	//cout<<"Arear error= "<<arear/(par[3]/(f->GetParError(3)))<<endl;
	cout<<"Ratio= "<<par[3]<<" +- "<<f->GetParError(3)<<endl;

	return 0;
}
