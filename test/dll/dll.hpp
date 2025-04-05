#pragma once
#include <string>

extern "C" void c_print();

void cpp_print();
void cpp_print(const char*);
void cpp_print(const std::string&);

struct cpp_class_base
{
    cpp_class_base();
    void func();
};  

struct cpp_class_derived
    : cpp_class_base
{
    void func();
}; 

extern const char* c_string;
extern std::string cpp_string;

namespace my_namespace
{
    extern const char* c_string;
    extern std::string cpp_string;
    
} // namespace my_namespace
