#pragma once
#include "../array/array.hpp"



/// Class

template < class char_type >
class basic_string;

template < class char_type >
class basic_string_range_view;

template < class char_type >
class basic_string_view;




/// Regex

template < class char_type >
class basic_regex;



/// Algo

template < class string_type, class char_type >
class string_algo;



/// Include

// In folder "string_base"
#include "string_base/string_global.hpp" // First.
#include "string_base/string_algo.hpp"

// In folder "string_class"
#include "string_class/string.hpp"

// In folder "string_regex"
#include "string_regex/regex.hpp"

// In folder "string_view"
#include "string_view/string_range_view.hpp"
#include "string_view/string_view.hpp"
