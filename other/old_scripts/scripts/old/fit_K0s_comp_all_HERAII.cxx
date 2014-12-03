/////////////////////
//  F i t t i n g  //
//       o f	   //
//      K 0 s      //
//    invariant    //
//      mass       //
//  distribution   //
/////////////////////
//
// Vladyslav Libov
//      KNU
#include<canvas.cxx>
Double_t as_db_gaus_pol1(Double_t *x,Double_t *par)
{
	// This is double gaussian with one of them assymetric(with 2 different sigma for <mean and >mean regions)
	// Parameters:
	//gaus 1:	par[0] - constant
	//		par[1] - mass
	//		par[2] - sigma
	//gaus 2:	par[3] - constant
	//		par[1] - mass
	//		par[4] - sigma(left)
	//		par[7] - sigma(right)
	//polynom	par[5] - A
	// (A+Bx)	par[6] - B
	Double_t 	gaus1=0,
			gaus2left=0,
			gaus2right=0,
			pol1=0;
	gaus1=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gaus2left=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[4]*par[4]));
	gaus2right=par[3]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[7]*par[7]));
	pol1=par[5]+par[6]*x[0];
	if(x[0]<=par[1]) return gaus1+gaus2left+pol1;
	if(x[0]>par[1]) return gaus1+gaus2right+pol1;
}

