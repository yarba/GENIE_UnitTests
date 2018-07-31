/*
#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_suite.hpp>

// #include <iostream>

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

   //
   // there're (at least) 3 levels of "severity:
   // BOOST_WARN_EQUAL(left, right);
   // BOOST_CHECK_EQUAL(left, right);
   // BOOST_REQUIRE_EQUAL(left, right);
   //
   // there're also the "NE counterparts":
   // BOOST_WARN_NE(left, right);
   // BOOST_CHECK_NE(left, right);
   // BOOST_REQUIRE_NE(left, right); 
   //     
   //
   // however, this does't compile, complaining of comparison
   // between pointer and integer... 
   // ... even if I pass in a NULL instead of 0
   //
   // BOOST_CHECK_NE( lwlyn, NULL );


// It'd make sense to declare it as global 
// if there's a group of tests that "share" the same tolerance,
// and they're all implemented in one source file
//
// double tolerance_in_percent = 0.001;

// lwlyn-specific
#include "Physics/QuasiElastic/XSection/LwlynSmithQELCCPXSec.h"

void lwlyn_ut()
{
      
   double tolerance_in_percent = 0.001;
  
   // Carbon target nucleus + nu_mu projectile (probe)
   //
   InitialState istate( 6, 12, 14 );
   // make sure to set hit tgt nuc to neutron with the nu_mu probe
   // ... or to proton with nu_mu_bar probe
   istate.TgtPtr()->SetHitNucPdg( 2112 );
   double Ev = 3; // in GeV
   TLorentzVector nup4(0., 0., Ev, Ev); //px, py, pz, E
   istate.SetProbeP4( nup4 );
   //
   ProcessInfo  procinfo( kScQuasiElastic, kIntWeakCC );
   //          
   Interaction inter( istate, procinfo );
   inter.KinePtr()->SetQ2( 2.0 ); // just to set something sensible...

   // NOTE: it can as well be a local object
   //       at present it's done this way only to "test" 
   //       for a valid pointer with the BOOST_CHECK functionality 
   //
   LwlynSmithQELCCPXSec* lwlyn = new LwlynSmithQELCCPXSec();
   
   BOOST_CHECK( lwlyn != 0 );
   
   // now configure it, for (future) XSec calculation
   //
   // NOTE: Calling Configure(...) before an InitialState object exists 
   //       will results in a segfault at the very exit; the stack is below:
// #0  0x0000000000df1ee0 in ?? ()
// #1  0x00007ffff6db95be in genie::Messenger::Instance () at Messenger.cxx:95
// #2  0x00007ffff6b80e74 in genie::Registry::Clear (this=0xadcf10, force=true) at Registry.cxx:878
// #3  0x00007ffff6b7a9ae in genie::Registry::~Registry (this=0xadcf10, __in_chrg=<value optimized out>) at Registry.cxx:121
// #4  0x00007ffff6b7aa48 in genie::Registry::~Registry (this=0xadcf10, __in_chrg=<value optimized out>) at Registry.cxx:122
// #5  0x00007ffff693bd79 in genie::AlgConfigPool::~AlgConfigPool (this=0xad2c40, __in_chrg=<value optimized out>) at AlgConfigPool.cxx:88
// #6  0x00007ffff693bf1a in genie::AlgConfigPool::~AlgConfigPool (this=0xad2c40, __in_chrg=<value optimized out>) at AlgConfigPool.cxx:96
// #7  0x00007ffff6940d51 in genie::AlgConfigPool::Cleaner::~Cleaner (this=0x7ffff6b62b48, __in_chrg=<value optimized out>)
   //
   // lwlyn->Configure( "Default" );
   lwlyn->Configure( "Dipole" );

   // bool   pvalid = lwlyn->ValidProcess( &inter );
   // cout << "LwlynSmithQELCCPXSec process valid: " << pvalid << endl; 
   BOOST_CHECK( lwlyn->ValidProcess( &inter ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 
   
   double xsec = lwlyn->XSec( &inter, kpst );
   BOOST_REQUIRE_NE( xsec, 0. );
   // BOOST_CHECK_CLOSE( xsec, 9.08713e-12, tolerance_in_percent ); // as ov GENIE v2.x.x-series
   BOOST_CHECK_CLOSE( xsec, 9.11463e-12, tolerance_in_percent ); // going towards GENIE v3-series
   //
   // JY: this one below will artificially emulate an error ^_^
   //
   // ---> BOOST_CHECK_CLOSE( xsec, 8.08713e-12, tolerance_in_percent );

   // ---> later ! double integral = lwlyn->Integral( &inter ); // should be 1.41266e-10
   
   delete lwlyn;
   
   return;
}
