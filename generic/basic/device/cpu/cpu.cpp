#pragma once

           //  cpu::execution_context_type cpu::execution_context = cpu::execution_context_type(1);
thread_local cpu::random_context_type    cpu::random_context    = cpu::random_context_type   (std::random_device()());

struct deleter
{
    static void operator() ( cpu::execution_context_type* ptr )
    {
        std::cout << "destruct.start" << std::endl; 
        delete ptr;
        std::cout << "destruct.finish" << std::endl;
    }
};

auto my_test = std::unique_ptr<cpu::execution_context_type,deleter>(new cpu::execution_context_type(1));
