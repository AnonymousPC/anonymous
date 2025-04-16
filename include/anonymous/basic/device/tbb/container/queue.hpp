#pragma once

template < class type, class alloc >
class tbb::queue
    extends public ::tbb::concurrent_queue<type,alloc>
{
    private: // Typedef
        using base = ::tbb::concurrent_queue<type,alloc>;

    public: // Override  
        int  size ( ) const { return base::unsafe_size(); }
        type pop  ( )       { auto poped = type(); auto ok = base::try_pop(poped); return ok ? poped : throw value_error("cannot pop from an empty queue"); }
};