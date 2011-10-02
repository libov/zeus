int TList()
{
		TList			*HistToFill=new TList();
		TH1F *h1=new TH1F("h1","",10,0,10);
		HistToFill->Add(h1);
		HistToFill->Add(new TH1F("h2","",20,0,20));
		HistToFill->ls();

	/*
		//HistToFill->FindObject("h1")->Draw();
		((TH1F*)HistToFill->FindObject("h1"))->Fill(5);
		TH1F *h3=HistToFill->FindObject("h1");
		TH1F *h4=(TH1F*)HistToFill->FindObject("h2");

		//h3->Draw();
		//h3->Draw();
	*/

		TH1F				*currentTH1F;
		TIter				Iter(HistToFill);

		while (currentTH1F=(TH1F *)Iter.Next())
		{
			cout<<"bla"<<endl;
		}

		cout<<"second loop"<<endl;
		TIter				Iter2(HistToFill);
		while (currentTH1F=(TH1F *)Iter2.Next())
		{
			cout<<"bla"<<endl;
		}



		return 0;
}
