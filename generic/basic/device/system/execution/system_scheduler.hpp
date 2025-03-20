#pragma once

class system_scheduler
{
    private: // Typedef
        class sender;

    public: // Interface
        constexpr static sender schedule ( ) noexcept;  

    public: // Operator
        friend constexpr bool operator == ( const system_scheduler&, const system_scheduler& ) = default;
};

#include "system_scheduler.ipp"
