template < class type, class device >
class detail::array_upper<type,1,device>
{
    public: // Data
        array<type,2,device>*   ptr = nullptr;
        detail::array_attribute atr = detail::rows_attribute;
        int                     ofs = 0;

    public: // Typedef
        using value_type      = device::template value_type          <type>;
        using reference       = device::template reference           <type>;
        using const_reference = device::template const_reference     <type>;
        using pointer         = device::template pointer             <type>;
        using const_pointer   = device::template const_pointer       <type>;
        class iterator;
        class const_iterator;
    
    public: // Core
        constexpr array_upper ( )                                                           = default;
        constexpr array_upper (       array<type,2,device>&, detail::array_attribute, int );
        constexpr array_upper ( const array<type,2,device>&, detail::array_attribute, int );

    public: // Member
        constexpr int             size        ( )     const;
        constexpr int             capacity    ( )     const = delete;
        constexpr array<int>      shape       ( )     const;
        constexpr int             row         ( )     const = delete;
        constexpr int             column      ( )     const = delete;
        constexpr bool            empty       ( )     const;
        constexpr pointer         data        ( );
        constexpr const_pointer   data        ( )     const;
        constexpr iterator        begin       ( );
        constexpr const_iterator  begin       ( )     const;
        constexpr iterator        end         ( );
        constexpr const_iterator  end         ( )     const;
        constexpr reference       operator [] ( int );
        constexpr const_reference operator [] ( int ) const;
    
    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const;

    public: // Detail
                               constexpr       int                                              get_size_top    ( )     const;
        template < int axis >  constexpr       int                                              get_size_axis   ( )     const;
                               constexpr       detail::array_shape<1>                           get_shape       ( )     const;
        template < int dim2 >  constexpr       std::span<detail::array_upper<type,dim2,device>> get_rows        ( )           = delete;
        template < int dim2 >  constexpr const std::span<detail::array_upper<type,dim2,device>> get_rows        ( )     const = delete;
        template < int dim2 >  constexpr       std::span<detail::array_upper<type,dim2,device>> get_columns     ( )           = delete;
        template < int dim2 >  constexpr const std::span<detail::array_upper<type,dim2,device>> get_columns     ( )     const = delete;
                               constexpr       reference                                        get_value       ( int );
                               constexpr       const_reference                                  get_value       ( int ) const;
                               constexpr       pointer                                          get_pointer     ( int );
                               constexpr       const_pointer                                    get_pointer     ( int ) const;

                               constexpr       detail::array_attribute                          get_attribute   ( )     const;
                               constexpr       int                                              get_offset      ( )     const;
        template < auto attr > constexpr       array<type,2,device>&                            get_host        ( )           requires ( attr == rows_attribute or attr == columns_attribute );
        template < auto attr > constexpr const array<type,2,device>&                            get_host        ( )     const requires ( attr == rows_attribute or attr == columns_attribute );
                               constexpr       int                                              get_stride      ( )     const;
};