#pragma once

#ifdef __x86_64__
    class tbb
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Execution
            static execpools::tbb_thread_pool execution_context;

        public: // Type
            /* Same as cpu */

        public: // Allocator
            template < class type > using allocator = ::tbb::cache_aligned_allocator<type>;

        public: // Layout
            using layout_type = std::layout_right;

        public: // Operator
            /* Same as cpu */

        public: // Hash
            /* Same as cpu */

        public: // Container
            template < class type, class alloc = allocator<type> >                                                                                                using vector         = ::tbb::concurrent_vector<type,alloc>;
            template < class type, class alloc = allocator<type> >                                                                                                using queue          = ::tbb::concurrent_queue<type>;
            template < class type, class container = vector<type>, class compare = less<type> >                                                                   using priority_queue = ::tbb::concurrent_priority_queue<type,compare,typename container::allocator_type>;
            template < class type, class compare = less<type>, class alloc = allocator<type> >                                                                    using set            = ::tbb::concurrent_set<type,compare,alloc>;
            template < class type, class hash = hash<type>, class equal = equal_to<type>, class alloc = allocator<type> >                                         using unordered_set  = ::tbb::concurrent_unordered_set<type,hash,equal,alloc>;
            template < class type1, class type2, class compare = less<type1>, class alloc = allocator<std::pair<const type1,type2>> >                             using map = ::tbb::concurrent_map<type1,type2,compare,alloc>;
            template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<type1>, class alloc = allocator<std::pair<const type1,type2>> > using unordered_map = ::tbb::concurrent_unordered_map<type1,type2,hash,equal,alloc>;
    
        public: // Algorithm
            static decltype(auto) for_each       ( auto&&... args ) { return ::tbb::parallel_for_each(std::forward<decltype(args)>(args)...); }
         // static decltype(auto) inclusive_scan ( auto&&... args ); 
         // static decltype(auto) reduce         ( auto&&... args );
            static decltype(auto) sort           ( auto&&... args ) { return ::tbb::parallel_sort    (std::forward<decltype(args)>(args)...); }
    };

 // #include "detail/inclusive_scan.ipp"
 // #include "detail/reduce.ipp"

    execpools::tbb_thread_pool tbb::execution_context = execpools::tbb_thread_pool(::tbb::this_task_arena::max_concurrency());
#else
    class tbb
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }  
    };
#endif