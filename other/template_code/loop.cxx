// ROOT headers
#include <TChain.h>
#include <TH1F.h>

// system headers
#include <iostream>

int loop () {

    // create a "chain" - an object that will contain all the ROOT files ("ntuples") we want to analyze
    TChain  * fChain = new TChain ("orange");

    // add those files we want to analyze
    fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.acpx424.f13695.rgap3.nc.ccdir.p.q2g4.205.root");
    fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.fcpx424.f13695.rgap3.nc.ccdir.p.q2g4.208.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.fcpx424.f13695.rgap3.nc.ccdir.p.q2g4.213.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.192.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.193.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.194.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.195.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.196.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.197.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.198.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.207.root");
//     fChain -> Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.hcpx424.f13695.rgap3.nc.ccdir.p.q2g4.209.root");

    // calculate number of events (entries) in this set of files
    unsigned   Nevents = fChain -> GetEntries ();
    cout << Nevents << " in this chain " << endl;

    // also have to create some variables which will hold information from ntuples
    // for available variables see http://www-zeus.desy.de/ZEUS_ONLY/analysis/orange/release.notes/orange_ntuple.v2009a.html

    // this disables all branches; later we enable only the neccessary ones, and
    // don't process others; this saves the CPU time
    fChain->SetBranchStatus("*", 0);

    // declare a variable
    Float_t     Siq2da[15];
    // enable the branch and "connect" it to our local variable declared above
    fChain -> SetBranchAddress("Siq2da", Siq2da);
    fChain -> SetBranchStatus("Siq2da", 1);

    // create a histogram - for graphical visualization
    TH1F * histo_q2da = new TH1F ("h1", "Q^{2} distribution (double-angle method)", 100, 0, 1000);
    histo_q2da -> SetXTitle ("Q^{2}_{da}, GeV");

    // loop over those events
    for (unsigned i = 0; i < Nevents; i++) {
        // "get" an entry, i.e. fill the variables which were connected to branches above for the current event
        fChain -> GetEntry(i);
        // fill this variable to the histogram
        histo_q2da -> Fill(Siq2da[0]);
    }

    // now draw the histogram
    histo_q2da -> Draw();

    return 0;
}
