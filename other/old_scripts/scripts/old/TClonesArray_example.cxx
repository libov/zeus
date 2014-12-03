int main()
{

	TClonesArray a("TH1F",3072);
	int	counter=0;
	for (Int_t bin_th=0;bin_th<48;bin_th++)
	{
		for (Int_t bin_pt=0;bin_pt<64;bin_pt++)
		{
			counter++;
			char 	hist[50];
			Int_t 	n=sprintf(hist,"hinv_K0s_%d_%d",bin_th,bin_pt);
			new(a[counter]) TH1F(hist,"",5000,0,5000);
		}

	}


	//TIter myiter(&a);
	//TH1F *myobject;
	for(int i=1;i<3073;i++)
	{
  		//a.At(i)->Draw();
		//myobject=(TH1F *)a.At(i);
		//myobject->Fill(i*i);
		((TH1F *)a.At(i))->Fill(i);
	}

	TFile *f=new TFile("z.root","recreate");

	for(int i=1;i<3073;i++)
	{
  		//a.At(i)->Draw();
		//myobject=(TH1F *)a.At(i);
		//myobject->Fill(i*i);
		((TH1F *)a.At(i))->Write();
	}


 /*for(int i=1;i<5;i++)
	{
		//myobject=(TH1F *)a.At(i);
		//myobject->Write();
		(TH1F *)a.At(i)->Write();

	}*/
	f->Close();
	/*int i=1;
	while ((myobject = (TH1F *)myiter.Next()))
	{
		myobject->Fill(i);
		i++;
		cout<<i<<endl;
		// process myobject
	}
	cout<<"out"<<endl;
	myiter.Reset();
	while ((myobject = (TH1F *)myiter.Next()))
	{
		myobject->Fill(i);
		i++;
		cout<<i<<endl;
		// process myobject
	}*/




	return 0;
}
