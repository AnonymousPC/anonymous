#pragma once

namespace detail
{
    class system_error
        extends public boost::system::system_error
    {
        public: // Core
            system_error ( );
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