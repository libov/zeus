int hist_diff_files_part2()
{
	TFile *f1=new TFile("part1.root","update");
	cout<<gDirectory->pwd()<<endl;
	cout<<gDirectory->ls()<<endl;
	TFile *f2=new TFile("part2.root","recreate");
	cout<<gDirectory->pwd()<<endl;
	cout<<gDirectory->ls()<<endl;

	TIter next(f1->GetListOfKeys());
	cout<<gDirectory->pwd()<<endl;
	cout<<gDirectory->ls()<<endl;

	TKey	*key;
	cout<<"loop"<<endl;
	while((key=(TKey*)next()))
	{
		cout<<"aaaaaaaaaaaaaaaaa"<<endl;
		cout<<gDirectory->pwd()<<endl;
		cout<<gDirectory->ls()<<endl;

		printf("key: %s points to an object of class: %s at %d\n",key->GetName(),key->GetClassName(),key->GetSeekKey());

		cout<<gDirectory->pwd()<<endl;
		cout<<gDirectory->ls()<<endl;
		f1->cd();
		TH1F*	h2=(TH1F*)f1->Get(key->GetName());
		TH1F	*cHist=(TH1F*)f1->Get(key->GetName())->Clone("bla");
		//h2->Draw();
		cout<<gDirectory->pwd()<<endl;
		cout<<gDirectory->ls()<<endl;



		f1->cd();
		cout<<gDirectory->pwd()<<endl;
		cout<<gDirectory->ls()<<endl;

		f1->Write();
		f2->Write();

	}
	f1->Close();
	f2->Close();

	return 0;
}