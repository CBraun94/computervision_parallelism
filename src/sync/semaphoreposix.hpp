#ifndef SEMAPHOREPOSIX_HPP_INCLUDED
#define SEMAPHOREPOSIX_HPP_INCLUDED

#include <semaphore.h>

class SemaphorePosix{
public:
    SemaphorePosix();
    ~SemaphorePosix();
    
    SemaphorePosix(const SemaphorePosix&) =delete;
    SemaphorePosix(SemaphorePosix&& s);
    
    void Enter();
    void Leave();
private:
    sem_t _sem;
};

#endif // SEMAPHOREPOSIX_HPP_INCLUDED
