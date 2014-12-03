#include<canvas.cxx>
Double_t rel_breit_wigner_bg(Double_t *x,Double_t *par)
{
	// par[0] -> par[2] BACKGROUND, see function "bg()"

	// 1st Breit-Wigner
	//par[3]=peak position 1320/1270
	//par[4]=FWHM
	//par[5]=constant

	// 2nd Breit-Wigner
	// par[6]=peak position f(1525) meson
	// par[7]=FWHM
	// par[8]=Constant

	//3rd Breit-Wigner
	// par[9]=peak position 1750 meson
	// par[10]=FWHM
	// par[11]=constant

	/*Double_t 	q=0.5*(x[0]*x[0]-4*0.497672*0.497672);
	Double_t 	exp=TMath::Exp(par[2]*q+par[3]*q*q);
	Double_t	pow=TMath::Power((q/x[0]),par[1]);*/
	Double_t 	q=x[0]-2*0.497672;
	Double_t 	exp=TMath::Exp(par[2]*sqrt(q));
	Double_t	pow=TMath::Power(q,par[1]);

	Double_t bw1=x[0]*par[5]/((x[0]*x[0]-par[3]*par[3])*(x[0]*x[0]-par[3]*par[3])+par[4]*par[4]*x[0]*x[0]);
	Double_t bw2=x[0]*par[8]/((x[0]*x[0]-par[6]*par[6])*(x[0]*x[0]-par[6]*par[6])+par[7]*par[7]*x[0]*x[0]);
	Double_t bw3=x[0]*par[11]/((x[0]*x[0]-par[9]*par[9])*(x[0]*x[0]-par[9]*par[9])+par[10]*par[10]*x[0]*x[0]);

	return par[0]*pow*exp+bw1+bw2+bw3;
}

Double_t rel_breit_wigner(Double_t *x,Double_t *par)
{
	// par[0]=peak position
	// par[1]=FWHM
	// par[2]=Constant
	Double_t 	x2=x[0]*x[0],
			m2=par[0]*par[0],
			g2=par[1]*par[1];

	Double_t bw=x[0]*par[2]/((x2-m2)*(x2-m2)+x2*g2);
	return bw;
}

/*Double_t bg(Double_t *x,Double_t *par)
{

	Double_t 	q=0.5*(x[0]*x[0]-4*0.497672*0.497672);
	Double_t 	exp=TMath::Exp(par[2]*q+par[3]*q*q);
	Double_t	pow=TMath::Power((q/x[0]),par[1]);
	return par[0]*pow*exp;
}*/
Double_t bg(Double_t *x,Double_t *par)
{

	Double_t 	q=x[0]-2*0.497672;
	Double_t 	exp=TMath::Exp(par[2]*sqrt(q));
	Double_t	pow=TMath::Power(q,par[1]);
	return par[0]*pow*exp;
}

