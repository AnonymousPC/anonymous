template < class base >
std::size_t detail::tbb_container<base>::size ( ) const
{
    if constexpr ( requires { base::size(); } )
        return base::size();
    else
        return base::unsafe_size();
}

template < class base >
void detail::tbb_container<base>::pop ( )
{
    auto poped = base::value_type();

    bool success = base::try_pop(poped);
    if ( not success )
        throw value_error("pop failed (with empty() = true)");
}