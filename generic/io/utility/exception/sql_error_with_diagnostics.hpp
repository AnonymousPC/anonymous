#pragma once

namespace detail
{
    class sql_error_with_diagnostics
        extends public boost::mysql::error_with_diagnostics
    {
        public: // Core
            sql_error_with_diagnostics ( const boost::mysql::error_with_diagnostics& );

        public: // What
            virtual const char* what ( ) const noexcept;

        private: // Data
            string error_what = "";
    };
} // namespace detail

#if dll
    #include "sql_error_with_diagnostics.cpp"
#endif