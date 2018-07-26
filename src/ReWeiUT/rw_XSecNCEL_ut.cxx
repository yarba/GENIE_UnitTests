#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_suite.hpp>

#include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"

#include "Framework/EventGen/EventRecord.h"

#include "Framework/GHEP/GHepParticle.h"
#include "Framework/Conventions/Units.h"

#include "Framework/Algorithm/AlgFactory.h"
#include "Framework/Algorithm/AlgConfigPool.h"
#include "Framework/EventGen/XSecAlgorithmI.h"
#include "Framework/Registry/Registry.h"

#include "Tools/ReWeight/GSystSet.h"
#include "Tools/ReWeight/GSyst.h"
#include "Tools/ReWeight/GReWeight.h"
#include "Tools/ReWeight/GSystUncertainty.h"

// Modules to calc weights/uncertainties
// by varying specific variables
//
// This one right below is for MaNCEL & EtaNCEL (all in one)
//
#include "Tools/ReWeight/GReWeightNuXSecNCEL.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void rw_XSecNCEL_ut()
{

   double tolerance_in_percent = 0.001;

   EventRecord* synth_event = new SynthEvent();

   // now mess up with algoritm,s configs, etc.
   //
   
   AlgConfigPool* conf_pool = AlgConfigPool::Instance();
   Registry* gpl = conf_pool->GlobalParameterList();   
   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/QEL-NC");
  
   AlgId id(xsec_alg);

   AlgFactory* algf = AlgFactory::Instance();
   Algorithm* alg_def = (Algorithm*)(algf->GetAlgorithm(id)); // ugly trick - cast away const
   XSecAlgorithmI* XSecModelDef = dynamic_cast<XSecAlgorithmI*>(alg_def);
   
   // BOOST_CHECK( XSecModelDef != 0 );
   // BOOST_CHECK( XSecModelDef->ValidProcess( synth_event->Summary() ) );

   // OK, now that the XSec calculator is setup, calculate the diff.xsec for the NCEL process
   //
   double xsec_diff = XSecModelDef->XSec( synth_event->Summary(), kPSQ2fE );
   
   // BOOST_REQUIRE_NE( xsec_diff, 0. );
      
   //
   // Setup XSec in the "synthetic" event
   //
   synth_event->SetDiffXSec( xsec_diff, kPSQ2fE );

   // re-weighting business
   //
   rew::GSyst_t param_to_tweak = rew::kXSecTwkDial_MaNCEL ;

   // Create a GReWeight object and add to it a set of weight calculators
   //
   rew::GReWeight rw;
   
   // Add weight calculator for MaNCEL & EtaNCEL  
   // NOTE: will add other weight calculators later
   //
   rw.AdoptWghtCalc( "xsec_ncel", new rew::GReWeightNuXSecNCEL() );

   // Get GSystSet and include the (single) input systematic parameter
   //
   rew::GSystSet& syst = rw.Systematics();
   syst.Init( param_to_tweak );

   double twk = -0.5;
   syst.Set( param_to_tweak, twk );
   rw.Reconfigure();
   double wt = rw.CalcWeight(*synth_event);

   // Now mess up with algoritms, (re)configs, etc.

   // One should do via AlgorithmFactory;
   // one can NOT directly instantiate XSecAlgorithmI object ( e.g. new XSecAlgorithmI(&alg_def) )
   // because several virtual functions are pure
   //
   Algorithm* alg_twk = algf->AdoptAlgorithm(id); 
   XSecAlgorithmI* XSecModelTwk = dynamic_cast<XSecAlgorithmI*>(alg_twk);
   XSecModelTwk->AdoptSubstructure();

   // This is the path to the (default) Ma value
   // Unfortunately, this needs to be done the long way because
   //    double MaDefault = gpl->GetDouble(MaPath);
   // says that there's no such key in registry
   //
   // string MaPath = "FormFactorsAlg/AxialFormFactorModel/QEL-Ma";
   // double MaDefault = (XSecModelTwk->GetConfig()).GetDouble(MaPath);

   return;

}
