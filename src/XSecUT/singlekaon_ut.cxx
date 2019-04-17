
#include "CommonXSec.h"

using namespace std;
using namespace genie;

// Specific to SingleKaon (SK)
#include "Physics/Strange/XSection/AlamSimoAtharVacasSKPXSec2014.h"

void singlekaon_ut()
{

   double tolerance_in_percent = 0.001;

   // this part below is identical between lwlyn and niev !!!
   //
   InitialState istate( 6, 12, 14 );
   double Ev = 3; // in GeV
   TLorentzVector nup4(0., 0., Ev, Ev); //px, py, pz, E
   istate.SetProbeP4( nup4 );
   istate.TgtPtr()->SetHitNucPdg( 2112 );
   istate.TgtPtr()->SetHitNucP4( TLorentzVector( -0.157149, -0.071223, 0.148711, 0.966781 ) ); // this is essential !!!
   //
   ProcessInfo  procinfo( kScSingleKaon, kIntWeakCC );
   //        
   Interaction inter( istate, procinfo );
   
   // doesn't seem to be necessary
   //
   // inter.ResetBit(kISkipProcessChk);
   // inter.ResetBit(kISkipKinematicChk);
   
   inter.KinePtr()->SetKV( kKVTk, 0.386 );  // running
   inter.KinePtr()->SetKV( kKVTl, 1.428 );  // running
   inter.KinePtr()->SetKV( kKVctl, 0.930 ); // running
   inter.KinePtr()->SetKV( kKVphikq, 1.586 ); // running
   inter.KinePtr()->SetKV( kKVSelTk, 0.386 );  // selected
   inter.KinePtr()->SetKV( kKVSelTl, 1.428 );  // selected
   inter.KinePtr()->SetKV( kKVSelctl, 0.930 ); // selected
   inter.KinePtr()->SetKV( kKVSelphikq, 1.586 ); // selected
   inter.KinePtr()->Setx( 0.008, true ); // selected (2nd arg true)
   inter.KinePtr()->Sety( 0.413, true ); // selected (2nd arg true)
   inter.KinePtr()->SetQ2( 0.188 ); 
   inter.KinePtr()->SetW( 1.562 );
   inter.ExclTagPtr()->SetNProtons(1); // either num of protons or neutrons should be set explicitly

//        if      (numProtons==0 && numNeutrons==1 && kaonPDG==kPdgKP) reactionType=1;
//        else if (numProtons==1 && numNeutrons==0 && kaonPDG==kPdgK0) reactionType=2;
//        else if (numProtons==1 && numNeutrons==0 && kaonPDG==kPdgKP) reactionType=3;

   inter.ExclTagPtr()->SetStrange( kPdgK0 ); // kaon pdg, either K+ or K0s, should be set explicitly;
                                             // also, one should keep in mind that 
					     // num.neutrons=1 && K0s is NOT a valid combo
					     // instead, K0s will go only with a proton
   
   // inter.InitState().Print( std::cout );
   // inter.InitState().TgtPtr()->HitNucP4().Print();
      
   AlamSimoAtharVacasSKPXSec2014 sk;
   sk.Configure("Default");
   
   BOOST_CHECK( sk.ValidProcess( &inter ) );
   
   double xsec = sk.XSec( &inter, kPSNull ); // the KPS arg does NOT matter here as it's not used
   // double xsec = sk.XSec( &inter, kPSTkTlctl ); 
   
   // ---> that's how it's done in SKKinematicsGenerator: evrec->SetDiffXSec(xsec*(1.0-costhetal),kPSTkTlctl);
   // so let's replicate it...
   //
   xsec *= ( 1. - inter.KinePtr()->GetKV(kKVSelctl) );
   
   BOOST_REQUIRE_NE( xsec, 0. );
   BOOST_CHECK_CLOSE( xsec, 6.9463227404016836e-14, tolerance_in_percent );
   
   return;

}
