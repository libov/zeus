#include<canvas.cxx>
Double_t gaus(Double_t *x,Double_t *par)
{
	// par[0] - constant;
	// par[1] - mean (mass);
	// par[2] - sigma;
	Double_t	gaus=0;
	gaus=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	//Double_t	mK0=0.497648;
	Double_t	mK0=0.497672;

	if (x[0]>2*mK0)
	{
		//bw=0;
		return gaus;
	}
	else
		return 0;
	//return gaus;
}
// Background + peak (bw times phase space)
Double_t f0_bg(Double_t *x,Double_t *par)
{
	// par[0] - constant;
	// par[1] - mean (mass);
	// par[2] - sigma;
	// par[3] - power
	// par[4] - normalization of bg

	//Double_t	mK0=0.497648;
	Double_t	mK0=0.497672;

	Double_t	gaus=0;
	gaus=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));


	Double_t	pow=par[3];
	Double_t	bg_norm=par[4];
	Double_t	m=x[0];

	//Double_t	bg=par[2]*(TMath::Exp((m-2*mK0)*pow)-1);
	Double_t	bg=bg_norm*(TMath::Power((m-2*mK0),pow));


	if (m>2*mK0)
	{
		//bw=0;
		return (gaus+bg);
	}
	else
		return 0;

}
Double_t bg(Double_t *x,Double_t *par)
{
	//	par[3] - power of exponent
	//	par[4] - normalization of bg

	Double_t	m=x[0];
	Double_t	bgg=0;
	//Double_t	mK0=0.497648;
	Double_t	mK0=0.497672;
	Double_t	pow=0;
	pow=par[3];
	//bgg=par[2]*(TMath::Exp((m-2*mK0)*pow)-1);
	bgg=par[4]*(TMath::Power((m-2*mK0),pow));

	return bgg;
}
int main()
{
	CreateCanvas();
	Double_t	par[5];
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_substr.root");


	TH1F *htemp2 = (TH1F*)f1->Get("h2z_0_signal");
	//TF1 *f=new TF1("f",fit,0.7,1.4,3);
	TF1 *f_bg_est=new TF1("f_bg_est",bg,1.15,1.36,5);
	par[3]=2;
	par[4]=1500;
	f_bg_est->SetParameters(&par[0]);
	f_bg_est->SetLineStyle(2);

 	htemp2->Draw();
	htemp2->Fit("f_bg_est","R");


	f_bg_est->GetParameters(&par[0]);
	par[0]=500;
	par[1]=1.020;
	par[2]=0.05;
	cout<<par[0]<<" "<<par[1]<<" "<<par[2]<<" "<<par[3]<<" "<<par[4]<<endl;

	TF1 *f_fin=new TF1("f_fin",f0_bg,0.99,1.36,5);
	f_fin->SetParameters(&par[0]);

	f_fin->SetLineColor(4);
	//f_fin->Draw("same");
	htemp2->Fit("f_fin","R");



	TF1 *b=new TF1("b",bg,1,1.4,5);
	//b->SetParameters(par[2],par[1]);
	b->SetParameters(&par[0]);
	b->SetLineStyle(2);
	b->SetLineColor(6);
	b->SetLineWidth(2);

	b->Draw("same");

	TF1 *fgaus=new TF1("fgaus",gaus,0.7,1.4,3);
	fgaus->SetParameters(&par[0]);
	fgaus->Draw("same");
	fgaus->SetLineStyle(3);
	fgaus->SetLineColor(3);
	fgaus->SetLineWidth(3);




	return 0;
}

