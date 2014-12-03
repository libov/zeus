int main()
{
TChain *myChain=new TChain("resonance");
myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_0.root");
myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_1.root");
myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_2.root");
myChain->Add("/data/zenith226a/libov/data/2007pRP/v0_mini07pRP_3.root");



	Int_t		Trk_nvert,
			Vtx_id[120],
			Vtx_prim[120];
	Float_t		Vtx_x[120],
			Vtx_y[120],
			Vtx_z[120],
			Xvtx,
			Yvtx,
			Zvtx;
//Trk_vert
myChain->SetBranchAddress("Trk_nvert",&Trk_nvert);
myChain->SetBranchAddress("Vtx_id",Vtx_id);
myChain->SetBranchAddress("Vtx_prim",Vtx_prim);
myChain->SetBranchAddress("Vtx_x",Vtx_x);
myChain->SetBranchAddress("Vtx_y",Vtx_y);
myChain->SetBranchAddress("Vtx_z",Vtx_z);

myChain->SetBranchAddress("Xvtx",&Xvtx);
myChain->SetBranchAddress("Yvtx",&Yvtx);
myChain->SetBranchAddress("Zvtx",&Zvtx);

int nevents=myChain->GetEntries();
cout<<nevents<<" events in this chain"<<endl;
for (int j=0;j<nevents;j++)
{
	myChain->GetEntry(j);
	//cout<<"event "<<j<<endl;
	for (int k=0;k<Trk_nvert;k++)
	{
		if (Vtx_prim[k]!=1) continue;
		//cout<<Vtx_x[k]<<" "<<Vtx_y[k]<<" "<<Vtx_z[k]<<endl;
	}
	//cout<<Xvtx<<" "<<Yvtx<<" "<<Zvtx<<" vertex"<<endl;

}

return 0;
}