#pragma once

template < class type1, class type2 >
constexpr pair<type1,type2>::pair ( type1 k, type2 v )
    extends std::pair<type1,type2>(std::move(k), std::move(v))
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
constexpr type1& pair<type1,type2>::key ( )
{
    return self.first;
}

template < class type1, class type2 >
constexpr const type1& pair<type1,type2>::key ( ) const
{
    return self.first;
}

template < class type1, class type2 >
constexpr type2& pair<type1,type2>::value ( )
{
    return self.second;
}

template < class type1, class type2 >
constexpr const type2& pair<type1,type2>::value ( ) const
{
    return self.second;
}