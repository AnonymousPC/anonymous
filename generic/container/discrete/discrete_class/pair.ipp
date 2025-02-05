#pragma once

template < class type1, class type2 >
constexpr pair<type1,type2>::pair ( type1 k, type2 v )
    extends std::pair<type1,type2>(std::move(k), std::move(v))
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