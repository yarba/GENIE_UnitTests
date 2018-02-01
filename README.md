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

