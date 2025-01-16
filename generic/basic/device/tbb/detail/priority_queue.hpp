#pragma once

template < class type, class less, class alloc >
class tbb::priority_queue
    extends public ::tbb::concurrent_priority_queue<type,less,alloc>
{
    private: // Typedef
        using base = ::tbb::concurrent_priority_queue<type,less,alloc>;
    
    public: // Override
        type pop ( ) { let poped = type(); let ok = base::try_pop(poped); return ok ? poped otherwise throw value_error("cannot pop from an empty priority_queue"); }
};