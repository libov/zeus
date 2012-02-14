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

TAdvCanvas::TAdvCanvas()
{
}

TAdvCanvas::TAdvCanvas(Int_t NPads_X,Int_t NPads_Y,TString CanvName, TString colonVariables, Int_t	LogPads[6]):
fNPads_X(NPads_X),
fNPads_Y(NPads_Y),
fCanvName(CanvName),
fcolonVariables(colonVariables),
fWidth(1200),
fHeight(800)
{
    this->SeparateVariables();
    for (int k=0; k<fNPads_X*fNPads_Y; k++) {
        fLogPads[k+1]=LogPads[k];
    }
}

TAdvCanvas::~TAdvCanvas() {
}

Int_t		TAdvCanvas::GetNPads()
{
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
Bool_t		TAdvCanvas::LogPad(Int_t	Pad)
{
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

    return fCanvas;
}

TString TAdvCanvas::GetName() {
    return fCanvName;
}
