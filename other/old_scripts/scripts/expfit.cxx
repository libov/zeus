#include<canvas.cxx>
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

int main()

{
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/heraII.root");
	TH1F *htemp2 = (TH1F*)f1->Get("h3");
	TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_1");

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
	//-------------------------------------------------------------//


	TF1 *exp=new TF1("exp",bg,1.6,2.7,3);
	exp->SetParameter(0,1);
	exp->SetParameter(1,1);
	exp->SetParameter(2,1);
	htemp2->Fit("exp","R");

	return 0;
}