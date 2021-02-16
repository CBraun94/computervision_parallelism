#ifndef CBCTRL_HPP_INCLUDED
#define CBCTRL_HPP_INCLUDED

#include "../thread/cbthreadpool.hpp"
#include "../task/cbtask.hpp"

enum parallel_mode {pmSingle, pmThreaded};

class cbctrl{
public:
    cbctrl(size_t capacity=4): _tp(capacity), _mode(pmThreaded) {};
    
    void push_task(CBTask* t, bool wait = true);
    void push_tasks(std::vector<CBTask*> v, bool wait = true);
private:
    CBThreadPool _tp;
    
    parallel_mode _mode;
};

#endif // CBCTRL_HPP_INCLUDED
