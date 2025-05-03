template < class type, class device >
class detail::array_upper<type,max_dim,device>
{
    private: // Data
        array<type,max_dim,device>* ptr = nullptr;

    public: // Typedef
        using value_type      = device::template value_type      <type>;
        using reference       = device::template reference       <type>;
        using const_reference = device::template const_reference <type>;
        using pointer         = device::template pointer         <type>;
        using const_pointer   = device::template const_pointer   <type>;
        using iterator        = detail::array_line_iterator      <type,max_dim,device>;
        using const_iterator  = detail::array_line_const_iterator<type,max_dim,device>;
    
    public: // Core
        constexpr array_upper ( ) = default;
        constexpr array_upper (       array<type,max_dim,device>& );
        constexpr array_upper ( const array<type,max_dim,device>& );

    public: // Member
        constexpr       int                           size          ( )     const;
        constexpr       int                           capacity      ( )     const = delete;
        constexpr       array<int>                    shape         ( )     const;
        constexpr       int                           row           ( )     const;
        constexpr       int                           column        ( )     const requires ( max_dim == 2 );
        constexpr       bool                          empty         ( )     const;
        constexpr       pointer                       data          ( )           = delete;
        constexpr       const_pointer                 data          ( )     const = delete;
        constexpr       iterator                      begin         ( );
        constexpr       const_iterator                begin         ( )     const;
        constexpr       iterator                      end           ( );
        constexpr       const_iterator                end           ( )     const;
        constexpr       array<type,max_dim-1,device>& operator []   ( int );
        constexpr const array<type,max_dim-1,device>& operator []   ( int ) const;

    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const = delete;

    public: // Detail
                              constexpr       int                                              get_size_top  ( )                  const = delete;
        template < int axis > constexpr       int                                              get_size_axis ( )                  const;
                              constexpr       detail::array_shape<max_dim>                     get_shape     ( )                  const;
        template < int dim2 > constexpr       std::span<detail::array_upper<type,dim2,device>> get_rows      ( int_type auto... );
        template < int dim2 > constexpr const std::span<detail::array_upper<type,dim2,device>> get_rows      ( int_type auto... ) const;
        template < int dim2 > constexpr       std::span<detail::array_upper<type,dim2,device>> get_columns   ( int_type auto... );
        template < int dim2 > constexpr const std::span<detail::array_upper<type,dim2,device>> get_columns   ( int_type auto... ) const;
                              constexpr       reference                                        get_value     ( int_type auto... )       = delete;
                              constexpr       const_reference                                  get_value     ( int_type auto... ) const = delete;
                              constexpr       pointer                                          get_pointer   ( int_type auto... )       = delete;
                              constexpr       const_pointer                                    get_pointer   ( int_type auto... ) const = delete;

                              constexpr       array_attribute                                  get_attribute ( )                  const;
                              constexpr       int                                              get_offset    ( )                  const;
                              constexpr       array<type,max_dim,device>&                      get_host      ( );
                              constexpr const array<type,max_dim,device>&                      get_host      ( )                  const;
                              constexpr       int                                              get_stride    ( )                  const = delete;
};