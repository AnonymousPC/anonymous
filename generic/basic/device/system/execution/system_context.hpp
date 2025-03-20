#pragma once

class system_context
{   
    public: // Interface
        constexpr static std::execution::scheduler auto get_scheduler ( ) noexcept;
};   

#include "system_context.ipp"