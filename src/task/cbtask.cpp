#include "cbtask.hpp"

#include "../log.hpp"

CBTask::CBTask ( CBTask && t )
{
    callback = std::move(t.callback);
}

CBTask::CBTask ( const CBTask& t )
{
    callback = t.callback;
}

CBTask & CBTask::operator= ( const CBTask& t )
{
    callback = t.callback;
    return *this;
}

void CBTask::operator()() const
{
    Execute();
    
    if(callback != NULL)
        callback();
}

void CBTask::Execute() const
{
    _log("CBTask", "Execute");
}

