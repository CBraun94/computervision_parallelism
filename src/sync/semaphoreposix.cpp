#include "semaphoreposix.hpp"

#include <algorithm>

SemaphorePosix::SemaphorePosix()
{
    sem_init(&_sem, 0, 1);
}

SemaphorePosix::~SemaphorePosix()
{
    sem_destroy(&_sem);
}

SemaphorePosix::SemaphorePosix ( SemaphorePosix && s )
{
    std::swap(s._sem, _sem);
}

void SemaphorePosix::Enter()
{
    sem_wait(&_sem);
}

void SemaphorePosix::Leave()
{
    sem_post(&_sem);
}
