#pragma once
#include "../chain/chain_class/queue.hpp"

/// Class

template < class type, int dim >
class array;

template < class type, int len >
class static_array;

template < class type, int len >
class inplace_array;




/// Algo

template < class array_type, class value_type, class iterate_type = value_type, int dim = 1 >
class array_algo;



/// Views

template < int dim, class coor_type = int >
class array_coordinate;

template < class container_type, int axis, int axis_to_fill = 1 >
class array_axis_view;

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
class array_filter_view;

template < class container_type >
class array_flatten_view;

template < class type, int dim = 1 >
class array_line;

template < class container_type, bool continuous = false >
class array_range_view;

template < class container_type, int dim, int dim_to_fill = 1 >
class array_reshape_view;

template < class container_type >
class array_span_view;

template < class container_type, class type2 >
class array_type_view;

template < class array_view_type >
class array_view_iterator;

template < class array_view_type >
class array_view_const_iterator;





/// Include

// In folder "array_base"
#include "array_base/array_global.hpp" // First.
#include "array_base/array_algo_1d.hpp"
#include "array_base/array_algo_nd.hpp"

// In folder "array_class"
#include "array_class/array_1d.hpp"
#include "array_class/array_-1d.hpp"
#include "array_class/array_nd.hpp"
#include "array_class/static_array.hpp"
#include "array_class/inplace_array.hpp"

// In folder "array_view"
#include "array_view/array_coordinate.hpp" // First.
#include "array_view/array_axis_view.hpp"
#include "array_view/array_filter_view.hpp"
#include "array_view/array_flatten_view.hpp"
#include "array_view/array_line.hpp"
#include "array_view/array_range_view.hpp"
#include "array_view/array_reshape_view.hpp"
#include "array_view/array_span_view.hpp"
#include "array_view/array_type_view.hpp"
#include "array_view/array_view_iterator.hpp"
