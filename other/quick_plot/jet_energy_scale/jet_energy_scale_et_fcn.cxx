#include <TPaveText.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TAxis.h>

int jet_energy_scale_et_fcn() {
    
    // various switches
    bool    cal_part_only = true;
    bool    scaled_errors = true;
    bool    beauty = true;
    bool    etcut4_2 = false;
    bool    useAtan = false; // if false, linear function will be used for fit
    
    // only jone of them should be true!
    bool    et_dependence = true;
    bool    q2_dependence = false;
    bool    x_dependence = false;
    bool    eta_dependence = false;
    bool    double_diff = false;

    // declare the arrays
    const int     NPOINTS = 7;    // et
    //const int     NPOINTS = 8;  // q2
    //const int     NPOINTS = 6;  // x
    //const int     NPOINTS = 11;  // eta
    // const int     NPOINTS = 18;  // double diff

    // for x-arrays
    double  x[NPOINTS];
    double  x_err[NPOINTS];

    // charm
    double  cal_c[NPOINTS];
    double  cal_c_err[NPOINTS];
    double  cal_c_err_scaled[NPOINTS];
    double  total_c[NPOINTS];
    double  total_c_err[NPOINTS];
    double  total_c_err_scaled[NPOINTS];

    // beauty
    double  cal_b[NPOINTS];
    double  cal_b_err[NPOINTS];
    double  cal_b_err_scaled[NPOINTS];
    double  total_b[NPOINTS];
    double  total_b_err[NPOINTS];
    double  total_b_err_scaled[NPOINTS];
    
    if (et_dependence) {
        // these are middle points of the et bins
        if (etcut4_2) {
            x [0] = 6.1;  // for ET > 4.2 GeV
        } else {
            x [0] = 6.5;  // for ET >  5 GeV
        }
        x [1] = 9.5;
        x [2] = 12.5;
        x [3] = 15.5;
        x [4] = 18.5;
        x [5] = 22.5;
        x [6] = 30;
    }
    if (q2_dependence) {
        x[0] = 7.5;
        x[1] = 15;
        x[2] = 30;
        x[3] = 55;
        x[4] = 95;
        x[5] = 160;
        x[6] = 300;
        x[7] = 700;
    }

    if (x_dependence) {
        x[0] = 0.00014;
        x[1] = 0.0004;
        x[2] = 0.0011;
        x[3] = 0.0033;
        x[4] = 0.0075;
        x[5] = 0.055;
    }

    if (eta_dependence) {
        x[0] = 1.35;
        x[1] = 0.95;
        x[2] = 0.65;
        x[3] = 0.35;
        x[4] = 0.15;
        x[5] = 0.25;
        x[6] = 0.55;
        x[7] = 0.85;
        x[8] = 1.15;
        x[9] = 1.45;
        x[10] = 1.9;
    }

    if (double_diff) {
        
    }




    // x-axis error is zero
    for (int i = 0; i < NPOINTS; i++) {
        x_err [i] = 0;
    }

    // now set values and their errors

    // Et cut 4.2 GeV, dependence of systematic on ET
    if (etcut4_2 && et_dependence) {
        // charm
        // calorimetric part
        cal_c[0] =-0.45;    cal_c_err[0] =0.7;      cal_c_err_scaled[0] =0.2;
        cal_c[1] =-3.5;     cal_c_err[1] =0.6;      cal_c_err_scaled[1] =0.2;
        cal_c[2] =-7.8;     cal_c_err[2] =0.9;      cal_c_err_scaled[2] =0.3;
        cal_c[3] =-9.4;     cal_c_err[3] =1.4;      cal_c_err_scaled[3] =0.3;
        cal_c[4] =-12.2;    cal_c_err[4] =2.1;      cal_c_err_scaled[4] =0.8;
        cal_c[5] =-14.2;    cal_c_err[5] =3.4;      cal_c_err_scaled[5] =1.4;
        cal_c[6] =-14.5;    cal_c_err[6] =10;       cal_c_err_scaled[6] =3.7;

        // total jet energy
        total_c[0] =-1.5;   total_c_err[0] =0.7;    total_c_err_scaled[0] =0.2;
        total_c[1] =-9;     total_c_err[1] =0.6;    total_c_err_scaled[1] =0.3;
        total_c[2] =-12.1;  total_c_err[2] =0.9;    total_c_err_scaled[2] =0.5;
        total_c[3] =-14.4;  total_c_err[3] =1.34;   total_c_err_scaled[3] =0.6;
        total_c[4] =-14.1;  total_c_err[4] =2.2;    total_c_err_scaled[4] =1.3;
        total_c[5] =-14.5;  total_c_err[5] =3.3;    total_c_err_scaled[5] =1.4;
        total_c[6] =-16;    total_c_err[6] =9.9;    total_c_err_scaled[6] =4.2;
        
        // beauty
        // calorimetric part
        cal_b[0] = 10.5;    cal_b_err[0] = 2.4;     cal_b_err_scaled[0] = 0.8;
        cal_b[1] = 5.2;     cal_b_err[1] = 1.4;     cal_b_err_scaled[1] = 0.2;
        cal_b[2] = 2.4;     cal_b_err[2] = 1.2;     cal_b_err_scaled[2] = 0.3;
        cal_b[3] = -3.2;    cal_b_err[3] = 1.4;     cal_b_err_scaled[3] = 0.4;
        cal_b[4] = -5.9;    cal_b_err[4] = 2.1;     cal_b_err_scaled[4] = 0.7;
        cal_b[5] = -10.1;   cal_b_err[5] = 2.6;     cal_b_err_scaled[5] = 0.9;
        cal_b[6] = -19.9;   cal_b_err[6] = 4.7;     cal_b_err_scaled[6] = 1.6;

        // total jet energy
        total_b[0] = 18.8;  total_b_err[0] = 2.3;   total_b_err_scaled[0] = 1.1;
        total_b[1] = 10.5;  total_b_err[1] = 1.4;   total_b_err_scaled[1] = 0.5;
        total_b[2] = 1.4;   total_b_err[2] = 1.2;   total_b_err_scaled[2] = 0.4;
        total_b[3] = -4.9;  total_b_err[3] = 1.4;   total_b_err_scaled[3] = 0.7;
        total_b[4] = -10.1; total_b_err[4] = 2;     total_b_err_scaled[4] = 0.5;
        total_b[5] = -14.2; total_b_err[5] = 2.5;   total_b_err_scaled[5] = 1.1;
        total_b[6] = -20.7; total_b_err[6] = 4.7;   total_b_err_scaled[6] = 2;
    }
    if (etcut4_2 && q2_dependence) {
        cal_c[0] = -1.58882; cal_c_err[0] = 0.82825;    cal_c_err_scaled[0] = 0.2;
        cal_c[1] = -0.929659; cal_c_err[1] = 0.639753;  cal_c_err_scaled[1] = 0.2;
        cal_c[2] = -0.913488; cal_c_err[2] = 0.589741;  cal_c_err_scaled[2] = 0.2;
        cal_c[3] = -0.865226; cal_c_err[3] = 0.766939;  cal_c_err_scaled[3] = 0.1;
        cal_c[4] = -0.712095; cal_c_err[4] = 0.899292;  cal_c_err_scaled[4] = 0.25;
        cal_c[5] = -0.376884; cal_c_err[5] = 1.35314;   cal_c_err_scaled[5] = 0.3;
        cal_c[6] = 0.272009; cal_c_err[6] = 1.4521;     cal_c_err_scaled[6] = 0.25;
        cal_c[7] = -1.16376; cal_c_err[7] = 3.298;      cal_c_err_scaled[7] = 1.074;

        cal_b[0] =  0.763555;   cal_b_err[0] = 1.65295; cal_b_err_scaled[0] = 0.4;
        cal_b[1] =  0.110516;   cal_b_err[1] = 1.63399; cal_b_err_scaled[1] = 0.4;
        cal_b[2] =  0.447728;   cal_b_err[2] = 1.71882; cal_b_err_scaled[2] = 0.5;
        cal_b[3] =  0.667424;   cal_b_err[3] = 1.83669; cal_b_err_scaled[3] = 0.3;
        cal_b[4] =  -0.11311;   cal_b_err[4] = 2.00159; cal_b_err_scaled[4] = 0.6;
        cal_b[5] =  -0.108705;  cal_b_err[5] = 1.81492; cal_b_err_scaled[5] = 0.6;
        cal_b[6] =  -1.38997;   cal_b_err[6] = 2.04572; cal_b_err_scaled[6] = 0.6;
        cal_b[7] =  0.852825;   cal_b_err[7] = 3.57648; cal_b_err_scaled[7] = 1.2;
    }

    if (etcut4_2 && x_dependence) {
        cal_c[0]= -1.81112; cal_c_err[0]=1.62649;
        cal_c[1]= -0.822568; cal_c_err[1]=0.743124;
        cal_c[2]= -0.965282; cal_c_err[2]=0.50435;
        cal_c[3]= -0.947308; cal_c_err[3]=0.50132;
        cal_c[4]= -0.537309; cal_c_err[4]=0.950579;
        cal_c[5]= -0.989486; cal_c_err[5]=1.50598;

        cal_b[0]= 0.0598682; cal_b_err[0]=2.96829;
        cal_b[1]= -0.153028; cal_b_err[1]=1.26877;
        cal_b[2]= 0.840825; cal_b_err[2]=1.21749;
        cal_b[3]= 0.470533; cal_b_err[3]=1.21605;
        cal_b[4]= -0.425112; cal_b_err[4]=2.02325;
        cal_b[5]= 0.13848; cal_b_err[5]=3.24598;
    }

    if (etcut4_2 && eta_dependence) {
        cal_c[0]= -2.17489; cal_c_err[0]=2.75058;
        cal_c[1]= -0.960681; cal_c_err[1]=1.13215;
        cal_c[2]= -0.570489; cal_c_err[2]=0.880295;
        cal_c[3]= -0.673533; cal_c_err[3]=0.702265;
        cal_c[4]= -0.573652; cal_c_err[4]=0.753396;
        cal_c[5]= -0.50874; cal_c_err[5]=0.722657;
        cal_c[6]= -0.719877; cal_c_err[6]=0.76216;
        cal_c[7]= -1.04486; cal_c_err[7]=0.824234;
        cal_c[8]= -0.558724; cal_c_err[8]=1.08474;
        cal_c[9]= -1.90666; cal_c_err[9]=1.75372;
        cal_c[10]= -2.87272; cal_c_err[10]=2.63567;

        cal_b[0]= -3.4836; cal_b_err[0]=7.51761;
        cal_b[1]= 0.309286; cal_b_err[1]=5.84373;
        cal_b[2]= -1.27048; cal_b_err[2]=2.31041;
        cal_b[3]= 0.237402; cal_b_err[3]=2.07876;
        cal_b[4]= -0.111824; cal_b_err[4]=1.41559;
        cal_b[5]= 0.844575; cal_b_err[5]=1.41825;
        cal_b[6]= -0.0965355; cal_b_err[6]=1.33236;
        cal_b[7]= -0.192007; cal_b_err[7]=1.69776;
        cal_b[8]= 0.838165; cal_b_err[8]=1.82742;
        cal_b[9]= 1.46212; cal_b_err[9]=3.12681;
        cal_b[10]= 1.45462; cal_b_err[10]=4.94056;
    }

    if (etcut4_2 && double_diff) {
        cal_c[0]= -1.81112; cal_c_err[0]=1.62649;
        cal_c[1]= -0.989605; cal_c_err[1]=1.36964;
        cal_c[2]= -0.770765; cal_c_err[2]=1.18482;
        cal_c[3]= -1.26254; cal_c_err[3]=0.661961;
        cal_c[4]= -0.995413; cal_c_err[4]=3.13696;
        cal_c[5]= -0.56747; cal_c_err[5]=0.796671;
        cal_c[6]= -0.399019; cal_c_err[6]=0.919056;
        cal_c[7]= -0.925827; cal_c_err[7]=1.02203;
        cal_c[8]= -1.76642; cal_c_err[8]=1.37275;
        cal_c[9]= -0.946665; cal_c_err[9]=2.20191;
        cal_c[10]= -0.759261; cal_c_err[10]=1.50492;
        cal_c[11]= -0.91059; cal_c_err[11]=1.21822;
        cal_c[12]= -0.874281; cal_c_err[12]=1.71854;
        cal_c[13]= -0.591356; cal_c_err[13]=1.36269;
        cal_c[14]= 0.180213; cal_c_err[14]=1.32971;
        cal_c[15]= 0.241401; cal_c_err[15]=3.8205;
        cal_c[16]= 0.365905; cal_c_err[16]=3.34849;
        cal_c[17]= -3.5351; cal_c_err[17]=8.7276;

        cal_b[0]= 0.0598682; cal_b_err[0]=2.96829;
        cal_b[1]= -0.599542; cal_b_err[1]=2.66917;
        cal_b[2]= -0.220524; cal_b_err[2]=1.86343;
        cal_b[3]= 1.66997; cal_b_err[3]=2.07352;
        cal_b[4]= 2.43205; cal_b_err[4]=4.34644;
        cal_b[5]= -0.750729; cal_b_err[5]=1.74739;
        cal_b[6]= -0.617666; cal_b_err[6]=2.30832;
        cal_b[7]= 1.31218; cal_b_err[7]=2.76052;
        cal_b[8]= 4.76382; cal_b_err[8]=9.00434;
        cal_b[9]= 0.0725576; cal_b_err[9]=2.31431;
        cal_b[10]= 0.00683635; cal_b_err[10]=2.34607;
        cal_b[11]= 0.212814; cal_b_err[11]=3.02552;
        cal_b[12]= 1.03023; cal_b_err[12]=13.8123;
        cal_b[13]= 1.15777; cal_b_err[13]=2.43305;
        cal_b[14]= -0.603596; cal_b_err[14]=1.50213;
        cal_b[15]= -6.19809; cal_b_err[15]=8.49434;
        cal_b[16]= -0.763366; cal_b_err[16]=4.03559;
        cal_b[17]= 1.50495; cal_b_err[17]=7.07639;
    }


/* 
   // ET CUT 5 GEV, WITHOUT 0304P
    // -------------- charm -----------------
    //  VARIATION OF THE CAL PART
    cal_c[0] = -0.256074;
    cal_c[1] = -3.67987;
    cal_c[2] =-8.14181;
    cal_c[3] = -8.93918;
    cal_c[4] = -12.3905;
    cal_c[5] = -14.9292;
    cal_c[6] = -19.2526;

    cal_c_err_scaled[0] =0.2;
    cal_c_err_scaled[1] =0.2;
    cal_c_err_scaled[2] =0.4;
    cal_c_err_scaled[3] =0.6;
    cal_c_err_scaled[4] =1.1;
    cal_c_err_scaled[5] =1.7;
    cal_c_err_scaled[6] =4.6;

    // ------------- beauty --------------
    //  VARIATION OF THE CAL PART

    cal_b[0] = 10.7496;
    cal_b[1] = 5.90815;
    cal_b[2] = 3.32237;
    cal_b[3] = -2.67697;
    cal_b[4] = -5.70652;
    cal_b[5] = -9.84458;
    cal_b[6] = -15.8302;

    cal_b_err_scaled[0] = 0.8;
    cal_b_err_scaled[1] = 0.4;
    cal_b_err_scaled[2] = 0.6;
    cal_b_err_scaled[3] = 0.4;
    cal_b_err_scaled[4] = 0.8;
    cal_b_err_scaled[5] = 1.8;
    cal_b_err_scaled[6] = 1.5;
*/

    // ET CUT 5 GEV, WITH 0304P
    if (!etcut4_2) {
        // -------------- charm -----------------
        //  VARIATION OF THE CAL PART
        cal_c[0]= -0.36908;     cal_c_err[0]=0.600262;  cal_c_err_scaled[0] = 0.2;
        cal_c[1]= -3.7231;      cal_c_err[1]=0.556069;  cal_c_err_scaled[1] = 0.15;
        cal_c[2]= -7.62437;     cal_c_err[2]=0.843398;  cal_c_err_scaled[2] = 0.4;
        cal_c[3]= -9.64093;     cal_c_err[3]=1.30881;   cal_c_err_scaled[3] = 0.5;
        cal_c[4]= -11.2986;     cal_c_err[4]=1.98653;   cal_c_err_scaled[4] = 0.6;
        cal_c[5]= -13.8181;     cal_c_err[5]=3.46494;   cal_c_err_scaled[5] = 1.2;
        cal_c[6]= -19.8228;     cal_c_err[6]=9.79082;   cal_c_err_scaled[6] = 3.4;
        //cal_c[999]= -1.44885; cal_c_err[999]=0.291669

        // ------------- beauty --------------
        //  VARIATION OF THE CAL PART
        cal_b[0]= 10.5629; cal_b_err[0]=2.57837;        cal_b_err_scaled[0] = 0.6;
        cal_b[1]= 5.88092; cal_b_err[1]=1.29365;        cal_b_err_scaled[1] = 0.3; 
        cal_b[2]= 2.44423; cal_b_err[2]=1.1154;         cal_b_err_scaled[2] = 0.4;
        cal_b[3]= -1.84038; cal_b_err[3]=1.34402;       cal_b_err_scaled[3] = 0.3;
        cal_b[4]= -5.57807; cal_b_err[4]=2.00686;       cal_b_err_scaled[4] = 0.6;
        cal_b[5]= -9.83243; cal_b_err[5]=2.50934;       cal_b_err_scaled[5] = 1.1;
        cal_b[6]= -16.1032; cal_b_err[6]=5.11725;       cal_b_err_scaled[6] = 1.7;
        //cal_b[999]= 0.716015; cal_b_err[999]=0.637465


    }
    
    // some settings
    gStyle->SetOptFit(1);
    gStyle->SetOptTitle(0);
    gStyle->SetStatX(0.85);
    gStyle->SetStatY(0.35);
    gStyle->SetPadTopMargin(0.025);
    gStyle->SetPadRightMargin(0.025);

    // create canvas
    TCanvas *def = new TCanvas();
    def->cd();
    // create a graph
    TGraphErrors * graph;

if (!beauty) {

    if (cal_part_only) {
        if (scaled_errors) {
            graph = new TGraphErrors(NPOINTS, x, cal_c, x_err, cal_c_err_scaled);
        } else {
            graph = new TGraphErrors(NPOINTS, x, cal_c, x_err, cal_c_err);
        }
    } else {
        if (scaled_errors) {
            graph = new TGraphErrors(NPOINTS, x, total_c, x_err, total_c_err_scaled);
        } else {
            graph = new TGraphErrors(NPOINTS, x, total_c, x_err, total_c_err);
        }
    }
} else {
    if (cal_part_only) {
        if (scaled_errors) {
            graph = new TGraphErrors(NPOINTS, x, cal_b, x_err, cal_b_err_scaled);
        } else {
            graph = new TGraphErrors(NPOINTS, x, cal_b, x_err, cal_b_err);
        }
    } else {
        if (scaled_errors) {
            graph = new TGraphErrors(NPOINTS, x, total_b, x_err, total_b_err_scaled);
        } else {
            graph = new TGraphErrors(NPOINTS, x, total_b, x_err, total_b_err);
        }
    }
}

    graph -> SetMarkerStyle(22);
    graph -> SetMarkerColor(kGreen);
    graph -> SetMarkerSize(1.5);
    graph -> Draw("ap");

    // set range of the y axis
    TAxis   *ax_charm_y = graph -> GetYaxis();
    ax_charm_y -> SetTitle("Systematic uncertainty, %");

    TAxis   *ax_charm_x = graph -> GetXaxis();
    if (et_dependence) ax_charm_x -> SetTitle("E_{T}(jet), GeV");
    if (q2_dependence) {
        //gPad -> SetLogx();
        ax_charm_x -> SetTitle("Q^{2}, GeV^{2}");
    }

    TF1 * fcn;
    if (useAtan) {
        fcn = new TF1("fcn", "[0]*atan([1]*x+[2])", 5.5, 30);
    } else {
        fcn = new TF1("fcn", "pol1", 5.5, 30);
    }
    //TF1 * fcn = new TF1("fcn", "pol2", 5.5, 30);

    fcn -> SetParameter(0, 19);
    fcn -> SetParameter(1, -0.13);
    fcn -> SetParameter(2, 1.8);
    graph -> Fit(fcn, "", "", 5.8, 30);

    TPaveText   * pave = new TPaveText (0.13, 0.8,0.4,0.88,"NDC");
    if (useAtan) {
        pave -> AddText("f(x)=p_{0}atan(p_{1} x+p_{2})");
    } else {
       pave -> AddText("f(x)=p_{0}+p_{1}x");
    }

    pave -> SetShadowColor(0);
    pave -> Draw();


    /*TLine * line;
    if (isBeauty && etcut4_2) {
        line = 
    }*/
    //def.Print("jet_energy_scale_plots/"+bin_str+".png");

    return 0;
}
