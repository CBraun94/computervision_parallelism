#ifndef CBTASKFOR_HPP_INCLUDED
#define CBTASKFOR_HPP_INCLUDED

#include "cbtask.hpp"

#include <functional> /* std::bind */
#include <iostream>

using TaskFor = std::function<void(int)>;

class CBTaskFor final: public CBTask{
public:
    CBTaskFor(TaskFor task = NULL, 
              int begin=0, int end=0, int increment=0, 
              Task callback = NULL): 
              CBTask{callback}, 
              _begin(begin), _end(end), _increment(increment),
              _task{task} {};
    
    CBTaskFor(const CBTaskFor& t);
    CBTaskFor(CBTaskFor&& t);
    
    CBTaskFor& operator=(const CBTaskFor& t);
protected:    
    void Execute() const;
private:
    int _begin;
    int _end;
    int _increment;
    
    TaskFor _task;
};

#endif // CBTASKFOR_HPP_INCLUDED
