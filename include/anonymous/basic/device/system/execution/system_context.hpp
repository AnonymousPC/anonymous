class system_context
{   
    private: // Core
        constexpr system_context ( ) = default;
        friend class system;

    public: // Interface
        constexpr static std::execution::scheduler auto get_scheduler ( ) noexcept;
};   

#include "system_context.cpp"