#include "example_one.hpp"
#include "example_two.hpp"
#include "example_three.hpp"
#include "example_four.hpp"

#include <iostream>

int main(int argc, char** argv)
{    
	std::cout<<"start of main" << std::endl << std::flush;

    //example_one();
    //example_two();
    //example_three();
    example_four();

	std::cout<<"end of main" << std::endl << std::flush;
    
    return 0;
}
