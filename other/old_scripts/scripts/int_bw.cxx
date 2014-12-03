Double_t	integral(Double_t m, Double_t G, Double_t constant)
{
	Double_t	a=(m**4)+(m**2)*(G**2);
	Double_t	b=(-2)*(m**2);
	Double_t	c=1.0000;
	
	Double_t	q=(a/c)**(0.2500);
	Double_t	cos_alpha=(-0.5)*b/(sqrt(a*c));
	Double_t	sin_alpha=sqrt(1-cos_alpha**2);
	Double_t	cos_halfalpha=sqrt(0.50*(1+cos_alpha));

	Double_t	pi=TMath::Pi();

	Double_t	integral=(pi*cos_halfalpha)/(2*c*(q**3)*sin_alpha);

	return (constant*integral);
}
Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=par[2]/((x2-m2)*(x2-m2)+m2*g2);
	//Double_t bw=par[2]/((x[0]-par[0])*(x[0]-par[0])+g2/4);
	return bw;
}

int main()
{
	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,100,3);
	fbw1->SetParameters(1,0.05,100);
	fbw1->Draw("l");
	Double_t	int1=fbw1->Integral(0,100);
	Double_t	int2=100*integral(1,0.05);	
	cout<<int1<<" "<<int2<<endl;
	
	return 0;
}
