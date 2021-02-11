#ifndef EXAMPLE_TWO_HPP_INCLUDED
#define EXAMPLE_TWO_HPP_INCLUDED

#include "../cbparallel/thread/cbthreadpool.hpp"
#include "../cbparallel/task/cbtaskanonymous.hpp"
#include "../cbparallel/task/cbtaskfor.hpp"

#include "log.hpp"

#include <iostream>

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

constexpr auto task_count = 5;
constexpr auto loop_end = 1000;
constexpr auto minChunkSize = 10;

void counter_for(int i){
    std::cout << "threadID: "<< gettid() << " counter: " << i << std::endl << std::flush;
}

void counter(){
    for(auto i = 0; i < loop_end; i++){
        counter_for(i);
    }
}

void example_two_anonymous(){
    CBThreadPool p(4);
    
    for(auto i=0;i<task_count;i++){
        std::cout<<"example_two: about to push " << i << std::endl << std::flush;
        p.push_task(new CBTaskAnonymous(counter));
    }
}

void example_two_for(){
    CBThreadPool p(4);
    
    for(auto i=0;i<task_count;i++){
        std::cout<<"example_two: about to push " << i << std::endl << std::flush;
        p.push_task(new CBTaskFor(counter_for, 0, loop_end, 1));
    }
}

void example_two_for_sliced(){
    CBThreadPool p(4);
    
    for(auto i=0;i<task_count;i++){
        std::cout<<"example_two: about to push " << i << std::endl << std::flush;
        p.push_tasks(CBTaskFor::slice(counter_for, 0, loop_end, 1, NULL, minChunkSize));
    }
}

void example_two(){
    example_two_anonymous();
    example_two_for();
    example_two_for_sliced();
}

#endif // EXAMPLE_TWO_HPP_INCLUDED
