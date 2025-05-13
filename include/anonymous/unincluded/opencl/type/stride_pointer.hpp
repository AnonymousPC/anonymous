template < class type >
class opencl::stride_pointer
{
    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = opencl::template value_type<type>;
        using reference         = opencl::template reference <type>;
        using pointer           = opencl::template pointer   <type>;
        using difference_type   = std::ptrdiff_t;

    private: // Data
        pointer         ptr  = pointer();
        difference_type strd = 1;

    public: // Core
        constexpr stride_pointer ( ) = default;
        constexpr stride_pointer ( pointer, difference_type );

    public: // Const
        constexpr explicit stride_pointer ( const_stride_pointer<type> );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const;

    public: // Access  
        constexpr       pointer&         get_pointer ( );
        constexpr const pointer&         get_pointer ( ) const;
        constexpr       difference_type& get_stride  ( );
        constexpr const difference_type& get_stride  ( ) const;

    public: // Boost.compute
        constexpr type read  (              boost::compute::command_queue& ) const;
        constexpr void write ( const type&, boost::compute::command_queue& ) const;
        template < class index >   struct index_expr;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;
};
    
template < class type >
class opencl::const_stride_pointer
{
    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = opencl::template value_type     <type>;
        using reference         = opencl::template const_reference<type>;
        using pointer           = opencl::template const_pointer  <type>;
        using difference_type   = std::ptrdiff_t;

    private: // Data
        pointer         ptr  = pointer();
        difference_type strd = 1;

    public: // Core
        constexpr const_stride_pointer ( ) = default;
        constexpr const_stride_pointer ( pointer, difference_type );

    public: // Const
        constexpr const_stride_pointer ( stride_pointer<type> );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const;

    public: // Access  
        constexpr       pointer&         get_pointer ( );
        constexpr const pointer&         get_pointer ( ) const;
        constexpr       difference_type& get_stride  ( );
        constexpr const difference_type& get_stride  ( ) const;

    public: // Boost.compute
        constexpr type read  (              boost::compute::command_queue& ) const;
        constexpr void write ( const type&, boost::compute::command_queue& ) const = delete;
        template < class index >   struct index_expr;
        template < class... expr > constexpr const auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > constexpr const auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > constexpr const auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;
};

template < class type > constexpr bool                                         operator ==  ( opencl::template       stride_pointer<type>,  opencl::template       stride_pointer<type> );
template < class type > constexpr bool                                         operator ==  ( opencl::template       stride_pointer<type>,  opencl::template const_stride_pointer<type> );
template < class type > constexpr bool                                         operator ==  ( opencl::template const_stride_pointer<type>,  opencl::template       stride_pointer<type> );
template < class type > constexpr bool                                         operator ==  ( opencl::template const_stride_pointer<type>,  opencl::template const_stride_pointer<type> );
template < class type > constexpr std::partial_ordering                        operator <=> ( opencl::template       stride_pointer<type>,  opencl::template       stride_pointer<type> );
template < class type > constexpr std::partial_ordering                        operator <=> ( opencl::template       stride_pointer<type>,  opencl::template const_stride_pointer<type> );
template < class type > constexpr std::partial_ordering                        operator <=> ( opencl::template const_stride_pointer<type>,  opencl::template       stride_pointer<type> );
template < class type > constexpr std::partial_ordering                        operator <=> ( opencl::template const_stride_pointer<type>,  opencl::template const_stride_pointer<type> );
template < class type > constexpr opencl::template       stride_pointer<type>  operator  +  ( opencl::template       stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr opencl::template const_stride_pointer<type>  operator  +  ( opencl::template const_stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr opencl::template       stride_pointer<type>  operator  +  ( std::ptrdiff_t,                            opencl::template       stride_pointer<type> );
template < class type > constexpr opencl::template const_stride_pointer<type>  operator  +  ( std::ptrdiff_t,                            opencl::template const_stride_pointer<type> );
template < class type > constexpr opencl::template       stride_pointer<type>  operator  -  ( opencl::template       stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr opencl::template const_stride_pointer<type>  operator  -  ( opencl::template const_stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr std::ptrdiff_t                               operator  -  ( opencl::template       stride_pointer<type>,  opencl::template       stride_pointer<type> );
template < class type > constexpr std::ptrdiff_t                               operator  -  ( opencl::template       stride_pointer<type>,  opencl::template const_stride_pointer<type> );
template < class type > constexpr std::ptrdiff_t                               operator  -  ( opencl::template const_stride_pointer<type>,  opencl::template       stride_pointer<type> );
template < class type > constexpr std::ptrdiff_t                               operator  -  ( opencl::template const_stride_pointer<type>,  opencl::template const_stride_pointer<type> );
template < class type > constexpr opencl::template       stride_pointer<type>& operator  += ( opencl::template       stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr opencl::template const_stride_pointer<type>& operator  += ( opencl::template const_stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr opencl::template       stride_pointer<type>& operator  -= ( opencl::template       stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr opencl::template const_stride_pointer<type>& operator  -= ( opencl::template const_stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr opencl::template       stride_pointer<type>& operator  ++ ( opencl::template       stride_pointer<type>&                                           );
template < class type > constexpr opencl::template const_stride_pointer<type>& operator  ++ ( opencl::template const_stride_pointer<type>&                                           );
template < class type > constexpr opencl::template       stride_pointer<type>  operator  ++ ( opencl::template       stride_pointer<type>&, int                                      );
template < class type > constexpr opencl::template const_stride_pointer<type>  operator  ++ ( opencl::template const_stride_pointer<type>&, int                                      );
template < class type > constexpr opencl::template       stride_pointer<type>& operator  -- ( opencl::template       stride_pointer<type>&                                           );
template < class type > constexpr opencl::template const_stride_pointer<type>& operator  -- ( opencl::template const_stride_pointer<type>&                                           );
template < class type > constexpr opencl::template       stride_pointer<type>  operator  -- ( opencl::template       stride_pointer<type>&, int                                      );
template < class type > constexpr opencl::template const_stride_pointer<type>  operator  -- ( opencl::template const_stride_pointer<type>&, int                                      );


#include "stride_pointer.cpp"