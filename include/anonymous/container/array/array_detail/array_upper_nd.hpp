template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
class detail::array_upper<type,dim,device>
{
    private: // Data
        array<type,dim+1,device>* ptr1 = nullptr;
        array<type,dim,  device>* ptr2 = nullptr;
        detail::array_attribute   atr  = detail::rows_attribute;
        int                       ofs  = 0;

    public: // Typedef
        using value_type      = device::template value_type      <type>;
        using reference       = device::template reference       <type>;
        using const_reference = device::template const_reference <type>;
        using pointer         = device::template pointer         <type>;
        using const_pointer   = device::template const_pointer   <type>;
        using iterator        = cpu   ::template transform_iterator<      detail::array_upper<type,dim-1,device>*,detail::transform_to_array<type,dim-1,device>>;
        using const_iterator  = cpu   ::template transform_iterator<const detail::array_upper<type,dim-1,device>*,detail::transform_to_array<type,dim-1,device>>;
    
    public: // Core
        constexpr array_upper ( )                                                               = default;
        constexpr array_upper (       array<type,dim+1,device>&, detail::array_attribute, int );
        constexpr array_upper ( const array<type,dim+1,device>&, detail::array_attribute, int );
        constexpr array_upper (       array<type,dim,  device>& );
        constexpr array_upper ( const array<type,dim,  device>& );

    public: // Member
        constexpr       int                       size        ( )     const;
        constexpr       int                       capacity    ( )     const = delete;
        constexpr       array<int>                shape       ( )     const;
        constexpr       int                       row         ( )     const;
        constexpr       int                       column      ( )     const requires ( dim == 2 );
        constexpr       bool                      empty       ( )     const;
        constexpr       pointer                   data        ( );
        constexpr       const_pointer             data        ( )     const;
        constexpr       iterator                  begin       ( );
        constexpr       const_iterator            begin       ( )     const;
        constexpr       iterator                  end         ( );
        constexpr       const_iterator            end         ( )     const;
        constexpr       array<type,dim-1,device>& operator [] ( int );
        constexpr const array<type,dim-1,device>& operator [] ( int ) const;

    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const;

    public: // Detail
                               constexpr       int                                                get_size_top  ( )                  const;
        template < int axis >  constexpr       int                                                get_size_axis ( )                  const;
                               constexpr       detail::array_shape<dim>                           get_shape     ( )                  const;
        template < int dim2 >  constexpr       pair<      detail::array_upper<type,dim2,device>*> get_rows      ( integral auto... );
        template < int dim2 >  constexpr       pair<const detail::array_upper<type,dim2,device>*> get_rows      ( integral auto... ) const;
        template < int dim2 >  constexpr       pair<      detail::array_upper<type,dim2,device>*> get_columns   ( integral auto... );
        template < int dim2 >  constexpr       pair<const detail::array_upper<type,dim2,device>*> get_columns   ( integral auto... ) const;
                               constexpr       reference                                          get_value     ( integral auto... );
                               constexpr       const_reference                                    get_value     ( integral auto... ) const;
                               constexpr       pointer                                            get_pointer   ( integral auto... );
                               constexpr       const_pointer                                      get_pointer   ( integral auto... ) const;

                               constexpr       array_attribute                                    get_attribute ( )                  const;
                               constexpr       int                                                get_offset    ( )                  const;
        template < auto attr > constexpr       array<type,dim+1,device>&                          get_host      ( )                        requires ( attr == rows_attribute or attr == columns_attribute );
        template < auto attr > constexpr const array<type,dim+1,device>&                          get_host      ( )                  const requires ( attr == rows_attribute or attr == columns_attribute );
        template < auto attr > constexpr       array<type,dim,  device>&                          get_host      ( )                        requires ( attr == transpose_attribute );
        template < auto attr > constexpr const array<type,dim,  device>&                          get_host      ( )                  const requires ( attr == transpose_attribute );
                               constexpr       int                                                get_stride    ( )                  const;
};