class cuda
{
    public: // Execution
     // using execution_context_type = not supported;
     // inline static execution_context_type execution_context = not supported;

    public: // Type
        template < class type > using value_type      = type;
        template < class type > using reference       = thrust::device_reference<      type>;
        template < class type > using const_reference = thrust::device_reference<const type>;
        template < class type > using pointer         = thrust::device_ptr      <      type>;
        template < class type > using const_pointer   = thrust::device_ptr      <const type>;
        
    public: // Memory
        template < class type > using allocator   = thrust::device_allocator<type>;
                                using layout_type = std::layout_left;
        template < class type > using accessor_type = ::cuda::std::default_accessor<type>;

    public: // Operator
        template < class type = void > using plus          = ::cuda::std::plus         <type>;
        template < class type = void > using minus         = ::cuda::std::minus        <type>;
        template < class type = void > using multiplies    = ::cuda::std::multiplies   <type>;
        template < class type = void > using divides       = ::cuda::std::divides      <type>;
        template < class type = void > using modulus       = ::cuda::std::modulus      <type>;
        template < class type = void > using negate        = ::cuda::std::negate       <type>;
        template < class type = void > using equal_to      = ::cuda::std::equal_to     <type>;
        template < class type = void > using not_equal_to  = ::cuda::std::not_equal_to <type>;
        template < class type = void > using less          = ::cuda::std::less         <type>;
        template < class type = void > using less_equal    = ::cuda::std::less_equal   <type>;
        template < class type = void > using greater       = ::cuda::std::greater      <type>;
        template < class type = void > using greater_equal = ::cuda::std::greater_equal<type>; 
        template < class type = void > using logical_and   = ::cuda::std::logical_and  <type>;
        template < class type = void > using logical_or    = ::cuda::std::logical_or   <type>;
        template < class type = void > using logical_not   = ::cuda::std::logical_not  <type>;
        template < class type = void > using bit_and       = ::cuda::std::bit_and      <type>;
        template < class type = void > using bit_or        = ::cuda::std::bit_or       <type>;
        template < class type = void > using bit_xor       = ::cuda::std::bit_xor      <type>;
        template < class type = void > using bit_not       = ::cuda::std::bit_not      <type>;
     // template < class type = void > using hash          = not supported;

    public: // Traits
        template < class type > using allocator_traits = ::cuda::std::allocator_traits<type>;
        template < class type > using iterator_traits  = ::cuda::std::iterator_traits <type>;
        template < class type > using char_traits      = ::cuda::std::char_traits     <type>;

    public: // Structure
        template < class type1, class type2 > using pair  = ::cuda::std::pair <type1,type2>;
        template < class... types >           using tuple = ::cuda::std::tuple<types...>;

    public: // Container
     //                                                                                                                                             using any            = not supported;
        template < class type, int len >                                                                                                            using array          = ::cuda::std::array         <type,len>;
     // template < class type, class traits = char_traits<type>, class alloc = allocator<type> >                                                    using basic_string   = not supported;
        template < int len >                                                                                                                        using bitset         = ::cuda::std::bitset        <len>;
     // template < class type, class alloc = allocator<type> >                                                                                      using deque          = not supported;
        template < class type, class error >                                                                                                        using expected       = ::cuda::std::expected      <type,error>;
     // template < class type, class alloc = allocator<type> >                                                                                      using forward_list   = not supported;
     // template < class type >                                                                                                                     using function       = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using hive           = not supported;
        template < class type, int len >                                                                                                            using inplace_vector = ::cuda::std::inplace_vector<type,len>;
     // template < class type, class alloc = allocator<type> >                                                                                      using list           = not supported;
     // template < class type1, class type2, class compare = less<>, class alloc = allocator<pair<const type1,type2>> >                             using map            = not supported;
        template < class type >                                                                                                                     using optional       = ::cuda::std::optional      <type>;
     // template < class type, class compare = less<>, class alloc = allocator<type> >                                                              using priority_queue = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using queue          = not supported;
     // template < class type, class compare = less<>, class alloc = allocator<type> >                                                              using set            = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using stack          = not supported;
     // template < class type1, class type2, class hash = hash<type1>, class equal = equal_to<>, class alloc = allocator<pair<const type1,type2>> > using unordered_map  = not supported;
     // template < class type, class hash = hash<type>, class equal = equal_to<>, class alloc = allocator<type> >                                   using unordered_set  = not supported;
     // template < class type, class alloc = allocator<type> >                                                                                      using valarray       = not supported;
        template < class... types >                                                                                                                 using variant        = ::cuda::std::variant       <types...>;
        template < class type, class alloc = allocator<type> >                                                                                      using vector         = thrust::device_vector      <type,alloc>;

