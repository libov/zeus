int main()
{

TChain *myChain=new TChain("resonance");
myChain->Add("/data/zenith226a/libov/results/K0sK0s_trees/K0sK0s/COMMON_NTUPLES/MCdijetPHPv2/*.root");
	Int_t	nevents=myChain->GetEntries();
	cout<<nevents<<" events here"<<endl;
	return 0;
}
