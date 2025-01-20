#pragma once

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */

#include "array_base/array_global.hpp"
// #include "array_base/array_lower.hpp"
// #include "array_base/array_upper.hpp"
// #include "array_class/array_1d.hpp"
// #include "array_class/array_nd.hpp"
#include "array_class/inplace_array.hpp"
#include "array_class/static_array.hpp"

// #include "array_base/array_global.ipp": this .ipp file does not to be explicit extern included.
// #include "array_base/array_lower.ipp"
// #include "array_base/array_upper.ipp"
// #include "array_class/array_1d.ipp"
// #include "array_class/array_nd.ipp"
#include "array_class/inplace_array.ipp"
#include "array_class/static_array.ipp"