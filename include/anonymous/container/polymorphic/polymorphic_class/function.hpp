/// Declaration

template < class type, class device >
class function; // No implemention.

template < class ret_type, class... arg_types, class device >
class function<ret_type(arg_types...),device>
    extends public device::template function<ret_type(arg_types...)>
{
    public: // Typedef
        using return_type   = ret_type;
        template < int index > requires ( ( index >= -sizeof...(arg_types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(arg_types) ) ) using argument_type = index_type_of<index,arg_types...>;
        using device_type   = device;

    public: // Core
        constexpr function ( )                              = default;
        constexpr function ( const function&  )             = default;
        constexpr function (       function&& )             = default;
        constexpr function& operator = ( const function&  ) = default;
        constexpr function& operator = (       function&& ) = default;

    public: // Constructor
        constexpr function ( invocable_r<ret_type,arg_types...> auto );

    public: // Member
        constexpr ret_type              operator() ( arg_types... ) const;
        constexpr bool                  empty      ( )              const;
        constexpr const std::type_info& type       ( )              const;
};

#include "function.cpp"