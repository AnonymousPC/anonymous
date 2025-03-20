#pragma once

class system_context
{    
    public: // Interface
        constexpr static system_scheduler get_scheduler ( ) noexcept;
};   

#include "system_context.ipp"