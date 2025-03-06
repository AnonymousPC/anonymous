#pragma once

template < class type >
class opencl::pointer
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Typedef
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using value_type        = opencl::template value_type<type>;
        using reference         = opencl::template reference <type>;
     // using pointer           = opencl::template pointer   <type>;
        using difference_type   = std::ptrdiff_t;

    public: // Core 
        pointer ( ) = default;

    public: // Const
        explicit pointer ( const_pointer<type> cvt ) extends buf ( cvt.buf ), idx ( cvt.idx ) { };
        pointer& operator = ( const_pointer<type> ) = delete;

    public: // Operator
        reference operator *  ( )                   const { return reference(buf, idx); };
        reference operator [] ( difference_type t ) const { return reference(buf, idx + t); };

    public: // Boost.compute
        pointer ( boost::compute::buffer, size_t );
        pointer ( boost::compute::buffer_iterator<type> );
        operator  boost::compute::buffer_iterator<type> ( ) const;
        pointer ( boost::compute::detail::device_ptr<type> );
        operator  boost::compute::detail::device_ptr<type> ( ) const;
        type read  (              boost::compute::command_queue& ) const;
        void write ( const type&, boost::compute::command_queue& ) const;
        template < class... expr > auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;
        boost::compute::buffer get_buffer ( ) const;
        size_t                 get_index  ( ) const;

    public: // Friend
        friend class const_pointer<type>;
};

template < class type >
class opencl::const_pointer
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;
    
    public: // Typedef
        using iterator_concept  = std::contiguous_iterator_tag;
        using iterator_category = std::contiguous_iterator_tag;
        using value_type        = opencl::template value_type     <type>;
        using reference         = opencl::template const_reference<type>;
     // using pointer           = opencl::template const_pointer  <type>;
        using difference_type   = std::ptrdiff_t;

    public: // Core 
        const_pointer ( ) = default;

    public: // Const
        const_pointer ( pointer<type> cvt ) extends buf ( cvt.buf ), idx ( cvt.idx ) { };
        const_pointer& operator = ( pointer<type> cvt ) { buf = cvt.buf; idx = cvt.idx; return self; };

    public: // Operator
        reference operator *  ( )                   const { return reference(buf, idx); };
        reference operator [] ( difference_type t ) const { return reference(buf, idx + t); };

    public: // Boost.compute
        const_pointer ( boost::compute::buffer, size_t );
        const_pointer ( boost::compute::buffer_iterator<type> );
        operator        boost::compute::buffer_iterator<type> ( ) const = delete;
        const_pointer ( boost::compute::detail::device_ptr<type> );
        operator        boost::compute::detail::device_ptr<type> ( ) const = delete; 
        type read  (              boost::compute::command_queue& ) const;
        void write ( const type&, boost::compute::command_queue& ) const = delete;
        template < class... expr > auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;
        const boost::compute::buffer get_buffer ( ) const;
        size_t                       get_index  ( ) const;

    public: // Friend
        friend class pointer<type>;
};

template < class type > bool                                  operator ==  ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > bool                                  operator ==  ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > bool                                  operator ==  ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > bool                                  operator ==  ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > std::partial_ordering                 operator <=> ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > opencl::template       pointer<type>  operator  +  ( opencl::template       pointer<type>,  std::ptrdiff_t                       );
template < class type > opencl::template const_pointer<type>  operator  +  ( opencl::template const_pointer<type>,  std::ptrdiff_t                       );
template < class type > opencl::template       pointer<type>  operator  +  ( std::ptrdiff_t,                        opencl::template       pointer<type> );
template < class type > opencl::template const_pointer<type>  operator  +  ( std::ptrdiff_t,                        opencl::template const_pointer<type> );
template < class type > opencl::template       pointer<type>  operator  -  ( opencl::template       pointer<type>,  std::ptrdiff_t                       );
template < class type > opencl::template const_pointer<type>  operator  -  ( opencl::template const_pointer<type>,  std::ptrdiff_t                       );
template < class type > std::ptrdiff_t                        operator  -  ( opencl::template       pointer<type>,  opencl::template       pointer<type> );
template < class type > std::ptrdiff_t                        operator  -  ( opencl::template       pointer<type>,  opencl::template const_pointer<type> );
template < class type > std::ptrdiff_t                        operator  -  ( opencl::template const_pointer<type>,  opencl::template       pointer<type> );
template < class type > std::ptrdiff_t                        operator  -  ( opencl::template const_pointer<type>,  opencl::template const_pointer<type> );
template < class type > opencl::template       pointer<type>& operator  += ( opencl::template       pointer<type>&, std::ptrdiff_t                       );
template < class type > opencl::template const_pointer<type>& operator  += ( opencl::template const_pointer<type>&, std::ptrdiff_t                       );
template < class type > opencl::template       pointer<type>& operator  -= ( opencl::template       pointer<type>&, std::ptrdiff_t                       );
template < class type > opencl::template const_pointer<type>& operator  -= ( opencl::template const_pointer<type>&, std::ptrdiff_t                       );
template < class type > opencl::template       pointer<type>& operator  ++ ( opencl::template       pointer<type>&                                       );
template < class type > opencl::template const_pointer<type>& operator  ++ ( opencl::template const_pointer<type>&                                       );
template < class type > opencl::template       pointer<type>  operator  ++ ( opencl::template       pointer<type>&, int                                  );
template < class type > opencl::template const_pointer<type>  operator  ++ ( opencl::template const_pointer<type>&, int                                  );
template < class type > opencl::template       pointer<type>& operator  -- ( opencl::template       pointer<type>&                                       );
template < class type > opencl::template const_pointer<type>& operator  -- ( opencl::template const_pointer<type>&                                       );
template < class type > opencl::template       pointer<type>  operator  -- ( opencl::template       pointer<type>&, int                                  );
template < class type > opencl::template const_pointer<type>  operator  -- ( opencl::template const_pointer<type>&, int                                  );

#include "pointer.ipp"