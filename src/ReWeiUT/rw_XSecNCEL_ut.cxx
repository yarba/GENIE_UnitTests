
#include "CommonRwght.h"

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
   
   // reset ProcessInfo (D=QEL+CC)
   //
   synth_event->Summary()->SetProcInfo( ProcessInfo( kScQuasiElastic, kIntWeakNC ) );

   // now mess up with algoritm,s configs, etc.
   //
   
   AlgConfigPool* conf_pool = AlgConfigPool::Instance();
   Registry* gpl = conf_pool->GlobalParameterList();   
   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/QEL-NC");
  
   AlgId id(xsec_alg);

   AlgFactory* algf = AlgFactory::Instance();
   Algorithm* alg_def = (Algorithm*)(algf->GetAlgorithm(id)); // ugly trick - cast away const
   XSecAlgorithmI* XSecModelDef = dynamic_cast<XSecAlgorithmI*>(alg_def);
   
   BOOST_CHECK( XSecModelDef != 0 );
   BOOST_CHECK( XSecModelDef->ValidProcess( synth_event->Summary() ) );

   // OK, now that the XSec calculator is setup, calculate the diff.xsec for the NCEL process
   //
   double xsec_diff = XSecModelDef->XSec( synth_event->Summary(), kPSQ2fE );
   
   BOOST_REQUIRE_NE( xsec_diff, 0. );
      
   //
   // Setup XSec in the "synthetic" event
   //
   synth_event->SetDiffXSec( xsec_diff, kPSQ2fE );

   // re-weighting business
   //
   // Create a GReWeight object and add to it a set of weight calculators
   //
   rew::GReWeight rw;
   
   // tweak in the units of sigma
   //
   double twk = -0.5;
   
   // Sigma's (-/+) can be extracted from GSystUncertainty
   //
   rew::GSystUncertainty* syser = rew::GSystUncertainty::Instance();

   // Mass
   //
   rew::GSyst_t param_to_tweak = rew::kXSecTwkDial_MaNCEL ;
   double sigmin_ma = syser->OneSigmaErr( param_to_tweak, -1 );
  
   // Add weight calculator for MaNCEL & EtaNCEL  
   // NOTE: will add other weight calculators later
   //
   rw.AdoptWghtCalc( "xsec_ncel", new rew::GReWeightNuXSecNCEL() );

   // Get GSystSet and include the (single) input systematic parameter
   //
   rew::GSystSet& syst = rw.Systematics();

   syst.Init( param_to_tweak );
   syst.Set( param_to_tweak, twk );
   rw.Reconfigure();
   double wt_ma = rw.CalcWeight(*synth_event);
   
   // restore Ma in the RW module
   //
   syst.Set( param_to_tweak, 0. );

   // same for Eta
   //
   param_to_tweak = rew::kXSecTwkDial_EtaNCEL;
   double sigmin_eta = syser->OneSigmaErr( param_to_tweak, -1 );   
   syst.Init( param_to_tweak );
   syst.Set( param_to_tweak, twk );
   rw.Reconfigure();
   double wt_eta = rw.CalcWeight(*synth_event);

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
   string MaPath = "QEL-Ma";
   double MaDefault = (XSecModelTwk->GetConfig()).GetDouble(MaPath);
   string EtaPath = "EL-Axial-Eta";
   double EtaDefault = (XSecModelTwk->GetConfig()).GetDouble(EtaPath);

   // Create tmp XSec algorithm with the tweaked Ma & Eta
   //
   double MaChange = MaDefault * ( 1. + sigmin_ma*twk );
   double EtaChange = EtaDefault * (1. + sigmin_eta*twk );
   //
   Registry r("Tmp_MaTwk",false);
   r.Set( MaPath, MaChange );
   XSecModelTwk->Configure(r);

   // For some (strange) reason one must repeat these 2 procedures below,
   // even if it was done when synth_event was initially composed, 
   // right before XSec was calculated with the "decault" component 
   //
   synth_event->Summary()->KinePtr()->UseSelectedKinematics();
   synth_event->Summary()->SetBit(kIAssumeFreeNucleon);
   //
   double xsec_diff_twk = XSecModelTwk->XSec( synth_event->Summary(), synth_event->DiffXSecVars() );

   BOOST_REQUIRE_NE( xsec_diff_twk, 0. );
   
   // Scale original XSecDiff with the weight calculated by the RW
   // and compared with the one calculated by the "tweaked" one
   //
   double xsec_diff_scaled = wt_ma*synth_event->DiffXSec();
   //
   double delta = fabs(xsec_diff_twk - xsec_diff_scaled) / synth_event->DiffXSec() ;
   delta *= 100; // in percent
   
   BOOST_CHECK_CLOSE( xsec_diff_twk, xsec_diff_scaled, tolerance_in_percent );
   
   r.Set( MaPath, MaDefault ); // restore default axial Mass
   r.Set( EtaPath, EtaChange );
   XSecModelTwk->Configure(r);
   
   xsec_diff_twk = XSecModelTwk->XSec( synth_event->Summary(), synth_event->DiffXSecVars() );

   BOOST_REQUIRE_NE( xsec_diff_twk, 0. );
   
   // Scale original XSecDiff with the weight calculated by the RW
   // and compared with the one calculated by the "tweaked" one
   //
   xsec_diff_scaled = wt_eta*synth_event->DiffXSec();

   //
   delta = fabs(xsec_diff_twk - xsec_diff_scaled) / synth_event->DiffXSec() ;
   delta *= 100; // in percent
   
   BOOST_CHECK_CLOSE( xsec_diff_twk, xsec_diff_scaled, tolerance_in_percent );

   return;

}
