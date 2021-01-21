#ifndef CBTHREAD_HPP_INCLUDED
#define CBTHREAD_HPP_INCLUDED

#include "virtualcbthread.hpp"
#include "../task/cbtask.hpp"

class CBThread: public VirtualCBThread
{
public:
    CBThread(Task task): _task(task) {};
protected:
    void ThreadMainWrapper();
private:
    Task _task;
};

#endif // CBTHREAD_HPP_INCLUDED
