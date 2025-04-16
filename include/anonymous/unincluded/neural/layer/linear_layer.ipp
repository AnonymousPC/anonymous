#pragma once

#define weights self[1c]
#define bias    self[2c]

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr linear_layer<type1,type2>::linear_layer ( int input_size, int output_size )
    extends tuple<matrix<common_type<typename type1::value_type,typename type2::value_type>>,
                  vector<common_type<typename type1::value_type,typename type2::value_type>>>
                ( matrix<common_type<typename type1::value_type,typename type2::value_type>> ( output_size, input_size ),
                  vector<common_type<typename type1::value_type,typename type2::value_type>> ( output_size ) )
{

}





template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename linear_layer<type1,type2>::output_type linear_layer<type1,type2>::forward ( const input_type& inputs ) const
{
    return weights * inputs + bias;
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename linear_layer<type1,type2>::batch_output_type linear_layer<type1,type2>::linear_layer::forward ( const batch_input_type& inputs ) const
{
    return transpose(weights * transpose(inputs)).each([&] (auto& outputs) { outputs += bias; }); // ( weights * inputs[column-major]] ) [[=> column-major]] + bias[[broadcast]].
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename linear_layer<type1,type2>::output_type linear_layer<type1,type2>::linear_layer::forward ( input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.forward(std::move(inputs)));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename linear_layer<type1,type2>::batch_output_type linear_layer<type1,type2>::linear_layer::forward ( batch_input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.forward(std::move(inputs)));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename linear_layer<type1,type2>::input_type linear_layer<type1,type2>::backward ( const output_type& losses, optimizer_type auto& optimizer )
{
    auto& inputs = optimizer.template forward<input_type>();

    auto grad_weights = losses * transpose(inputs);
    auto grad_bias    = losses;
    auto grad_layer   = transpose(weights) * losses;

    weights -= optimizer.backward(weights, grad_weights);
    bias    -= optimizer.backward(weights, grad_bias);

    return grad_layer;
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename linear_layer<type1,type2>::batch_input_type linear_layer<type1,type2>::backward ( const batch_output_type& losses, optimizer_type auto& optimizer )
{
    auto& inputs = optimizer.template forward<batch_input_type>();

    auto grad_weights = transpose(losses) * inputs;                        // losses[[column-major]] * transpose(inputs[[column-major]]).
    auto grad_bias    = losses.template sum<1>();                          // losses[[column-major]] * array<value_type,-1>{1, 1, 1...}.
    auto grad_layer   = transpose(transpose(weights) * transpose(losses)); // ( transpose(weights) * losses[[column-major]] ) [[=> column-major]].

    weights -= optimizer.backward(weights, grad_weights);
    bias    -= optimizer.backward(bias,    grad_bias);

    return grad_layer;
}


#undef weights
#undef bias