
#include <getopt.h>
#include <iostream>
using namespace std;

#include <TChain.h>
#include <TMath.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TROOT.h>
#include <TSystem.h>

#include <inc/TControlPlot.h>
#include <inc/normtype.h>

int main (int argc, char **argv) {

        // check if there are at least two arguments; if not, print help message
    if ( argc < 3 ) {
        cout<<"Please provide necessary parameters"<<endl;
        cout<<"usage:\n\t plotter <Binning File Suffix> <Histograms Version Ending> [<remark>]\n"<<endl;
        cout<<"Terminating, sorry."<<endl;
        exit(-1);
    }

        // welcome message
    cout<<"******************************************************"<<endl;
    cout<<"* Welcome to ZEUS Common Ntuple analysis framework   *"<<endl;
    cout<<"* Step 4: Visualizing the data                       *"<<endl;
    cout<<"* Input: root files with merged histograms           *"<<endl;
    cout<<"******************************************************"<<endl;

        // get suffix of the binning file
    TString        BinningFileSuffix = argv[1];

        // get histograms version
    TString        HistogramsVersionEnding = argv[2];

        // construct identifier to be passed to TControlPlot
    TString     HistogramsVersion=BinningFileSuffix + HistogramsVersionEnding;
    cout << "Histograms Version: " << HistogramsVersion << endl;

        // if 3rd argument is given, concatenate to the filename
    if (argc == 4) {
        TString    remark = argv[3];
        cout<<"remark: "<<remark<<endl;
        HistogramsVersion += remark;
    }

        // create an instance of TControlPlot
    TControlPlot *myPlots=new TControlPlot(HistogramsVersion);

    // specify what has to be plotted;
        // plots will appear in the same order they are added via AddPlotType
    // first agrument comes from TPlotMerger.cxx (?)
    // TODO: hardcoded now, should be changed to something more controllable (?)
        // (REMINDER: TControlPlot::AddPlotType(TString Name, Bool_t DrawHisto, Int_t MarkerStyle, Int_t MarkerSize, Int_t FillColor, Int_t LineColor, Int_t LineWidth))

    myPlots->AddPlotType("data", false, 20, 0.5, 0, 1, 0);
    myPlots->AddPlotType("mc", true, 0,0, kYellow, kBlack, 1);
    myPlots->AddPlotType("light", true, 0, 0, 0, kRed, 2);
    myPlots->AddPlotType("beauty", true, 0, 0, 0, kBlue, 2);
    myPlots->AddPlotType("charm", true, 0, 0, 0, kGreen, 2);
    myPlots->AddPlotType("beauty_resolved", true, 0, 0, 0, kBlue, 5);
    myPlots->AddPlotType("charm_resolved", true, 0, 0, 0, kGreen, 5);

        // buffers to contain 
    TString    Variables="";
    TString    VarSetName="";

    // 0: linear scale
    // 1: log scale
    Int_t        Lin3Log3[6]={0,0,0,1,1,1};
    Int_t        Lin6[6]={0,0,0,0,0,0};
    Int_t        Lin1Log1Lin4[6]={0,1,0,0,0,0};
    Int_t        Lin2Log2Lin2[6]={0,0,1,1,0,0};
    Int_t        Lin2Log1Lin3[6]={0,0,1,0,0,0};
    Int_t        Lin1Log2Lin3[6]={0,1,1,0,0,0};

    // standard control plots
    myPlots->AddAdvCanvas(1, 1, "zvtx", "zvtx:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "significance", "significance:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "significance_massbin1_mirrored", "significance_massbin1_mirrored:", Lin1Log1Lin4);
    myPlots->AddAdvCanvas(1, 1, "significance_massbin2_mirrored", "significance_massbin2_mirrored:", Lin1Log1Lin4);
    myPlots->AddAdvCanvas(1, 1, "significance_massbin3_mirrored", "significance_massbin3_mirrored:", Lin1Log1Lin4);
    myPlots->AddAdvCanvas(1, 1, "x_gamma_breit_jets", "x_gamma_breit_jets:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "x_gamma_breit_jets_charm_diff", "x_gamma_breit_jets_charm_diff:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "x_gamma_breit_jets_beauty_diff", "x_gamma_breit_jets_beauty_diff:", Lin6);

    myPlots->AddAdvCanvas(1, 1, "x_gamma_lab_jets_tagged", "x_gamma_lab_jets_tagged:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "x_gamma_lab_jets_tagged_charm_diff", "x_gamma_lab_jets_tagged_charm_diff:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "x_gamma_lab_jets_tagged_beauty_diff", "x_gamma_lab_jets_tagged_beauty_diff:", Lin6);

    myPlots->AddAdvCanvas(1, 1, "kt_etajet_b", "kt_etajet_b:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "kt_etajet_b_charm_diff", "kt_etajet_b_charm_diff:", Lin6);
    myPlots->AddAdvCanvas(1, 1, "kt_etajet_b_beauty_diff", "kt_etajet_b_beauty_diff:", Lin6);

    // perform drawing and store to file
    myPlots->Draw();

    return 0;
}



    // inclusive plots (no c/b enrichment)

// 
//     Variables="q2da:siecorr:thetael:phiel:";
//     VarSetName="002_cplots_dis_part2";
//     myPlots->AddAdvCanvas(2,2,VarSetName,Variables,AllLin);
// 
//     Variables="kt_etjet_b:kt_etajet_b:kt_etjet_b:kt_phijet_b:";
//     VarSetName="003_cplots_jets";
//     myPlots->AddAdvCanvas(2,2,VarSetName,Variables,bla2);
// 
//     Variables="significance_massbin1:significance_massbin2:significance_massbin3:significance_massbin1:significance_massbin2:significance_massbin3:";
//     VarSetName="14_secvtx_significance";
//     myPlots->AddAdvCanvas(3,2,VarSetName,Variables,Logs);
// 
//     Variables="significance_massbin1_mirrored:significance_massbin2_mirrored:significance_massbin3_mirrored:significance_massbin1_mirrored:significance_massbin2_mirrored:significance_massbin3_mirrored:";
//     VarSetName="14_secvtx_significance_mirrored";
//     myPlots->AddAdvCanvas(3,2,VarSetName,Variables,Logs);
// 
//     Variables="kt_etjet_b:kt_masjet_b:kt_etajet_b:kt_etjet_b:kt_masjet_b:kt_etajet_b:";
//     VarSetName="10_jetsb";
//     myPlots->AddAdvCanvas(3,2,VarSetName,Variables,Logs);
// 
//     Variables="significance:significance:";
//     VarSetName="unmirrored_significance";
//     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,bla);
// 
//     // enriched plots

    // charm
/*    myPlots->AddAdvCanvas(3,2,"charm_enriched1","q2da_charm_diff:xda_charm_diff:yel_charm_diff:yjb_charm_diff:zvtx_charm_diff:empz_charm_diff:", Lin6);*/
/*
    Variables="kt_etjet_b_charm_diff:kt_etajet_b_charm_diff:kt_etjet_b_charm_diff:kt_phijet_b_charm_diff:";
    VarSetName="charm_enriched2";
    myPlots->AddAdvCanvas(2,2,VarSetName,Variables,bla2);


    // beauty
    Variables="q2da_beauty_diff:xda_beauty_diff:yel_beauty_diff:yjb_beauty_diff:zvtx_beauty_diff:empz_beauty_diff:";
    VarSetName="beauty_enriched1";
    myPlots->AddAdvCanvas(3,2,VarSetName,Variables,AllLin);

    Variables="kt_etjet_b_beauty_diff:kt_etajet_b_beauty_diff:kt_etjet_b_beauty_diff:kt_phijet_b_beauty_diff:";
    VarSetName="beauty_enriched2";
    myPlots->AddAdvCanvas(2,2,VarSetName,Variables,bla2);



        // some plots for testing - the most relevant for the results
        // unmirrored siginficance
    Variables="significance:significance:";
    VarSetName="test01_significance_unmirrored";
    myPlots->AddAdvCanvas(1,2,VarSetName,Variables,bla);*/





    // charm vertex multiplicity
//     Variables="vtxsec_multi_charm_diff:vtxsec_multi_charm_diff:";
//     VarSetName="charm_multi";
//     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,bla);

    // beauty vertex multiplicity
//     Variables="vtxsec_multi_beauty_diff:vtxsec_multi_beauty_diff:";
//     VarSetName="beauty_multi";
//     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,bla);

     /*Variables="kt_etjet_b:kt_etjet_b:";
     VarSetName="et_jet";
     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,bla);*/


/*
    Variables="vtxsec_mass:vtxsec_multi:vtxsec_mass:vtxsec_chi2ndf:";
    VarSetName="004_cplots_vertex";
    myPlots->AddAdvCanvas(2,2,VarSetName,Variables,bla3);

    Variables="vtxsec_mass_charm_diff:vtxsec_multi_charm_diff:vtxsec_chi2ndf_charm_diff:vtxsec_multi_charm_diff:";
    VarSetName="charm_enriched3";
    myPlots->AddAdvCanvas(2,2,VarSetName,Variables,bla1);

    Variables="vtxsec_mass_beauty_diff:vtxsec_multi_beauty_diff:vtxsec_mass_beauty_diff:vtxsec_multi_beauty_diff:";
    VarSetName="beauty_enriched3";
    myPlots->AddAdvCanvas(2,2,VarSetName,Variables,bla1);*/


// 
// 

//     Variables="significance:";
//     VarSetName="02_significance";
//     myPlots->AddAdvCanvas(1,1,VarSetName,Variables,AllLin);


//         Variables="vtxsec_mass_charm_diff:vtxsec_multi_charm_diff:";
//     VarSetName="001_charm";
//     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,AllLin);
// 
//         Variables="vtxsec_mass_beauty_diff:vtxsec_multi_beauty_diff:";
//     VarSetName="002_beauty";
//     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,AllLin);
// 
//         Variables="vtxsec_mass:vtxsec_multi:";
//     VarSetName="003_inclusive";
//     myPlots->AddAdvCanvas(1,2,VarSetName,Variables,AllLin);
/*
     myPlots -> AddAdvCanvas(1, 2, "01_et_jet_b", "kt_etjet_b:kt_etjet_b:", Lin1Log1Lin4);
     myPlots -> AddAdvCanvas(1, 2, "02_et_jet_b_charm", "kt_etjet_b_charm_diff:kt_etjet_b_charm_diff:", Lin1Log1Lin4);
     myPlots -> AddAdvCanvas(1, 2, "02_et_jet_b_beauty", "kt_etjet_b_beauty_diff:kt_etjet_b_beauty_diff:", Lin1Log1Lin4);

     myPlots -> AddAdvCanvas(1, 2, "01_eta_jet_b", "kt_etajet_b:kt_etajet_b:", Lin1Log1Lin4);
     myPlots -> AddAdvCanvas(1, 2, "02_eta_jet_b_charm", "kt_etajet_b_charm_diff:kt_etajet_b_charm_diff:", Lin1Log1Lin4);
     myPlots -> AddAdvCanvas(1, 2, "02_eta_jet_b_beauty", "kt_etajet_b_beauty_diff:kt_etajet_b_beauty_diff:", Lin1Log1Lin4);

//     myPlots -> AddAdvCanvas(1,1,"03_trackpT","track_vtx_pT:", Lin6);

    // significance in the mass bins
    myPlots->AddAdvCanvas(3,2,"significance_massbins_mirrored", "significance_massbin1_mirrored:significance_massbin2_mirrored:significance_massbin3_mirrored:significance_massbin1_mirrored:significance_massbin2_mirrored:significance_massbin3_mirrored:", Lin3Log3);

    myPlots->AddAdvCanvas(3,2,"significance_massbins", "significance_massbin1:significance_massbin2:significance_massbin3:significance_massbin1:significance_massbin2:significance_massbin3:", Lin3Log3);
    
    // x gamma 
     myPlots -> AddAdvCanvas(1,1,"x_gamma_1","x_gamma_1:", Lin6);

     myPlots -> AddAdvCanvas(1,1,"x_gamma_2","x_gamma_2:", Lin6);


    myPlots->AddAdvCanvas(2, 2, "02_dis", "zvtx:empz:yel:yjb:", Lin6);
*/
