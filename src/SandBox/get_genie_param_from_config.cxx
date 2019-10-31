/*

This example show how to get the value of one or another parameter 
of a given model directly from GENIE "global" configuration.

The procedure is not very straightforward, and requires knowledge
of some "gut" of GENIE. 
In particular, it requires knowledge what model is part of what tune.
E.g. ReinSehgal model is part of G00_00a tune which used to be the default
up until GENIE R-3 release.
In R-3, the default tune is G18_02a where ReinSehgal has been replaced
by the BergerSehgal model.

Obviously, one fisrt need to load a particular tune before beign able
to access the global configuration, and a specific parameter in it.

*/

#include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"
#include "Framework/Conventions/Units.h"

#include "Framework/Algorithm/AlgFactory.h"
#include "Framework/Algorithm/AlgConfigPool.h"
#include "Framework/EventGen/XSecAlgorithmI.h"
#include "Framework/Registry/Registry.h"

#include "Physics/Coherent/XSection/ReinSehgalCOHPiPXSec.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;

int main( void )
{

   RunOpt* inst = RunOpt::Instance();
   
   inst->SetTuneName("G00_00a_00_000");

   // NOTE-1: doing just this will result in the following crash:
   //
   // 1551828507 ERROR AlgConfigPool : [s] <LoadRegistries (289)> : The XML doc doesn't exist! (filename : ModelConfiguration.xml)
   // 1551828507 ERROR AlgConfigPool : [n] <AlgConfigPool.cxx::AlgConfigPool (70)> : Could not load XML config file
   //
   // NOTE-2: OK, I think I understand why it works only through RunOpt. the story is the following:
   //         When AlgConfigPool tries to load up all the configs, it uses functions from XmlParserUtils, 
   //         such as GetXMLFilePath, etc. Subsequently, those functions call GetXMLPathList, and this one
   //         EXPLICITLY checks the path via RunOpt, also tune's status via RunOpt, and all that jazz !!!
   //
   // TuneId* tune = new TuneId( "G00_00a_00_000" );
   // --> NO NEED since TuneId ctor already calls Build(tune_name) --> tune->Build();
   
   EventRecord* synth_event = new SynthEventCOH();
   
   AlgConfigPool* conf_pool = AlgConfigPool::Instance();

   Registry* gpl  = conf_pool->GlobalParameterList();
   
   gpl->Print( cout );
   cout << endl;
   cout << "=============================" << endl;
   cout << endl;
      
/* more examples of accessing info...

   Registry* tnl  = conf_pool->TuneGeneratorList();
   const vector<string> cfgl = conf_pool->ConfigKeyList();

   tnl->Print( cout );

   RgKeyList keylist = gpl->FindKeys("COH");
   cout << "size of keylist = " << keylist.size() << endl;

*/

   // NOTE: Basically, RgAlg is just a "pair" of strings (but not an std::pair),
   // i.e. algorithm's name (e.g. Lwlyn...) and configuration (e.g. Dipole)
   //
   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/COH-CC-PION");
   
   cout << " RgAlg = " << xsec_alg << endl;
  
   AlgId id(xsec_alg);

   AlgFactory* algf = AlgFactory::Instance();

   Algorithm* the_alg = (Algorithm*)(algf->GetAlgorithm(id)); // ugly trick - cast away const
   XSecAlgorithmI* TheXSecModel = dynamic_cast<XSecAlgorithmI*>(the_alg);
   
   // get model's config
   //
   const Registry& rconf = TheXSecModel->GetConfig();
   rconf.Print(cout);

   // get config of a sub-algorithm XSec-Integrator, if any
   //
   // const Registry& rg_xsec_int = (TheXSecModel->SubAlg("XSec-Integrator"))->GetConfig();
   const Algorithm* xsec_int = TheXSecModel->SubAlg("XSec-Integrator");
   if ( xsec_int )
   {
      const Registry& rconf_xsec_int = xsec_int->GetConfig();
      rconf_xsec_int.Print(cout);  
   }
   
   string MaPath = "COH-Ma";  // alt.: COH-Ro
   double Ma = (TheXSecModel->GetConfig()).GetDouble(MaPath);
   cout << " Ma = " << Ma << endl;
   
   string RoPath = "COH-Ro";
   double Ro = (TheXSecModel->GetConfig()).GetDouble(RoPath);
   cout << " Ro = " << Ro << endl;
   
   string ReImPath = "COH-ReImAmpl";
   double ReIm = (TheXSecModel->GetConfig()).GetDouble(ReImPath);
   cout << " ReIm = " << ReIm << endl;
   
   string ModPCACPath = "COH-UseModifiedPCAC";
   bool ModPCAC = (TheXSecModel->GetConfig()).GetBool(ModPCACPath);
   cout << " ModPCAC = " << ModPCAC << endl;
   
   double xsec = TheXSecModel->XSec( synth_event->Summary(), kPSxyfE );
   cout << " XSec = " << xsec << endl;
   
   
   // This trick below will work HERE...
   // ... but that's maybe because all the paths, and all the global configs, etc.
   // are already in, and are known to RunOpt...
   // ... because if trying the same WITHOUT RunOpt in a separate code results 
   // in segfault going through LoadConfig (called from Configure) 
   //
   // Well, just adding this RunOpt thing does NOT seem to help.
   // Apparently the issue is somewhere else.
   // Could it be XSec-Integrator ??? 
   
   Registry rconf_modi = Registry( rconf );
   rconf_modi.Set( ModPCACPath, false );
   rconf_modi.Print(cout);
   
   ReinSehgalCOHPiPXSec* rs_xsec_modi = new ReinSehgalCOHPiPXSec();
   
   rs_xsec_modi->Configure( rconf_modi );
   double xsec_modi = rs_xsec_modi->XSec( synth_event->Summary(), kPSxyfE );
   cout << " XSec(modi) = " << xsec_modi << endl;

//   delete tune;
   
/*
   // FIXME !!!
   // Need to find out how to re-load the AlgConfig !!!
   // Because simply re-setting the tune in RunOpt does NOT do the trick !!!
   //
   // Well, perhaps nothing will do the trick because AlgConfigPool is a singleton, 
   // and once it's instanciated, it stays there all the same, and there's no way
   // to change anything in the guts in a consistent manner.
   // There's a number of access methods, each resturning a Registry* which is non-const !
   // Maybe there's a chance to do through that door... 

   RunOpt::Instance()->SetTuneName("G18_02a_00_000");
   
   conf_pool = AlgConfigPool::Instance();
   gpl = conf_pool->GlobalParameterList();
   
   gpl->Print( cout );
*/   

   cout << endl;
   cout << "=============================" << endl;
   cout << endl;
   cout << " Enjoy your day !" << endl;
   cout << endl;
        
   return 0;

}
