#pragma once

template < class type, class alloc >
class opencl::stack
    extends public boost::compute::stack<type>
{
    private: // Typedef
        using base = boost::compute::stack<type>;

    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;

    public: // Override
        reference top ( ) = delete; // base::top() returns cpu::value_type, which is not assignable.

        const_reference top ( ) const
        {
            // base::top() returns cpu::value_type, which is not assignable.
            return const_reference(base::top());
        } 

        type pop ( )       
        {
            let poped = base::top(); base::pop(); return poped;
        }                             
};