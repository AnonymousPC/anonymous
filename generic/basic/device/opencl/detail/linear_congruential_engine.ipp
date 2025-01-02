#pragma once

template < unsigned_int_type type >
class opencl::linear_congruential_engine
    extends public boost::compute::linear_congruential_engine<type>
{
    private: // Typedef
        using base = boost::compute::linear_congruential_engine<type>;

    public: // Core
        using base::base;
        linear_congruential_engine ( auto&&... args )
            requires constructible_from<base,boost::compute::command_queue&,decltype(args)...>
            extends base ( opencl::execution_context.get_command_queue(), std::forward<decltype(args)>(args)... )
        {
            
        }

    public: // Member
        void seed ( auto&&... args )
        {
            base::seed(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue());
            opencl::execution_context.get_command_queue().finish();
        }

        type operator() ( )
        {
            let result = boost::compute::vector<type>(1);
            base::generate(result.begin(), result.end(), opencl::execution_context.get_command_queue());
            opencl::execution_context.get_command_queue().finish();
            return type(result[0]);
        }

        void discard ( auto&&... args )
        {
            base::discard(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue());
            opencl::execution_context.get_command_queue().finish();
        }

        constexpr static type min ( )
        {
            return 0;
        }

        constexpr static type max ( )
        {
            return std::numeric_limits<type>::max(); // The source code of boost::compute always implicitly mod 2^sizeof(type).
        }
};
