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

void cpp_print(const char* msg)
{
    std::cout << msg << std::endl;
}

void cpp_print(const std::string& msg)
{
    std::cout << msg << std::endl;
}

cpp_class_base::cpp_class_base()
{
    std::cout << "Construct" << std::endl;
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

const char* my_namespace::c_string = "C string";

std::string my_namespace::cpp_string = "C++ string";
