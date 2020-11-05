#include "cbthreadpool.hpp"

#include <iostream>
#include <functional>

CBThreadPool::CBThreadPool ( size_t capacity )
{
    _capacity = capacity;
    employ();
}

CBThreadPool::~CBThreadPool()
{
    _sem_task.Enter();
    for(auto w = _worker.begin(); w != _worker.end(); w++)
        delete (*w);
    _worker.clear();
    _sem_task.Leave();
}

void CBThreadPool::push_task ( CBTask* t )
{
    _sem_task.Enter();
    _tasks.push_back(t);
    _sem_task.Leave();
    
    resume();
}

void CBThreadPool::employ()
{
    std::cout<<"CBThreadPool about to employ " << std::endl << std::flush;
    _sem_task.Enter();
    auto f = std::bind(&CBThreadPool::getTask, this);
    for(auto i = 0; i < _capacity; i++){
        _worker.push_back(new CBPoolWorker(f));
        (*_worker.back()).start();
    }
    _sem_task.Leave();
}

void CBThreadPool::resume()
{
    _sem_task.Enter();
    for(auto it = _worker.begin(); it != _worker.end(); it++){
        (*(*it)).resume();
    }
    _sem_task.Leave();
}

CBTask* CBThreadPool::getTask()
{
    _sem_task.Enter();

    CBTask* t = NULL;
    if(!_tasks.empty()){
        t = std::move(_tasks.front());
        _tasks.erase(_tasks.begin());
    } else  {
        /* consider replacing return value CBTask */
    }
    _sem_task.Leave();
    return t;
}
