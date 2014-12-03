#include <canvas.cxx>
int main()
{
	CreateCanvas("compare");
	//c1->Divide(2,2);
	TString		HistogramName="";

	//HistogramName="h_pT_KK";
	HistogramName="h_eta_KK";

	//TFile *f_data =new TFile("/data/zenith226a/libov/scripts/HERAII_basic_test1.root","read");
	//TFile *f_MC =new TFile("/data/zenith226a/libov/scripts/beauty_basic_test1.root","read");


	TFile *f_data =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/HERAII_basic.root","read");
	TFile *f_MC =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/MCdijet_basic.root","read");


	//c1->cd(1);
	TH1F *h_data= (TH1F*)f_data->Get(HistogramName);
	TH1F *h_MC= (TH1F*)f_MC->Get(HistogramName);

	Double_t		content=h_data->GetBinContent(20);
	cout<<content<<endl;
	cout<<sqrt(content)<<endl;
	Double_t		err=h_data->GetBinError(20);
	cout<<err<<endl;
	h_data->Sumw2();
	Double_t		err1=h_data->GetBinError(20);
	cout<<err1<<endl;
	h_data->SetMarkerStyle(20);

		h_MC->Sumw2();
	Double_t	scale_factor=(h_data->Integral())/(h_MC->Integral());

	cout<<"*****"<<endl;

	Double_t		contentMC=h_MC->GetBinContent(20);
	cout<<contentMC<<endl;
	cout<<sqrt(contentMC)<<endl;
	Double_t		err1MC=h_MC->GetBinError(20);
	cout<<err1MC<<endl;

	h_MC->Scale(scale_factor);
	Double_t		contentMCa=h_MC->GetBinContent(20);
	cout<<contentMCa<<endl;
	cout<<sqrt(contentMCa)<<endl;
	Double_t		err1MCa=h_MC->GetBinError(20);
	cout<<err1MCa<<endl;



	h_data->SetMarkerStyle(20);
	h_data->SetStats(0);
	h_MC->SetStats(0);
	h_MC->SetFillColor(5);
	h_MC->Draw();
	h_data->Draw("same");



	leg1 = new TLegend(0.2,0.65,0.3,0.85);
   leg1->AddEntry(h_data,"ZEUS","p");
   leg1->AddEntry(h_MC,"MC (dijet)","f");
 	leg1->SetFillColor(0);
	leg1->Draw("same");
	return 0;
}
