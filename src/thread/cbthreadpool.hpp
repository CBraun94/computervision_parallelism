#ifndef CBTHREADPOOL_HPP_INCLUDED
#define CBTHREADPOOL_HPP_INCLUDED

#include "cbpoolworker.hpp"
#include "../task/cbtask.hpp"
#include "../task/cbtaskanonymous.hpp"
#include "../sync/semaphoreposix.hpp"
#include "../sync/eventposix.hpp"

#include <vector>
#include <memory>

class CBThreadPool{
public:
    CBThreadPool(size_t capacity): _capacity(capacity){
        _sem_working = std::make_shared<SemaphorePosix>(capacity);
        employ();
    };  
    ~CBThreadPool();
    
    void push_task(CBTask* t);
    void push_tasks(std::vector<CBTask*> v);
    
    void wait();
private:
    size_t _capacity;
    
    std::vector<CBPoolWorker*> _worker;
    std::vector<CBTask*> _tasks;
    
    SemaphorePosix _sem_task;
    std::shared_ptr<SemaphorePosix> _sem_working;
    
    EventPosix _event_empty;
    
    void employ();
    void resume();
    
    CBTask *getTask();
};

#endif // CBTHREADPOOL_HPP_INCLUDED
