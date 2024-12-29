#pragma once

template < float_type type >
class opencl::uniform_real_distribution
    extends public boost::compute::uniform_real_distribution<type>
{
    private: // Typedef
        using base = boost::compute::uniform_real_distribution<type>;

    public:
        using base::base;
        type operator() ( auto& random_engine )
        {
            let result = boost::compute::vector<type>(1);
            base::generate(result.begin(), result.end(), random_engine, opencl::execution_context.get_command_queue());
            return type(result[0]);
        } 
}; 