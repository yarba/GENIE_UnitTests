#
# GENIE Makefile 
#
# Author: Julia Yarba, Fermilab 
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
include $(GENIE)/src/make/Make.include

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
BOOST_UT_LIBS = -L$(BOOST_LIB) -lboost_unit_test_framework
LIBRARIES := $(GENIE_GENERATOR_LIBS) $(BOOST_UT_LIBS)  $(LIBRARIES) 

all: lwlyn_nieves_ut 

lwlyn_nieves_ut: FORCE
	$(CXX) $(CXXFLAGS) -c lwlyn_nieves_ut.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) lwlyn_nieves_ut.$(ObjSuf) $(LIBRARIES) -o lwlyn_nieves_ut 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	$(RM) lwlyn_nieves_ut


FORCE:

# DO NOT DELETE
