/* .ipp files are explicit externally included, which
 * instantiates array templates in a correct order

 * example:
 * array.shape()                => static_array<int,...>
 * array_algo.where()           => array<int>
 * detail::array_lower.[[data]] => detail::array_upper<...>
 */

constexpr int max_dim = 3;

// .hpp

#include "array_base/array_detail.hpp"
#include "array_base/array_deduction.hpp"

#include "array_base/array_global.hpp"
#include "array_base/array_line_iterator.hpp"
#include "array_base/array_upper.hpp"
#include "array_base/array_lower.hpp"
#include "array_base/array_info.hpp"
#include "array_base/array_algo_1d.hpp"
#include "array_base/array_algo_nd.hpp"


#include "array_class/array_1d.hpp"
#include "array_class/array_nd.hpp"
#include "array_class/array_xd.hpp"
#include "array_class/static_array.hpp"
#include "array_class/inplace_array.hpp"



// .ipp

#include "array_base/array_global.cpp"
#include "array_base/array_upper.cpp"
#include "array_base/array_lower.cpp"
#include "array_base/array_info.cpp"
#include "array_base/array_algo_1d.cpp"
#include "array_base/array_algo_nd.cpp"

#include "array_class/array_1d.cpp"
#include "array_class/array_nd.cpp"
#include "array_class/array_xd.cpp"
#include "array_class/static_array.cpp"
#include "array_class/inplace_array.cpp"