#include <TCanvas.h>
void CreateCanvas(char * canvas_name="Default Canvas")
{
	TCanvas *c1 = new TCanvas(canvas_name, "Fit",14,31,700,500);
   gStyle->SetOptFit(1111);
   c1->Range(0.275,-234.806,5.525,2113.26);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
	c1->SetFillColor(0);
   c1->ToggleToolBar();
	c1->ToggleEventStatus();
	c1->ToggleEditor();
}
