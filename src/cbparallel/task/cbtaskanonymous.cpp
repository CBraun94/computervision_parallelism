#include "cbtaskanonymous.hpp"

#include "../util/cblog.hpp"

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
    std::string s;
    s = "Execute";
    cb::log("CBTaskAnonymous", s);
    
    if(task != NULL)
        task();
}
