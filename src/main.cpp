#include "example_one.hpp"
#include "example_two.hpp"
#include "example_three.hpp"
#include "example_four.hpp"

#include "log.hpp"

#include <iostream>

int main(int argc, char** argv)
{    
    cb::run_example(cb::_ex1, example_one);
    cb::run_example(cb::_ex2, example_two);
    cb::run_example(cb::_ex3, example_three);
    cb::run_example(cb::_ex4, example_four);
    
    return 0;
}
