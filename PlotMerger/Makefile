FLAGS=`root-config --glibs --cflags` -g
FLAGS_OBJ=`root-config --cflags` -g
OBJ := tmp
SRC := src
INC := inc
vpath %.o $(OBJ)
vpath %.cxx $(SRC)
vpath %.C $(SRC)
vpath %.h $(INC)


.PHONY: all
all: merger plotter

OBJECTS= TSample.o TPlotMerger.o merger.o

OBJECTS_XML= TXMLparser.o TCrossSection.o TCrossSectionBin.o TDataset.o TSubSet.o

merger: $(OBJECTS)
	gcc -o merger $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) -I. $(FLAGS) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -lxerces-c

TSample.o: TSample.cxx TSample.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc
TPlotMerger.o: TPlotMerger.cxx TPlotMerger.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc
merger.o: merger.cxx
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc

OBJECTS1=  TControlPlot.o TAdvCanvas.o TPlotType.o plotter.o
plotter: $(OBJECTS1)
	gcc -o plotter $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS1)) -I. $(FLAGS)

TControlPlot.o: TControlPlot.cxx TControlPlot.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

TAdvCanvas.o: TAdvCanvas.cxx TAdvCanvas.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

TPlotType.o: TPlotType.cxx TPlotType.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

plotter.o: plotter.cxx
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

.PHONY: clean
clean:
	-rm $(OBJ)/*.o
	-rm merger
	-rm plotter
