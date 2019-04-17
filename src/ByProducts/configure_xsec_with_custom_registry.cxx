// #include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"
#include "Framework/Conventions/Units.h"

// #include "Framework/Algorithm/AlgFactory.h"
// #include "Framework/Algorithm/AlgConfigPool.h"
// #include "Framework/EventGen/XSecAlgorithmI.h"
#include "Framework/Registry/Registry.h"

#include "Physics/Coherent/XSection/ReinSehgalCOHPiPXSec.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;

int main( void )
{

   RunOpt::Instance()->SetTuneName("G00_00a_00_000");

   EventRecord* synth_event = new SynthEventCOH();

   Registry rconf = Registry( "RSXSecConfig", false ); // 2nd arg set to false means that it's NOT read-only
   rconf.InhibitItemLocks();
   
   string MaPath = "COH-Ma";  // alt.: COH-Ro
   rconf.Set( MaPath, 1. );
   
   string RoPath = "COH-Ro";
   rconf.Set( RoPath, 1. );
   
   string ReImPath = "COH-ReImAmpl";
   rconf.Set( ReImPath, 0.3 );
   
   string ModPCACPath = "COH-UseModifiedPCAC";
   rconf.Set( ModPCACPath, true );
   
   string IntegratorPath = "XSec-Integrator";
   // ---> INCORRECT; it's not a string but an RgAlg !!! ---> rconf.Set( IntegratorPath, "genie::COHXSec/Default"  );
   RgAlg int_xsec( "genie::COHXSec", "Default" );
   rconf.Set( IntegratorPath, int_xsec );
   
   rconf.Print( cout );
   
   ReinSehgalCOHPiPXSec* rs_xsec = new ReinSehgalCOHPiPXSec();
   
   //
   // It crashes on line 207 (or maybe 208) of ReinSehgalCOHPiPXSec.cxx,
   // in the LoadConfig function, trying to do the following:
   //
   //       fXSecIntegrator =
   //            dynamic_cast<const XSecIntegratorI *> (this->SubAlg("XSec-Integrator"));
   // 
   // NOTE-1: fOwnsSubstruc=false in this case and also in get_genie_param_from_config.cxx
   //       so apparently it's just some kind of sub-config...
   //
   // NOTE-2: Well, perhaps it crashes because "genie::COHXSec/Default" is NOT a string;
   //         it's the name of an Algorithm !!!
   //         To be more precise, it's an RgAlg object that's defined by a name (string, public)
   //         and a config (string, public).
   //         So see a bit earlier in the code how it should be configured.
   // 
   // NOTE-2: BUT !!! Even if you're mechanically seting up the registry the right way,
   //         the configuration will still throw with the following diagnostics:
   // 1553115532 ERROR AlgConfigPool : [s] <LoadRegistries (289)> : The XML doc doesn't exist! (filename : ModelConfiguration.xml)
   // 1553115532 ERROR AlgConfigPool : [n] <AlgConfigPool.cxx::AlgConfigPool (70)> : Could not load XML config file
   // 1553115532 WARN Algorithm : [n] <Algorithm.cxx::FindConfig (165)> : No Configuration available for genie::COHXSec/Default at the ConfigPool
   // 1553115532 WARN Algorithm : [n] <Algorithm.cxx::FindConfig (224)> : No Tunable parameter set available at the ConfigPool
   // 1553115532 FATAL Algorithm : [n] </genie/app/yarba_j/GENIE-work/try-github/master_mar19_2019_root6.12.06a_dbg/Generator/src/Framework/Algorithm/Algorithm.icc::GetParam (102)> : 
   // *** Key: COH-t-max does not exist in pools from algorithm : genie::COHXSec/Default   
   //
   // ... UNLESS YOU LOAD UP TO RunOpt SOME TUNE THAT CONTAISN THE XSEC MODEL YOU'RE INTERESTED ABOUT !!!
   // 
   rs_xsec->Configure( rconf );
      
   double xsec = rs_xsec->XSec( synth_event->Summary(), kPSxyfE );
   cout << " XSec(modi) = " << xsec << endl;
   
   
   return 0;

}
