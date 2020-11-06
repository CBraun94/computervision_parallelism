#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include <string>

inline void _log(std::string caller, std::string msg)
{
    std::cout << "tid" << gettid()<< " - "<< caller <<" - " << msg << std::endl << std::flush;
}

#endif // LOG_HPP_INCLUDED
