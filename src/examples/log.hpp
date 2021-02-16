#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include "../cbparallel/util/cblog.hpp"

namespace cb {

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

}

inline void run_example(std::string ex, cb::LogFunc f)
{
    std::string sa, sb;
    
    sa = "start of example: " + ex;
    cb::log("run_example", sa);
    f();
    sb = "end of example: " + ex;
    cb::log("run_example", sb);
}

#endif // LOG_HPP_INCLUDED
