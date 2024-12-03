#pragma once

/// Global

template < class type, class original_less >
struct as_compares; // The as_compares defines 2 elements: less and equal_to.

template < class type1, class type2, class original_key_less >
struct as_key_compares; // The as_key_compares defines 2 elements: (key) less and (key) equal_to.

template < class type1, class type2, class original_value_less >
struct as_value_pointer_compares; // The as_value_pointer_compares defines 2 elements: (value*) less and (value*) equal_to.

template < class type, class original_hash >
struct as_hash;

template < class type1, class type2, class original_key_hash >
struct as_key_hash;

template < class type1, class type2, class original_value_hash >
struct as_value_pointer_hash;



/// Data-type

template < class type1, class type2 >
class map_pair;



/// Tree-container

template < class type, class node >
class binary_node_interface;

template < class type >
class binary_tree_node;

template < class type >
class binary_search_tree_node;

template < class type >
class redblack_tree_node;

template < class type >
using rb_tree_node = redblack_tree_node<type>;



template < class type,
           class node = binary_tree_node<type> >
class binary_tree;

template < class type,
           class compares = as_compares<type,std::less<>>,
           class node     = binary_search_tree_node<type> >
class binary_search_tree;

template < class type,
           class compares = as_compares<type,std::less<>>,
           class node     = redblack_tree_node<type> >
class redblack_tree;

template < class type,
           class compares = as_compares<type,std::less<>>,
           class node     = rb_tree_node<type> >
using rb_tree = redblack_tree<type,compares,node>;



/// Flat-container

template < class type,
           class compares = as_compares<type,std::less<>> >
class sorted_vector;



/// Hash-container

template < class type >
struct hash;

template < class type,
           class hash = hash<type> >
class hash_table;




/// Class

template < class type, class compare, class container >
class basic_set;

template < class type1, class type2, class key_compare, class container >
class basic_map;

template < class type1, class type2, class key_compare, class value_compare, class container1, class container2 >
class basic_bimap;



template < class type,
           class less = std::less<> >
    requires function_type<less,bool(type,type)>
using set = basic_set<type,less,rb_tree<type,as_compares<type,less>>>;

template < class type1,
           class type2,
           class key_less = std::less<> >
    requires function_type<key_less,bool(type1,type1)>
using map = basic_map<type1,type2,key_less,rb_tree<map_pair<type1,type2>,as_key_compares<type1,type2,key_less>>>;

template < class type1,
           class type2,
           class key_less = std::less<>,
           class value_less = std::less<> >
    requires function_type<key_less,  bool(type1,type1)> and
             function_type<value_less,bool(type2,type2)>
using bimap = basic_bimap<type1,type2,key_less,value_less,
                          rb_tree<map_pair<type1, type2 >,as_key_compares          <type1,type2,key_less  >>,
                          rb_tree<map_pair<type1*,type2*>,as_value_pointer_compares<type1,type2,value_less>>>;

template < class type,
           class less = std::less<> >
    requires function_type<less,bool(type,type)>
using flat_set = basic_set<type,less,sorted_vector<type,as_compares<type,less>>>;

template < class type1,
           class type2,
           class key_less = std::less<> >
    requires function_type<key_less,bool(type1,type1)>
using flat_map = basic_map<type1,type2,key_less,sorted_vector<map_pair<type1,type2>,as_key_compares<type1,type2,key_less>>>;

template < class type,
           class hash = hash<type> >
    requires std::invocable<hash,type>
using unordered_set = basic_set<type,hash,hash_table<type,as_hash<type,hash>>>;

template < class type1,
           class type2,
           class key_hash = hash<type1> >
    requires std::invocable<key_hash,type1>
using unordered_map = basic_map<type1,type2,key_hash,hash_table<map_pair<type1,type2>,as_key_hash<type1,type2,key_hash>>>;



/// Algo

template < class collection_type, class iterate_type >
class collection_algo;



/// Views

template < class type >
class collection_keys_view;

template < class type >
class collection_values_view;





/// Include

// In folder "collection_base"
#include "collection_base/collection_global.hpp" // First.
#include "collection_base/collection_algo.hpp"

// In folder "collection_class"
#include "collection_class/set.hpp"
#include "collection_class/map.hpp"

// In folder "collection_data"
#include "collection_data/map_pair/map_pair.hpp"
#include "collection_data/flat/sorted_vector.hpp"
#include "collection_data/tree/tree.hpp"

// In folder "collection_view"
#include "collection_view/collection_keys_view.hpp"
#include "collection_view/collection_values_view.hpp"
