Double_t	integral(Double_t m, Double_t G)
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

	return integral;
}
Double_t		bw(Double_t *x,Double_t *par)
{
	Double_t		x2=x[0]**2;
	Double_t 	m3=TMath::Power(par[0],2);
	Double_t		g3=TMath::Power(par[1],2);
	Double_t		c3=integral(par[0],par[1]);
	Double_t 	bw3=1/(c3*(TMath::Power((x2-m3),2)+g3*m3));

	return par[2]*bw3;
}
int TestBwFunction()
{

	TF1 *fbw=new TF1("fbw",bw,1,2,3);
	Double_t		par[10];
	par[0]=1.5;
	par[1]=0.08;
	par[2]=1000;

	fbw->SetParameters(&par[0]);
	fbw->Draw("al");

	cout<<"AREA= "<<par[2]<<endl;

	Double_t	integral_bw=fbw->Integral(par[0]-10*par[1],par[0]+10*par[1]);
	cout<<"Integral= "<<integral_bw<<endl;



	return 0;
}