#ifndef CBTASK_HPP_INCLUDED
#define CBTASK_HPP_INCLUDED

#include <functional> /* std::bind */
#include <iostream>

using Task = std::function<void(void)>;

class CBTask
{
public:
    CBTask(Task callback = 0): callback(callback) {};
    virtual ~CBTask() {};
    
    CBTask(const CBTask& t);
    CBTask(CBTask&& t);
    
    CBTask& operator=(const CBTask& t);
    
    void operator()() const;
protected:
    /* can't bet pure virtual as it needs to be callable */
    virtual void Execute() const;
private:
    Task callback;
};

#endif // CBTASK_HPP_INCLUDED
