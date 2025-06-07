template < class iterator > 
constexpr cpu::stride_iterator<iterator>::stride_iterator ( iterator init_iter, difference_type init_strd )
    extends iter ( init_iter ),
            strd ( init_strd )
{
    
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>::reference cpu::stride_iterator<iterator>::operator * ( ) const
{
    return *iter;
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>::pointer cpu::stride_iterator<iterator>::operator -> ( ) const
{
    return iter;
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>::reference cpu::stride_iterator<iterator>::operator [] ( difference_type offset ) const
    requires std::random_access_iterator<iterator>
{
    return iter[offset * strd];
}

template < class iterator >
constexpr iterator cpu::stride_iterator<iterator>::base ( ) const
{
    return iter;
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>::difference_type cpu::stride_iterator<iterator>::stride ( ) const
{
    return strd;
}

template < class iterator > 
constexpr bool operator == ( cpu::template stride_iterator<iterator> left, cpu::template stride_iterator<iterator> right )
    requires std::sentinel_for<iterator,iterator>
{
    return left.base() == right.base();
}

template < class iterator >
constexpr std::compare_three_way_result_t<iterator,iterator> operator <=> ( cpu::template stride_iterator<iterator> left, cpu::template stride_iterator<iterator> right )
    requires std::totally_ordered<iterator>
{
    if constexpr ( debug )
    {
        if ( left.stride() != right.stride() )
            throw value_error("cannot compare stride_iterator: stride mismatches (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
        if ( left.stride() == 0 )
            throw value_error("cannot compare stride_iterator: stride is zero (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
    }

    return left.stride() >= 0 ? (left .base() <=> right.base()) :
                                (right.base() <=> left .base());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator> operator + ( cpu::template stride_iterator<iterator> left, std::iter_difference_t<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return cpu::template stride_iterator<iterator>(left.base() + left.stride() * right, left.stride());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator> operator + ( std::iter_difference_t<iterator> left, cpu::template stride_iterator<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return cpu::template stride_iterator<iterator>(left * right.stride() + right.base(), right.stride());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator> operator - ( cpu::template stride_iterator<iterator> left, std::iter_difference_t<iterator> right )
    requires std::random_access_iterator<iterator>  
{
    return cpu::template stride_iterator<iterator>(left.base() - left.stride() * right, left.stride());
}

template < class iterator >
constexpr std::iter_difference_t<iterator> operator - ( cpu::template stride_iterator<iterator> left, cpu::template stride_iterator<iterator> right )
     requires std::random_access_iterator<iterator>
{
    if constexpr ( debug )
    {
        if ( left.stride() != right.stride() )
            throw value_error("cannot compare stride_iterator: stride mismatches (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
        if ( left.stride() == 0 )
            throw value_error("cannot compare stride_iterator: stride is zero (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
    }

    return (left.base() - right.base()) / left.stride();
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>& operator += ( cpu::template stride_iterator<iterator>& left, std::iter_difference_t<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return left = cpu::template stride_iterator<iterator>(left.base() + right, left.stride());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>& operator -= ( cpu::template stride_iterator<iterator>& left, std::iter_difference_t<iterator> right )
     requires std::random_access_iterator<iterator>
{
    return left = cpu::template stride_iterator<iterator>(left.base() - right, left.stride());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>& operator ++ ( cpu::template stride_iterator<iterator>& left )
     requires std::bidirectional_iterator<iterator>
{
    if constexpr ( std::random_access_iterator<iterator> )
        return left = cpu::template stride_iterator<iterator>(left.base() + left.stride(), left.stride());
    else
        return left = cpu::template stride_iterator<iterator>([&] { auto iter = left.base(); std::advance(iter, left.stride()); return iter; } (), left.stride());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator> operator ++ ( cpu::template stride_iterator<iterator>& left, int )
     requires std::bidirectional_iterator<iterator>
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator>& operator -- ( cpu::template stride_iterator<iterator>& left )
     requires std::bidirectional_iterator<iterator>
{
    if constexpr ( std::random_access_iterator<iterator> )
        return left = cpu::template stride_iterator<iterator>(left.base() - left.stride(), left.stride());
    else
        return left = cpu::template stride_iterator<iterator>([&] { auto iter = left.base(); std::advance(iter, -left.stride()); return iter; } (), left.stride());
}

template < class iterator >
constexpr cpu::template stride_iterator<iterator> operator -- ( cpu::template stride_iterator<iterator>& left, int )
     requires std::bidirectional_iterator<iterator>
{
    auto tmp = left;
    --left;
    return tmp;
}