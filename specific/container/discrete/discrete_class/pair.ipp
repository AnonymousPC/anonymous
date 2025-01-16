#pragma once

template < class type1, class type2 >
constexpr int pair<type1,type2>::size ( )
{
    return 2;
}

template < class type1, class type2 >
constexpr pair<type1,type2>::pair ( type1 init_x, type2 init_y )
    extends std::pair<type1,type2>(std::move(init_x), std::move(init_y))
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

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( const pair<type3,type4>& cvt )
    requires convertible_to<type3,type1> and convertible_to<type4,type2> but
             ( not same_as<type1,type3> or not same_as<type2,type4> )
    extends pair<type1,type2>(type1(cvt.key()), type2(cvt.value()))
{

}

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( const pair<type3,type4>& cvt )
    requires constructible_from<type1,type3> and constructible_from<type2,type4> but
             ( not convertible_to<type3,type1> or not convertible_to<type4,type2> )
    extends pair<type1,type2>(type1(cvt.key()), type2(cvt.value()))
{

}