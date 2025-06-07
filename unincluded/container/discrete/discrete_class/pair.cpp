template < class type1, class type2 >
constexpr pair<type1,type2>::pair ( type1 k, type2 v )
    extends base ( std::move(k), std::move(v) )
{

}

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( const pair<type3,type4>& cvt )
    requires convertible_to<type3,type1> and convertible_to<type4,type2>
    extends pair ( type1(cvt.key()), type2(cvt.value()) )
{

}

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( const pair<type3,type4>& cvt )
    requires constructible_to<type3,type1> and constructible_to<type4,type2>
    extends pair ( type1(cvt.key()), type2(cvt.value()) )
{

}

template < class type1, class type2 >
constexpr pair<type1,type2>::key_reference pair<type1,type2>::key ( )
{
    return base::first;
}

template < class type1, class type2 >
constexpr pair<type1,type2>::const_key_reference pair<type1,type2>::key ( ) const
{
    return base::first;
}

template < class type1, class type2 >
constexpr pair<type1,type2>::value_reference pair<type1,type2>::value ( )
{
    return base::second;
}

template < class type1, class type2 >
constexpr pair<type1,type2>::const_value_reference pair<type1,type2>::value ( ) const
{
    return base::second;
}