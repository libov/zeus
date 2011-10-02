// shows that objects created on heap are visible
// even outside the scope of the function which
// created them (in contrast to objects created on steak)

int		visibility()
{
		{
			int a=9;
			cout<<a<<endl;
		}
		cout<<a<<endl;
		histo();
		TH1F *bl=gROOT->FindObject("h1");
		bl->Fill(8);




		return 0;
}

void	histo()
{
		/*TH1F	hist("h","",10,0,10);
		hist.Fill(3);
		hist.Draw();*/

		TH1F *hist1=new TH1F("h1","",20,0,20);
		hist1->Fill(5);
		hist1->Draw();

		TH1F *hist2=hist1->Clone("h1_clone");
		hist2->Fill(10);

		hist2->Draw();
}