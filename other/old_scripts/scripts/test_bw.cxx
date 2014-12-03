Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=par[2]/((x2-m2)*(x2-m2)+m2*g2);
	return bw;
}


Double_t non_rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];
	Double_t bw=par[2]/((x[0]-par[0])*(x[0]-par[0])+g2/4);
	return bw;
}

Double_t rel_breit_wigner_varG(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	//Double_t	mK0=0.49672;
	//Double_t	mK0=0.001;
	Double_t	mK0=par[3];
	Double_t	mK02=mK0*mK0;
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];
	//cout<<0.25*x2-mK02<<endl;
	if ((0.25*x2-mK02)<0) return 0;
	Double_t	G=par[1]*sqrt(0.25*x2-mK02);
	//Double_t	G=par[1];

	Double_t bw=par[2]*G/((x2-m2)*(x2-m2)+m2*G*G);
	return bw;
}


int main()

{
	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner_varG,9,11,4);
	fbw1->SetParameters(10,0.05,1,0);
	fbw1->SetLineStyle(3);

	TF1 *fbw2=new TF1("fbw2",rel_breit_wigner_varG,9,11,4);
	fbw2->SetParameters(10,0.05,1,5.1);
	fbw2->SetLineColor(3);
	fbw2->Draw();


	Double_t	int1=fbw1->Integral(9,11);
	Double_t	int2=fbw2->Integral(9,11);

	//Double_t	ratio=int2/int1;

	//fbw1->SetParameters(10,0.05,ratio);
	fbw1->Draw("same");

	cout<<"before: "<<int1<<" "<<int2<<endl;

	int1=fbw1->Integral(9,11);
	int2=fbw2->Integral(9,11);
	cout<<"after: "<<int1<<" "<<int2<<endl;

	/*
	TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,0,2,3);
	fbw1->SetParameters(1,0.05,1);
	//

	TF1 *fbw2=new TF1("fbw2",non_rel_breit_wigner,0,2,3);
	fbw2->SetParameters(1,0.05,1);
	fbw2->SetLineColor(3);
	fbw2->Draw();

	Double_t	int1=fbw1->Integral(0,2);
	Double_t	int2=fbw2->Integral(0,2);

	Double_t	ratio=int2/int1;

	fbw1->SetParameters(1,0.05,ratio);
	fbw1->Draw("same");

	cout<<int1<<" "<<int2<<endl;
	*/


	return 0;
}
