#pragma once

namespace detail
{
    class mysql_error_with_diagnostics
        extends public boost::mysql::error_with_diagnostics
    {
        public: // Core
            mysql_error_with_diagnostics ( const boost::mysql::error_with_diagnostics& );

        public: // What
            virtual const char* what ( ) const noexcept;

        private: // Data
            string error_what = "";
    };
} // namespace detail

#if dll
    #include "mysql_error_with_diagnostics.cpp"
#endif