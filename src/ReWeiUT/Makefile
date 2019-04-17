#
# GENIE-UT Makefile 
#
# Author: Julia Yarba, FNAL 
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
include $(GENIE_REWEIGHT)/src/make/Make.include

#INCLUDES += -I$(BOOST_INC)
ifdef CPP_INCLUDES
INCLUDES := $(CPP_INCLUDES) -I$(BOOST_INC)
else
INCLUDES := $(INCLUDES) -I$(BOOST_INC)
endif

RW_SOURCES := $(wildcard *.cxx)
RW_OBJECTS    = $(addsuffix .$(ObjSuf), $(basename $(RW_SOURCES)))

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
GENIE_RW_LIBS = $(shell $(GENIE_REWEIGHT)/src/scripts/setup/genie-reweight-config --libs)
BOOST_UT_LIBS = -L$(BOOST_LIB) -lboost_unit_test_framework
LIBRARIES := $(GENIE_GENERATOR_LIBS) $(GENIE_RW_LIBS) $(LIBRARIES)  

all: rwgt_ut 

rwgt_ut: FORCE
	$(CXX) $(CXXFLAGS) -c $(RW_SOURCES) $(INCLUDES) 
	# $(LD) $(LDFLAGS) $(RW_OBJECTS) $(LIBRARIES) $(BOOST_UT_LIBS) -o rwgt_ut 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	# $(RM) rwgt_ut


FORCE:

# DO NOT DELETE
