//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav,                            //
//  DESY,                                       //
//  libov@mail.desy.de                          //
//                                              //
//////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

#include<TPointF2theo.h>

TPointF2theo::TPointF2theo(Float_t q2, Float_t x, Float_t xsect, Float_t low_q2, Float_t up_q2, Float_t low_x, Float_t up_x) {
    fq2 = q2;
    fx = x;
    fxsect = xsect;
    flow_q2 = low_q2;
    fup_q2 = up_q2;
    flow_x = low_x;
    fup_x = up_x;

    GetDiffXsect();
    EvaluateF2();
}

void TPointF2theo::GetDiffXsect() {
    // get differential cross-section: divide by the bin width
    fdiffxsect = fxsect;
    fdiffxsect /= (fup_q2-flow_q2);
    fdiffxsect /= (fup_x-flow_x);
    // transform to natural units
    fdiffxsect *= (pb_natural_conversion);
}

void TPointF2theo::EvaluateF2() {
    // evaluate y from Q2, x and s
    Float_t y = fq2/( s * fx);
    Float_t kinematic_factor = 2 * pi * alpha_em * alpha_em * (1 + (1-y)*(1-y)) / (fq2 * fq2 * fx);
    f2 = fdiffxsect / kinematic_factor; 
}

void TPointF2theo::EvaluateUncertainty() {
    Float_t up_variation = 0;
    Float_t down_variation = 0;
    for (unsigned i=0; i<fvariation2.size(); i++) {
        Float_t variation = fvariation2[i];
        if (variation > fxsect) up_variation += pow(variation - fxsect, 2);
        if (variation < fxsect) down_variation += pow(variation - fxsect, 2);
    }
    up_variation = sqrt(up_variation);
    down_variation = sqrt(down_variation);

    frel_unc_up = up_variation/fxsect;
    frel_unc_down = down_variation/fxsect;
}


void TPointF2theo::Print() {
    cout << "\tQ2= " << fq2 << "\t\tx= " << fx << "\tF2_th= " << f2 << " +" << f2 * frel_unc_up << " -" << f2 * frel_unc_down << endl;
}
