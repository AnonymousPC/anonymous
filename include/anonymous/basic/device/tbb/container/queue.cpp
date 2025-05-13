template < class type, class alloc >
void tbb::queue<type,alloc>::pop ( )
{
    auto poped = type();
    bool success = ::tbb::concurrent_queue<type,alloc>::try_pop(poped);
    if ( not success )
        throw value_error("pop failed (with empty() = true)");
}