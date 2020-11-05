#ifndef VIRTUALCBTHREAD_HPP_INCLUDED
#define VIRTUALCBTHREAD_HPP_INCLUDED

#include "../sync/eventposix.hpp"

#include <pthread.h>
#include <atomic>

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

using Event = EventPosix;

class VirtualCBThread
{
public:
    VirtualCBThread();
    virtual ~VirtualCBThread();
    
    VirtualCBThread(const VirtualCBThread&)=delete;
    VirtualCBThread(VirtualCBThread&& t);
    
    void start();
    void join() const;
    void terminate();
    
    /*!
     * brief: will be set to true as the thread is finishes it's given task
     * (read only) 
     * see also: ThreadMainWrapper, ThreadMainWrapperEntry
     */
    bool finished() const;
    bool terminated() const;
    
    pthread_t handle() const; /* pthread specific */
    
    pid_t threadID() const; /* linux specific */
protected:
   virtual void ThreadMainWrapper(void) {};
private:
    pthread_t _thread = 0; /* pthread specific */
    int i = 0; /* pthread specific */
    
    pid_t _threadID = 0; /* linux specific */
    
    std::atomic<bool> _finished = false;
    std::atomic<bool> _terminated = false;
    
    Event _event_start;

    static void * ThreadMainWrapperEntry(void * This);
    
    void create_pthread();
};

#endif // VIRTUALCBTHREAD_HPP_INCLUDED
