BOOSTDIR = /afs/cern.ch/sw/lcg/external/Boost/1.50.0_python2.7/x86_64-slc5-gcc46-opt

INCLUDE = -I$(shell root-config --incdir) -I$(BOOSTDIR)/include/boost-1_50/
OPFLAGS = -O2
CFLAGS = -Wall -Wextra -std=c++11 $(INCLUDE) $(OPFLAGS)
LDFLAGS = $(shell root-config --libs) -lTreePlayer -L$(BOOSTDIR)/lib/ -lboost_filesystem-gcc46-mt-1_50

# For some reason needed to do export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/cern.ch/sw/lcg/external/Boost/1.50.0_python2.7/x86_64-slc5-gcc46-opt/lib/ as one of the libraries needed by boost_filesystem is not found otherwise...

all: effCalc

effCalc: effCalc.cpp
	@ g++ $< $(CFLAGS) $(LDFLAGS) -o $@