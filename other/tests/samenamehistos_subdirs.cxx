int samenamehistos_subdirs()
{
		TFile *f1=new TFile("test.root","recreate");
		f1->cd();
		f1->mkdir("bla1");
		f1->mkdir("bla2");

		f1->cd("bla1");

		TH1F	*h1=new TH1F("h1","",10,0,10);
		h1->SetBinContent(3,13);

		f1->cd("bla2");

		TH1F	*h2=new TH1F("h1","",10,0,10);
		h2->SetBinContent(7,13);


		f1->ls();

		f1->Write();
		f1->Close();


	return 0;
}