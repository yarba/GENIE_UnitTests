
#include "Utils.h"

extern std::string path2ut()
{

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
      thepath = "";
   }

   return thepath;

}
