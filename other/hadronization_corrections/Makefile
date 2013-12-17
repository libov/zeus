# Vladyslav Libov
# libov@mail.desy.de

FLAGS=`root-config --glibs --cflags` `/data/zenith226a/libov/fastJet/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` -g 

FLAGS_OBJ=`root-config --cflags` -Wall -g

all: hadronic_corrections

hadronic_corrections: hadronic_corrections.o
	gcc -o hadronic_corrections hadronic_corrections.o $(FLAGS)

hadronic_corrections.o: hadronic_corrections.cxx
	gcc -o $@ -c $< -I/data/zenith226a/libov/fastJet/fastjet-install/include $(FLAGS_OBJ)

.PHONY: clean
clean:
	-rm -rf *.o
	-rm -rf test2