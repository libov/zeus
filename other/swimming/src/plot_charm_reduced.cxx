//#include <TROOT.h>

// custom headers
#include<TCharmMeasurement.h>
#include<TMultiCanvas.h>

int main(int argc, char **argv) {

    // read input data
    TCharmMeasurement combination("charm_data/kl_paper_v3.out", "HERA", 1);
    TCharmMeasurement dplus("charm_data/dplus.dat", "ZEUS D^{+} 354 pb^{-1}", 2);
    TCharmMeasurement dstar("charm_data/dstarhera2_forplot.dat", "ZEUS D* 363 pb^{-1}", 3);
    TCharmMeasurement vtx("charm_data/zeus_vtx.dat", "ZEUS vtx 354 pb^{-1}", 2);

    TMultiCanvas plot(7);

    plot.PlotData(vtx, 0.0, 20, 1, kBlack, true, true);

    plot.PlotData(dstar, -0.025, 26, 1, kMagenta, true, true);
    plot.PlotData(dstar, -0.025, 26, 1, kMagenta, false, false);

    plot.PlotData(dplus, 0.0, 25, 1, kBlue, true, true);
    plot.PlotData(dplus, 0.0, 25, 1, kBlue, false, false);

    plot.PlotData(combination, 0.025, 24, 1, kRed, true, true);
    plot.PlotData(combination, 0.025, 24, 1, kRed, false, false);

    plot.PlotData(vtx, 0.0, 20, 1, kBlack, true, false);
    plot.PlotData(vtx, 0.0, 20, 0.5, kBlack, false, false); // smaller point size so that error bars are still drawn when smaller than the marker

    plot.Print("Sigma_Reduced_Charm.eps");

    return 0;
}
