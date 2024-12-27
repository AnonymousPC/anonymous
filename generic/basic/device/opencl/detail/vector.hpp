#pragma once

template < class type, class alloc >
class opencl::vector
    extends public boost::compute::vector<type,alloc>
{
    private: // Typedef
        using base = boost::compute::vector<type,alloc>

    public: // Core: TODO: noexcept.
        vector ( auto&&... args ) requires       std::constructible_from<base,decltype(args...),boost::compute::command_queue&>   extends public base ( std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue() ) { }
        vector ( auto&&... args ) requires not ( std::constructible_from<base,decltype(args...),boost::compute::command_queue&> ) extends public base ( std::forward<decltype(args)>(args)...                                                ) { }

    public: // Member
        decltype(auto) resize        ( auto&&... args ) { base::resize       (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) reserve       ( auto&&... args ) { base::reserve      (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) shrink_to_fit ( auto&&... args ) { base::shrink_to_fit(std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) assign        ( auto&&... args ) { base::assign       (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) push_back     ( auto&&... args ) { base::push_back    (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) pop_back      ( auto&&... args ) { base::pop_back     (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) insert        ( auto&&... args ) { base::insert       (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
        decltype(auto) erase         ( auto&&... args ) { base::erase        (std::forward<decltype(args)>(args)..., opencl::execution_context.get_command_queue()); }
};
     