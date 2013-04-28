FLAGS=`root-config --glibs --cflags` -g
FLAGS_OBJ=`root-config --cflags` -g
OBJ := tmp
SRC := src
INC := inc
vpath %.o $(OBJ)
vpath %.cxx $(SRC)
vpath %.C $(SRC)
vpath %.h $(INC)

OBJECTS=TCharmMeasurement.o TMultiCanvas.o

default: all

all: plot_charm_reduced

TCharmMeasurement.o: TCharmMeasurement.cxx TCharmMeasurement.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

TMultiCanvas.o: TMultiCanvas.cxx TMultiCanvas.h
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

plot_charm_reduced.o: plot_charm_reduced.cxx
	g++ -o $(OBJ)/$@ -c $< -I$(INC) $(FLAGS_OBJ)

plot_charm_reduced: $(OBJECTS) plot_charm_reduced.o
	g++ -o plot_charm_reduced $(patsubst %.o, $(OBJ)/%.o, $(OBJECTS)) $(OBJ)/plot_charm_reduced.o -I$(INC) $(FLAGS) -lxerces-c

.PHONY: clean
clean:
	-rm -rf $(OBJ)/*.o
	-rm -rf plot_charm_reduced
