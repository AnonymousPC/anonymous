#pragma once

class eigen
    extends protected cpu
{
    public: // Execution
        using  cpu::execution_context_type;
        static execution_context_type& execution_context;

    public: // Type
        using cpu::value_type;
        using cpu::reference;
        using cpu::const_reference;
        using cpu::pointer;
        using cpu::const_pointer;
        using cpu::stride_pointer;
        using cpu::const_stride_pointer;

    public: // Allocator
        template < class type > using allocator = Eigen::aligned_allocator<type>;

    public: // Memory
                                using layout_type   = std::layout_left;
        template < class type > using accessor_type = std::aligned_accessor<type>;

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
        template < class type, int len >                                                                                                                 using array             = Eigen::Vector<type,len>;
     // template < class type, class traits = std::char_traits<type>, class alloc = allocator<type> >                                                    using basic_string      = unsupported;
     // template < class type, class traits = std::char_traits<type> >                                                                                   using basic_string_view = unsupported;
     // template < class type, class alloc = allocator<type> >                                                                                           using deque             = unsupported;
     // template < class type, int len >                                                                                                                 using inplace_vector    = unsupported;
     // template < class type, class alloc = allocator<type> >                                                                                           using list              = unsupported;
     // template < class type1, class type2, class compare = less<>, class alloc = allocator<std::pair<const type1,type2>> >                             using map               = unsupported;
     // template < class type, class compare = less<>, class alloc = allocator<type> >                                                                   class priority_queue;   = unsupported;
     // template < class type, class alloc = allocator<type> >                                                                                           class queue;            = unsupported;
     // template < class type, class compare = less<>, class alloc = allocator<type> >                                                                   using set               = unsupported;
     // template < class type, class alloc = allocator<type> >                                                                                           using stack             = unsupported;
     // template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<>, class alloc = allocator<std::pair<const type1,type2>> > using unordered_map     = unsupported;
     // template < class type, class hash = hash<type>, class equal = equal_to<>,  class alloc = allocator<type> >                                       using unordered_set     = unsupported;
        template < class type, class alloc = allocator<type> >                                                                                           using vector            = Eigen::Vector<type,Eigen::Dynamic>;

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

    public: // Linalg
        struct linalg
        {
            constexpr static void unary_plus      ( const auto,             auto );
            constexpr static void unary_minus     ( const auto,             auto );
            constexpr static void plus            ( const auto, const auto, auto );
            constexpr static void minus           ( const auto, const auto, auto );
            constexpr static void left_scale      ( const auto, const auto, auto );
            constexpr static void right_scale     ( const auto, const auto, auto );
            constexpr static void multiply        ( const auto, const auto, auto );
            constexpr static void divide          ( const auto, const auto, auto );
            constexpr static void dot             ( const auto, const auto, auto );
            constexpr static void cross           ( const auto, const auto, auto );
            constexpr static void convolve        ( const auto, const auto, auto );

            constexpr static auto transpose       ( const auto,             auto );
            constexpr static auto hermitian       ( const auto,             auto );

            constexpr static void det             ( const auto,             auto& );
            constexpr static void eigen           ( const auto,             auto, auto );
            constexpr static void eigen_value     ( const auto,             auto );
            constexpr static void eigen_vector    ( const auto,             auto );
            constexpr static void evd             ( const auto,             auto, auto, auto );
            constexpr static void inverse         ( const auto,             auto );
            constexpr static void lu              ( const auto,             auto, auto, auto );
            constexpr static void qr              ( const auto,             auto, auto );
            constexpr static void rank            ( const auto,             int& );
            constexpr static void singular        ( const auto,             auto, auto, auto );
            constexpr static void singular_value  ( const auto,             auto );
            constexpr static void singular_vector ( const auto,             auto, auto );
            constexpr static void svd             ( const auto,             auto, auto, auto );
            constexpr static void tr              ( const auto,             auto& );

            constexpr static void fft             ( auto,                   auto );
            constexpr static void ifft            ( auto,                   auto );
        };
};

eigen::execution_context_type& eigen::execution_context = cpu::execution_context;

#include "linalg/linalg.hpp"