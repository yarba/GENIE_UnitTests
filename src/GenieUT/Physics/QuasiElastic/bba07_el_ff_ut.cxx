#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

#include "Physics/QuasiElastic/XSection/BBA07ELFormFactorsModel.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void bba07_el_ff_ut()
{

   EventRecord* evt = new SynthEvent();

   BBA07ELFormFactorsModel* bba = new BBA07ELFormFactorsModel();

   BOOST_CHECK( bba != 0 );

   // configure from tune (global config pool)
   //
   bba->Configure("Default");
   
   double gep = bba->Gep( evt->Summary() );
   
   BOOST_CHECK_CLOSE( gep, qel_xsec::bba07el::gep_default,  tolerance_in_percent );
      
   double gmp = bba->Gmp( evt->Summary() );

   BOOST_CHECK_CLOSE( gmp, qel_xsec::bba07el::gmp_default,  tolerance_in_percent );

   double gen = bba->Gen( evt->Summary() );

   BOOST_CHECK_CLOSE( gen, qel_xsec::bba07el::gen_default,  tolerance_in_percent );

   double gmn = bba->Gmn( evt->Summary() );

   BOOST_CHECK_CLOSE( gmn, qel_xsec::bba07el::gmn_default,  tolerance_in_percent );

#ifdef PRINTOUT
   std::ostringstream os;
   UpdateBenchmark::Instance()->Write( "namespace bba07el {" );
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
   UpdateBenchmark::Instance()->Write( "} // end namespace bba07el" );
#endif

   delete evt;
   delete bba;
   
   return;

}
