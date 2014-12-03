int main()
{
	TChain *myChain=new TChain("resonance");
	myChain->Add("/data/zenith226a/libov/myOrange/job003/run/*.root");
	int n;
	myChain->SetBranchAddress("n",&n);
	int nevents=myChain->GetEntries();
	cout<<nevents<<" here"<<endl;
	for (int i=0; i<nevents;i++)
	{
		cout<<n<<"  ";
	}
	return 0;
}