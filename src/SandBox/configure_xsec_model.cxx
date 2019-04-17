#include "Framework/Utils/RunOpt.h"
#include "Framework/Conventions/Units.h"

#include "Framework/Registry/Registry.h"

#include "Physics/Coherent/XSection/ReinSehgalCOHPiPXSec.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;

int main( void )
{

   // Select the tune
   // NOTE: We selecting G00_00a_00_000 because we want to handle
   //       ReinSehgalCOHPiPXSec model, and it's not clear if it's
   //       included in more modern tunes (perhaps it's replaced
   //       by BergerSehgal)
   //
   RunOpt::Instance()->SetTuneName("G00_00a_00_000");

   // Instanciate ReinSehgalCOHPiPXSec object
   //
   ReinSehgalCOHPiPXSec* rs_xsec = new ReinSehgalCOHPiPXSec();
   //
   // Configure it with "Default"
   //
   rs_xsec->Configure( "Default" );
   
   // Instaciate COH event (this one is generic enough)
   //
   EventRecord* synth_event = new SynthEventCOH();
   
   // Calculate the XSec for the interaction 
   //
   double xsec = rs_xsec->XSec( synth_event->Summary(), kPSxyfE );
   cout << " Unmodified RS XSec = " << xsec << endl;   
   
   // Now let's see what we can extract from the configuration 
   //
   // First, let's print the whole configuration
   //
   (rs_xsec->GetConfig()).Print( cout );
   
   // Now let's extract various config parameters one by one
   //
   string MaPath = "COH-Ma";  
   double Ma = (rs_xsec->GetConfig()).GetDouble(MaPath);
   cout << " Ma = " << Ma << endl;
   
   string RoPath = "COH-Ro";
   double Ro = (rs_xsec->GetConfig()).GetDouble(RoPath);
   cout << " Ro = " << Ro << endl;
   
   string ReImPath = "COH-ReImAmpl";
   double ReIm = (rs_xsec->GetConfig()).GetDouble(ReImPath);
   cout << " ReIm = " << ReIm << endl;
   
   string ModPCACPath = "COH-UseModifiedPCAC";
   bool ModPCAC = (rs_xsec->GetConfig()).GetBool(ModPCACPath);
   cout << " ModPCAC = " << ModPCAC << endl;
   
   // NOTE-1: What sits on the IntegratorPath is NOT a string;
   //         it's the name of an ** Algorithm ** !!!
   //
   // NOTE-2: Mechanically speaking, it's an RgAlg object 
   //         which is defined by a name (string) and a config (string)
   string IntegratorPath = "XSec-Integrator";
   RgAlg XSecIntegrator = (rs_xsec->GetConfig()).GetAlg(IntegratorPath);
   cout << " XSecIntegrator = " << XSecIntegrator.name << "/" << XSecIntegrator.config << endl;
   
   // Now let's create a custom registry, with some changes of the parameters
   // Let's make it a copy of the "default" one because it'll simplify our life it bit.
   // Keep in mind that the GetConfig() method returns a const Registry&, so you're
   // unlikely to be able to modify it (unless you do an ugly trick of casting away cosnt).
   //
   Registry config_modi( rs_xsec->GetConfig() );
   //
   // Now our new objet config_modi is NOT cosnt, and we can make modifications to it. 
   //
   config_modi.Set( ModPCACPath, false );
   config_modi.Set( ReImPath, 0.35 );
   //
   // Print out the modified config
   //
   config_modi.Print( cout );
      
   // Reconfigure the RS XSec object with the new config
   //
   rs_xsec->Configure( config_modi );
   
   // Check what XSec it generates now
   //
   double xsec_modi = rs_xsec->XSec( synth_event->Summary(), kPSxyfE );
   cout << " Modified RS XSec(modi) = " << xsec_modi << endl;   
   
   cout << " ENJOY THE REST OF YOUR DAY !!!" << endl;
   
/* 
   NOW, another example that will work BUT !!! ONLY !!! if you load up the tune into RunOpt.
   
   If not, it'll chock on trying to configure the XSec Integrator algorithm genie::COHXSec/Default,
   and will spit the following diagnostics:
   // 1553115532 ERROR AlgConfigPool : [s] <LoadRegistries (289)> : The XML doc doesn't exist! (filename : ModelConfiguration.xml)
   // 1553115532 ERROR AlgConfigPool : [n] <AlgConfigPool.cxx::AlgConfigPool (70)> : Could not load XML config file
   // 1553115532 WARN Algorithm : [n] <Algorithm.cxx::FindConfig (165)> : No Configuration available for genie::COHXSec/Default at the ConfigPool
   // 1553115532 WARN Algorithm : [n] <Algorithm.cxx::FindConfig (224)> : No Tunable parameter set available at the ConfigPool
   // 1553115532 FATAL Algorithm : [n] </genie/app/yarba_j/GENIE-work/try-github/master_mar19_2019_root6.12.06a_dbg/Generator/src/Framework/Algorithm/Algorithm.icc::GetParam (102)> : 
   // *** Key: COH-t-max does not exist in pools from algorithm : genie::COHXSec/Default   
   
   The issue here is that most of the configuration mechanisms try to local XML configurations via XmlParserUtils,
   and those in turn rely on RunOpt.

   Registry conf_custom = Registry( "RSXSecConfig", false ); // 2nd arg set to false means that it's NOT read-only
   conf_custom.InhibitItemLocks();
   
   string MaPath = "COH-Ma";  // alt.: COH-Ro
   conf_custom.Set( MaPath, 1. );
   
   string RoPath = "COH-Ro";
   conf_custom.Set( RoPath, 1. );
   
   string ReImPath = "COH-ReImAmpl";
   conf_custom.Set( ReImPath, 0.3 );
   
   string ModPCACPath = "COH-UseModifiedPCAC";
   conf_custom.Set( ModPCACPath, true );
   
   string IntegratorPath = "XSec-Integrator";
   // ---> INCORRECT; it's not a string but an RgAlg !!! ---> rconf.Set( IntegratorPath, "genie::COHXSec/Default"  );
   RgAlg int_xsec( "genie::COHXSec", "Default" );
   conf_custom.Set( IntegratorPath, int_xsec );

   ReinSehgalCOHPiPXSec* rs_xsec_custom = new ReinSehgalCOHPiPXSec();
   rs_xsec_custom->Configure( conf_custom );
      
   double xsec_custom = rs_xsec_custom->XSec( synth_event->Summary(), kPSxyfE );
   cout << " RS XSec(custom) = " << xsec_custom << endl;

*/   
   
   return 0;
   
}
