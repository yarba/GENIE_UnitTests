

#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

#include "Physics/QuasiElastic/XSection/ZExpAxialFormFactorModel.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void zexp_axial_ff_ut()
{
      
   EventRecord* evt = new SynthEvent();
   
   ZExpAxialFormFactorModel* zexp = new ZExpAxialFormFactorModel();
   
   BOOST_CHECK( zexp != 0 );
      
   // configure with tune (global pool from XML config)
   //
   zexp->Configure("ZExp");

/*
   // explicit (local) config would look as follows:
   //
   Registry* rg = new Registry( "zexp_axial_ut" );
   rg->UnLock();
   rg->Set( "CommonParam", "QuasiElastic" );
   rg->Set( "QEL-FA0", -1.267 );
   rg->Set( "QEL-Kmax", 4 );
   rg->Set( "QEL-Ma",   0.99  );
   rg->Set( "QEL-Mv",   0.84  );
   rg->Set( "QEL-Q4limit", true );
   rg->Set( "QEL-T0",   -0.28 );
   rg->Set( "QEL-Tcut",  0.1764 );
   rg->Set( "QEL-Z_A1",  2.3 ); 
   rg->Set( "QEL-Z_A2", -0.6 ); 
   rg->Set( "QEL-Z_A3", -3.8 ); 
   rg->Set( "QEL-Z_A4",  2.3 );    
   zexp->Configure( *rg );
*/
   
   double fa = zexp->FA( evt->Summary() );
   
   // Q: Should we check that it's non-zero ?
   
   BOOST_CHECK_CLOSE( fa, qel_xsec::zexpaxialff::fa_default, tolerance_in_percent ); 
         
#ifdef PRINTOUT
   std::ostringstream os;
   os << fa;
   std::string s = "static const double fa_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( "namespace zexpaxialff {" );
   UpdateBenchmark::Instance()->Write( s );
   UpdateBenchmark::Instance()->Write( "} // end namespace zexpaxialff" );
#endif
   
   // We can also modify some of the parameters 
   // and recalculate/re-check FA
   
   delete evt;
   delete zexp;
   
   return;

}
