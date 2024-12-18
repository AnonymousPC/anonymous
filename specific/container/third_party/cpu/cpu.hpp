#pragma once

class cpu
{
    public: // Allocator
        template < class type > using allocator = std::allocator<type>;

    public: // Compare
        template < class type = void > using equal_to      = std::equal_to<type>;
        template < class type = void > using not_equal_to  = std::not_equal_to<type>;
        template < class type = void > using less          = std::less<type>;
        template < class type = void > using less_equal    = std::less_equal<type>;
        template < class type = void > using greater       = std::greater<type>;
        template < class type = void > using greater_equal = std::greater_equal<type>; 

    public: // Hash
        template < class type > using hash = std::hash<type>;

    public: // Container
        template < class type, class alloc = allocator<type> >                                                                                                using vector         = std::vector<type,alloc>;
        template < class type, int len >                                                                                                                      using array          = std::array<type,len>;
        template < class type, class alloc = allocator<type> >                                                                                                using deque          = std::deque<type,alloc>;
        template < class type, class alloc = allocator<type> >                                                                                                using list           = std::list<type,alloc>;
        template < class type, class container = deque<type> >                                                                                                using stack          = std::stack<type,container>;
        template < class type, class container = deque<type> >                                                                                                using queue          = std::queue<type,container>;
        template < class type, class container = vector<type>, class compare = less<type> >                                                                   using priority_queue = std::priority_queue<type,container,compare>;
        template < class type, class compare = less<type>, class alloc = allocator<type> >                                                                    using set            = std::set<type,compare,alloc>;
        template < class type, class compare = less<type>, class alloc = allocator<type> >                                                                    using flat_set       = boost::container::flat_set<type,compare,alloc>;
        template < class type, class method = hash<type>, class equal = equal_to<type>, class alloc = allocator<type> >                                       using unordered_set  = std::unordered_set<type,method,equal,alloc>;
        template < class type1, class type2, class compare = less<type1>, class alloc = allocator<std::pair<const type1,type2>>>                              using map            = std::map<type1,type2,compare,alloc>;
        template < class type1, class type2, class compare = less<type1>, class alloc = allocator<std::pair<type1,type2>>>                                    using flat_map       = boost::container::flat_map<type1,type2,compare,alloc>;
        template < class type1, class type2, class method = hash<type1>, class equal = equal_to<type>, class alloc = allocator<std::pair<const type1,type2>>> using unordered_map  = std::unordered_map<type1,type2,method,equal,alloc>;
        template < class type1, class type2 >                                                                                                                 using bimap          = boost::bimaps::bimap<type1,type2>;

    public: // Algorithm
        constexpr static decltype(auto) adjacent_find     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) all_of  ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) any_of     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) binary_search     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) count     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) count_if     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_backward     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) copy_n     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) equal     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) equal_range     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) fill     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) fill_n    ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_end     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_first_of     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_if     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) find_if_not     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) for_each     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) for_each_n( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) generate     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) generate_n     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) includes     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) inplace_merge     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_partitioned     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_sorted     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) is_sorted_until     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) lower_bound     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) merge     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) mismatch     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) move     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) move_backward     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) none_of ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) nth_element     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partial_sort     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partial_sort_copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition_copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) partition_point     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_copy_if     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) remove_if     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_copy    ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_copy_if     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) replace_if     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reverse     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) reverse_copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) rotate     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) rotate_copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) sample     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) search     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) search_n     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_difference     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_intersection     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_symmetric_difference     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) set_union     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shift_left     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shift_right     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) shuffle     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) sort     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) stable_partition     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) stable_sort     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) swap_ranges     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) transform     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) unique     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) unique_copy     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
        constexpr static decltype(auto) upper_bound     ( auto&&... args ) { return std::all_of(std::forward<decltype(args)>(args)...); }
}