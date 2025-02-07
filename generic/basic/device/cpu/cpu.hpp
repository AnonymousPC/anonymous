#pragma once

class cpu
{
    public: // Trait
        struct device_tag { };

    public: // Execution
        using  execution_context_type = std::execution::static_thread_pool;
        static execution_context_type execution_context;

    public: // Type
        template < class type > using value_type      = type;
        template < class type > using reference       = type&;
        template < class type > using const_reference = const type&;
        template < class type > using pointer         = type*;
        template < class type > using const_pointer   = const type*;
        template < class type > class stride_pointer;
        template < class type > class const_stride_pointer;

    public: // Allocator
        template < class type > using allocator = std::allocator<type>;

    public: // Memory
                                using layout_type         = std::layout_right;
        template < class type > class accessor_type;
        template < class type > class const_accessor_type;

    public: // Operator
        template < class type = void > using plus          = std::plus         <type>;
        template < class type = void > using minus         = std::minus        <type>;
        template < class type = void > using multiplies    = std::multiplies   <type>;
        template < class type = void > using divides       = std::divides      <type>;
        template < class type = void > using negate        = std::negate       <type>;
        template < class type = void > using equal_to      = std::equal_to     <type>;
        template < class type = void > using not_equal_to  = std::not_equal_to <type>;
        template < class type = void > using less          = std::less         <type>;
        template < class type = void > using less_equal    = std::less_equal   <type>;
        template < class type = void > using greater       = std::greater      <type>;
        template < class type = void > using greater_equal = std::greater_equal<type>; 
        template < class type = void > using logical_and   = std::logical_and  <type>;
        template < class type = void > using logical_or    = std::logical_or   <type>;
        template < class type = void > using logical_not   = std::logical_not  <type>;
        template < class type = void > using bit_and       = std::bit_and      <type>;
        template < class type = void > using bit_or        = std::bit_or       <type>;
        template < class type = void > using bit_xor       = std::bit_xor      <type>;
        template < class type = void > using bit_not       = std::bit_not      <type>;

    public: // Hash
        template < class type > using hash = std::hash<type>;

    public: // Container
        template < class type, int len >                                                                                                                 using array             = std::array            <type,len>;
        template < class type, class traits = std::char_traits<type>, class alloc = allocator<type> >                                                    using basic_string      = std::basic_string     <type,traits,alloc>;
        template < class type, class traits = std::char_traits<type> >                                                                                   using basic_string_view = std::basic_string_view<type,traits>;
        template < class type, class alloc = allocator<type> >                                                                                           using deque             = std::deque            <type,alloc>;
        template < class type, int len >                                                                                                                 using inplace_vector    = std::inplace_vector   <type,len>;
        template < class type, class alloc = allocator<type> >                                                                                           using list              = std::list             <type,alloc>;
        template < class type1, class type2, class compare = less<>, class alloc = allocator<std::pair<const type1,type2>> >                             using map               = std::map              <type1,type2,compare,alloc>;
        template < class type, class compare = less<>, class alloc = allocator<type> >                                                                   using priority_queue    = std::priority_queue   <type,std::vector<type,alloc>,compare>;
        template < class type, class alloc = allocator<type> >                                                                                           using queue             = std::queue            <type,std::vector<type,alloc>>;
        template < class type, class compare = less<>, class alloc = allocator<type> >                                                                   using set               = std::set              <type,compare,alloc>;
        template < class type, class alloc = allocator<type> >                                                                                           using stack             = std::stack            <type,std::vector<type,alloc>>;
        template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<>, class alloc = allocator<std::pair<const type1,type2>> > using unordered_map     = std::unordered_map    <type1,type2,hash,equal,alloc>;
        template < class type, class hash = hash<type>, class equal = equal_to<>, class alloc = allocator<type> >                                        using unordered_set     = std::unordered_set    <type,hash,equal,alloc>;
        template < class type, class alloc = allocator<type> >                                                                                           using vector            = std::vector           <type,alloc>;

