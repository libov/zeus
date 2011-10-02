int canvas_test()
{
	gROOT->SetBatch();
	TCanvas *fCanvas = new TCanvas("bla", "Control Plots",14,31,700,500);

	//fCanvas->SetBatch(kTRUE);
	gStyle->SetOptFit(1111);
   fCanvas->Range(0.275,-234.806,5.525,2113.26);
   fCanvas->SetBorderSize(2);
	fCanvas->SetFrameFillColor(0);
	fCanvas->SetFillColor(0);
   fCanvas->ToggleToolBar();
	fCanvas->ToggleEventStatus();
	fCanvas->ToggleEditor();
	fCanvas->Divide(2,2);

	return 0;
}