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
	c1->Divide(3,3);

	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/04-07_track_type_test.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/v0psy_testsample.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/v0lite_2K0s_req.root");
	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/v0lite_testsample.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/TEST_Verb_orig.root");
	//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/TEST_Verb_mod.root");
	//TH1F *htemp = (TH1F*)f1->Get("hinv1");
	//TH1F *htemp = (TH1F*)f1->Get("hinv_base");
	//TH1F *htemp = (TH1F*)f1->Get("h");
	//htemp->Draw();

for(int k=5;k<14;k++)
{
	c1->cd(k-4);
	char hist[3];
	Int_t n=sprintf(hist,"h%d",k);
	cout<<hist<<endl;
	TH1F *htemp = (TH1F*)f1->Get(hist);
	//TH1F *htemp = (TH1F*)f1->Get("h07");
	//TH1F *htemp = (TH1F*)f1->Get("h13");
	Float_t	histRangeLow=450,
		histRangeUp=552,
		histRange=histRangeUp-histRangeLow,
		bin_width=histRange/60;
	cout<<bin_width<<endl;
	gStyle->SetOptFit(1111);
	htemp->GetXaxis()->SetTitle("MeV");
	htemp->GetYaxis()->SetTitle("Entries");
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
	//if (k==9) {init_const1=par[0]; init_const2=par[0];}
	init_mass=par[1];
	init_sigma1=par[2]/2;
	init_sigma2=1.1*par[2];  //2*
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
	cout<<bin_width<<endl;
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
	n=sprintf(result,"%5.3f<->%d",K0cand/Signal,(Int_t)K0cand);
	cout<<"waaaaaaa: "<<result<<endl;
	text = pt->AddText(result);
	//pt->Draw();
	pt->Draw("same");

	Int_t yoo=0;
	for(int j=1;j<60;j++) yoo=yoo+htemp->GetBinContent(j);
	cout<<"OK "<<yoo<<endl;

}
	return 0;
}
