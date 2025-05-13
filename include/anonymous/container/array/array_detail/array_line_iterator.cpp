template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::array_line_iterator ( std::span<detail::array_upper<type,dim-1,device>>::iterator init )
    extends std::span<detail::array_upper<type,dim-1,device>>::iterator ( init )
{

}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::reference detail::array_line_iterator<type,dim,device>::operator * ( ) const
{
    return static_cast<reference>(std::span<detail::array_upper<type,dim-1,device>>::iterator::operator*());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::pointer detail::array_line_iterator<type,dim,device>::operator -> ( ) const
{
    return static_cast<pointer>(std::span<detail::array_upper<type,dim-1,device>>::iterator::operator->());
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>::reference detail::array_line_iterator<type,dim,device>::operator [] ( difference_type offset ) const
{
    return static_cast<reference>(std::span<detail::array_upper<type,dim-1,device>>::iterator::operator[](offset));
}

template < class type, int dim, class device >
constexpr bool operator == ( detail::array_line_iterator<type,dim,device> left, detail::array_line_iterator<type,dim,device> right )
{
    return static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) == static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right);
}

template < class type, int dim, class device >
constexpr std::strong_ordering operator <=> ( detail::array_line_iterator<type,dim,device> left, detail::array_line_iterator<type,dim,device> right )
{
    return static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) <=> static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right);
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator + ( detail::array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::array_line_iterator<type,dim,device>(static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) + right);
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator + ( std::ptrdiff_t left, detail::array_line_iterator<type,dim,device> right )
{
    return detail::array_line_iterator<type,dim,device>(left + static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right));
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator - ( detail::array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::array_line_iterator<type,dim,device>(static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) - right);
}

template < class type, int dim, class device >
constexpr std::ptrdiff_t operator - ( detail::array_line_iterator<type,dim,device> left, detail::array_line_iterator<type,dim,device> right )
{
    return static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) - static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right);
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator += ( detail::array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left) += right;
    return left;
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator -= ( detail::array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left) -= right;
    return left;
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device>& operator ++ ( detail::array_line_iterator<type,dim,device>& left )
{
    ++static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left);
    return left;
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
    --static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left);
    return left;
}

template < class type, int dim, class device >
constexpr detail::array_line_iterator<type,dim,device> operator -- ( detail::array_line_iterator<type,dim,device>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::const_array_line_iterator ( std::span<detail::array_upper<type,dim-1,device>>::iterator init )
    extends std::span<detail::array_upper<type,dim-1,device>>::iterator ( init )
{

}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::reference detail::const_array_line_iterator<type,dim,device>::operator * ( ) const
{
    return static_cast<reference>(std::span<detail::array_upper<type,dim-1,device>>::iterator::operator*());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::pointer detail::const_array_line_iterator<type,dim,device>::operator -> ( ) const
{
    return static_cast<pointer>(std::span<detail::array_upper<type,dim-1,device>>::iterator::operator->());
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>::reference detail::const_array_line_iterator<type,dim,device>::operator [] ( difference_type offset ) const
{
    return static_cast<reference>(std::span<detail::array_upper<type,dim-1,device>>::iterator::operator[](offset));
}

template < class type, int dim, class device >
constexpr bool operator == ( detail::const_array_line_iterator<type,dim,device> left, detail::const_array_line_iterator<type,dim,device> right )
{
    return static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) == static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right);
}

template < class type, int dim, class device >
constexpr std::strong_ordering operator <=> ( detail::const_array_line_iterator<type,dim,device> left, detail::const_array_line_iterator<type,dim,device> right )
{
    return static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) <=> static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right);
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator + ( detail::const_array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::const_array_line_iterator<type,dim,device>(static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) + right);
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator + ( std::ptrdiff_t left, detail::const_array_line_iterator<type,dim,device> right )
{
    return detail::const_array_line_iterator<type,dim,device>(left + static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right));
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator - ( detail::const_array_line_iterator<type,dim,device> left, std::ptrdiff_t right )
{
    return detail::const_array_line_iterator<type,dim,device>(static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) - right);
}

template < class type, int dim, class device >
constexpr std::ptrdiff_t operator - ( detail::const_array_line_iterator<type,dim,device> left, detail::const_array_line_iterator<type,dim,device> right )
{
    return static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(left) - static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator>(right);
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator += ( detail::const_array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left) += right;
    return left;
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator -= ( detail::const_array_line_iterator<type,dim,device>& left, std::ptrdiff_t right )
{
    static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left) -= right;
    return left;
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device>& operator ++ ( detail::const_array_line_iterator<type,dim,device>& left )
{
    ++static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left);
    return left;
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
    --static_cast<typename std::span<detail::array_upper<type,dim-1,device>>::iterator&>(left);
    return left;
}

template < class type, int dim, class device >
constexpr detail::const_array_line_iterator<type,dim,device> operator -- ( detail::const_array_line_iterator<type,dim,device>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}

