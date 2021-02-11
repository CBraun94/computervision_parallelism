#ifndef EXAMPLE_MAIN_HPP_INCLUDED
#define EXAMPLE_MAIN_HPP_INCLUDED

#include "log.hpp"

#include "example_one.hpp"
#include "example_two.hpp"
#include "example_three.hpp"
#include "example_four.hpp"

inline void example_main(){
    cb::run_example(cb::_ex1, example_one);
    cb::run_example(cb::_ex2, example_two);
    cb::run_example(cb::_ex3, example_three);
    cb::run_example(cb::_ex4, example_four);
}
#endif // EXAMPLE_MAIN_HPP_INCLUDED
