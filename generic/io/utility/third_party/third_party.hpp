#pragma once

namespace detail
{
    class boost_system_error
    extends public exception,
            public exception_interface<boost_system_error>
    {
        public:
            boost_system_error ( const boost::system::system_error& e )

        public:
            virtual const char* what ( ) const

        private:
            string error_what = "";
    };
    
} // namespace detail

#if dll
    #include "third_party.cpp"
#endif