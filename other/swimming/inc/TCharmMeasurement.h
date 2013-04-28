#ifndef __TCHARMMEASUREMENT_H__
#define __TCHARMMEASUREMENT_H__

#include <TROOT.h>

class TCharmMeasurement {

    public:

        TCharmMeasurement();
        TCharmMeasurement(TString filename, unsigned type);
        ~TCharmMeasurement(){};

        unsigned get_n_points() {return fNpoints;}
        Double_t getQ2(unsigned point) {return fQ2[point];}
        Double_t getX(unsigned point) {return fX[point];}
        Double_t getValue(unsigned point) {return fValue[point];}
        Double_t getErrStat(unsigned point) {return fErrStat[point];}
        Double_t getErrSystUp(unsigned point) {return fErrSystUp[point];}
        Double_t getErrSystDown(unsigned point) {return fErrSystDown[point];}
        Double_t getErrExtrapUp(unsigned point) {return fErrExtrapUp[point];}
        Double_t getErrExtrapDown(unsigned point) {return fErrExtrapDown[point];}
        Double_t getErrTotalUp(unsigned point) {return fErrTotalUp[point];}
        Double_t getErrTotalDown(unsigned point) {return fErrTotalDown[point];}

    private:

        void read_data();

        TString fFilename;
        unsigned fNpoints;
        Double_t fQ2[100];
        Double_t fX[100];
        Double_t fValue[100];
        Double_t fErrStat[100];
        Double_t fErrSystUp[100];
        Double_t fErrSystDown[100];
        Double_t fErrExtrapUp[100];
        Double_t fErrExtrapDown[100];
        Double_t fErrTotalUp[100];
        Double_t fErrTotalDown[100];

        unsigned fFileType;
};

#endif
