# UnitTests

This is the initial collection of unit tests for the GENIE nu(bar)+A event generator.

==========

GENERAL INFORMATION ABOUT THE TESTS

Unit testing is a software testing method by which individual units of source code, sets of one 
or more computer program modules together with associated control data, usage procedures, and 
operating procedures, are tested to determine whether they perform as exopected.

The most traditional unit test exercises the lowest level componests, e.g. public methods of 
a particular class in the simplest application.
E.g. the simplest and perhaps the most classical example is to instantiate an object by calling 
its constructor, then call one or several public methods and ensure their perform as expected,
via comparing against well defined metric. 

In the concept of GENIE the situation is somewhat more complex and in order to test features even 
of a single class one often need several other classes/components to be involved.

However, the idea of this unit testing suite is to implement (and maintain) a collection of
simplest possible application that would exercise features of various GENIE code components 
as fast as feasible.  

==========

CODE INFRASTRUCTURE

GENIE Unit Test Suite cirrently resides in https://github.com/GENIE-MC/UnitTests

NOTE: that this is public repository.

In order to detect failures and/or deviation from expected and/or to report seccessfull completion, 
GENIE Unit Test Suite is using features of  the boost unit testing framework: 
https://www.boost.org/doc/libs/1_44_0/libs/test/doc/html/utf.html

The Suite is organized as follows:

src/MasterUT contains high level code, main and initialization, that glue various tests together 
and run them in one go.
The list of unit test applications is defined in /src/MasterUT/ExternalFunctions.h 

src/XSecUT contains applications that unit-test features/methods of LwlynSmith and Nieves cross section
models and ensure that these components perform as expected.
If additional unit tests for cross section models are to be implemented, they should be committed 
to this subdirectory.

src/ReWei contains an application that tests so-called ReWeighting module which calculates uncertanties 
(ina form of event weight) associated with variations of parameters of the CCQE cross-section model.
An additional application, for the NCEL cross-esction reweighting tools, is in progress.
If more unit tests for GENIE reweighting modules are to be added, they should be committed to this 
subdirectory. 

As more unit test application for other GENIE code components are implemented, additional subdirectories
maybe created, as needed.

Makefiles are supplied in each subdirecory to build the applications.

src/Makefile is a "master" makefile that steers the build procedure through the right subdirectories 
in the right order.

==========

Provided that GENIE, required extefrnal packages, and boost package are properly setup, one can build
the Unit Tests by issueing the `make' command in the `src' directory. 

==========

HUMBLE SUGGESTIONS FOR DEVELOPERS/CONTRIBUTORS

We would like to offer several tips to potential contributors who are to develop additional 
unit test applications.

This tips aim at working on the GENIE virtual machine at FNAL: geniegpvm01.fnal.gov

In principle, a family of GENIE releases and all the necessary external toools are centrally installed 
in the cvmfs space and are accessible from geniegpvm01.

However, we presume that developers will work with their own build of GENIE.

We assume building GENIE vs root v6-series (although building vs root5-series is also possible). 

(Example) Instructions below show how to build GENIE on geniegpvm01 using pre-facbricated 
external packages.

 source /cvmfs/fermilab.opensciencegrid.org/products/genie/bootstrap_genie_ups.sh  
 setup root v6_12_06a -q e17:prof
 setup lhapdf v5_9_1k -q e17:prof
 setup log4cpp v1_1_3a -q e17:prof
 cd <your-work-area>

If you wish to check out public revision of GENIE (incl. trunk) with read-only access, please do:

 git clone git@github.com:GENIE-MC/Generator.git <your-genie-area>

NOTE-1: In some cases "git clone" as shown will NOT work properly (ssh specifics or whatever reason).
As an alternative, one may try as follows:
  git clone https://git@github.com/GENIE-MC/Generator.git <your-genie-area>


NOTE-2: If you don't specify <your-genie-area>, the code will be checked out into (sub)directory Generator.

NOTE-3: Due to migration from HepForge/SVN to GitHub, port of development/feature branches is still in progress.

To build GENIE:

 cd <your-genie-area>

Setup mandatory GENIE environment variable :

 GENIE=$PWD
 
Configure GENIE build:
 
 ./configure \
  --enable-test \
  --enable-numi \
  --enable-gsl \
  --enable-lhapdf5 \
  --with-optimiz-level=O3 \
  --with-pythia6-lib=$PYTHIA6_LIBRARY \
  --with-lhapdf5-lib=$LHAPDF_FQ_DIR/lib \
  --with-lhapdf5-inc=$LHAPDF_FQ_DIR/include \
  --with-log4cpp-lib=$LOG4CPP_FQ_DIR/lib \
  --with-log4cpp-inc=$LOG4CPP_FQ_DIR/include \
  --with-libxml2-lib=$LIBXML2_FQ_DIR/lib \
  --with-libxml2-inc=$LIBXML2_FQ_DIR/include/libxml2 1>configure.out 2>configure.err

If you need a debug build of GENIE, you'll need to activate the debug option and to use O0 optimization
instead of O3; please use the following flags on input to the configure script:

  --enable-debug 
  --with-optimiz-level=O0 
  
