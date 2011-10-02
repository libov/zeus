int tobjarray_initialization()
{
	//TObjArray	HistogramsToWrite(0);
	TObjArray	HistogramsToWrite;
	TH1F		*bla=new TH1F("bla","",10,0,10);
	bla->SetBinContent(3,10000);

	HistogramsToWrite.Add(bla);
	TFile out("tobjarray_initialization.root","recreate");
	HistogramsToWrite.Write();
	out.Close();

	return 0;
}