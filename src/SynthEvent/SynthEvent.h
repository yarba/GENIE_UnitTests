#ifndef SYNTH_EVENT_H
#define SYNTH_EVENT_H

#include "Framework/EventGen/EventRecord.h"

#include "Framework/GHEP/GHepParticle.h"
#include "Framework/Conventions/Units.h"

class SynthEvent : public genie::EventRecord
{

   public :
   
      // ctor & dtor
      //
      SynthEvent();
      ~SynthEvent() {}

};

class SynthEventRES : public genie::EventRecord
{

   public :
   
      // ctor & dtor
      //
      SynthEventRES();
      ~SynthEventRES() {}

};

class SynthEventCOH : public genie::EventRecord
{

   public :
   
      // ctor & dtor
      //
      SynthEventCOH();
      ~SynthEventCOH() {}

};

#endif
