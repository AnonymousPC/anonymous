#pragma once

#ifdef __TBB_tbb_H
    class tbb
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Context
            using  execution_context_type = execpools::tbb_thread_pool;
            static execution_context_type execution_context;

        public: // Layout
            using layout_type = std::layout_right;

        public: // Allocator
            template < class type > using allocator = ::tbb::cache_aligned_allocator<type>;

        public: // Container
            template < class type, class alloc = allocator<type> >                              using vector         = ::tbb::concurrent_vector<type,alloc>;
            template < class type, class alloc = allocator<type> >                              using queue          = ::tbb::concurrent_queue<type>;
            template < class type, class container = vector<type>, class compare = less<type> > using priority_queue = ::tbb::concurrent_priority_queue<type,compare,typename container::allocator_type>;
    };
    tbb::execution_context_type tbb::execution_context = tbb::execution_context_type(::tbb::this_task_arena::max_concurrency());
#else
    class tbb
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }  
    };
#endif