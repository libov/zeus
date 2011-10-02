int basic() {

	TH1F* h1 = new TH1F("h1","z distribution",20000,-10,10);
	TH2F* h2 = new TH2F("h2","y vs x",20000,-25,25,20000,-25,25);

	h2 -> Draw();

        return 0;
}


	