    public: // Iterator
     // template < class iterator >                 using const_iterator     = not supported;
     // template < class iterator >                 using move_iterator      = not supported;
     // template < class iterator >                 using counted_iterator   = not supported;
        template < class iterator >                 using reverse_iterator   = thrust::reverse_iterator<iterator>;
        template < class iterator >                 using stride_iterator    = thrust::strided_iterator<iterator,thrust::runtime_value<::cuda::std::iter_difference_t<iterator>>>;
        template < class iterator, class function > using transform_iterator = thrust::transform_iterator<function,iterator>;

    public: // Algorithm
     // constexpr static decltype(auto) accumulate                        ( auto&&... args ) { return thrust::accumulate                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) adjacent_difference               ( auto&&... args ) { return thrust::adjacent_difference              (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) adjacent_find                     ( auto&&... args ) { return thrust::adjacent_find                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) all_of                            ( auto&&... args ) { return thrust::all_of                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) any_of                            ( auto&&... args ) { return thrust::any_of                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) binary_search                     ( auto&&... args ) { return thrust::binary_search                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy                              ( auto&&... args ) { return thrust::copy                             (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) copy_backward                     ( auto&&... args ) { return thrust::copy_backward                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_if                           ( auto&&... args ) { return thrust::copy_if                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_n                            ( auto&&... args ) { return thrust::copy_n                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) count                             ( auto&&... args ) { return thrust::count                            (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) count_if                          ( auto&&... args ) { return thrust::count_if                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) equal                             ( auto&&... args ) { return thrust::equal                            (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) equal_range                       ( auto&&... args ) { return thrust::equal_range                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) exclusive_scan                    ( auto&&... args ) { return thrust::exclusive_scan                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) fill                              ( auto&&... args ) { return thrust::fill                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) fill_n                            ( auto&&... args ) { return thrust::fill_n                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find                              ( auto&&... args ) { return thrust::find                             (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) find_end                          ( auto&&... args ) { return thrust::find_end                         (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) find_first_of                     ( auto&&... args ) { return thrust::find_first_of                    (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_if                           ( auto&&... args ) { return thrust::find_if                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_if_not                       ( auto&&... args ) { return thrust::find_if_not                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) for_each                          ( auto&&... args ) { return thrust::for_each                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) for_each_n                        ( auto&&... args ) { return thrust::for_each_n                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) generate                          ( auto&&... args ) { return thrust::generate                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) generate_n                        ( auto&&... args ) { return thrust::generate_n                       (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) includes                          ( auto&&... args ) { return thrust::includes                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) inclusive_scan                    ( auto&&... args ) { return thrust::inclusive_scan                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) inner_product                     ( auto&&... args ) { return thrust::inner_product                    (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) inplace_merge                     ( auto&&... args ) { return thrust::inplace_merge                    (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) iota                              ( auto&&... args ) { return thrust::iota                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_partitioned                    ( auto&&... args ) { return thrust::is_partitioned                   (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) is_permutation                    ( auto&&... args ) { return thrust::is_permutation                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_sorted                         ( auto&&... args ) { return thrust::is_sorted                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_sorted_until                   ( auto&&... args ) { return thrust::is_sorted_until                  (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) lower_bound                       ( auto&&... args ) { return thrust::lower_bound                      (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) lexicographical_compare           ( auto&&... args ) { return thrust::lexicographical_compare          (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) lexicographical_compare_three_way ( auto&&... args ) { return thrust::lexicographical_compare_three_way(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) max_element                       ( auto&&... args ) { return thrust::max_element                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) merge                             ( auto&&... args ) { return thrust::merge                            (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) min_element                       ( auto&&... args ) { return thrust::min_element                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) minmax_element                    ( auto&&... args ) { return thrust::minmax_element                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) mismatch                          ( auto&&... args ) { return thrust::mismatch                         (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) move                              ( auto&&... args ) { return thrust::move                             (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) move_backward                     ( auto&&... args ) { return thrust::move_backward                    (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) next_permutation                  ( auto&&... args ) { return thrust::next_permutation                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) none_of                           ( auto&&... args ) { return thrust::none_of                          (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) nth_element                       ( auto&&... args ) { return thrust::nth_element                      (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) partial_sort                      ( auto&&... args ) { return thrust::partial_sort                     (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) partial_sort_copy                 ( auto&&... args ) { return thrust::partial_sort_copy                (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) partial_sum                       ( auto&&... args ) { return thrust::partial_sum                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition                         ( auto&&... args ) { return thrust::partition                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition_copy                    ( auto&&... args ) { return thrust::partition_copy                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition_point                   ( auto&&... args ) { return thrust::partition_point                  (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) prev_permutation                  ( auto&&... args ) { return thrust::prev_permutation                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reduce                            ( auto&&... args ) { return thrust::reduce                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove                            ( auto&&... args ) { return thrust::remove                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_copy                       ( auto&&... args ) { return thrust::remove_copy                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_copy_if                    ( auto&&... args ) { return thrust::remove_copy_if                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_if                         ( auto&&... args ) { return thrust::remove_if                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace                           ( auto&&... args ) { return thrust::replace                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_copy                      ( auto&&... args ) { return thrust::replace_copy                     (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_copy_if                   ( auto&&... args ) { return thrust::replace_copy_if                  (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_if                        ( auto&&... args ) { return thrust::replace_if                       (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reverse                           ( auto&&... args ) { return thrust::reverse                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reverse_copy                      ( auto&&... args ) { return thrust::reverse_copy                     (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) rotate                            ( auto&&... args ) { return thrust::rotate                           (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) rotate_copy                       ( auto&&... args ) { return thrust::rotate_copy                      (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) sample                            ( auto&&... args ) { return thrust::sample                           (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) search                            ( auto&&... args ) { return thrust::search                           (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) search_n                          ( auto&&... args ) { return thrust::search_n                         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_difference                    ( auto&&... args ) { return thrust::set_difference                   (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_intersection                  ( auto&&... args ) { return thrust::set_intersection                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_symmetric_difference          ( auto&&... args ) { return thrust::set_symmetric_difference         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_union                         ( auto&&... args ) { return thrust::set_union                        (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) shift_left                        ( auto&&... args ) { return thrust::shift_left                       (std::forward<decltype(args)>(args)...); }
     // constexpr static decltype(auto) shift_right                       ( auto&&... args ) { return thrust::shift_right                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shuffle                           ( auto&&... args ) { return thrust::shuffle                          (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) sort                              ( auto&&... args ) { return thrust::sort                             (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) stable_partition                  ( auto&&... args ) { return thrust::stable_partition                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) stable_sort                       ( auto&&... args ) { return thrust::stable_sort                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) swap_ranges                       ( auto&&... args ) { return thrust::swap_ranges                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform                         ( auto&&... args ) { return thrust::transform                        (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform_exclusive_scan          ( auto&&... args ) { return thrust::transform_exclusive_scan         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform_inclusive_scan          ( auto&&... args ) { return thrust::transform_inclusive_scan         (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform_reduce                  ( auto&&... args ) { return thrust::transform_reduce                 (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) unique                            ( auto&&... args ) { return thrust::unique                           (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) unique_copy                       ( auto&&... args ) { return thrust::unique_copy                      (std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) upper_bound                       ( auto&&... args ) { return thrust::upper_bound                      (std::forward<decltype(args)>(args)...); }

