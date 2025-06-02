namespace detail
{
    template < class type >
    struct transpose_layout_of_helper;

    template < >
    struct transpose_layout_of_helper<std::layout_right>
    {
        using type = std::layout_left;
    };

    template < >
    struct transpose_layout_of_helper<std::layout_left>
    {
        using type = std::layout_right;
    };

    template < std::size_t padding >
    struct transpose_layout_of_helper<std::layout_right_padded<padding>>
    {
        using type = std::layout_left_padded<padding>;
    };

    template < std::size_t padding >
    struct transpose_layout_of_helper<std::layout_left_padded<padding>>
    {
        using type = std::layout_right_padded<padding>;
    };

    template < class type >
    using transpose_layout_of = transpose_layout_of_helper<type>::type;
    
} // namespace detail
