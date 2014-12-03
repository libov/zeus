#include<canvas.cxx>
int draw_z_dependence()
{
		Double_t			z[10];
		Double_t			z_err[10];

		Double_t			r[10];
		Double_t			r_err[10];

		z_err[0]=(0.07-0)/2.;
		z[0]=0+z_err[0];

		z_err[1]=(0.1-0.07)/2.;
		z[1]=0.07+z_err[1];

		z_err[2]=(0.15-0.1)/2.;
		z[2]=0.1+z_err[2];

		z_err[3]=(1.-0.15)/2.;
		z[3]=0.15+z_err[3];

		r[0]=0;
		r_err[0]=0;

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
		r[1]=0.327;
		r_err[1]=0.124;

		r[2]=0.938;
		r_err[2]=0.233;

		r[3]=0.761;
		r_err[3]=0.160;
		

		TGraphErrors *zplot=new TGraphErrors(4,z,r,z_err,r_err);
		zplot->Draw("pa");
		return 0;
}
