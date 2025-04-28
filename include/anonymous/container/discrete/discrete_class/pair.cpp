template < class type1, class type2, class device >
constexpr pair<type1,type2,device>::pair ( type1 k, type2 v )
    extends base ( std::move(k), std::move(v) )
{

}

template < class type1, class type2, class device >
constexpr pair<type1,type2,device>::pair ( const pair_type auto& cvt )
    requires convertible_to<cvt_key_type,key_type> and convertible_to<cvt_value_type,value_type>
    extends pair ( cvt.key(), cvt.value() )
{

}

template < class type1, class type2, class device >
constexpr pair<type1,type2,device>::key_reference pair<type1,type2,device>::key ( )
{
    return base::first;
}

template < class type1, class type2, class device >
constexpr pair<type1,type2,device>::const_key_reference pair<type1,type2,device>::key ( ) const
{
    return base::first;
}

template < class type1, class type2, class device >
constexpr pair<type1,type2,device>::value_reference pair<type1,type2,device>::value ( )
{
    return base::second;
}

template < class type1, class type2, class device >
constexpr pair<type1,type2,device>::const_value_reference pair<type1,type2,device>::value ( ) const
{
    return base::second;
}