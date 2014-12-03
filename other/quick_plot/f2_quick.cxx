int f2_quick(){

    TCanvas c;

    // Massimo
    unsigned n1 = 6;
    Float_t x1[10]={0.00022, 0.00032, 0.00050, 0.00080, 0.00150, 0.00300};
    Float_t y1[10]={0.24104, 0.22013, 0.19314, 0.16597, 0.13332, 0.10180};
    TGraph * g1 = new TGraph (n1, x1, y1);
    g1->Draw("apl");
    g1->SetLineColor(kBlue);
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kBlue);
    (g1 -> GetHistogram()) -> SetAxisRange(0, 0.3,"Y");
    (g1 -> GetHistogram()) -> Draw();
    g1->Draw("samep");


    // Slava
    unsigned n2 = 5;
    Float_t x2[10]={0.0002, 0.00043, 0.00065, 0.001, 0.002};
    Float_t y2[10]={0.257402, 0.203322, 0.17797, 0.152785, 0.119929};
    TGraph * g2 = new TGraph (n2, x2, y2);
    g2->Draw("psame");
    g2->SetLineColor(kRed);
    g2->SetMarkerStyle(20);
    g2->SetMarkerColor(kRed);


    TLegend * l = new TLegend (0.5, 0.7, 0.7, 0.9);
    l -> SetHeader("Q^{2}=12 GeV^{2}");
    l -> AddEntry (g1, "Massimo", "l");
    l -> AddEntry (g2, "Slava", "l");
    l -> Draw();

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c.Print(PLOTS_PATH+"/f2_quick.eps");

    return 0;
}

int f2_quick_same_grid () {

    TCanvas c;
    c.Divide (2,3);
    const unsigned N_Q2 = 5;


    unsigned n[N_Q2];
    Float_t q2[N_Q2];
    Float_t x[N_Q2][10];
    Float_t f2_slava[N_Q2][10];
    Float_t f2_massimo[N_Q2][10];

    // 1st q2 point
    n[0] = 5;
    q2[0] = 2.5;
    x[0][0]=0.00003;
    x[0][1]=0.00007;
    x[0][2]=0.00013;
    x[0][3]=0.00018;
    x[0][4]=0.00035;

    f2_massimo[0][0] = 0.09659;
    f2_massimo[0][1] = 0.07990;
    f2_massimo[0][2] = 0.06748;
    f2_massimo[0][3] = 0.06157;
    f2_massimo[0][4] = 0.05077;

    f2_slava[0][0] = 0.0960349;
    f2_slava[0][1] = 0.0801324;
    f2_slava[0][2] = 0.0678521;
    f2_slava[0][3] = 0.0611367;
    f2_slava[0][4] = 0.0499133;

    // 2nd q2 point
    n[1] = 4;
    q2[1] = 5.0;
    x[1][0]=0.00007;
    x[1][1]=0.00018;
    x[1][2]=0.00035;
    x[1][3]=0.00100;

    f2_massimo[1][0] = 0.15564;
    f2_massimo[1][1] = 0.12481;
    f2_massimo[1][2] = 0.10272;
    f2_massimo[1][3] = 0.07322;

    f2_slava[1][0] = 0.155467;
    f2_slava[1][1] = 0.124508;
    f2_slava[1][2] = 0.103222;
    f2_slava[1][3] = 0.0728377;

    // 3rd q2 point
    n[2] = 2;
    q2[2] = 200;
    x[2][0]=0.00500;
    x[2][1]=0.01300;

    f2_massimo[2][0] = 0.25467;
    f2_massimo[2][1] = 0.14731;

    f2_slava[2][0] = 0.254773;
    f2_slava[2][1] = 0.147584;

    // 4th q2 point
    n[3] = 2;
    q2[3] = 350;
    x[3][0]=0.01;
    x[3][1]=0.025;

    f2_massimo[3][0] = 0.18994;
    f2_massimo[3][1] = 0.09668;

    f2_slava[3][0] = 0.190034;
    f2_slava[3][1] = 0.0969699;

    // 5th q2 point
    n[4] = 2;
    q2[4] = 650;
    x[4][0]=0.013;
    x[4][1]=0.032;

    f2_massimo[4][0] = 0.16976;
    f2_massimo[4][1] = 0.08169;

    f2_slava[4][0] = 0.169821;
    f2_slava[4][1] = 0.0819446;

    // now draw
    for (int i = 0; i<N_Q2; i++) {
        TGraph * g_massimo = new TGraph(n[i], x[i], f2_massimo[i]);
        TGraph * g_slava = new TGraph(n[i], x[i], f2_slava[i]);
        c.cd(i+1);
        g_massimo -> Draw("ap");
        g_slava -> Draw("psame");
        g_massimo -> SetMarkerStyle(20);
        g_slava -> SetMarkerStyle(20);
        g_slava -> SetMarkerColor(kRed);
        g_massimo -> SetMarkerSize(0.5);
        g_slava -> SetMarkerSize(0.5);


        TLegend * l = new TLegend (0.5, 0.7, 0.7, 0.9);
        TString header = "Q^{2}=";
        header+=q2[i];
        header+=" GeV^{2}";
        l -> SetHeader(header);
        l -> AddEntry (g_massimo, "Massimo", "p");
        l -> AddEntry (g_slava, "Slava", "p");
        l -> Draw();

        cout << "\nq2= " << q2[i] << endl;
        for (int j=0; j< n[i]; j++) cout << "(slava-massimo)/massimo= " << (f2_slava[i][j]-f2_massimo[i][j])/f2_massimo[i][j] << endl;

    }

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c.Print(PLOTS_PATH+"/f2_quick_same_grid.eps");
}

int f2_meas_ABKM_vs_HERAPDF () {

    TCanvas  * c =new TCanvas();

    const unsigned N_POINTS = 18;
    Float_t x[N_POINTS];
    Float_t y_ABKM[N_POINTS] = {0.216664, 0.212259, 0.247826, 0.236396, 0.560154, 0.431722, 0.307311, 0.22951, 0.195669, 0.383002, 0.335127, 0.240066, 0.21136, 0.438824, 0.196624, 0.153832, 0.246463, 0.0779024};
    Float_t y_HERAPDF[N_POINTS] = {0.216339, 0.211554, 0.246958, 0.232257, 0.562195, 0.426262, 0.304719, 0.229239, 0.190007, 0.383709, 0.332492, 0.240955, 0.208374, 0.439009, 0.197231, 0.151576, 0.247712, 0.0789746};
    
    for (int i=0; i<N_POINTS; i++) {
        x[i] = i+1;
    }

    TGraph * g_ABKM = new TGraph (N_POINTS, x, y_ABKM);
    TGraph * g_HERAPDF = new TGraph (N_POINTS, x, y_HERAPDF);

    g_ABKM -> SetMarkerStyle(20);
    g_HERAPDF -> SetMarkerStyle(20);

    g_ABKM -> SetMarkerColor(kRed);
    g_HERAPDF -> SetMarkerColor(7);

    g_ABKM -> Draw("ap");
    g_HERAPDF -> Draw("psame");

    TString PLOTS_PATH = getenv("PLOTS_PATH");
    c->Print(PLOTS_PATH +"/f2_meas_ABKM_vs_HERAPDF.eps");
}

