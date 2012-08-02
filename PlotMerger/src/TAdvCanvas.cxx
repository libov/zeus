//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  September 2009                              //
//                                              //
//////////////////////////////////////////////////
#include <inc/TAdvCanvas.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TString.h>

#include <iostream>
using namespace std;

TAdvCanvas::TAdvCanvas()
{
}

TAdvCanvas::TAdvCanvas(Int_t NPads_X,Int_t NPads_Y,TString CanvName, TString colonVariables, unsigned *LogPads, Int_t width, Int_t height):
fNPads_X(NPads_X),
fNPads_Y(NPads_Y),
fCanvName(CanvName),
fcolonVariables(colonVariables),
fWidth(width),
fHeight(height)
{
    SeparateVariables();
    unsigned npads = fNPads_X*fNPads_Y;
    fLogPads = new unsigned [npads+1];
    for (int k=0; k<npads; k++) {
        fLogPads[k+1]=LogPads[k];
    }
}

TAdvCanvas::~TAdvCanvas() {
    // clean up
    delete [] fLogPads;
}

Int_t TAdvCanvas::GetNPads() {
    return fNPads_X*fNPads_Y;
}

void		TAdvCanvas::SeparateVariables()
{
		TString			tempVar;
		fNumberOfVariables=0;
		while (fcolonVariables.Contains(":"))
		{
			tempVar="";
			Int_t		colonPos=fcolonVariables.Index(":",1,0,TString::kExact);
			for (int k=0;k<colonPos;k++)
			{
				tempVar=tempVar+fcolonVariables[k];
			}
			fArrayOfVariables[fNumberOfVariables]=tempVar;
			fNumberOfVariables++;

			fcolonVariables.Remove(0,colonPos+1);
		}
}
Int_t		TAdvCanvas::GetNumberOfVariables()
{
	return fNumberOfVariables;
}
TString	TAdvCanvas::GetVariable(Int_t	VarNum)
{
	return fArrayOfVariables[VarNum];
}

Bool_t TAdvCanvas::LogPad(Int_t Pad) {
    if (fLogPads[Pad]==1) return true;
    if (fLogPads[Pad]==0) return false;
}

TCanvas* TAdvCanvas::CreateCanvas() {

    TCanvas *fCanvas = new TCanvas(fCanvName, "Control Plots", fWidth, fHeight);

    fCanvas->Range(0.275,-234.806,5.525,2113.26);
    fCanvas->SetBorderSize(2);
    fCanvas->SetFrameFillColor(0);
    fCanvas->SetFillColor(0);
    fCanvas->ToggleToolBar();
    fCanvas->ToggleEventStatus();
    fCanvas->ToggleEditor();
    fCanvas->Divide(fNPads_X,fNPads_Y);

    // resize the pads to allow some space on top - for the ZEUS logo
    Float_t top_margin = 0.1;
    Float_t pad_size_y = (1-top_margin)/fNPads_Y;
    for (int i=1; i<= fNPads_X*fNPads_Y; i++) {
        // get the row number
        div_t divresult;
        divresult = div (i-1, fNPads_X);
        unsigned row = divresult.quot + 1;

        // get the pad
        TString index;
        index += i;
        TPad * pad = (TPad*)fCanvas -> GetPrimitive(fCanvName+"_"+index);

        // get pad coordinates
        Double_t x1, x2, y1, y2;
        pad -> GetPadPar(x1, y1, x2, y2);

        // modify y-coordinates
        y1 = 1 - top_margin - row * pad_size_y;
        y2 = 1 - top_margin - (row-1) * pad_size_y;

        // set them
        pad -> SetPad(x1, y1, x2, y2);
    }

    return fCanvas;
}

TString TAdvCanvas::GetName() {
    return fCanvName;
}
