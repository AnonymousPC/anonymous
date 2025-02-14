#pragma once

namespace detail
{
    class system_error
        extends public std::exception
    {
        public: // Core
            system_error ( ) = default;
            system_error ( const boost::system::system_error& );

        public: // What
            virtual const char* what ( ) const noexcept;

        private: // Data
            string error_what = "";
    };
} // namespace detail

#if dll
    #include "system_error.cpp"
#endif