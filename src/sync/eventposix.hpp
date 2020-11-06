#ifndef EVENTPOSIX_HPP_INCLUDED
#define EVENTPOSIX_HPP_INCLUDED

#include <pthread.h>
#include <atomic>

class EventPosix
{
public:
    EventPosix();

    ~EventPosix();

    void WaitForSignal();

    void Signal();
private:
    bool signalled = false;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    
    void Lock();
    void Unlock();
};

#endif // EVENTPOSIX_HPP_INCLUDED
