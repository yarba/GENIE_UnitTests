#
# GENIE Makefile 
#
# Author: Julia Yarba, FNAL 
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
include $(GENIE)/src/make/Make.include

ifdef CPP_INCLUDES
INCLUDES := $(CPP_INCLUDES) 
endif

# Add extra libraries needed for these executables
GENIE_GENERATOR_LIBS   = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
LIBRARIES := $(GENIE_GENERATOR_LIBS)  $(LIBRARIES)  

# MISC_SRC := $(wildcard *.cxx)

SPL_EVT_SRC := gen_spl_evts.cxx
SPL_EVT_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(SPL_EVT_SRC))) 

PARAM_CFG_SRC := get_genie_param_from_config.cxx SynthEvent.cxx
PARAM_CFG_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(PARAM_CFG_SRC)))

CONF_XSEC_SRC := configure_xsec_model.cxx SynthEvent.cxx
CONF_XSEC_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(CONF_XSEC_SRC)))

CONF_CUSTOM_SRC := get_config_from_custom_path.cxx
CONF_CUSTOM_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(CONF_CUSTOM_SRC)))

MULT_TUNES_SRC := multiple_tunes.cxx SynthEvent.cxx
MULT_TUNES_OBJ  = $(addsuffix .$(ObjSuf), $(basename $(MULT_TUNES_SRC)))

all: gen_spl_evts get_param conf_xsec conf_custom mult_tunes

gen_spl_evts: FORCE
	$(CXX) $(CXXFLAGS) -c $(SPL_EVT_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(SPL_EVT_OBJ) $(LIBRARIES) -o gen_spl_evts 

get_param: FORCE
	$(CXX) $(CXXFLAGS) -c $(PARAM_CFG_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(PARAM_CFG_OBJ) $(LIBRARIES) -o get_param 

conf_xsec: FORCE
	$(CXX) $(CXXFLAGS) -c $(CONF_XSEC_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(CONF_XSEC_OBJ) $(LIBRARIES) -o conf_xsec 

conf_custom: FORCE
	$(CXX) $(CXXFLAGS) -c $(CONF_CUSTOM_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(CONF_CUSTOM_OBJ) $(LIBRARIES) -o conf_custom 

mult_tunes: FORCE
	$(CXX) $(CXXFLAGS) -c $(MULT_TUNES_SRC) $(INCLUDES) 
	$(LD) $(LDFLAGS) $(MULT_TUNES_OBJ) $(LIBRARIES) -o mult_tunes 


purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	$(RM) gen_spl_evts
	$(RM) get_param
	$(RM) conf_xsec
	$(RM) conf_custom
	$(RM) mult_tunes


FORCE:

# DO NOT DELETE
