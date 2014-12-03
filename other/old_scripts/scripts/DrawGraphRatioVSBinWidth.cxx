int main()
{
/*
	Float_t		bins[10];
	Float_t		bins_error[10];
	Float_t		ratio[10];
	Float_t		ratio_error[10];


	// independent
	bins[0]=15.0;	bins_error[0]=0.0;	ratio[0]=0.85;	ratio_error[0]=0.18;
	bins[1]=21.0;	bins_error[1]=0.0;	ratio[1]=0.90;	ratio_error[1]=0.20;
	bins[2]=28.0;	bins_error[2]=0.0;	ratio[2]=0.68;	ratio_error[2]=0.16;


	TGraphErrors *area=new TGraphErrors(3,bins,ratio,bins_error,ratio_error);
	area->Draw("ap");
*/

	Float_t		z[15];
	z[0]=(0.05+0.1)/2;
	z[1]=(0.1+1)/2;

	Float_t		z_err[15];
	z_err[0]=(0.1-0.05)/2;
	z_err[1]=(1-0.1)/2;

	Float_t		ksi[15];
	ksi[0]=0.45;
	ksi[1]=0.84;

	Float_t		ksi_err[15];
	ksi_err[0]=0.10;
	ksi_err[1]=0.12;


	cout<<z[0]<<" +- "<<z_err[0]<<endl;

	TGraphErrors *area=new TGraphErrors(2,z,ksi,z_err,ksi_err);
	area->Draw("ap");


	return 0;
}
