#include "semaphoreposix.hpp"

#include <algorithm>

#include <iostream>

SemaphorePosix::SemaphorePosix(unsigned int value)
{
    auto i = sem_init(&_sem, 0, value);
    if(i !=0)
        std::cout<< "SemaphorePosix: sem_init ret was: " << i << std::endl << std::flush;
}

SemaphorePosix::~SemaphorePosix()
{
    sem_destroy(&_sem);
}

SemaphorePosix::SemaphorePosix ( SemaphorePosix && s )
{
    _sem=s._sem;
}

void SemaphorePosix::Enter()
{
    auto i = sem_wait(&_sem);
    if(i !=0)
        std::cout<< "SemaphorePosix: sem_wait ret was: " << i << std::endl << std::flush;
}

void SemaphorePosix::Leave()
{
    sem_post(&_sem);
}

int SemaphorePosix::value()
{
    int r;
    sem_getvalue(&_sem, &r);
    return r;
}
