void steer(TString version = "2.52.2") {

	// load the script
	gROOT->ProcessLine(" .L significance_data_to_mc.cxx");

	// execute it
	for (int i=1; i<=63; i++) {
		TString bin = "bin";
		bin += i;
		significance_data_to_mc(version, bin);
	}

	// quit ROOT
	gROOT->ProcessLine(".q");

}
