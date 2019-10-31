#include "BoostUtils.h"
#include "BenchmarkCriteria.h"

#ifdef PRINTOUT
#include "UpdateBenchmark.h"
#endif
#include "Physics/Coherent/XSection/ARConstants.h"
#include "Framework/Interaction/Interaction.h"

using namespace std;
using namespace genie;
using namespace boost::unit_test;
using namespace alvarezruso;

void arconstants_ut()
{
  ARConstants* ar=new ARConstants();
  double val;
  std::ostringstream os;
  std::string s;

#ifdef PRINTOUT  
  UpdateBenchmark::Instance()->Write( "namespace arconstant {" );
#endif

  val=ar->HBar();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double HBar = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::HBar, tolerance_in_percent );
#endif

  val=ar->Ma_Nucleon();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Ma_Nucleon = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Ma_Nucleon, tolerance_in_percent );
#endif

  val=ar->Mv_Nucleon();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Mv_Nucleon = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Mv_Nucleon, tolerance_in_percent );
#endif

  val=ar->Ma_Delta();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Ma_Delta = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Ma_Delta, tolerance_in_percent );
#endif

  val=ar->Mv_Delta();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Mv_Delta = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Mv_Delta, tolerance_in_percent );
#endif

  val=ar->GAxial();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double GAxial = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::GAxial, tolerance_in_percent );
#endif

  val=ar->Rho0();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Rho0 = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Rho0, tolerance_in_percent );
#endif

  val=ar->CA4_A();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double CA4_A = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::CA4_A, tolerance_in_percent );
#endif

  val=ar->CA5_A();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double CA5_A = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::CA5_A, tolerance_in_percent );
#endif

  val=ar->CA4_B();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double CA4_B = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::CA4_B, tolerance_in_percent );
#endif

  val=ar->CA5_B();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double CA5_B = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::CA5_B, tolerance_in_percent );
#endif

  val=ar->PiDecayConst();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double PiDecayConst = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::PiDecayConst, tolerance_in_percent );
#endif

  val=ar->DeltaNCoupling();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double DeltaNCoupling = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::DeltaNCoupling, tolerance_in_percent );
#endif

  val=ar->CosCabibboAngle();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double CosCabibboAngle = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::CosCabibboAngle, tolerance_in_percent );
#endif

  val=ar->SinWeinbergAngle();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double SinWeinbergAngle = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::SinWeinbergAngle, tolerance_in_percent );
#endif

  val=ar->GFermi();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double GFermi = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::GFermi, tolerance_in_percent );
#endif

  val=ar->ElectronMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double ElectronMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::ElectronMass, tolerance_in_percent );
#endif

  val=ar->MuonMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double MuonMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::MuonMass, tolerance_in_percent );
#endif

  val=ar->TauMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double TauMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::TauMass, tolerance_in_percent );
#endif

  val=ar->ProtonMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double ProtonMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::ProtonMass, tolerance_in_percent );
#endif

  val=ar->NucleonMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double NucleonMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::NucleonMass, tolerance_in_percent );
#endif

  val=ar->NucleonMassSq();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double NucleonMassSq = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::NucleonMassSq, tolerance_in_percent );
#endif

  val=ar->DeltaPMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double DeltaPMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::DeltaPMass, tolerance_in_percent );
#endif

  val=ar->Delta0Mass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Delta0Mass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Delta0Mass, tolerance_in_percent );
#endif

  val=ar->PiPMass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double PiPMass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::PiPMass, tolerance_in_percent );
#endif

  val=ar->Pi0Mass();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double Pi0Mass = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::Pi0Mass, tolerance_in_percent );
#endif

  val=ar->cm38Conversion();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double cm38Conversion = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::cm38Conversion, tolerance_in_percent );
#endif

  val=ar->NCFactor();
#ifdef PRINTOUT  
  os.clear();
  os.str("");
  os << val;
  s = "static const double NCFactor = " + os.str() + ";" ;
  UpdateBenchmark::Instance()->Write( s );
#else
  BOOST_CHECK_CLOSE( val, coh_xsec::arconstant::NCFactor, tolerance_in_percent );
#endif

#ifdef PRINTOUT
   UpdateBenchmark::Instance()->Write( "} // end namespace arconstants" );
#endif
  return;
}
