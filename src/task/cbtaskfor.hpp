#ifndef CBTASKFOR_HPP_INCLUDED
#define CBTASKFOR_HPP_INCLUDED

#include "cbtask.hpp"

#include <functional> /* std::bind */
#include <iostream>

using TaskFor = std::function<void(int)>;

class CBTaskFor: public CBTask{
private:
    TaskFor _task;
    
    int _begin;
    int _end;
    int _increment;
};

#endif // CBTASKFOR_HPP_INCLUDED
