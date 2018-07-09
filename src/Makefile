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

MODULES := XSecUT ReWeiUT MasterUT

.PHONY: all $(MODULES)

all:     $(MODULES)

$(MODULES):
	@echo "** Building... $@" 
	$(MAKE) -C $@ 

clean:
	@echo "** Cleaning..."
	$(foreach mod, $(MODULES), make -C $(mod) clean;)
