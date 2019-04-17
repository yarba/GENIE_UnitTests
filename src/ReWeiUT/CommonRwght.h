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

// migration
//#include "Tools/ReWeight/GSystSet.h"
//#include "Tools/ReWeight/GSyst.h"
//#include "Tools/ReWeight/GReWeight.h"
//#include "Tools/ReWeight/GSystUncertainty.h"
//
#include "RwFramework/GSystSet.h"
#include "RwFramework/GSyst.h"
#include "RwFramework/GSystUncertainty.h"
#include "RwFramework/GReWeight.h"

