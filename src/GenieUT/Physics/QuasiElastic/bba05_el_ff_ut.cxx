#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

#include "Physics/QuasiElastic/XSection/BBA05ELFormFactorsModel.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void bba05_el_ff_ut()
{

   EventRecord* evt = new SynthEvent();

   BBA05ELFormFactorsModel* bba = new BBA05ELFormFactorsModel();

   BOOST_CHECK( bba != 0 );

   // configure from tune (global config pool)
   //
   bba->Configure("Default");
   
// (bba->GetConfig()).Print(cout), as of Oct30, 2019, will produce the following:  
//
// Registry name: [genie::BBA05ELFormFactorsModel/Default_summary] - Write Status: [unlocked] - Inhibited Item Locking: [on] - # entries:  31
// |--------------------------------> AnomMagnMoment-N [double] [unlocked] [l] : -1.91304
// |--------------------------------> AnomMagnMoment-P [double] [unlocked] [l] : 2.793
// |------------------------------------> BBA05-Gen-a0 [double] [unlocked] [l] : 0
// |------------------------------------> BBA05-Gen-a1 [double] [unlocked] [l] : 1.25
// |------------------------------------> BBA05-Gen-a2 [double] [unlocked] [l] : 1.3
// |------------------------------------> BBA05-Gen-b1 [double] [unlocked] [l] : -9.86
// |------------------------------------> BBA05-Gen-b2 [double] [unlocked] [l] : 305
// |------------------------------------> BBA05-Gen-b3 [double] [unlocked] [l] : -758
// |------------------------------------> BBA05-Gen-b4 [double] [unlocked] [l] : 802
// |------------------------------------> BBA05-Gep-a0 [double] [unlocked] [l] : 1
// |------------------------------------> BBA05-Gep-a1 [double] [unlocked] [l] : -0.0578
// |------------------------------------> BBA05-Gep-a2 [double] [unlocked] [l] : 0
// |------------------------------------> BBA05-Gep-b1 [double] [unlocked] [l] : 11.1
// |------------------------------------> BBA05-Gep-b2 [double] [unlocked] [l] : 13.6
// |------------------------------------> BBA05-Gep-b3 [double] [unlocked] [l] : 33
// |------------------------------------> BBA05-Gep-b4 [double] [unlocked] [l] : 0
// |------------------------------------> BBA05-Gmn-a0 [double] [unlocked] [l] : 1
// |------------------------------------> BBA05-Gmn-a1 [double] [unlocked] [l] : 1.81
// |------------------------------------> BBA05-Gmn-a2 [double] [unlocked] [l] : 0
// |------------------------------------> BBA05-Gmn-b1 [double] [unlocked] [l] : 14.1
// |------------------------------------> BBA05-Gmn-b2 [double] [unlocked] [l] : 20.7
// |------------------------------------> BBA05-Gmn-b3 [double] [unlocked] [l] : 68.7
// |------------------------------------> BBA05-Gmn-b4 [double] [unlocked] [l] : 0
// |------------------------------------> BBA05-Gmp-a0 [double] [unlocked] [l] : 1
// |------------------------------------> BBA05-Gmp-a1 [double] [unlocked] [l] : 0.15
// |------------------------------------> BBA05-Gmp-a2 [double] [unlocked] [l] : 0
// |------------------------------------> BBA05-Gmp-b1 [double] [unlocked] [l] : 11.1
// |------------------------------------> BBA05-Gmp-b2 [double] [unlocked] [l] : 19.6
// |------------------------------------> BBA05-Gmp-b3 [double] [unlocked] [l] : 7.54
// |------------------------------------> BBA05-Gmp-b4 [double] [unlocked] [l] : 0
// |-------------------------------------> CommonParam [string] [unlocked] [l] : MagnMoments

/*
   // explicit (local) configuration would be partially exemplied as follows:
   //
   Registry* rg = new Registry( "bba03_el_ut" );
   rg->UnLock();
   rg->Set( "CommonParam",      "MagnMoments" );
   rg->Set( "AnomMagnMoment-N", -1.91304 ); 
   rg->Set( "AnomMagnMoment-P",  2.793 ); 
   // etc...
*/
   double gep = bba->Gep( evt->Summary() );
   
   BOOST_CHECK_CLOSE( gep, qel_xsec::bba05el::gep_default,  tolerance_in_percent );
      
   double gmp = bba->Gmp( evt->Summary() );

   BOOST_CHECK_CLOSE( gmp, qel_xsec::bba05el::gmp_default,  tolerance_in_percent );

   double gen = bba->Gen( evt->Summary() );

   BOOST_CHECK_CLOSE( gen, qel_xsec::bba05el::gen_default,  tolerance_in_percent );

   double gmn = bba->Gmn( evt->Summary() );

   BOOST_CHECK_CLOSE( gmn, qel_xsec::bba05el::gmn_default,  tolerance_in_percent );

#ifdef PRINTOUT
   std::ostringstream os;
   UpdateBenchmark::Instance()->Write( "namespace bba05el {" );
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
   UpdateBenchmark::Instance()->Write( "} // end namespace bba05el" );
#endif

   delete evt;
   delete bba;
   
   return;

}
