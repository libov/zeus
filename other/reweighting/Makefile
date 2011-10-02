# definitions
FLAGS=`root-config --glibs --cflags`
FLAGS_OBJ=`root-config --cflags`
OBJ := tmp
SRC := src
INC := inc
vpath %.o $(OBJ)
vpath %.cxx $(SRC)
vpath %.C $(SRC)
vpath %.h $(INC)

OBJ_XML = $(ANALYSIS)/TXMLparser/tmp
INC_XML = $(ANALYSIS)/TXMLparser/inc

default: all

all: reweight_et

reweight_et.o: reweight_et.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ) -I$(INC_XML)

reweight_et: reweight_et.o
	g++ -o reweight_et $(OBJ)/reweight_et.o $(OBJ_XML)/THistogram.o $(OBJ_XML)/TXMLparser.o $(FLAGS) -lxerces-c

.PHONY: clean
clean:
	-rm -rf $(OBJ)/*.o
