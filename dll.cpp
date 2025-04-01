#include <iostream>
#include "dll.hpp"

extern "C" void hello_world()
{
    std::cout << "Hello, world" << std::endl;
}

std::string str = "this is a string";
