void test_histogram_binning_rule()
{
	TH1F * h=new TH1F("h","",10,0,10);
	h->SetBinContent(0,1);
	h->SetBinContent(1,2);
	h->SetBinContent(3,3);
	h->SetBinContent(10,15);
	h->SetBinContent(11,20);

	h->Sumw2();
	h->SetMarkerStyle(20);

	cout<<h->GetXaxis()->GetBinCenter(0)<<endl;
	cout<<h->GetXaxis()->GetBinCenter(1)<<endl;
	cout<<h->GetXaxis()->GetBinCenter(2)<<endl;
	cout<<h->GetXaxis()->GetBinCenter(10)<<endl;


	h->Draw();

}