    public: // Linalg
        struct linalg
        {
            constexpr static void unary_plus        ( const auto,             auto );
            constexpr static void unary_minus       ( const auto,             auto );
            constexpr static void plus              ( const auto, const auto, auto );
            constexpr static void minus             ( const auto, const auto, auto );
            constexpr static void left_scale        ( const auto, const auto, auto );
            constexpr static void right_scale       ( const auto, const auto, auto );
            constexpr static void multiply          ( const auto, const auto, auto );
            constexpr static void divide            ( const auto, const auto, auto );
            constexpr static void plus_equal        (       auto, const auto );
            constexpr static void minus_equal       (       auto, const auto );
            constexpr static void right_scale_equal (       auto, const auto );
            constexpr static void multiply_equal    (       auto, const auto );
            constexpr static void divide_equal      (       auto, const auto );

            constexpr static void convolve          ( const auto, const auto, auto );
            constexpr static void cross             ( const auto, const auto, auto );
            constexpr static void dot               ( const auto, const auto, auto );
            constexpr static void fft               ( const auto,             auto );
            constexpr static void ifft              ( const auto,             auto );
            constexpr static void tensor            ( const auto, const auto, auto );

            constexpr static void det               ( const auto,             auto );
            constexpr static void eigen             ( const auto,             auto, auto );
            constexpr static void eigen_value       ( const auto,             auto );
            constexpr static void eigen_vector      ( const auto,             auto );
            constexpr static void evd               ( const auto,             auto, auto, auto );
            constexpr static void inverse           ( const auto,             auto );
            constexpr static void lu                ( const auto,             auto, auto, auto );
            constexpr static void qr                ( const auto,             auto, auto );
            constexpr static void rank              ( const auto,             auto );
            constexpr static void singular          ( const auto,             auto, auto, auto );
            constexpr static void singular_value    ( const auto,             auto );
            constexpr static void singular_vector   ( const auto,             auto, auto );
            constexpr static void svd               ( const auto,             auto, auto, auto );
            constexpr static void tr                ( const auto,             auto );

