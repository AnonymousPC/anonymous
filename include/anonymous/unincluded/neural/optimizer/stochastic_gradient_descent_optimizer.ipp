#pragma once

template < layer_type type >
constexpr float& stochastic_gradient_descent_optimizer<type>::learning_rate ( )
{
    return lr;
}

template < layer_type type >
constexpr float& stochastic_gradient_descent_optimizer<type>::momentum ( )
{
    return mmt;
}

template < layer_type type >
constexpr float& stochastic_gradient_descent_optimizer<type>::dampening ( )
{
    return dmp;
}

template < layer_type type >
constexpr float& stochastic_gradient_descent_optimizer<type>::weight_decay ( )
{
    return wd;
}

template < layer_type type >
constexpr bool& stochastic_gradient_descent_optimizer<type>::nesterov ( )
{
    return nst;
}

template < layer_type type >
template < class param_type >
constexpr const param_type& stochastic_gradient_descent_optimizer<type>::forward ( )
    requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>
{
    if constexpr ( std::same_as<param_type,input_type> )
        return self.history_inputs;

    else if constexpr ( std::same_as<param_type,batch_input_type> )
        return self.history_batch_inputs;
}

template < layer_type type >
template < class param_type >
constexpr const param_type& stochastic_gradient_descent_optimizer<type>::forward ( param_type inputs )
    requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>
{
    if constexpr ( std::same_as<param_type,input_type> )
        return self.history_inputs = std::move(inputs);

    else if constexpr ( std::same_as<param_type,batch_input_type> )
        return self.history_batch_inputs = std::move(inputs);
}

template < layer_type type >
template < class param_type >
constexpr param_type stochastic_gradient_descent_optimizer<type>::backward ( const param_type& params, const param_type& losses )
    requires aux::same_as_one_of_tuple_value_type<param_type,type>
{
    let& velocity = history_updates[constexpr_index<aux::index_of_same_type_in_tuple_value_types<param_type,type>>()];

    let grads = losses + weight_decay() * params;
    velocity = not velocity.empty() ? momentum() * velocity + ( 1 - dampening() ) * grads otherwise
                                                              ( 1 - dampening() ) * grads;

    if ( not nesterov() )
        return learning_rate() * velocity;
    else
        return learning_rate() * ( momentum() * velocity + grads );
}