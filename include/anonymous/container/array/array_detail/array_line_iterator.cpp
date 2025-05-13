template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::array_line_iterator ( std::span<detail::array_upper<type,dim-1,device>>::iterator init_iter )
    extends iter ( init_iter )
{

}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::reference detail::array_line_iterator<type,dim,device>::operator * ( ) const
{
    return static_cast<reference>(iter.operator*());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::pointer detail::array_line_iterator<type,dim,device>::operator -> ( ) const
{
    return static_cast<pointer>(iter.operator->());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::reference detail::array_line_iterator<type,dim,device>::operator [] ( difference_type offset ) const
{
    return static_cast<reference>(iter.operator[](offset));
}

template < class type, int dim, class device >
constexpr std::span<detail::array_upper<type,dim-1,device>>::iterator detail::array_line_iterator<type,dim,device>::base ( ) const
{
    return iter;
}

template < class type, int dim, class device >
constexpr bool operator == ( detail::array_line_iterator<type,dim,device> left, detail::array_line_iterator<type,dim,device> right )
{
    return left.base() == right.base();
}

template < class type, int dim, class device >
constexpr std::strong_ordering operator <=> ( detail::array_line_iterator<type,dim,device> left, detail::array_line_iterator<type,dim,device> right )
{
    return left.base() <=> right.base();
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator + ( detail::array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::array_line_iterator<type,dim,device>(left.base() + right);
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator + ( std::ptrdiff_t left, detail::array_line_iterator<type,dim,device> right )
{
    return detail::array_line_iterator<type,dim,device>(left + right.base());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator - ( detail::array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::array_line_iterator<type,dim,device>(left.base() - right);
}

template < class type, int dim, class device >
constexpr std::ptrdiff_t operator - ( detail::array_line_iterator<type,dim,device> left, detail::array_line_iterator<type,dim,device> right )
{
    return left.base() - right.base();
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator += ( detail::array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    return left = detail::array_line_iterator<type,dim,device>(left.base() + right);
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator -= ( detail::array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    return left = detail::array_line_iterator<type,dim,device>(left.base() - right);
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator ++ ( detail::array_line_iterator<type,dim,device>& left )
{
    return left = detail::array_line_iterator<type,dim,device>(++left.base());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator ++ ( detail::array_line_iterator<type,dim,device>& left, int )
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator -- ( detail::array_line_iterator<type,dim,device>& left )
{
    return left = detail::array_line_iterator<type,dim,device>(--left.base());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator -- ( detail::array_line_iterator<type,dim,device>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::const_array_line_iterator ( std::span<detail::array_upper<type,dim-1,device>>::iterator init_iter )
    extends iter ( init_iter )
{

}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::reference detail::const_array_line_iterator<type,dim,device>::operator * ( ) const
{
    return static_cast<reference>(iter.operator*());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::pointer detail::const_array_line_iterator<type,dim,device>::operator -> ( ) const
{
    return static_cast<pointer>(iter.operator->());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::reference detail::const_array_line_iterator<type,dim,device>::operator [] ( difference_type offset ) const
{
    return static_cast<reference>(iter.operator[](offset));
}

template < class type, int dim, class device >
constexpr std::span<detail::array_upper<type,dim-1,device>>::iterator detail::const_array_line_iterator<type,dim,device>::base ( ) const
{
    return iter;
}

template < class type, int dim, class device >
constexpr bool operator == ( detail::const_array_line_iterator<type,dim,device> left, detail::const_array_line_iterator<type,dim,device> right )
{
    return left.base() == right.base();
}

template < class type, int dim, class device >
constexpr std::strong_ordering operator <=> ( detail::const_array_line_iterator<type,dim,device> left, detail::const_array_line_iterator<type,dim,device> right )
{
    return left.base() <=> right.base();
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator + ( detail::const_array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::const_array_line_iterator<type,dim,device>(left.base() + right);
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator + ( std::ptrdiff_t left, detail::const_array_line_iterator<type,dim,device> right )
{
    return detail::const_array_line_iterator<type,dim,device>(left + right.base());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator - ( detail::const_array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::const_array_line_iterator<type,dim,device>(left.base() - right);
}

template < class type, int dim, class device >
constexpr std::ptrdiff_t operator - ( detail::const_array_line_iterator<type,dim,device> left, detail::const_array_line_iterator<type,dim,device> right )
{
    return left.base() - right.base();
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator += ( detail::const_array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    return left = detail::const_array_line_iterator<type,dim,device>(left.base() + right);
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator -= ( detail::const_array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    return left = detail::const_array_line_iterator<type,dim,device>(left.base() - right);
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator ++ ( detail::const_array_line_iterator<type,dim,device>& left )
{
    return left = detail::const_array_line_iterator<type,dim,device>(++left.base());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator ++ ( detail::const_array_line_iterator<type,dim,device>& left, int )
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator -- ( detail::const_array_line_iterator<type,dim,device>& left )
{
    return left = detail::const_array_line_iterator<type,dim,device>(--left.base());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator -- ( detail::const_array_line_iterator<type,dim,device>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}

