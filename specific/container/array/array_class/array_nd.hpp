#pragma once
#define template_int_axis template < int axis = 1 > requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )

template < class type, int dim, class device >
    requires ( dim >= 2 )
class array
    extends public  device::template vector<type>,
            private detail::upper_array<type,1,  device>, // Make abi compatible with array<type,1>, required from as_flat().
            private detail::array_info <     dim,device>,
            private detail::upper_array<type,dim,device>,
            private detail::lower_array<type,dim,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( not same_as<type,bool> );

    private: // Base
        using vector = device::template vector<type>;
        using flat   = detail::upper_array<type,1,  device>;
        using info   = detail::array_info <     dim,device>;
        using upper  = detail::upper_array<type,dim,device>;
        using lower  = detail::lower_array<type,dim,device>;

    public: // Typedef
        using  value_type      = type;
        using  reference       = base::reference;
        using  const_reference = base::const_reference;
        using  pointer         = base::pointer;
        using  const_pointer   = base::const_pointer;
        class  iterator;
        class  const_iterator;
        using  device_type     = device;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )                                           requires copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  )                               requires copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( int_type auto... args )                                   requires ( sizeof...(args)     == dim );
        constexpr          array ( auto... args )                                            requires ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_type     <type,decltype(args)...> and copyable<type>;
        constexpr          array ( auto... args )                                            requires ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_func     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                            requires ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_func_ints<type,decltype(args)...>;
        constexpr          array ( int,  function_type<array<type,dim-1>()>    auto );
        constexpr          array ( int,  function_type<array<type,dim-1>(int)> auto );
        constexpr          array ( const std::initializer_list<array<type,dim-1>>& );

    public: // Conversion (type)
        template < class type2 > constexpr          array ( const array<type2,dim,device>& ) requires convertible_to<type2,type>     but ( not same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array<type2,dim,device>& ) requires constructible_from<type,type2> but ( not convertible_to<type2,type> );

    public: // Member
        constexpr static int                       dimension     ( );
        constexpr        int                       size          ( )     const;
        constexpr        array        <int>        shape         ( )     const;
        constexpr        inplace_array<int,dim>    inplace_shape ( )     const;
        constexpr        static_array <int,dim>    static_shape  ( )     const;
        constexpr        int                       row           ( )     const;
        constexpr        int                       column        ( )     const requires ( dim == 2 );
        constexpr        bool                      empty         ( )     const;
        constexpr        const_pointer             data          ( )     const;
        constexpr        iterator                  begin         ( );
        constexpr        const_iterator            begin         ( )     const;
        constexpr        iterator                  end           ( );
        constexpr        const_iterator            end           ( )     const;
        constexpr        array<type,dim-1,device>& operator []   ( int );
        constexpr const  array<type,dim-1,device>& operator []   ( int ) const;

    public: // Member
        template_int_axis constexpr array& resize ( int );
                          constexpr array& resize ( int_type auto... args ) requires ( sizeof...(args) == dim );
                          constexpr array& resize ( const array<int,1>& );
        template_int_axis constexpr array& clear  ( );
        template_int_axis constexpr array& push   (      const array<type,dim-1,device>& );
        template_int_axis constexpr array& pop    ( int );
        template_int_axis constexpr array& insert ( int, const array<type,dim-1,device>& );
        template_int_axis constexpr array& erase  ( int, int );

    public: // View
        constexpr       array<type,1,device>&   as_flat      ( );
        constexpr const array<type,1,device>&   as_flat      ( ) const;
        constexpr       array<type,dim,device>& as_transpose ( );
        constexpr const array<type,dim,device>& as_transpose ( ) const;

    public: // Memory
        constexpr bool independent ( ) const;

    private: // Detail
        constexpr reference       locate ( int_type auto... args )       requires ( sizeof...(args) == dim );
        constexpr const_reference locate ( int_type auto... args ) const requires ( sizeof...(args) == dim );
}

#include "array_nd.ipp"
#undef template_int_axis