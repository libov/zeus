#include <canvas.cxx>
int main()
{
	//TCanvas *c1=0;
	CreateCanvas();
	c1->Divide(2,2);

	TFile *f1 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/event_var_MC.root","read");
	//TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/event_var_07pRP.root","read");
	TFile *f2 =new TFile("/data/zenith226a/libov/results/K0sK0s_hist/event_var_07pRP_K0s_not_req.root","read");


	c1->cd(1);
	TH1F *q2elMC= (TH1F*)f1->Get("q2el");
	q2elMC->SetMarkerStyle(20);
	q2elMC->SetStats(0);
	TH1F *q2elD= (TH1F*)f2->Get("q2el");
	q2elD->SetStats(0);
	leg1 = new TLegend(0.55,0.55,0.89,0.89);
    	leg1->AddEntry(q2elMC,"Ariadne","p");
    	leg1->AddEntry(q2elD,"2007pRP","f");
 	leg1->SetHeader("   Q^{2}_{el}   ");
	leg1->SetFillColor(0);
	q2elD->Draw();
	q2elMC->Sumw2();
	Double_t integral=q2elMC->Integral();
	q2elMC->Scale((q2elD->Integral())/integral);
	q2elMC->Draw("same");
	leg1->Draw();

	c1->cd(2);
	TH1F *yjbMC= (TH1F*)f1->Get("yjb");
	yjbMC->SetMarkerStyle(20);
	yjbMC->SetStats(0);
	TH1F *yjbD= (TH1F*)f2->Get("yjb");
	yjbD->SetStats(0);
	leg2 = new TLegend(0.55,0.55,0.89,0.89);
    	leg2->AddEntry(yjbMC,"Ariadne","p");
    	leg2->AddEntry(yjbD,"2007pRP","f");
 	leg2->SetHeader("   y_{jb}   ");
	leg2->SetFillColor(0);
	yjbD->Draw();
	yjbMC->Sumw2();
	integral=yjbMC->Integral();
	yjbMC->Scale((yjbD->Integral())/integral);
	yjbMC->Draw("same");
	leg2->Draw();


	c1->cd(3);
	TH1F *yelMC= (TH1F*)f1->Get("yel");
	yelMC->SetMarkerStyle(20);
	yelMC->SetStats(0);
	TH1F *yelD= (TH1F*)f2->Get("yel");
	yelD->SetStats(0);
	yelD->Draw();
	yelMC->Sumw2();
	integral=yelMC->Integral();
	yelMC->Scale((yelD->Integral())/integral);
	yelMC->Draw("same");
	leg3 = new TLegend(0.55,0.55,0.89,0.89);
	leg3->AddEntry(yelMC,"Ariadne","p");
    	leg3->AddEntry(yelD,"2007pRP","f");
 	leg3->SetHeader("   y_{el}   ");
	leg3->SetFillColor(0);
	leg3->Draw();

	c1->cd(4);
	TH1F *zMC= (TH1F*)f1->Get("z");
	zMC->SetMarkerStyle(20);
	zMC->SetStats(0);
	TH1F *zD= (TH1F*)f2->Get("z");
	zD->SetStats(0);
	zD->Draw();
	zMC->Sumw2();
	integral=zMC->Integral();
	zMC->Scale((zD->Integral())/integral);
	zMC->Draw("same");
	leg4 = new TLegend(0.55,0.55,0.89,0.89);
    	leg4->AddEntry(yelMC,"Ariadne","p");
    	leg4->AddEntry(yelD,"2007pRP","f");
 	leg4->SetHeader("   z_{vtx}   ");
	leg4->SetFillColor(0);
	leg4->Draw();





	return 0;
}
