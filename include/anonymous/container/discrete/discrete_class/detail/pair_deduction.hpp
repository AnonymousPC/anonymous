template < class type1, class type2 >
pair ( type1, type2 ) -> pair<type1,type2>;

template < pair_type type >
pair ( type ) -> pair<typename type::key_type,typename type::value_type>;