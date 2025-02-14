#pragma once

namespace detail
{
    template < class type >
        requires derived_from<type,std::exception>
    class all_attempts_failure  
        extends public std::exception
    {
        public: // Core
            all_attempts_failure ( input_range auto&& r ) requires same_as<range_value<decltype(r)>,type>;
            
        public: // What
            virtual const char* what ( ) const noexcept;

        private: // Data
            string error_what = "";
    };

    all_attempts_failure ( input_range auto&& r ) -> all_attempts_failure<range_value<decltype(r)>>;

} // namespace detail

#include "all_attempts_failure.ipp"


