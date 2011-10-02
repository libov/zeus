int histograms()
{
		TH1F		*bla=new TH1F("bla","",10,0,10);
		bla->SetBinContent(3,10000);
		bla->SetFillColor(kYellow);
		bla->Draw();
		bla->Sumw2();

		return 0;
}
