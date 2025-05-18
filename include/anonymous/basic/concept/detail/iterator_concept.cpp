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
    
} // namespace detail
