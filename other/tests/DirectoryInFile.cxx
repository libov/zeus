int DirectoryInFile()
{
		//--------------------------------------------//
		// user's guide:  chapter 11, "Input/Output"; //
		// section "Subdirectories and navigation"    //
		//--------------------------------------------//

		cout<<"Hi, this is DirectoryInFile.cxx"<<endl;
		TH1F h1("h1","",10,0,10);
		TH1F h2("h2","",20,0,20);
		TH1F h3("h3","",30,0,30);

		TFile *f = new TFile("DirectoryInFile.root","recreate");
		f->mkdir("1");
		f->mkdir("2");
		f->mkdir("3");
		f->ls();

		f->cd("1");
		h1.Write();
		f->cd("2");
		h2.Write();
		f->cd("3");
		h3.Write();
		f->ls();

		f->Close();

		// checking ls() command
		TFile *f = new TFile("DirectoryInFile.root","read");
		//f->FindObject("1")->ls();
		if (f->cd("3")) cout<<"ok"<<endl;
		f->Close();

		TFile *f = new TFile("DirectoryInFile.root","read");
		TH1F *h=(TH1F*)f->Get("1/h1");

		TFile *f1 = new TFile("DirectoryInFile1.root","recreate");
		f1->cd();
		h->Write();
		f1->Close();
		f->Close();

		//--
		cout<<"check read type"<<endl;
		char		bla[256];  sprintf(bla,"%i",1);
		TString	bb="1";
		TFile *f = new TFile("DirectoryInFile.root","read");
		cout<<f->cd(bb)<<endl;
		cout<<f->cd(bla)<<endl;
		cout<<f->cd("1")<<endl;


		return 0;
}
