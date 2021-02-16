#include "virtualcbthread.hpp"

#include <functional> /* std::bind */
#include <algorithm>

#include "../util/cblog.hpp"

VirtualCBThread::VirtualCBThread(){
    //create_pthread();
}

VirtualCBThread::~VirtualCBThread()
{
    if (_thread != 0)
        if(!finished()){
            terminate();
            join();
        }
}

VirtualCBThread::VirtualCBThread ( VirtualCBThread && t )
{
	_thread = std::move(t._thread);
}

void VirtualCBThread::start(){
    _event_start.Signal();
    create_pthread();
}

void VirtualCBThread::join() const
{
    pthread_join(_thread, NULL);
}

void VirtualCBThread::terminate()
{
    _terminated = true;
}

bool VirtualCBThread::finished() const
{
    return _finished;
}

bool VirtualCBThread::terminated() const
{
    return _terminated;
}

pthread_t VirtualCBThread::handle() const
{
    return _thread;
}

pid_t VirtualCBThread::threadID() const
{
    return _threadID;
}

void * VirtualCBThread::ThreadMainWrapperEntry(void* This)
{
    auto t = (( VirtualCBThread *)This);
    
    cb::log("ThreadMainWrapperEntry", "start");
    
    t->_event_start.WaitForSignal();
    
    if(!t->terminated()){
        t->ThreadMainWrapper();
    }
    
    t->_finished = true;
    
    cb::log("ThreadMainWrapperEntry", "exit");
    
    pthread_exit(NULL);
    
    return NULL;
}

void VirtualCBThread::create_pthread(){
    i = pthread_create(&_thread, NULL, VirtualCBThread::ThreadMainWrapperEntry, this);
}
