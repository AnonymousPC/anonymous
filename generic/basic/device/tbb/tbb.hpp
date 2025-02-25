#pragma once

class tbb
    extends protected cpu
{
    public: // Execution
        using  execution_context_type = execpools::tbb_thread_pool;
        static execution_context_type execution_context;

    public: // Type
        using cpu::value_type;
        using cpu::reference;
        using cpu::const_reference;
        using cpu::pointer;
        using cpu::const_pointer;
        using cpu::stride_pointer;
        using cpu::const_stride_pointer;

    public: // Allocator
        template < class type > using allocator = ::tbb::tbb_allocator<type>;

    public: // Memory
        using cpu::layout_type;
        using cpu::accessor_type;

    public: // Operator
        using cpu::plus;
        using cpu::minus;
        using cpu::divides;
        using cpu::negate;
        using cpu::equal_to;
        using cpu::not_equal_to;
        using cpu::less;
        using cpu::less_equal;
        using cpu::greater;
        using cpu::greater_equal;
        using cpu::logical_and;
        using cpu::logical_or;
        using cpu::logical_not;
        using cpu::bit_and;
        using cpu::bit_or;
        using cpu::bit_xor;
        using cpu::bit_not;

    public: // Hash
        using cpu::hash;
        
    public: // Container
     // template < class type, int len >                                                                                                                 using array             = unsupported;
     // template < class type, class traits = std::char_traits<type>, class alloc = allocator<type> >                                                    using basic_string      = unsupported;
     // template < class type, class traits = std::char_traits<type> >                                                                                   using basic_string_view = unsupported;
     // template < class type, class alloc = allocator<type> >                                                                                           using deque             = unsupported;
     // template < class type, int len >                                                                                                                 using inplace_vector    = unsupported;
     // template < class type, class alloc = allocator<type> >                                                                                           using list              = unsupported;
        template < class type1, class type2, class compare = less<>, class alloc = allocator<std::pair<const type1,type2>> >                             using map               = ::tbb::concurrent_map<type1,type2,compare,alloc>;
        template < class type, class compare = less<>, class alloc = allocator<type> >                                                                   class priority_queue;    // Override pop().
        template < class type, class alloc = allocator<type> >                                                                                           class queue;             // Override size(), pop().
        template < class type, class compare = less<>, class alloc = allocator<type> >                                                                   using set               = ::tbb::concurrent_set<type,compare,alloc>;
     // template < class type, class alloc = allocator<type> >                                                                                           using stack             = unsupported;
        template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<>, class alloc = allocator<std::pair<const type1,type2>> > using unordered_map     = ::tbb::concurrent_unordered_map<type1,type2,hash,equal>; // Use default allocator<std::pair>
        template < class type, class hash = hash<type>, class equal = equal_to<>,  class alloc = allocator<type> >                                       using unordered_set     = ::tbb::concurrent_unordered_set<type,hash,equal,alloc>;
     // template < class type, class alloc = allocator<type> >                                                                                           using vector            = supported, but memory is not contiguous.

    public: // Algorithm
        using cpu::accumulate;
        using cpu::adjacent_difference;
        using cpu::adjacent_find;
        using cpu::all_of;
        using cpu::any_of;
        using cpu::binary_search;
        using cpu::copy;
        using cpu::copy_backward;
        using cpu::copy_if;
        using cpu::copy_n;
        using cpu::count;
        using cpu::count_if;
        using cpu::equal;
        using cpu::equal_range;
        using cpu::exclusive_scan;
        using cpu::fill;
        using cpu::fill_n;
        using cpu::find;
        using cpu::find_end;
        using cpu::find_first_of;
        using cpu::find_if;
        using cpu::find_if_not;
        using cpu::for_each;
        using cpu::for_each_n;
        using cpu::generate;
        using cpu::generate_n;
        using cpu::includes;
        using cpu::inclusive_scan;
        using cpu::inner_product;
        using cpu::inplace_merge;
        using cpu::iota;
        using cpu::is_partitioned;
        using cpu::is_permutation;
        using cpu::is_sorted;
        using cpu::is_sorted_until;
        using cpu::lower_bound;
        using cpu::lexicographical_compare;
        using cpu::lexicographical_compare_three_way;
        using cpu::max_element;
        using cpu::merge;
        using cpu::min_element;
        using cpu::minmax_element;
        using cpu::mismatch;
        using cpu::move;
        using cpu::move_backward;
        using cpu::next_permutation;
        using cpu::none_of;
        using cpu::nth_element;
        using cpu::partial_sort;
        using cpu::partial_sort_copy;
        using cpu::partial_sum;
        using cpu::partition;
        using cpu::partition_copy;
        using cpu::partition_point;
        using cpu::prev_permutation;
        using cpu::reduce;
        using cpu::remove;
        using cpu::remove_copy;
        using cpu::remove_copy_if;
        using cpu::remove_if;
        using cpu::replace;
        using cpu::replace_copy;
        using cpu::replace_copy_if;
        using cpu::replace_if;
        using cpu::reverse;
        using cpu::reverse_copy;
        using cpu::rotate;
        using cpu::rotate_copy;
        using cpu::sample;
        using cpu::search;
        using cpu::search_n;
        using cpu::set_difference;
        using cpu::set_intersection;
        using cpu::set_symmetric_difference;
        using cpu::set_union;
        using cpu::shift_left;
        using cpu::shift_right;
        using cpu::shuffle;
        using cpu::sort;
        using cpu::stable_partition;
        using cpu::stable_sort;
        using cpu::swap_ranges;
        using cpu::transform;
        using cpu::transform_exclusive_scan;
        using cpu::transform_inclusive_scan;
        using cpu::transform_reduce;
        using cpu::unique;
        using cpu::unique_copy;
        using cpu::upper_bound;
};

#include "container/priority_queue.hpp"
#include "container/queue.hpp"

tbb::execution_context_type tbb::execution_context = tbb::execution_context_type(1 /*::tbb::this_task_arena::max_concurrency()*/);