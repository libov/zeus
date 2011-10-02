// ROOT includes
#include <TGraphErrors.h>
#include <TPad.h>
#include <TAxis.h>
#include <TF1.h>
#include <TPaveText.h>

// main program
int plot_syst () {
    
    // number of point to appear in a graph
    const int     NPOINTS = 9;
    bool          etcut4_2 = false;
    bool          vary_prob_central_core = true;

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
    x [1] = 25;
    x [2] = 50;
    x [3] = 75;
    x [4] = 100;
    x [5] = 125;
    x [6] = 150;
    x [7] = 175;
    x [8] = 200;

    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

    if (!etcut4_2) {

        //----- 2.19.0 -------
        k_c[0]= 1.29918; k_c_err[0]= 0.0199421;
        k_b[0]= 1.46999; k_b_err[0]= 0.0494826;
        sigma_c[0]= 3228.09; sigma_c_err[0]= 49.5505;
        sigma_b[0]= 231.949; sigma_b_err[0]= 7.8078;

        //----- 2.19.1 -------
        k_c[1]= 1.28958; k_c_err[1]= 0.0199787;
        k_b[1]= 1.49976; k_b_err[1]= 0.0497005;
        sigma_c[1]= 3204.23; sigma_c_err[1]= 49.6413;
        sigma_b[1]= 236.645; sigma_b_err[1]= 7.8422;

        //----- 2.19.2 -------
        k_c[2]= 1.28871; k_c_err[2]= 0.0200125;
        k_b[2]= 1.4739; k_b_err[2]= 0.0500819;
        sigma_c[2]= 3202.06; sigma_c_err[2]= 49.7252;
        sigma_b[2]= 232.566; sigma_b_err[2]= 7.90238;

        //----- 2.19.3 -------
        k_c[3]= 1.27795; k_c_err[3]= 0.0199246;
        k_b[3]= 1.44933; k_b_err[3]= 0.0499399;
        sigma_c[3]= 3175.34; sigma_c_err[3]= 49.5068;
        sigma_b[3]= 228.688; sigma_b_err[3]= 7.87997;

        //----- 2.19.4 -------
        k_c[4]= 1.27032; k_c_err[4]= 0.0199508;
        k_b[4]= 1.4668; k_b_err[4]= 0.0502009;
        sigma_c[4]= 3156.37; sigma_c_err[4]= 49.5719;
        sigma_b[4]= 231.445; sigma_b_err[4]= 7.92115;

        //----- 2.19.5 -------
        k_c[5]= 1.25371; k_c_err[5]= 0.0198913;
        k_b[5]= 1.46621; k_b_err[5]= 0.0501991;
        sigma_c[5]= 3115.1; sigma_c_err[5]= 49.4241;
        sigma_b[5]= 231.351; sigma_b_err[5]= 7.92087;

        //----- 2.19.6 -------
        k_c[6]= 1.24066; k_c_err[6]= 0.0198688;
        k_b[6]= 1.48882; k_b_err[6]= 0.0502782;
        sigma_c[6]= 3082.68; sigma_c_err[6]= 49.3682;
        sigma_b[6]= 234.919; sigma_b_err[6]= 7.93335;

        //----- 2.19.7 -------
        k_c[7]= 1.23638; k_c_err[7]= 0.0198287;
        k_b[7]= 1.43646; k_b_err[7]= 0.0503533;
        sigma_c[7]= 3072.05; sigma_c_err[7]= 49.2685;
        sigma_b[7]= 226.658; sigma_b_err[7]= 7.94519;

        //----- 2.19.8 -------
        k_c[8]= 1.24045; k_c_err[8]= 0.0198149;
        k_b[8]= 1.42873; k_b_err[8]= 0.0504133;
        sigma_c[8]= 3082.15; sigma_c_err[8]= 49.2344;
        sigma_b[8]= 225.439; sigma_b_err[8]= 7.95466;
     }

    if (etcut4_2 && vary_prob_central_core) {
        //----- 2.18.0 -------
        k_c[0]= 1.17547; k_c_err[0]= 0.0376061;
        k_b[0]= 1.67722; k_b_err[0]= 0.21397;
        sigma_c[0]= 3601.56; sigma_c_err[0]= 115.223;
        sigma_b[0]= 182.838; sigma_b_err[0]= 23.3254;

        //----- 2.18.1 -------
        k_c[1]= 1.16545; k_c_err[1]= 0.0379022;
        k_b[1]= 1.73547; k_b_err[1]= 0.215924;
        sigma_c[1]= 3570.86; sigma_c_err[1]= 116.13;
        sigma_b[1]= 189.188; sigma_b_err[1]= 23.5384;
        
        //----- 2.18.2 -------
        k_c[2]= 1.16567; k_c_err[2]= 0.0376494;
        k_b[2]= 1.63399; k_b_err[2]= 0.214784;
        sigma_c[2]= 3571.54; sigma_c_err[2]= 115.355;
        sigma_b[2]= 178.126; sigma_b_err[2]= 23.4142;
        
        //----- 2.18.3 -------
        k_c[3]= 1.15118; k_c_err[3]= 0.0379207;
        k_b[3]= 1.66359; k_b_err[3]= 0.217472;
        sigma_c[3]= 3527.12; sigma_c_err[3]= 116.186;
        sigma_b[3]= 181.352; sigma_b_err[3]= 23.7071;
        
        //----- 2.18.4 -------
        k_c[4]= 1.15871; k_c_err[4]= 0.0377051;
        k_b[4]= 1.62257; k_b_err[4]= 0.216972;
        sigma_c[4]= 3550.21; sigma_c_err[4]= 115.526;
        sigma_b[4]= 176.88; sigma_b_err[4]= 23.6527;
        
        //----- 2.18.5 -------
        k_c[5]= 1.12096; k_c_err[5]= 0.0372464;
        k_b[5]= 1.71687; k_b_err[5]= 0.214929;
        sigma_c[5]= 3434.53; sigma_c_err[5]= 114.12;
        sigma_b[5]= 187.161; sigma_b_err[5]= 23.4299;
        
        //----- 2.18.6 -------
        k_c[6]= 1.12312; k_c_err[6]= 0.0376166;
        k_b[6]= 1.73855; k_b_err[6]= 0.217204;
        sigma_c[6]= 3441.18; sigma_c_err[6]= 115.255;
        sigma_b[6]= 189.524; sigma_b_err[6]= 23.6779;
        
        //----- 2.18.7 -------
        k_c[7]= 1.09768; k_c_err[7]= 0.0374948;
        k_b[7]= 1.76141; k_b_err[7]= 0.21768;
        sigma_c[7]= 3363.21; sigma_c_err[7]= 114.882;
        sigma_b[7]= 192.015; sigma_b_err[7]= 23.7298;
        
        //----- 2.18.8 -------
        k_c[8]= 1.10128; k_c_err[8]= 0.037345;
        k_b[8]= 1.66275; k_b_err[8]= 0.216449;
        sigma_c[8]= 3374.26; sigma_c_err[8]= 114.423;
        sigma_b[8]= 181.261; sigma_b_err[8]= 23.5957;
    }



    // create and draw graph for charm
    TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, k_c, x_err, k_c_err);
    //TGraphErrors * gr_charm = new TGraphErrors(NPOINTS, x, sigma_c, x_err, sigma_c_err);
    gr_charm -> SetMarkerStyle(22);
    gr_charm -> SetMarkerColor(kGreen);
    gr_charm -> SetMarkerSize(1.5);
    gr_charm -> Draw("ap");

    // create and draw graph for beauty
    TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, k_b, x_err, k_b_err);
    //TGraphErrors * gr_beauty = new TGraphErrors(NPOINTS, x, sigma_b, x_err, sigma_b_err);
    gr_beauty -> SetMarkerStyle(23);
    gr_beauty -> SetMarkerColor(kBlue);
    gr_beauty -> SetMarkerSize(1.5);
    gr_beauty -> Draw("psame");

    TAxis * axis = gr_charm -> GetXaxis();
    axis -> SetTitle("Smearing effect, %");
    TAxis * y_axis = gr_charm -> GetYaxis();
    y_axis -> SetTitle("Scaling Factor");
    y_axis -> SetLimits (0, 2);
    y_axis -> SetRange (0, 2);

    TAxis * y_axis_b = gr_beauty -> GetYaxis();
    y_axis_b -> SetRange (0, 2);
    gPad -> Update();

    // now fit the graphs
/*    gr_charm -> Fit("pol1", "", "", 0, 5);
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

    
