#pragma once

constexpr int max_dim = 2;

template < class type, class device >
class array<type,max_dim,device>
    extends public device::template vector<type>,
            public detail::array_upper<type,1,      device>, // Make abi compatible with array<type,1>, required from as_flat().
            public detail::array_info <type,max_dim,device>,
            public detail::array_lower<type,max_dim,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( not same_as<type,bool> );

    private: // Base
        using base   = device::template vector<type>;
        using flat   = detail::array_upper<type,1,      device>;
        using info   = detail::array_info <type,max_dim,device>;
        using lower  = detail::array_lower<type,max_dim,device>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = std::vector<detail::array_upper<type,max_dim-1,device>>::iterator;
        using  const_iterator  = std::vector<detail::array_upper<type,max_dim-1,device>>::const_iterator;
        using  device_type     = device;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )             requires copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  ) requires copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( int_type auto... args )                                 requires                    ( sizeof...(args)     == max_dim );
        constexpr          array ( auto... args )                                          requires copyable<type> and ( sizeof...(args) - 1 == max_dim ) and detail::ints_until_last_type     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                          requires                    ( sizeof...(args) - 1 == max_dim ) and detail::ints_until_last_func     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                          requires                    ( sizeof...(args) - 1 == max_dim ) and detail::ints_until_last_func_ints<type,decltype(args)...>;
        constexpr          array ( int,  function_type<array<type,max_dim-1>()>    auto );
        constexpr          array ( int,  function_type<array<type,max_dim-1>(int)> auto );
        constexpr          array ( std::initializer_list<array<type,max_dim-1,device>> )   requires copyable<type>;

    public: // Conversion (type)
        template < class type2 > constexpr          array ( const array<type2,max_dim,device>& ) requires convertible_to<type2,type>     but ( not same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array<type2,max_dim,device>& ) requires constructible_from<type,type2> but ( not convertible_to<type2,type> );

    public: // Conversion (device)
        template < class device2 > constexpr array ( const array<type,max_dim,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>;

    public: // Member
        constexpr static int                           dimension     ( );
        constexpr        int                           size          ( )     const;
        constexpr        int                           capacity      ( )     const = delete;
        constexpr        array<int>                    shape         ( )     const;
        constexpr        inplace_array<int,max_dim>    inplace_shape ( )     const;
        constexpr        static_array<int,max_dim>     static_shape  ( )     const;
        constexpr        int                           row           ( )     const;
        constexpr        int                           column        ( )     const requires ( max_dim == 2 );
        constexpr        bool                          empty         ( )     const;
        constexpr        pointer                       data          ( );
        constexpr        const_pointer                 data          ( )     const;
        constexpr        iterator                      begin         ( );
        constexpr        const_iterator                begin         ( )     const;
        constexpr        iterator                      end           ( );
        constexpr        const_iterator                end           ( )     const;
        constexpr        array<type,max_dim-1,device>& operator []   ( int );
        constexpr const  array<type,max_dim-1,device>& operator []   ( int ) const;

    public: // Member
                                  constexpr array& clear  ( );
        template < int axis = 1 > constexpr array& resize ( int )                               requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) );
                                  constexpr array& resize ( int_type auto... args )             requires ( sizeof...(args) == max_dim );
                                  constexpr array& resize ( const array<int>& );
        template < int axis = 1 > constexpr array& push   (      array<type,max_dim-1,device> ) requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) );
        template < int axis = 1 > constexpr array& pop    ( int = -1 )                          requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) );
        template < int axis = 1 > constexpr array& insert ( int, array<type,max_dim-1,device> ) requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) );
        template < int axis = 1 > constexpr array& erase  ( int, int )                          requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) );

    public: // View
        constexpr       array<type,1,device>&       as_flat      ( );
        constexpr const array<type,1,device>&       as_flat      ( ) const;
        constexpr       array<type,max_dim,device>& as_transpose ( );
        constexpr const array<type,max_dim,device>& as_transpose ( ) const;

    public: // Memory
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );

    public: // View
        template < int dim2 > constexpr       std::vector<detail::array_upper<type,dim2,device>>& rows     ( );
        template < int dim2 > constexpr const std::vector<detail::array_upper<type,dim2,device>>& rows     ( ) const;
        template < int dim2 > constexpr       std::vector<detail::array_upper<type,dim2,device>>& columns  ( );
        template < int dim2 > constexpr const std::vector<detail::array_upper<type,dim2,device>>& columns  ( ) const;
                              constexpr       int                                                 top_size ( )                       const;
                              constexpr       reference                                           at       ( int_type auto... args )       requires ( sizeof...(args) == max_dim );
                              constexpr       const_reference                                     at       ( int_type auto... args ) const requires ( sizeof...(args) == max_dim );
};

template < class type, int dim, class device >
    requires ( dim >= 2 ) and ( dim > max_dim )
class array<type,dim,device>
{
    static_assert(false, "dim > max_dim");
};

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */