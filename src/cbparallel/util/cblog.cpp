#include "cblog.hpp"

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include <chrono> 
#include <iostream>

void _print(std::string s){
    std::cout << s << std::endl << std::flush;
}

void cb::log(std::string caller, std::string msg)
{
    std::string s;
    auto tid = gettid();
    s =  "tid" + std::to_string(tid) + " - " + caller + " - " + msg;
    _print(s);
}

void cb::timetaken(std::string name, LogFunc f)
{
    auto start = std::chrono::high_resolution_clock::now(); 
    f();
    auto stop = std::chrono::high_resolution_clock::now(); 
    
    auto durationms = duration_cast<std::chrono::milliseconds>(stop - start); 
    auto durationsec = duration_cast<std::chrono::seconds>(stop - start);
    
    std::string s;
  
    s = "Time taken by " + name + ": " + std::to_string(durationsec.count()) + " seconds or " + std::to_string(durationms.count()) + " milliseconds";
    _print(s);
}
