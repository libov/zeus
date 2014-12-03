#############################################################################
# Makefile for building: main
# Made by Denys Lontkovskyi & Inna Makarenko
# On: Mon Nov 26 17:14:41 2007
# Project:  hello.pro
#############################################################################

CXX         = g++
CXXFLAGS    = -O -O2 -Wall -fPIC

LD          = g++
KTLIB       = -L./lib -lKtJet
KTINCLUDE   = -I./include

CLHEPLIB    = -L/opt/products/CLHEP/2.0.3.1/lib -lCLHEP
CLHEPINCLUDE= -I/opt/products/CLHEP/2.0.3.1/include

ROOTCFLAGS  = $(shell root-config --nonew --cflags)
ROOTLIBS    = $(shell root-config --nonew --libs)

CXXFLAGS    += $(ROOTCFLAGS)
CXXFLAGS    += $(KTINCLUDE)
CXXFLAGS    += $(CLHEPINCLUDE)
LIBS        += $(ROOTLIBS)
LIBS        += $(KTLIB)
LIBS        += $(CLHEPLIB)

OBJECTS     = main.o

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%.o: %.C
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Tasks:         main

main: $(OBJECTS)
	$(LD) $^ $(LIBS) -o $@
clean:
	@rm *.o main