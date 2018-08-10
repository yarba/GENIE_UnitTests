
#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_suite.hpp>

#include "ExternalFunctions.h"

using namespace boost::unit_test;

/* NOTE: no need to have input args - the way unit_test_main is called,
         the args will get in (somehow) 
	 ... oh, that's actually not "somehow", that's likely to be done via
	 framework::master_test_suite().argc and/or  framework::master_test_suite().argv[] 
	 ... but if one passes then in explicitly, it'll probably work as well
	 */
bool init_unit_test_suite( /* int argc, char *argv[] */ )
{

   auto ts1 = BOOST_TEST_SUITE("XSec");
   
   ts1->add( BOOST_TEST_CASE( &lwlyn_ut ) );
   ts1->add( BOOST_TEST_CASE( &nieves_ut ) );
   // ---> later !!! ts1->add( BOOST_TEST_CASE( &singlekaon_ut ) ); // produces strangely large number
                                                                    // needs further understanding...
      
   auto ts2 = BOOST_TEST_SUITE("ReWei");
   ts2->add( BOOST_TEST_CASE( &rw_XSecCCQE_ut ) );
   ts2->add( BOOST_TEST_CASE( &rw_XSecNCEL_ut ) );
   ts2->add( BOOST_TEST_CASE( &rw_XSecCCRES_ut ) );
   ts2->add( BOOST_TEST_CASE( &rw_XSecNCRES_ut ) );

   // add other tests suites here...
   
   framework::master_test_suite().add(ts1);
   framework::master_test_suite().add(ts2);
     
   return true;

}

