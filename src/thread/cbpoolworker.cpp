#include "cbpoolworker.hpp"

#include <iostream>

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include "../log.hpp"

CBPoolWorker::~CBPoolWorker()
{
    /* consider virtual CBVirtualThread::DoBeforeDestruct */
    terminate();
    resume();
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
        _log("CBPoolWorker", "wait for resume");
        _event_resume.WaitForSignal();
        
        _log("CBPoolWorker", "check terminated");
        if(terminated()){
                _log("CBPoolWorker", "terminate break");
                break;
        }
        
        CBTask* t = 0;
        _log("CBPoolWorker", "gettask");
        do{
            if(_gettask != NULL)
            {
                t = _gettask();
                if (t != NULL)
                {
                    (*t)();
                    delete t;
                
                    _log("CBPoolWorker", "task done");
                } else 
                {
                    _log("CBPoolWorker", "no more work to do");
                }
            } else 
            {
                // throw exception
            }
        }while((t != NULL)&&(!terminated()));
    }
    _log("CBPoolWorker", "about to terminate");
}
