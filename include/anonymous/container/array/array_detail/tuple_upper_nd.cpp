template < class type, int dim, class device >
    requires ( dim >= 2 )
template < auto attr, int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> detail::tuple_upper<type,dim,device>::value ( const auto& shp, const int_type auto&... offsets )
{
    static_assert ( dim2 >= 1 and dim2 <= dim );
    if constexpr ( dim2 == dim )
        return std::span(vct.data() + detail::view_offset_begin<attr>(shp, offsets...),
                         vct.data() + detail::view_offset_end  <attr>(shp, offsets...));
    else
        return vct_other.template value<attr,dim2>(shp, offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < auto attr, int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> detail::tuple_upper<type,dim,device>::value ( const auto& shp, const int_type auto&... offsets ) const
{
    static_assert ( dim2 >= 1 and dim2 <= dim );
    if constexpr ( dim2 == dim )
        return std::span(const_cast<detail::array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_begin<attr>(shp, offsets...)),
                         const_cast<detail::array_upper<type,dim2,device>*>(vct.data() + detail::view_offset_end  <attr>(shp, offsets...)));
    else
        return vct_other.template value<attr,dim2>(shp, offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr detail::tuple_upper<type,dim,device>& detail::tuple_upper<type,dim,device>::clear ( )
{
    vct.clear();
    vct_other.clear();
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < auto attr >
constexpr detail::tuple_upper<type,dim,device>& detail::tuple_upper<type,dim,device>::resize ( const auto& shp, array<type,dim+1,device>& arr )
{
    auto s = 1;
    if constexpr ( attr == rows_attribute )
        for_constexpr<1,shp.size()-dim>([&] <int index> { s *= shp[index]; });
    else if constexpr ( attr == columns_attribute )
        for_constexpr<dim+1,shp.size()>([&] <int index> { s *= shp[index]; });
    else
        static_assert(false, "unknown attribute");
    vct.resize(s);
    for ( int i in range(0, s-1) )
        vct[i] = detail::array_upper<type,dim,device>(arr, attr, i);
    vct_other.template resize<attr>(shp, vct);
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < auto attr >
constexpr detail::tuple_upper<type,dim,device>& detail::tuple_upper<type,dim,device>::resize ( const auto& shp, std::vector<detail::array_upper<type,dim+1,device>>& arrs )
{
    auto s = 1;
    if constexpr ( attr == rows_attribute )
        for_constexpr<1,shp.size()-dim>([&] <int index> { s *= shp[index]; });
    else if constexpr ( attr == columns_attribute )
        for_constexpr<dim+1,shp.size()>([&] <int index> { s *= shp[index]; });
    else
        static_assert(false, "unknown attribute");
    vct.resize(s);
    [[assume(s % arrs.size() == 0)]];
    auto ck = s / arrs.size(); // chunk.
    for ( int i in range(0, int(arrs.size()-1)) )
        for ( int j in range(0, int(ck-1)) )
            vct[i*ck+j] = detail::array_upper<type,dim,device>(static_cast<array<type,dim+1,device>&>(arrs[i]), attr, j);
    vct_other.template resize<attr>(shp, vct);
    return self;
}