#pragma once

template < unsigned_int_type type >
class opencl::mersenne_twister_engine
    extends public boost::compute::mersenne_twister_engine<type>
{
    private: // Typedef
        using base = boost::compute::mersenne_twister_engine<type>;

    public: // Core
        using base::base;
        mersenne_twister_engine ( auto&&... args )
            requires std::constructible_from<base,boost::compute::command_queue&,decltype(args)...>
            extends base ( opencl::execution_context.get_command_queue(), std::forward<decltype(args)>(args)... )
        {

        }

    public: // Member
        void seed ( auto&&... args )
        {
            return base::seed(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue());
        }

        type operator() ( )
        {
            let result = boost::compute::vector<type>(1);
            base::generate(result.begin(), result.end(), opencl::execution_context.get_command_queue());
            return type(result[0]);
        }

        void discard ( auto&&... args )
        {
            return base::discard(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue());
        }
        
        constexpr static type min ( )
        {
            return 0;
        }

        constexpr static type max ( )
        {
            return std::numeric_limits<type>::max();
        }
};  