#include "cbpoolworker.hpp"

#include <iostream>

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

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
    while(!terminated()){
        usleep(100);
        std::cout << "CBPoolWorker: wait for resume" << std::endl << std::flush;
        _event_resume.WaitForSignal();
        
        std::cout << "CBPoolWorker: check terminated" << std::endl << std::flush;
        if(terminated())
            return;
        
        CBTask* t = 0;
        std::cout << "CBPoolWorker: gettask" << std::endl << std::flush;
        if(_gettask != NULL){
            do{
            t = _gettask();
            if (t != NULL){
                (*t)();
                delete t;
                
                std::cout << "CBPoolWorker: task done" << std::endl << std::flush;
            } else {
                std::cout << "CBPoolWorker: no more work to do" << std::endl << std::flush;
            }
            
            }while((t != NULL)&&(!terminated()));
            
        } else {
            // throw exception
        }
    }
}
