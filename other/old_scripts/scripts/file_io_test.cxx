int file_io_test()
{
	ifstream 	myfile("test.file",ios::in);
	string 		variable;
	string 		value;

	int			index=0;
	Double_t		bla=0;

	while (!myfile.eof())
	{
		index=0;
		bla=0;
		myfile>>index>>bla;
		cout<<index<<" "<<bla<<endl;
	}
	return 0;
}