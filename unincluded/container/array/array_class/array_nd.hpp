#include "detail/ints_until.cpp"

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
class array<type,dim,device>
    extends private device::template vector<type>,        // (Static  extends) Data storage.
            private detail::array_upper<type,1,  device>, // (Static  extends) Make abi compatible with array<type,1,device>, required from flatten().
            private detail::array_info <type,dim,device>, // (Dyanmic extends) Manages the shape info of array.
            private detail::array_upper<type,dim,device>, // (Dyanmic extends) Manages the upper-dimension host arrays. Only transposable.
            private detail::array_lower<type,dim,device>  // (Dyanmic extends) Manages the lower-dimension sub  arrays.
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> );

    private: // Base
        using base   = device::template vector<type>;
        using info   = detail::array_info <type,dim,device>;
        using upper  = detail::array_upper<type,dim,device>;
        using lower  = detail::array_lower<type,dim,device>;

    public: // Typedef
        using value_type      = device::template value_type        <type>;
        using reference       = device::template reference         <type>;
        using const_reference = device::template const_reference   <type>;
        using pointer         = device::template pointer           <type>;
        using const_pointer   = device::template const_pointer     <type>;
        using iterator        = cpu   ::template transform_iterator<      detail::array_upper<type,dim-1,device>*,detail::transform_to_array<type,dim-1,device>>;
        using const_iterator  = cpu   ::template transform_iterator<const detail::array_upper<type,dim-1,device>*,detail::transform_to_array<type,dim-1,device>>;
        using device_type     = device;

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )             requires copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  ) requires copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( integral auto... args )                           requires                    ( sizeof...(args)     == dim );
        constexpr          array ( auto... args )                                    requires copyable<type> and ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_type     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                    requires                    ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_generator<type,decltype(args)...>;
        constexpr          array ( auto... args )                                    requires                    ( sizeof...(args) - 1 == dim ) and detail::ints_until_last_function <type,decltype(args)...>;
        constexpr          array ( std::initializer_list<array<type,dim-1,device>> ) requires copyable<type>;

    public: // Conversion
        template < class type2, class device2 > constexpr          array ( const array<type2,dim,device2>& ) requires convertible_to  <type2,type>;
        template < class type2, class device2 > constexpr explicit array ( const array<type2,dim,device2>& ) requires constructible_to<type2,type>;

    public: // Member
        constexpr static int                       dimension     ( );
        constexpr        int                       size          ( )     const;
        constexpr        int                       capacity      ( )     const = delete;
        constexpr        array<int>                shape         ( )     const;
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
                                  constexpr array& resize ( integral auto... args )         requires ( sizeof...(args) == dim );
                                  constexpr array& resize ( array<int> );
        template < int axis = 1 > constexpr array& push   (      array<type,dim-1,device> ) requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis = 1 > constexpr array& pop    ( )                               requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis = 1 > constexpr array& insert ( int, array<type,dim-1,device> ) requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis = 1 > constexpr array& erase  ( int )                           requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );

    public: // View
        constexpr       array<type,1,device>&   flatten   ( );
        constexpr const array<type,1,device>&   flatten   ( ) const;
        constexpr       array<type,dim,device>& transpose ( );
        constexpr const array<type,dim,device>& transpose ( ) const;

    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const;

    public: // Mdspan
        constexpr       auto mdspan ( );
        constexpr const auto mdspan ( ) const;
        
    private: // Detail
                              constexpr int                                                get_size_top  ( )                          const;
        template < int axis > constexpr int                                                get_size_axis ( )                          const;
                              constexpr detail::array_shape<dim>                           get_shape     ( )                          const;
        template < int dim2 > constexpr pair<      detail::array_upper<type,dim2,device>*> get_rows      ( integral auto... );
        template < int dim2 > constexpr pair<const detail::array_upper<type,dim2,device>*> get_rows      ( integral auto... )         const;
        template < int dim2 > constexpr pair<      detail::array_upper<type,dim2,device>*> get_columns   ( integral auto... );
        template < int dim2 > constexpr pair<const detail::array_upper<type,dim2,device>*> get_columns   ( integral auto... )         const;
                              constexpr reference                                          get_value     ( integral auto... );
                              constexpr const_reference                                    get_value     ( integral auto... )         const;
                              constexpr pointer                                            get_pointer   ( integral auto... );
                              constexpr const_pointer                                      get_pointer   ( integral auto... )         const;
                              constexpr void                                               set_resize    ( detail::array_shape<dim> );

    private: // Friend
        template < class type2, int dim2, class device2 > friend class array;
        template < class type2, int dim2, class device2 > friend class detail::array_upper;
        template < class type2, int dim2, class device2 > friend class detail::array_uppers;
        template < class type2, int dim2, class device2 > friend class detail::array_lower;
        template < class type2, int dim2, class device2 > friend class detail::transform_to_array;

    protected: // ADL
        template < class type2, class device2 = cpu > using vector = array<type2,1,device2>; // Redirect to global array instead of extended one.
};