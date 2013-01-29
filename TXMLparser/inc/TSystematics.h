#ifndef __TSYSTEMATICS_H__
#define __TSYSTEMATICS_H__

#define MAXPOINTS 100

#include <TString.h>
#include <TGraphErrors.h>

#include <map>

enum flavour {
  kCharm,
  kBeauty
};

class TSystematics {

    public:
        TSystematics();
        ~TSystematics() {};

        void        Initialize();               //!< is called after all the settings were done

        void        Draw();                     //!< main function; draws the scan result as a function of a scan variable for a single bin
        void        DrawAll();                  //!< draws the scan result as a function of a scan variable for all bins
        void        DrawVector(map<unsigned, Float_t>, map<unsigned, Float_t>, TString); //!< draws the systematic uncertainty for all bins
        void        GetResult(unsigned point, Float_t & result, Float_t & result_err);
        void        PrintAll();
        void        PrintDifferential(unsigned, unsigned, flavour, TString);

        // setters
        void        SetNpoints(int  npoints) {fNpoints = npoints;};
        void        SetXArray(double * x_arr);
        void        SetXerrorArray(double * x_err_arr);
        void        SetVersionArray(TString * version_arr);
        void        SetXAxisTitle(TString   ax_title) {fXAxisTitle = ax_title;};
        void        SetYaxisLowLimit (Float_t   limit) {fYaxisLowLimit = limit;};
        void        SetYaxisUpLimit (Float_t   limit) {fYaxisUpLimit = limit;};
        void        SetDefault(Float_t  def) {fDefault = def;};
        void        SetVariation(Float_t  var) {fUpVariation = var; fDownVariation = var;};
        void        SetUpVariation(Float_t  var) {fUpVariation = var;};
        void        SetDownVariation(Float_t  var) {fDownVariation = var;};
        void        SetOutputPath(TString   path) {fOutputPath = path;};
        void        SetOutputFileName(TString   name) {fOutputFileName = name;};
        void        SetBin (unsigned bin) {fBin = bin;};
        void        SetBinningFile(TString file) {fBinningFile = file;};
        void        SetYears(TString years) {fYears = years;};
        void        SetCNVersion(TString    cn_version) {fCNVersion = cn_version;};
        void        SetTrueYears(TString    true_years) {fTrueYears = true_years;};
        void        SetDrawOnlyErrors(Bool_t    draw_errors) {fDrawOnlyErrors = draw_errors;};
        void        SetDrawCrossSections(Bool_t draw_xsect) {fPlotxSect = draw_xsect;};
        void        SetOnlyInclusive(bool only_inclusive) {fOnlyInclusive = only_inclusive;}
        void        SetBothFlavours(bool both_flavours) {fBothFlavours = both_flavours;}
        void        CorrectCrossSections(TString XMLfile);
        void        DrawLine(Double_t x1, Double_t y1, Double_t x2, Double_t y2);
        void        PrintVariable(Double_t x, Double_t y, TString text);

        // getters
        int         GetNpoints() {return fNpoints;};

    private:
        unsigned    fNpoints;                   //!< Number of points in the scan

        double      x[MAXPOINTS];               //!< array of values of variable which is scanned
        double      x_err[MAXPOINTS];           //!< array of their errors, typically all zeros
        double      k_c[MAXPOINTS];             //!< array of charm scaling factors for different values of the scanning variable
        double      k_c_err[MAXPOINTS];         //!< error of charm scaling factors
        double      k_b[MAXPOINTS];             //!< beauty scaling factors
        double      k_b_err[MAXPOINTS];         //!< beauty scaling factors error
        double      sigma_c[MAXPOINTS];         //!< charm cross section
        double      sigma_c_err[MAXPOINTS];     //!< charm cross section error
        double      sigma_b[MAXPOINTS];         //!< beauty cross section
        double      sigma_b_err[MAXPOINTS];     //!< beauty cross section error

        TString     fVersionArray[MAXPOINTS];   //!< array containing histogram versions which were got with different
                                                //!< values of the scanning variable

        // now the variables that are necessary to access particular XML file other than version of the histogram
        TString     fCNVersion;                 //!< version of CN
        TString     fYears;                     //!< shows which run periods were used during merging step

        bool        fIsCharm;                   //!<
        bool        fPlotxSect;                 //!<

        unsigned    fBin;
        map<unsigned, Float_t>  fCharmUpSyst;
        map<unsigned, Float_t>  fCharmDownSyst;
        map<unsigned, Float_t>  fBeautyUpSyst;
        map<unsigned, Float_t>  fBeautyDownSyst;
        map<unsigned, Float_t>  fCharmUpSyst_err;
        map<unsigned, Float_t>  fCharmDownSyst_err;
        map<unsigned, Float_t>  fBeautyUpSyst_err;
        map<unsigned, Float_t>  fBeautyDownSyst_err;

        TString     fOutputPath;
        TString     fOutputFileName;

        TGraphErrors    *fCharmGraph;
        TGraphErrors    *fBeautyGraph;

        TString     fXAxisTitle;
        Float_t     fYaxisLowLimit;
        Float_t     fYaxisUpLimit;

        Float_t     fDefault;                   //!< default value of the scan variable - i.e. one at which central values are determined
        Float_t     fUpVariation;               //!< up-variation of the scan variable to be taken as a systematic error
        Float_t     fDownVariation;             //!< down-variation of the scan variable to be taken as a systematic error
        TString     fBinningFile;
        TString     fTrueYears;

        Bool_t      fDrawOnlyErrors;            //!< sometimes it's desirable to plot only errors, not the scaling factors

        TString     fXMLfile_xsect;             //!< XML filename to be corrected

        flavour     fFlavour;                   //!< charm or beauty

        bool        fOnlyInclusive;             //!< don't print the slope for every bin

        bool        fBothFlavours;              //!< plot/fit/print results for both charm and beauty; otherwise - according to fFlavour
};

#endif
