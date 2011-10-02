int	sumw2()
{

		// test errors treatment during histogram scaling
		TH1F		*bla=new TH1F("bla","",10,0,10);

		bla->SetBinContent(3,10000);
		//cout<<"sumw2?: "<<(bla->GetSumw2())<<endl;
		bla->Sumw2();
		bla->Sumw2();
		cout<<"sumw2?: "<<bla->GetSumw2()<<endl;
		cout<<bla->GetBinError(3)<<endl;
		cout<<bla->GetBinError(3)/bla->GetBinContent(3)<<endl;

		bla->Scale(0.01);
		cout<<bla->GetBinError(3)<<endl;
		cout<<bla->GetBinError(3)/bla->GetBinContent(3)<<endl;


		// test errors treatment when histogram adding
/*
		TH1F		*bla1=new TH1F("bla1","",10,0,10);
		TH1F		*bla2=new TH1F("bla2","",10,0,10);

		bla1->SetBinContent(3,10000);
		bla2->SetBinContent(3,10000);

		bla1->Sumw2();
		bla2->Sumw2();

		cout<<bla1->GetBinError(3)<<endl;
		//cout<<bla1->GetBinError(3)/bla1->GetBinContent(3)<<endl;

		cout<<bla2->GetBinError(3)<<endl;
		//cout<<bla2->GetBinError(3)/bla2->GetBinContent(3)<<endl;

		bla1->Add(bla2,-1);
		//bla1->Add(bla2);

		cout<<bla1->GetBinError(3)<<endl;
		//cout<<bla1->GetBinError(3)/bla1->GetBinContent(3)<<endl;
*/
		return 0;
}

