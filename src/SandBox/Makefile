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
# --> INCLUDES := $(CPP_INCLUDES) -I$(BOOST_INC)
INCLUDES := $(CPP_INCLUDES) 
else
# --> INCLUDES := $(INCLUDES) -I$(BOOST_INC)
INCLUDES := $(INCLUDES) 
endif

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
# --> BOOST_UT_LIBS = -L$(BOOST_LIB) -lboost_unit_test_framework
LIBRARIES := $(GENIE_GENERATOR_LIBS)  $(LIBRARIES)  

# MISC_SRC := $(wildcard *.cxx)

SPL_EVT_SRC := gen_spl_evts.cxx
SPL_EVT_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(SPL_EVT_SRC))) 

PARAM_CFG_SRC := get_genie_param_from_config.cxx SynthEvent.cxx
PARAM_CFG_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(PARAM_CFG_SRC)))

CONF_XSEC_SRC := configure_xsec_model.cxx SynthEvent.cxx
CONF_XSEC_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(CONF_XSEC_SRC)))

all: gen_spl_evts get_param conf_xsec

gen_spl_evts: FORCE
	$(CXX) $(CXXFLAGS) -c $(SPL_EVT_SRC) $(INCLUDES) 
# -->	$(LD) $(LDFLAGS) $(MISC_OBJ) $(LIBRARIES) $(BOOST_UT_LIBS) -o gen_spl_evts 
	$(LD) $(LDFLAGS) $(SPL_EVT_OBJ) $(LIBRARIES) -o gen_spl_evts 

get_param: FORCE
	$(CXX) $(CXXFLAGS) -c $(PARAM_CFG_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(PARAM_CFG_OBJ) $(LIBRARIES) -o get_param 

conf_xsec: FORCE
	$(CXX) $(CXXFLAGS) -c $(CONF_XSEC_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(CONF_XSEC_OBJ) $(LIBRARIES) -o conf_xsec 

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	$(RM) gen_spl_evts
	$(RM) get_param
	$(RM) conf_xsec


FORCE:

# DO NOT DELETE
