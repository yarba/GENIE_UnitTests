#ifndef UPDATE_BENCHMARK_H
#define UPDATE_BENCHMARK_H

#include <iostream>
#include <fstream>
#include <string>

class UpdateBenchmark {

   public:
   
      ~UpdateBenchmark();
      
      static UpdateBenchmark* Instance();
      void Write( const std::string& );
   
   private:
   
      UpdateBenchmark();
   
      std::ofstream           fOstr;
      static UpdateBenchmark* fInstance;

};

#endif
