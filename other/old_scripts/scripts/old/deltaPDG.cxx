#include<canvas.cxx>
int main(int style=7)
{
	//int style=7;
	Double_t 	year[10],
			year_error[10],
			mass[10],
			mass_error[10],
			mass_corr[10],
			mass__corr_error[10];
	year[0]=2004;
	year[1]=2005;
	year[2]=2006;
	year[3]=2007;
	for(int i=0;i<10;i++) year_error[i]=0;
	mass[0]=495.86-497.672;
	mass[1]=495.07-497.672;
	mass[2]=495.27-497.672;
	mass[3]=495.67-497.672;
	mass_error[0]=0.02;
	mass_error[1]=0.012;
	mass_error[2]=0.016;
	mass_error[3]=0.015;


	mass_corr[0]=497.45-497.672;
	mass_corr[1]=497.91-497.672;
	mass_corr[2]=497.71-497.672;
	mass_corr[3]=497.73-497.672;


	CreateCanvas();
	/*TGraph *gr1 = new TGraphErrors (4, year,mass,year_error,mass_error);
	gr1->SetMarkerStyle(style);
	gr1->SetTitle("K0s mass shift");
	gr1->GetYaxis()->SetTitle("MeV");
	gr1->GetXaxis()->SetTitle("Year");
	//gr1->GetYaxis()->SetRangeUser(-2.8,0.5);
	gr1->GetXaxis()->SetRangeUser(2000.,2010.);
	gr1->Draw("Ap");*/

	TGraph *gr2 = new TGraphErrors (4, year,mass_corr,year_error,mass_error);
	gr2->SetMarkerStyle(style);
	gr2->SetTitle("K0s mass shift after correction");
	gr2->GetYaxis()->SetTitle("MeV");
	gr2->GetXaxis()->SetTitle("Year");
	gr2->GetYaxis()->SetRangeUser(-0.5,0.5);
	gr2->GetXaxis()->SetRangeUser(2000.,2010.);
	gr2->Draw("pa");

	return 0;
}
