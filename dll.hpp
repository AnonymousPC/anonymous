#pragma once

class test_class
{
    test_class();
    ~test_class();

    static void* operator new(size_t);
    static void* operator new[](size_t);
    static void  operator delete(void*);
    static void  operator delete[](void*);

};