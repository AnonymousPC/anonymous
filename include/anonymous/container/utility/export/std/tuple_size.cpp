namespace detail
{
    template < class input_type, int count = 1 >
    constexpr size_t tuple_size_helper = []
        {
            if constexpr ( requires ( input_type s ) { s.key(); s.value(); } )
                return 2;
            else if constexpr ( requires ( input_type s ) { s.template value<count>(); } )
                return tuple_size_helper<input_type,count+1>;
            else
                return count - 1;
        } ();
    
} // namespace detail


template < anonymous::structure input_type >
struct tuple_size<input_type>
{
    constexpr static const size_t value = detail::tuple_size_helper<input_type>;
};

