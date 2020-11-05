#ifndef CBWORKER_HPP_INCLUDED
#define CBWORKER_HPP_INCLUDED

#include "virtualcbthread.hpp"

enum ThreadMode{single, task, thread};

class CBWorker: private VirtualCBThread
{
public:
    CBWorker(ThreadMode mode): _mode(mode) {};
private:
    ThreadMode _mode;
};

#endif // CBWORKER_HPP_INCLUDED
