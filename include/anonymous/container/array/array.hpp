constexpr int max_dim = 4;

#include "array_detail/declaration.hpp"
#include "array_detail/array_shape.hpp"
#include "array_detail/array_upper_1d.hpp"
#include "array_detail/array_upper_nd.hpp"
#include "array_detail/array_upper_xd.hpp"
#include "array_detail/array_uppers_1d.hpp"
#include "array_detail/array_uppers_nd.hpp"
#include "array_detail/array_lower_nd.hpp"
#include "array_detail/array_info_nd.hpp"
#include "array_detail/array_deduction.hpp"
#include "array_detail/transform_to_array.hpp"

#include "array_class/array_1d.hpp"
#include "array_class/array_nd.hpp"
#include "array_class/array_xd.hpp"





// These implemention files are included seperately due to possible recursive dependencies.
// e.g. array<int,1> -> detail::array_upper<int,1> -> array<int,1> detail::array_upper shape() -> array<int,1>

#include "array_detail/array_shape.cpp"
#include "array_detail/array_upper_1d.cpp"
#include "array_detail/array_upper_nd.cpp"
#include "array_detail/array_upper_xd.cpp"
#include "array_detail/array_uppers_1d.cpp"
#include "array_detail/array_uppers_nd.cpp"
#include "array_detail/array_lower_nd.cpp"
#include "array_detail/array_info_nd.cpp"
#include "array_detail/array_deduction.cpp"
#include "array_detail/transform_to_array.cpp"

#include "array_class/array_1d.cpp"
#include "array_class/array_nd.cpp"
#include "array_class/array_xd.cpp"



// Explicit include "container_interface.cpp"
//#include "../utility/container_interface/container_interface.cpp"