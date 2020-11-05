#ifndef CBPOOLWORKER_HPP_INCLUDED
#define CBPOOLWORKER_HPP_INCLUDED

#include "virtualcbthread.hpp"
#include "../task/cbtask.hpp"

#include <functional>
//#include <cbtask.hpp>

using GetTaskFunction = std::function<CBTask*(void)>;

class CBPoolWorker final: public VirtualCBThread{
public:
    CBPoolWorker(GetTaskFunction gettask = NULL): _gettask(gettask) {};
    ~CBPoolWorker();
    
    CBPoolWorker(const CBPoolWorker &w);
    CBPoolWorker(CBPoolWorker&& w);
    
    CBPoolWorker& operator=(const CBPoolWorker &w);
    
    void resume();
protected:
    void ThreadMainWrapper();
private:
    GetTaskFunction _gettask = NULL;
    
    /* consider replacing with non-manuel reset event (not yet implemented) */
    Event _event_resume;
};

#endif // CBPOOLWORKER_HPP_INCLUDED
