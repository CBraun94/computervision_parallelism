#include "cbtaskfor.hpp"

#include <iostream>

CBTaskFor::CBTaskFor ( const CBTaskFor& t )
{
    _task = t._task;
}

CBTaskFor::CBTaskFor ( CBTaskFor && t)
{
    _task = std::move(t._task);
}

CBTaskFor & CBTaskFor::operator= ( const CBTaskFor& t )
{
    _task = t._task;
    return *this;
}

void CBTaskFor::Execute() const
{
    std::cout << "CBTaskFor Execute" << std::endl << std::flush;
    if(_task != NULL)
        for(auto i = _begin; i < _end; i+=_increment) 
            _task(i);
}
