#pragma once

namespace detail
{
    template < class type, class device >
    class array_iterator
    {
        private: // Typedef
            using base = device::template pointer<type>;

        private: // Data
            base iter = base();
            int  step = 1;

        public: // Typedef
            using iterator_concept = std::random_access_iterator_tag;
            using value_type       = device::template value_type<type>;
            using reference        = device::template reference <type>;
            using pointer          = device::template pointer   <type>;
            using difference_type  = minus_result<pointer,pointer>;

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

    template < class type, class device >
    class array_const_iterator
    {
        private: // Base
            using base = device::template const_pointer<type>;

        private: // Data
            base iter = base();
            int  step = 1;

        public: // Typedef
            using iterator_concept = std::random_access_iterator_tag;
            using value_type       = device::template value_type     <type>;
            using reference        = device::template const_reference<type>;
            using pointer          = device::template const_pointer  <type>;
            using difference_type  = minus_result<pointer,pointer>;

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
            friend constexpr difference_type       operator  -  ( const array_const_iterator& left, const array_const_iterator& right ) { [[assume(left.step == right.step)]]; return (left.iter - right.iter) / left.step;  }
            friend constexpr array_const_iterator& operator ++  (       array_const_iterator& left                                    ) { left.iter += left.step;         return left; }
            friend constexpr array_const_iterator  operator ++  (       array_const_iterator& left,       int                         ) { let it = left; ++left;          return it;   }
            friend constexpr array_const_iterator& operator --  (       array_const_iterator& left                                    ) { left.iter -= left.step;         return left; }
            friend constexpr array_const_iterator  operator --  (       array_const_iterator& left,       int                         ) { let it = left; --left;          return it;   }
            friend constexpr array_const_iterator& operator +=  (       array_const_iterator& left,       difference_type       right ) { left.iter += left.step * right; return left; }
            friend constexpr array_const_iterator& operator -=  (       array_const_iterator& left,       difference_type       right ) { left.iter -= left.step * right; return left; }
    };
} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */