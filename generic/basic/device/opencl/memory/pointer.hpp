#pragma once

template < class type >
class opencl::pointer
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Core 
        pointer ( )                            = default;
        pointer ( const pointer& )             = default;
        pointer& operator = ( const pointer& ) = default;

    public: // Assign
     // pointer& operator = (       pointer<type> );
        pointer& operator = ( const_pointer<type> ) = delete;

    public: // Member
        explicit pointer ( const_pointer<type> );
        reference<type> operator *  ( )     const;
        reference<type> operator [] ( int ) const;

    public: // Boost.compute
        pointer ( boost::compute::buffer, size_t );
        pointer ( boost::compute::buffer_iterator<type> );
        operator  boost::compute::buffer_iterator<type> ( ) const;
        pointer ( boost::compute::detail::device_ptr<type> );
        operator  boost::compute::detail::device_ptr<type> ( ) const;
        template < class expr > auto operator [] ( const boost::compute::detail::meta_kernel_variable<expr>& ) const;

    public: // Member
        boost::compute::buffer get_buffer ( ) const;
        size_t                 get_index  ( ) const;
};

template < class type >
class opencl::const_pointer
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Core 
        const_pointer ( )                                  = default;
        const_pointer ( const const_pointer& )             = default;
        const_pointer& operator = ( const const_pointer& ) = default;

    public: // Assign
        const_pointer& operator = (       pointer<type> );
     // const_pointer& operator = ( const_pointer<type> );

    public: // Member
        const_pointer ( pointer<type> );
        const_reference<type> operator *  ( )     const;
        const_reference<type> operator [] ( int ) const;

    public: // Boost.compute
        const_pointer ( boost::compute::buffer, size_t );
        const_pointer ( boost::compute::buffer_iterator<type> );
        operator        boost::compute::buffer_iterator<type> ( ) const = delete;
        const_pointer ( boost::compute::detail::device_ptr<type> );
        operator        boost::compute::detail::device_ptr<type> ( ) const = delete; 
        template < class expr > auto operator [] ( const boost::compute::detail::meta_kernel_variable<expr>& ) const;

    public: // Member
        boost::compute::buffer get_buffer ( ) const;
        size_t                 get_index  ( ) const;
};

template < class type > bool                                  operator ==  ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > bool                                  operator ==  ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > bool                                  operator ==  ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > bool                                  operator ==  ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > opencl::template       pointer<type>  operator  +  ( opencl::template       pointer<type>,  int                                  );
template < class type > opencl::template const_pointer<type>  operator  +  ( opencl::template const_pointer<type>,  int                                  );
template < class type > opencl::template       pointer<type>  operator  +  ( int,                                   opencl::template       pointer<type> );
template < class type > opencl::template const_pointer<type>  operator  +  ( int,                                   opencl::template const_pointer<type> );
template < class type > opencl::template       pointer<type>  operator  -  ( opencl::template       pointer<type>,  int                                  );
template < class type > opencl::template const_pointer<type>  operator  -  ( opencl::template const_pointer<type>,  int                                  );
template < class type > int                                   operator  -  ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > int                                   operator  -  ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > int                                   operator  -  ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > int                                   operator  -  ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > opencl::template       pointer<type>& operator  += ( opencl::template       pointer<type>&, int                                  );
template < class type > opencl::template const_pointer<type>& operator  += ( opencl::template const_pointer<type>&, int                                  );
template < class type > opencl::template       pointer<type>& operator  -= ( opencl::template       pointer<type>&, int                                  );
template < class type > opencl::template const_pointer<type>& operator  -= ( opencl::template const_pointer<type>&, int                                  );
template < class type > opencl::template       pointer<type>& operator  ++ ( opencl::template       pointer<type>&                                       );
template < class type > opencl::template const_pointer<type>& operator  ++ ( opencl::template const_pointer<type>&                                       );
template < class type > opencl::template       pointer<type>  operator  ++ ( opencl::template       pointer<type>&, int                                  );
template < class type > opencl::template const_pointer<type>  operator  ++ ( opencl::template const_pointer<type>&, int                                  );
template < class type > opencl::template       pointer<type>& operator  -- ( opencl::template       pointer<type>&                                       );
template < class type > opencl::template const_pointer<type>& operator  -- ( opencl::template const_pointer<type>&                                       );
template < class type > opencl::template       pointer<type>  operator  -- ( opencl::template       pointer<type>&, int                                  );
template < class type > opencl::template const_pointer<type>  operator  -- ( opencl::template const_pointer<type>&, int                                  );

#include "pointer.ipp"