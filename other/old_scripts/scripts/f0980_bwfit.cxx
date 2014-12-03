#include<canvas.cxx>
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
Double_t bg(Double_t *x,Double_t *par)
{//	par[0] - normalization of the signal
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
	//mf0=0.980;

	// background
	Double_t	pow=par[3];
	//Double_t	bg=par[2]*(TMath::Exp((m-2*mK0)*pow)-1);
	Double_t	bg=par[4]*(TMath::Power((m-2*mK0),pow));

	if (m>2*mK0)
	{
		return (bg);
	}
	else
		return 0;

}

int main()
{
	CreateCanvas();
	Double_t	par[5];


//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_v2.6.root");
//TH1F *htemp2 = (TH1F*)f1->Get("h3");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/plots/05e06p07p.root");
//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_5");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/plots/05e06p07p_280.root");
//TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_5_280");

TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/05e_COMMNTUP_MC_v2.2.root");
//TH1F *htemp2 = (TH1F*)f1->Get("h3");
TH1F *htemp2 = (TH1F*)f1->Get("hk0k0_5");



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
	htemp2->GetXaxis()->SetRangeUser(0.95,2);

	TF1 *f_bg_est=new TF1("f_bg_est",bg,1.15,1.36,5);
	par[3]=2;
	par[4]=1500;
	f_bg_est->SetParameters(&par[0]);
	f_bg_est->SetLineStyle(2);

 	htemp2->Draw();

	htemp2->Fit("f_bg_est","NR");
	f_bg_est->GetParameters(&par[0]);
	par[0]=200;
	par[1]=1.03;
	par[2]=0.05;
	TF1 *f_fin=new TF1("f_fin",f0_bg,0.993,1.36,5);
	f_fin->SetParameters(&par[0]);
	f_fin->SetParNames("Signal const","mass","width","BG::power","BG::const");
	f_fin->SetLineColor(4);

	//f_fin->FixParameter(1,0.98);
	//f_fin->FixParameter(2,0.05);
	//f_fin->FixParameter(3,par[3]);
	//f_fin->FixParameter(4,par[4]);


	//f_fin->Draw("same");
	htemp2->Fit("f_fin","R");


	f_fin->GetParameters(&par[0]);
	TF1 *b=new TF1("b",bg,1,1.4,5);
	b->SetParameters(&par[0]);
	b->SetLineStyle(2);
	b->SetLineColor(6);
	b->SetLineWidth(2);
	b->Draw("same");

	TF1 *ff=new TF1("ff",f0,0.7,1.4,3);
	cout<<par[0]<<endl;
	ff->SetParameters(&par[0]);
	//b->SetLineStyle(3);
	ff->SetLineColor(3);
	ff->SetLineWidth(3);
	ff->Draw("same");




	return 0;
}

