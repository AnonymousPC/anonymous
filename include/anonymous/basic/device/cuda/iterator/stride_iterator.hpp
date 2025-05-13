template < class iterator >
class cuda::stride_iterator
    extends public thrust::iterator_adaptor<stride_iterator<iterator>,iterator>
{
    public: // Typedef
        using iterator_concept  = ::cuda::std::common_type_t<typename ::cuda::std::iterator_traits<iterator>::iterator_category,::cuda::std::random_access_iterator_tag>;
        using iterator_category = ::cuda::std::common_type_t<typename ::cuda::std::iterator_traits<iterator>::iterator_category,::cuda::std::random_access_iterator_tag>;
        using value_type        = ::cuda::std::iterator_traits<iterator>::value_type;
        using reference         = ::cuda::std::iterator_traits<iterator>::reference;
        using pointer           = ::cuda::std::iterator_traits<iterator>::pointer;
        using difference_type   = ::cuda::std::iterator_traits<iterator>::difference_type;

    public: // Data
        difference_type strd = difference_type();

    public: // Core
        constexpr stride_iterator ( )                           requires ::cuda::std::default_initializable<iterator> = default;
        constexpr stride_iterator ( iterator, difference_type );

    public: // Member
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const requires ::cuda::std::random_access_iterator<iterator>;

    public: // Access
        constexpr difference_type stride ( ) const;

    public: // Cuda
        friend class thrust::iterator_core_access;
};

template < class iterator > constexpr bool                                                       operator ==  ( cuda::template stride_iterator<iterator>,  cuda::template stride_iterator<iterator> ) requires ::cuda::std::sentinel_for          <iterator,iterator>;
template < class iterator > constexpr /*cuda*/std::compare_three_way_result_t<iterator,iterator> operator <=> ( cuda::template stride_iterator<iterator>,  cuda::template stride_iterator<iterator> ) requires ::cuda::std::totally_ordered       <iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>                   operator +   ( cuda::template stride_iterator<iterator>,  ::cuda::std::iter_difference_t<iterator> ) requires ::cuda::std::random_access_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>                   operator +   ( ::cuda::std::iter_difference_t<iterator>,  cuda::template stride_iterator<iterator> ) requires ::cuda::std::random_access_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>                   operator -   ( cuda::template stride_iterator<iterator>,  ::cuda::std::iter_difference_t<iterator> ) requires ::cuda::std::random_access_iterator<iterator>;
template < class iterator > constexpr ::cuda::std::iter_difference_t<iterator>                   operator -   ( cuda::template stride_iterator<iterator>,  cuda::template stride_iterator<iterator> ) requires ::cuda::std::random_access_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>&                  operator +=  ( cuda::template stride_iterator<iterator>&, ::cuda::std::iter_difference_t<iterator> ) requires ::cuda::std::random_access_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>&                  operator -=  ( cuda::template stride_iterator<iterator>&, ::cuda::std::iter_difference_t<iterator> ) requires ::cuda::std::random_access_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>&                  operator ++  ( cuda::template stride_iterator<iterator>&                                           ) requires ::cuda::std::bidirectional_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>                   operator ++  ( cuda::template stride_iterator<iterator>&, int                                      ) requires ::cuda::std::bidirectional_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>&                  operator --  ( cuda::template stride_iterator<iterator>&                                           ) requires ::cuda::std::bidirectional_iterator<iterator>;
template < class iterator > constexpr cuda::template stride_iterator<iterator>                   operator --  ( cuda::template stride_iterator<iterator>&, int                                      ) requires ::cuda::std::bidirectional_iterator<iterator>;
        
#include "stride_iterator.cpp"
