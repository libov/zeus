int sprintf_test()
{
	Int_t			temp=0;
	char 			name[256];

	Int_t		batch_num=2;
	Int_t		file_num=5;
	string   la="07pGR_%d_%d.root";
	string 	ququ=la+"blabla";

	temp=sprintf(name,ququ.data(),batch_num,file_num);

	cout<<name<<endl;
	return 0;
}