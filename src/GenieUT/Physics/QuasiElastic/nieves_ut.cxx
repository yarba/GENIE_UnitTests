
#include "CommonXSec.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif

using namespace std;
using namespace genie;
using namespace boost::unit_test;

#include "Physics/QuasiElastic/XSection/QELUtils.h"
// nieves-specific
#include "Physics/QuasiElastic/XSection/NievesQELCCPXSec.h"

void nieves_ut()
{

   EventRecord* evt = new SynthEvent();
      
   NievesQELCCPXSec niev;
   niev.Configure( "ZExp" ); // as of trunk/v3, most recent valid configuration

   RgKey nuclkey = "IntegralNuclearModel";
   const NuclearModelI* nucl_model = dynamic_cast< const NuclearModelI* >(
     niev.SubAlg(nuclkey) );
   BOOST_CHECK( nucl_model );

   BOOST_CHECK( niev.ValidProcess( evt->Summary() ) );

   // CM frame scattering angles of the outgoing lepton, measured with respect
   // to the boost direction for going from the CM frame to the lab frame
   double cos_theta_0 = 0.5;
   double phi_0 = 0.;

   double dummy_binding_energy = 0.;
   double dummy_min_angle_EM = 0.;

   QELEvGen_BindingMode_t hitNucleonBindingMode = kUseNuclearModel;

   double xsec = utils::ComputeFullQELPXSec(evt->Summary(), nucl_model, &niev,
     cos_theta_0, phi_0, dummy_binding_energy, hitNucleonBindingMode,
     dummy_min_angle_EM, true);

   BOOST_REQUIRE_NE( xsec, 0. );

   BOOST_CHECK_CLOSE( xsec, qel_xsec::nieves::xsec_default, tolerance_in_percent );

#ifdef PRINTOUT
   std::ostringstream os;
   os << xsec;
   std::string s = "static const double xsec_default = " + os.str() + ";" ;
   UpdateBenchmark::Instance()->Write( "namespace nieves {" );
   UpdateBenchmark::Instance()->Write( s );
   UpdateBenchmark::Instance()->Write( "} // end namespace nieves" );
#endif

   delete evt;
   
   return;
}
