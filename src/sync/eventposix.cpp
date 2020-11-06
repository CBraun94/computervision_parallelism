#include "eventposix.hpp"

EventPosix::EventPosix()
{
    signalled = false;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

EventPosix::~EventPosix()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void EventPosix::WaitForSignal()
{
    Lock();
    while (!signalled)
    {
        pthread_cond_wait(&cond, &mutex);
    }
    signalled = false;
    Unlock();
}

void EventPosix::Signal()
{
    Lock();
    signalled = true;
    Unlock();
    pthread_cond_signal(&cond);
}

void EventPosix::Reset()
{
    Lock();
    signalled = false;
    Unlock();
}

void EventPosix::Lock()
{
    pthread_mutex_lock(&mutex);
}

void EventPosix::Unlock()
{
    pthread_mutex_unlock(&mutex);
}
