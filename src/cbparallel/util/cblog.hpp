#ifndef CBLOG_HPP_INCLUDED
#define CBLOG_HPP_INCLUDED

#include <string>
#include <functional>

namespace cb{

using LogFunc = std::function<void(void)>;

void log(std::string caller, std::string msg);
void timetaken(std::string name, LogFunc f);

}

#endif // CBLOG_HPP_INCLUDED
