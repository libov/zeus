// obsolete
// see lumi.py
int calc_lumi() {
	//____________________________//

	//Int_t			run_lower_limit=60005;
	//Int_t			run_upper_limit=61746;

	Int_t			run_lower_limit=61747;
	Int_t			run_upper_limit=62636;
	//ifstream 	myfile("06p07p.lumi",ios::in);
	//ifstream 	myfile("06p07p.MVD.lumi",ios::in);
	ifstream 	myfile("06p07p.MVD.STT.lumi",ios::in);
	//____________________________//
	Int_t			run,
					nevents;
	Float_t		pcal,
					spec;
	Int_t			last_gflt;
	string		trigger;
	Float_t		lumi_pcal=0;
	Float_t		lumi_spec=0;

	while (!myfile.eof())
	{
		myfile>>run>>nevents>>pcal>>spec>>last_gflt>>trigger;

	//cout<<run<<" "<<nevents<<" "<<pcal<<" "<<spec<<" "<<last_gflt<<" "<<trigger<<endl;

		if (!((run>=run_lower_limit)&&(run<=run_upper_limit))) continue;
		lumi_pcal=lumi_pcal+pcal;
		lumi_spec=lumi_spec+spec;
	}
	//cout<<"***************************"<<endl;
	cout<<lumi_pcal<<endl;
	//cout<<lumi_spec<<endl;
	//cout<<"***************************"<<endl;

	return 0;
}
