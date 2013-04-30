//#include <TROOT.h>

// custom headers
#include<TCharmMeasurement.h>
#include<TMultiCanvas.h>

int main(int argc, char **argv) {

    // read input data
    TCharmMeasurement combination("charm_data/kl_paper_v3.out", "HERA", 1);
    TCharmMeasurement dplus("charm_data/dplus.dat", "ZEUS D^{+} 354 pb^{-1}", 2);
    TCharmMeasurement dstar("charm_data/dstarhera2_forplot.dat", "ZEUS D* 363 pb^{-1}", 3);
    TCharmMeasurement vtx("charm_data/zeus_vtx.dat", "this analysis", 2);

    TMultiCanvas plot(7);

    plot.PlotData(combination, 0.025, 24, 1, kRed, true);
    plot.PlotData(combination, 0.025, 24, 1, kRed, false);

    plot.PlotData(dplus, 0.0, 25, 1, kBlue, true);
    plot.PlotData(dplus, 0.0, 25, 1, kBlue, false);

    plot.PlotData(dstar, -0.025, 20, 1, kBlack, true);
    plot.PlotData(dstar, -0.025, 20, 1, kBlack, false);

    plot.PlotData(vtx, 0.0, 21, 0.7, kMagenta, true);
    plot.PlotData(vtx, 0.0, 21, 0.7, kMagenta, false);

    plot.Print("sigma_red.eps");

    return 0;
}
