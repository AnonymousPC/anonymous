module;
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wassume"
    #pragma GCC diagnostic ignored "-Wuser-defined-literals"
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wassume"
    #pragma clang diagnostic ignored "-Wuser-defined-literals"
#endif

export module anonymous.container;
import std;
import boost;
import anonymous.basic;

export namespace anonymous
{
    /// Concept
    // template < class type > concept container             = forward_range<type> and not std::ranges::enable_view<type>;
    // template < class type > concept sequence_container    = container<type> and random_access_range<type>;
    // template < class type > concept associative_container = container<type> and requires { typename type::compare_type: };
    // template < class type > concept unordered_container   = container<type> and requires { typename type::hash_type;    }; 
    // template < class type > concept structure             = 
    
    /// Class
    template < class type1, class type2 = type1 >                                               class pair;
    template < class... types >                                                                 class tuple;

                                                                                                class any;
    template < class type >                                                                     class function;
    template < class type >                                                                     class optional;
    template < class type1, class type2 >                                                       class expected;
    template < class... types >                                                                 class variant;

    template < class type, int dim = 1,                                    class device = cpu > class array;
    template < class type,                                                 class device = cpu > using vector = array<type,1,device>;
    template < class type,                                                 class device = cpu > using matrix = array<type,2,device>;

    template < class type,                                                 class device = cpu > class deque;
    template < class type,                                                 class device = cpu > class list;
    template < class type,               class compare = std::less<type>,  class device = cpu > class priority_queue;
    template < class type,                                                 class device = cpu > class queue;
    template < class type,                                                 class device = cpu > class stack;

    template < class type,               class compare = std::less<type>,  class device = cpu > class set;
    template < class type1, class type2, class compare = std::less<type1>, class device = cpu > class map;
    template < class type,               class hash    = std::hash<type>,  class device = cpu > class unordered_set;
    template < class type1, class type2, class hash    = std::hash<type1>, class device = cpu > class unordered_map;

    template < class type,                                                 class device = cpu > class string;
                                                                                            
    /// Include
    #include "macro.cpp"
    #include "utility/utility.hpp"
    #include "discrete/discrete.hpp"
    #include "polymorphic/polymorphic.hpp"
    #include "array/array.hpp"
    #include "chain/chain.hpp"
    #include "collection/collection.hpp"
    // #include "string/string.hpp"

} // namespace anonymous

export namespace std
{
    // #include "utility/export/std/formatter.hpp"
    // #include "utility/export/std/hash.hpp"
    // #include "utility/export/std/tuple_size.hpp"
    // #include "utility/export/std/tuple_element.hpp"
    // #include "utility/export/std/get.hpp"
    
} // namespace std
