template < class type, int dim, class device >
    requires ( dim >= 2 )
class detail::array_info<type,dim,device>
{
    private: // Data
        detail::array_shape<dim> shp;

    public: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    public: // Core
        constexpr array_info ( )                          = default;
        constexpr array_info ( detail::array_shape<dim> );

    public: // Member
        constexpr int        size   ( ) const;
        constexpr array<int> shape  ( ) const;
        constexpr int        row    ( ) const;
        constexpr int        column ( ) const requires ( dim == 2 );
        constexpr bool       empty  ( ) const;

    public: // Member
        constexpr array_info& clear ( );

    public: // Detail
        template < int axis > constexpr int                      get_size_axis ( )                          const;
                              constexpr detail::array_shape<dim> get_shape     ( )                          const;
                              constexpr void                     set_resize    ( detail::array_shape<dim> );
        
};