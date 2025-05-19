namespace detail
{
    template < class type > concept enable_container = derived_from<type,container_interface<type,range_value_type<type>,typename type::device_type>>;
    template < class type > concept enable_structure = derived_from<type,structure_interface<type>>;
}

template < class type > concept container        = forward_range<type> and copyable<type> and enable_container<type>;
template < class type > concept array_container  = container<type> and random_access_range<type> and requires { type::dimension(); };
template < class type > concept set_container    = container<type> and bidirectional_range<type> and requires { typename type::compare_type; };
template < class type > concept map_container    = container<type> and bidirectional_range<type> and requires { typename type::compare_type; typename type::key_type; typename type::value_type; };
template < class type > concept string_container = container<type> and contiguous_range   <type> and requires { type().c_str(); };

template < class type > concept structure        = requires { std::tuple_size<type>::value; } and enable_structure<type>;
template < class type > concept pair_structure   = structure<type> and ( tuple_size<type> == 2 ) and requires { typename type::key_type; typename type::value_type; };
template < class type > concept tuple_structure  = structure<type> and 