template < array_type type1, array_type type2 >
class linear_layer;


template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
class linear_layer<type1,type2>
    extends public tuple<matrix<common_type<typename type1::value_type,typename type2::value_type>>,
                         vector<common_type<typename type1::value_type,typename type2::value_type>>>
{
    public: // Typedef
        using  input_type        = type1;
        using  batch_input_type  = array<typename input_type ::value_type,input_type::dimension()+1>;
        using  output_type       = type2;
        using  batch_output_type = array<typename output_type::value_type,output_type::dimension()+1>;
        struct layer_concept { };

    public: // Core
        constexpr linear_layer ( ) = default;
        constexpr linear_layer ( int, int );

    public: // Interface
        constexpr output_type       forward  ( const input_type&                              ) const;
        constexpr batch_output_type forward  ( const batch_input_type&                        ) const;
        constexpr output_type       forward  (       input_type,         optimizer_type auto& ) const;
        constexpr batch_output_type forward  (       batch_input_type,   optimizer_type auto& ) const;
        constexpr input_type        backward ( const output_type&,       optimizer_type auto& );
        constexpr batch_input_type  backward ( const batch_output_type&, optimizer_type auto& );
};

#include "linear_layer.cpp"