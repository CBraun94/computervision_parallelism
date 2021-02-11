#ifndef CBLOG_HPP_INCLUDED
#define CBLOG_HPP_INCLUDED

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include <string>
#include <chrono> 
#include <iostream>
#include <functional>

namespace cb{

using LogFunc = std::function<void(void)>;

inline void log(std::string caller, std::string msg)
{
    std::cout << "tid" << gettid()<< " - "<< caller <<" - " << msg << std::endl << std::flush;
}

void timetaken(std::string name, LogFunc f);

}

#endif // CBLOG_HPP_INCLUDED
