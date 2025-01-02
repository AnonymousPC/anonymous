#pragma once

template < class type, class alloc >
class opencl::vector
    extends public boost::compute::vector<type,alloc>
{
    private: // Typedef
        using base = boost::compute::vector<type,alloc>;

    public: // Core
        /* boost::compute::vector<int>(10, 0, queue) failes, should use size_t(10) */
        using base::base;
        vector ( )                            noexcept = default;
        vector ( const vector&  )                      = default;
        vector (       vector&& )             noexcept = default;
        vector& operator = ( const vector&  )          = default;
        vector& operator = (       vector&& ) noexcept = default;
        vector ( auto&&... args ) requires       std::constructible_from<base,decltype(args)...,boost::compute::command_queue&>   extends base ( std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue() ) { }
        vector ( auto&&... args ) requires ( not std::constructible_from<base,decltype(args)...,boost::compute::command_queue&> ) extends base ( std::forward<decltype(args)>(args)...                                                ) { }
        vector ( int arg1, const convertible_to<type> auto& arg2 )                                                                extends base ( size_t(arg1), arg2,                    opencl::execution_context.get_command_queue() ) { }        

    public: // Member
        decltype(auto) resize        ( auto&&... args ) { return base::resize       (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) reserve       ( auto&&... args ) { return base::reserve      (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) shrink_to_fit ( auto&&... args ) { return base::shrink_to_fit(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) assign        ( auto&&... args ) { return base::assign       (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) push_back     ( auto&&... args ) { return base::push_back    (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) pop_back      ( auto&&... args ) { return base::pop_back     (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) insert        ( auto&&... args ) { return base::insert       (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
        decltype(auto) erase         ( auto&&... args ) { return base::erase        (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); opencl::execution_context.get_command_queue().finish(); }
};
     