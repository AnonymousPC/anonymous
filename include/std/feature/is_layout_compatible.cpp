export module std.feature.is_layout_compatible;

#ifndef __cpp_lib_is_layout_compatible

export namespace std
{
    template < class type1, class type2 >
    struct is_layout_compatible
    {
        constexpr static const bool value = sizeof(type1) == sizeof(type2);
    };
}

#endif
