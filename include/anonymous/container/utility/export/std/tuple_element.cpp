template < size_t index, anonymous::structure input_type >
struct tuple_element<index,input_type>
{
    using type = decltype([] 
        {
            if constexpr ( requires ( input_type s ) { s.key(); s.value(); } )
                if constexpr ( index == 0 )
                    return std::declval<input_type>().key();
                else if constexpr ( index == 1 )
                    return std::declval<input_type>().value();
                else 
                    static_assert(false, "index out of range");
            else
                if constexpr ( requires ( input_type s ) { s.template value<index+1>(); } )
                    return std::declval<input_type>().template value<index+1>();
                else
                    static_assert(false, "index out of range");
        } ());
};