Build GENIE:

 make
  
Extend LD_LIBRARY_PATH and PATH:

 LD_LIBRARY_PATH=$GENIE/lib:$LD_LIBRARY_PATH
 PATH=$GENIE/bin:$PATH
 
 
Now you need to build Reweight package.

BEAR IN MIND THAT STARTING OCT.2018 Tools/ReWeight PACKAGE HAS MOVED OUT OF GENIE (Generator)
INTO ITS OWN REPOSITORY Reweight.

 git clone git@github.com:GENIE-MC/Reweight.git <your-genie-RW-area>

NOTE-4: As already mentioned earlier, in some cases "git clone" will NOT work as shown above.
Alternative was is the following:
  git clone https://git@github.com/GENIE-MC/Reweight.git <your-genie-RW-area>

NOTE-5: If you don't specify <your-genie-RW-area>, the code will be checked out into (sub)directory Reweight.


 cd <your-genie-RW-area>

Setup mandatory GENIE_REWEIGHT environment variable :

 GENIE_REWEIGHT=$PWD

Build Reweight:

  make
  
Extend LD_LIBRARY_PATH and PATH to include RW libraries and executables:

 LD_LIBRARY_PATH=$GENIE_REWEIGHT/lib:$LD_LIBRARY_PATH
 PATH=$GENIE_REWEIGHT/bin:$PATH


In order to build GENIE_UnitTests you'll also need boost packakge wich is also centrally
available on geniegpvm01:

 setup boost v1_66_0a -q e17:prof

Obtain GENIE Unit Tests Suite:
The easiest way to get started is to clone the Suite from GitHub:

 cd <your-work-area>
 git clone  git@github.com:GENIE-MC/UnitTests.git
 
NOTE-6: As already mentioned earlier, in some cases "git clone" will NOT work as shon above.
Alternative was is the following:
  git clone https://git@github.com/GENIE-MC/UnitTests.git 

NOTE-7: in principle, for future development it may be more practical to fork UnitTests
repository, do all the development there, then initiate a Git pull request to have updates
megred into the main branch.

To build the Unit Tests Suite, go to the GENIE_UnitTests/src directory and execute "make":

 cd UnitTests/src
 make

To run the suite, do the following:

 MasterUT/master_ut
 
WARNING !!! If you work out of a specific development/feature branch, you should make sure 
that all the configuration files ( config/*.xml, config/G*/*.xml, etc.) are up-to-date.
Otherwise you may experinece problems at run time.
 
 
If you want to develop an additional unit test, you may be interested in the following:

a) Using either GenieUT/Physics/QuasiElastic or ReWeiUT as an example/pattern, create a new subdirecory to populate 
with the new applications
NOTE: The GenieUT/Physics/QuasiElastic applications are a bit simpler than the ReWeiUT ones are. 
E.g. src/GenieUT/Physics/QuasiElastic/lwlyn_ut.cc or src/GenieUT/Physics/QuasiElastic/nieves_ut.cxx applications 
maybe easier examples to follow. 
But this may depend on the use case.

b) E.g. src/GenieUT/Physics/QuasiElastic/Makefile can serve an an example of a makefile.

c) Once the application is ready, it can be added to the list of all in src/MasterUT/ExternalFunctions.h
and included in one or another "BOOST_TEST_SUITE", as shown in src/MasterUT/master_init_ut.cxx

MISC: WALK-THROUGH UNIT TEST FOR THE NIEVES XSEC MODEL

The source code for the Nieves XSec unit test is src/GenieUT/Physics/QuasiElastic/lwlyn_ut.cxx

All necessary (common) header, except LwlynSmithQELCCPXSec.h one, are encapsulated in 
src/GenieUT/Physics/QuasiElastic/CommonXSec.h

First of all, one needs to setup the test.

In order to calculate an XSec, an Interaction object is needed, which in turn requires 
an InitialState and a ProcessInfo.
Although this can be done explicitly, in this application this is implemented within SynthEvent class 
(see src/SynthEvent). The SynthEvent object(s) can be re-used in a number of other unit tests.
In the nieves_ut.cxx, the SynthEvent is instanciated at line 37.

Next, the LwlynSmithQELCCPXSec object is instanciated on line 43 and properly configured on line 60.

Lines 62 through 70 are actually the "beef" of the unit test.

Line 62 shows
a) how a public method ValidProcess of the LwlynSmithQELCCPXSec object is called
b) how boost's BOOST_CHECK functionality is used to ensure the method returns the right value

Line 66 illustrates how the XSec public mathod of the LwlynSmithQELCCPXSec object is called to calculate
differential cross section for a given Interaction and phase space.

Line 68 shows how boost's functionality is used to make sure the calculated cross sections is non-zero.

Line 70 shows how to use boost's functionality to compare the calculated cross section vs predefined
value and to make sure that the difference between the two does not exceed 0.001% (the tolarnce itself
is define at the very beginning of the code, on line 14).

Lines 88 and 90 show the "tear down", i.e. deletion of the created objects.


 





