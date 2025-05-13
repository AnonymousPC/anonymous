#include "detail/view_offset.cpp"

template < class type, class device >
template < auto attr, int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> detail::array_uppers<type,1,device>::value ( const auto& shp, const int_type auto&... offsets )
{
    static_assert ( dim2 == 1 );
    return std::span(vct.data() + detail::view_offset_begin<attr>(shp, offsets...),
                     vct.data() + detail::view_offset_end  <attr>(shp, offsets...));
}

template < class type, class device >
template < auto attr, int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> detail::array_uppers<type,1,device>::value ( const auto& shp, const int_type auto&... offsets ) const
{
    static_assert ( dim2 == 1 );
    return std::span(const_cast<detail::array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_begin<attr>(shp, offsets...)),
                     const_cast<detail::array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_end  <attr>(shp, offsets...)));
}

template < class type, class device >
constexpr detail::array_uppers<type,1,device>& detail::array_uppers<type,1,device>::clear ( )
{
    vct.clear();
    return self;
}

template < class type, class device >
template < auto attr >
constexpr detail::array_uppers<type,1,device>& detail::array_uppers<type,1,device>::resize ( const auto& shp, array<type,2,device>& arr )
{
    auto s = 1;
    if constexpr ( attr == rows_attribute )
        for_constexpr<1,shp.size()-1>([&] <int index> { s *= shp[index]; });
    else if constexpr ( attr == columns_attribute )
        for_constexpr<2,shp.size()  >([&] <int index> { s *= shp[index]; });
    else
        static_assert(false, "unknown attribute");
    vct.resize(s);
    for ( int i in range(0, s-1) ) 
        vct[i] = detail::array_upper<type,1,device>(arr, attr, i);
    return self;
}

template < class type, class device >
template < auto attr >
constexpr detail::array_uppers<type,1,device>& detail::array_uppers<type,1,device>::resize ( const auto& shp, std::vector<detail::array_upper<type,2,device>>& arrs )
{
    auto s = 1;
    if constexpr ( attr == rows_attribute )
        for_constexpr<1,shp.size()-1>([&] <int index> { s *= shp[index]; });
    else if constexpr ( attr == columns_attribute )
        for_constexpr<2,shp.size()  >([&] <int index> { s *= shp[index]; });
    else
        static_assert(false, "unknown attribute");
    vct.resize(s);
    [[assume(s % arrs.size() == 0)]];
    auto ck = s / arrs.size(); // chunk.
    for ( int i in range(0, int(arrs.size()-1)) )
        for ( int j in range(0, int(ck-1)))
            vct[i*ck+j] = detail::array_upper<type,1,device>(static_cast<array<type,2,device>&>(arrs[i]), attr, j);
    return self;
}
