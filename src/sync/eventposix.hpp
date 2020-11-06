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
    
    void Reset();
private:
    std::atomic<bool> signalled;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    
    void Lock();
    void Unlock();
};

#endif // EVENTPOSIX_HPP_INCLUDED
