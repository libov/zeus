FLAGS=`root-config --glibs --cflags`
FLAGS_OBJ=`root-config --cflags`
OBJ := tmp
SRC := src
INC := inc
vpath %.o $(OBJ)
vpath %.cxx $(SRC)
vpath %.C $(SRC)
vpath %.h $(INC)


.PHONY: all
all:	fitter plot_results xsect_philipp_XMLconverter result_plotter

OBJECTS=  TMyFitter.o TDistribution.o TResultPlotter.o
OBJECTS_XML= TXMLparser.o TCrossSection.o TCrossSectionBin.o TDataset.o TSubSet.o
OBJ_XML = $(ANALYSIS)/TXMLparser/tmp 

fitter: $(OBJECTS) fitter.o
	g++ -o fitter $(OBJ)/fitter.o $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -lMinuit -lxerces-c

plot_results: $(OBJECTS) plot_results.o
	g++ -o plot_results $(OBJ)/plot_results.o $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -lMinuit -lxerces-c

result_plotter: $(OBJECTS) result_plotter.o
	g++ -o result_plotter $(OBJ)/result_plotter.o $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -lMinuit -lxerces-c

xsect_philipp_XMLconverter: $(OBJECTS) xsect_philipp_XMLconverter.o
	g++ -o xsect_philipp_XMLconverter $(OBJ)/xsect_philipp_XMLconverter.o $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -lMinuit -lxerces-c



TMyFitter.o: TMyFitter.cxx TMyFitter.h
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

TDistribution.o: TDistribution.cxx TDistribution.h
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

TResultPlotter.o: TResultPlotter.cxx TResultPlotter.h
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(FITTER)/inc -I$(ANALYSIS)/TXMLparser/inc

plot_results.o: plot_results.cxx
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(FITTER)/inc

result_plotter.o: result_plotter.cxx
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(FITTER)/inc

fitter.o: fitter.cxx
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc

xsect_philipp_XMLconverter.o: xsect_philipp_XMLconverter.cxx
	g++ -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc


.PHONY: clean
clean:
	-rm -rf $(OBJ)/*.o
	-rm -rf fitter