            constexpr static auto transpose         ( const auto,             auto );
            constexpr static auto hermitian         ( const auto,             auto );
        };

    public: // Random
        using random_context_type = thrust::default_random_engine;
        inline static thread_local random_context_type random_context = random_context_type(std::random_device()());

     //                                  using bernoulli_distribution          = not supported;
     // template < integral       type > using binomial_distribution           = not supported;
     // template < floating_point type > using cauchy_distribution             = not supported;
     // template < floating_point type > using chi_squared_distribution        = not supported;
     // template < integral       type > using discrete_distribution           = not supported;
     // template < floating_point type > using exponential_distribution        = not supported;
     // template < floating_point type > using extreme_value_distribution      = not supported;
     // template < floating_point type > using fisher_f_distribution           = not supported;
     // template < floating_point type > using gamma_distribution              = not supported;
     // template < integral       type > using geometric_distribution          = not supported;
     // template < integral       type > using lognormal_distribution          = not supported;
     // template < integral       type > using negative_binomial_distribution  = not supported;
        template < integral       type > using normal_distribution             = thrust::normal_distribution      <type>;
     // template < floating_point type > using piecewise_constant_distribution = not supported;
     // template < floating_point type > using piecewise_linear_distribution   = not supported;
     // template < integral       type > using poisson_distribution            = not supported;
     // template < floating_point type > using student_t_distribution          = not supported;
        template < integral       type > using uniform_int_distribution        = thrust::uniform_int_distribution <type>;
        template < floating_point type > using uniform_real_distribution       = thrust::uniform_real_distribution<type>;
     // template < floating_point type > using weibull_distribution            = not supported;
};

// #include "memory/accessor_type.hpp"