template < class iterator >
class cpu::stride_iterator
{
    public: // Typedef
        using iterator_category = std::common_type_t<typename std::iterator_traits<iterator>::iterator_category,std::random_access_iterator_tag>;
        using value_type        = std::iterator_traits<iterator>::value_type;
        using reference         = std::iterator_traits<iterator>::reference;
        using pointer           = std::iterator_traits<iterator>::pointer;
        using difference_type   = std::iterator_traits<iterator>::difference_type;

    private: // Data
        iterator        iter = iterator();
        difference_type strd = difference_type();

    public: // Core
        constexpr stride_iterator ( )                           requires std::default_initializable<iterator> = default;
        constexpr stride_iterator ( iterator, difference_type );

    public: // Member
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const requires std::random_access_iterator<iterator>;

    public: // Access
        constexpr difference_type stride ( ) const;
};

template < class iterator > constexpr bool                                               operator ==  ( cpu::template stride_iterator<iterator>,  cpu::template stride_iterator<iterator> ) requires std::sentinel_for          <iterator,iterator>;
template < class iterator > constexpr std::compare_three_way_result_t<iterator,iterator> operator <=> ( cpu::template stride_iterator<iterator>,  cpu::template stride_iterator<iterator> ) requires std::totally_ordered       <iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>            operator +   ( cpu::template stride_iterator<iterator>,  std::iter_difference_t       <iterator> ) requires std::random_access_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>            operator +   ( std::iter_difference_t       <iterator>,  cpu::template stride_iterator<iterator> ) requires std::random_access_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>            operator -   ( cpu::template stride_iterator<iterator>,  std::iter_difference_t       <iterator> ) requires std::random_access_iterator<iterator>;
template < class iterator > constexpr std::iter_difference_t       <iterator>            operator -   ( cpu::template stride_iterator<iterator>,  cpu::template stride_iterator<iterator> ) requires std::random_access_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>&           operator +=  ( cpu::template stride_iterator<iterator>&, std::iter_difference_t       <iterator> ) requires std::random_access_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>&           operator -=  ( cpu::template stride_iterator<iterator>&, std::iter_difference_t       <iterator> ) requires std::random_access_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>&           operator ++  ( cpu::template stride_iterator<iterator>&                                          ) requires std::bidirectional_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>            operator ++  ( cpu::template stride_iterator<iterator>&, int                                     ) requires std::bidirectional_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>&           operator --  ( cpu::template stride_iterator<iterator>&                                          ) requires std::bidirectional_iterator<iterator>;
template < class iterator > constexpr cpu::template stride_iterator<iterator>            operator --  ( cpu::template stride_iterator<iterator>&, int                                     ) requires std::bidirectional_iterator<iterator>;
        
#include "stride_iterator.cpp"