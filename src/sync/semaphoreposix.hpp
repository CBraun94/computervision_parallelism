#ifndef SEMAPHOREPOSIX_HPP_INCLUDED
#define SEMAPHOREPOSIX_HPP_INCLUDED

#include <semaphore.h>

class SemaphorePosix{
public:
    SemaphorePosix(unsigned int value = 1);
    ~SemaphorePosix();
    
    SemaphorePosix(const SemaphorePosix&) =delete;
    SemaphorePosix(SemaphorePosix&& s);
    
    void Enter();
    void Leave();
    
    int value();
private:
    sem_t _sem;
};

#endif // SEMAPHOREPOSIX_HPP_INCLUDED
