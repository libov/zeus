Double_t bw(Double_t *x,Double_t *par)
{
	Double_t		M=par[0]; 	// peak position
	Double_t		G=par[1]; 	// peak width
	Double_t		m=x[0];		// function variable
	Double_t		ReBW=0,		// Real part of ith peak
					ImBW=0,		// Imaginary part of ith peak
					den=0;		// denominator of ith peak
	Double_t		temp1=0,
					temp2=0;

	temp1=M*M-m*m;
	temp2=M*sqrt(G);
	den=TMath::Power(temp1,2)+TMath::Power((M*G),2);
	ReBW=(temp1*temp2)/den;
	ImBW=(temp2*M*G)/den;

	Double_t	total=0;
	total=par[2]*(ReBW**2+ImBW**2);
	return	total;
}
int bw_test()
{
		TF1 *bw1=new TF1("bw1",bw,0,3,3);
		Double_t		par[50];
		par[0]=1.3;
		par[1]=0.184;
		par[2]=1.;
		bw1->SetParameters(&par[0]);

		cout<<"Area= "<<bw1->Integral(par[0]-3*par[1],par[0]+3*par[1])<<endl;
		bw1->Draw("l");

		return 0;

}