

#include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"

#include "Framework/Interaction/Interaction.h"
#include "Framework/ParticleData/PDGCodes.h"
#include "Framework/ParticleData/PDGLibrary.h"
#include "Framework/ParticleData/PDGUtils.h"

#include "SynthEvent.h"

#include "Physics/Coherent/XSection/ReinSehgalCOHPiPXSec.h"
#include "Physics/QuasiElastic/XSection/LwlynSmithQELCCPXSec.h"



using namespace std;
using namespace genie;

int main( /* int argc, char* argv[] */ )
{

   // First of all, quiet the Messenger as much as possible !
   //
   
   Messenger::Instance()->SetPrioritiesFromXmlFile("Messenger_whisper.xml");
   
   // Pull up RunOpt
   //
   
   RunOpt* inst = RunOpt::Instance();   

   // ReinSehgal XSec model (coherent process)
   //
   // NOTE-1: This process is included only in tune G00_00a
   //         in (now default) tune G18_02a it's replaced with Berger-Sehgal model
   //
   
   inst->SetTuneName("G00_00a_00_000");
   
   ReinSehgalCOHPiPXSec* rs_xsec = new ReinSehgalCOHPiPXSec();
   
   const AlgId& rs_id = rs_xsec->Id();
   cout << " Model name = " << rs_id.Name() << endl;

   rs_xsec->Configure("Default" );
   
   EventRecord* synth_event = new SynthEventCOH();
   
   if ( !rs_xsec->ValidProcess( synth_event->Summary() ) )
   {
       cout << " Invalid interaction for " << (rs_xsec->Id()).Name() << endl;
   }
   
   double xsec = rs_xsec->XSec( synth_event->Summary(), kPSxyfE );
   cout << (rs_xsec->Id()).Name() << ", with PhaseSpace=kPSxyfE --> XSec = " << xsec << endl; 

   // Llewvellyn-Smith XSec model
   //
  
   inst->SetTuneName("G18_02a_00_000");

   LwlynSmithQELCCPXSec* lw_xsec = new LwlynSmithQELCCPXSec();

   cout << " Model name = " << (lw_xsec->Id()).Name() << endl;
   
   lw_xsec->Configure("Dipole");
   
   InitialState istate( 6, 12, 14 );   
   // make sure to set hit tgt nucleon to neutron with the nu_mu probe
   // ... or to proton with nu_mu_bar probe
   istate.TgtPtr()->SetHitNucPdg( 2112 );
   double Ev = 3; // in GeV
   TLorentzVector nup4(0., 0., Ev, Ev); //px, py, pz, E
   istate.SetProbeP4( nup4 );
   ProcessInfo procinfo( kScQuasiElastic, kIntWeakCC );
   Interaction lw_inter( istate, procinfo );
   lw_inter.KinePtr()->SetQ2( 2.0 ); // just to set something sensible...
   
   bool valid = lw_xsec->ValidProcess( &lw_inter );
   if ( !valid )
   {
      cout << " Invalid interaction for " << (lw_xsec->Id()).Name() << endl;
      return 1;
   }

   xsec = 0.;
   KinePhaseSpace_t kpst = kPSQ2fE;    
   xsec = lw_xsec->XSec( &lw_inter, kpst );
   cout << (lw_xsec->Id()).Name() << ", with PhaseSpace=kPSQ2fE --> XSec = " << xsec << endl; 

   cout << " Finishing up... " << endl;
   
   return 0;

}
