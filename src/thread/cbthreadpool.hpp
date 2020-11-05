#ifndef CBTHREADPOOL_HPP_INCLUDED
#define CBTHREADPOOL_HPP_INCLUDED

#include "cbpoolworker.hpp"
#include "../task/cbtask.hpp"
#include "../task/cbtaskanonymous.hpp"
#include "../sync/semaphoreposix.hpp"

#include <vector>

class CBThreadPool{
public:
    CBThreadPool(size_t capacity);
    ~CBThreadPool();
    
    void push_task(CBTaskAnonymous* t);
private:
    size_t _capacity;
    
    std::vector<CBPoolWorker*> _worker;
    std::vector<CBTaskAnonymous*> _tasks;
    
    SemaphorePosix _sem_task;
    
    void employ();
    void resume();
    
    CBTask *getTask();
};

#endif // CBTHREADPOOL_HPP_INCLUDED
