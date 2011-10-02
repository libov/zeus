// ROOT includes
#include <TGraphErrors.h>
#include <TPad.h>
#include <TAxis.h>

// main program
int TOTALjet_energy_scale () {
    
    // number of point to appear in a graph
    const int     NPOINTS = 3;

    // declare the arrays
    double  x[NPOINTS];
    double  x_err[NPOINTS];
    double  y_c[NPOINTS];
    double  y_c_err[NPOINTS];
    double  y_b[NPOINTS];
    double  y_b_err[NPOINTS];


    // now fill the arrays

    // x-axis, i.e. probabilities of track dropping in percent
    x [0] = -3;
    x [1] = 0;
    x [2] = 3;

    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

    // now the values of the charm scaling factors - for 2.11
    y_c[0] = 1.27213;
    y_c_err[0] = 0.02;

    y_c[1] = 1.24236;
    y_c_err[1] = 0.02;

    y_c[2] = 1.21105;
    y_c_err[2] = 0.02;


    // create and draw graph for charm
    TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, y_c, x_err, y_c_err);
    gr_charm -> SetMarkerStyle(22);
    gr_charm -> SetMarkerColor(kGreen);
    gr_charm -> SetMarkerSize(1.5);
    gr_charm -> Draw("ap");

    // now the values of the beauty scaling factors
    y_b[0] = 1.51575;
    y_b_err[0] = 0.055;

    y_b[1] = 1.53529;
    y_b_err[1] = 0.055;

    y_b[2] = 1.54949;
    y_b_err[2] = 0.054;
    
 
    // create and draw graph for beauty
    TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, y_b, x_err, y_b_err);
    gr_beauty -> SetMarkerStyle(23);
    gr_beauty -> SetMarkerColor(kBlue);
    gr_beauty -> SetMarkerSize(1.5);
    gr_beauty -> Draw("psame");

    TAxis * axis = gr_charm -> GetXaxis();
    axis -> SetTitle("TOTAL energy variation , %");

    // now fit the graphs
    gr_charm -> Fit("pol1", "", "", -4.5, 4.5);
    gr_beauty -> Fit("pol1", "", "", -4.5, 4.5);

    return 0;
}

    
    