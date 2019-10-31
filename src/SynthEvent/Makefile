#
# GENIE-UT Makefile 
#
# Author: Julia Yarba, Fermilab
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
include $(GENIE)/src/make/Make.include

# --> not needed --> LIBNAME = libSynthEventUT

ifdef CPP_INCLUDES
INCLUDES := $(CPP_INCLUDES) 
else
INCLUDES := $(INCLUDES) 
endif

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
LIBRARIES := $(GENIE_GENERATOR_LIBS)  $(LIBRARIES)

XS_SOURCES := $(wildcard *.cxx)
XS_OBJECTS    = $(addsuffix .$(ObjSuf), $(basename $(XS_SOURCES)))

all: synthevt_ut 

synthevt_ut: FORCE
	$(CXX) $(CXXFLAGS) -c $(XS_SOURCES) $(INCLUDES) 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 


FORCE:

# DO NOT DELETE
