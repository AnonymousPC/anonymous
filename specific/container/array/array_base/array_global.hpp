#pragma once

// For std::ostream& opeartor<< ( std::ostream&, const array_type auto& ): See container/utility/print.
// For linear math:                                                        See math/linear.

          std::ostream& operator << ( std::ostream&, const array_type auto& ); // Declaration only, for implemention, see container/utility/print.
constexpr bool          operator == ( const array_type auto&, const array_type auto& );