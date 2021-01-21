#ifndef CBTASKFOR_HPP_INCLUDED
#define CBTASKFOR_HPP_INCLUDED

#include "cbtask.hpp"

#include <functional> /* std::bind */
#include <iostream>
#include <vector>

using TaskFor = std::function<void(int)>;

class CBTaskFor final: public CBTask{
public:
    CBTaskFor(TaskFor task = NULL, 
              int begin=0, int end=0, int increment=1, 
              Task callback = NULL): 
              CBTask{callback}, 
              _begin(begin), _end(end), _increment(increment),
              _task{task} {};
    
    CBTaskFor(const CBTaskFor& t);
    CBTaskFor(CBTaskFor&& t);
    
    CBTaskFor& operator=(const CBTaskFor& t);
    
    static std::vector<CBTask*> slice(TaskFor task = NULL,
                                         int begin=0, int end=0, int increment=1,
                                         Task callback = NULL,
                                         int minChunkSize = 0,
                                         int threadCount = 1);
    
    /* WARNING! NOT YET FINISHED! */
    template <
    typename Iterator,
    typename Compare=std::less<typename std::iterator_traits<Iterator>::value_type>
    >
    static std::vector<CBTask*> slice(TaskFor task,
                                      Iterator begin, Iterator end, int increment,
                                      Task callback = NULL,
                                      int minChunkSize = 0,
                                      int threadCount = 1)
    {
        /* WARNING! NOT YET FINISHED! */
        std::vector<CBTask*> v;
    
        auto range = std::distance(begin, end);
        int chunkCount;
    
        if(minChunkSize>0){
            chunkCount = range/minChunkSize;
        }else{
            chunkCount = range/threadCount;
        }
    
        if(chunkCount<1)
            chunkCount=1;
    
        auto chunkSize = range/chunkCount;
        if (chunkSize<1)
            chunkSize=1;
    
        std::vector<int> index;
        index.push_back(begin);
        for(auto i=1;i<chunkCount;i++)
            index.push_back(begin+i*chunkSize);
        index.push_back(end);
    
        for(auto it=index.begin();it!=std::prev(index.end());it++)
            v.push_back(new CBTaskFor(task, (*it), (*std::next(it,1)), increment, callback));
    
        return v;
    }
                                      
protected:    
    void Execute() const;
private:
    int _begin;
    int _end;
    int _increment;
    
    TaskFor _task;
};

#endif // CBTASKFOR_HPP_INCLUDED
