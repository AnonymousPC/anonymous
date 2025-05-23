template < array_type type >
class mean_squared_error_loss;

template < array_type type >
    requires floating_point<typename type::value_type>
class mean_squared_error_loss<type>
{
    private: // Data
        type outputs = {};
        type labels  = {};

    public: // Typedef
        using  value_type = type::value_type;
        struct loss_concept { };

    public: // Core
        constexpr mean_squared_error_loss ( type, type );

    public: // Conversion
        template < array_type type2 >
        constexpr operator mean_squared_error_loss<type2> ( ) const;

    public: // Interface
        constexpr const type&      from  ( ) const;
        constexpr const type&      to    ( ) const;
        constexpr       type       grad  ( ) const;
        constexpr       value_type value ( ) const;
};

#include "mean_squared_error_loss.cpp"