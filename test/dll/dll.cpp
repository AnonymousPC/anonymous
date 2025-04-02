#include <iostream>
#include "dll.hpp"

extern "C" void c_print()
{
    std::cout << "Hello, world, C!" << std::endl;
}

void cpp_print()
{
    std::cout << "Hello, world, C++!" << std::endl;
}

void cpp_class_base::func()
{
    std::cout << "base" << std::endl;
}

void cpp_class_derived::func()
{
    std::cout << "derived" << std::endl;
}

const char* c_string = "C string";

std::string cpp_string = "C++ string";
