#pragma once

/** Notes:
  * An binary_tree-like object should only focus on memory management, and conatains functions below:
  * ( with []'ed with optional position-hint input. )
  *
  ** construcor, destructor, assignment.
  ** size(), empty().
  ** begin(), clear(), end(), find, min, mid, max, push[], pop[]. { Function in this line always returns const_iterator }.
  *
  * and typedefs below:
  *
  ** value_type, const_iterator.
  *
  */

#include "binary_node_interface.hpp"

#include "binary_tree.hpp"
#include "binary_search_tree.hpp"
#include "redblack_tree.hpp"