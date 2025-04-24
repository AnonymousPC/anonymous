/// Declaration

template < class type >
class function; // No implemention.

template < class ret_type, class... arg_types >
class function<ret_type(arg_types...)>
    extends public std::function<ret_type(arg_types...)>
{
    private: // Typedef
        using base = std::function<ret_type(arg_types...)>;

    public: // Core
        constexpr function ( )                              = default;
        constexpr function ( const function&  )             = default;
        constexpr function (       function&& )             = default;
        constexpr function& operator = ( const function&  ) = default;
        constexpr function& operator = (       function&& ) = default;

    public: // Constructor
        constexpr function ( invocable_r<ret_type,arg_types...> auto );

    public: // Member
        constexpr       bool            empty      ( )              const;
        constexpr const std::type_info& type       ( )              const;
        constexpr       ret_type        operator() ( arg_types... ) const;
};

#include "function.cpp"