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

OBJECTS=TDataset.o TXMLparser.o TSubSet.o TCrossSection.o TCrossSectionBin.o TSystematics.o TPointF2theo.o

default: all

all: compare_CN_versions compare_fit_results THistogram.o jet_energy_scale systematics f2bc txt2XML reweighting correct_qed

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

TPointF2theo.o: TPointF2theo.cxx TPointF2theo.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

compare_CN_versions.o: compare_CN_versions.cxx TDataset.o
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

compare_fit_results.o: compare_fit_results.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

jet_energy_scale.o: jet_energy_scale.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

systematics.o: systematics.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

f2bc.o: f2bc.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

txt2XML.o: txt2XML.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

reweighting.o: reweighting.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

correct_qed.o: correct_qed.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

systematics: $(OBJECTS) systematics.o
	g++ -o systematics $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/systematics.o -I$(INC) $(FLAGS) -lxerces-c

compare_CN_versions: $(OBJECTS) compare_CN_versions.o
	g++ -o compare_CN_versions $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/compare_CN_versions.o -I$(INC) $(FLAGS) -lxerces-c

compare_fit_results: $(OBJECTS) compare_fit_results.o
	g++ -o compare_fit_results $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/compare_fit_results.o -I$(INC) $(FLAGS) -lxerces-c

jet_energy_scale: $(OBJECTS) jet_energy_scale.o
	g++ -o jet_energy_scale $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/jet_energy_scale.o -I$(INC) $(FLAGS) -lxerces-c

f2bc: $(OBJECTS) f2bc.o
	g++ -o f2bc $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/f2bc.o -I$(INC) $(FLAGS) -lxerces-c

txt2XML: $(OBJECTS) txt2XML.o
	g++ -o txt2XML $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/txt2XML.o -I$(INC) $(FLAGS) -lxerces-c

reweighting: $(OBJECTS) reweighting.o
	g++ -o reweighting $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/reweighting.o -I$(INC) $(FLAGS) -lxerces-c

correct_qed: $(OBJECTS) correct_qed.o
	g++ -o correct_qed $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/correct_qed.o -I$(INC) $(FLAGS) -lxerces-c

.PHONY: clean
clean:
	-rm -rf $(OBJ)/*.o
	-rm -rf compare_CN_versions compare_fit_results systematics jet_energy_scale f2bc
