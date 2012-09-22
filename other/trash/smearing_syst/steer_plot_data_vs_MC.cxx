steer_plot_data_vs_MC_eta () {

    gROOT->ProcessLine(" .L plot_data_vs_MC.cxx+");

    TCanvas * c1 = new TCanvas ();
    c1 -> Divide(3,2); 
    
    c1 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(2)");
    c1 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(3)");
    c1 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(4)");
    c1 -> cd(4);
    gROOT->ProcessLine("plot_data_vs_MC(5)");
    c1 -> cd(5);
    gROOT->ProcessLine("plot_data_vs_MC(6)");
    c1 -> cd(6);
    gROOT->ProcessLine("plot_data_vs_MC(7)");

    TCanvas * c2 = new TCanvas ();
    c2 -> Divide(3,2); 
    
    c2 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(8)");
    c2 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(9)");
    c2 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(10)");
    c2 -> cd(4);
    gROOT->ProcessLine("plot_data_vs_MC(11)");
    c2 -> cd(5);
    gROOT->ProcessLine("plot_data_vs_MC(12)");
}

steer_plot_data_vs_MC_et () {

    gROOT->ProcessLine(" .L plot_data_vs_MC.cxx+");

    TCanvas * c1 = new TCanvas ();
    c1 -> Divide(2,2); 
    
    c1 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(14)");
    c1 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(15)");
    c1 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(16)");
    c1 -> cd(4);
    gROOT->ProcessLine("plot_data_vs_MC(17)");

    TCanvas * c2 = new TCanvas ();
    c2 -> Divide(2,2); 
    
    c2 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(18)");
    c2 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(19)");
    c2 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(20)");
}

steer_plot_data_vs_MC_x () {

    gROOT->ProcessLine(" .L plot_data_vs_MC.cxx+");

    TCanvas * c1 = new TCanvas ();
    c1 -> Divide(2,2); 
    
    c1 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(31)");
    c1 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(32)");
    c1 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(33)");
    c1 -> cd(4);
    gROOT->ProcessLine("plot_data_vs_MC(34)");

    TCanvas * c2 = new TCanvas ();
    c2 -> Divide(2,2); 
    
    c2 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(35)");
    c2 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(36)");
}

steer_plot_data_vs_MC_q2 () {

    gROOT->ProcessLine(" .L plot_data_vs_MC.cxx+");

    TCanvas * c1 = new TCanvas ();
    c1 -> Divide(2,2); 
    
    c1 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(38)");
    c1 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(39)");
    c1 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(40)");
    c1 -> cd(4);
    gROOT->ProcessLine("plot_data_vs_MC(41)");

    TCanvas * c2 = new TCanvas ();
    c2 -> Divide(2,2); 
    
    c2 -> cd(1);
    gROOT->ProcessLine("plot_data_vs_MC(42)");
    c2 -> cd(2);
    gROOT->ProcessLine("plot_data_vs_MC(43)");
    c2 -> cd(3);
    gROOT->ProcessLine("plot_data_vs_MC(44)");
    c2 -> cd(4);
    gROOT->ProcessLine("plot_data_vs_MC(45)");
}