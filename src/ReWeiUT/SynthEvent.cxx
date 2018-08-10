
#include "SynthEvent.h"

using namespace genie;

SynthEvent::SynthEvent()
   : genie::EventRecord()
{

   // "synthetic" event
   //
   InitialState init_state( 6, 12, 14 );
   TLorentzVector nu_p4(0., 0., 3., 3.); //px, py, pz, E in GeV
   init_state.SetProbeP4( nu_p4 );
   init_state.TgtPtr()->SetHitNucPdg( 2112 );
      
   this->AttachSummary( new Interaction( init_state, ProcessInfo( kScQuasiElastic, kIntWeakCC ) ) );
   this->Summary()->KinePtr()->Setx( 0.538, true );
   this->Summary()->KinePtr()->Sety( 0.042, true );
   this->Summary()->KinePtr()->SetQ2( 0.103, true );
   this->Summary()->KinePtr()->SetW( 0.938, true );
   this->Summary()->KinePtr()->UseSelectedKinematics(); // this is a must if kine vars are marked as "selected" 
                                                               // which is typically the case when an event is generated by the EVTdriver;
					                       // if not, the returned xsec=0
   this->Summary()->SetBit(kIAssumeFreeNucleon); // this is essential to generate diff. xsec; otherwise somethig else is generated
                                                        // and this is what the RW does !!!
      
//
// add probe and target to the event; probe is mandatory, otherwise the RW will crash
// 
   this->AddParticle( 14,         kIStInitialState,        -1, -1,  4,  4,  0.,     0.,     3.,     3.,   
                             0.982484, 0.250677, -0.742634, 0.000000 );
   this->AddParticle( 1000060120, kIStInitialState,        -1, -1,  2,  3,  0.,     0.,     0.,    11.175, 
                             0., 0., 0., 0. );

/* in this case no need to have all secondaries in the event record, just overall kinenatic and probe/target would be enough

   synth_event->AddParticle( 2112,       kIStNucleonTarget,        1, -1,  5,  5, -0.157, -0.071,  0.149,  0.918, 
                             0.982484, 0.250677, -0.742634, 0.000000 );
   synth_event->AddParticle( 1000060110, kIStIntermediateState,    1, -1, 11, 11,  0.157,  0.071, -0.149, 10.257, 
                             0., 0., 0., 0. );
   synth_event->AddParticle( 13,         kIStStableFinalState,     0, -1, -1, -1, -0.202,  0.241,  2.871,  2.890, 
                             0.982484, 0.250677, -0.742634, 0.000000 );
   synth_event->AddParticle( 2212,       kIStHadronInTheNucleus,   2, -1,  6,  6,  0.045, -0.312,  0.277,  1.028, 
                             0.982484, 0.250677, -0.742634, 0.000000 );
   synth_event->AddParticle( 2000000300, kIStNucleonClusterTarget, 5, -1,  7, 10,  0.045, -0.312,  0.277,  1.028, 
                             1.041835, -0.157858, -0.379211, 0.000000 );
   synth_event->AddParticle( 2212,       kIStStableFinalState,     6, -1, -1, -1, -0.074, -0.185,  0.238,  0.988, 
                             1.041835, -0.157858, -0.379211, 0.000000 );
   synth_event->AddParticle( 2212,       kIStStableFinalState,     6, -1, -1, -1,  0.085,  0.100, -0.023,  0.948, 
                             1.041835, -0.157858, -0.379211, 0.000000 );
   synth_event->AddParticle( 2212,       kIStStableFinalState,     6, -1, -1, -1, -0.072, -0.094, -0.048,  0.947, 
                             1.041835, -0.157858, -0.379211, 0.000000 );
   synth_event->AddParticle( 2112,       kIStStableFinalState,     6, -1, -1, -1,  0.107, -0.133,  0.110,  0.961, 
                             1.041835, -0.157858, -0.379211, 0.000000 );
   synth_event->AddParticle( 2000000002, kIStFinalStateNuclearRemnant, 3, -1, -1, -1, 0.157149,0.071223,-0.148711,7.440439,
                             0., 0., 0., 0. );
   synth_event->SetXSec( 1.40526805040119e-10 );
   synth_event->SetDiffXSec( 4.1199820102841004e-11, kPSQ2fE );
*/

}

