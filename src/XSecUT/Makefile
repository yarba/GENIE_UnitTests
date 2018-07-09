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

LIBNAME = libXSecUT

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

XS_SOURCES := $(wildcard *.cxx)
XS_OBJECTS    = $(addsuffix .$(ObjSuf), $(basename $(XS_SOURCES)))

all: xsec_ut 

xsec_ut: FORCE
	$(CXX) $(CXXFLAGS) -c $(XS_SOURCES) $(INCLUDES) 
	# $(LD) $(LDFLAGS) $(XS_OBJECTS) $(LIBRARIES) $(BOOST_UT_LIBS) -o  $(LIBNAME).$(StaticLibSuf)
	# $(SOCMD) $(SOFLAGS) $(SOMINF) $(XS_OBJECTS) $(EXTRA_EXT_LIBS) $(OutPutOpt) $(LIBNAME).$(DllSuf)


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	# $(RM) lwlyn_nieves_ut


FORCE:

# DO NOT DELETE
