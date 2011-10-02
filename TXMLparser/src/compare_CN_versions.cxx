// my includes
#include<TDataset.h>
#include<TSubSet.h>

// system includes
#include<iostream>

// root includes
#include<TFile.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TLine.h>
#include<TString.h>
#include<TLegend.h>

using namespace std;

// function declarations; see implementation below, after main()
int     plot_year (TString file1, TString file2);
int     plot_histo(TCanvas * c, unsigned pad_number, TString histo_name);
void    plot_mc(TSubSet::Period p);
void    plot_data(TSubSet::Period p);
void    getXMLfileName (TString & , TString);

// some global variables
TFile           *f1;
TFile           *f2;
TLegend         *leg;
TString         HISTOGRAM_VERSION1;
TString         HISTOGRAM_VERSION2;
TString         XML_FILE1;
TString         XML_FILE2;

// main function
int main(int argc, char **argv) {

        // options handling: get binning file name and histograms version so that
        // selected files with histograms can be picked up
        // first check whether there are two arguments
	if ( argc != 5 ) {
		cout<<"Please provide necessary parameters"<<endl;
		cout<<"usage:\n\t compare_CN_versions <Binning File Suffix 1st file> <Histograms Version Ending 1st file> ";
                cout<<"<Binning File Suffix 2nd file> <Histograms Version Ending 2nd file>\n ";
		cout<<"Terminating, sorry."<<endl;
		exit(-1);
	}
        // get arguments
	TString		BinningFileSuffix1 = argv[1];
	TString		HistogramsVersionEnding1 = argv[2];
	TString		BinningFileSuffix2 = argv[3];
	TString		HistogramsVersionEnding2 = argv[4];
        // construct endings of files
	HISTOGRAM_VERSION1 = "."+BinningFileSuffix1 + HistogramsVersionEnding1+".root";
        HISTOGRAM_VERSION2 = "."+BinningFileSuffix2 + HistogramsVersionEnding2+".root";  
	cout << "INFO: File ending sample1 = " << HISTOGRAM_VERSION1 << endl;
        cout << "INFO: File ending sample2 = " << HISTOGRAM_VERSION2 << endl;
      
        // determine which XML files should be used for sample information
        getXMLfileName(XML_FILE1, HISTOGRAM_VERSION1);
        getXMLfileName(XML_FILE2, HISTOGRAM_VERSION2);
	cout << "INFO: XML_FILE1= " << XML_FILE1 << endl;
        cout << "INFO: XML_FILE2 = " << XML_FILE2 << endl;

        // now plot results
        // plot MC
        
        cout << "\n\n\n" << endl;
        cout << "NOTE: THE ORDER FOR MC IS THE FOLLOWING: charm(Q2>1.5), charm(Q2>4), beauty, light flavour" << endl;
        cout << "------- MC 05e -------" << endl;
        plot_mc(TSubSet::k05E);
        cout << "------- MC 06e -------" << endl;
        plot_mc(TSubSet::k06E);
        cout << "------- MC 07p -------" << endl;
        plot_mc(TSubSet::k0607P);


        // plot DATA
        cout << "\n\n\n" << endl;
        cout << "------- DATA 05e -------" << endl;
        plot_data(TSubSet::k05E);
        cout << "------- DATA 06e -------" << endl;
        plot_data(TSubSet::k06E);
        cout << "------- DATA 06p -------" << endl;
        plot_data(TSubSet::k06P);
        cout << "------- DATA 07p -------" << endl;
        plot_data(TSubSet::k07P);

        // done
	cout << "\n---> Finished successfully <---\n";
	return 0;
}


void plot_mc(TSubSet::Period period){

        // some initialization
        vector<TString>         samples_v02;
        vector<TString>         samples_v04;
        TSubSet                 cSubSet;

	TDataset Dataset_v02(XML_FILE1);
        TDataset Dataset_v04(XML_FILE2);

	cSubSet = Dataset_v02.getSubSet(TSubSet::kMC, period, TSubSet::kCHARM, TSubSet::kQ2g1_5, TSubSet::kBGF);
        samples_v02.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION1);
        cSubSet = Dataset_v02.getSubSet(TSubSet::kMC, period, TSubSet::kCHARM, TSubSet::kQ2g4, TSubSet::kBGF);
        samples_v02.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION1);
        cSubSet = Dataset_v02.getSubSet(TSubSet::kMC, period, TSubSet::kBEAUTY, TSubSet::kQ2g1, TSubSet::kBGF);
        samples_v02.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION1);
        cSubSet = Dataset_v02.getSubSet(TSubSet::kMC, period, TSubSet::kLIGHT, TSubSet::kQ2g4, TSubSet::kBGF);
        samples_v02.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION1);

	cSubSet = Dataset_v04.getSubSet(TSubSet::kMC, period, TSubSet::kCHARM, TSubSet::kQ2g1_5, TSubSet::kBGF);
        samples_v04.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION2);
        cSubSet = Dataset_v04.getSubSet(TSubSet::kMC, period, TSubSet::kCHARM, TSubSet::kQ2g4, TSubSet::kBGF);
        samples_v04.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION2);
        cSubSet = Dataset_v04.getSubSet(TSubSet::kMC, period, TSubSet::kBEAUTY, TSubSet::kQ2g1, TSubSet::kBGF);
        samples_v04.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION2);
        cSubSet = Dataset_v04.getSubSet(TSubSet::kMC, period, TSubSet::kLIGHT, TSubSet::kQ2g4, TSubSet::kBGF);
        samples_v04.push_back ("analysis."+cSubSet.getSampleName()+HISTOGRAM_VERSION2);

        if (samples_v02.size() != samples_v04.size()) {
                cout << "Number of samples for v02 and v04 are not the same" << endl;
                exit(-1);
        }
        
        for (int i = 0; i < samples_v02.size(); i++) {
                plot_year(samples_v02[i], samples_v04[i]);
        }
}

