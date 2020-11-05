#ifndef EXAMPLE_TWO_HPP_INCLUDED
#define EXAMPLE_TWO_HPP_INCLUDED

#include "thread/cbthreadpool.hpp"
#include "task/cbtaskanonymous.hpp"
#include "task/cbtaskfor.hpp"

#include <iostream>

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

constexpr auto task_count = 5;
constexpr auto after_example_wait = 3;
constexpr auto loop_end = 100;

void counter_for(int i){
    std::cout << "threadID: "<< gettid() << " counter: " << i << std::endl << std::flush;
}

void counter(){
    for(auto i = 0; i < loop_end; i++){
        counter_for(i);
    }
}

void example_two_anonymous(){
    std::cout<<"start of example_two_anonymous" << std::endl << std::flush;
    CBThreadPool p(4);
    
    sleep(3);
    
    for(auto i=0;i<task_count;i++){
        std::cout<<"example_two: about to push " << i << std::endl << std::flush;
        p.push_task(new CBTaskAnonymous(counter));
    }
    
    sleep(after_example_wait);
    std::cout<<"end of example_two_anonymous" << std::endl << std::flush;
}

void example_two_for(){
    std::cout<<"start of example_two_for" << std::endl << std::flush;
    CBThreadPool p(4);
    
    sleep(3);
    
    for(auto i=0;i<task_count;i++){
        std::cout<<"example_two: about to push " << i << std::endl << std::flush;
        p.push_task(new CBTaskFor(counter_for, 0, loop_end, 1));
    }
    
    sleep(after_example_wait);   
    std::cout<<"end of example_two_for" << std::endl << std::flush;
}

void example_two(){
	std::cout<<"start of example_two" << std::endl << std::flush;

    example_two_anonymous();
    example_two_for();

    std::cout<<"end of example_two" << std::endl << std::flush;
}

#endif // EXAMPLE_TWO_HPP_INCLUDED
