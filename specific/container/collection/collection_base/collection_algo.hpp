#pragma once

template < class collection_type, class type, class device > // Type means the type in iterator, not key_type or value_type.
class collection_algo
{
    public: // Algorithm
        constexpr       bool             all     ( predicate<type>        auto    ) const;
        constexpr       int              count   ( predicate<type>        auto    ) const;
        constexpr       bool             exist   ( predicate<type>        auto    ) const;
        constexpr       bool             none    ( predicate<type>        auto    ) const;
        constexpr       collection_type& each    ( invocable<type&>       auto    );
        constexpr const collection_type& each    ( invocable<const type&> auto    ) const;
        constexpr       auto             sum     (                                ) const requires default_initializable<type>                             and plusable<type>;
        constexpr       auto             sum     ( invocable<type>        auto op ) const requires default_initializable<invoke_result<decltype(op),type>> and plusable<invoke_result<decltype(op),type>>;
        constexpr       auto             product (                                ) const requires convertible_to<int,type>                                and multipliable<type>;
        constexpr       auto             product ( invocable<type>        auto op ) const requires convertible_to<int,invoke_result<decltype(op),type>>    and multipliable<invoke_result<decltype(op),type>>;
};


#include "collection_algo.ipp"