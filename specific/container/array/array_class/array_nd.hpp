#pragma once

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
class array<type,dim,device>
    extends public  device::template vector<type>,
            private detail::array_upper<type,1,  device>, // Make abi compatible with array<type,1,device>, required from flatten().
            private detail::array_info <type,dim,device>,
            private detail::array_upper<type,dim,device>,
            private detail::array_lower<type,dim,device>,
            public  array_algo<array<type,dim,device>,type,dim,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and ( movable<type> or string_type<type> ) );
        static_assert ( not ( same_as<type,bool> and same_as<device,cpu> ) ); // std::vector<bool>

    private: // Base
        using base   = device::template vector<type>;
        using info   = detail::array_info <type,dim,device>;
        using upper  = detail::array_upper<type,dim,device>;
        using lower  = detail::array_lower<type,dim,device>;

    public: // Typedef
        using  value_type      = device::template value_type      <type>;
        using  reference       = device::template reference       <type>;
        using  const_reference = device::template const_reference <type>;
        using  pointer         = device::template pointer         <type>;
        using  const_pointer   = device::template const_pointer   <type>;
        using  iterator        = detail::array_line_iterator      <type,dim,device>;
        using  const_iterator  = detail::array_line_const_iterator<type,dim,device>;
        using  device_type     = device;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )             requires copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  ) requires copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( int_type auto... args )                             requires                    ( sizeof...(args)     == dim );
        constexpr          array ( auto... args )                                      requires copyable<type> and ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_type     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                      requires                    ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_func     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                      requires                    ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_func_ints<type,decltype(args)...>;
        constexpr          array ( int,  function_type<array<type,dim-1>()>    auto );
        constexpr          array ( int,  function_type<array<type,dim-1>(int)> auto );
        constexpr          array ( std::initializer_list<array<type,dim-1,device>> )   requires copyable<type>;

    public: // Conversion (type)
        template < class type2 > constexpr          array ( const array<type2,dim,device>& ) requires convertible_to<type2,type>     but ( not same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array<type2,dim,device>& ) requires constructible_from<type,type2> but ( not convertible_to<type2,type> );

    public: // Conversion (device)
        template < class device2 > constexpr explicit array ( const array<type,dim,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>;

    public: // Member
        constexpr static int                       dimension     ( );
        constexpr        int                       size          ( )     const;
        constexpr        int                       capacity      ( )     const = delete;
        constexpr        static_array<int,dim>     shape         ( )     const;
        constexpr        int                       row           ( )     const requires ( dim == 2 );
        constexpr        int                       column        ( )     const requires ( dim == 2 );
        constexpr        bool                      empty         ( )     const;
        constexpr        pointer                   data          ( );
        constexpr        const_pointer             data          ( )     const;
        constexpr        iterator                  begin         ( );
        constexpr        const_iterator            begin         ( )     const;
        constexpr        iterator                  end           ( );
        constexpr        const_iterator            end           ( )     const;
        constexpr        array<type,dim-1,device>& operator []   ( int );
        constexpr const  array<type,dim-1,device>& operator []   ( int ) const;

    public: // Member
                                  constexpr array& clear  ( );
                                  constexpr array& resize ( int_type auto... args )         requires ( sizeof...(args) == dim );
                                  constexpr array& resize ( static_array<int,dim> );
        template < int axis = 1 > constexpr array& push   (      array<type,dim-1,device> ) requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) );
        template < int axis = 1 > constexpr array& pop    ( int = -1 )                      requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) );
        template < int axis = 1 > constexpr array& insert ( int, array<type,dim-1,device> ) requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) );
        template < int axis = 1 > constexpr array& erase  ( int, int )                      requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) );

    public: // View
        constexpr       array<type,1,device>&   flatten   ( );
        constexpr const array<type,1,device>&   flatten   ( ) const;
        constexpr       array<type,dim,device>& transpose ( );
        constexpr const array<type,dim,device>& transpose ( ) const;

    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const;

    private: // Detail
                              constexpr       int                                              get_size_top  ( )                  const;
        template < int axis > constexpr       int                                              get_size_axis ( )                  const;
        template < int dim2 > constexpr       std::span<detail::array_upper<type,dim2,device>> get_rows      ( int_type auto... );
        template < int dim2 > constexpr const std::span<detail::array_upper<type,dim2,device>> get_rows      ( int_type auto... ) const;
        template < int dim2 > constexpr       std::span<detail::array_upper<type,dim2,device>> get_columns   ( int_type auto... );
        template < int dim2 > constexpr const std::span<detail::array_upper<type,dim2,device>> get_columns   ( int_type auto... ) const;
                              constexpr       reference                                        get_value     ( int_type auto... );
                              constexpr       const_reference                                  get_value     ( int_type auto... ) const;
                              constexpr       pointer                                          get_pointer   ( int_type auto... );
                              constexpr       const_pointer                                    get_pointer   ( int_type auto... ) const;

    private: // Friend
        template < class type2, int dim2, class device2 > friend class array;
        template < class type2, int dim2, class device2 > friend class detail::array_lower;
        template < class type2, int dim2, class device2 > friend class detail::array_upper;
        template < class type2, int dim2, class device2 > friend class detail::tuple_upper;
        template < class type2, int dim2, class device2 > friend class detail::array_line_iterator;
        template < class type2, int dim2, class device2 > friend class detail::array_line_const_iterator;
};