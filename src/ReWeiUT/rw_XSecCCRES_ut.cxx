
#include "CommonRwght.h"

// --> migration --> #include "Tools/ReWeight/GReWeightNuXSecCCRES.h"
#include "RwCalculators/GReWeightNuXSecCCRES.h"

#include "SynthEvent.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;

// NOTE (JVY): List of possible resonances:
//
//       kNoResonance = -1,
//       kP33_1232    =  0,
//       kS11_1535    =  1,
//       kD13_1520    =  2,
//       kS11_1650    =  3,
//       kD13_1700    =  4,
//       kD15_1675    =  5,
//       kS31_1620    =  6,
//       kD33_1700    =  7,
//       kP11_1440    =  8,
//       kP33_1600    =  9,
//       kP13_1720    = 10,
//       kF15_1680    = 11,
//       kP31_1910    = 12,
//       kP33_1920    = 13,
//       kF35_1905    = 14,
//       kF37_1950    = 15,
//       kP11_1710    = 16,
//       kF17_1970    = 17

void rw_XSecCCRES_ut()
{

   EventRecord* synth_event = new SynthEventRES();
   
   // (re)set exclusive tag
   //
   XclsTag exclt;
   exclt.SetResonance( kP33_1232 ); 
   synth_event->Summary()->SetExclTag( exclt );
      
   AlgConfigPool* conf_pool = AlgConfigPool::Instance();
   Registry* gpl = conf_pool->GlobalParameterList();
   
   // NOTE: Basically, RgAlg is just a "pair" of strings (but not an std::pair),
   // i.e. algorithm's name (e.g. Lwlyn...) and configuration (e.g. Dipole)
   //
   RgAlg xsec_alg = gpl->GetAlg("XSecModel@genie::EventGenerator/RES-CC");

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

   rew::GSyst_t param_to_tweak = rew::kXSecTwkDial_MvCCRES ;

   rew::GReWeight rw;
   
   rw.AdoptWghtCalc( "xsec_ccres", new rew::GReWeightNuXSecCCRES() );

   rew::GSystSet& syst = rw.Systematics();
   syst.Init( param_to_tweak );
   
   // By default GReWeightNuXSecCCRES is in `NormAndMaMvShape' mode 
   // If the input is MaCCRES or MvCCRES, switch the weight calculator to `MaMv' mode
   //
   rew::GReWeightNuXSecCCRES* rwccres = dynamic_cast<rew::GReWeightNuXSecCCRES*>( rw.WghtCalc("xsec_ccres") );  
   rwccres->SetMode( rew::GReWeightNuXSecCCRES::kModeMaMv );
   
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

