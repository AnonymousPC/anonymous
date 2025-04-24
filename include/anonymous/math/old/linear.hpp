/// Define

#define decay<decltype(left)>                         decay<decltype(left)>
#define typename decay<decltype(left )>::value_type          typename decay<decltype(left)>::value_type
#define left_iterate_type        typename decay<decltype(left)>::iterate_type
#define decay<decltype(right)>                        decay<decltype(right)>
#define typename decay<decltype(right)>::value_type         typename decay<decltype(right)>::value_type
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

#include "third_party/eigen.cpp"
#include "1d/convolve.cpp"
#include "1d/cross.cpp"
#include "1d/dct.cpp"
#include "1d/dot.cpp"
#include "1d/fft.cpp"
#include "1d/norm.cpp"
#include "1d/operator.cpp"
#include "1d/tensor.cpp"
#include "2d/convolve.cpp"
#include "2d/det.cpp"
#include "2d/eigen.cpp"
#include "2d/evd.cpp"
#include "2d/inverse.cpp"
#include "2d/lu.cpp"
#include "2d/norm.cpp"
#include "2d/operator.cpp"
#include "2d/qr.cpp"
#include "2d/rank.cpp"
#include "2d/singular.cpp"
#include "2d/svd.cpp"
#include "2d/tr.cpp"
#include "nd/operator.cpp"
#include "nd/swap.cpp"
#include "nd/transpose.cpp"


/// Undef

#undef decay<decltype(left)>
#undef typename decay<decltype(left )>::value_type
#undef left_iterate_type
#undef decay<decltype(right)>
#undef typename decay<decltype(right)>::value_type
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