int nested_subdirs()
{
		TFile *f1=new TFile("test.root","recreate");
		f1->cd();
		f1->mkdir("bla1");
		f1->cd("bla1");
		gDirectory->mkdir("bla2");

		gDirectory->pwd();

		TDirectory *bbb=f1->GetDirectory("bla1/bla2");
		cout<<"now bla"<<endl;
		bbb->pwd();


		TH1F	*h1=new TH1F("h1","",10,0,10);
		h1->SetBinContent(3,13);

		gDirectory->cd("bla2");
		TH1F	*h2=h1->Clone("h2");
		h2->Fill(5);
		h1->GetDirectory()->pwd();
		h2->GetDirectory()->pwd();

		//h1->SetDirectory()

		f1->Write();
		f1->Close();

		return 0;
}