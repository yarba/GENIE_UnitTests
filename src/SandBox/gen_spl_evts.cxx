
/* This example emulates the following:

gmkspl -n 50 -p 14 -t 1000180400 -e 20 --disable-bare-xsec-pre-calc \
--message-thresholds Messenger_whisper.xml --event-generator-list CCQE -o CCQE_1000180400_splines.xml

EXCEPT: it'll NOT output splines to CCQE_1000180400_splines.xml but instead will keep them in memory ! 

gevgen -n 5 -p 14 -t 1000180400 -e 3 -r 42 --seed 2989819 --cross-sections CCQE_1000180400_splines.xml \
 --message-thresholds Messenger_whisper.xml --event-generator-list CCQE
 
EXCEPT THE FOLLOWING:
a) it'll NOT take xsec splines from an external file but from memory
b) it'll NOT write output event(s) to file, so the run number (-r) is irrelevant

In addition, it isslustrates how to change the process (from CCQE to SingleKaon), 
reset the xsec/events generation driver, and repeat the procedure

*/


#include <iostream>

#include "Framework/Messenger/Messenger.h"
#include "Framework/Utils/RunOpt.h"
#include "Framework/Interaction/Interaction.h"
#include "Framework/ParticleData/PDGCodes.h"
#include "Framework/ParticleData/PDGLibrary.h"
#include "Framework/ParticleData/PDGUtils.h"

#include "Framework/EventGen/GEVGDriver.h"
#include "Framework/Utils/XSecSplineList.h"
#include "Framework/EventGen/EventRecord.h"

#include "Framework/Numerical/RandomGen.h"

using namespace std;
using namespace genie;


