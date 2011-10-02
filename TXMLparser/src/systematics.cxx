#include <iostream>
using namespace std;

// my headers
#include <TSystematics.h>

// main function
int main(int argc, char **argv) {

    // create an instance of TSystematics object
    TSystematics instance;


    // --------------------------------------------------------------//
    // -------------------------  settings  -------------------------//
    // --------------------------------------------------------------//

    // settings for the core gaussian
/*    const unsigned NPOINTS = 7;
    double  x[NPOINTS] = {3, 5, 6, 7, 8, 9, 11};
    instance.SetXAxisTitle("probability of core gaussian, %");
    instance.SetDefault(7);
    instance.SetVariation(2);
//     // charm (ET>4.2)
//     TString version[NPOINTS] = {"2.22.2", "2.22.3", "2.22.4", "2.22.5", "2.22.6", "2.22.7", "2.22.8"};
//     // beauty (ET>5)
    instance.SetBinningFile("full");
    TString version[NPOINTS] = {"2.23.2", "2.23.3", "2.23.4", "2.23.5", "2.23.6", "2.23.7", "2.23.8"};*/
    
    //instance.SetOutputFileName("smearing_syst_gaus1_ET5_bin1");

/*    // settings for the tail gaussian
    const unsigned NPOINTS = 9;
    double  x[NPOINTS] = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5};
    instance.SetXAxisTitle("probability of tail gaussian, %");
     instance.SetDefault(0.2);
     instance.SetVariation(0.2);
    // charm
    //TString version[NPOINTS] = {"2.22.9", "2.22.10", "2.22.11", "2.22.12", "2.22.13", "2.22.14", "2.22.15", "2.22.16", "2.22.17"};
    // beauty
    TString version[NPOINTS] = {"2.23.9", "2.23.10", "2.23.11", "2.23.12", "2.23.13", "2.23.14", "2.23.15", "2.23.16", "2.23.17"};
    instance.SetBinningFile("full");
    instance.SetOutputFileName("smearing_syst_gaus2_ET5_bin1");*/
/*
    // pt scan - 4.2 GeV
    const unsigned NPOINTS = 15;
    double  x[NPOINTS] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.9, 1.0};
    instance.SetXAxisTitle("track(p_{T}) cut, [GeV]");
    instance.SetDefault(0.5);
    instance.SetVariation(0.1);
    TString version[NPOINTS] = {"2.28.18", "2.28.17", "2.28.16", "2.28.15", "2.28.14", "2.28.13", "2.28.12", "2.28.19",  "2.28.20",  "2.28.21",  "2.28.22",  "2.28.23",  "2.28.24",  "2.28.25", "2.28.26"};
    instance.SetBinningFile("full.forCHARM");
    instance.SetOutputFileName("pt_scan_2.28.12-2.28.26_errors");
    instance.SetYears(".06e");
    instance.SetCNVersion("v06");
    instance.SetTrueYears(".true06e");
    instance.SetDrawOnlyErrors(true);
    instance.SetOutputPath("/data/zenith226a/libov/analysis/data/plots/10_30August2011/01_pt_scan_2.28");
*/

    // pt scan - 2 GeV
    const unsigned NPOINTS = 15;
    double  x[NPOINTS] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.9, 1.0};
    instance.SetXAxisTitle("track(p_{T}) cut, [GeV]");
    instance.SetDefault(0.5);
    instance.SetVariation(0.1);
    TString version[NPOINTS] = {"2.28.28", "2.28.29", "2.28.30", "2.28.31", "2.28.32", "2.28.33", "2.28.34", "2.28.35", "2.28.36", "2.28.37", "2.28.38", "2.28.39", "2.28.40", "2.28.41", "2.28.42"};
    instance.SetBinningFile("full.forCHARM.ET2.v2");
    instance.SetOutputFileName("pt_scan_2.28.28-2.28.42_errors");
    instance.SetYears(".06e");
    instance.SetCNVersion("v06");
    instance.SetTrueYears(".true06e");
    instance.SetDrawOnlyErrors(true);
    instance.SetOutputPath("/data/zenith226a/libov/analysis/data/plots/10_30August2011/02_pt_scan_2.28_2GeV");

    // --------------------------------------------------------------//
    // --------------------------------------------------------------//
    // --------------------------------------------------------------//

    // set number of points in the scan
    instance.SetNpoints(NPOINTS);

    // set necessary information
    instance.SetXArray(x);
    instance.SetVersionArray(version);
    
    instance.SetYaxisLowLimit(0);
    instance.SetYaxisUpLimit(0.2);

    //instance.SetOutputPath("/data/zenith226a/libov/analysis/other/quick_plot/smearing_syst/systematics/differential");
    //instance.SetOutputPath("/data/zenith226a/libov/analysis/other/quick_plot/smearing_syst/systematics");
    

    // initialize the object
    instance.Initialize();

    // do the drawing   
    instance.Draw();
    
    return  0;
}
