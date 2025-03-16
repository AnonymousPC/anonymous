#pragma once

extern              exec::static_thread_pool& execution_context;
extern thread_local std::mt19937&             random_context;

#include "global.ipp"
#if dll
    #include "global.cpp"
#endif