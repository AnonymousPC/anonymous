template < class iterator, class function > 
constexpr cpu::transform_iterator<iterator,function>::transform_iterator ( iterator init_iter )
    requires std::default_initializable<function>
    extends iter ( init_iter )
{
    
}

template < class iterator, class function > 
constexpr cpu::transform_iterator<iterator,function>::transform_iterator ( iterator init_iter, function init_func )
    extends iter ( init_iter ),
            func ( init_func )
{
    
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>::reference cpu::transform_iterator<iterator,function>::operator * ( ) const
{
    return func(*iter);
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>::pointer cpu::transform_iterator<iterator,function>::operator -> ( ) const
{
    return func(iter);
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>::reference cpu::transform_iterator<iterator,function>::operator [] ( difference_type offset ) const
    requires std::random_access_iterator<iterator>
{
    return func(iter[offset]);
}

template < class iterator, class function >
constexpr iterator cpu::transform_iterator<iterator,function>::base ( ) const
{
    return iter;
}

template < class iterator, class function >
constexpr function cpu::transform_iterator<iterator,function>::transform ( ) const
{
    return func;
}

template < class iterator, class function > 
constexpr bool operator == ( cpu::template transform_iterator<iterator,function> left, cpu::template transform_iterator<iterator,function> right )
    requires std::sentinel_for<iterator,iterator>
{
    return left.base() == right.base();
}

template < class iterator, class function >
constexpr std::compare_three_way_result_t<iterator,iterator> operator <=> ( cpu::template transform_iterator<iterator,function> left, cpu::template transform_iterator<iterator,function> right )
    requires std::totally_ordered<iterator>
{
    return left.base() <=> right.base();
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function> operator + ( cpu::template transform_iterator<iterator,function> left, std::iter_difference_t<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return cpu::template transform_iterator<iterator,function>(left.base() + right, left.transform());
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function> operator + ( std::iter_difference_t<iterator> left, cpu::template transform_iterator<iterator,function> right )
     requires std::random_access_iterator<iterator>
{
    return cpu::template transform_iterator<iterator,function>(left + right.base(), right.transform());
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function> operator - ( cpu::template transform_iterator<iterator,function> left, std::iter_difference_t<iterator> right )
    requires std::random_access_iterator<iterator>  
{
    return cpu::template transform_iterator<iterator,function>(left.base() - right, left.transform());
}

template < class iterator, class function >
constexpr std::iter_difference_t<iterator> operator - ( cpu::template transform_iterator<iterator,function> left, cpu::template transform_iterator<iterator,function> right )
     requires std::random_access_iterator<iterator>
{
    return left.base() - right.base();
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>& operator += ( cpu::template transform_iterator<iterator,function>& left, std::iter_difference_t<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return left = cpu::template transform_iterator<iterator,function>(left.base() + right, std::move(left.transform()));
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>& operator -= ( cpu::template transform_iterator<iterator,function>& left, std::iter_difference_t<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return left = cpu::template transform_iterator<iterator,function>(left.base() - right, std::move(left.transform()));
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>& operator ++ ( cpu::template transform_iterator<iterator,function>& left )
     requires std::bidirectional_iterator<iterator>
{
    auto tmp = left.base();
    ++tmp;
    return left = cpu::template transform_iterator<iterator,function>(std::move(tmp), std::move(left.transform()));
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function> operator ++ ( cpu::template transform_iterator<iterator,function>& left, int )
     requires std::bidirectional_iterator<iterator>
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function>& operator -- ( cpu::template transform_iterator<iterator,function>& left )
     requires std::bidirectional_iterator<iterator>
{
    auto tmp = left.base();
    --tmp;
    return left = cpu::template transform_iterator<iterator,function>(std::move(tmp), std::move(left.transform()));
}

template < class iterator, class function >
constexpr cpu::template transform_iterator<iterator,function> operator -- ( cpu::template transform_iterator<iterator,function>& left, int )
     requires std::bidirectional_iterator<iterator>
{
    auto tmp = left;
    --left;
    return tmp;
}