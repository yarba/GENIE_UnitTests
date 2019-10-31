
#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

using namespace std;
using namespace genie;
using namespace boost::unit_test;

   // A few boost tips:
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
   // however, this one below doesn't compile, complaining 
   // of comparison between pointer and integer... 
   // ... even if I pass in a NULL instead of 0
   //
   // BOOST_CHECK_NE( lwlyn, NULL );

// lwlyn-specific
#include "Physics/QuasiElastic/XSection/LwlynSmithQELCCPXSec.h"

void lwlyn_ut()
{
      
   // silence TransverseEnhancementFFModel messages
   //
   Messenger::Instance()->SetPriorityLevel( "TransverseEnhancementFFModel", pFATAL );

   EventRecord* evt = new SynthEvent();

   // NOTE: it can as well be a local object rather than a pointer
   //       it's done this way only to "test" for a valid pointer with 
   //       the BOOST_CHECK functionality 
   //
   LwlynSmithQELCCPXSec* lwlyn = new LwlynSmithQELCCPXSec();
   
   BOOST_CHECK( lwlyn != 0 );
   
   // now configure it, for (future) XSec calculation
   //
   // NOTE: Calling Configure(...) before exists an InitialState object (part of event record) 
   //       will results in a segfault at the very exit, with the the stack as shown below:
// #0  0x0000000000df1ee0 in ?? ()
// #1  0x00007ffff6db95be in genie::Messenger::Instance () at Messenger.cxx:95
// #2  0x00007ffff6b80e74 in genie::Registry::Clear (this=0xadcf10, force=true) at Registry.cxx:878
// #3  0x00007ffff6b7a9ae in genie::Registry::~Registry (this=0xadcf10, __in_chrg=<value optimized out>) at Registry.cxx:121
// #4  0x00007ffff6b7aa48 in genie::Registry::~Registry (this=0xadcf10, __in_chrg=<value optimized out>) at Registry.cxx:122
// #5  0x00007ffff693bd79 in genie::AlgConfigPool::~AlgConfigPool (this=0xad2c40, __in_chrg=<value optimized out>) at AlgConfigPool.cxx:88
// #6  0x00007ffff693bf1a in genie::AlgConfigPool::~AlgConfigPool (this=0xad2c40, __in_chrg=<value optimized out>) at AlgConfigPool.cxx:96
// #7  0x00007ffff6940d51 in genie::AlgConfigPool::Cleaner::~Cleaner (this=0x7ffff6b62b48, __in_chrg=<value optimized out>)
   //
   lwlyn->Configure( "Dipole" );

   BOOST_CHECK( lwlyn->ValidProcess( evt->Summary() ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 
   
   double xsec = lwlyn->XSec( evt->Summary(), kpst );
   
   BOOST_REQUIRE_NE( xsec, 0. );
   
   BOOST_CHECK_CLOSE( xsec, qel_xsec::lwlyn::xsec_default, tolerance_in_percent ); 

#ifdef PRINTOUT
   std::ostringstream os;
   os << xsec;
   std::string s = "static const double xsec_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( "namespace lwlyn {" );
   UpdateBenchmark::Instance()->Write( s );
   UpdateBenchmark::Instance()->Write( "} // end namespace lwlyn" );
#endif
   
   //
   // JY: this one below will artificially emulate an error ^_^
   //
   // ---> BOOST_CHECK_CLOSE( xsec, 8.08713e-12, tolerance_in_percent );

   // ---> later ! double integral = lwlyn->Integral( &inter ); // should be 1.41266e-10
   
   delete evt;
   
   delete lwlyn;
   
   return;
}
