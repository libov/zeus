//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY			                //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TRESULTPLOTTER_H__
#define __TRESULTPLOTTER_H__

// my includes
#include<TCrossSection.h>
#include<TCrossSectionBin.h>

// ROOT includes
#include<TH1F.h>
#include<TCanvas.h>

class TResultPlotter {
        
        public:

                TResultPlotter();
                ~TResultPlotter(){};
        
                void    DrawPlots(TString file_name, bool recreate, unsigned pad_number, bool same, unsigned color) ;
                void    DrawPlots(TString file_name1, TString file_name2, bool recreate, unsigned pad_number, bool same ) ;

                void    AddXMLFile(TString file_name);

                void    PrintCanvases();

                void    Divide(unsigned npads_x, unsigned npads_y);

                void    SetLogY(unsigned pad_id);

                void    SetPlotCharm(bool plot_charm) {isCharm = plot_charm;};

                void    SetPlotScalingFactors(bool  plot_scaling) {fPlotScalingFactors = plot_scaling;};

        private:

                struct BinGroup{
                        TH1F    *histo;
                        std::vector<Float_t> binning;   // the binning here follows the ROOT convention, see TH1F documentation
                        TString binGroupID;
                        std::vector<Float_t> y_value;
                        std::vector<Float_t> y_error;
                };

                std::vector<BinGroup>   BinGroupList;

                std::vector<TCrossSection>                    fCrossSectionList;
                std::map<TString, std::vector<BinGroup> >     fBinGroupMap;

                std::map<TString, TCanvas *>                    fCanvasMap;


                // some drawing options

                // layout of a canvas - divisiion into subpads
                unsigned    fNpads_x;
                unsigned    fNpads_y;

                // a structure containing options for a subpad
                struct  DrawOption {
                      unsigned  padID;  // pad number ( to be used as an argument in TCanvas::cd(padID) ) NOT NEEDED IN PRINCIPLE AS WE ARE USING MAP
                      bool      isLog;  // true - log scale; false - linear scale
                };
                std::map <unsigned, DrawOption>   fMap_padID_Option;

                bool    isCharm;                    //!< true: plot charm results; false: plot beauty results
                bool    fPlotScalingFactors;        //!< true: plot scaling factors; false: plot cross-section
          
};

#endif
