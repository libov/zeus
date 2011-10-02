#include<Plotting/canvas.cxx>
int draw_z_dependence()
{
		CreateCanvas();
		Double_t			z[10];
		Double_t			z_err[10];

		Double_t			r[10];
		Double_t			r_err[10];

		/*
		// bin1, bin2
		z_err[0]=(0.0005-0.0001)/2.;
		z[0]=(0.0001+0.0005)/2.;
		z_err[1]=(0.001-0.0005)/2.;
		z[1]=(0.001+0.0005)/2.;
		r[0]=2.26;
		r_err[0]=0.24;
		r[1]=3.43;
		r_err[1]=0.58;*/

		// bin3 bin4
		/*z_err[0]=(0.001-0.0005)/2.;
		z[0]=(0.0005+0.001)/2.;

		z_err[1]=(0.004-0.001)/2.;
		z[1]=(0.004+0.001)/2.;

		r[0]=2.28;
		r_err[0]=0.26;
		r[1]=1.87;
		r_err[1]=0.21;*/

		// bin5 bin6
/*		z_err[0]=(0.01-0.001)/2.;
		z[0]=(0.01+0.001)/2.;

		z_err[1]=(0.04-0.01)/2.;
		z[1]=(0.04+0.01)/2.;

		r[0]=1.65;
		r_err[0]=0.17;
		r[1]=2.63;
		r_err[1]=1.06;
*/

		z_err[0]=(0.02-0.004)/2.;
		z[0]=(0.02+0.004)/2.;

		r[0]=1.14;
		r_err[0]=0.18;



		/*
		// new unsubstr
		r[1]=0.445;
		r_err[1]=0.167;

		r[2]=0.677;
		r_err[2]=0.174;

		r[3]=0.692;
		r_err[3]=0.154;
		*/

		/*
		// new substr
		r[1]=0.440;
		r_err[1]=0.147;

		r[2]=0.700;
		r_err[2]=0.164;

		r[3]=0.649;
		r_err[3]=0.137;
		*/



		// old unsubstr
		/*r[1]=0.327;
		r_err[1]=0.124;

		r[2]=0.938;
		r_err[2]=0.233;

		r[3]=0.761;
		r_err[3]=0.160;*/


		//TGraphErrors *zplot=new TGraphErrors(4,z,r,z_err,r_err);
		//TGraphErrors *zplot=new TGraphErrors(2,z,r,z_err,r_err);
		TGraphErrors *zplot=new TGraphErrors(1,z,r,z_err,r_err);
		zplot->SetTitle("k_{b}");
		zplot->SetMarkerStyle(20);
		zplot->Draw("pa");
		//zplot->GetXaxis()->SetRangeUser(0.00005,0.05);
		zplot->GetXaxis()->SetTitle("x_{Bjorken}");

		 TPaveText *pt = new TPaveText(0.15,0.6,0.5,0.85,"brNDC");
   pt->SetFillColor(19);
   pt->SetFillStyle(0);
   pt->SetLineColor(0);
   //TText *text = pt->AddText("Q^{2}#in [5,20] GeV^{2}");
	//TText *text = pt->AddText("Q^{2}#in [80,200] GeV^{2}");
	TText *text = pt->AddText("Q^{2}#in [200, 1000] GeV^{2}");
   pt->Draw("same");

   pt = new TPaveText(6.390307e-05,4.254486,0.0001068718,4.489495,"br");
   pt->SetLineColor(0);
   text = pt->AddText("k_{b}");
   //pt->Draw("same");
		return 0;
}
