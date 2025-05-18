namespace detail
{
    template < derived_from<std::exception> type >
    class all_attempts_failed
        extends public type
    {
        public: // Core
            all_attempts_failed ( input_range auto&& r ) requires same_as<range_value<decltype(r)>,type>;
            
        public: // What
            virtual const char* what ( ) const noexcept;

        private: // Data
            string error_what = "";
    };

    all_attempts_failed ( input_range auto&& r ) -> all_attempts_failed<range_value<decltype(r)>>;
} // namespace detail

#include "all_attempts_failed.cpp"


