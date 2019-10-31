#include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"
#include "Framework/Conventions/Units.h"

#include "Framework/Algorithm/AlgFactory.h"
#include "Framework/Algorithm/AlgConfigPool.h"
#include "Framework/EventGen/XSecAlgorithmI.h"
#include "Framework/Registry/Registry.h"

// This one is needed to be able if desired directory exists
#include <dirent.h>

using namespace std;
using namespace genie;

//==================================================================================================================
//
// If one wants to use custom configuration files (XML) from some area **different** from $GENIE/config, 
// one should setup env.variable GXMLPATH
// It's not entirely clear if/where it's documented, but there're some comments on this matter in the source code:
// $GENIE/src/FrameworkUtils/XmlParserUtils.h lines 70-73
// $GENIE/src/FrameworkUtils/XmlParserUtils.cxx lines 58-73
// There also seem to be one more env.var. GALGCONF which seems to be serving the same purpose
//
// Alternative way to set fXMLPath data member of RunOpt class is via 
//    RunOpt::ReadFromCommandLine(int argc, char** argv) method
// There's NO method of RunOpt to set fXMLPath directly !!!
// Again, it works either via env.var $GXMLPATH or via RunOpt::ReadFromCommandLine(...) method !!!
//
//==================================================================================================================

int main( /* int argc, char** argv */ )
{

   // Get config from non-default path via setting env.var GXMLPATH 
   // The config in this case will be the "frozen" one from 
   //    UnitTests/config/Frozen_Config
   // 
   
   // First of all, find path to UnitTests from the name of the application 
   //   
   // NOTE: do NOT use argv[0] because it's not always **full path* to the app
   //
         
   int pid = getpid();   
   char exepath[ PATH_MAX + 1 ] = {0};
   string arg = "/proc/" + std::to_string(pid) + "/exe";   
   readlink( arg.c_str(), exepath, sizeof(exepath) );
   
   string gxmlpath = exepath;
   
   string task_name = "UnitTests";
   size_t pos = gxmlpath.find( task_name );
   if ( pos != string::npos )
   {
      
      gxmlpath.erase( pos+task_name.length() ); // erase all the way to the end (npos)
      gxmlpath += "/config/Frozen_Config" ;
      
      DIR* exists = opendir( gxmlpath.c_str() );
      if ( exists != NULL )
      {      
         cout << " Directory " << gxmlpath << " exists; now set GXMLPATH env.var. " << endl;
         (void) closedir( exists );  
         int status = setenv( "GXMLPATH", gxmlpath.c_str(), 1 ); // 3rd input arg overwrite is a flag that tells
                                                                 // to overwrite an existing env.var. if it's >0  
         if ( status != 0 )
         {
            cout << " Can NOT set env.var. GXMLPATH via setenv(...)" << endl;
            return status;
         }
      }
      else
      {
         cout << " Can NOT find path to UnitTests/config/Frozen_Config; DEFAULT XML path to $GENIE/config " << endl;
      }
   }
         
// Cross-check printout
//   char* test_gxml = getenv( "GXMLPATH" );
//   cout << " $GXMLPATH = " << test_gxml << endl;

   // now check if possible to get a parameter from 
   // the **custom** config/registry at $GXMLPATH
   //
   
   // First of all, setup desired tune 
   // Otherwise default tune (D=G18_02a_00_000) will be selected
   //
   
   RunOpt* inst = RunOpt::Instance();
   
   inst->SetTuneName("G00_00a_00_000");
   
   // Now do all the manipulations with (model) configs
   //

   AlgConfigPool* conf_pool = AlgConfigPool::Instance();

   Registry* gpl  = conf_pool->GlobalParameterList();

   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/COH-CC-PION");
   
   AlgId id(xsec_alg);

   AlgFactory* algf = AlgFactory::Instance();

   Algorithm* the_alg = (Algorithm*)(algf->GetAlgorithm(id)); // ugly trick - cast away const
   XSecAlgorithmI* TheXSecModel = dynamic_cast<XSecAlgorithmI*>(the_alg);
   
// --> NOT needed -->   const Registry& rconf = TheXSecModel->GetConfig();
// -->   rconf.Print(cout);
   
   string MaPath = "COH-Ma";  // alt.: COH-Ro
   double Ma = (TheXSecModel->GetConfig()).GetDouble(MaPath);
   cout << " Ma = " << Ma << endl;

   return 0;

}
