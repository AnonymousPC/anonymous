namespace detail
{
    template < class... types >
    struct array_deduction;
    
} // namespace detail


array ( auto... args ) -> array<typename detail::array_deduction<decltype(args)...>::value_type,
                                         detail::array_deduction<decltype(args)...>::dim>;