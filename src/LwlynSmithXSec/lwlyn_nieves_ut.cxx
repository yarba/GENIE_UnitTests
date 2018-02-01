// --> #define BOOST_TEST_DYN_LINK
// --> #define BOOST_TEST_MODULE Genie

#define BOOST_TEST_ALTERNATIVE_INIT_API
#undef BOOST_TEST_MAIN
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <iostream>

// these includes below are common for lwlyn and nieves
#include "Framework/Messenger/Messenger.h"
#include "Framework/Interaction/Interaction.h"
// --> r2xx-series  #include "PDG/PDGCodes.h"
// --> r2xx-series #include "PDG/PDGLibrary.h"
// --> r2xx-series #include "PDG/PDGUtils.h"
#include "Framework/ParticleData/PDGCodes.h"
#include "Framework/ParticleData/PDGLibrary.h"
#include "Framework/ParticleData/PDGUtils.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;
// using namespace boost::test_tools;

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
   
   
double tolerance_in_percent = 0.001;

// lwlyn-specific
// ---> r2xx-series ---> #include "LlewellynSmith/LwlynSmithQELCCPXSec.h"
#include "Physics/QuasiElastic/XSection/LwlynSmithQELCCPXSec.h"

void lwlyn_ut()
{
      
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
   lwlyn->Configure( "Default" );
         
   // bool   pvalid = lwlyn->ValidProcess( &inter );
   // cout << " process valid: " << pvalid << endl; 
   BOOST_CHECK( lwlyn->ValidProcess( &inter ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 
   
   double xsec = lwlyn->XSec( &inter, kpst );
   BOOST_REQUIRE_NE( xsec, 0. );
   BOOST_CHECK_CLOSE( xsec, 9.08713e-12, tolerance_in_percent );
   //
   // JY: this one below will artificially emulate an error ^_^
   //
   // ---> BOOST_CHECK_CLOSE( xsec, 8.08713e-12, tolerance_in_percent );

   // ---> later ! double integral = lwlyn->Integral( &inter ); // should be 1.41266e-10
   
   delete lwlyn;
   
   return;
}

// nieves-specific

// ---> r2xx-series ---> #include "LlewellynSmith/NievesQELCCPXSec.h"
#include "Physics/QuasiElastic/XSection/NievesQELCCPXSec.h"

void nieves_ut()
{

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
   niev.Configure("Default");

   BOOST_CHECK( niev.ValidProcess( &inter ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 

   double xsec = niev.XSec( &inter, kpst );
   BOOST_REQUIRE_NE( xsec, 0. );
   BOOST_CHECK_CLOSE( xsec, 1.3332e-11, tolerance_in_percent );
   
   return;

}

// below are a couple of "toys" to serve as examples for future development
/*
void dvalue1_ut()
{

   double tolerance_in_percent = 0.0;
   string argname = "-tolerance_in_percent";
    
   for ( int i=1; i<framework::master_test_suite().argc; ++i )
   {
      if ( strcmp( framework::master_test_suite().argv[i], argname.c_str() ) == 0 )  
      {
         if ( (i+1) < framework::master_test_suite().argc )
	 {
	    tolerance_in_percent = atof( framework::master_test_suite().argv[i+1] );
	 }
      } 
   }

   double x = 10.0;
   double y = 10.0001;
   //
   // this will work in boost 1.57.0
   // bear in mind that the 3rd argument is expressed in **PERCENTS** 
   // (i.e. "0.0001" means 0.0001%)
   //
   BOOST_CHECK_CLOSE( x, y, tolerance_in_percent );
   //
   // this is available starting boost 1.60.x series
   // bear in mind that in this case tolerance can be given as an absolute value
   //
   // BOOST_TEST( x == y, boost::test_tools::tolerance(0.001) );
   
   return;

}
*/
/*
void dvalue2_ut()
{

   double x = 10.0;
   double y = 10.0005;
   BOOST_TEST( x == y );
   
   return;

}
*/
/* NOTE: no need to have input args - the way unit_test_main is called,
         the args will get in (somehow) */
bool init_unit_test_suite( /* int argc, char *argv[] */ )
{

   auto ts = BOOST_TEST_SUITE("lwlyn_ut");
   ts->add( BOOST_TEST_CASE( &lwlyn_ut ) );
   ts->add( BOOST_TEST_CASE( &nieves_ut ) );
   // ---> later !!! ts->add( BOOST_TEST_CASE( &dvalue1_ut ) );
   // ---> later !!! ts->add( BOOST_AUTO_TEST_CASE( &dvalue2_ut, *tolerance(0.0001) ) );
   framework::master_test_suite().add(ts);
     
   return true;

}

int main( int argc, char *argv[] )
{

   // try to silence GENIE Messenger just a little bit...
   //
   Messenger::Instance()->SetPrioritiesFromXmlFile("Messenger_whisper.xml");
   
   cout << "***** Starting Unit Tests *****" << endl;
   
   return unit_test_main( &init_unit_test_suite, argc, argv );

}