Double_t asymmetric_gaus(Double_t *x,Double_t *par)
{
	// This is asymmetric gaussian
	// par[0] - constant; par[1] - mean (mass); par[2] - left sigma; par[3] - right sigma;
	Double_t	gausleft=0,
			gausright=0;

	gausleft=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2]));
	gausright=par[0]*TMath::Exp((-0.5)*(x[0]-par[1])*(x[0]-par[1])/(par[3]*par[3]));
	if (x[0]<=par[1]) return gausleft;
	if (x[0]>par[1]) return gausright;
}
int main()
{



	CreateCanvas();
	Float_t 	bin_width=1.5;
	Float_t		histRangeLow=450,
			histRangeUp=542,
			histRange=histRangeUp-histRangeLow;
	gStyle->SetOptFit(1111);

	//htemp->Draw();

	TF1 *fgaus=new TF1("fgaus","gaus",483,507);
	TF1 *fpol1=new TF1("fpol1","pol1",histRangeLow,histRangeUp);
	Double_t	par[10],
			par2004[10],
			par2005[10],
			par2006[10],
			par2007[10];
	Double_t 	init_const1=0,
			init_const2=0,
			init_sigma1=0,
			init_sigma2=0,
			init_mass=0,
			init_A=0,
			init_B=0;

	TF1 *fsum=new TF1("fsum",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
	fsum->SetParNames("Constant1","Mass","Sigma1","Constant2","LeftSigma2","A","B","Rightsigma2");

	// -----------  2004 ------------------
	cout<<"@@@@@@@@@@@@@@@@ 2004 @@@@@@@@@@@@@@@@@@"<<endl;
	TFile *f1 =new TFile("/data/zenith226a/libov/results/recent/K0s_2004noRTfit.root");
	TH1F *htemp = (TH1F*)f1->Get("hinv_base");
	//in. par
	htemp->Fit("fgaus","NR");
	htemp->Fit("fpol1","NR");
	fgaus->GetParameters(&par[0]);
	fpol1->GetParameters(&par[3]);
	init_const1=par[0];
	init_const2=par[0]/3;
	init_mass=par[1];
	init_sigma1=par[2]/2;
	init_sigma2=2*par[2];
	init_A=par[3];
	init_B=par[4];
	fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
	//fsum->Draw("same");
	htemp->Fit("fsum","NR+");
	fsum->GetParameters(&par[0]);
	fpol1->SetParameters(&par[5]);
	Double_t 	range_low=par[1]-40,
			range_up=par[1]+40;
	fsum->GetParameters(&par2004[0]);
	Double_t norm2004=fsum->Integral(range_low,range_up)/bin_width;
	par2004[0]=par2004[0]/norm2004;
	par2004[3]=par2004[3]/norm2004;
	par2004[5]=par2004[5]/norm2004;
	par2004[6]=par2004[6]/norm2004;
	TF1 *fsum2004=new TF1("fsum2004",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
	fsum2004->SetParameters(&par2004[0]);
	fsum2004->SetLineColor(2);
	fsum2004->Draw("pc");
	f1->Close();
	//---------------------------------------
	// -----------  2005 ------------------
	cout<<"@@@@@@@@@@@@@@@@ 2005 @@@@@@@@@@@@@@@@@@"<<endl;
	TFile *f5 =new TFile("/data/zenith226a/libov/results/recent/K0s_2005noRTfit.root");
	TH1F *htemp5 = (TH1F*)f5->Get("hinv_base");
	//in. par
	htemp5->Fit("fgaus","NR");
	htemp5->Fit("fpol1","NR");
	fgaus->GetParameters(&par[0]);
	fpol1->GetParameters(&par[3]);
	init_const1=par[0];
	init_const2=par[0]/3;
	init_mass=par[1];
	init_sigma1=par[2]/2;
	init_sigma2=2*par[2];
	init_A=par[3];
	init_B=par[4];
	fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
	//fsum->Draw("same");
	htemp5->Fit("fsum","NR+");
	fsum->GetParameters(&par[0]);
	fpol1->SetParameters(&par[5]);
	Double_t 	range_low=par[1]-40,
			range_up=par[1]+40;
	fsum->GetParameters(&par2005[0]);
	Double_t norm2005=fsum->Integral(range_low,range_up)/bin_width;
	par2005[0]=par2005[0]/norm2005;
	par2005[3]=par2005[3]/norm2005;
	par2005[5]=par2005[5]/norm2005;
	par2005[6]=par2005[6]/norm2005;
	TF1 *fsum2005=new TF1("fsum2005",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
	fsum2005->SetParameters(&par2005[0]);
	fsum2005->SetLineColor(3);
	fsum2005->Draw("samepc");
	f5->Close();

	//---------------------------------------

	cout<<"@@@@@@@@@@@@@@@@ 2006 @@@@@@@@@@@@@@@@@@"<<endl;
	TFile *f6 =new TFile("/data/zenith226a/libov/results/recent/K0s_2006fullnoRTfit.root");
	TH1F *htemp6 = (TH1F*)f6->Get("hinv_base");
	//in. par
	htemp6->Fit("fgaus","NR");
	htemp6->Fit("fpol1","NR");
	fgaus->GetParameters(&par[0]);
	fpol1->GetParameters(&par[3]);
	init_const1=par[0];
	init_const2=par[0]/3;
	init_mass=par[1];
	init_sigma1=par[2]/2;
	init_sigma2=2*par[2];
	init_A=par[3];
	init_B=par[4];
	fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
	//fsum->Draw("same");
	htemp6->Fit("fsum","NR+");
	fsum->GetParameters(&par[0]);
	fpol1->SetParameters(&par[5]);
	Double_t 	range_low=par[1]-40,
			range_up=par[1]+40;
	fsum->GetParameters(&par2006[0]);
	Double_t norm2006=fsum->Integral(range_low,range_up)/bin_width;
	par2006[0]=par2006[0]/norm2006;
	par2006[3]=par2006[3]/norm2006;
	par2006[5]=par2006[5]/norm2006;
	par2006[6]=par2006[6]/norm2006;
	TF1 *fsum2006=new TF1("fsum2006",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
	fsum2006->SetParameters(&par2006[0]);
	fsum2006->SetLineColor(4);
	fsum2006->Draw("samepc");
	f6->Close();
	//---------------------------------------

	//---------------------------------------

	cout<<"@@@@@@@@@@@@@@@@ 2007 @@@@@@@@@@@@@@@@@@"<<endl;
	TFile *f7 =new TFile("/data/zenith226a/libov/results/recent/K0s_2007noRTfit.root");
	TH1F *htemp7 = (TH1F*)f7->Get("hinv_base");
	//in. par
	htemp7->Fit("fgaus","NR");
	htemp7->Fit("fpol1","NR");
	fgaus->GetParameters(&par[0]);
	fpol1->GetParameters(&par[3]);
	init_const1=par[0];
	init_const2=par[0]/3;
	init_mass=par[1];
	init_sigma1=par[2]/2;
	init_sigma2=2*par[2];
	init_A=par[3];
	init_B=par[4];
	fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
	//fsum->Draw("same");
	htemp7->Fit("fsum","NR+");
	fsum->GetParameters(&par[0]);
	fpol1->SetParameters(&par[5]);
	Double_t 	range_low=par[1]-40,
			range_up=par[1]+40;
	fsum->GetParameters(&par2007[0]);
	Double_t norm2007=fsum->Integral(range_low,range_up)/bin_width;
	par2007[0]=par2007[0]/norm2007;
	par2007[3]=par2007[3]/norm2007;
	par2007[5]=par2007[5]/norm2007;
	par2007[6]=par2007[6]/norm2007;
	TF1 *fsum2007=new TF1("fsum2007",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
	fsum2007->SetParameters(&par2007[0]);
	fsum2007->SetLineColor(25);
	fsum2007->Draw("samepc");
	f7->Close();
	//---------------------------------------
	return 0;
}
