#include "cbtaskanonymous.hpp"

#include <iostream>

CBTaskAnonymous::CBTaskAnonymous ( const CBTaskAnonymous& t )
{
    task = t.task;
}

CBTaskAnonymous::CBTaskAnonymous ( CBTaskAnonymous && t)
{
    task = std::move(t.task);
}

CBTaskAnonymous & CBTaskAnonymous::operator= ( const CBTaskAnonymous& t )
{
    task = t.task;
    return *this;
}

void CBTaskAnonymous::Execute() const
{
    std::cout << "CBTaskAnonymous Execute" << std::endl << std::flush;
    if(task != NULL)
        task();
}
