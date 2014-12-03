#include<canvas.cxx>
Int_t	use=0;
//------------------------  MAIN --------------------------//
int main()
{
	// ----------------- INPUT ----------------- //
	CreateCanvas("default");
	TCanvas *c1=gROOT->FindObject("default");
	c1->Divide(2,3);
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root");
TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijetPHPv2.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCbeautyPHP05v1.root");
//TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MEPS.root");



	//TH1F *h1 = (TH1F*)f1->Get("hk0k0_45_280");
	//TH1F *h1 = (TH1F*)f1->Get("hk0k0_2");
	//TH1F *h1 = (TH1F*)f1->Get("h2z_1");
	TH1F *h1 = (TH1F*)f1->Get("h2");
	h1->SetMarkerStyle(20);
	h1->Sumw2();
	h1->SetXTitle("M(K^{0}_{S}K^{0}_{S}, GeV)");
	h1->GetXaxis()->SetTitleSize(0.06);
	h1->GetXaxis()->SetTitleOffset(0.7);
	//h1->SetRangeUser(0.95,3);
	h1->SetTitle("ZEUS");
	h1->Sumw2();
	h1->SetMarkerStyle(20);
	Int_t	nbins=h1->GetNbinsX();
	cout<<nbins<<" bins"<<endl;
	Float_t 	bin_width=0;
	bin_width=(5.0-0.8)/nbins;
	cout<<"bin_width: "<<bin_width<<" GeV"<<endl;
	char Ytitle[25];
	Int_t n=0;
	n=sprintf(Ytitle,"Entries/ %1.3f GeV",bin_width);
	cout<<Ytitle<<endl;
	h1->GetYaxis()->SetTitleOffset(0.7);
	h1->GetYaxis()->SetTitleSize(0.06);
	h1->SetYTitle(Ytitle);
	h1->GetXaxis()->SetRangeUser(0.95,3);

	h1->Clone("h22");
	h1->Clone("h33");
	h1->Clone("h4");
	h1->Clone("h5");
	h1->Clone("h6");
	h1->Clone("h7");



	pt1 = new TPaveText(0.2,0.13,0.35,0.35,"brNDC");
	pt1->SetFillColor(0);
	pt2 = new TPaveText(0.2,0.13,0.35,0.35,"brNDC");
	pt2->SetFillColor(0);
	pt3 = new TPaveText(0.2,0.13,0.35,0.35,"brNDC");
	pt3->SetFillColor(0);
	pt4 = new TPaveText(0.2,0.13,0.35,0.35,"brNDC");
	pt4->SetFillColor(0);
	pt5 = new TPaveText(0.2,0.13,0.35,0.35,"brNDC");
	pt5->SetFillColor(0);
	pt6 = new TPaveText(0.2,0.13,0.35,0.35,"brNDC");
	pt6->SetFillColor(0);
	//text = pt->AddText("Number of Candidates: ");
	pt1->Draw("same");



	Double_t	par[25];
	par[7]=1;

// -------------------------------------------- //
	c1->cd(1);

	h1->Draw();
	TF1 *fwork=new TF1("fwork",work,0.995,2.5,8);

	fwork->SetParName(0,"Total norm");
	fwork->SetParName(6,"Exponent slope");

	for(int k=1;k<6;k++)
	{
		par[k]=0;
		fwork->FixParameter(k,0);
	}

	par[0]=500;
	par[6]=-4.3;
	fwork->SetParameters(&par[0]);
	fwork->SetLineColor(4);
	fwork->FixParameter(10,1);
	//fwork->Draw("same");
	h1->Fit("fwork","NQR+");
	h1->Fit("fwork","R+");
	fwork->GetParameters(&par[0]);
	text = pt1->AddText("n=0");
	pt1->Draw("same");
// -------------------------------------------- //
	c1->cd(2);
	h22->Draw();
	TF1 *fwork_iter2=new TF1("fwork_iter2",work,0.995,2.5,8);
	fwork_iter2->SetParName(0,"Total norm");
	fwork_iter2->SetParName(6,"Exponent slope");
	par[1]=1;
	fwork_iter2->SetParameters(&par[0]);
	fwork_iter2->SetLineColor(5);
	for(int k=2;k<6;k++)
	{
		fwork_iter2->FixParameter(k,0);
	}
	fwork_iter2->FixParameter(10,1);
	h22->Fit("fwork_iter2","R+");
	fwork_iter2->GetParameters(&par[0]);
	text = pt2->AddText("n=1");
	pt2->Draw("same");

// -------------------------------------------- //
	c1->cd(3);
	h33->Draw();
	TF1 *fwork_iter3=new TF1("fwork_iter3",work,0.995,2.5,8);
	fwork_iter3->SetParName(0,"Total norm");
	fwork_iter3->SetParName(6,"Exponent slope");
	par[2]=0.5;
	fwork_iter3->SetParameters(&par[0]);
	fwork_iter3->SetLineColor(6);
	for(int k=3;k<6;k++)
	{
		fwork_iter3->FixParameter(k,0);
	}
fwork_iter3->FixParameter(10,1);
	h33->Fit("fwork_iter3","R+");
	fwork_iter3->GetParameters(&par[0]);
	text = pt3->AddText("n=2");
	pt3->Draw("same");
// -------------------------------------------- //
	c1->cd(4);
	h4->Draw();
	TF1 *fwork_iter4=new TF1("fwork_iter4",work,0.995,2.5,8);
	fwork_iter4->SetParName(0,"Total norm");
	fwork_iter4->SetParName(6,"Exponent slope");
	par[3]=0.5;
	fwork_iter4->SetParameters(&par[0]);
	fwork_iter4->SetLineColor(7);
	for(int k=4;k<6;k++)
	{
		fwork_iter4->FixParameter(k,0);
	}
fwork_iter4->FixParameter(10,1);
	h4->Fit("fwork_iter4","R+");
	fwork_iter4->GetParameters(&par[0]);
	text = pt4->AddText("n=3");
	pt4->Draw("same");
//------------------------------------------------//
	c1->cd(5);
	h5->Draw();
	TF1 *fwork_iter5=new TF1("fwork_iter5",work,0.995,2.5,8);
	fwork_iter5->SetParName(0,"Total norm");
	fwork_iter5->SetParName(6,"Exponent slope");
	par[4]=0.5;
	fwork_iter5->SetParameters(&par[0]);
	fwork_iter5->SetLineColor(8);
	for(int k=5;k<6;k++)
	{
		fwork_iter5->FixParameter(k,0);
	}
fwork_iter5->FixParameter(10,1);
	h5->Fit("fwork_iter5","R+");
	fwork_iter5->GetParameters(&par[0]);
	text = pt5->AddText("n=4");
	pt5->Draw("same");

//-----------------------------------------------//
	c1->cd(6);
	h6->Draw();
	TF1 *fwork_iter6=new TF1("fwork_iter6",work,0.995,2.5,8);
	fwork_iter6->SetParName(0,"Total norm");
	fwork_iter6->SetParName(6,"Exponent slope");
	par[5]=0.5;
	fwork_iter6->SetParameters(&par[0]);
	fwork_iter6->SetLineColor(9);
	for(int k=6;k<6;k++)
	{
		fwork_iter6->FixParameter(k,0);
	}
	fwork_iter6->FixParameter(10,1);
	h6->Fit("fwork_iter6","R+");
	fwork_iter6->GetParameters(&par[0]);
	text = pt6->AddText("n=5");
	pt6->Draw("same");

//-----------------------------------------------//
	/*TCanvas *c2 = new TCanvas("c2", "c2",14,31,700,500);
	c2->SetFillColor(0);
	//TF1 *fsimple=new TF1("fsimple",simple,0.995,2.5,3);
	TF1 *fsimple=new TF1("fsimple",simple,1.036,2.5,3);
	fsimple->SetLineColor(3);
	fsimple->SetParameters(1000,-1,0.5);
	fsimple->Draw("same");
	h7->Fit("fsimple","R+");*/

	return 0;
}
//____________________________________________________________________//

Double_t work(Double_t *x,Double_t *par)
{
	Double_t		mKK=2*0.497672;
	Double_t 	q=x[0]-mKK;
	if (q<0) 	return 0;

	Double_t		q2=q**2;
	Double_t		q3=q**3;
	Double_t		q4=q**4;
	Double_t		q5=q**5;

	Double_t		pol2=par[6]*q;

	Double_t		f1=par[1]*q;
	Double_t		f2=par[2]*q2;
	Double_t		f3=par[3]*q3;
	Double_t		f4=par[4]*q4;
	Double_t		f5=par[5]*q5;

	return (q**(par[7]))*par[0]*(1+f1+f2+f3+f4+f5)*TMath::Exp(pol2);
}
//____________________________________________________________________//
Double_t	I(Double_t slope, Int_t power)
{
	Double_t	mKK=2*0.497672;
	TF1 *ftemp=new TF1("ftemp",part,0,4,2);
	ftemp->SetParameters(slope,power);
	cout<<power<<endl;
	Double_t	I=ftemp->Integral(0,(4-mKK));
	return I;
}
