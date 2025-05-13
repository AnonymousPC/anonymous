template < class type >
class opencl::pointer
{
    public: // Typedef
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using value_type        = opencl::template value_type<type>;
        using reference         = opencl::template reference <type>;
     // using pointer           = opencl::template pointer   <type>;
        using difference_type   = std::ptrdiff_t;

    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        difference_type        idx = 0;

    public: // Core 
        constexpr pointer ( ) = default;
        constexpr pointer ( boost::compute::buffer, difference_type );

    public: // Const
        constexpr explicit pointer ( const_pointer<type> );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr reference operator [] ( difference_type ) const;

    public: // Access
        constexpr       boost::compute::buffer& get_buffer ( );
        constexpr const boost::compute::buffer& get_buffer ( ) const;
        constexpr       difference_type&        get_index  ( );
        constexpr const difference_type&        get_index  ( ) const;

    public: // Boost.compute
        constexpr pointer ( boost::compute::buffer_iterator<type> );
        constexpr operator  boost::compute::buffer_iterator<type> ( )        const;
        constexpr pointer ( boost::compute::detail::device_ptr<type> );
        constexpr operator  boost::compute::detail::device_ptr<type> ( )     const;
        constexpr type read  (              boost::compute::command_queue& ) const;
        constexpr void write ( const type&, boost::compute::command_queue& ) const;

        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;
};

template < class type >
class opencl::const_pointer
{
    public: // Typedef
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using value_type        = opencl::template value_type     <type>;
        using reference         = opencl::template const_reference<type>;
     // using pointer           = opencl::template const_pointer  <type>;
        using difference_type   = std::ptrdiff_t;

    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        difference_type        idx = 0;

    public: // Core 
        constexpr const_pointer ( ) = default;
        constexpr const_pointer ( boost::compute::buffer, difference_type );

    public: // Const
        constexpr const_pointer ( pointer<type> );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr reference operator [] ( difference_type ) const;

    public: // Access
        constexpr       boost::compute::buffer& get_buffer ( )       = delete;
        constexpr const boost::compute::buffer& get_buffer ( ) const;
        constexpr       difference_type&        get_index  ( );
        constexpr const difference_type&        get_index  ( ) const;

    public: // Boost.compute
        constexpr const_pointer ( boost::compute::buffer_iterator<type> );
        constexpr operator        boost::compute::buffer_iterator<type>    ( ) const = delete;
        constexpr const_pointer ( boost::compute::detail::device_ptr<type> );
        constexpr operator        boost::compute::detail::device_ptr<type> ( ) const = delete; 
        constexpr type read  (              boost::compute::command_queue& )   const;
        constexpr void write ( const type&, boost::compute::command_queue& )   const = delete;

        template < class... expr > constexpr const auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > constexpr const auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > constexpr const auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;
};

template < class type > constexpr bool                                  operator ==  ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > constexpr bool                                  operator ==  ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > constexpr bool                                  operator ==  ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > constexpr bool                                  operator ==  ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > constexpr std::partial_ordering                 operator <=> ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > constexpr std::partial_ordering                 operator <=> ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > constexpr std::partial_ordering                 operator <=> ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > constexpr std::partial_ordering                 operator <=> ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > constexpr opencl::template       pointer<type>  operator  +  ( opencl::template       pointer<type>,  std::ptrdiff_t                       );
template < class type > constexpr opencl::template const_pointer<type>  operator  +  ( opencl::template const_pointer<type>,  std::ptrdiff_t                       );
template < class type > constexpr opencl::template       pointer<type>  operator  +  ( std::ptrdiff_t,                        opencl::template       pointer<type> );
template < class type > constexpr opencl::template const_pointer<type>  operator  +  ( std::ptrdiff_t,                        opencl::template const_pointer<type> );
template < class type > constexpr opencl::template       pointer<type>  operator  -  ( opencl::template       pointer<type>,  std::ptrdiff_t                       );
template < class type > constexpr opencl::template const_pointer<type>  operator  -  ( opencl::template const_pointer<type>,  std::ptrdiff_t                       );
template < class type > constexpr std::ptrdiff_t                        operator  -  ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > constexpr std::ptrdiff_t                        operator  -  ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > constexpr std::ptrdiff_t                        operator  -  ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > constexpr std::ptrdiff_t                        operator  -  ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > constexpr opencl::template       pointer<type>& operator  += ( opencl::template       pointer<type>&, std::ptrdiff_t                       );
template < class type > constexpr opencl::template const_pointer<type>& operator  += ( opencl::template const_pointer<type>&, std::ptrdiff_t                       );
template < class type > constexpr opencl::template       pointer<type>& operator  -= ( opencl::template       pointer<type>&, std::ptrdiff_t                       );
template < class type > constexpr opencl::template const_pointer<type>& operator  -= ( opencl::template const_pointer<type>&, std::ptrdiff_t                       );
template < class type > constexpr opencl::template       pointer<type>& operator  ++ ( opencl::template       pointer<type>&                                       );
template < class type > constexpr opencl::template const_pointer<type>& operator  ++ ( opencl::template const_pointer<type>&                                       );
template < class type > constexpr opencl::template       pointer<type>  operator  ++ ( opencl::template       pointer<type>&, int                                  );
template < class type > constexpr opencl::template const_pointer<type>  operator  ++ ( opencl::template const_pointer<type>&, int                                  );
template < class type > constexpr opencl::template       pointer<type>& operator  -- ( opencl::template       pointer<type>&                                       );
template < class type > constexpr opencl::template const_pointer<type>& operator  -- ( opencl::template const_pointer<type>&                                       );
template < class type > constexpr opencl::template       pointer<type>  operator  -- ( opencl::template       pointer<type>&, int                                  );
template < class type > constexpr opencl::template const_pointer<type>  operator  -- ( opencl::template const_pointer<type>&, int                                  );

#include "pointer.cpp"