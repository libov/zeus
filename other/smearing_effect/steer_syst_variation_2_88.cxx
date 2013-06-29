void steer_syst_variation_2_88() {

	// load the script
	gROOT->ProcessLine(" .L significance_data_to_mc.cxx");

	// produce scripts
	significance_data_to_mc("2.88.3");
	significance_data_to_mc("2.88.5");
	significance_data_to_mc("2.88.7");
	significance_data_to_mc("2.88.9");
	significance_data_to_mc("2.88.13");
	significance_data_to_mc("2.88.16");

	// quit ROOT
	gROOT->ProcessLine(".q");

}
