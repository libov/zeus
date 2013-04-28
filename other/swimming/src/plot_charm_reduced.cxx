//#include <TROOT.h>

// custom headers
#include<TCharmMeasurement.h>
#include<TMultiCanvas.h>

int main(int argc, char **argv) {

    // read input data
    TCharmMeasurement combination("charm_data/kl_paper_v3_ucost.out", 1);
    TCharmMeasurement dplus("charm_data/dplus.dat", 2);
    TCharmMeasurement dstar("charm_data/dstarhera2_forplot.dat", 3);
    TCharmMeasurement vtx("charm_data/zeus_vtx.dat", 2);

    TMultiCanvas plot(7);

    plot.PlotData(combination, 0.0, 24, 1, kRed, true);
    plot.PlotData(combination, 0.0, 24, 1, kRed, false);

    plot.PlotData(dplus, 0.0, 25, 1, kBlue, true);
    plot.PlotData(dplus, 0.0, 25, 1, kBlue, false);

    plot.PlotData(dstar, -0.0, 20, 1, kBlack, true);
    plot.PlotData(dstar, -0.0, 20, 1, kBlack, false);

    plot.PlotData(vtx, 0.0, 21, 0.7, kMagenta, true);
    plot.PlotData(vtx, 0.0, 21, 0.7, kMagenta, false);

    plot.Print("sigma_red.eps");

    return 0;
}
