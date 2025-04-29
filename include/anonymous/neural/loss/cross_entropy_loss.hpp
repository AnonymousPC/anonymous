template < array_type type >
class cross_entropy_loss;

template < array_type type >
    requires float_type<typename type::value_type>
class cross_entropy_loss<type>
{
    private: // Data
        type outputs = {};
        type labels  = {};

    public: // Typedef
        using  value_type = type::value_type;
        struct loss_concept { };

    public: // Core
        constexpr cross_entropy_loss ( type, type );

    public: // Conversion
        template < array_type type2 >
        constexpr operator cross_entropy_loss<type2> ( ) const;

    public: // Interface
        constexpr const type&      from  ( ) const;
        constexpr const type&      to    ( ) const;
        constexpr       type       grad  ( ) const;
        constexpr       value_type value ( ) const;
};

#include "cross_entropy_loss.cpp"