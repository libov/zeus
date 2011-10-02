int generator () {

	TH1F * h = new TH1F ("", "", 100, -2, 20);
	TRandom3 rnd;
	for (int i=0; i< 10000000; i++){	
		float k = rnd.Rndm();
		float l = -TMath::Log(k);
		h -> Fill(l);
	}
	h -> Draw();
	return 0;
}
