// ROOT includes
#include <TGraphErrors.h>
#include <TPad.h>
#include <TAxis.h>

// main program
int jet_energy_scale () {
    
    // number of points to appear in a graph
    const int     NPOINTS = 13;

    // declare the arrays
    double  x[NPOINTS];
    double  x_err[NPOINTS];
    double  y_c[NPOINTS];
    double  y_c_err[NPOINTS];
    double  y_b[NPOINTS];
    double  y_b_err[NPOINTS];


    // now fill the arrays

    // x-axis, i.e. probabilities of track dropping in percent
    x [0] = -8;
    x [1] = -6;
    x [2] = -4;
    x [3] = -3;
    x [4] = -2;
    x [5] = -1;
    x [6] = 0;
    x [7] = 1;
    x [8] = 2;
    x [9] = 3;
    x [10] = 4;
    x [11] = 6;
    x [12] = 8;

    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

//----- 2.12.21 -------
y_c[0]= 1.27909;    y_c_err[0] =  0.0204525;
y_b[0]= 1.52768;    y_b_err[0] = 0.0550053;

//----- 2.12.19 -------
y_c[1]= 1.25979;    y_c_err[1] =  0.0203597;
y_b[1]= 1.53367;    y_b_err[1] = 0.0547909;

//----- 2.12.7 -------
y_c[2]= 1.24418;    y_c_err[2] =  0.0202787;
y_b[2]= 1.5461;    y_b_err[2] = 0.0547891;

//----- 2.12.3 -------
y_c[3]= 1.25309;    y_c_err[3] =  0.020204;
y_b[3]= 1.51489;    y_b_err[3] = 0.0546516;

//----- 2.12.9 -------
y_c[4]= 1.24237;    y_c_err[4] =  0.020126;
y_b[4]= 1.52492;    y_b_err[4] = 0.0544414;

//----- 2.12.11 -------
y_c[5]= 1.24295;    y_c_err[5] =  0.020115;
y_b[5]= 1.51464;    y_b_err[5] = 0.054457;

//----- 2.12.1 -------
y_c[6]= 1.24236;    y_c_err[6] =  0.0201146;
y_b[6]= 1.53529;    y_b_err[6] = 0.0546242;

//----- 2.12.10 -------
y_c[7]= 1.23292;    y_c_err[7] =  0.0199831;
y_b[7]= 1.5438;    y_b_err[7] = 0.0544929;

//----- 2.12.8 -------
y_c[8]= 1.22832;    y_c_err[8] =  0.0199915;
y_b[8]= 1.53724;    y_b_err[8] = 0.0544676;

//----- 2.12.2 -------
y_c[9]= 1.23235;    y_c_err[9] =  0.0199624;
y_b[9]= 1.51596;    y_b_err[9] = 0.0543374;

//----- 2.12.6 -------
y_c[10]= 1.21922;    y_c_err[10] =  0.0199661;
y_b[10]= 1.53372;    y_b_err[10] = 0.0543374;

//----- 2.12.18 -------
y_c[11]= 1.22065;    y_c_err[11] =  0.0197848;
y_b[11]= 1.55058;    y_b_err[11] = 0.0542772;

//----- 2.12.20 -------
y_c[12]= 1.21127;    y_c_err[12] =  0.0198224;
y_b[12]= 1.55593;    y_b_err[12] = 0.0541509;


    // now the values of the charm scaling factors - for 2.11
/*    y_c[0] = 1.24418;
    y_c_err[0] = 0.02;

    y_c[1] = 1.25309;
    y_c_err[1] = 0.02;

    y_c[2] = 1.24237;
    y_c_err[2] = 0.02;

    y_c[3] = 1.24295;
    y_c_err[3] = 0.020115;

    y_c[4] = 1.24236;
    y_c_err[4] = 0.02;

    y_c[5] = 1.23292;
    y_c_err[5] = 0.0199831 ;


    y_c[6] = 1.22832;
    y_c_err[6] = 0.02;

    y_c[7] = 1.23235;
    y_c_err[7] = 0.02;

    y_c[8] = 1.21922;
    y_c_err[8] = 0.02;*/

    // create and draw graph for charm
    TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, y_c, x_err, y_c_err);
    gr_charm -> SetMarkerStyle(22);
    gr_charm -> SetMarkerColor(kGreen);
    gr_charm -> SetMarkerSize(1.5);
    gr_charm -> Draw("ap");

    // now the values of the beauty scaling factors
/*    y_b[0] = 1.5461;
    y_b_err[0] = 0.055;

    y_b[1] = 1.5149;
    y_b_err[1] = 0.055;

    y_b[2] = 1.52492;
    y_b_err[2] = 0.054;
    
    y_b[3] = 1.51464;
    y_b_err[3] = 0.054457;
    
    y_b[4] = 1.53529;
    y_b_err[4] = 0.055;

    y_b[5] = 1.5438;
    y_b_err[5] = 0.0544929;

    y_b[6] = 1.537;
    y_b_err[6] = 0.054;

    y_b[7] = 1.51596;
    y_b_err[7] = 0.054;

    y_b[8] = 1.53372;
    y_b_err[8] = 0.054;*/

 
    // create and draw graph for beauty
    TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, y_b, x_err, y_b_err);
    gr_beauty -> SetMarkerStyle(23);
    gr_beauty -> SetMarkerColor(kBlue);
    gr_beauty -> SetMarkerSize(1.5);
    gr_beauty -> Draw("psame");

    TAxis * axis = gr_charm -> GetXaxis();
    axis -> SetTitle("Calorimeter energy variation , %");

    // now fit the graphs
    gr_charm -> Fit("pol1", "", "", -8, 8);
    gr_beauty -> Fit("pol1", "", "", -8, 8);

    return 0;
}
/*






*/
    