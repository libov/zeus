//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav,                            //
//  DESY,                                       //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

#include <TROOT.h>
#include <TMath.h>

const Double_t   alpha_em = (1./137);
const Double_t   pi = TMath::Pi();
const Double_t   s = 318*318;
const Double_t   pb_natural_conversion = 2.56819e-9;

const unsigned  n_variations = 6;

class TPointF2theo {

    public:

        TPointF2theo(Float_t q2, Float_t x, Float_t xsect, Float_t low_q2, Float_t up_q2, Float_t low_x, Float_t up_x);
        TPointF2theo() {};
        ~TPointF2theo() {};

        void GetDiffXsect();

        void EvaluateF2();

        void addVariation(Float_t xsect) {fvariation2.push_back(xsect); EvaluateUncertainty();};

        void EvaluateUncertainty();

        Float_t getQ2() {return fq2;}
        Float_t getX() {return fx;}
        Float_t getF2() {return f2;}
        Float_t getRelativeUncertaintyUp() {return frel_unc_up;}
        Float_t getRelativeUncertaintyDown() {return frel_unc_down;}

        void Print();

    private:

        Float_t     fq2;
        Float_t     fx;

        Float_t     fxsect;
        Float_t     fdiffxsect;
        Float_t     f2;

        Float_t     flow_q2;
        Float_t     fup_q2;
        Float_t     flow_x;
        Float_t     fup_x;

        //Float_t*    fvariation;
        vector<Float_t>      fvariation2;

        Float_t     frel_unc_up;
        Float_t     frel_unc_down;
};
