int string_test()
{
		TString bla("bla1:bla2:blabla:bla4:yo:");
		cout<<bla<<endl;
		TString var;

		TString  ku[10];
		Int_t		j=0;
		while (bla.Contains(":"))
		{
			var="";
			Int_t		colonPos=bla.Index(":",1,0);
			for (int k=0;k<colonPos;k++)
			{
				var=var+bla[k];
			}
			bla.Remove(0,colonPos+1);
			cout<<var<<endl;
			ku[j]=var;
			j++;

		}

		for (int k=0;k<10;k++)
		{
			cout<<ku[k]<<endl;
		}
		cout<<j<<endl;
		TString		kuku[j+10];
		for (int k=1;k<(j+5);k++)
		{
			kuku[k]=kuku[k-1]+"yo";
			//kuku[k]=kuku[k-1]+"yo"<<endl;
			cout<<kuku[k]<<endl;
		}
		//cout<<bla<<endl;

		return 0;
}