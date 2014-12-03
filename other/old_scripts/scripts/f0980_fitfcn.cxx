
Double_t			mK0=0.497648;
Double_t			mf0=0.98;
Double_t			Gf0=0.1;
// bw times phase space
Double_t f0(Double_t *x,Double_t *par)
{
	Double_t			m=x[0];
	Double_t			ph_space=0,
						bw=0;


	ph_space=TMath::Power((1-4*(mK0/m)*(mK0/m)),par[1]);
	//ph_space=1;
	Double_t	mf0_sq=mf0*mf0;
	bw=(mf0_sq*Gf0)/((mf0_sq-m*m)**2+mf0_sq*Gf0*Gf0);

	if (m>2*mK0)
		return par[0]*bw*ph_space;
	else
		return 0;

}
//bw
Double_t bw(Double_t *x,Double_t *par)
{
	Double_t	m=x[0];
	Double_t	bw=0;

	Double_t	mf0_sq=mf0*mf0;
	bw=par[0]*(mf0_sq*Gf0)/((mf0_sq-m*m)*(mf0_sq-m*m)+mf0_sq*Gf0*Gf0);
	return bw;
}

void f0980_fitfcn()
{

	TF1 *fbw=new TF1("fbw",bw,0.7,3,1);
	fbw->SetParameter(0,1);
	fbw->Draw("pl");

	TF1 *f1=new TF1("f1",f0,0.7,3,2);
	f1->SetParameter(0,1);
	f1->SetParameter(1,1);
	f1->SetLineColor(2);
	f1->Draw("same");

	/*TF1 *f2=new TF1("f2",f0,0.7,3,2);
	f2->SetParameter(0,1);
	f2->SetParameter(1,0.5);
	f2->SetLineColor(3);
	f2->Draw("same");

	TF1 *f3=new TF1("f3",f0,0.7,3,2);
	f3->SetParameter(0,1);
	f3->SetParameter(1,1.5);
	f3->SetLineColor(4);
	f3->Draw("same");*/

}
