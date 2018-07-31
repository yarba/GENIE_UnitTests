/*
#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <iostream>

// these includes below are common for lwlyn and nieves
#include "Framework/Interaction/Interaction.h"
#include "Framework/ParticleData/PDGCodes.h"
#include "Framework/ParticleData/PDGLibrary.h"
#include "Framework/ParticleData/PDGUtils.h"
*/

#include "CommonXSec.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;


// It'd make sense to declare it as global 
// if there's a group of tests that "share" the same tolerance,
// and they're all implemented in one source file
//
// double tolerance_in_percent = 0.001;

// nieves-specific
#include "Physics/QuasiElastic/XSection/NievesQELCCPXSec.h"

void nieves_ut()
{
      
   double tolerance_in_percent = 0.001;

   // this part below is identical between lwlyn and niev !!!
   //
   InitialState istate( 6, 12, 14 );
   istate.TgtPtr()->SetHitNucPdg( 2112 );
   double Ev = 3; // in GeV
   TLorentzVector nup4(0., 0., Ev, Ev); //px, py, pz, E
   istate.SetProbeP4( nup4 );
   //
   ProcessInfo  procinfo( kScQuasiElastic, kIntWeakCC );
   //        
   Interaction inter( istate, procinfo );
   inter.KinePtr()->SetQ2( 2.0 ); // just to set something sensible...
   
   NievesQELCCPXSec niev;
   // niev.Configure("Default");
   // niev.Configure("Dipole");
   niev.Configure( "ZExp" );

   BOOST_CHECK( niev.ValidProcess( &inter ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 

   double xsec = niev.XSec( &inter, kpst );
   BOOST_REQUIRE_NE( xsec, 0. );
   // BOOST_CHECK_CLOSE( xsec, 1.335315e-11, tolerance_in_percent ); // going towards GENIE v3-series... but this was for "Dipole"
   BOOST_CHECK_CLOSE( xsec, 1.195979e-11, tolerance_in_percent ); // this is for "ZExp", towards v3-series
   
   return;
}