int main()
{

		gStyle->SetOptFit(1111);
		CreateCanvas();
		Double_t par[15];

		TFile *f1 =new TFile("/data/zenith226a/libov/results/recent/K0sK0sHERAIv2007a_fdr1.root");
		TH1F *htemp2 = (TH1F*)f1->Get("h1");
		TFile *f1 =new TFile("/data/zenith226a/libov/results/recent/K0sK0s_HERAII.root");
		TH1F *htemp = (TH1F*)f1->Get("h");
		//TH1F *htemp2 = (TH1F*)f1->Get("h");
		htemp2->Add(h);


		htemp2->Draw();
		TF1 *fsum=new TF1("fsum",rel_breit_wigner_bg,1.0,2.5,12);
		fsum->SetParName(0,"BG::Constant");
		fsum->SetParName(1,"BG::Power");
		fsum->SetParName(2,"BG::exp slope");
		fsum->SetParName(3,"BW1::peak position");
		fsum->SetParName(4,"BW1::FWHM");
		fsum->SetParName(5,"BW1::constant");
		fsum->SetParName(6,"BW2::peak position");
		fsum->SetParName(7,"BW2::FWHM");
		fsum->SetParName(8,"BW2::constant");
		fsum->SetParName(9,"BW3::peak position");
		fsum->SetParName(10,"BW3::FWHM");
		fsum->SetParName(11,"BW3::constant");

		TF1 *fbg1=new TF1("fbg1",bg,1.05,2.5,3);
		par[0]=90173.9;
		par[1]=1.15683;
		par[2]=-4.4346;
		fbg1->SetParameters(&par[0]);
		htemp2->Fit("fbg1","NQR");
		fbg1->GetParameters(&par[0]);
		/*
		15 MeV/bin
		par[0]=45173.9;
		par[1]=1.15683;
		par[2]=-4.4346;

		par[3]=1.300;
		par[4]=0.07;
		par[5]=0.8/2;
		par[6]=1.525;
		par[7]=0.07;
		par[8]=2/2;
		par[9]=1.71;
		par[10]=0.1;
		par[11]=3/2;*/

		//30 MeV/bin
		//par[0]=90173.9;
		//par[1]=1.15683;
		//par[2]=-4.4346;

		/*par[3]=1.300;
		par[4]=0.07;
		par[5]=0.8;
		par[6]=1.525;
		par[7]=0.07;
		par[8]=2;
		par[9]=1.71;
		par[10]=0.1;
		par[11]=3;*/
		par[0]=par[0]/1.08;

		par[3]=1.307;
		par[4]=0.1;
		par[5]=2.5;

		par[6]=1.517;
		par[7]=0.0789;
		par[8]=2.;


		par[9]=1.688;
		par[10]=0.1215;
		par[11]=2.7;


		fsum->SetParameters(&par[0]);
		//fsum->SetParLimits(0,100000,170000);
		fsum->SetLineColor(2);
		//fsum->Draw("same");
		htemp2->Fit("fsum","R+");

		fsum->GetParameters(&par[0]);

		TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1.05,2.3,3);
		fbw1->SetParameters(par[3],par[4],par[5]);
		fbw1->Draw("same");

		TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,1.05,2.3,3);
		fbw2->SetParameters(par[6],par[7],par[8]);
		fbw2->Draw("same");

		TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,1.05,2.3,3);
		fbw3->SetParameters(par[9],par[10],par[11]);
		fbw3->Draw("same");

		TF1 *fbg=new TF1("fbg",bg,1,2.3,3);
		fbg->SetParameters(par[0],par[1],par[2]);
		fbg->Draw("same");

		/*TF1 *fsum=new TF1("fsum",rel_breit_wigner_exp,1.1,2.5,9);//11);
		fsum->SetParameters(1.525,0.03,1,15000,0.5,1.650,0.5,0.03,3);//1.3,0.5,0.03);

		fsum->SetParNames("Mean1","FWHM1","exp slope","Constant_exp","Constant_bw1","Mean2","Constant_bw2","FWHM2","power");//"Mean3","Constant_bw3","FWHM3");
		fsum->SetLineColor(2);
		//fsum->SetLineWidth(2);
		//fsum->Draw("same");
		htemp2->Fit("fsum","R");
		//fsum->GetParameters(&par[0]);
		//fpol1->SetParameters(&par[5]);
		fsum->GetParameters(&par[0]);
		TF1 *fbw1=new TF1("fbw1",rel_breit_wigner,1,2.3,3);
		fbw1->SetParameters(par[0],par[1],par[4]);
		fbw1->Draw("same");

		TF1 *fbw2=new TF1("fbw2",rel_breit_wigner,1,2.3,3);
		fbw2->SetParameters(par[5],par[7],par[6]);
		fbw2->Draw("same");
		//TF1 *fbw3=new TF1("fbw3",rel_breit_wigner,1,2.3,3);
		//fbw3->SetParameters(par[8],par[10],par[9]);
		//fbw3->Draw("same");*/
		/*Double_t 	area_1525=(fbw1->Integral(1.400,1.626))/0.0286,
				area_1710=(fbw1->Integral(1.500,1.84))/0.0286;
		cout<<area_1525<<" "<<area_1710<<endl;*/



		return 0;
}
