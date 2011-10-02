int keys_in_file_with_subdir()
{
	TFile *f1=new TFile("Histograms4.root","read");
	f1->cd();
	gDirectory->pwd();
	gDirectory->ls();

	TIter next(gDirectory->GetListOfKeys());
	TKey	*key;

	while((key=(TKey*)next()))
	{
		TString SubDirName=key->GetName();
		printf("key: %s points to an object of class: %s at %d\n",SubDirName.Data(),key->GetClassName(),key->GetSeekKey());
		f1->cd(SubDirName);

		gDirectory->pwd();
		//gDirectory->ls();
		cout<<gDirectory->GetListOfKeys()->GetEntries()<<endl;
		TIter next1(gDirectory->GetListOfKeys());
		TKey	*key1;
		while((key1=(TKey*)next1()))
		{
			printf("key: %s points to an object of class: %s at %d\n",key1->GetName(),key1->GetClassName(),key1->GetSeekKey());
		}


	}
	f1->Close();
	return 0;
}