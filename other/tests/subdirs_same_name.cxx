int subdirs_same_name()
{

	TFile *f1=new TFile("test.root","recreate");
	f1->cd();
	f1->mkdir("bla1");
	f1->mkdir("bla2");

	f1->cd("bla1");
	gDirectory->pwd();
	gDirectory->mkdir("sub");

	f1->cd("bla2");
	gDirectory->pwd();
	gDirectory->mkdir("sub");
	gDirectory->mkdir("sub");

	f1->Write();
	f1->Close();


	return 0;
}