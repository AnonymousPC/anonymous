#pragma once

/// Class map_pair

template < class type1, class type2 >
constexpr map_pair<type1,type2>::map_pair ( map_pair&& init )
    extends pair<const type1,type2> ( std::move ( const_cast<type1&>(init.key()) ), std::move ( init.value() ) )
{

}

template < class type1, class type2 >
constexpr map_pair<type1,type2>& map_pair<type1,type2>::operator = ( const map_pair& right )
{
    const_cast<type1&>(self.key()) = right.key();
    self.value() = std::move ( right.value() );
    return self;
}

template < class type1, class type2 >
constexpr map_pair<type1,type2>& map_pair<type1,type2>::operator = ( map_pair&& right )
{
    const_cast<type1&>(self.key()) = std::move ( const_cast<type1&>(right.key()) );
    self.value() = std::move ( right.value() );
    return self;
}

template < class type1, class type2 >
template < class type3, class type4 >
constexpr map_pair<type1,type2>::map_pair ( pair<type3,type4>&& cvt )
    requires std::same_as<decay<type1>,decay<type3>> and
             std::same_as<decay<type2>,decay<type4>>
    extends pair<const type1,type2> ( typename pair<const type1,type2>::map_pair_tag(), std::move(cvt) )
{

}