void plot_data(TSubSet::Period period){

        // some initializations
        TSubSet     cSubSet_v02;
        TSubSet     cSubSet_v04;
        TString     SampleName_v02;
        TString     SampleName_v04;

        // open files with samples information
	TDataset Dataset_v02(XML_FILE1);
        TDataset Dataset_v04(XML_FILE2);

        // get TSubSets with given properties
        cSubSet_v02 = Dataset_v02.getSubSet(TSubSet::kDATA, period);
        cSubSet_v04 = Dataset_v04.getSubSet(TSubSet::kDATA, period);

        // get samples names and construct filenames
        SampleName_v02 = "analysis."+cSubSet_v02.getSampleName()+HISTOGRAM_VERSION1;
        SampleName_v04 = "analysis."+cSubSet_v04.getSampleName()+HISTOGRAM_VERSION2;

        // plot
        plot_year(SampleName_v02, SampleName_v04);
}


int plot_year (TString file1, TString file2) {
        // get files
        TString		HISTO=getenv("HISTO_PATH");
	f1 = new TFile (HISTO+"/"+file1);
	f2 = new TFile (HISTO+"/"+file2);

        TCanvas *c = new TCanvas();
        c -> Divide(4,2);

        plot_histo(c, 1, "bin1/significance");
        plot_histo(c, 2, "bin1/significance_massbin1_mirrored");
        plot_histo(c, 3, "bin1/significance_massbin2_mirrored");
        plot_histo(c, 4, "bin1/significance_massbin3_mirrored");

        c -> Print(file1+"___VS___"+file2+".png");
        c -> Print(file1+"___VS___"+file2+".root");
        return 0;
}

int plot_histo(TCanvas * c, unsigned pad_number, TString histo_name) {
        cout <<  histo_name << ": ";
        // get histograms
	TH1F * h1 = (TH1F*) f1 -> Get(histo_name);
	TH1F * h2 = (TH1F*) f2 -> Get(histo_name);

	// set colors to distinguish them
	h1 -> SetLineColor(kRed);
	h2 -> SetLineColor(kBlue);
        // draw histograms
        c -> cd(pad_number);
	h1 -> Draw();
	h2 -> Draw("same");
        
        Float_t integral1 = h1->Integral();
        Float_t integral2 = h2->Integral();
        Float_t deviation = 100 * (integral1 -integral2) / integral1;
        cout << integral1 << " <---> " << integral2 << " (" <<deviation << " %)" << endl;

        // create and draw a legend
        if ( pad_number==1 ) {
	       leg = new TLegend(0.1,0.7,0.44,0.9);
               //TString title1 = sample_Titles[sample_counter]+"v02e";
               //TString title2 = sample_Titles[sample_counter]+"v04b";
	       //leg -> AddEntry(h1, title1, "l");
	       //leg -> AddEntry(h2, title2, "l");
	       leg -> Draw();
        }

        // now a ratio plot
        TH1F *h3 = (TH1F*)h1->Clone("h3");
        h3 -> Divide(h2);
        c -> cd (pad_number+4);
        h3 -> SetMarkerColor(kBlack);
        h3 -> SetMarkerStyle(20);
        h3 -> SetMarkerSize(1);
        h3 -> SetAxisRange(0, 2, "Y");
        h3 -> Draw();

        TLine *line = new TLine(h3 -> GetBinLowEdge(1), 1, h3 -> GetBinLowEdge(h1->GetNbinsX()), 1);
        line -> Draw("same");

        return 0;
}


void getXMLfileName (TString & name, TString histo_name) {

        // determine which XML files should be used for sample information
        if ( histo_name.Contains("2.2") || histo_name.Contains("2.3") || histo_name.Contains("2.5") || histo_name.Contains("2.7") || histo_name.Contains("2.9.0") || histo_name.Contains("2.9.1") ) {
          name = "samples.v04.xml";
        } else if ( histo_name.Contains("2.1") || histo_name.Contains("2.4") || histo_name.Contains("2.6") || histo_name.Contains("2.9.2") || histo_name.Contains("2.9.3")) {
          name = "samples.v02.xml";
        } else {
          cout << " Unknown histogram version: " << histo_name << endl;
          cout << " At the moment 2.1, 2.2, 2.3, 2,4, 2.5 and 2.6 are supported" << endl;
          cout << " Choose the correct one or implement in "<< __FILE__ << endl;
          cout << " Terminating, sorry" << endl;
          abort();
        }
}
