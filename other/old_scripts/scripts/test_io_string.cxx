#include <TFile.h>
void read_cuts()
{
		TFile *f1 =new TFile("jovjov.root","recreate");
		string aa="jojov.root";
		char* a="aaaaa.root";
		TFile *f2 =new TFile(aa.data(),"recreate");
		f1->Close();
		//f2.Close();

}