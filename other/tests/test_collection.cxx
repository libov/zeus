#include <canvas.cxx>
#include <TList.h>
int test_collection()
{
		CreateCanvas("canv1");
		TCanvas *canv1=gROOT->FindObject("canv1");
		canv1->Divide(3,2);

		CreateCanvas("canv2");
		TCanvas *canv2=gROOT->FindObject("canv2");
		canv2->Divide(3,2);

		CreateCanvas("canv3");
		TCanvas *canv3=gROOT->FindObject("canv3");
		canv3->Divide(3,2);

		CreateCanvas("canv4");
		TCanvas *canv4=gROOT->FindObject("canv4");
		canv4->Divide(3,2);

		TList *fCanvases=new TList();
		fCanvases->AddFirst(canv1);
		fCanvases->Add(canv2);
		fCanvases->Add(canv3);
		fCanvases->Add(canv4);

		//fCanvases->Dump();

		TIter	myIterator(fCanvases);
		


		return 0;
}