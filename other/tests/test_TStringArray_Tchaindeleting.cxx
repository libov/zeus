int main()
{
	TString a[6];
	a[0]="0th element;";
	a[1]="1st element;";
	a[2]="2nd element;";
	cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;

	a[5]="sxsxsx:xsxsxs";
	if (a[5].Contains("sx")) cout<<"ok"<<endl;
	if (a[5].Contains("")) cout<<"oh..."<<endl;

	//a={"s","s","s","s","s","s"};
	//Double_t		bla[3]={1,2,3};
	//cout<<bla[0]<<" "<<bla[1]<<" "<<bla[2]<<" "<<endl;
	//bla={1,2,3};

	TChain *bla=new TChain("orange");
	TString PathNtuples="/data/zenith226a/libov/F2CC/ntuples/";
	TString PathNtuplesData=PathNtuples+"data/";

	bla->Add(PathNtuplesData+"07p_0.root");
	cout<<bla->GetEntries()<<endl;
	bla->Add(PathNtuplesData+"07p_1.root");
	cout<<bla->GetEntries()<<endl;
	bla->Add(PathNtuplesData+"07p_1.root");

	bla->Reset();
	//delete bla;
	cout<<bla->GetEntries()<<endl;

	bla->Add(PathNtuplesData+"07p_5.root");
	cout<<bla->GetEntries()<<endl;

	return 0;
}
