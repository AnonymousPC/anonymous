#pragma once

template < class type, class compare, class alloc >
class tbb::priority_queue
    extends public ::tbb::concurrent_priority_queue<type,compare,alloc>
{
    private: // Typedef
        using base = ::tbb::concurrent_priority_queue<type,compare,alloc>;
    
    public: // Override
        type pop ( ) { auto poped = type(); auto ok = base::try_pop(poped); return ok ? poped : throw value_error("cannot pop from an empty priority_queue"); }
};