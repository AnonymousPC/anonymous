template < class type, class alloc >
class tbb::queue
    extends public ::tbb::concurrent_queue<type,alloc>
{
    public:
        void pop ( );
};

#include "queue.cpp"