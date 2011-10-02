void histotest() {

	TH2F * h1 = new TH2F("h1","", 10, 0, 10, 10, 0, 10);
	h1 -> Fill(5, 5);
	h1 -> Draw();
}
