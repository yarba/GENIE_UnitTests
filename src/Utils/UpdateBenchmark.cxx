
#include "UpdateBenchmark.h"

#include "Utils.h"

UpdateBenchmark* UpdateBenchmark::fInstance = 0;

UpdateBenchmark::UpdateBenchmark()
{

/*
   int pid = getpid();   
   char exepath[ PATH_MAX + 1 ] = {0};
   std::string arg = "/proc/" + std::to_string(pid) + "/exe";   
   readlink( arg.c_str(), exepath, sizeof(exepath) );
   
   std::string thepath = exepath;
   
   std::string task_name = "UnitTests";
   size_t pos = thepath.find( task_name );
   if ( pos != std::string::npos )
   {      
      thepath.erase( pos+task_name.length() ); // erase all the way to the end (npos)
   }
   else
   {
      std::cout << " Can NOT find path to the UnitTests directory; bail out" << std::endl;
      exit(1);
   }
*/   
   
   std::string thepath = path2ut();
   
   if ( thepath.empty() )
   {
      std::cout << " Can NOT find path to the UnitTests directory; bail out" << std::endl;
      exit(1);
   }
   
   thepath += "/src/Common";
   DIR* exists = opendir( thepath.c_str() );
   if ( !exists )
   {
      std::cout << " Can NOT find path to UnitTests/src/Common; updates can NOT be written out " << std::endl;
      exit(1);
   }
   else
   {
      (void) closedir( exists );
      //
      std::string outfile = thepath + "/BenchmarkCriteria-Updates.h";
      //
      // check if outfile is already there; delete it in so
      //
      if ( FILE* file = fopen(outfile.c_str(),"r") )
      {
         fclose(file);
	 std::string command = "rm -f " + outfile;
	 system( command.c_str() );
      }
      //
      if ( !fOstr.is_open() )
      {
	 fOstr.open( outfile.c_str() );
      }
   }       
}

UpdateBenchmark::~UpdateBenchmark()
{

   if ( fOstr.is_open() ) fOstr.close();
   if ( fInstance )
   {
      delete fInstance;
      fInstance = 0;
   }

}

UpdateBenchmark* UpdateBenchmark::Instance()
{

   if ( fInstance == 0 )
   {
      fInstance = new UpdateBenchmark();
   }
   
   return fInstance;

}

void UpdateBenchmark::Write( const std::string& s )
{
      
   fOstr << s << std::endl;
   
   return;
   
}
