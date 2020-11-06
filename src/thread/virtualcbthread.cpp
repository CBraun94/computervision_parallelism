#include "virtualcbthread.hpp"

#include <functional> /* std::bind */
#include <algorithm>
#include <iostream>

#include "../log.hpp"

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
    //->_threadID = gettid(); /* linux specific */
    
    _log("ThreadMainWrapperEntry", "start");
    
    //sleep(1);
    
    t->_event_start.WaitForSignal();
    
    if(!t->terminated()){
        t->ThreadMainWrapper();
    }
    
    t->_finished = true;
    
    _log("ThreadMainWrapperEntry", "exit");
    
    pthread_exit(NULL);
    
    return NULL;
}

void VirtualCBThread::create_pthread(){
    i = pthread_create(&_thread, NULL, VirtualCBThread::ThreadMainWrapperEntry, this);
}
