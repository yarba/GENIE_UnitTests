
#include "CommonXSec.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

// nieves-specific
#include "Physics/QuasiElastic/XSection/NievesQELCCPXSec.h"

void nieves_ut()
{
      
   double tolerance_in_percent = 0.001;

   // this part below is identical between lwlyn and niev !!!
   //
   InitialState istate( 6, 12, 14 ); // tgt=Carbon, projectile=nu_mu
   istate.TgtPtr()->SetHitNucPdg( 2112 ); // "hit nucleon" is neutron
   
   // kinematics
   //
   double Ev = 3; // in GeV
   TLorentzVector nup4(0., 0., Ev, Ev); //px, py, pz, E
   istate.SetProbeP4( nup4 );
   //
   ProcessInfo  procinfo( kScQuasiElastic, kIntWeakCC );
   //        
   Interaction inter( istate, procinfo );
   inter.KinePtr()->SetQ2( 2.0 ); // just to set something sensible...
   
   NievesQELCCPXSec niev;
   // niev.Configure("Default");
   // niev.Configure("Dipole");
   niev.Configure( "ZExp" ); // as of trunk/v3, most recent valid configuration

   BOOST_CHECK( niev.ValidProcess( &inter ) );

   KinePhaseSpace_t kpst = kPSQ2fE; 

   double xsec = niev.XSec( &inter, kpst );
   
   BOOST_REQUIRE_NE( xsec, 0. );
   
   // BOOST_CHECK_CLOSE( xsec, 1.335315e-11, tolerance_in_percent ); // going towards GENIE v3-series... but this was for "Dipole"
   BOOST_CHECK_CLOSE( xsec, 1.195979e-11, tolerance_in_percent ); // this is for "ZExp", towards v3-series
   
   return;
}
