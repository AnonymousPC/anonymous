template < class type, class compare, class alloc >
class tbb::priority_queue
    extends public ::tbb::concurrent_priority_queue<type,compare,alloc>
{
    public:
        void pop ( );
};

#include "priority_queue.cpp"