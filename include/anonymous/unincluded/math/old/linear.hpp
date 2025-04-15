#pragma once

/// Define

#define left_type                         decay<decltype(left)>
#define left_value_type          typename decay<decltype(left)>::value_type
#define left_iterate_type        typename decay<decltype(left)>::iterate_type
#define right_type                        decay<decltype(right)>
#define right_value_type         typename decay<decltype(right)>::value_type
#define right_iterate_type       typename decay<decltype(right)>::iterate_type
#define vector_type                       decay<decltype(vector)>
#define vector_value_type        typename decay<decltype(vector)>::value_type
#define vector_iterate_type      typename decay<decltype(vector)>::iterate_type
#define matrix_type                       decay<decltype(matrix)>
#define matrix_value_type        typename decay<decltype(matrix)>::value_type
#define matrix_iterate_type      typename decay<decltype(matrix)>::iterate_type
#define ndarray_type                      decay<decltype(ndarray)>
#define ndarray_value_type       typename decay<decltype(ndarray)>::value_type
#define ndarray_iterate_type     typename decay<decltype(ndarray)>::iterate_type

/// Include

#include "third_party/eigen.ipp"
#include "1d/convolve.ipp"
#include "1d/cross.ipp"
#include "1d/dct.ipp"
#include "1d/dot.ipp"
#include "1d/fft.ipp"
#include "1d/norm.ipp"
#include "1d/operator.ipp"
#include "1d/tensor.ipp"
#include "2d/convolve.ipp"
#include "2d/det.ipp"
#include "2d/eigen.ipp"
#include "2d/evd.ipp"
#include "2d/inverse.ipp"
#include "2d/lu.ipp"
#include "2d/norm.ipp"
#include "2d/operator.ipp"
#include "2d/qr.ipp"
#include "2d/rank.ipp"
#include "2d/singular.ipp"
#include "2d/svd.ipp"
#include "2d/tr.ipp"
#include "nd/operator.ipp"
#include "nd/swap.ipp"
#include "nd/transpose.ipp"


/// Undef

#undef left_type
#undef left_value_type
#undef left_iterate_type
#undef right_type
#undef right_value_type
#undef right_iterate_type
#undef vector_type
#undef vector_value_type
#undef vector_iterate_type
#undef matrix_type
#undef matrix_value_type
#undef matrix_iterate_type
#undef ndarray_type
#undef ndarray_value_type
#undef ndarray_iterate_type