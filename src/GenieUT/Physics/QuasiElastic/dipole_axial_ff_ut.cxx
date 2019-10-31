#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

#include "Physics/QuasiElastic/XSection/DipoleAxialFormFactorModel.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void dipole_axial_ff_ut()
{

   EventRecord* evt = new SynthEvent();
   
   DipoleAxialFormFactorModel* dip = new DipoleAxialFormFactorModel();
   
   BOOST_CHECK( dip != 0 );
   
   // --> dip->Configure("Dipole"); // this way it'll pickup from the config of the tune (global) 

   Registry* rg_dip_ax = new Registry( "dipole_axial_ut" );
   rg_dip_ax->UnLock();
   rg_dip_ax->Set( "CommonParam", "QuasiElastic" );
   rg_dip_ax->Set( "QEL-FA0", -1.267 );
   rg_dip_ax->Set( "QEL-Ma",   0.99  );
   rg_dip_ax->Set( "QEL-Mv",   0.84  ); 
// -->   rg_dip_ax->Print( cout );

   dip->Configure( *rg_dip_ax );
   
   double fa = dip->FA( evt->Summary() );
   
   // Q: Should we check that it's non-zero ?
   
//   BOOST_CHECK_CLOSE( fa, -1.03748, tolerance_in_percent ); 
   BOOST_CHECK_CLOSE( fa, qel_xsec::dipoleaxialff::fa_default, tolerance_in_percent ); 
         
#ifdef PRINTOUT
   std::ostringstream os;
   os << fa;
   std::string s = "static const double fa_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( "namespace dipoleaxialff {" );
   UpdateBenchmark::Instance()->Write( s );
   UpdateBenchmark::Instance()->Write( "} // end namespace dipoleaxialff" );
#endif
   
   // We can also extract configuration (const Registry & GetConfig(void))
   // make modifications in it, and recalculate FA one more time
   // Data members to possibly change: fMa, fMv, fFA0 (<FA(q2=0)  
   
   delete evt;
   delete dip;

   return;

}
