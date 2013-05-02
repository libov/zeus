//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                                 //
//  libov@mail.desy.de                          //
//  July 2009                                   //
//                                              //
//////////////////////////////////////////////////
#ifndef __TPlotType_H__
#define __TPlotType_H__
#include <TROOT.h>

class	TPlotType : public TObject
{
	public:
		TPlotType();
		TPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Float_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth, Int_t LineStyle);
		~TPlotType();

		TString		GetName();
		Int_t			GetMarkerStyle();
		Float_t		GetMarkerSize();
		Int_t			GetFillColor();
		Int_t			GetLineColor();
		Int_t			GetLineWidth();
		Int_t			GetLineStyle();
		Bool_t		IsDrawHisto();

	private:
		// this is indeed reinventing the wheel; one could inherit this from some root class
		// that already has these variables
		TString		fName;			// the same as in merged.j.root, change to smth more automatic
		Int_t			fMarkerStyle;
		Float_t		fMarkerSize;
		Bool_t		fDrawHisto;
		Int_t			fFillColor;
		Int_t			fLineColor;
		Int_t			fLineWidth;
                Int_t                   fLineStyle;

};
#endif
