//-------------------------------------------------//
// A template code for common ntuples analysis     //
// Libov Vladyslav										   //
// 21.07.2009													//
//-------------------------------------------------//

int main()
{
		// declare variables
		Int_t			nevents=0,
						Nv0lite=0;


		TChain *myChain=new TChain("orange");		// declare chain of files (trees)
		myChain->Add("*.root");							// add files to the chain

		// Specify which variables you want to read from your tree (chain)
		myChain->SetBranchAddress("Nv0lite",&Nv0lite);			// this is number of V0 particles
																				// candidates found in particular
																				// event (i.e. in ep-interaction
																				// 				final state)
		// Get number of events
		nevents=myChain->GetEntries();
		cout<<nevents<<" events in this chain."

		// Now loop over events
		for (int k=0;k<nevents;k++)
		{
			// some code here
		}

		return 0;
}
