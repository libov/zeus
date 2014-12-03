#include<canvas.cxx>
/////////////////////
//  F i t t i n g  //
//       o f	   //
//      K 0 s      //
//    invariant    //
//      mass       //
//  distribution   //
/////////////////////
//
// Vladyslav Libov(KNU)
//
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
	//return gaus1+pol1;
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
	//c1->Divide(2,2);

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/split_years/0000993142/HERAII_05test.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/split_years/0000993143/HERAII_06ptest.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/split_years/0000993144/HERAII_04pGR1test.root");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/split_years/0000993145/HERAII_04pGR1test.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/split_years/0000993146/HERAII_04pGR1test.root");

//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_cuts.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_tight3.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/scripts/0001047831/HERAII_basic_1.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/V0lite_master.root");
TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic_1.root");

//TFile *f1 =new TFile("/data/zenith226a/libov/master/MC_k0_true.root");


	//TH1F *htemp = (TH1F*)f1->Get("hinv_K0s_all");
	TH1F *htemp = (TH1F*)f1->Get("h_k0inv_total");
	//TH1F *htemp = (TH1F*)f1->Get("hK0_mass");
	//TH1F *htemp = (TH1F*)f1->Get("hK0_07p");
	//TH1F *htemp = (TH1F*)f1->Get("h_k0sinv_matched_reco");

	// these values come from K0s_analysis_K0K0_comb.cxx
	Float_t		histRangeLow=450,
					histRangeUp=552,
					histRange=histRangeUp-histRangeLow,
					bin_width=histRange/60;
	cout<<"Bin width= "<<bin_width<<endl;
	gStyle->SetOptFit(1111);
	htemp->GetXaxis()->SetTitle("M(#pi^{+}#pi^{-}), MeV");
	htemp->SetTitle("N(K^{0}_{S})>=2");
	char Ytitle[25];
	Int_t nn=sprintf(Ytitle,"Combinations/ %2.1f MeV",bin_width);
	cout<<Ytitle<<endl;
	htemp->SetYTitle(Ytitle);
	htemp->Draw();

	TF1 *fgaus=new TF1("fgaus","gaus",483,507);
	fgaus->SetLineWidth(2);
	TF1 *fpol1=new TF1("fpol1","pol1",histRangeLow,histRangeUp);
	fpol1->SetLineWidth(2);
	Double_t par[10];
	htemp->Fit("fgaus","NR");
	htemp->Fit("fpol1","NR");
	Double_t 	init_const1=0,
			init_const2=0,
			init_sigma1=0,
			init_sigma2=0,
			init_mass=0,
			init_A=0,
			init_B=0;
	fgaus->GetParameters(&par[0]);
	fpol1->GetParameters(&par[3]);
	init_const1=par[0]/2; //1
	init_const2=par[0]/6; //3
	init_mass=par[1];
	init_sigma1=par[2]/2;
	init_sigma2=1.1*par[2];
	init_A=par[3];
	init_B=par[4];
	TF1 *fsum=new TF1("fsum",as_db_gaus_pol1,histRangeLow,histRangeUp,8);
	fsum->SetParameters(init_const1,init_mass,init_sigma1,init_const2,init_sigma2,init_A,init_B,init_sigma2*1.2);
	fsum->SetParNames("Constant1","Mass","Sigma1","Constant2","LeftSigma2","A","B","Rightsigma2");
	fsum->SetLineColor(2);
	fsum->SetLineWidth(2);

	//fsum->Draw("same");
	htemp->Fit("fsum","R+");
	fsum->GetParameters(&par[0]);
	fpol1->SetParameters(&par[5]);
	Double_t 	range_low=par[1]-25,
			range_up=par[1]+25;
	Double_t	Signal=0,
			Background=0,
			K0cand=0;

	Signal=fsum->Integral(range_low,range_up)/bin_width;
	Background=fpol1->Integral(range_low,range_up)/bin_width;
	K0cand=Signal-Background;
	cout<<K0cand/Signal<<" <--> "<<K0cand<<endl;
	TF1 *fgaus1=new TF1("fgaus1","gaus",histRangeLow,histRangeUp);
	TF1 *fgaus2=new TF1("fgaus2",asymmetric_gaus,histRangeLow,histRangeUp,4);
	fgaus1->SetLineWidth(2);
	fgaus2->SetLineWidth(2);
	fgaus1->SetParameters(par[0],par[1],par[2]);
	fgaus2->SetParameters(par[3],par[1],par[4],par[7]);
	fgaus1->Draw("same");
	fgaus2->Draw("same");
	TF1 *fline=new TF1("fline","pol1",histRangeLow,histRangeUp);
	fline->SetParameters(par[5],par[6]);
	fline->SetLineColor(7);
	fline->SetLineStyle(7);
	fline->Draw("same");

	pt = new TPaveText(0.15,0.6,0.4,0.85,"brNDC");
   pt->SetFillColor(0);
	char result[25];
	Int_t 	n=sprintf(result,"%5.3f<->%d",K0cand/Signal,(Int_t)K0cand);
	text = pt->AddText(result);
	pt->Draw("same");


	pt1 = new TPaveText(507.737,1205931,545.9468,1884594,"br");
   pt1->SetFillColor(19);
   text = pt1->AddText("Mean: 496.3 MeV");
	text = pt1->AddText("#sigma_{1}=4.3 MeV");
   text = pt1->AddText("#sigma_{2}=10.8 MeV");
   text = pt1->AddText("K^{0}_{S} in peak: 1.5*10^{7}");
   pt1->Draw("same");


   pt = new TPaveText(459.997,2151760,538.8534,2369792,"br");
   pt->SetLineColor(0);
   text = pt->AddText("ZEUS");
   pt->Draw();


	return 0;
}
