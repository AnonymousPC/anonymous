template < class type1, class type2 >
constexpr expected<type1,type2>::expected ( type1 init )
    extends base ( std::move(init) )
{

}

template < class type1, class type2 >
constexpr expected<type1,type2>::expected ( type2 init )
    extends base ( std::move(init) )
{

}

template < class type1, class type2 >
constexpr expected<type1,type2>::value_reference expected<type1,type2>::value ( )
{
    if ( index() == 1 ) [[likely]]
        return base::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type2), typeid(type1));
}

template < class type1, class type2 >
constexpr expected<type1,type2>::const_value_reference expected<type1,type2>::value ( ) const
{
    if ( index() == 1 ) [[likely]]
        return base::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type2), typeid(type1));
}

template < class type1, class type2 >
constexpr expected<type1,type2>::error_reference expected<type1,type2>::error ( )
{
    if ( index() == 2 ) [[likely]]
        return base::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type1), typeid(type2));
}

template < class type1, class type2 >
constexpr expected<type1,type2>::const_error_reference expected<type1,type2>::error ( ) const
{
    if ( index() == 2 ) [[likely]]
        return base::value();
    else
        throw type_error("bad expected access (with type() = {}, access = {})", typeid(type1), typeid(type2));
}

template < class type1, class type2 >
constexpr int expected<type1,type2>::index ( ) const
{
    return base::has_value() ? 1 : 2;
}

template < class type1, class type2 >
constexpr const std::type_info& expected<type1,type2>::type ( ) const
{
    return base::has_value() ? typeid(type1) : typeid(type2);
}