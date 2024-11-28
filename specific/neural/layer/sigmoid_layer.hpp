#pragma once

namespace aux
{
    template < class input_type, class array_type > concept bce_loss_type = std::same_as<input_type,bce_loss<array_type>>;
}




template < array_type type1, array_type type2 >
class sigmoid_layer;

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
class sigmoid_layer<type1,type2>
{
    public: // Typedef
        using  input_type        = type1;
        using  batch_input_type  = array<typename input_type::value_type,input_type::dimension()+1>;
        using  output_type       = type2;
        using  batch_output_type = array<typename output_type::value_type,output_type::dimension()+1>;
        using  bce_loss          = neural::bce_loss<output_type>;
        using  batch_bce_loss    = neural::bce_loss<batch_output_type>;
        struct layer_tag { };

    public: // Interface
        constexpr output_type       forward  ( const input_type&                              ) const;
        constexpr batch_output_type forward  ( const batch_input_type&                        ) const;
        constexpr output_type       forward  (       input_type,         optimizer_type auto& ) const;
        constexpr batch_output_type forward  (       batch_input_type,   optimizer_type auto& ) const;
        constexpr input_type        backward ( const output_type&,       optimizer_type auto& );
        constexpr batch_input_type  backward ( const batch_output_type&, optimizer_type auto& );
        constexpr input_type        backward ( const bce_loss&,          optimizer_type auto& );
        constexpr batch_input_type  backward ( const batch_bce_loss&,    optimizer_type auto& );

    private: // Auxiliary
        constexpr auto backward_one_sample ( const auto&, auto& );
};

#include "sigmoid_layer.ipp"