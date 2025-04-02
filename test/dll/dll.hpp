#pragma once
#include <string>

extern "C" void c_print();

void cpp_print();

struct cpp_class_base
{
    virtual void func();
};  

struct cpp_class_derived
    : cpp_class_base
{
    virtual void func();
}; 

extern const char* c_string;
extern std::string cpp_string;