#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

#include "Physics/QuasiElastic/XSection/DipoleELFormFactorsModel.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void dipole_el_ff_ut()
{

   EventRecord* evt = new SynthEvent();
   
   DipoleELFormFactorsModel* dip = new DipoleELFormFactorsModel();
   
   BOOST_CHECK( dip != 0 );
   
   Registry* rg_dip_el = new Registry( "dipole_el_ut" );
   rg_dip_el->UnLock();
   rg_dip_el->Set( "EL-Mv", 0.840 );
   rg_dip_el->Set( "AnomMagnMoment-P", 2.793 );
   rg_dip_el->Set( "AnomMagnMoment-N", -1.913042 );
   
   dip->Configure( *rg_dip_el );
   
   double gep = dip->Gep( evt->Summary() ); 
   
//   BOOST_CHECK_CLOSE( gep, 0.76146, tolerance_in_percent ); 
   BOOST_CHECK_CLOSE( gep, qel_xsec::dipoleelff::gep_default, tolerance_in_percent ); 

   double gmp = dip->Gmp( evt->Summary() );

//   BOOST_CHECK_CLOSE( gmp, 2.12677, tolerance_in_percent ); 
   BOOST_CHECK_CLOSE( gmp, qel_xsec::dipoleelff::gmp_default, tolerance_in_percent ); 

   double gen = dip->Gen( evt->Summary() ); // 0. (zero) by definition !!!

   BOOST_CHECK( gen == 0. ); 

   double gmn = dip->Gmn( evt->Summary() ); 

//   BOOST_CHECK_CLOSE( gmn, -1.45671, tolerance_in_percent ); 
   BOOST_CHECK_CLOSE( gmn, qel_xsec::dipoleelff::gmn_default, tolerance_in_percent ); 
   
#ifdef PRINTOUT
   std::ostringstream os;
   UpdateBenchmark::Instance()->Write( "namespace dipoleelff {" );
   os << gep;
   std::string s = "static const double gep_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( s );
   os.clear();
   os.str("");
   os << gmp;
   s = "static const double gmp_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write(s);
   os.clear();
   os.str("");
   os << gmn;
   s = "static const double gmn_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write(s);   
   UpdateBenchmark::Instance()->Write( "} // end namespace dipoleelff" );
#endif

   // Data member to (possibly) modify:
   // fMv,fMuP, fMuN; 

   delete evt;
   delete dip;
   delete rg_dip_el;

   return;

}
