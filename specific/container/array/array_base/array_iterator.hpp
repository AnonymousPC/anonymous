#pragma once

namespace detail
{
    template < class type, int dim, class device > 
    class array_upper; // Declaration.

    template < class type, int dim, class device >
    class array_iterator;

    template < class type, class device >
    class array_iterator<type,1,device>
    {
        private: // Typedef
            using base = device::template pointer<type>;

        private: // Data
            base iter = base();
            int  step = 1;

        public: // Typedef
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = device::template value_type<type>;
            using reference         = device::template reference <type>;
            using pointer           = device::template pointer   <type>;
            using difference_type   = minus_result<pointer,pointer>;

        public: // Core
            constexpr array_iterator ( ) = default;
            constexpr array_iterator ( base init_iter )                extends iter ( init_iter )                     { };
            constexpr array_iterator ( base init_iter, int init_step ) extends iter ( init_iter ), step ( init_step ) { }; 

        public: // Operator.member
            constexpr           operator base ( )                   const { return  iter;    }
            constexpr reference operator *    ( )                   const { return *iter;    }
            constexpr pointer   operator ->   ( )                   const { return  iter;    }
            constexpr reference operator []   ( difference_type t ) const { return  iter[t]; }

        public: // Operator.global
            friend constexpr bool                 operator ==  ( const array_iterator& left, const array_iterator& right ) { return left.iter == right.iter;                                     }
            friend constexpr std::strong_ordering operator <=> ( const array_iterator& left, const array_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter);   }
            friend constexpr array_iterator       operator  +  ( const array_iterator& left,       difference_type right ) { return array_iterator(left .iter + left .step * right, left .step); }
            friend constexpr array_iterator       operator  +  (       difference_type left, const array_iterator& right ) { return array_iterator(right.iter + right.step * left,  right.step); }
            friend constexpr array_iterator       operator  -  ( const array_iterator& left,       difference_type right ) { return array_iterator(left .iter - left .step * right, left .step); }
            friend constexpr difference_type      operator  -  ( const array_iterator& left, const array_iterator& right ) { [[assume(left.step == right.step)]]; return (left.iter - right.iter) / left.step; }
            friend constexpr array_iterator&      operator ++  (       array_iterator& left                              ) { left.iter += left.step;         return left; }
            friend constexpr array_iterator       operator ++  (       array_iterator& left,       int                   ) { let it = left; ++left;          return it;   }
            friend constexpr array_iterator&      operator --  (       array_iterator& left                              ) { left.iter -= left.step;         return left; }
            friend constexpr array_iterator       operator --  (       array_iterator& left,       int                   ) { let it = left; --left;          return it;   }
            friend constexpr array_iterator&      operator +=  (       array_iterator& left,       difference_type right ) { left.iter += left.step * right; return left; }
            friend constexpr array_iterator&      operator -=  (       array_iterator& left,       difference_type right ) { left.iter -= left.step * right; return left; }
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class array_iterator<type,dim,device>
    {
        private: // Typedef
            using base = std::span<array_upper<type,dim-1,device>>::iterator;

        private: // Data
            base iter = base();

        public: // Typedef
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = array<type,dim-1,device>;
            using reference         = array<type,dim-1,device>&;
            using pointer           = array<type,dim-1,device>*;
            using difference_type   = ptrdiff_t;

        public: // Core
            constexpr array_iterator ( ) = default;
            constexpr array_iterator ( base init_iter ) extends iter ( init_iter ) { };

        public: // Operator.member
            constexpr           operator base ( )                   const { return iter; }
            constexpr reference operator *    ( )                   const { return static_cast<reference>(iter.operator*());   }
            constexpr pointer   operator ->   ( )                   const { return static_cast<pointer>  (iter.operator->());  }
            constexpr reference operator []   ( difference_type t ) const { return static_cast<reference>(iter.operator[](t)); }

        public: // Operator.global
            friend constexpr bool                 operator ==  ( const array_iterator& left, const array_iterator& right ) { return left.iter == right.iter;                                   }
            friend constexpr std::strong_ordering operator <=> ( const array_iterator& left, const array_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter); }
            friend constexpr array_iterator       operator  +  ( const array_iterator& left,       difference_type right ) { return array_iterator(left .iter + right); }
            friend constexpr array_iterator       operator  +  (       difference_type left, const array_iterator& right ) { return array_iterator(right.iter + left); }
            friend constexpr array_iterator       operator  -  ( const array_iterator& left,       difference_type right ) { return array_iterator(left .iter - right); }
            friend constexpr difference_type      operator  -  ( const array_iterator& left, const array_iterator& right ) { return left.iter - right.iter; }
            friend constexpr array_iterator&      operator ++  (       array_iterator& left                              ) { ++left.iter;           return left; }
            friend constexpr array_iterator       operator ++  (       array_iterator& left,       int                   ) { let it = left; ++left; return it;   }
            friend constexpr array_iterator&      operator --  (       array_iterator& left                              ) { --left.iter;;          return left; }
            friend constexpr array_iterator       operator --  (       array_iterator& left,       int                   ) { let it = left; --left; return it;   }
            friend constexpr array_iterator&      operator +=  (       array_iterator& left,       difference_type right ) { left.iter += right;    return left; }
            friend constexpr array_iterator&      operator -=  (       array_iterator& left,       difference_type right ) { left.iter -= right;    return left; }
    };

    template < class type, int dim, class device >
    class array_const_iterator;

    template < class type, class device >
    class array_const_iterator<type,1,device>
    {
        private: // Base
            using base = device::template const_pointer<type>;

        private: // Data
            base iter = base();
            int  step = 1;

        public: // Typedef
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = device::template value_type     <type>;
            using reference         = device::template const_reference<type>;
            using pointer           = device::template const_pointer  <type>;
            using difference_type   = minus_result<pointer,pointer>;

        public: // Core
            constexpr array_const_iterator ( ) = default;
            constexpr array_const_iterator ( base init_iter )                extends iter ( init_iter )                     { }
            constexpr array_const_iterator ( base init_iter, int init_step ) extends iter ( init_iter ), step ( init_step ) { } 

        public: // Operator.member
            constexpr           operator base ( )                   const { return  iter;    }
            constexpr reference operator *    ( )                   const { return *iter;    }
            constexpr pointer   operator ->   ( )                   const { return  iter;    }
            constexpr reference operator []   ( difference_type t ) const { return  iter[t]; }

        public: // Operator.global
            friend constexpr bool                  operator ==  ( const array_const_iterator& left, const array_const_iterator& right ) { return left.iter == right.iter;                                           }                  
            friend constexpr std::strong_ordering  operator <=> ( const array_const_iterator& left, const array_const_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter);         }
            friend constexpr array_const_iterator  operator  +  ( const array_const_iterator& left,       difference_type       right ) { return array_const_iterator(left .iter + left .step * right, left .step); }
            friend constexpr array_const_iterator  operator  +  (       difference_type       left, const array_const_iterator& right ) { return array_const_iterator(right.iter + right.step * left,  right.step); }
            friend constexpr array_const_iterator  operator  -  ( const array_const_iterator& left,       difference_type       right ) { return array_const_iterator(left .iter - left .step * right, left .step); }
            friend constexpr difference_type       operator  -  ( const array_const_iterator& left, const array_const_iterator& right ) { [[assume(left.step == right.step)]]; return (left.iter - right.iter) / left.step; }
            friend constexpr array_const_iterator& operator ++  (       array_const_iterator& left                                    ) { left.iter += left.step;         return left; }
            friend constexpr array_const_iterator  operator ++  (       array_const_iterator& left,       int                         ) { let it = left; ++left;          return it;   }
            friend constexpr array_const_iterator& operator --  (       array_const_iterator& left                                    ) { left.iter -= left.step;         return left; }
            friend constexpr array_const_iterator  operator --  (       array_const_iterator& left,       int                         ) { let it = left; --left;          return it;   }
            friend constexpr array_const_iterator& operator +=  (       array_const_iterator& left,       difference_type       right ) { left.iter += left.step * right; return left; }
            friend constexpr array_const_iterator& operator -=  (       array_const_iterator& left,       difference_type       right ) { left.iter -= left.step * right; return left; }
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class array_const_iterator<type,dim,device>
    {
        private: // Typedef
            using base = std::span<array_upper<type,dim-1,device>>::iterator; // TODO: use span::const_iterator

        private: // Data
            base iter = base();

        public: // Typedef
            using iterator_category = std::random_access_iterator_tag;
            using value_type        = array<type,dim-1,device>;
            using reference         = const array<type,dim-1,device>&;
            using pointer           = const array<type,dim-1,device>*;
            using difference_type   = ptrdiff_t;

        public: // Core
            constexpr array_const_iterator ( ) = default;
            constexpr array_const_iterator ( base init_iter ) extends iter ( init_iter ) { };

        public: // Operator.member
            constexpr           operator base ( )                   const { return iter; }
            constexpr reference operator *    ( )                   const { return static_cast<reference>(iter.operator*());   }
            constexpr pointer   operator ->   ( )                   const { return static_cast<pointer>  (iter.operator->());  }
            constexpr reference operator []   ( difference_type t ) const { return static_cast<reference>(iter.operator[](t)); }

        public: // Operator.global
            friend constexpr bool                  operator ==  ( const array_const_iterator& left, const array_const_iterator& right ) { return left.iter == right.iter;                                   }
            friend constexpr std::strong_ordering  operator <=> ( const array_const_iterator& left, const array_const_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter); }
            friend constexpr array_const_iterator  operator  +  ( const array_const_iterator& left,       difference_type       right ) { return array_const_iterator(left .iter + right); }
            friend constexpr array_const_iterator  operator  +  (       difference_type       left, const array_const_iterator& right ) { return array_const_iterator(right.iter + left);  }
            friend constexpr array_const_iterator  operator  -  ( const array_const_iterator& left,       difference_type       right ) { return array_const_iterator(left .iter - right); }
            friend constexpr difference_type       operator  -  ( const array_const_iterator& left, const array_const_iterator& right ) { return left.iter - right.iter; }
            friend constexpr array_const_iterator& operator ++  (       array_const_iterator& left                                    ) { ++left.iter;           return left; }
            friend constexpr array_const_iterator  operator ++  (       array_const_iterator& left,       int                         ) { let it = left; ++left; return it;   }
            friend constexpr array_const_iterator& operator --  (       array_const_iterator& left                                    ) { --left.iter;;          return left; }
            friend constexpr array_const_iterator  operator --  (       array_const_iterator& left,       int                         ) { let it = left; --left; return it;   }
            friend constexpr array_const_iterator& operator +=  (       array_const_iterator& left,       difference_type       right ) { left.iter += right;    return left; }
            friend constexpr array_const_iterator& operator -=  (       array_const_iterator& left,       difference_type       right ) { left.iter -= right;    return left; }
    };
} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */