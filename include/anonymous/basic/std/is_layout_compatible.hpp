template < class type1, class type2 >
struct is_layout_compatible
{
    constexpr static const bool value = sizeof(type1) == sizeof(type2);
};