    public: // Algorithm
        constexpr static decltype(auto) accumulate                        ( auto&&... args ) { return std::accumulate                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) adjacent_difference               ( auto&&... args ) { return std::adjacent_difference              (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) adjacent_find                     ( auto&&... args ) { return std::adjacent_find                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) all_of                            ( auto&&... args ) { return std::all_of                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) any_of                            ( auto&&... args ) { return std::any_of                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) binary_search                     ( auto&&... args ) { return std::binary_search                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy                              ( auto&&... args ) { return std::copy                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_backward                     ( auto&&... args ) { return std::copy_backward                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_if                           ( auto&&... args ) { return std::copy_if                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_n                            ( auto&&... args ) { return std::copy_n                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) count                             ( auto&&... args ) { return std::count                            (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) count_if                          ( auto&&... args ) { return std::count_if                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) equal                             ( auto&&... args ) { return std::equal                            (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) equal_range                       ( auto&&... args ) { return std::equal_range                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) exclusive_scan                    ( auto&&... args ) { return std::exclusive_scan                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) fill                              ( auto&&... args ) { return std::fill                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) fill_n                            ( auto&&... args ) { return std::fill_n                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find                              ( auto&&... args ) { return std::find                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_end                          ( auto&&... args ) { return std::find_end                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_first_of                     ( auto&&... args ) { return std::find_first_of                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_if                           ( auto&&... args ) { return std::find_if                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_if_not                       ( auto&&... args ) { return std::find_if_not                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) for_each                          ( auto&&... args ) { return std::for_each                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) for_each_n                        ( auto&&... args ) { return std::for_each_n                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) generate                          ( auto&&... args ) { return std::generate                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) generate_n                        ( auto&&... args ) { return std::generate_n                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) includes                          ( auto&&... args ) { return std::includes                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) inclusive_scan                    ( auto&&... args ) { return std::inclusive_scan                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) inner_product                     ( auto&&... args ) { return std::inner_product                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) inplace_merge                     ( auto&&... args ) { return std::inplace_merge                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) iota                              ( auto&&... args ) { return std::iota                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_partitioned                    ( auto&&... args ) { return std::is_partitioned                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_permutation                    ( auto&&... args ) { return std::is_permutation                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_sorted                         ( auto&&... args ) { return std::is_sorted                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_sorted_until                   ( auto&&... args ) { return std::is_sorted_until                  (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) lower_bound                       ( auto&&... args ) { return std::lower_bound                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) lexicographical_compare           ( auto&&... args ) { return std::lexicographical_compare          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) lexicographical_compare_three_way ( auto&&... args ) { return std::lexicographical_compare_three_way(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) max_element                       ( auto&&... args ) { return std::max_element                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) merge                             ( auto&&... args ) { return std::merge                            (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) min_element                       ( auto&&... args ) { return std::min_element                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) minmax_element                    ( auto&&... args ) { return std::minmax_element                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) mismatch                          ( auto&&... args ) { return std::mismatch                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) move                              ( auto&&... args ) { return std::move                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) move_backward                     ( auto&&... args ) { return std::move_backward                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) next_permutation                  ( auto&&... args ) { return std::next_permutation                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) none_of                           ( auto&&... args ) { return std::none_of                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) nth_element                       ( auto&&... args ) { return std::nth_element                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partial_sort                      ( auto&&... args ) { return std::partial_sort                     (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partial_sort_copy                 ( auto&&... args ) { return std::partial_sort_copy                (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partial_sum                       ( auto&&... args ) { return std::partial_sum                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition                         ( auto&&... args ) { return std::partition                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition_copy                    ( auto&&... args ) { return std::partition_copy                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition_point                   ( auto&&... args ) { return std::partition_point                  (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) prev_permutation                  ( auto&&... args ) { return std::prev_permutation                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reduce                            ( auto&&... args ) { return std::reduce                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove                            ( auto&&... args ) { return std::remove                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_copy                       ( auto&&... args ) { return std::remove_copy                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_copy_if                    ( auto&&... args ) { return std::remove_copy_if                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_if                         ( auto&&... args ) { return std::remove_if                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace                           ( auto&&... args ) { return std::replace                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_copy                      ( auto&&... args ) { return std::replace_copy                     (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_copy_if                   ( auto&&... args ) { return std::replace_copy_if                  (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_if                        ( auto&&... args ) { return std::replace_if                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reverse                           ( auto&&... args ) { return std::reverse                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reverse_copy                      ( auto&&... args ) { return std::reverse_copy                     (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) rotate                            ( auto&&... args ) { return std::rotate                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) rotate_copy                       ( auto&&... args ) { return std::rotate_copy                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) sample                            ( auto&&... args ) { return std::sample                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) search                            ( auto&&... args ) { return std::search                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) search_n                          ( auto&&... args ) { return std::search_n                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_difference                    ( auto&&... args ) { return std::set_difference                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_intersection                  ( auto&&... args ) { return std::set_intersection                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_symmetric_difference          ( auto&&... args ) { return std::set_symmetric_difference         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_union                         ( auto&&... args ) { return std::set_union                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shift_left                        ( auto&&... args ) { return std::shift_left                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shift_right                       ( auto&&... args ) { return std::shift_right                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shuffle                           ( auto&&... args ) { return std::shuffle                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) sort                              ( auto&&... args ) { return std::sort                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) stable_partition                  ( auto&&... args ) { return std::stable_partition                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) stable_sort                       ( auto&&... args ) { return std::stable_sort                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) swap_ranges                       ( auto&&... args ) { return std::swap_ranges                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform                         ( auto&&... args ) { return std::transform                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform_exclusive_scan          ( auto&&... args ) { return std::transform_exclusive_scan         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform_inclusive_scan          ( auto&&... args ) { return std::transform_inclusive_scan         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform_reduce                  ( auto&&... args ) { return std::transform_reduce                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) unique                            ( auto&&... args ) { return std::unique                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) unique_copy                       ( auto&&... args ) { return std::unique_copy                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) upper_bound                       ( auto&&... args ) { return std::upper_bound                      (std::forward<decltype(args)>(args)...); }

    public: // Linalg
        struct linalg
        {
            constexpr static void plus            ( auto, auto, auto );
            constexpr static void minus           ( auto, auto, auto );
            constexpr static void multiply        ( auto, auto, auto );
            constexpr static void dot             ( auto, auto, auto );
            constexpr static void cross           ( auto, auto, auto );
            constexpr static void convolve        ( auto, auto, auto );

            constexpr static auto transpose       ( auto, auto );
            constexpr static auto hermitian       ( auto, auto );

            constexpr static void det             ( auto, auto& );
            constexpr static void eigen           ( auto, auto, auto );
            constexpr static void eigen_value     ( auto, auto );
            constexpr static void eigen_vector    ( auto, auto );
            constexpr static void evd             ( auto, auto, auto, auto );
            constexpr static void inverse         ( auto, auto );
            constexpr static void lu              ( auto, auto, auto, auto );
            constexpr static void qr              ( auto, auto, auto );
            constexpr static void rank            ( auto, int& );
            constexpr static void singular        ( auto, auto, auto, auto );
            constexpr static void singular_value  ( auto, auto );
            constexpr static void singular_vector ( auto, auto, auto );
            constexpr static void svd             ( auto, auto, auto, auto );
            constexpr static void tr              ( auto, auto& );

            constexpr static void fft             ( auto, auto );
            constexpr static void ifft            ( auto, auto );
        };

};

cpu::execution_context_type cpu::execution_context = cpu::execution_context_type(std::thread::hardware_concurrency());

#include "type/stride_pointer.hpp"

#include "memory/accessor_type.hpp"

#include "linalg/linalg.hpp"