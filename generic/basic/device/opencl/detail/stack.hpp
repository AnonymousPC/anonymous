#pragma once

template < class type, class alloc >
class opencl::stack
    extends public boost::compute::stack<type>
{
    private: // Typedef
        using base            = boost::compute::stack<type>;
        using reference       = opencl::template reference<type>;
        using const_reference = opencl::template const_reference<type>;

    public: // Override
        reference       top ( ) = delete;                                      // base::top() returns cpu::value_type, which is not assignable.
        const_reference top ( ) const { return const_reference(base::top()); } // base::top() returns cpu::value_type, which is not assignable.
        type            pop ( )       { let poped = base::top(); base::pop(); return poped; }                             
};