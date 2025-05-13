template < class iterator > 
constexpr cuda::stride_iterator<iterator>::stride_iterator ( iterator init_iter, difference_type init_strd )
    extends thrust::iterator_adaptor<stride_iterator<iterator>,iterator> ( init_iter ),
            strd ( init_strd )
{
    
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>::reference cuda::stride_iterator<iterator>::operator * ( ) const
{
    return *thrust::iterator_adaptor<stride_iterator<iterator>,iterator>::base();
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>::pointer cuda::stride_iterator<iterator>::operator -> ( ) const
{
    return thrust::iterator_adaptor<stride_iterator<iterator>,iterator>::base();
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>::reference cuda::stride_iterator<iterator>::operator [] ( difference_type offset ) const
    requires ::cuda::std::random_access_iterator<iterator>
{
    return thrust::iterator_adaptor<stride_iterator<iterator>,iterator>::base()[offset * strd];
}


template < class iterator >
constexpr cuda::template stride_iterator<iterator>::difference_type cuda::stride_iterator<iterator>::stride ( ) const
{
    return strd;
}

template < class iterator > 
constexpr bool operator == ( cuda::template stride_iterator<iterator> left, cuda::template stride_iterator<iterator> right )
    requires ::cuda::std::sentinel_for<iterator,iterator>
{
    return left.operator->() == right.operator->();
}

template < class iterator >
constexpr /*cuda*/std::compare_three_way_result_t<iterator,iterator> operator <=> ( cuda::template stride_iterator<iterator> left, cuda::template stride_iterator<iterator> right )
    requires ::cuda::std::totally_ordered<iterator>
{
    if constexpr ( debug )
    {
        if ( left.stride() != right.stride() )
            throw value_error("cannot compare stride_iterator: stride mismatches (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
        if ( left.stride() == 0 )
            throw value_error("cannot compare stride_iterator: stride is zero (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
    }

    return left.stride() >= 0 ? (left .operator->() <=> right.operator->()) :
                                (right.operator->() <=> left .operator->());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator> operator + ( cuda::template stride_iterator<iterator> left, ::cuda::std::iter_difference_t<iterator> right )
     requires ::cuda::std::random_access_iterator<iterator>
{
    return cuda::template stride_iterator<iterator>(left.operator->() + left.stride() * right, left.stride());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator> operator + ( ::cuda::std::iter_difference_t<iterator> left, cuda::template stride_iterator<iterator> right )
     requires ::cuda::std::random_access_iterator<iterator>
{
    return cuda::template stride_iterator<iterator>(left * right.stride() + right.operator->(), right.stride());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator> operator - ( cuda::template stride_iterator<iterator> left, ::cuda::std::iter_difference_t<iterator> right )
    requires ::cuda::std::random_access_iterator<iterator>  
{
    return cuda::template stride_iterator<iterator>(left.operator->() - left.stride() * right, left.stride());
}

template < class iterator >
constexpr ::cuda::std::iter_difference_t<iterator> operator - ( cuda::template stride_iterator<iterator> left, cuda::template stride_iterator<iterator> right )
     requires ::cuda::std::random_access_iterator<iterator>
{
    if constexpr ( debug )
    {
        if ( left.stride() != right.stride() )
            throw value_error("cannot compare stride_iterator: stride mismatches (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
        if ( left.stride() == 0 )
            throw value_error("cannot compare stride_iterator: stride is zero (with left.stride() = {}, right.stride() = {})", left.stride(), right.stride());
    }

    return (left.operator->() - right.operator->()) / left.stride();
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>& operator += ( cuda::template stride_iterator<iterator>& left, ::cuda::std::iter_difference_t<iterator> right )
     requires ::cuda::std::random_access_iterator<iterator>
{
    return left = cuda::template stride_iterator<iterator>(left.operator->() + right, left.stride());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>& operator -= ( cuda::template stride_iterator<iterator>& left, ::cuda::std::iter_difference_t<iterator> right )
     requires ::cuda::std::random_access_iterator<iterator>
{
    return left = cuda::template stride_iterator<iterator>(left.operator->() - right, left.stride());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>& operator ++ ( cuda::template stride_iterator<iterator>& left )
     requires ::cuda::std::bidirectional_iterator<iterator>
{
    if constexpr ( ::cuda::std::random_access_iterator<iterator> )
        return left = cuda::template stride_iterator<iterator>(left.operator->() + left.stride(), left.stride());
    else
        return left = cuda::template stride_iterator<iterator>([&] { auto iter = left.operator->(); ::cuda::std::advance(iter, left.stride()); return iter; } (), left.stride());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator> operator ++ ( cuda::template stride_iterator<iterator>& left, int )
     requires ::cuda::std::bidirectional_iterator<iterator>
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator>& operator -- ( cuda::template stride_iterator<iterator>& left )
     requires ::cuda::std::bidirectional_iterator<iterator>
{
    if constexpr ( ::cuda::std::random_access_iterator<iterator> )
        return left = cuda::template stride_iterator<iterator>(left.operator->() - left.stride(), left.stride());
    else
        return left = cuda::template stride_iterator<iterator>([&] { auto iter = left.operator->(); ::cuda::std::advance(iter, -left.stride()); return iter; } (), left.stride());
}

template < class iterator >
constexpr cuda::template stride_iterator<iterator> operator -- ( cuda::template stride_iterator<iterator>& left, int )
     requires ::cuda::std::bidirectional_iterator<iterator>
{
    auto tmp = left;
    --left;
    return tmp;
}