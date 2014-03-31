#ifndef __TMULTICANVAS_H__
#define __TMULTICANVAS_H__

// ROOT headers
#include <TROOT.h>
#include <TCanvas.h>
#include <TPad.h>

// custom headers
#include <TCharmMeasurement.h>

class TMultiCanvas {

    public:

        TMultiCanvas(unsigned npads);
        TMultiCanvas();
        ~TMultiCanvas(){};

        void Print(TString filename);
        void PlotData(TCharmMeasurement data, Float_t shift, int marker_style, Float_t marker_size, int color, bool draw_total_uncertainty, bool draw_legend);

    private:

        void create_pads();
        void draw_dummy_histos();
        void draw_axes();
        void draw_labels();

        Int_t get_pad_number(Double_t q2);

        TCanvas * fCanvas;
        TPad * fPads[10];

        unsigned fNPads;

        Float_t fMarginX;
        Float_t fMarginY;
        Float_t fPadSizeY;
        Float_t fPadSizeX;

        Float_t fXmin;
        Float_t fXmax;

        Float_t fYmin;
        Float_t fYmaxBeauty;
        Float_t fYmaxBeautyUpperRow;
        Float_t fYmaxCharm;

        Float_t fRightMargin;

        TString fYAxisTitle;

        Bool_t fBeauty;

        TLegend * fLegend;

};

#endif
