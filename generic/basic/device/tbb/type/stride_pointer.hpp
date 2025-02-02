#pragma once
    
template < class type >
class tbb::stride_pointer
{
    private: // Data
        type* ptr  = nullptr;
        int   step = 1;

    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = type;
        using reference         = type&;
        using pointer           = type*;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr stride_pointer ( ) = default;
        constexpr stride_pointer ( type* init_ptr, int init_step ) extends ptr ( init_ptr ), step ( init_step ) { }; 

    public: // Operator.member
        constexpr reference operator *  ( )                   const { return *ptr;    }
        constexpr pointer   operator -> ( )                   const { return  ptr;    }
        constexpr reference operator [] ( difference_type t ) const { return  ptr[t]; }

    public: // Operator.global
        friend constexpr bool                 operator ==  ( const stride_pointer& left, const stride_pointer& right ) { return left.ptr ==  right.ptr; }
        friend constexpr std::strong_ordering operator <=> ( const stride_pointer& left, const stride_pointer& right ) { return left.ptr <=> right.ptr; }
        friend constexpr stride_pointer       operator  +  ( const stride_pointer& left,       difference_type right ) { return stride_pointer(left .ptr + left .step * right, left .step); }
        friend constexpr stride_pointer       operator  +  (       difference_type left, const stride_pointer& right ) { return stride_pointer(right.ptr + right.step * left,  right.step); }
        friend constexpr stride_pointer       operator  -  ( const stride_pointer& left,       difference_type right ) { return stride_pointer(left .ptr - left .step * right, left .step); }
        friend constexpr difference_type      operator  -  ( const stride_pointer& left, const stride_pointer& right ) { [[assume(left.step == right.step)]]; return (left.ptr - right.ptr) / left.step; }
        friend constexpr stride_pointer&      operator ++  (       stride_pointer& left                              ) { left.ptr += left.step;         return left; }
        friend constexpr stride_pointer       operator ++  (       stride_pointer& left,       int                   ) { let it = left; ++left;         return it;   }
        friend constexpr stride_pointer&      operator --  (       stride_pointer& left                              ) { left.ptr -= left.step;         return left; }
        friend constexpr stride_pointer       operator --  (       stride_pointer& left,       int                   ) { let it = left; --left;         return it;   }
        friend constexpr stride_pointer&      operator +=  (       stride_pointer& left,       difference_type right ) { left.ptr += left.step * right; return left; }
        friend constexpr stride_pointer&      operator -=  (       stride_pointer& left,       difference_type right ) { left.ptr -= left.step * right; return left; }
};
    
template < class type >
class tbb::const_stride_pointer
{
    private: // Data
        const type* ptr  = nullptr;
        int         step = 1;

    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = type;
        using reference         = const type&;
        using pointer           = const type*;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr const_stride_pointer ( ) = default;
        constexpr const_stride_pointer ( const type* init_ptr, int init_step ) extends ptr ( init_ptr ), step ( init_step ) { }; 

    public: // Operator.member
        constexpr reference operator *  ( )                   const { return *ptr;    }
        constexpr pointer   operator -> ( )                   const { return  ptr;    }
        constexpr reference operator [] ( difference_type t ) const { return  ptr[t]; }

    public: // Operator.global
        friend constexpr bool                  operator ==  ( const const_stride_pointer& left, const const_stride_pointer& right ) { return left.ptr ==  right.ptr; }
        friend constexpr std::strong_ordering  operator <=> ( const const_stride_pointer& left, const const_stride_pointer& right ) { return left.ptr <=> right.ptr; }
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
};