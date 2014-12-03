#include<canvas.cxx>
Double_t	mK0=0.497648;
Double_t	mf0=0.98;
//Double_t	Gf0=0.05;
Double_t	Gf0=0.1;
Double_t	par[25];

Double_t fit(Double_t *x,Double_t *par)
{
	Double_t			m=x[0];
	Double_t			ph_space=0,
						bw=0;

	ph_space=TMath::Power((1-4*(mK0/m)*(mK0/m)),0.5);
	Double_t	mf0_sq=mf0*mf0;
	bw=par[0]*(mf0_sq*Gf0)/((mf0_sq-m*m)**2+mf0_sq*(Gf0**2));
	Double_t	bg=par[2]*TMath::Power((m-2*mK0),par[1]);

	if (m>2*mK0)
		return (bw*ph_space+bg);
	else
		return 0;
}
void f0980_fit()
{
	CreateCanvas();
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight_substr.root");
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root");


	TH1F *htemp2 = (TH1F*)f1->Get("h2z_0");
	//TH1F *htemp2 = (TH1F*)f1->Get("h2z_0_signal");
	htemp2->Draw();

	TF1 *f=new TF1("f",fit,1.15,1.35,3);
	f->SetLineColor(6);
	//f->SetParameter(0,2000);
	f->SetParameter(0,0);
	f->FixParameter(0,0);
	f->SetParameter(1,0.2);
	f->SetParameter(2,1500);

	htemp2->Fit("f","R");
	f->GetParameters(&par[0]);

	TF1 *fin=new TF1("fin",fit,0.996,1.4,3);
	f->SetLineColor(46);
	par[0]=2000;
	fin->SetParameters(&par[0]);
	htemp2->Fit("fin","R+");
	fin->GetParameters(&par[0]);

	TF1 *fbg=new TF1("b",fit,0.996,1.4,3);
	par[0]=0;
	fbg->SetParameters(&par[0]);
	fbg->SetLineColor(4);
	fbg->Draw("same");

	//TF1 *ff=new TF1("ff",f0,0.7,1.4,1);
	//ff->SetParameter(0,par[0]);
	//ff->Draw("same");
}
