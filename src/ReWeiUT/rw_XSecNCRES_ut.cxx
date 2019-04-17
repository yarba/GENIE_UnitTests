#include "CommonRwght.h"

// --> migration --> #include "Tools/ReWeight/GReWeightNuXSecNCRES.h"
#include "RwCalculators/GReWeightNuXSecNCRES.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

void rw_XSecNCRES_ut()
{

   double tolerance_in_percent = 0.001;

   EventRecord* synth_event = new SynthEventRES();

   // (re)set scattering type
   //
   synth_event->Summary()->SetProcInfo( ProcessInfo( kScResonant, kIntWeakNC ) );
   //
   // (re)set exclusive tag
   //
   XclsTag exclt;
   exclt.SetResonance( kP33_1232 ); 
   synth_event->Summary()->SetExclTag( exclt );
      
   AlgConfigPool* conf_pool = AlgConfigPool::Instance();
   Registry* gpl = conf_pool->GlobalParameterList();

   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/RES-NC");

   AlgId id(xsec_alg);

   AlgFactory* algf = AlgFactory::Instance();

   Algorithm* alg_def = (Algorithm*)(algf->GetAlgorithm(id)); // ugly trick - cast away const
   XSecAlgorithmI* XSecModelDef = dynamic_cast<XSecAlgorithmI*>(alg_def);

   BOOST_CHECK( XSecModelDef != 0 );
   BOOST_CHECK( XSecModelDef->ValidProcess( synth_event->Summary() ) );

   double xsec_diff = XSecModelDef->XSec( synth_event->Summary(), kPSWQ2fE );
   
   BOOST_REQUIRE_NE( xsec_diff, 0. );

   synth_event->SetDiffXSec( xsec_diff, kPSWQ2fE );

   // re-weighting business
   //

   rew::GSyst_t param_to_tweak = rew::kXSecTwkDial_MvNCRES ;

   rew::GReWeight rw;
   
   rw.AdoptWghtCalc( "xsec_ncres", new rew::GReWeightNuXSecNCRES() );

   rew::GSystSet& syst = rw.Systematics();
   syst.Init( param_to_tweak );
   
   // By default GReWeightNuXSecNCRES is in `NormAndMaMvShape' mode 
   // If the input is MaNCRES or MvNCRES, switch the weight calculator to `MaMv' mode
   //
   rew::GReWeightNuXSecNCRES* rwncres = dynamic_cast<rew::GReWeightNuXSecNCRES*>( rw.WghtCalc("xsec_ncres") );  
   rwncres->SetMode( rew::GReWeightNuXSecNCRES::kModeMaMv );
   
   double twk = -0.5;
   syst.Set( param_to_tweak, twk );
   rw.Reconfigure();
   double wt = rw.CalcWeight( *synth_event );

   Algorithm* alg_twk = algf->AdoptAlgorithm(id); 
   XSecAlgorithmI* XSecModelTwk = dynamic_cast<XSecAlgorithmI*>(alg_twk);
   XSecModelTwk->AdoptSubstructure();

//  this->SetMaPath("RES-Ma");
//  this->SetMvPath("RES-Mv");
   string MvPath = "RES-Mv";
   double MvDefault = (XSecModelTwk->GetConfig()).GetDouble(MvPath);

   rew::GSystUncertainty* syser = rew::GSystUncertainty::Instance();
   double sigmin = syser->OneSigmaErr( param_to_tweak, -1 );

   double MvChange = MvDefault * ( 1. + sigmin*twk );

   Registry r("Tmp_MvTwk",false);
   r.Set( MvPath, MvChange );
   XSecModelTwk->Configure(r);

   synth_event->Summary()->KinePtr()->UseSelectedKinematics();
   synth_event->Summary()->SetBit(kIAssumeFreeNucleon);

   double xsec_diff_twk = XSecModelTwk->XSec( synth_event->Summary(), synth_event->DiffXSecVars() );
   
   BOOST_REQUIRE_NE( xsec_diff_twk, 0. );

   double xsec_diff_scaled = wt*synth_event->DiffXSec();

   double delta = fabs(xsec_diff_twk - xsec_diff_scaled) / synth_event->DiffXSec() ;
   delta *= 100; // in percent
   
   BOOST_CHECK_CLOSE( xsec_diff_twk, xsec_diff_scaled, tolerance_in_percent );

   delete synth_event;
   
   return;

}
