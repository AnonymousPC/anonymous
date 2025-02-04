#pragma once

#define templates            template < class container, class iterate_type >
#define collection_algo      collection_algo<container,iterate_type>
#define derive_of_self       static_cast<container&>(self)
#define const_derive_of_self static_cast<const container&>(self)

// Abbreviation

templates
constexpr int collection_algo::size ( ) const
{
    return const_derive_of_self.size();
}

templates
constexpr bool collection_algo::empty ( ) const
{
    return const_derive_of_self.empty();
}

templates
constexpr decltype(auto) collection_algo::begin ( )
{
    return derive_of_self.begin();
}

templates
constexpr decltype(auto) collection_algo::begin ( ) const
{
    return const_derive_of_self.begin();
}

templates
constexpr decltype(auto) collection_algo::end ( )
{
    return derive_of_self.end();
}

templates
constexpr decltype(auto) collection_algo::end ( ) const
{
    return const_derive_of_self.end();
}



// Algorithm

templates
constexpr bool collection_algo::all ( unary_pred<iterate_type> auto pred ) const
{
    return std::all_of ( begin(), end(), pred );
}

templates
constexpr int collection_algo::count ( unary_pred<iterate_type> auto pred ) const
{
    return std::count_if ( begin(), end(), pred );
}

templates
constexpr bool collection_algo::exist ( unary_pred<iterate_type> auto pred ) const
{
    return std::any_of ( begin(), end(), pred );
}

templates
constexpr bool collection_algo::none ( unary_pred<iterate_type> auto pred ) const
{
    return std::none_of ( begin(), end(), pred );
}

templates
constexpr container& collection_algo::each ( std::invocable<iterate_type&> auto op )
{
    std::for_each ( begin(), end(), op );
    return derive_of_self;
}

templates
constexpr const container& collection_algo::each ( std::invocable<iterate_type> auto op ) const
{
    std::for_each ( begin(), end(), op );
    return const_derive_of_self;
}

templates
constexpr auto collection_algo::sum ( ) const
    requires std::default_initializable<iterate_type> and addable<iterate_type>
{
    return std::accumulate ( begin(), end(), iterate_type() );
}

templates
constexpr auto collection_algo::sum ( std::invocable<iterate_type> auto op ) const
    requires std::default_initializable<invoke_result<decltype(op),iterate_type>> and addable<invoke_result<decltype(op),iterate_type>>
{
    using result_type = std::invoke_result<decltype(op),iterate_type>::type;
    return std::accumulate ( begin(), end(), result_type(), [&] ( const auto& a, const auto& b ) { return a + op(b); } );
}

templates
constexpr auto collection_algo::product ( ) const
    requires std::convertible_to<int,iterate_type> and multipliable<iterate_type>
{
    return std::accumulate ( begin(), end(), iterate_type(1), [] ( const auto& a, const auto& b ) { return a * b; } );
}

templates
constexpr auto collection_algo::product ( std::invocable<iterate_type> auto op ) const
    requires std::convertible_to<int,invoke_result<decltype(op),iterate_type>> and multipliable<invoke_result<decltype(op),iterate_type>>
{
    using result_type = std::invoke_result<decltype(op),iterate_type>::type;
    return std::accumulate ( begin(), end(), result_type(1), [&] ( const auto& a, const auto& b ) { return a * op(b); } );
}






#undef templates
#undef collection_algo
#undef derive_of_self
#undef const_derive_of_self