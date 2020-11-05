#ifndef CBTASKANONYMOUS_HPP_INCLUDED
#define CBTASKANONYMOUS_HPP_INCLUDED

#include "cbtask.hpp"

class CBTaskAnonymous final: public CBTask
{
public:
    CBTaskAnonymous(Task task = NULL, Task callback = NULL): CBTask{callback}, task{task} {};
    
    CBTaskAnonymous(const CBTaskAnonymous& t);
    CBTaskAnonymous(CBTaskAnonymous&& t);
    
    CBTaskAnonymous& operator=(const CBTaskAnonymous& t);
protected:    
    void Execute() const;
private:
    Task task;
};

#endif // CBTASKANONYMOUS_HPP_INCLUDED
