#ifndef EXAMPLE_TWO_HPP_INCLUDED
#define EXAMPLE_TWO_HPP_INCLUDED

#include "thread/cbthreadpool.hpp"
#include "task/cbtaskanonymous.hpp"

#include <iostream>

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

void counter(){
    for(auto i = 0; i < 10; i++){
        std::cout << "threadID: "<< gettid() << " counter: " << i << std::endl << std::flush;
    }
}

void example_two(){
	std::cout<<"start of example_two" << std::endl << std::flush;

    CBThreadPool p(4);
    
    sleep(3);
    
    for(auto i=0;i<100;i++){
        std::cout<<"example_two: about to push " << i << std::endl << std::flush;
        p.push_task(new CBTaskAnonymous(counter));
    }
    
    sleep(15);

    std::cout<<"end of example_two" << std::endl << std::flush;
}

#endif // EXAMPLE_TWO_HPP_INCLUDED
