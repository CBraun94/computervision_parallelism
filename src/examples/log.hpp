#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include <string>
#include <chrono> 
#include <iostream>
#include <functional>

namespace cb{

constexpr auto _delimiter = ".";
constexpr auto _ex1 = "one";
constexpr auto _ex2 = "two";
constexpr auto _ex3 = "three";
constexpr auto _ex4 = "four";
constexpr auto _ex5 = "five";
constexpr auto _ex6 = "six";
constexpr auto _ex7 = "seven";
constexpr auto _ex8 = "eight";
constexpr auto _ex9 = "nine";

using LogFunc = std::function<void(void)>;

inline void log(std::string caller, std::string msg)
{
    std::cout << "tid" << gettid()<< " - "<< caller <<" - " << msg << std::endl << std::flush;
}

inline void timetaken(std::string name, LogFunc f)
{
    auto start = std::chrono::high_resolution_clock::now(); 
    f();
    auto stop = std::chrono::high_resolution_clock::now(); 
    
    auto durationms = duration_cast<std::chrono::milliseconds>(stop - start); 
    auto durationsec = duration_cast<std::chrono::seconds>(stop - start);
  
    std::cout << "Time taken by " << name << ": " << durationsec.count() << " seconds or " << durationms.count() << " milliseconds" << std::endl << std::flush;
}

inline void run_example(std::string ex, LogFunc f)
{
    std::cout<<"start of example: " << ex << std::endl << std::flush;
    f();
    std::cout<<"end of example: " << ex << std::endl << std::flush;
}

}

#endif // LOG_HPP_INCLUDED
