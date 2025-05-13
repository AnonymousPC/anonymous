namespace detail
{ 
    template < class type > 
    constexpr auto get_iterator_concept_tag ( )
    {
        if constexpr ( std::contiguous_iterator<type> )
            return std::contiguous_iterator_tag();
        else if constexpr ( std::random_access_iterator<type> )
            return std::random_access_iterator_tag();
        else if constexpr ( std::bidirectional_iterator<type> )
            return std::bidirectional_iterator_tag();
        else if constexpr ( std::input_iterator<type> )
            return std::input_iterator_tag();
        else
            static_assert(false, "no iterator_concept");
    }

    template < class type >
    using get_iterator_concept = decltype(get_iterator_concept_tag<type>());

    template < class type > 
    constexpr auto get_range_concept_tag ( )
    {
        if constexpr ( std::ranges::contiguous_range<type> )
            return std::contiguous_iterator_tag();
        else if constexpr ( std::ranges::random_access_range<type> )
            return std::random_access_iterator_tag();
        else if constexpr ( std::ranges::bidirectional_range<type> )
            return std::bidirectional_iterator_tag();
        else if constexpr ( std::ranges::input_range<type> )
            return std::input_iterator_tag();
        else
            static_assert(false, "no range_concept");
    }

    template < class type >
    using get_range_concept = decltype(get_range_concept_tag<type>());


    
} // namespace detail
