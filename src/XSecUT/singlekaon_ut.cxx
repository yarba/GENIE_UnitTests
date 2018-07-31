
#include "CommonXSec.h"

using namespace std;
using namespace genie;
// ---> LATER ---> using namespace boost::unit_test;

// Specific to SingleKaon (SK)
#include "Physics/Strange/XSection/AlamSimoAtharVacasSKPXSec2014.h"

void singlekaon_ut()
{

   // ---> LATER ---> double tolerance_in_percent = 0.001;

   // this part below is identical between lwlyn and niev !!!
   //
   InitialState istate( 6, 12, 14 );
   istate.TgtPtr()->SetHitNucPdg( 2112 );
   double Ev = 3; // in GeV
   TLorentzVector nup4(0., 0., Ev, Ev); //px, py, pz, E
   istate.SetProbeP4( nup4 );
   //
   ProcessInfo  procinfo( kScSingleKaon, kIntWeakCC );
   //        
   Interaction inter( istate, procinfo );
   inter.KinePtr()->SetQ2( 2.0 ); // just to set something sensible...
   inter.ExclTagPtr()->SetNProtons(1); // either num of protons or neutrons should be set explicitly
   inter.ExclTagPtr()->SetStrange( kPdgKP ); // kaon pdg, either K+ or K0s, should be set explicitly;
                                             // also, one should keep in mind that 
					     // num.neutrons=1 && K0s is NOT a valid combo
					     // instead, K0s will go only with a proton
   
   AlamSimoAtharVacasSKPXSec2014 sk;
   sk.Configure("Default");
   
   // BOOST_CHECK( sk.ValidProcess( &inter ) );
   
   double xsec = sk.XSec( &inter, kPSNull ); // the KPS arg does NOT matter here as it's not used
   
   cout << "SK XSec = " << xsec << endl;

   // BOOST_REQUIRE_NE( xsec, 0. );
   // BOOST_CHECK_CLOSE( xsec, 1.195979e-11, tolerance_in_percent ); // this is for "ZExp", towards v3-series
   
   return;

}
