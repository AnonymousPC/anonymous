#pragma once

namespace aux
{
    template < layer_type... types >
    constexpr bool chain_invocable;

    template < layer_type type >
    constexpr bool chain_invocable<type> = true;

    template < layer_type type1, layer_type type2, layer_type... types >
    constexpr bool chain_invocable<type1,type2,types...> = std::convertible_to<typename type1::output_type,typename type2::input_type> and chain_invocable<type2,types...>;
}

#include "sequence_model.hpp"