int main( /* int argc, char *argv[] */ )
{

   // try to silence GENIE Messenger just a little bit...
   //
   Messenger::Instance()->SetPrioritiesFromXmlFile("Messenger_whisper.xml");
       
   // Define the process (CCQE in this case, but there may be many other,
   // e.g. Charm, NuE, QE, CCDIS, NCDIS, CCRES, NCRES, SingleKaon,
   // CharmCCDIS, CharmCCQE, NuEElastic, IMD, COH, etc.
   //
   // NOTE: COH seems to take forever !
   //
   RunOpt::Instance()->SetEventGeneratorList("CCQE");   

   // Set the tune
   //
   // There're several ways to set the tune.
   // Most, if not all, GENIE applications define the tune through the command line interface
   // (the --tune <tune-name> argument).
   // In this case the tune name/setting propagates through the
   // --->   RunOpt::Instance()->ReadFromCommandLine( argc, argv );
   // If the tune is not explicitly given and/or if it's set to "Default", it'll translate
   // to G18_02a_00_000, as of GENIE R-3-series.
   // In principle, one can emulate an "empty" configuration command, as follows:
   // --->   RunOpt::Instance()->ReadFromCommandLine(0,0);
   // In this case, again, the tune name will be set to G18_02a_00_000 (default, and one may 
   // want to check if it's valid and to build it, as follows:
   // --->  RunOpt::Instance()->BuildTune();
   // --->  if ( ! RunOpt::Instance() -> Tune() ) {
   // --->     LOG("gunittest", pFATAL) << " No TuneId in RunOption";
   // --->     exit(-1);
   // --->  }
   // --->  RunOpt::Instance()->Tune()->Build() ;    
   //
   //
   // Alternatively, one can set tune through RunOpt::SetTuneName method, as shown below.  
   // NOTE: This method will call TuneId ctor which in turn will call the TuneId::Build method.
   //       So there's no need tocall the Build (or BuildTune) method again.
   //       BUT !!! It's necessary to set up also to the XSecSplineList  (as it'd be in RunOpt::BuildTune)
   //
   RunOpt::Instance()->SetTuneName("G18_02a_00_000");
   XSecSplineList::Instance()->SetCurrentTune( "G18_02a_00_000" );

   // disable-bare-xsec-pre-calc
   //
   RunOpt::Instance()->EnableBareXSecPreCalc(false);

   // Define # of knots, projectile nu, target nucleus, and max energy
   //
   int    NKnots = 50;
   int    NuPDG = 14;
   int    TgtPDG = 1000180400 ;
   double MaxE = 20.;
        
   // Define initial state for the given target and projectile
   //
   InitialState init_state( TgtPDG, NuPDG );
   
   // Greate and configure the GENIE/Generator driver
   //
   GEVGDriver driver;
   driver.SetEventGeneratorList(RunOpt::Instance()->EventGeneratorList());
   driver.Configure( init_state );
   
   // Generate splines for CCQE process
   //
   driver.CreateSplines( NKnots, MaxE );

/* // This is an example of writing out the splines 
   // The code fragment taken from $GENIE/src/Apps/gMakeSplines.cxx

  // Save the splines at the requested XML file
  XSecSplineList* xspl = XSecSplineList::Instance();
  bool NoCopy = false;
  bool save_init = !NoCopy;
  cout << "save_init = " << save_init << endl;
  xspl->SaveAsXml( "test_spl_1.xml", save_init ); // 2nd arg set to false means "no copy" ? or the other way around ?
                                                // ... if this matter at all...
*/   
   
   // Now prepare to generate an event (or multiple events in a loop)
   //
   // Q: Do we necessarily need to set the mask ???
   //
   // driver.SetUnphysEventMask(*RunOpt::Instance()->UnphysEventMask());
   //
   // Define kinematics
   //
   double NuE    = 3.;
   TLorentzVector nu_p4 (0., 0., NuE, NuE ); // px,py,pz,E (GeV)
   //
   // Set random seed (if desired)
   //
   long int seed = 2989819;
   RandomGen::Instance()->SetSeed(seed);
   //
   // Now generate the event
   //
   EventRecord* event = driver.GenerateEvent(nu_p4);
   //
   // Check if it's valid...
   //
   if ( !event )
   {
      cout << " FAILED to generate CCQE event " << endl; 
   }
   else
   {
   // ... and if so, print out out and then discard
   //
      cout << endl;
      cout << "   ===  HERE IS AN EXAMPLE CCQE EVENT RECORD  === " << endl;
      event->Print();
      cout << endl;
      delete event;
   }
   
   // Now change the process/Generator (--event-generator-list) to e.g. SingleKaon
   // and repeat the procedure
   //
   // ---> It takes forever ! !! ---> RunOpt::Instance()->SetEventGeneratorList("COH");
   RunOpt::Instance()->SetEventGeneratorList("SingleKaon");
   //
   // Reconfigure the driver
   //
   // NOTE: It should be Reset; otherwise the previous generator/process will stick
   //
   driver.Reset();
   driver.SetEventGeneratorList(RunOpt::Instance()->EventGeneratorList());
   driver.Configure( init_state );
   
   // NOTE: For this exercise we don't need to reset the tune, on initial state,
   //       or the kinematics, etc. For now, let's re-use what we already defined.
   
   // Generate splines for SingleKaon process
   //
   driver.CreateSplines( NKnots, MaxE );
   
/*
   xspl = XSecSplineList::Instance();
   xspl->SaveAsXml( "test_spl_2.xml", save_init );
*/   
      
   // Re-instate the seed (if desired)
   //
   RandomGen::Instance()->SetSeed(seed);
   
   // Generate event (same kinematics as for CCQE, but it's a different process)
   //
   event = driver.GenerateEvent(nu_p4);
   
   // And repeat event check, printout, clreanup
   //
   if ( !event )
   {
      cout << endl;
      cout << " FAILED to generate SingleKaon event " << endl; 
   }
   else
   {
   // ... and if so, print out out and then discard
   //
      cout << endl;
      cout << "   ===  HERE IS AN EXAMPLE SingleKaon EVENT RECORD  === " << endl;
      event->Print();
      cout << endl;
      delete event;
   }
   
   cout << "   ***  End of exercise !  *** " << endl;
     
   return 0; 

}

