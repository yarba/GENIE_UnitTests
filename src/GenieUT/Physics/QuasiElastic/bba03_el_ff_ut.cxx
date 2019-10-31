#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

#include "Physics/QuasiElastic/XSection/BBA03ELFormFactorsModel.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void bba03_el_ff_ut()
{

   EventRecord* evt = new SynthEvent();

   BBA03ELFormFactorsModel* bba = new BBA03ELFormFactorsModel();

   BOOST_CHECK( bba != 0 );

   // configure from tune (global config pool)
   //
   bba->Configure("Default");

// (bba->GetConfig()).Print(cout), as of Oct.30, 2019, will produce the following:  
//
// Registry name: [genie::BBA03ELFormFactorsModel/Default_summary] - Write Status: [unlocked] - Inhibited Item Locking: [on] - # entries:  25
// |--------------------------------> AnomMagnMoment-N [double] [unlocked] [l] : -1.91304
// |--------------------------------> AnomMagnMoment-P [double] [unlocked] [l] : 2.793
// |-------------------------------------> BBA03-Gen-a [double] [unlocked] [l] : 0.942
// |-------------------------------------> BBA03-Gen-b [double] [unlocked] [l] : 4.61
// |-----------------------------------> BBA03-Gep-a10 [double] [unlocked] [l] : -0.09371
// |-----------------------------------> BBA03-Gep-a12 [double] [unlocked] [l] : 0.01076
// |------------------------------------> BBA03-Gep-a2 [double] [unlocked] [l] : 3.253
// |------------------------------------> BBA03-Gep-a4 [double] [unlocked] [l] : 1.422
// |------------------------------------> BBA03-Gep-a6 [double] [unlocked] [l] : 0.08582
// |------------------------------------> BBA03-Gep-a8 [double] [unlocked] [l] : 0.3318
// |-----------------------------------> BBA03-Gmn-a10 [double] [unlocked] [l] : 0.008912
// |-----------------------------------> BBA03-Gmn-a12 [double] [unlocked] [l] : 0
// |------------------------------------> BBA03-Gmn-a2 [double] [unlocked] [l] : 3.043
// |------------------------------------> BBA03-Gmn-a4 [double] [unlocked] [l] : 0.8548
// |------------------------------------> BBA03-Gmn-a6 [double] [unlocked] [l] : 0.6806
// |------------------------------------> BBA03-Gmn-a8 [double] [unlocked] [l] : -0.1287
// |-----------------------------------> BBA03-Gmp-a10 [double] [unlocked] [l] : 0.0003705
// |-----------------------------------> BBA03-Gmp-a12 [double] [unlocked] [l] : -7.063e-06
// |------------------------------------> BBA03-Gmp-a2 [double] [unlocked] [l] : 3.104
// |------------------------------------> BBA03-Gmp-a4 [double] [unlocked] [l] : 1.428
// |------------------------------------> BBA03-Gmp-a6 [double] [unlocked] [l] : 0.1112
// |------------------------------------> BBA03-Gmp-a8 [double] [unlocked] [l] : -0.006981
// |-------------------------------------> BBA03-Q2Max [double] [unlocked] [l] : 6
// |-------------------------------------> CommonParam [string] [unlocked] [l] : MagnMoments
// |-------------------------------------------> EL-Mv [double] [unlocked] [l] : 0.84
//

/*   // explicit (local) configuration would look as follows:
   //
   Registry* rg = new Registry( "bba03_el_ut" );
   rg->UnLock();
   rg->Set( "CommonParam",      "MagnMoments" );
   rg->Set( "AnomMagnMoment-N", -1.91304 ); 
   rg->Set( "AnomMagnMoment-P",  2.793 ); 
   rg->Set( "BBA03-Gen-a",       0.942 );
   rg->Set( "BBA03-Gen-b",       4.61 );
   rg->Set( "BBA03-Gep-a10",    -0.09371 );
   rg->Set( "BBA03-Gep-a12",     0.01076 );
   rg->Set( "BBA03-Gep-a2",      3.253 );
   rg->Set( "BBA03-Gep-a4",      1.422 );
   rg->Set( "BBA03-Gep-a6",      0.08582 );
   rg->Set( "BBA03-Gep-a8",      0.3318 );
   rg->Set( "BBA03-Gmn-a10",     0.008912 );
   rg->Set( "BBA03-Gmn-a12",     0. );
   rg->Set( "BBA03-Gmn-a2",      3.043 );
   rg->Set( "BBA03-Gmn-a4",      0.8548 );
   rg->Set( "BBA03-Gmn-a6",      0.6806 );
   rg->Set( "BBA03-Gmn-a8",     -0.1287 );
   rg->Set( "BBA03-Gmp-a10",     0.0003705 );
   rg->Set( "BBA03-Gmp-a12",    -7.063e-06 );
   rg->Set( "BBA03-Gmp-a2",      3.104 );
   rg->Set( "BBA03-Gmp-a4",      1.428 );
   rg->Set( "BBA03-Gmp-a6",      0.1112 );
   rg->Set( "BBA03-Gmp-a8",     -0.006981 );
   rg->Set( "BBA03-Q2Max",       6. );
   rg->Set( "EL-Mv",             0.84 ); 
   bba->Configure( *rg );
*/


   double gep = bba->Gep( evt->Summary() );
   
   BOOST_CHECK_CLOSE( gep, qel_xsec::bba03el::gep_default,  tolerance_in_percent );
      
   double gmp = bba->Gmp( evt->Summary() );

   BOOST_CHECK_CLOSE( gmp, qel_xsec::bba03el::gmp_default,  tolerance_in_percent );

   double gen = bba->Gen( evt->Summary() );

   BOOST_CHECK_CLOSE( gen, qel_xsec::bba03el::gen_default,  tolerance_in_percent );

   double gmn = bba->Gmn( evt->Summary() );

   BOOST_CHECK_CLOSE( gmn, qel_xsec::bba03el::gmn_default,  tolerance_in_percent );

#ifdef PRINTOUT
   std::ostringstream os;
   UpdateBenchmark::Instance()->Write( "namespace bba03el {" );
   os << gep;
   std::string s = "static const double gep_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( s );
   os.clear();
   os.str("");
   os << gmp;
   s = "static const double gmp_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( s );
   os.clear();
   os.str("");
   os << gen;
   s = "static const double gen_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( s );
   os.clear();
   os.str("");
   os << gmn;
   s = "static const double gmn_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( s );
   UpdateBenchmark::Instance()->Write( "} // end namespace bba03el" );
#endif

   delete evt;
   delete bba;
   
   return;

}
