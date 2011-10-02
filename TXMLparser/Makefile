# definitions
FLAGS=`root-config --glibs --cflags` -g
FLAGS_OBJ=`root-config --cflags` -g
OBJ := tmp
SRC := src
INC := inc
vpath %.o $(OBJ)
vpath %.cxx $(SRC)
vpath %.C $(SRC)
vpath %.h $(INC)

OBJECTS=TDataset.o TXMLparser.o TSubSet.o TCrossSection.o TCrossSectionBin.o TSystematics.o

default: all

all: test compare_CN_versions compare_fit_results THistogram.o jet_energy_scale systematics

TXMLparser.o: TXMLparser.cxx TXMLparser.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

TDataset.o: TDataset.cxx TDataset.h TXMLparser.cxx TXMLparser.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

TSubSet.o: TSubSet.cxx TSubSet.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

TCrossSection.o: TCrossSection.cxx TCrossSection.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

TCrossSectionBin.o: TCrossSectionBin.cxx TCrossSectionBin.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

THistogram.o: THistogram.cxx THistogram.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

TSystematics.o: TSystematics.cxx TSystematics.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

test.o: test.cxx TDataset.o
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

compare_CN_versions.o: compare_CN_versions.cxx TDataset.o
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

compare_fit_results.o: compare_fit_results.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

jet_energy_scale.o: jet_energy_scale.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

systematics.o: systematics.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

systematics: $(OBJECTS) systematics.o
	g++ -o systematics $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/systematics.o -I$(INC) $(FLAGS) -lxerces-c

test: $(OBJECTS) test.o
	g++ -o test $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/test.o -I$(INC) $(FLAGS) -lxerces-c

compare_CN_versions: $(OBJECTS) compare_CN_versions.o
	g++ -o compare_CN_versions $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/compare_CN_versions.o -I$(INC) $(FLAGS) -lxerces-c

compare_fit_results: $(OBJECTS) compare_fit_results.o
	g++ -o compare_fit_results $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/compare_fit_results.o -I$(INC) $(FLAGS) -lxerces-c

jet_energy_scale: $(OBJECTS) jet_energy_scale.o
	g++ -o jet_energy_scale $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/jet_energy_scale.o -I$(INC) $(FLAGS) -lxerces-c


.PHONY: clean
clean:
	-rm -rf $(OBJ)/*.o
	-rm -rf test
