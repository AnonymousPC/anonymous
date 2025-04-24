template < array_type type1, array_type type2 >
class softmax_layer;


template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
class softmax_layer<type1,type2>
{
    public: // Typedef
        using  input_type        = type1;
        using  batch_input_type  = array<typename input_type::value_type,input_type::dimension()+1>;
        using  output_type       = type2;
        using  batch_output_type = array<typename output_type::value_type,output_type::dimension()+1>;
        using  ce_loss           = neural::ce_loss<output_type>;
        using  batch_ce_loss     = neural::ce_loss<batch_output_type>;
        struct layer_tag { };

    public: // Interface
        constexpr output_type       forward  ( const input_type&                              ) const;
        constexpr batch_output_type forward  ( const batch_input_type&                        ) const;
        constexpr output_type       forward  (       input_type,         optimizer_type auto& ) const;
        constexpr batch_output_type forward  (       batch_input_type,   optimizer_type auto& ) const;
        constexpr input_type        backward ( const output_type&,       optimizer_type auto& );
        constexpr batch_input_type  backward ( const batch_output_type&, optimizer_type auto& );
        constexpr input_type        backward ( const ce_loss&,           optimizer_type auto& );
        constexpr batch_input_type  backward ( const batch_ce_loss&,     optimizer_type auto& );

    private: // Auxiliary
        constexpr auto backward_one_sample ( const auto&, auto& );
};

#include "softmax_layer.cpp"