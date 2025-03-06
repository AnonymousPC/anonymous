#pragma once
    
template < class type >
class opencl::stride_pointer
{
    private: // Data
        opencl::template pointer<type> ptr  = opencl::template pointer<type>();
        int                            step = 1;

    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = opencl::template value_type<type>;
        using reference         = opencl::template reference <type>;
        using pointer           = opencl::template pointer   <type>;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr stride_pointer ( ) = default;
        constexpr stride_pointer ( opencl::template pointer<type> init_ptr, int init_step ) extends ptr ( init_ptr ), step ( init_step ) { }; 

    public: // Const
        constexpr explicit stride_pointer ( const_stride_pointer<type> cvt ) extends ptr ( cvt.ptr ), step ( cvt.step ) { }
        constexpr stride_pointer& operator = ( const_stride_pointer<type> ) = delete;

    public: // Operator.member
        constexpr reference operator *  ( )                   const { return *ptr;    }
        constexpr pointer   operator -> ( )                   const { return  ptr;    }
        constexpr reference operator [] ( difference_type t ) const { return  ptr[t]; }

    public: // Operator.global
        friend constexpr bool                  operator ==  ( const stride_pointer& left, const stride_pointer& right ) { return left.ptr ==  right.ptr; }
        friend constexpr std::partial_ordering operator <=> ( const stride_pointer& left, const stride_pointer& right ) { return left.ptr <=> right.ptr; }
        friend constexpr stride_pointer        operator  +  ( const stride_pointer& left,       difference_type right ) { return stride_pointer(left .ptr + left .step * right, left .step); }
        friend constexpr stride_pointer        operator  +  (       difference_type left, const stride_pointer& right ) { return stride_pointer(right.ptr + right.step * left,  right.step); }
        friend constexpr stride_pointer        operator  -  ( const stride_pointer& left,       difference_type right ) { return stride_pointer(left .ptr - left .step * right, left .step); }
        friend constexpr difference_type       operator  -  ( const stride_pointer& left, const stride_pointer& right ) { [[assume(left.step == right.step)]]; return (left.ptr - right.ptr) / left.step; }
        friend constexpr stride_pointer&       operator ++  (       stride_pointer& left                              ) { left.ptr += left.step;         return left; }
        friend constexpr stride_pointer        operator ++  (       stride_pointer& left,       int                   ) { let it = left; ++left;         return it;   }
        friend constexpr stride_pointer&       operator --  (       stride_pointer& left                              ) { left.ptr -= left.step;         return left; }
        friend constexpr stride_pointer        operator --  (       stride_pointer& left,       int                   ) { let it = left; --left;         return it;   }
        friend constexpr stride_pointer&       operator +=  (       stride_pointer& left,       difference_type right ) { left.ptr += left.step * right; return left; }
        friend constexpr stride_pointer&       operator -=  (       stride_pointer& left,       difference_type right ) { left.ptr -= left.step * right; return left; }

    public: // Extension
        type read  (              boost::compute::command_queue& ) const;
        void write ( const type&, boost::compute::command_queue& ) const;
        template < class index > struct index_expr;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;

    public: // Friend
        friend class const_stride_pointer<type>;
};

template < class type >
class opencl::const_stride_pointer
{
    private: // Data
        opencl::template const_pointer<type> ptr  = opencl::template const_pointer<type>();
        int                                  step = 1;

    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = opencl::template value_type     <type>;
        using reference         = opencl::template const_reference<type>;
        using pointer           = opencl::template const_pointer  <type>;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr const_stride_pointer ( ) = default;
        constexpr const_stride_pointer ( opencl::template const_pointer<type> init_ptr, int init_step ) extends ptr ( init_ptr ), step ( init_step ) { }; 

    public: // Const
        constexpr const_stride_pointer ( stride_pointer<type> cvt ) extends ptr ( cvt.ptr ), step ( cvt.step ) { }
        constexpr const_stride_pointer& operator = ( stride_pointer<type> cvt ) { ptr = cvt.ptr; step = cvt.step; return self; }

    public: // Operator.member
        constexpr reference operator *  ( )                   const { return *ptr;    }
        constexpr pointer   operator -> ( )                   const { return  ptr;    }
        constexpr reference operator [] ( difference_type t ) const { return  ptr[t]; }

    public: // Operator.global
        friend constexpr bool                  operator ==  ( const const_stride_pointer& left, const const_stride_pointer& right ) { return left.ptr ==  right.ptr; }
        friend constexpr std::partial_ordering operator <=> ( const const_stride_pointer& left, const const_stride_pointer& right ) { return left.ptr <=> right.ptr; }
        friend constexpr const_stride_pointer  operator  +  ( const const_stride_pointer& left,       difference_type       right ) { return const_stride_pointer(left .ptr + left .step * right, left .step); }
        friend constexpr const_stride_pointer  operator  +  (       difference_type       left, const const_stride_pointer& right ) { return const_stride_pointer(right.ptr + right.step * left,  right.step); }
        friend constexpr const_stride_pointer  operator  -  ( const const_stride_pointer& left,       difference_type       right ) { return const_stride_pointer(left .ptr - left .step * right, left .step); }
        friend constexpr difference_type       operator  -  ( const const_stride_pointer& left, const const_stride_pointer& right ) { [[assume(left.step == right.step)]]; return (left.ptr - right.ptr) / left.step; }
        friend constexpr const_stride_pointer& operator ++  (       const_stride_pointer& left                                    ) { left.ptr += left.step;         return left; }
        friend constexpr const_stride_pointer  operator ++  (       const_stride_pointer& left,       int                         ) { let it = left; ++left;         return it;   }
        friend constexpr const_stride_pointer& operator --  (       const_stride_pointer& left                                    ) { left.ptr -= left.step;         return left; }
        friend constexpr const_stride_pointer  operator --  (       const_stride_pointer& left,       int                         ) { let it = left; --left;         return it;   }
        friend constexpr const_stride_pointer& operator +=  (       const_stride_pointer& left,       difference_type       right ) { left.ptr += left.step * right; return left; }
        friend constexpr const_stride_pointer& operator -=  (       const_stride_pointer& left,       difference_type       right ) { left.ptr -= left.step * right; return left; }

    public: // Extension
        type read  (              boost::compute::command_queue& ) const;
        void write ( const type&, boost::compute::command_queue& ) const = delete;
        template < class index > struct index_expr;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::meta_kernel_variable      <expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& ) const;
        template < class... expr > constexpr auto operator [] ( const boost::compute::detail::device_ptr_index_expr     <expr...>& ) const;

    public: // Friend
        friend class stride_pointer<type>;
};

#include "stride_pointer.ipp"