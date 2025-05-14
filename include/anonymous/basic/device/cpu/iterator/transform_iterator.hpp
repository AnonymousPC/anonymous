template < class iterator, class function >
class cpu::transform_iterator
{
    public: // Typedef
        using iterator_category = std::common_type_t<typename std::iterator_traits<iterator>::iterator_category,std::random_access_iterator_tag>;
        using value_type        = std::invoke_result_t<function,typename std::iterator_traits<iterator>::value_type>;
        using reference         = std::invoke_result_t<function,typename std::iterator_traits<iterator>::reference>; // TODO: does this pass compiler if not invocable ?
        using pointer           = std::invoke_result_t<function,typename std::iterator_traits<iterator>::pointer>;   // TODO: does this pass compiler if not invocable ?
        using difference_type   = std::iterator_traits<iterator>::difference_type;

    private: // Data
        iterator iter = iterator();
        function func = function();

    public: // Core
        constexpr transform_iterator ( )                    requires std::default_initializable<iterator> and std::default_initializable<function> = default;
        constexpr transform_iterator ( iterator )           requires std::default_initializable<function>;
        constexpr transform_iterator ( iterator, function );

    public: // Member
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const requires std::random_access_iterator<iterator>;

    public: // Access
        constexpr iterator base      ( ) const;
        constexpr function transform ( ) const;
};

template < class iterator, class function > constexpr bool                                                 operator ==  ( cpu::template transform_iterator<iterator,function>,  cpu::template transform_iterator<iterator,function> ) requires std::sentinel_for          <iterator,iterator>;
template < class iterator, class function > constexpr std::compare_three_way_result_t <iterator,iterator>  operator <=> ( cpu::template transform_iterator<iterator,function>,  cpu::template transform_iterator<iterator,function> ) requires std::totally_ordered       <iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>  operator +   ( cpu::template transform_iterator<iterator,function>,  std::iter_difference_t          <iterator>          ) requires std::random_access_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>  operator +   ( std::iter_difference_t          <iterator>,           cpu::template transform_iterator<iterator,function> ) requires std::random_access_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>  operator -   ( cpu::template transform_iterator<iterator,function>,  std::iter_difference_t          <iterator>          ) requires std::random_access_iterator<iterator>;
template < class iterator, class function > constexpr std::iter_difference_t          <iterator>           operator -   ( cpu::template transform_iterator<iterator,function>,  cpu::template transform_iterator<iterator,function> ) requires std::random_access_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>& operator +=  ( cpu::template transform_iterator<iterator,function>&, std::iter_difference_t          <iterator>          ) requires std::random_access_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>& operator -=  ( cpu::template transform_iterator<iterator,function>&, std::iter_difference_t          <iterator>          ) requires std::random_access_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>& operator ++  ( cpu::template transform_iterator<iterator,function>&                                                      ) requires std::bidirectional_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>  operator ++  ( cpu::template transform_iterator<iterator,function>&, int                                                 ) requires std::bidirectional_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>& operator --  ( cpu::template transform_iterator<iterator,function>&                                                      ) requires std::bidirectional_iterator<iterator>;
template < class iterator, class function > constexpr cpu::template transform_iterator<iterator,function>  operator --  ( cpu::template transform_iterator<iterator,function>&, int                                                 ) requires std::bidirectional_iterator<iterator>;
        
#include "transform_iterator.cpp"