template < class type1, class type2, class device >
constexpr expected<type1,type2,device>::expected ( type1 init )
    extends device::template expected<type1,type2> ( std::move(init) )
{

}

template < class type1, class type2, class device >
constexpr expected<type1,type2,device>::expected ( type2 init )
    extends device::template expected<type1,type2> ( std::move(init) )
{

}

template < class type1, class type2, class device >
constexpr expected<type1,type2,device>::value_reference expected<type1,type2,device>::value ( )
{
    if ( index() == 1 ) [[likely]]
        return device::template expected<type1,type2>::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type2), typeid(type1));
}

template < class type1, class type2, class device >
constexpr expected<type1,type2,device>::const_value_reference expected<type1,type2,device>::value ( ) const
{
    if ( index() == 1 ) [[likely]]
        return device::template expected<type1,type2>::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type2), typeid(type1));
}

template < class type1, class type2, class device >
constexpr expected<type1,type2,device>::error_reference expected<type1,type2,device>::error ( )
{
    if ( index() == 2 ) [[likely]]
        return device::template expected<type1,type2>::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type1), typeid(type2));
}

template < class type1, class type2, class device >
constexpr expected<type1,type2,device>::const_error_reference expected<type1,type2,device>::error ( ) const
{
    if ( index() == 2 ) [[likely]]
        return device::template expected<type1,type2>::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type1), typeid(type2));
}

template < class type1, class type2, class device >
constexpr int expected<type1,type2,device>::index ( ) const
{
    return device::template expected<type1,type2>::has_value() ? 1 : 2;
}

template < class type1, class type2, class device >
constexpr const std::type_info& expected<type1,type2,device>::type ( ) const
{
    return device::template expected<type1,type2>::has_value() ? typeid(type1) : typeid(type2);
}