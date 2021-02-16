#include "cbpoolworker.hpp"

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include "../util/cblog.hpp"

CBPoolWorker::~CBPoolWorker()
{
    /* consider virtual CBVirtualThread::DoBeforeDestruct */
    terminate();
    resume();
    _event_finalized.WaitForSignal();
}

CBPoolWorker::CBPoolWorker ( const CBPoolWorker& w )
{
    this->_gettask = w._gettask;
}

CBPoolWorker::CBPoolWorker ( CBPoolWorker && w )
{
    _gettask = std::move(w._gettask);
}

CBPoolWorker & CBPoolWorker::operator= ( const CBPoolWorker& w )
{
    _gettask = w._gettask;
    return *this;
}

void CBPoolWorker::resume()
{
    _event_resume.Signal();
}

void CBPoolWorker::ThreadMainWrapper()
{
    while(!terminated())
    {
        cb::log("CBPoolWorker", "wait for resume");
        _event_resume.WaitForSignal();
        
        cb::log("CBPoolWorker", "check terminated");
        if(terminated()){
                cb::log("CBPoolWorker", "terminate break");
                break;
        } else {
           _work(); 
        }
    }
    _event_finalized.Signal();
    cb::log("CBPoolWorker", "about to terminate");
}

void CBPoolWorker::_work()
{
    CBTask* t = 0;
    cb::log("CBPoolWorker", "gettask");
    if(_gettask != NULL)
    {
        _sem_working.get()->Enter();
        do{
            t = _gettask();
            if (t != NULL)
            {
                (*t)();
                delete t;
                
                cb::log("CBPoolWorker", "task done");
            } else 
            {
                cb::log("CBPoolWorker", "no more work to do");
            } 
        }while((t != NULL)&&(!terminated()));
        _sem_working.get()->Leave();
    } else 
    {
        // throw exception
    }
}
