int main()
{
	TChain *myChain=new TChain("h421");
	myChain->Add("/data/zenith226a/libov/anal9600.root");
	Float_t q2,dm;
	myChain->SetBranchAddress("q2",&q2);
	myChain->SetBranchAddress("dm",&dm);
	TH1F *hdm=new TH1F("hdm","",150,0.8,5);
	Int_t nevents=myChain->GetEntries();
	cout<<nevents<<endl;
	for(int i=0;i<nevents;i++)
	{
		myChain->GetEntry(i);
		if (q2<1) continue;
		hdm->Fill(dm);
	}
	hdm->Draw();
	return 0;
}
