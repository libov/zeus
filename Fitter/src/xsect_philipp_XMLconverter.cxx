// ROOT includes
#include <TFile.h>
#include <TKey.h>

// system includes
#include <iostream>
using namespace std;

// my includes
#include <inc/TMyFitter.h>
#include <TDataset.h>
#include <TSubSet.h>
#include <TCrossSection.h>
#include <TCrossSectionBin.h>

// everything should be ok if this does not crash:
TCrossSection   cCrossSection("binning.full.xml");


void    set_cross_sections(const unsigned n_bins, const unsigned first_bin_id, Double_t * sigma, Double_t   * sigma_err) {
    cout << "in set cross sections " << first_bin_id << " " << n_bins << endl;
    Int_t     counter = first_bin_id;
    for (int i = 0; i < n_bins; i++) {
        // get TCrossSectionBin object by id
        TCrossSectionBin cBin = cCrossSection.getCrossSectionBin(counter);
        cBin.set_sigma_b(sigma[i]);
        cBin.set_sigma_b_err(sigma_err[i]);

        cCrossSection.modifyCrossSectionBin(counter, cBin);
        counter++;
    }
}

int main(int argc, char **argv) {


    // number of bins in each diff cros section
    const unsigned    n_bins_et = 7;
    const unsigned    n_bins_eta = 10;
    const unsigned    n_bins_phi = 8;
    const unsigned    n_bins_q2 = 8;
    const unsigned    n_bins_x = 6;

    // first bin id in the XML file
    const unsigned    first_bin_id_et = 13;
    const unsigned    first_bin_id_eta = 2;
    const unsigned    first_bin_id_phi = 21;
    const unsigned    first_bin_id_q2 = 37;
    const unsigned    first_bin_id_x = 30;

    // http://www-zeus.desy.de/~roloff/for_slava/new/Cross_Sections_Et.txt
    Double_t    et_b[n_bins_et] = {156.153,79.3434,28.8692,11.3802,4.41399,1.85859,0.358242};
    Double_t    et_b_err[n_bins_et] = {23.3583,5.33797,1.73777,0.7814,0.469572,0.239675,0.083076};

    // http://www-zeus.desy.de/~roloff/for_slava/new/Cross_Sections_Eta.txt
    Double_t    eta_b[n_bins_eta] = {96.3955,248.813,209.092,300.433,300.018,357.324,313.877,298.98,227.274,176.006};
    Double_t    eta_b_err[n_bins_eta] = {29.0794,30.077,23.154,21.8377,22.0924,23.7446,25.3962,29.4869,39.209,57.1886};

    // http://www-zeus.desy.de/~roloff/for_slava/new/Cross_Sections_Phi.txt
    Double_t    phi_b[n_bins_phi] = {121.31,131.886,126.103,143.433,156.223,149.16,152.667,144.923};
    Double_t    phi_b_err[n_bins_phi] = {14.4113,14.5248,12.0092,15.847,19.0881,12.8271,11.0807,13.0329};

    // http://www-zeus.desy.de/~roloff/for_slava/new/Cross_Sections_Q2.txt
    Double_t   q2_b[n_bins_q2] = {47.6242,20.6352,8.25459,4.19245,1.28041,0.718438,0.144805,0.0165757};
    Double_t   q2_b_err[n_bins_q2] = {4.11893,1.6618,0.728177,0.363648,0.144553,0.0654863,0.0168996,0.00327751};

    // http://www-zeus.desy.de/~roloff/for_slava/new/Cross_Sections_x.txt
    Double_t   x_b[n_bins_x] = {710278,689577,236999,53934.1,11882.5,376.205};
    Double_t   x_b_err[n_bins_x] = {114414,45291.3,13908.9,3368.26,1247.4,71.3737};

    // finally, modify the files
    set_cross_sections(n_bins_et, first_bin_id_et, et_b, et_b_err);
    set_cross_sections(n_bins_eta, first_bin_id_eta, eta_b, eta_b_err);
    set_cross_sections(n_bins_phi, first_bin_id_phi, phi_b, phi_b_err);
    set_cross_sections(n_bins_q2, first_bin_id_q2, q2_b, q2_b_err);
    set_cross_sections(n_bins_x, first_bin_id_x, x_b, x_b_err);

    cCrossSection.WriteXMLfile("results_Philipp_ET5.xml");

    return 0;
}

    
