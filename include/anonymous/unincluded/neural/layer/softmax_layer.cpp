#pragma once

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::output_type softmax_layer<type1,type2>::forward ( const input_type& inputs ) const
{
    auto total = inputs.template as_type<typename output_type::value_type>().sum([] (const auto& x) { return exp(x); });
    return output_type(inputs.size(), [&] (int i) { return exp(inputs[i]) / total; });
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::batch_output_type softmax_layer<type1,type2>::forward ( const batch_input_type& inputs ) const
{
    return batch_output_type(inputs.row(), [&] (int i) { return self.forward(inputs[i]); });
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::output_type softmax_layer<type1,type2>::forward ( input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.forward(std::move(inputs)));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::batch_output_type softmax_layer<type1,type2>::forward ( batch_input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.forward(std::move(inputs)));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::input_type softmax_layer<type1,type2>::backward ( const output_type& losses, optimizer_type auto& optimizer )
{
    auto& inputs = optimizer.template forward<input_type>();
    return self.backward_one_sample(losses, inputs);
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::batch_input_type softmax_layer<type1,type2>::backward ( const batch_output_type& losses, optimizer_type auto& optimizer )
{
    auto& inputs = optimizer.template forward<batch_input_type>();
    return batch_input_type(inputs.row(), [&] (int i) { return self.backward_one_sample(losses[i], inputs[i]); });
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::input_type softmax_layer<type1,type2>::backward ( const ce_loss& losses, optimizer_type auto& optimizer )
{
    return losses.from() - losses.to(); // Combine softmax_layer with ce_loss will boost!
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr typename softmax_layer<type1,type2>::batch_input_type softmax_layer<type1,type2>::backward ( const batch_ce_loss& losses, optimizer_type auto& optimizer )
{
    return losses.from() - losses.to(); // Combine softmax_layer with ce_loss will boost!
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and ( type1::dimension() == 1 ) and
             float_type<typename type2::value_type> and ( type2::dimension() == 1 )
constexpr auto softmax_layer<type1,type2>::backward_one_sample ( const auto& losses, auto& inputs )
{
    auto outputs  = self.forward(inputs);
    auto dot_prod = dot(outputs, losses);
    return input_type(inputs.size(), [&] (int i) { return outputs[i] * (losses[i] - dot_prod); });
}