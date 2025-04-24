namespace anonymous::neural
{
    /// Concept
    template < class input_type > concept layer_type     = requires { typename input_type::layer_tag;     };
    template < class input_type > concept loss_type      = requires { typename input_type::loss_tag;      };
    template < class input_type > concept model_type     = requires { typename input_type::model_tag;     };
    template < class input_type > concept optimizer_type = requires { typename input_type::optimizer_tag; };

    /// Layer
    template < array_type type1, array_type type2 > class convolve_layer;
    template < array_type type1, array_type type2 > class linear_layer;
    template < array_type type1, array_type type2 > class max_pool_layer;
    template < array_type type1, array_type type2 > class relu_layer;
    template < array_type type1, array_type type2 > class sigmoid_layer;
    template < array_type type1, array_type type2 > class softmax_layer;

    /// Loss
    template < array_type type >                    class binary_cross_entropy_loss;
    template < array_type type >                    class cross_entropy_loss;
    template < array_type type >                    class mean_absolute_error_loss;
    template < array_type type >                    class mean_squared_error_loss;
    template < array_type type >                    using bce_loss = binary_cross_entropy_loss<type>;
    template < array_type type >                    using ce_loss  = cross_entropy_loss       <type>;
    template < array_type type >                    using mae_loss = mean_absolute_error_loss <type>;
    template < array_type type >                    using mse_loss = mean_squared_error_loss  <type>;

    /// Model
    template < layer_type... types >                class sequence_model;

    /// Optimizer
    template < layer_type... types >                class adaptive_moment_estimation_optimizer;
    template < layer_type... types >                class root_mean_square_propagation_optimizer;
    template < layer_type... types >                class stochastic_gradient_descent_optimizer;
    template < layer_type... types >                using adam    = adaptive_moment_estimation_optimizer  <types...>;
    template < layer_type... types >                using rmsprop = root_mean_square_propagation_optimizer<types...>;
    template < layer_type... types >                using sgd     = stochastic_gradient_descent_optimizer <types...>;

    /// Utility.Initialize
    constexpr array_type auto kaiming_normal_initialize  ( array_type auto, int_type   auto );
    constexpr array_type auto kaiming_uniform_initialize ( array_type auto, int_type   auto );
    constexpr array_type auto normal_initialize          ( array_type auto, float_type auto, float_type auto );
    constexpr array_type auto ones_initialize            ( array_type auto );
    constexpr array_type auto orthogonal_initialize      ( array_type auto );
    constexpr array_type auto sparse_initialize          ( array_type auto );
    constexpr array_type auto uniform_initialize         ( array_type auto, float_type auto, float_type auto );
    constexpr array_type auto xavier_normal_initialize   ( array_type auto, int_type   auto, int_type   auto );
    constexpr array_type auto xavier_uniform_initialize  ( array_type auto, int_type   auto, int_type   auto );
    constexpr array_type auto zeros_initialize           ( array_type auto );


    /// Include
    #include "layer/layer.hpp"
    #include "loss/loss.hpp"
    #include "model/model.hpp"
    #include "optimizer/optimizer.hpp"
    #include "utility/initialize/initialize.hpp"
}
