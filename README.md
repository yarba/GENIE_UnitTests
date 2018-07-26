# GENIE_UnitTests

This is the initial collection of unit tests for the GENIE nu(bar)+A event generator.

As of Feb.2018, we have two branches - master and genie_r2xx_series.

==========

Master is meant to work with the ongoing development towards GENIE v3-series, and is adapted
to its code infrastructure that recently went through a major restructuring.

It has been tested with the "e14:prof" installs of root v6_10_04d, lhapdf v5_9_1h, log4cpp v1_1_2,
and boost v1_64_0.

==========

Branch genie_r2xx_series is supposed to be compatible with the R-2_X_Y series (e.g. 2_12_10
release that is expected shortly).

It has been tested with a "trunk" revision of genie/generator built with the against
"e7:prof" installs of root v5_34_25a, lhapdf v5_9_1b, and log4cpp v1_1_1b.

It also requires boost v1_57_0 (with the e7:prof qualifier as installed at FNAL).

It should also build and run with boost v1_63_0a, e10:prof install (current at FNAL ?).
However, in the reasonably near future we plan some updates to the application code 
since boost 1.6x series has some additional attractive features and functionalities
that were not available in version 1_57_0. 

==========

GENERAL INFORMATION ABOUT THE TESTS

Unit testing is a software testing method by which individual units of source code, sets of one 
or more computer program modules together with associated control data, usage procedures, and 
operating procedures, are tested to determine whether they perform as exopected.

The most traditional unit test exercises the lowest level componests, e.g. public methods of 
a particular class in the simplest application.

In the concept of GENIE the situation is somewhat more complex and in order to test features even 
of a single class one often need several other classes/components to be involved.

However, the idea of this unit testing suite is to implement (and maintain) a collection of
simplest possible application that would exercise features of various GENIE code components 
as fast as feasible.  

==========

CODE INFRASTRUCTURE

GENIE UNit Test Suite cirrently resides in
https://github.com/yarba/GENIE_UnitTests

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

For contributors whi are to develop additional unit test applications we suggest the following:

a) Clone the Suite from GitHub
git clone https://github.com/yarba/GENIE_UnitTests.git

b) Using either XSecUT or ReWeiUT as an example/pattern, create a new subdirecory to populate 
with the new applications
NOTE: The XSecUT applications are a bit simpler than the ReWeiUT ones are. 
E.g. the src/XSecUT/lwlyn_ut.cc application maybe an easier example to follow. 
But this may depend on the use case.

c) E.g. src/XSecUT/Makefile can serve an an example of a makefile.

d) Once the application is ready, it can be added to the list of all in src/MasterUT/ExternalFunctions.h
and included in one or another "BOOST_TEST_SUITE", as shown in src/MasterUT/master_init_ut.cxx





