#ifndef CBPOOLWORKER_HPP_INCLUDED
#define CBPOOLWORKER_HPP_INCLUDED

#include "virtualcbthread.hpp"
#include "../task/cbtask.hpp"
#include "../sync/semaphoreposix.hpp"

#include <functional>
#include <memory>

using GetTaskFunction = std::function<CBTask*(void)>;

class CBPoolWorker final: public VirtualCBThread{
public:
    CBPoolWorker(std::shared_ptr<SemaphorePosix> sem_working, 
                 GetTaskFunction gettask = NULL): 
                 _sem_working(sem_working),
                 _gettask(gettask) {};
    ~CBPoolWorker();
    
    CBPoolWorker(const CBPoolWorker &w);
    CBPoolWorker(CBPoolWorker&& w);
    
    CBPoolWorker& operator=(const CBPoolWorker &w);
    
    void resume();
protected:
    void ThreadMainWrapper();
private:
    std::shared_ptr<SemaphorePosix> _sem_working;
    GetTaskFunction _gettask = NULL;
    
    Event _event_resume;
    Event _event_finalized=true;
    
    void _work();
};

#endif // CBPOOLWORKER_HPP_INCLUDED
