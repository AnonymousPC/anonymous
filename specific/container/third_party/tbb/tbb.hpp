#pragma once

#ifdef __TBB_tbb_H
    class tbb
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Layout
            using layout_type = std::layout_right;

        public: // Allocator
            template < class type > using allocator = ::tbb::cache_aligned_allocator<type>;

        public: // Container
            template < class type, class alloc = allocator<type> >                              using vector         = ::tbb::concurrent_vector<type,alloc>;
            template < class type, class alloc = allocator<type> >                              using queue          = ::tbb::concurrent_queue<type>;
            template < class type, class container = vector<type>, class compare = less<type> > using priority_queue = ::tbb::concurrent_priority_queue<type,compare,typename container::allocator_type>;
    };
#else
    class tbb
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }  
    };
#endif