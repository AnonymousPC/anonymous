constexpr void swap ( array_type auto&& left, array_type auto&& right )
    requires ( left.dimension() == right.dimension() ) and
             std::same_as<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type> and
             std::swappable_with<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>
{
    constexpr bool left_is_view  = requires { &left .resize; } or requires { &left .template resize<1>; };
    constexpr bool right_is_view = requires { &right.resize; } or requires { &right.template resize<1>; };

    // left is not view and right is not view
    if constexpr ( not left_is_view and not right_is_view )
        std::swap ( left, right );
    else
    {
        #ifdef debug
            if ( left.shape() != right.shape() )
                throw value_error("cannot swap {} of shape {} with {} of shape {}: shape must be equal",
                                  not left_is_view  ? "array" : "array_view", left .shape(),
                                  not right_is_view ? "array" : "array_view", right.shape());
        #endif

        std::swap_ranges ( left.begin(), left.end(), right.begin() );
    }
}