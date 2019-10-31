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

LIBNAME = libUtilsUT

#INCLUDES += -I$(BOOST_INC)
ifdef CPP_INCLUDES
INCLUDES := $(CPP_INCLUDES) -I$(BOOST_INC) -I../Common -I../SynthEvent -I../Utils
else
INCLUDES := $(INCLUDES) -I$(BOOST_INC) -I../Common -I../SynthEvent -I../Utils
endif

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
BOOST_UT_LIBS = -L$(BOOST_LIB) -lboost_unit_test_framework
LIBRARIES := $(GENIE_GENERATOR_LIBS)  $(LIBRARIES)

UTILS_SOURCES := $(wildcard *.cxx) 
UTILS_OBJECTS  = $(addsuffix .$(ObjSuf), $(basename $(UTILS_SOURCES)))

# --> old structure of dirs --> EXTRA_SRC := $(shell ls ../*UT/*.cxx | grep -v Master | grep -v ReWei) $(wildcard ../SynthEvent/*.cxx)
EXTRA_SRC := $(shell ls ../GenieUT/*/*/*.cxx | grep -v Strange) $(wildcard ../SynthEvent/*.cxx)
# I need to make it pickup objects files from here rather than *UT/...
EXTRA_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(notdir $(EXTRA_SRC))))

# make it pick pieces of code under #ifdef PRINTOUT
CXXFLAGS := $(CXXFLAGS) -DPRINTOUT=1

all: update_benchmark 

update_benchmark: FORCE
	$(CXX) $(CXXFLAGS) -c $(UTILS_SOURCES) $(EXTRA_SRC) $(INCLUDES)
	$(LD) $(LDFLAGS) $(UTILS_OBJECTS) $(EXTRA_OBJ) $(LIBRARIES) $(BOOST_UT_LIBS) -o update_benchmark 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core
	$(RM) update_benchmark 


FORCE:

# DO NOT DELETE
