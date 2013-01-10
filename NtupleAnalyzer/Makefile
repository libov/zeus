#
# Vladyslav Libov
# libov@mail.desy.de
#
# unoptimized! check prerequisites!
#
CN_VERSION=CN_VERSION_V02
FLAGS=`root-config --glibs --cflags` -g
FLAGS_OBJ=`root-config --cflags` -D$(CN_VERSION) -Wall -g
OBJ := tmp
SRC := src
INC := inc
vpath %.o $(OBJ)
vpath %.cxx $(SRC)
vpath %.C $(SRC)
vpath %.h $(INC)

OBJECTS_ANALYSIS= analysis.o TBin.o TGlobalBin.o TNtupleAnalyzer.o TMiniNtupleAnalyzer.o TMiniNtupleAnalyzerLoop.o TMiniNtupleAnalyzerTrackingEfficiency.o TMiniNtupleAnalyzerSetBinning.o TVertex.o BaseClass.o TRew.o

OBJECTS_SUBMIT_ANALYSIS= submit_analysis.o 

OBJECTS_CREATOR= createMiniNtuples.o TNtupleAnalyzer.o TMiniNtupleCreator.o BaseClass.o

OBJ_XML = $(ANALYSIS)/TXMLparser/tmp

OBJECTS_XML= TXMLparser.o TCrossSection.o TCrossSectionBin.o TDataset.o TSubSet.o

all: analysis createMiniNtuples submit_analysis
	echo "NOTE: COMMON NTUPLE VERSION: " $(CN_VERSION)
# executables

analysis: $(OBJECTS_ANALYSIS) config/orablocks.cfg create-BaseClass.py
	gcc -o analysis $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS_ANALYSIS)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -L$(TLITE)/lib/$(ZARCH_TYPE) -ltLite -L$(CLHEPLIBDIR) -lCLHEP -L. -lxerces-c -L$(TRACKING_MAP) -lTrackAllEfficiency_cc -lTrackSumEfficiency_cc -lTrackEfficiency_cc -lTrackRecEfficiency_cc

submit_analysis: $(OBJECTS_SUBMIT_ANALYSIS) config/orablocks.cfg create-BaseClass.py
	gcc -o submit_analysis $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS_SUBMIT_ANALYSIS)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -L$(TLITE)/lib/$(ZARCH_TYPE) -ltLite -L$(CLHEPLIBDIR) -lCLHEP -L. -lxerces-c

createMiniNtuples: $(OBJECTS_CREATOR) config/orablocks.cfg create-BaseClass.py
	gcc -o createMiniNtuples $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS_CREATOR)) $(patsubst %.o, /data/zenith226a/libov/analysis/TXMLparser/tmp/%.o, $(OBJECTS_XML)) -I. $(FLAGS) -L. -lxerces-c

doc: Doxyfile doxyinfo
	doxygen Doxyfile

# libraries

BaseClass.cxx: create-BaseClass.py
	python create-BaseClass.py

BaseClass.o: BaseClass.cxx
	gcc -o $(OBJ)/$@ -c $(SRC)/$< -I $(INC)/ $(FLAGS_OBJ)

TBin.o: TBin.cxx TBin.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ)

TVertex.o: TVertex.cxx TVertex.h
	gcc -o $(OBJ)/$@ -c $< -I. -I$(TLITE)/inc/vxlite -I$(CLHEPINCDIR) $(FLAGS_OBJ)

TGlobalBin.o: TGlobalBin.cxx TGlobalBin.h TBin.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces

TNtupleAnalyzer.o: TNtupleAnalyzer.cxx TNtupleAnalyzer.h BaseClass.o
	gcc -o $(OBJ)/$@ -c $< -I. -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces $(FLAGS_OBJ) 

TMiniNtupleAnalyzer.o: TMiniNtupleAnalyzer.cxx TMiniNtupleAnalyzer.h BaseClass.o TNtupleAnalyzer.o
	gcc -o $(OBJ)/$@ -c $< -I. -I$(TLITE)/inc/vxlite -I$(CLHEPINCDIR) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces $(FLAGS_OBJ)

TMiniNtupleCreator.o: TMiniNtupleCreator.cxx TMiniNtupleCreator.h BaseClass.o TNtupleAnalyzer.o
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces

TMiniNtupleAnalyzerLoop.o: TMiniNtupleAnalyzerLoop.cxx TMiniNtupleAnalyzer.h BaseClass.o
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces -I./reweightingFunction/inc/

TMiniNtupleAnalyzerTrackingEfficiency.o: TMiniNtupleAnalyzerTrackingEfficiency.cxx TMiniNtupleAnalyzer.h BaseClass.o
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces

TMiniNtupleAnalyzerSetBinning.o: TMiniNtupleAnalyzerSetBinning.cxx TMiniNtupleAnalyzer.h BaseClass.o
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces

TRew.o: reweightingFunction/src/weight_function.cxx reweightingFunction/inc/weight_function.h
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I./reweightingFunction/inc/

# main programs objects

analysis.o: analysis.cxx TMiniNtupleAnalyzer.o
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces

createMiniNtuples.o: createMiniNtuples.cxx TNtupleAnalyzer.o TMiniNtupleCreator.o BaseClass.o
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc -I$(ANALYSIS)/xerces

submit_analysis.o: submit_analysis.cxx
	gcc -o $(OBJ)/$@ -c $< -I. $(FLAGS_OBJ) -I$(ANALYSIS)/TXMLparser/inc

.PHONY: clean
clean:
	-rm -rf $(OBJ)/*.o
	-rm -rf analysis
	-rm -rf createMiniNtuples
	-rm -rf doc
	-rm -f src/BaseClass.cxx
	-rm -f inc/BaseClass.h
	-rm -f submit_analysis
