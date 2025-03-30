#include <iostream>
#include "dll.hpp"

test_class::test_class()
{
    std::cout << "Hello, world" << std::endl;
}

test_class::~test_class()
{
    std::cout << "Goodbye, world" << std::endl;
}

void* test_class::operator new(size_t sz)
{
    std::cout << "New" << std::endl;
    return ::operator new(sz);
}

void* test_class::operator new[](size_t sz)
{
    std::cout << "New[]" << std::endl;
    return ::operator new[](sz);
}

void test_class::operator delete(void* ptr)
{
    std::cout << "Delete" << std::endl;
    return ::operator delete(ptr);
}

void test_class::operator delete[](void* ptr)
{
    std::cout << "Delete[]" << std::endl;
    return ::operator delete[](ptr);
}

const char* this_is_my_string = "sohfoisdhiohfgioserheioshgioeherihgkserjh";