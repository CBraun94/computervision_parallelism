#include "cbthreadpool.hpp"

#include <iostream>
#include <functional>

#include "../../log.hpp"

CBThreadPool::~CBThreadPool()
{
    wait();
    //_sem_task.Enter();
    for(auto w = _worker.begin(); w != _worker.end(); w++)
        delete (*w);
    _worker.clear();
    //_sem_task.Leave();
}

void CBThreadPool::push_task (CBTask* t, bool wait)
{
    _sem_task.Enter();
    _tasks.push(t);
    t = NULL;
    resume();
    _sem_task.Leave();
    
    
    
    this->wait();
}

void CBThreadPool::push_tasks(std::vector<CBTask*> v, bool wait)
{
    _sem_task.Enter();
    
    for(auto it = v.begin(); it!=v.end(); it++)
        _tasks.push((*it));
    
    _sem_task.Leave();
    
    resume();
    
    this->wait();
}

void CBThreadPool::wait()
{
    _event_empty.WaitForSignal();
    _sem_working.get()->Enter();
    _sem_working.get()->Leave();
    sleep(1);
}

void CBThreadPool::employ()
{
    cb::log("CBThreadPool", "about to employ ");
    _sem_task.Enter();
    auto f = std::bind(&CBThreadPool::getTask, this);
    for(auto i = 0; i < _capacity; i++){
        _worker.push_back(new CBPoolWorker(_sem_working, f));
        (*_worker.back()).start();
    }
    _sem_task.Leave();
}

void CBThreadPool::resume()
{
    //_sem_task.Enter();
    for(auto it = _worker.begin(); it != _worker.end(); it++){
        (*(*it)).resume();
    }
    //_sem_task.Leave();
}

CBTask* CBThreadPool::getTask()
{
    _sem_task.Enter();

    CBTask* t = NULL;
    if(!_tasks.empty()){
        t = _tasks.front();
        _tasks.pop();
    } else  {
        cb::log("CBThreadPool", "empty");
        _event_empty.Signal();
    }
    
    _sem_task.Leave();
    return t;
}
