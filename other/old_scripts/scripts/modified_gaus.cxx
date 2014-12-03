#include <canvas.cxx>
Double_t gaus_modified(Double_t *x,Double_t *par)
{

	Double_t 	q=x[0];
	Double_t	norm=par[0];
	Double_t	mu=par[1];
	Double_t	a=(q-mu);
	Double_t	sigma=par[2];


	Double_t 	exp_mod=TMath::Exp((-1)*a*a/(2*sigma**2+par[3]*a));
	Double_t 	exp=TMath::Exp((-1)*a*a/(2*sigma**2));

	if ((q>mu)||(q==mu))
		return norm*exp_mod;
	if (q<mu)
		return norm*exp;
}
int main()
{
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_cuts.root");
	TH1F *htemp2 = (TH1F*)f1->Get("h2");
		// --------------  I N I T I A L I Z A T I O N ----------------------//
	gStyle->SetOptFit(0000);
	CreateCanvas();
	Double_t par[25];
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

	TF1 *fsum=new TF1("fsum",gaus_modified,1.06,2.7,4);
	Double_t	par[20];
	par[0]=8000;
	par[1]=1.2;
	par[2]=0.6;
	par[3]=1;
	fsum->SetParameters(&par[0]);

	//sfsum->Draw("lsame");

	htemp2->Fit("fsum","R+");
	//Double_t	xx=2;
	//cout<<gaus_modified(&xx,par)<<endl;

	return 0;
}