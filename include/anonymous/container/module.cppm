export module anonymous:container;
import :basic;
import std;
import boost;

export namespace anonymous
{
    /// Macro
    #include "macro.cpp"
    
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
    #include "utility/utility.hpp"
    #include "discrete/discrete.hpp"
    #include "polymorphic/polymorphic.hpp"
    #include "array/array.hpp"
    #include "chain/chain.hpp"
    #include "collection/collection.hpp"
   // #include "string/string.hpp"
   // #include "utility/utility.cpp"
}

export namespace std
{
    // #include "utility/export/std/formatter.hpp"
    // #include "utility/export/std/hash.hpp"
    // #include "utility/export/std/tuple_size.hpp"
    // #include "utility/export/std/tuple_element.hpp"
    // #include "utility/export/std/get.hpp"   
}
