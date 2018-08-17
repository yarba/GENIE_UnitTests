
#include "CommonRwght.h"

#include "Tools/ReWeight/GReWeightNuXSecCOH.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void rw_XSecCOH_ut()
{

   double tolerance_in_percent = 0.001;

   EventRecord* synth_event = new SynthEventCOH();

   AlgConfigPool* conf_pool = AlgConfigPool::Instance();
   Registry* gpl = conf_pool->GlobalParameterList();
   
   // NOTE: Basically, RgAlg is just a "pair" of strings (but not an std::pair),
   // i.e. algorithm's name (e.g. Lwlyn...) and configuration (e.g. Dipole)
   //
   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/COH-CC");
  
   AlgId id(xsec_alg);

   AlgFactory* algf = AlgFactory::Instance();

   Algorithm* alg_def = (Algorithm*)(algf->GetAlgorithm(id)); // ugly trick - cast away const
   XSecAlgorithmI* XSecModelDef = dynamic_cast<XSecAlgorithmI*>(alg_def);
   
   BOOST_CHECK( XSecModelDef != 0 );
   BOOST_CHECK( XSecModelDef->ValidProcess( synth_event->Summary() ) );

   double xsec_diff = XSecModelDef->XSec( synth_event->Summary(), kPSxyfE ); // alt.: phase space = kPSxytfE 
                                                                             //       but it causses issues with Jacobian calc.
									     //       besides, the RW COH uses fPSxyfE

   BOOST_REQUIRE_NE( xsec_diff, 0. );

   synth_event->SetDiffXSec( xsec_diff, kPSxyfE ); 

   // re-weighting business
   //

   rew::GSyst_t param_to_tweak = rew::kXSecTwkDial_MaCOHpi ; // alternative variable is kXSecTwkDial_R0COHpi

   rew::GReWeight rw;
   
   rw.AdoptWghtCalc( "xsec_ccqe", new rew::GReWeightNuXSecCOH() );

   rew::GSystSet& syst = rw.Systematics();
   syst.Init( param_to_tweak );

   double twk = -0.5;
   syst.Set( param_to_tweak, twk );
   rw.Reconfigure();
   double wt = rw.CalcWeight(*synth_event);

   // now reconfigure XSec algorithm
   //
   
   Algorithm* alg_twk = algf->AdoptAlgorithm(id); 
   XSecAlgorithmI* XSecModelTwk = dynamic_cast<XSecAlgorithmI*>(alg_twk);
   XSecModelTwk->AdoptSubstructure();

   string MaPath = "COH-Ma";  // alt.: COH-Ro
   double MaDefault = (XSecModelTwk->GetConfig()).GetDouble(MaPath);
   
   // Sigma's (-/+) can be extracted from GSystUncertainty
   //
   rew::GSystUncertainty* syser = rew::GSystUncertainty::Instance();
   double sigmin = syser->OneSigmaErr( param_to_tweak, -1 );
   // ---> NOT NEEDED SO FAR ---> double sigpls = syser->OneSigmaErr( param_to_tweak,  1 );
   
   double MaChange = MaDefault * ( 1. + sigmin*twk );

   Registry r("Tmp_MaTwk",false);
   r.Set( MaPath, MaChange );
   XSecModelTwk->Configure(r);

   // need to repeat this since RW modules first require it, then override
   //
   synth_event->Summary()->KinePtr()->UseSelectedKinematics();
   // ---> synth_event->Summary()->SetBit(kIAssumeFreeNucleon);

   double xsec_diff_twk = XSecModelTwk->XSec( synth_event->Summary(), synth_event->DiffXSecVars() );
   
   BOOST_REQUIRE_NE( xsec_diff_twk, 0. );

   double xsec_diff_scaled = wt*synth_event->DiffXSec();

   double delta = fabs(xsec_diff_twk - xsec_diff_scaled) / synth_event->DiffXSec() ;
   delta *= 100; // in percent
   
   BOOST_CHECK_CLOSE( xsec_diff_twk, xsec_diff_scaled, tolerance_in_percent );
   
   delete synth_event;

   return;

}
