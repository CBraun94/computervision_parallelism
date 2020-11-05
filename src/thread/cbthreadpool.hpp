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
    
    void push_task(CBTask* t);
    void push_tasks(std::vector<CBTask*> v);
private:
    size_t _capacity;
    
    std::vector<CBPoolWorker*> _worker;
    std::vector<CBTask*> _tasks;
    
    SemaphorePosix _sem_task;
    
    void employ();
    void resume();
    
    CBTask *getTask();
};

#endif // CBTHREADPOOL_HPP_INCLUDED
