#include "cblog.hpp"

void cb::timetaken(std::string name, LogFunc f)
{
    auto start = std::chrono::high_resolution_clock::now(); 
    f();
    auto stop = std::chrono::high_resolution_clock::now(); 
    
    auto durationms = duration_cast<std::chrono::milliseconds>(stop - start); 
    auto durationsec = duration_cast<std::chrono::seconds>(stop - start);
  
    std::cout << "Time taken by " << name << ": " << durationsec.count() << " seconds or " << durationms.count() << " milliseconds" << std::endl << std::flush;
}
