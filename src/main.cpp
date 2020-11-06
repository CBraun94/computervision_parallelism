#include "example_one.hpp"
#include "example_two.hpp"
#include "example_three.hpp"

#include <iostream>

int main(int argc, char** argv)
{    
	std::cout<<"start of main" << std::endl << std::flush;

    //example_one();
    //example_two();
    example_three();

	std::cout<<"end of main" << std::endl << std::flush;
    
    return 0;
}
