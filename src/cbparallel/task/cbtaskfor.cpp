#include "cbtaskfor.hpp"

#include <iostream>

CBTaskFor::CBTaskFor ( const CBTaskFor& t )
{
    _task = t._task;
}

CBTaskFor::CBTaskFor ( CBTaskFor && t)
{
    _task = std::move(t._task);
}

CBTaskFor & CBTaskFor::operator= ( const CBTaskFor& t )
{
    _task = t._task;
    return *this;
}

std::vector<CBTask*> CBTaskFor::slice(TaskFor task, 
                                           int begin, int end, int increment, 
                                           Task callback, 
                                           int minChunkSize, 
                                           int threadCount)
{
    std::vector<CBTask*> v;
    
    auto range = end-begin;
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

void CBTaskFor::Execute() const
{
    std::cout << "CBTaskFor Execute with: begin-"<< _begin << " end-" << _end << "increment-" << _increment << std::endl << std::flush;
    if(_task != NULL)
        for(auto i = _begin; i < _end; i+=_increment) 
            _task(i);
}
