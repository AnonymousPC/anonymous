class tbb
{
    public: // Execution
     // using execution_context_type = not supported;
     // inline static execution_context_type execution_context = not supported;

    public: // Type
        template < class type > using value_type      =       type;
        template < class type > using reference       =       type&;
        template < class type > using const_reference = const type&;
        template < class type > using pointer         =       type*;
        template < class type > using const_pointer   = const type*;

    public: // Allocator
        template < class type > using allocator = ::tbb::tbb_allocator<type>;

    public: // Memory
     //                         using layout_type   = not supported;
     // template < class type > using accessor_type = not supported;

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

    public: // Struct
        template < class type1, class type2 > using pair  = std::pair <type1,type2>;
        template < class... types >           using tuple = std::tuple<types...>;

    public: // Container
     //                                                                                                                                             using any             = not supported;
     // template < class type, int len >                                                                                                            using array           = not supported;
     // template < class type, class traits = std::char_traits<type>, class alloc = allocator<type> >                                               using basic_string    = not supported;
     // template < int len >                                                                                                                        using bitset          = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using deque           = not supported;
     // template < class type, class error >                                                                                                        using expected        = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using forward_list    = not supported;
     // template < class type >                                                                                                                     using function        = not supported;
     // template < class type, int len >                                                                                                            using inplace_vector  = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using list            = not supported;
        template < class type1, class type2, class compare = less<>, class alloc = allocator<pair<const type1,type2>> >                             using map             = ::tbb::concurrent_map          <type1,type2,compare,alloc>;
     // template < class type >                                                                                                                     using optional        = not supported;
        template < class type, class compare = less<>, class alloc = allocator<type> >                                                              class priority_queue; // Override pop().
        template < class type, class alloc = allocator<type> >                                                                                      class queue;          // Override pop()
        template < class type, class compare = less<>, class alloc = allocator<type> >                                                              using set             = ::tbb::concurrent_set          <type,compare,alloc>;
     // template < class type, class alloc = allocator<type> >                                                                                      using stack           = not supported;
        template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<>, class alloc = allocator<pair<const type1,type2>> > using unordered_map   = ::tbb::concurrent_unordered_map<type1,type2,hash,equal>; // Use default allocator<std::pair>
        template < class type, class hash = hash<type>, class equal = equal_to<>,  class alloc = allocator<type> >                                  using unordered_set   = ::tbb::concurrent_unordered_set<type,hash,equal,alloc>;
     // template < class type, class alloc = allocator<type> >                                                                                      using valarray        = not supported;
     // template < class... types >                                                                                                                 using variant         = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using vector          = supported, but does not satisfy std::contiguous_range.

    public: // Iterator
     // template < class iterator >                 using const_iterator     = not supported;
     // template < class iterator >                 using move_iterator      = not supported;
     // template < class iterator >                 using counted_iterator   = not supported;
     // template < class iterator >                 using reverse_iterator   = not supported;
     // template < class iterator >                 using stride_iterator    = not supported;
     // template < class iterator, class function > using transform_iterator = not supported;

    public: // Algorithm
     // constexpr static decltype(auto) accumulate                        ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) adjacent_difference               ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) adjacent_find                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) all_of                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) any_of                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) binary_search                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) copy                              ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) copy_backward                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) copy_if                           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) copy_n                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) count                             ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) count_if                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) equal                             ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) equal_range                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) exclusive_scan                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) fill                              ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) fill_n                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) find                              ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) find_end                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) find_first_of                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) find_if                           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) find_if_not                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) for_each                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) for_each_n                        ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) generate                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) generate_n                        ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) includes                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) inclusive_scan                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) inner_product                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) inplace_merge                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) iota                              ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) is_partitioned                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) is_permutation                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) is_sorted                         ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) is_sorted_until                   ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) lower_bound                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) lexicographical_compare           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) lexicographical_compare_three_way ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) max_element                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) merge                             ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) min_element                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) minmax_element                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) mismatch                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) move                              ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) move_backward                     ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) next_permutation                  ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) none_of                           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) nth_element                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) partial_sort                      ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) partial_sort_copy                 ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) partial_sum                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) partition                         ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) partition_copy                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) partition_point                   ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) prev_permutation                  ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) reduce                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) remove                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) remove_copy                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) remove_copy_if                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) remove_if                         ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) replace                           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) replace_copy                      ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) replace_copy_if                   ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) replace_if                        ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) reverse                           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) reverse_copy                      ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) rotate                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) rotate_copy                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) sample                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) search                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) search_n                          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) set_difference                    ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) set_intersection                  ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) set_symmetric_difference          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) set_union                         ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) shift_left                        ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) shift_right                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) shuffle                           ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) sort                              ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) stable_partition                  ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) stable_sort                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) swap_ranges                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) transform                         ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) transform_exclusive_scan          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) transform_inclusive_scan          ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) transform_reduce                  ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) unique                            ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) unique_copy                       ( auto&&... args ) { not supported }
     // constexpr static decltype(auto) upper_bound                       ( auto&&... args ) { not supported }

    public: // Random
     // using random_context_type = not supported;
     // inline static thread_local random_context_type random_context = not supported;

     //                              using bernoulli_distribution          = not supported;
     // template < integral   type > using binomial_distribution           = not supported;
     // template < floating_point type > using cauchy_distribution             = not supported;
     // template < floating_point type > using chi_squared_distribution        = not supported;
     // template < integral   type > using discrete_distribution           = not supported;
     // template < floating_point type > using exponential_distribution        = not supported;
     // template < floating_point type > using extreme_value_distribution      = not supported;
     // template < floating_point type > using fisher_f_distribution           = not supported;
     // template < floating_point type > using gamma_distribution              = not supported;
     // template < integral   type > using geometric_distribution          = not supported;
     // template < integral   type > using lognormal_distribution          = not supported;
     // template < integral   type > using negative_binomial_distribution  = not supported;
     // template < integral   type > using normal_distribution             = not supported;
     // template < floating_point type > using piecewise_constant_distribution = not supported;
     // template < floating_point type > using piecewise_linear_distribution   = not supported;
     // template < integral   type > using poisson_distribution            = not supported;
     // template < floating_point type > using student_t_distribution          = not supported;
     // template < integral   type > using uniform_int_distribution        = not supported;
     // template < floating_point type > using uniform_real_distribution       = not supported;
     // template < floating_point type > using weibull_distribution            = not supported;
};

#include "container/priority_queue.hpp"
#include "container/queue.hpp"