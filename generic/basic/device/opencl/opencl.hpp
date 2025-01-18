#pragma once

#ifdef BOOST_COMPUTE_HPP
    #include "detail/opencl_thread_pool.hpp"
    
    class opencl
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Execution
            static detail::opencl_thread_pool execution_context;

        public: // Type
            template < class type > using value_type      = type;
            template < class type > using reference       =       boost::compute::detail::buffer_value<type>;
            template < class type > using const_reference = const boost::compute::detail::buffer_value<type>;
            template < class type > using pointer         =       boost::compute::detail::device_ptr<type>;
            template < class type > using const_pointer   = const boost::compute::detail::device_ptr<type>;

        public: // Allocator
            template < class type > using allocator = boost::compute::buffer_allocator<type>;

        public: // Layout
            using layout_type = std::layout_left;

        public: // Operator
            template < class type = void > using plus          = boost::compute::plus         <type>;
            template < class type = void > using minus         = boost::compute::minus        <type>;
            template < class type = void > using multiplies    = boost::compute::multiplies   <type>;
            template < class type = void > using divides       = boost::compute::divides      <type>;
            template < class type = void > class negate        { static_assert(false, "not supported on this deivce"); };
            template < class type = void > using equal_to      = boost::compute::equal_to     <type>;
            template < class type = void > using not_equal_to  = boost::compute::not_equal_to <type>;
            template < class type = void > using less          = boost::compute::less         <type>;
            template < class type = void > using less_equal    = boost::compute::less_equal   <type>;
            template < class type = void > using greater       = boost::compute::greater      <type>;
            template < class type = void > using greater_equal = boost::compute::greater_equal<type>; 
            template < class type = void > using logical_and   = boost::compute::logical_and  <type>;
            template < class type = void > using logical_or    = boost::compute::logical_or   <type>;
            template < class type = void > using logical_not   = boost::compute::logical_not  <type>;
            template < class type = void > using bit_and       = boost::compute::bit_and      <type>;
            template < class type = void > using bit_or        = boost::compute::bit_or       <type>;
            template < class type = void > using bit_xor       = boost::compute::bit_xor      <type>;
            template < class type = void > class bit_not       { static_assert(false, "not supported on this deivce"); };

        public: // Hash
            template < class type > using hash = boost::compute::hash<type>;

        public: // Container
            template < class type, int len >                                                                                                                      using array             = boost::compute::array<type,len>;
            template < class type, class traits = std::char_traits<type>, class alloc = allocator<type> >                                                         using basic_string      = boost::compute::basic_string<type,traits>;
            template < class type, class traits = std::char_traits<type> >                                                                                        class basic_string_view;
            template < class type, class alloc = allocator<type> >                                                                                                class deque             { static_assert(false, "not supported on this device"); };
            template < class type, class alloc = allocator<type> >                                                                                                class list              { static_assert(false, "not supported on this device"); };
            template < class type1, class type2, class compare = less<type1>, class alloc = allocator<std::pair<const type1,type2>> >                             using map               = boost::compute::flat_map<type1,type2>;
            template < class type, class compare = less<type>, class alloc = allocator<type> >                                                                    class priority_queue    { static_assert(false, "not supported on this device"); };
            template < class type, class alloc = allocator<type> >                                                                                                class queue             { static_assert(false, "not supported on this device"); };
            template < class type, class compare = less<type>, class alloc = allocator<type> >                                                                    using set               = boost::compute::flat_set<type>;
            template < class type, class alloc = allocator<type> >                                                                                                class stack;            // Override top(), pop().
            template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<type1>, class alloc = allocator<std::pair<const type1,type2>> > class unordered_map     { static_assert(false, "not supported on this device"); };
            template < class type, class hash = hash<type>, class equal = equal_to<type>,  class alloc = allocator<type> >                                        class unordered_set     { static_assert(false, "not supported on this device"); };
            template < class type, class alloc = allocator<type> >                                                                                                using vector            = boost::compute::vector<type,alloc>;

        public: // Algorithm
            static decltype(auto) accumulate                        ( auto&&... args ) { return boost::compute::accumulate              (std::forward<decltype(args)>(args)...); }
            static decltype(auto) adjacent_difference               ( auto&&... args ) { return boost::compute::adjacent_difference     (std::forward<decltype(args)>(args)...); }
            static decltype(auto) adjacent_find                     ( auto&&... args ) { return boost::compute::adjacent_find           (std::forward<decltype(args)>(args)...); }
            static decltype(auto) all_of                            ( auto&&... args ) { return boost::compute::all_of                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) any_of                            ( auto&&... args ) { return boost::compute::any_of                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) binary_search                     ( auto&&... args ) { return boost::compute::binary_search           (std::forward<decltype(args)>(args)...); }
            static decltype(auto) copy                              ( auto&&... args ) { return boost::compute::copy                    (std::forward<decltype(args)>(args)...); }
            static decltype(auto) copy_backward                     ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) copy_if                           ( auto&&... args ) { return boost::compute::copy_if                 (std::forward<decltype(args)>(args)...); }
            static decltype(auto) copy_n                            ( auto&&... args ) { return boost::compute::copy_n                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) count                             ( auto&&... args ) { return boost::compute::count                   (std::forward<decltype(args)>(args)...); }
            static decltype(auto) count_if                          ( auto&&... args ) { return boost::compute::count_if                (std::forward<decltype(args)>(args)...); }
            static decltype(auto) equal                             ( auto&&... args ) { return boost::compute::equal                   (std::forward<decltype(args)>(args)...); }
            static decltype(auto) equal_range                       ( auto&&... args ) { return boost::compute::equal_range             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) exclusive_scan                    ( auto&&... args ) { return boost::compute::exclusive_scan          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) fill                              ( auto&&... args ) { return boost::compute::fill                    (std::forward<decltype(args)>(args)...); }
            static decltype(auto) fill_n                            ( auto&&... args ) { return boost::compute::fill_n                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) find                              ( auto&&... args ) { return boost::compute::find                    (std::forward<decltype(args)>(args)...); }
            static decltype(auto) find_end                          ( auto&&... args ) { return boost::compute::find_end                (std::forward<decltype(args)>(args)...); }
            static decltype(auto) find_first_of                     ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) find_if                           ( auto&&... args ) { return boost::compute::find_if                 (std::forward<decltype(args)>(args)...); }
            static decltype(auto) find_if_not                       ( auto&&... args ) { return boost::compute::find_if_not             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) for_each                          ( auto&&... args ) { return boost::compute::for_each                (std::forward<decltype(args)>(args)...); }
            static decltype(auto) for_each_n                        ( auto&&... args ) { return boost::compute::for_each_n              (std::forward<decltype(args)>(args)...); }
            static decltype(auto) generate                          ( auto&&... args ) { return boost::compute::generate                (std::forward<decltype(args)>(args)...); }
            static decltype(auto) generate_n                        ( auto&&... args ) { return boost::compute::generate_n              (std::forward<decltype(args)>(args)...); }
            static decltype(auto) includes                          ( auto&&... args ) { return boost::compute::includes                (std::forward<decltype(args)>(args)...); }
            static decltype(auto) inclusive_scan                    ( auto&&... args ) { return boost::compute::inclusive_scan          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) inner_product                     ( auto&&... args ) { return boost::compute::inner_product           (std::forward<decltype(args)>(args)...); }
            static decltype(auto) inplace_merge                     ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) iota                              ( auto&&... args ) { return boost::compute::iota                    (std::forward<decltype(args)>(args)...); }
            static decltype(auto) is_partitioned                    ( auto&&... args ) { return boost::compute::is_partitioned          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) is_permutation                    ( auto&&... args ) { return boost::compute::is_permutation          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) is_sorted                         ( auto&&... args ) { return boost::compute::is_sorted               (std::forward<decltype(args)>(args)...); }
            static decltype(auto) is_sorted_until                   ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) lower_bound                       ( auto&&... args ) { return boost::compute::lower_bound             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) lexicographical_compare           ( auto&&... args ) { return boost::compute::lexicographical_compare (std::forward<decltype(args)>(args)...); }
            static decltype(auto) lexicographical_compare_three_way ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) max_element                       ( auto&&... args ) { return boost::compute::max_element             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) merge                             ( auto&&... args ) { return boost::compute::merge                   (std::forward<decltype(args)>(args)...); }
            static decltype(auto) min_element                       ( auto&&... args ) { return boost::compute::min_element             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) minmax_element                    ( auto&&... args ) { return boost::compute::minmax_element          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) mismatch                          ( auto&&... args ) { return boost::compute::mismatch                (std::forward<decltype(args)>(args)...); }
      /*!*/ static decltype(auto) move                              ( auto&&... args ) { return boost::compute::copy                    (std::forward<decltype(args)>(args)...); }
            static decltype(auto) move_backward                     ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) next_permutation                  ( auto&&... args ) { return boost::compute::next_permutation        (std::forward<decltype(args)>(args)...); }
            static decltype(auto) none_of                           ( auto&&... args ) { return boost::compute::none_of                 (std::forward<decltype(args)>(args)...); }
            static decltype(auto) nth_element                       ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) partial_sort                      ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) partial_sort_copy                 ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) partial_sum                       ( auto&&... args ) { return boost::compute::partial_sum             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) partition                         ( auto&&... args ) { return boost::compute::partition               (std::forward<decltype(args)>(args)...); }
            static decltype(auto) partition_copy                    ( auto&&... args ) { return boost::compute::partition_copy          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) partition_point                   ( auto&&... args ) { return boost::compute::partition_point         (std::forward<decltype(args)>(args)...); }
            static decltype(auto) prev_permutation                  ( auto&&... args ) { return boost::compute::prev_permutation        (std::forward<decltype(args)>(args)...); }
            static decltype(auto) reduce                            ( auto&&... args ) { return boost::compute::reduce                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) remove                            ( auto&&... args ) { return boost::compute::remove                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) remove_copy                       ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) remove_copy_if                    ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) remove_if                         ( auto&&... args ) { return boost::compute::remove_if               (std::forward<decltype(args)>(args)...); }
            static decltype(auto) replace                           ( auto&&... args ) { return boost::compute::replace                 (std::forward<decltype(args)>(args)...); }
            static decltype(auto) replace_copy                      ( auto&&... args ) { return boost::compute::replace_copy            (std::forward<decltype(args)>(args)...); }
            static decltype(auto) replace_copy_if                   ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) replace_if                        ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) reverse                           ( auto&&... args ) { return boost::compute::reverse                 (std::forward<decltype(args)>(args)...); }
            static decltype(auto) reverse_copy                      ( auto&&... args ) { return boost::compute::reverse_copy            (std::forward<decltype(args)>(args)...); }
            static decltype(auto) rotate                            ( auto&&... args ) { return boost::compute::rotate                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) rotate_copy                       ( auto&&... args ) { return boost::compute::rotate_copy             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) sample                            ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) search                            ( auto&&... args ) { return boost::compute::search                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) search_n                          ( auto&&... args ) { return boost::compute::search_n                (std::forward<decltype(args)>(args)...); }
            static decltype(auto) set_difference                    ( auto&&... args ) { return boost::compute::set_difference          (std::forward<decltype(args)>(args)...); }
            static decltype(auto) set_intersection                  ( auto&&... args ) { return boost::compute::set_intersection        (std::forward<decltype(args)>(args)...); }
            static decltype(auto) set_symmetric_difference          ( auto&&... args ) { return boost::compute::set_symmetric_difference(std::forward<decltype(args)>(args)...); }
            static decltype(auto) set_union                         ( auto&&... args ) { return boost::compute::set_union               (std::forward<decltype(args)>(args)...); }
            static decltype(auto) shift_left                        ( auto&&... args ) { return boost::compute::shift_left              (std::forward<decltype(args)>(args)...); }
            static decltype(auto) shift_right                       ( auto&&... args ) { return boost::compute::shift_right             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) shuffle                           ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) sort                              ( auto&&... args ) { return boost::compute::sort                    (std::forward<decltype(args)>(args)...); }
            static decltype(auto) stable_partition                  ( auto&&... args ) { return boost::compute::stable_partition        (std::forward<decltype(args)>(args)...); }
            static decltype(auto) stable_sort                       ( auto&&... args ) { return boost::compute::stable_sort             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) swap_ranges                       ( auto&&... args ) { return boost::compute::swap_ranges             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) transform                         ( auto&&... args ) { return boost::compute::transform               (std::forward<decltype(args)>(args)...); }
            static decltype(auto) transform_exclusive_scan          ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) transform_inclusive_scan          ( auto&&... args ) { static_assert(false, "not supported on this device"); }
            static decltype(auto) transform_reduce                  ( auto&&... args ) { return boost::compute::transform_reduce        (std::forward<decltype(args)>(args)...); }
            static decltype(auto) unique                            ( auto&&... args ) { return boost::compute::unique                  (std::forward<decltype(args)>(args)...); }
            static decltype(auto) unique_copy                       ( auto&&... args ) { return boost::compute::unique_copy             (std::forward<decltype(args)>(args)...); }
            static decltype(auto) upper_bound                       ( auto&&... args ) { return boost::compute::upper_bound             (std::forward<decltype(args)>(args)...); }
    };

    #include "detail/stack.hpp"

    detail::opencl_thread_pool opencl::execution_context = detail::opencl_thread_pool(boost::compute::system::default_device().max_work_group_size());
#else
    class opencl
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }
    };
#endif
