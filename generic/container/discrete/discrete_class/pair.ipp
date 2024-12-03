#pragma once

/// Class pair

// Core

template < class type1, class type2 >
constexpr pair<type1,type2>::pair ( type1 init_x, type2 init_y )
    extends x ( std::forward<decltype(init_x)>(init_x) ),
            y ( std::forward<decltype(init_y)>(init_y) )
{

}

template < class type1, class type2 >
constexpr type1& pair<type1,type2>::key ( )
{
    return x;
}


template < class type1, class type2 >
constexpr const type1& pair<type1,type2>::key ( ) const
{
    return x;
}

template < class type1, class type2 >
constexpr type2& pair<type1,type2>::value ( )
{
    return y;
}

template < class type1, class type2 >
constexpr const type2& pair<type1,type2>::value ( ) const
{
    return y;
}

// Conversion

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( const pair<type3,type4>& cvt )
    requires std::convertible_to<type3,type1> and std::convertible_to<type4,type2> but
             ( not std::same_as<type1,type3> or not std::same_as<type2,type4> )
    extends x ( type1 ( cvt.key()   ) ),
            y ( type2 ( cvt.value() ) )
{

}

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( const pair<type3,type4>& cvt )
    requires std::constructible_from<type1,type3> and std::constructible_from<type2,type4> but
             ( not std::convertible_to<type3,type1> or not std::convertible_to<type4,type2> )
    extends x ( type1 ( cvt.key()   ) ),
            y ( type2 ( cvt.value() ) )
{

}



// For map_pair

template < class type1, class type2 >
template < class type3, class type4 >
constexpr pair<type1,type2>::pair ( map_pair_tag, pair<type3,type4>&& cvt )
    requires std::same_as<decay<type1>,decay<type3>> and
             std::same_as<decay<type2>,decay<type4>>
    extends x ( std::move ( cvt.key()   ) ),
            y ( std::move ( cvt.value() ) )
{

}