SynthEventRES::SynthEventRES()
   : genie::EventRecord()
{

   // RES "synthetic" event
   //
   InitialState init_state( 1000260560, 14 );
   TLorentzVector nu_p4(0., 0., 10., 10.); //px, py, pz, E in GeV
   init_state.SetProbeP4( nu_p4 );
   init_state.TgtPtr()->SetHitNucPdg( 2112 );

   this->AttachSummary( new Interaction( init_state, ProcessInfo( kScResonant, kIntWeakCC ) ) );
   this->Summary()->KinePtr()->Setx( 0.074, true );
   this->Summary()->KinePtr()->Sety( 0.134, true );
   this->Summary()->KinePtr()->SetQ2( 0.145, true );
   this->Summary()->KinePtr()->SetW( 1.607, true );
   this->Summary()->KinePtr()->UseSelectedKinematics(); // this is a must if kine vars are marked as "selected" 
                                                        // which is typically the case when an event is generated by the EVTdriver;
					                // if not, the returned xsec=0
   this->Summary()->SetBit(kIAssumeFreeNucleon); // this is essential to generate diff. xsec; otherwise somethig else is generated
                                                        // and this is what the RW does !!!

//
// add probe and target to the event; probe is mandatory, otherwise the RW will crash
// 
   this->AddParticle( 14,         kIStInitialState,        -1, -1,  4,  4,  0.,     0.,     10.,     10.,   
                             0.982484, 0.250677, -0.742634, 0.000000 );
   this->AddParticle( 1000260560, kIStInitialState,        -1, -1,  2,  3,  0.,     0.,     0.,    52.090, 
                             0., 0., 0., 0. );

// |         nu_mu |             14 |      0 |  -1 |  -1 |   4 |   4 |  0.000 |  0.000 | 10.000 | 10.000 |  0.000 |  
// |          Fe56 |     1000260560 |      0 |  -1 |  -1 |   2 |   3 |  0.000 |  0.000 |  0.000 | 52.090 | 52.090 |  
// |       neutron |           2112 |     11 |   1 |  -1 |   5 |   5 | -0.206 | -0.093 |  0.195 |  0.927 |  0.940 |  
// |          Fe55 |     1000260550 |      2 |   1 |  -1 |  11 |  11 |  0.206 |  0.093 | -0.195 | 51.162 | 51.161 |  
// |           mu- |             13 |      1 |   0 |  -1 |  -1 |  -1 |  0.030 |  0.350 |  8.602 |  8.610 |  0.106 |  
// |      N+(1720) |          32124 |      3 |   2 |  -1 |   6 |   7 | -0.236 | -0.443 |  1.593 |  2.318 |  1.720 |  
// |        proton |           2212 |     14 |   5 |  -1 |   8 |   9 | -0.175 | -0.579 |  1.047 |  1.530 |  0.938 |     4 |  
// |           eta |            221 |     14 |   5 |  -1 |  10 |  10 | -0.061 |  0.136 |  0.546 |  0.788 |  0.547 |  
// |        proton |           2212 |      1 |   6 |  -1 |  -1 |  -1 | -0.350 | -0.221 |  0.898 |  1.363 |  0.938 |  
// |       neutron |           2112 |      1 |   6 |  -1 |  -1 |  -1 |  0.253 | -0.383 |  0.387 |  1.115 |  0.940 |  
// |           eta |            221 |      3 |   7 |  -1 |  12 |  14 | -0.061 |  0.136 |  0.546 |  0.788 |  0.547 |  
// |      HadrBlob |     2000000002 |     15 |   3 |  -1 |  -1 |  -1 |  0.128 |  0.118 | -0.434 | 50.214 |  0.000 |  
// |           pi0 |            111 |      1 |  10 |  -1 |  -1 |  -1 |  0.018 |  0.039 |  0.038 |  0.147 |  0.135 |  
// |           pi0 |            111 |      1 |  10 |  -1 |  -1 |  -1 | -0.060 | -0.039 |  0.379 |  0.409 |  0.135 |  
// |           pi0 |            111 |      1 |  10 |  -1 |  -1 |  -1 | -0.019 |  0.137 |  0.129 |  0.232 |  0.135 |

// |--> *Selected* Bjorken x = 0.074
// |--> *Selected* Inelasticity y = 0.134
// |--> *Selected* Momentum transfer Q2 (>0) = 0.145
// |--> *Selected* Hadronic invariant mass W = 1.607


}
