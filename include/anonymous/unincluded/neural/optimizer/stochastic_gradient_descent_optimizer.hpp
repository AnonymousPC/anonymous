#pragma once

template < layer_type... types >
class stochastic_gradient_descent_optimizer;

template < layer_type type >
class stochastic_gradient_descent_optimizer<type>
    extends public type
{
    private: // Precondition
        static_assert ( not std::same_as<typename type::input_type,typename type::batch_input_type> );

    public: // Typedef
        using  input_type       = type::input_type;
        using  batch_input_type = type::batch_input_type;
        struct optimizer_tag { };

    private: // Data
        input_type       history_inputs       = {};
        batch_input_type history_batch_inputs = {};
        type             history_updates      = {};

        float lr  = 0.01;
        float mmt = 0;
        float dmp = 0;
        float wd  = 0;
        bool  nst = false;

    public: // Interface
        constexpr float& learning_rate ( );
        constexpr float& momentum      ( );
        constexpr float& dampening     ( );
        constexpr float& weight_decay  ( );
        constexpr bool&  nesterov      ( );

        template < class param_type > constexpr const param_type& forward  ( )                                      requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>;
        template < class param_type > constexpr const param_type& forward  ( param_type )                           requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>;
        template < class param_type > constexpr       param_type  backward ( const param_type&, const param_type& ) requires aux::same_as_one_of_tuple_value_type<param_type,type>;
};

template < layer_type... types >
class stochastic_gradient_descent_optimizer
    extends public tuple<stochastic_gradient_descent_optimizer<types>...>
{
    public: // Typedef
        struct optimizer_tag { };
};


#include "stochastic_gradient_descent_optimizer.ipp"