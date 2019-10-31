
#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

using namespace std;
using namespace genie;
using namespace boost::unit_test;

#include "Physics/QuasiElastic/XSection/AhrensNCELPXSec.h"

void ahrens_ut()
{
      
   EventRecord* evt = new SynthEvent();
   evt->Summary()->SetProcInfo( ProcessInfo( kScQuasiElastic, kIntWeakNC ) );

   // NOTE: it can as well be a local object rather than a pointer
   //       it's done this way only to "test" for a valid pointer with 
   //       the BOOST_CHECK functionality 
   //
   AhrensNCELPXSec* ahr = new AhrensNCELPXSec();
   
   BOOST_CHECK( ahr != 0 );
   
   // NOTE: Unfortunately, it does NOT seem to be possible to create a local config (Registry),
   //       and use it to configure an XSec model (Algorithm)
   //       The reason is the following: 
   //       Most, if not all, XSec models have an sub-algorithm (with its own configuration),
   //       and such sub-algorithm gets retrieved grom AlgFactory, which in turn gets populated
   //       from the "global" config (pool)
   //       There does NOT seem to be a method to set an sub-algorithm directly to an Algorithm
   //       (although there's a method Algorithm* Algorithm::SubAlg(string))
   //       There does NOT seem to be a method to directly add an Algorithm to the AlgFactory 
   //       Thus at this point configuring an XSec via "global" pool seems to be the only way
   //
   ahr->Configure( "Default" );

   BOOST_CHECK( ahr->ValidProcess( evt->Summary() ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 
   
   double xsec = ahr->XSec( evt->Summary(), kpst );
   
   BOOST_REQUIRE_NE( xsec, 0. );
   
//   BOOST_CHECK_CLOSE( xsec, 8.58382e-12, tolerance_in_percent ); 
   BOOST_CHECK_CLOSE( xsec, qel_xsec::ahrens::xsec_default, tolerance_in_percent ); 

#ifdef PRINTOUT
   std::ostringstream os;
   os << xsec;
   std::string s = "static const double xsec_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( "namespace ahrens {" );
   UpdateBenchmark::Instance()->Write( s );
   UpdateBenchmark::Instance()->Write( "} // end namespace ahrens" );
#endif
      
   delete evt;
   delete ahr;
   
   return;
}
