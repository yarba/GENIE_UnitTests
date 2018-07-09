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

UT_SRC := $(wildcard *.cxx)
UT_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(UT_SRC))) 
EXTRA_SRC = $(wildcard ../XSecUT/*.cxx ../ReWeiUT/*.cxx)
EXTRA_OBJ = $(addsuffix .$(ObjSuf), $(basename $(EXTRA_SRC)))

all: master_ut 

master_ut: FORCE
	# $(CXX) $(CXXFLAGS) -c lwlyn_nieves_ut.cxx $(INCLUDES) 
	# $(LD) $(LDFLAGS) lwlyn_nieves_ut.$(ObjSuf) $(LIBRARIES) $(BOOST_UT_LIBS) -o lwlyn_nieves_ut 
	$(CXX) $(CXXFLAGS) -c $(UT_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(UT_OBJ) $(EXTRA_OBJ) $(LIBRARIES) $(BOOST_UT_LIBS) -o master_ut 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	$(RM) master_ut


FORCE:

# DO NOT DELETE
