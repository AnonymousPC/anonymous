template < class... types >
    requires ( ( not tuple_type<types> ) and ... )
tuple ( types... ) -> tuple<types...>;

template < tuple_type type >
    requires ( tuple_size<type> == 1 )
tuple ( type ) -> tuple<typename type::template value_type<1>>;

template < tuple_type type >
    requires ( tuple_size<type> == 2 )
tuple ( type ) -> tuple<typename type::template value_type<1>,typename type::template value_type<2>>;

template < tuple_type type >
    requires ( tuple_size<type> == 3 )
tuple ( type ) -> tuple<typename type::template value_type<1>,typename type::template value_type<2>,typename type::template value_type<3>>;