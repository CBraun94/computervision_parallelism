#ifndef EVENTPOSIX_HPP_INCLUDED
#define EVENTPOSIX_HPP_INCLUDED

#include <pthread.h>
#include <atomic>

class EventPosix
{
public:
    EventPosix(bool manualreset = false);

    ~EventPosix();

    void WaitForSignal();

    void Signal();
    void Reset();
private:
    bool signalled = false;
    bool _manualreset = false;
    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    
    void Lock();
    void Unlock();
};

#endif // EVENTPOSIX_HPP_INCLUDED
