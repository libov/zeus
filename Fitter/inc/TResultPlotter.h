//////////////////////////////////////////////////
//                                              //
//  Inclusive  secondary vertex analysis        //
//  Libov Vladyslav                             //
//  DESY                                        //
//  libov@mail.desy.de                          //
//  February 2011                               //
//                                              //
//////////////////////////////////////////////////

#ifndef __TRESULTPLOTTER_H__
#define __TRESULTPLOTTER_H__

// custom headers
#include<TCrossSection.h>
#include<TCrossSectionBin.h>

// ROOT headers
#include<TH1F.h>
#include<TCanvas.h>
#include<TGraphErrors.h>
#include<TGraphAsymmErrors.h>

class TResultPlotter {

        public:

                TResultPlotter();
                ~TResultPlotter(){};

                void    Initialize();
                void    AddXMLFile(TString file_name);
                void    DrawPlots(TString file_name, unsigned pad_number, bool same);
                void    DrawRatio(TString file_name1, TString file_name2, unsigned pad_number, bool same ) ;
                void    PrintCanvases();

                void    Divide(unsigned npads_x, unsigned npads_y);
                void    SetPlotCharm(bool plot_charm) {isCharm = plot_charm;};
                void    SetPlotScalingFactors(bool  plot_scaling) {fPlotScalingFactors = plot_scaling;};
                void    SetConfigFile(TString file) {fConfig = file;}
                void    SetFileStyleSettings(TString, bool, int, int, int, bool, int, int, int, bool, int);

        private:

                // this structure corresponds to a differential distribution (e.g. dsigma/dQ2) from a certain XML file;
                // it can represent both data and theory; in the latter case only graph_tot is meaningful, since there are no stat. uncertainties
                struct BinGroup{
                        TH1F * histo_dummy;                             //!< dummy histogram to store the axes settings
                        TGraphErrors * graph_stat;                      //!< represents statistical uncertainties
                        TGraphAsymmErrors * graph_tot;                  //!< represents statistical and systematic uncertainties
                        TString ID;                                     //!< unique identifier of a differential distribution, matches "id" parameter of <bin_group> tag in an XML file
                };

                std::map<TString, std::vector<BinGroup> > fBinGroupMap; //!< maps a vector of BinGroup objects to every XML file
                std::map<TString, TCanvas *> fCanvasMap;                //!< maps a canvas to every BinGroup object ID, i.e. to every differential distribution type (e.g. Q2, x, etc.)

                unsigned    fNpads_x;                                   //!< number of pads horizontally
                unsigned    fNpads_y;                                   //!< number of pads vertically

                bool    isCharm;                                        //!< true: plot charm results; false: plot beauty results
                bool    fPlotScalingFactors;                            //!< true: plot scaling factors; false: plot cross-section

                TString fConfig;                                        //!< name of the configuration file with the plot settings

                // these options are read from the config file fConfig
                std::map <TString, TString> fXtitle;                    //!< maps X axis title to every BinGroup object ID, i.e. to every differential distribution type (e.g. Q2, x, etc.)
                std::map <TString, TString> fYtitle;                    //!< maps Y axis title -/-
                std::map <TString, Float_t> fYaxis_low_limit;           //!< maps lower limit of an Y axis -/-
                std::map <TString, Float_t> fYaxis_up_limit;            //!< maps upper limit of an Y axis -/-

                // a structure to hold style settings for each filename
                struct Style{
                    bool    draw_marker;
                    int     marker_color;
                    int     marker_style;
                    int     marker_size;
                    bool    draw_line;
                    int     line_color;
                    int     line_style;
                    int     line_width;
                    bool    draw_band;
                    int     band_color;
                };
                std::map<TString, Style>    fStyleMap;
};

#endif
