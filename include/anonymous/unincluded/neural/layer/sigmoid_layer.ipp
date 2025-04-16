#pragma once

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::output_type sigmoid_layer<type1,type2>::forward ( const input_type& inputs ) const
{
    if constexpr ( input_type::dimension() == 1 )
        return output_type(inputs.size(), [&] (int i) { return 1 / ( 1 + exp(-inputs[i]) ); });

    else if constexpr ( input_type::dimension() >= 2 )
    {
        output_type result = inputs;
        result.flatten().transform([] (const auto& x) { return 1 / ( 1 + exp(-x) ); });
        return result;
    }
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::batch_output_type sigmoid_layer<type1,type2>::forward ( const batch_input_type& inputs ) const
{
    return batch_output_type(inputs.row(), [&] (int i) { return self.forward(inputs[i]); });
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::output_type sigmoid_layer<type1,type2>::forward ( input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.forward(std::move(inputs)));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::batch_output_type sigmoid_layer<type1,type2>::forward ( batch_input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.forward(std::move(inputs)));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::input_type sigmoid_layer<type1,type2>::backward ( const output_type& losses, optimizer_type auto& optimizer )
{
    auto& inputs = optimizer.template forward<input_type>();
    return self.backward_one_sample(losses, inputs);
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::batch_input_type sigmoid_layer<type1,type2>::backward ( const batch_output_type& losses, optimizer_type auto& optimizer )
{
    auto& inputs = optimizer.template forward<batch_input_type>();
    return batch_input_type(inputs.row(), [&] (int i) { return self.backward_one_sample(losses[i], inputs[i]); });
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::input_type sigmoid_layer<type1,type2>::backward ( const bce_loss& losses, optimizer_type auto& /*optimizer*/ )
{
    return losses.from() - losses.to(); // Combine sigmoid_layer with bce_loss will boost!
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename sigmoid_layer<type1,type2>::batch_input_type sigmoid_layer<type1,type2>::backward ( const batch_bce_loss& losses, optimizer_type auto& /*optimizer*/ )
{
    return losses.from() - losses.to(); // Combine sigmoid_layer with bce_loss will boost!
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr auto sigmoid_layer<type1,type2>::backward_one_sample ( const auto& losses, auto& inputs )
{
    auto outputs = self.forward(inputs);

    if constexpr ( inputs.dimension() == 1 )
        return input_type(inputs.size(), [&] (int i) { return losses[i] * outputs[i] * ( 1 - outputs[i] ); });

    else if constexpr ( inputs.dimension() >= 2 )
    {
        auto result = input_type().resize(inputs.shape());
        for ( int i in range(result.size()) )
            result.flatten()[i] = losses.flatten()[i] * outputs.flatten()[i] * ( 1 - outputs.flatten()[i] );
        return result;
    }
}