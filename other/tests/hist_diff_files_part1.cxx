int hist_diff_files_part1()
{
	TFile *f1=new TFile("part1.root","recreate");
	TH1F*	h1=new TH1F("h1","",10,0,10);
	h1->SetBinContent(5,3);
	h1->Write();
	f1->Close();

	return 0;
}