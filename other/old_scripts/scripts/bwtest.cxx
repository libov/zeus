#include<canvas.cxx>
#include<TMath.h>
Double_t rel_breit_wigner_bg(Double_t *x,Double_t *par)
{
	Double_t 	xx=TMath::Power(x[0],2);

	Double_t 	m1=TMath::Power(par[0],2);
	Double_t	g1=TMath::Power(par[1],2);
	Double_t 	bw1=par[2]/(TMath::Power((xx-m1),2)+g1*m1);


	return bw1;
}

int main()
{
	TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,80,120,3);

	fsum->SetParName(0,"BW1::peak position");
	fsum->SetParName(1,"BW1::FWHM");
	fsum->SetParName(2,"BW1::constant");

	Double_t	par[3];

	par[0]=100;
	par[1]=1;
	par[2]=100;


	fsum->SetParameters(&par[0]);
	Double_t 	area=fsum->Integral(-1000,1000);
	fsum->Draw("pl");

	cout<<"integral= "<<area<<endl;

	return 0;
}
