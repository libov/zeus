//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                                 //
//  libov@mail.desy.de                          //
//  July 2009                                   //
//                                              //
//////////////////////////////////////////////////

#include <inc/TPlotType.h>
#include<iostream>
using namespace std;

TPlotType::TPlotType()
{
}

TPlotType::TPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Float_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth, Int_t LineStyle):
fName(Name),
fDrawHisto(DrawHisto),
fMarkerStyle(MarkerStyle),
fMarkerSize(MarkerSize),
fFillColor(FillColor),
fLineColor(LineColor),
fLineWidth(LineWidth),
fLineStyle(LineStyle)
{
}

TPlotType::~TPlotType()
{
}

TString		TPlotType::GetName()
{
		return fName;
}
Int_t		TPlotType::GetMarkerStyle()
{
		return fMarkerStyle;
}

Float_t		TPlotType::GetMarkerSize()
{
		return fMarkerSize;
}

Int_t		TPlotType::GetFillColor()
{
		return fFillColor;
}

Int_t		TPlotType::GetLineColor()
{
		return fLineColor;
}
Int_t		TPlotType::GetLineWidth()
{
		return fLineWidth;
}

Int_t		TPlotType::GetLineStyle()
{
		return fLineStyle;
}


Bool_t		TPlotType::IsDrawHisto()
{
		return fDrawHisto;
}








