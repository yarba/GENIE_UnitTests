#
# GENIE Makefile 
#
# Author: Marco Roda, Liverpool 
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
include $(GENIE)/src/make/Make.include

#INCLUDES += -I$(BOOST_INC)
ifdef CPP_INCLUDES
INCLUDES := $(CPP_INCLUDES) -I$(BOOST_INC)
else
INCLUDES := $(INCLUDES) -I$(BOOST_INC)
endif

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
BOOST_UT_LIBS = -L$(BOOST_LIB) -lboost_unit_test_framework
LIBRARIES := $(GENIE_GENERATOR_LIBS)  $(LIBRARIES)  

all: lwlyn_nieves_ut 

lwlyn_nieves_ut: FORCE
	$(CXX) $(CXXFLAGS) -c lwlyn_nieves_ut.cxx $(INCLUDES) 
	$(LD) $(LDFLAGS) lwlyn_nieves_ut.$(ObjSuf) $(LIBRARIES) $(BOOST_UT_LIBS) -o lwlyn_nieves_ut 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	$(RM) lwlyn_nieves_ut


FORCE:

# DO NOT DELETE
