int AddingHistograms()
{
	TH1F *h1=new TH1F("h1","",10,0,10);
	h1->Fill(1);
	TH1F *h2=new TH1F("h2","",10,0,10);
	h2->Fill(2);

	h1->Add(h2);
	h1->Draw();

	TH1F *h3=new TH1F();
	h3->Add(h1);


	return 0;
}
