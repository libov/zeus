int plot_compare_to_paper(TString dataset="v06_0607p_charm_1_5GeV2") {

    gROOT -> SetStyle("Plain");
    TString PLOTS_PATH = getenv("PLOTS_PATH");
    // open file with histograms (result of hadronic_correctins application)
    TFile * input = new TFile (PLOTS_PATH+"/"+dataset+"_max_0_partons"+".root", "read");

    // retrieve histograms
    TH1F * chad_et = (TH1F*) input -> Get("chad_et");
    TH1F * chad_eta = (TH1F*) input -> Get("chad_eta");
    TH1F * chad_q2 = (TH1F*) input -> Get("chad_q2");
    TH1F * chad_x = (TH1F*) input -> Get("chad_x");
    TH1F * chad_x_q2bin1 = (TH1F*) input -> Get("chad_x_q2bin1");
    TH1F * chad_x_q2bin2 = (TH1F*) input -> Get("chad_x_q2bin2");
    TH1F * chad_x_q2bin3 = (TH1F*) input -> Get("chad_x_q2bin3");
    TH1F * chad_x_q2bin4 = (TH1F*) input -> Get("chad_x_q2bin4");
    TH1F * chad_x_q2bin5 = (TH1F*) input -> Get("chad_x_q2bin5");

    TH1F * chad_et_paper = (TH1F*) input -> Get("chad_et_paper");
    TH1F * chad_eta_paper = (TH1F*) input -> Get("chad_eta_paper");
    TH1F * chad_q2_paper = (TH1F*) input -> Get("chad_q2_paper");
    TH1F * chad_x_paper = (TH1F*) input -> Get("chad_x_paper");
    TH1F * chad_x_q2bin1_paper = (TH1F*) input -> Get("chad_x_q2bin1_paper");
    TH1F * chad_x_q2bin2_paper = (TH1F*) input -> Get("chad_x_q2bin2_paper");
    TH1F * chad_x_q2bin3_paper = (TH1F*) input -> Get("chad_x_q2bin3_paper");
    TH1F * chad_x_q2bin4_paper = (TH1F*) input -> Get("chad_x_q2bin4_paper");
    TH1F * chad_x_q2bin5_paper = (TH1F*) input -> Get("chad_x_q2bin5_paper");

    TH1F * part_npartons = (TH1F*) input -> Get ("part_npartons");

    // draw and store to eps files
    TCanvas * c_corr = new TCanvas();
    c_corr -> Divide(2,2);

    c_corr -> cd (1);
    chad_et -> SetAxisRange(0, 1.4, "Y");
    chad_et -> Draw();

    c_corr -> cd (2);
    chad_eta -> SetAxisRange(0, 1.4, "Y");
    chad_eta -> Draw();

    c_corr -> cd (3);
    chad_q2 -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_q2 -> Draw();

    c_corr -> cd (4);
    chad_x -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_x -> Draw();

    // draw also corrections from the paper
    c_corr -> cd (1);
    chad_et_paper -> SetLineColor(kRed);
    chad_et_paper -> Draw("same");

    c_corr -> cd (2);
    chad_eta_paper -> SetLineColor(kRed);
    chad_eta_paper -> Draw("same");

    c_corr -> cd (3);
    chad_q2_paper -> SetLineColor(kRed);
    chad_q2_paper -> Draw("same");

    c_corr -> cd (4);
    chad_x_paper -> SetLineColor(kRed);
    chad_x_paper -> Draw("same");

    c_corr -> Print(PLOTS_PATH+"/"+dataset+"_corr.eps");

    TCanvas * c_corr_ddiff = new TCanvas();
    c_corr_ddiff -> Divide(3,2);

    c_corr_ddiff -> cd (1);
    chad_x_q2bin1 -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_x_q2bin1 -> Draw();
    chad_x_q2bin1_paper -> SetLineColor(kRed);
    chad_x_q2bin1_paper -> Draw("same");

    c_corr_ddiff -> cd (2);
    chad_x_q2bin2 -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_x_q2bin2 -> Draw();
    chad_x_q2bin2_paper -> SetLineColor(kRed);
    chad_x_q2bin2_paper -> Draw("same");

    c_corr_ddiff -> cd (3);
    chad_x_q2bin3 -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_x_q2bin3 -> Draw();
    chad_x_q2bin3_paper -> SetLineColor(kRed);
    chad_x_q2bin3_paper -> Draw("same");

    c_corr_ddiff -> cd (4);
    chad_x_q2bin4 -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_x_q2bin4 -> Draw();
    chad_x_q2bin4_paper -> SetLineColor(kRed);
    chad_x_q2bin4_paper -> Draw("same");

    c_corr_ddiff -> cd (5);
    chad_x_q2bin5 -> SetAxisRange(0, 1.4, "Y");
    gPad -> SetLogx();
    chad_x_q2bin5 -> Draw();
    chad_x_q2bin5_paper -> SetLineColor(kRed);
    chad_x_q2bin5_paper -> Draw("same");

    c_corr_ddiff -> Print(PLOTS_PATH+"/"+dataset+"_corr_ddiff.eps");

    TCanvas * c_npartons = new TCanvas();
    part_npartons -> Draw();
    c_npartons -> Print(PLOTS_PATH+"/"+dataset+"_npartons.eps");

    return 0;
}