// ROOT includes
#include <TGraphErrors.h>
#include <TPad.h>
#include <TAxis.h>
#include <TF1.h>
#include <TPaveText.h>

// main program
int tracking_efficiency_uncertainty () {
    
    // number of point to appear in a graph
    const int     NPOINTS = 5;
    bool          etcut4_2 = false;

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

    // now fill the arrays

    // x-axis, i.e. probabilities of track dropping in percent
    x [0] = 0;
    x [1] = 1;
    x [2] = 2;
    x [3] = 3;
    x [4] = 4;
    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

    if (!etcut4_2) {
        //----- 2.16.0 -------
        k_c[0]= 1.30775; k_c_err[0]= 0.0213772;
        k_b[0]= 1.56718; k_b_err[0]= 0.0537078;
        sigma_c[0]= 3249.3; sigma_c_err[0]= 53.1149;
        sigma_b[0]= 240.77; sigma_b_err[0]= 8.25127;

        //----- 2.16.1 -------
        k_c[1]= 1.29523; k_c_err[1]= 0.0212933;
        k_b[1]= 1.57095; k_b_err[1]= 0.0535701;
        sigma_c[1]= 3218.19; sigma_c_err[1]= 52.9064;
        sigma_b[1]= 241.348; sigma_b_err[1]= 8.23011;

        //----- 2.16.2 -------
        k_c[2]= 1.31382; k_c_err[2]= 0.0221282;
        k_b[2]= 1.63095; k_b_err[2]= 0.0554708;
        sigma_c[2]= 3264.39; sigma_c_err[2]= 54.9807;
        sigma_b[2]= 250.566; sigma_b_err[2]= 8.52212;

        //----- 2.16.3 -------
        k_c[3]= 1.3431; k_c_err[3]= 0.0225387;
        k_b[3]= 1.65899; k_b_err[3]= 0.0566362;
        sigma_c[3]= 3337.14; sigma_c_err[3]= 56.0008;
        sigma_b[3]= 254.874; sigma_b_err[3]= 8.70116;

        //----- 2.16.4 -------
        k_c[4]= 1.35643; k_c_err[4]= 0.0232161;
        k_b[4]= 1.71368; k_b_err[4]= 0.0584814;
        sigma_c[4]= 3370.26; sigma_c_err[4]= 57.6839;
        sigma_b[4]= 263.277; sigma_b_err[4]= 8.98464;

        //----- 2.16.5 -------
        k_c[5]= 1.37937; k_c_err[5]= 0.0238247;
        k_b[5]= 1.76221; k_b_err[5]= 0.0598417;
        sigma_c[5]= 3427.26; sigma_c_err[5]= 59.196;
        sigma_b[5]= 270.733; sigma_b_err[5]= 9.19363;

    }

    if (etcut4_2) {
        // now the values of the charm sscaling factors - for 2.11
        k_c[0] = 1.28428;
        k_c_err[0] = 0.02;

        k_c[1] = 1.30311;
        k_c_err[1] = 0.021;

        k_c[2] = 1.327;
        k_c_err[2] = 0.0214;

        k_c[3] = 1.34805;
        k_c_err[3] = 0.022;

        k_c[4] = 1.35184;
        k_c_err[4] = 0.023;
    } else {
    }

    // create and draw graph for charm
    //TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, k_c, x_err, k_c_err);
    TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, sigma_c, x_err, sigma_c_err);
    gr_charm -> SetMarkerStyle(22);
    gr_charm -> SetMarkerColor(kGreen);
    gr_charm -> SetMarkerSize(1.5);
    gr_charm -> Draw("ap");

    // now the values of the beauty scaling factors
    if (etcut4_2) {
        k_b[0] = 1.60431;   // 2.8.0 - correct
        k_b_err[0] = 0.056;

        k_b[1] = 1.64326;
        k_b_err[1] = 0.057;

        k_b[2] = 1.67022;
        k_b_err[2] = 0.058;

        k_b[3] = 1.74271;
        k_b_err[3] = 0.06;

        k_b[4] = 1.83483;
        k_b_err[4] = 0.06;
    } else {
    }

    // create and draw graph for beauty
    //TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, k_b, x_err, k_b_err);
    TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, sigma_b, x_err, sigma_b_err);
    gr_beauty -> SetMarkerStyle(23);
    gr_beauty -> SetMarkerColor(kBlue);
    gr_beauty -> SetMarkerSize(1.5);
    gr_beauty -> Draw("psame");

    TAxis * axis = gr_charm -> GetXaxis();
    axis -> SetTitle("Probability to discard track, %");
    TAxis * y_axis = gr_charm -> GetYaxis();
    y_axis -> SetTitle("Scaling Factor");
    y_axis -> SetLimits (0, 2);

    // now fit the graphs
    gr_charm -> Fit("pol1", "", "", 0, 5);
    gr_beauty -> Fit("pol1", "", "", 0, 5);

    // calculate systematic uncertainties from the fit parameters
    TF1 * fcn_c = gr_charm -> GetFunction("pol1");
    TF1 * fcn_b = gr_beauty -> GetFunction("pol1");
    Double_t    syst_beauty  = 2 * 100 * fcn_b -> GetParameter(1) / fcn_b -> GetParameter(0);
    Double_t    syst_charm  = 2 * 100 * fcn_c -> GetParameter(1) / fcn_c -> GetParameter(0);

    // draw text paves with systematic uncertainties
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
    syst_c -> Draw();


    return 0;
}

    