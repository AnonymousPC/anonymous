template < class type >
class cpu::stride_pointer
{
    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = cpu::template value_type<type>;
        using reference         = cpu::template reference <type>;
        using pointer           = cpu::template pointer   <type>;
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
};
    
template < class type >
class cpu::const_stride_pointer
{
    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = cpu::template value_type     <type>;
        using reference         = cpu::template const_reference<type>;
        using pointer           = cpu::template const_pointer  <type>;
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
};

template < class type > constexpr bool                                      operator ==  ( cpu::template       stride_pointer<type>,  cpu::template       stride_pointer<type> );
template < class type > constexpr bool                                      operator ==  ( cpu::template       stride_pointer<type>,  cpu::template const_stride_pointer<type> );
template < class type > constexpr bool                                      operator ==  ( cpu::template const_stride_pointer<type>,  cpu::template       stride_pointer<type> );
template < class type > constexpr bool                                      operator ==  ( cpu::template const_stride_pointer<type>,  cpu::template const_stride_pointer<type> );
template < class type > constexpr std::strong_ordering                      operator <=> ( cpu::template       stride_pointer<type>,  cpu::template       stride_pointer<type> );
template < class type > constexpr std::strong_ordering                      operator <=> ( cpu::template       stride_pointer<type>,  cpu::template const_stride_pointer<type> );
template < class type > constexpr std::strong_ordering                      operator <=> ( cpu::template const_stride_pointer<type>,  cpu::template       stride_pointer<type> );
template < class type > constexpr std::strong_ordering                      operator <=> ( cpu::template const_stride_pointer<type>,  cpu::template const_stride_pointer<type> );
template < class type > constexpr cpu::template       stride_pointer<type>  operator  +  ( cpu::template       stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr cpu::template const_stride_pointer<type>  operator  +  ( cpu::template const_stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr cpu::template       stride_pointer<type>  operator  +  ( std::ptrdiff_t,                            cpu::template       stride_pointer<type> );
template < class type > constexpr cpu::template const_stride_pointer<type>  operator  +  ( std::ptrdiff_t,                            cpu::template const_stride_pointer<type> );
template < class type > constexpr cpu::template       stride_pointer<type>  operator  -  ( cpu::template       stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr cpu::template const_stride_pointer<type>  operator  -  ( cpu::template const_stride_pointer<type>,  std::ptrdiff_t                           );
template < class type > constexpr std::ptrdiff_t                            operator  -  ( cpu::template       stride_pointer<type>,  cpu::template       stride_pointer<type> );
template < class type > constexpr std::ptrdiff_t                            operator  -  ( cpu::template       stride_pointer<type>,  cpu::template const_stride_pointer<type> );
template < class type > constexpr std::ptrdiff_t                            operator  -  ( cpu::template const_stride_pointer<type>,  cpu::template       stride_pointer<type> );
template < class type > constexpr std::ptrdiff_t                            operator  -  ( cpu::template const_stride_pointer<type>,  cpu::template const_stride_pointer<type> );
template < class type > constexpr cpu::template       stride_pointer<type>& operator  += ( cpu::template       stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr cpu::template const_stride_pointer<type>& operator  += ( cpu::template const_stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr cpu::template       stride_pointer<type>& operator  -= ( cpu::template       stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr cpu::template const_stride_pointer<type>& operator  -= ( cpu::template const_stride_pointer<type>&, std::ptrdiff_t                           );
template < class type > constexpr cpu::template       stride_pointer<type>& operator  ++ ( cpu::template       stride_pointer<type>&                                           );
template < class type > constexpr cpu::template const_stride_pointer<type>& operator  ++ ( cpu::template const_stride_pointer<type>&                                           );
template < class type > constexpr cpu::template       stride_pointer<type>  operator  ++ ( cpu::template       stride_pointer<type>&, int                                      );
template < class type > constexpr cpu::template const_stride_pointer<type>  operator  ++ ( cpu::template const_stride_pointer<type>&, int                                      );
template < class type > constexpr cpu::template       stride_pointer<type>& operator  -- ( cpu::template       stride_pointer<type>&                                           );
template < class type > constexpr cpu::template const_stride_pointer<type>& operator  -- ( cpu::template const_stride_pointer<type>&                                           );
template < class type > constexpr cpu::template       stride_pointer<type>  operator  -- ( cpu::template       stride_pointer<type>&, int                                      );
template < class type > constexpr cpu::template const_stride_pointer<type>  operator  -- ( cpu::template const_stride_pointer<type>&, int                                      );


#include "stride_pointer.cpp"