#include "cbthread.hpp"

void CBThread::ThreadMainWrapper()
{
    if(_task != NULL)
        _task();
}
