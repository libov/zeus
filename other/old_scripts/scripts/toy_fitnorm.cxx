Double_t gaus(Double_t *x,Double_t *par)
{
	// left
	// par[0] - constant; par[1] - mean; par[2] - sigma;
	// right
	// par[3] - constant; par[4] - mean; par[5] - sigma;
	Double_t	gaus1=0;
	Double_t	gaus2=0;

	gaus1=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gaus2=par[3]*TMath::Exp((-0.5)*(x[0]-par[4])*(x[0]-par[4])/(par[5]*par[5]));

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
	par[0]=10;
	par[1]=1;
	par[2]=0.5;

	par[3]=10;
	par[4]=3;
	par[5]=0.7;
	f->SetParameters(&par[0]);
	//f->Draw("same");
	h->Fit("f","R");

	f->GetParameters(&par[0]);
	Double_t	area=par[0]*sqrt(2*TMath::Pi())*par[2]/bin_width,
			arear=par[3]*sqrt(2*TMath::Pi())*par[5]/bin_width;

	cout<<"Area1= "<<area<<endl;
	cout<<"Area1= "<<arear<<endl;
	cout<<"Area1 error= "<<area/(par[0]/(f->GetParError(0)))<<endl;
	cout<<"Arear error= "<<arear/(par[3]/(f->GetParError(3)))<<endl;


	Double_t	ratio=arear/area;

	Double_t	rat_err1=0;
	Double_t	area_err=area/(par[0]/(f->GetParError(0)));
	Double_t	arear_err=arear/(par[3]/(f->GetParError(3)));
	rat_err1=ratio*sqrt( ((1/area)*area_err)**2 +((1/arear)*arear_err)**2);

	cout<<"Ratio= "<<ratio<<" +- "<<rat_err1<<endl;

	gMinuit->mnmatu(1);


/*
	// ----   area as parameter -----//
	TF1 *f1=new TF1("f1",gaus1,-1,3,3);
	f1->SetLineColor(3);
	par[0]=100;
	par[1]=1;
	par[2]=0.5;
	f1->SetParameters(&par[0]);
	//f1->Draw("same");
	h->Fit("f1","R+");

	f1->GetParameters(&par[0]);

	cout<<"Area= "<<par[0]/bin_width<<endl;
	cout<<"Area error= "<<(f1->GetParError(0))/bin_width<<endl;
	//cout<<"par[0]= "<<par[0]<<" +- "<<f1->GetParError(0)<<endl;
	//cout<<"'Significance'= "<<par[0]/(f1->GetParError(0))<<endl;
	//cout<<"Naive area error= "<<area1/(par[0]/(f1->GetParError(0)))<<endl;
*/
	return 0;
}
