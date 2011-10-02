// ROOT includes
#include <TGraphErrors.h>
#include <TPad.h>
#include <TAxis.h>
#include <TF1.h>
#include <TPaveText.h>

// main program
int plot_syst () {
    
    // number of point to appear in a graph
    const int     NPOINTS = 11;

    // declare the arrays
    double  x[NPOINTS];
    double  x_err[NPOINTS];
    double  k_c[NPOINTS];
    double  k_c_err[NPOINTS];
    double  k_b[NPOINTS];
    double  k_b_err[NPOINTS];
    double  sigma_c[NPOINTS];
    double  sigma_c_err[NPOINTS];
    double  sigma_b[NPOINTS];
    double  sigma_b_err[NPOINTS];
    double  chi2[NPOINTS];

    // now fill the arrays

    // x-axis, i.e. probabilities of track dropping in percent
    x [0] = 0.5;
    x [1] = 0.6;
    x [2] = 0.7;
    x [3] = 0.8;
    x [4] = 0.9;
    x [5] = 1.0;
    x [6] = 1.1;
    x [7] = 1.2;
    x [8] = 1.3;
    x [9] = 1.4;
    x [10] = 1.5;

    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

    //----- 2.12.1 -------
    k_c[0]= 1.2784;  k_c_err[0]= 0.017115;
    k_b[0]= 1.49581; k_b_err[0]= 0.0468634;
    
    //----- 2.12.1 -------
    k_c[1]= 1.26996; k_c_err[1]= 0.0174152;
    k_b[1]= 1.49794; k_b_err[1]= 0.0476104;
    
    //----- 2.12.1 -------
    k_c[2]= 1.26154; k_c_err[2]= 0.0177497;
    k_b[2]= 1.50004; k_b_err[2]= 0.0484715;
    
    //----- 2.12.1 -------
    k_c[3]= 1.25315; k_c_err[3]= 0.0181445;
    k_b[3]= 1.50213; k_b_err[3]= 0.0494713;
    
    //----- 2.12.1 -------
    k_c[4]= 1.24476; k_c_err[4]= 0.0185801;
    k_b[4]= 1.50418; k_b_err[4]= 0.0505875;
    
    //----- 2.12.1 -------
    k_c[5]= 1.23639; k_c_err[5]= 0.0190572;
    k_b[5]= 1.50619; k_b_err[5]= 0.0518118;
    
    //----- 2.12.1 -------
    k_c[6]= 1.22804; k_c_err[6]= 0.0195984;
    k_b[6]= 1.50815; k_b_err[6]= 0.0531684;
    
    //----- 2.12.1 -------
    k_c[7]= 1.21967; k_c_err[7]= 0.0201568;
    k_b[7]= 1.51009; k_b_err[7]= 0.0546025;
    
    //----- 2.12.1 -------
    k_c[8]= 1.2113; k_c_err[8]= 0.02077;
    k_b[8]= 1.512;  k_b_err[8]= 0.0561474;
    
    //----- 2.12.1 -------
    k_c[9]= 1.20293; k_c_err[9]= 0.0214007;
    k_b[9]= 1.51385; k_b_err[9]= 0.0577635;
    
    //----- 2.12.1 -------
    k_c[10]= 1.19453; k_c_err[10]= 0.0220846;
    k_b[10]= 1.51568; k_b_err[10]= 0.0594806;

    chi2[0]= 1.95754;
    chi2[1]= 1.8796;
    chi2[2]= 1.81998;
    chi2[3]= 1.77803;
    chi2[4]= 1.75262;
    chi2[5]= 1.74219;
    chi2[6]= 1.74499;
    chi2[7]= 1.75917;
    chi2[8]= 1.78292;
    chi2[9]= 1.81449;
    chi2[10]= 1.8523;

    // create and draw graph for charm
    TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, k_c, x_err, k_c_err);
    gr_charm -> SetMarkerStyle(22);
    gr_charm -> SetMarkerColor(kGreen);
    gr_charm -> SetMarkerSize(1.5);
    gr_charm -> Draw("ap");

    // create and draw graph for beauty
    TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, k_b, x_err, k_b_err);
    gr_beauty -> SetMarkerStyle(23);
    gr_beauty -> SetMarkerColor(kBlue);
    gr_beauty -> SetMarkerSize(1.5);
    gr_beauty -> Draw("psame");

    TAxis * axis = gr_charm -> GetXaxis();
    axis -> SetTitle("Light flavour assymetry scaling");
    TAxis * y_axis = gr_charm -> GetYaxis();
    y_axis -> SetTitle("Scaling Factor");
    y_axis -> SetLimits (0, 2);
    y_axis -> SetRange (0, 2);

    TAxis * y_axis_b = gr_beauty -> GetYaxis();
    y_axis_b -> SetRange (0, 2);
    gPad -> Update();

    // now fit the graphs
    gr_charm -> Fit("pol1", "", "", 0, 5);
    gr_beauty -> Fit("pol1", "", "", 0, 5);

    // calculate systematic uncertainties from the fit parameters
    TF1 * fcn_c = gr_charm -> GetFunction("pol1");
    TF1 * fcn_b = gr_beauty -> GetFunction("pol1");
    Double_t    syst_beauty  = 2 * 100 * fcn_b -> GetParameter(1) / fcn_b -> GetParameter(0);
    Double_t    syst_charm  = 2 * 100 * fcn_c -> GetParameter(1) / fcn_c -> GetParameter(0);*/

/*    // draw text paves with systematic uncertainties
    char    tmp[256];

    TPaveText   *  syst_b = new TPaveText(0.44, 0.65, 0.8, 0.73 ,"NDC");
    syst_b -> SetShadowColor(0);
    syst_b -> SetTextAlign(12);
    sprintf (tmp, "Syst. unc. beauty: %.3f %% ", syst_beauty);
    syst_b -> AddText(tmp);
    syst_b -> Draw();

    TPaveText   *  syst_c = new TPaveText(0.44, 0.65, 0.8, 0.73 ,"NDC");
    syst_c -> SetShadowColor(0);
    syst_c -> SetTextAlign(12);
    sprintf (tmp, "Syst. unc. charm: %.3f %% ", syst_charm);
    syst_c -> AddText(tmp);
    syst_c -> Draw();*/


    return 0;
}
