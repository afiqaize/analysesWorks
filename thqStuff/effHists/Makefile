BOOSTDIR = /afs/cern.ch/sw/lcg/external/Boost/1.50.0_python2.7/x86_64-slc5-gcc46-opt

INCLUDE = -I$(PEC_FWK_INSTALL)/core/include -I$(PEC_FWK_INSTALL)/extensions/include -I./ -I$(shell root-config --incdir)
OPFLAGS = -O2
CFLAGS = -Wall -Wextra -std=c++11 $(INCLUDE) $(OPFLAGS) $(MACROS)
LDFLAGS = $(shell root-config --libs) -lHistPainter $(PEC_FWK_INSTALL)/lib/libpecfwk.a -L$(BOOSTDIR)/lib -lboost_filesystem-gcc46-mt-1_50

all: effHists

effHists: effHists.o BTagEff.o $(PEC_FWK_INSTALL)/lib/libpecfwk.a
	@ g++ $(CFLAGS) $(LDFLAGS) $+ -o $@

%.o: %.cpp
	@ g++ $(CFLAGS) -c $< -o $@
