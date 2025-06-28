template < class type, class compare, class alloc >
void tbb::priority_queue<type,compare,alloc>::pop ( )
{
    auto poped = type();
    bool success = ::tbb::concurrent_priority_queue<type,compare,alloc>::try_pop(poped);
    if ( not success )
        throw value_error("pop failed (with empty() = true)");
}