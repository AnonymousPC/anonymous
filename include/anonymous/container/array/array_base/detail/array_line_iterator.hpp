template < class type, int dim, class device >
class detail::array_line_iterator
{
    private: // Precondition
        static_assert ( dim >= 2 );

    private: // Typedef
        using base = std::span<detail::array_upper<type,dim-1,device>>::iterator;

    private: // Data
        base iter = base();

    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = array<type,dim-1,device>;
        using reference         = array<type,dim-1,device>&;
        using pointer           = array<type,dim-1,device>*;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr array_line_iterator ( ) = default;
        constexpr array_line_iterator ( base init_iter ) extends iter ( init_iter ) { };

    public: // Operator.member
        constexpr           operator base ( )                   const { return iter; }
        constexpr reference operator *    ( )                   const { return static_cast<reference>(iter.operator*());   }
        constexpr pointer   operator ->   ( )                   const { return static_cast<pointer>  (iter.operator->());  }
        constexpr reference operator []   ( difference_type t ) const { return static_cast<reference>(iter.operator[](t)); }

    public: // Operator.global
        friend constexpr bool                 operator ==  ( const array_line_iterator& left, const array_line_iterator& right ) { return left.iter == right.iter; }
        friend constexpr std::strong_ordering operator <=> ( const array_line_iterator& left, const array_line_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter); }
        friend constexpr array_line_iterator  operator  +  ( const array_line_iterator& left,       difference_type      right ) { return array_line_iterator(left .iter + right); }
        friend constexpr array_line_iterator  operator  +  (       difference_type      left, const array_line_iterator& right ) { return array_line_iterator(right.iter + left); }
        friend constexpr array_line_iterator  operator  -  ( const array_line_iterator& left,       difference_type      right ) { return array_line_iterator(left .iter - right); }
        friend constexpr difference_type      operator  -  ( const array_line_iterator& left, const array_line_iterator& right ) { return left.iter - right.iter; }
        friend constexpr array_line_iterator& operator ++  (       array_line_iterator& left                                   ) { ++left.iter;            return left; }
        friend constexpr array_line_iterator  operator ++  (       array_line_iterator& left,       int                        ) { auto it = left; ++left; return it;   }
        friend constexpr array_line_iterator& operator --  (       array_line_iterator& left                                   ) { --left.iter;;           return left; }
        friend constexpr array_line_iterator  operator --  (       array_line_iterator& left,       int                        ) { auto it = left; --left; return it;   }
        friend constexpr array_line_iterator& operator +=  (       array_line_iterator& left,       difference_type      right ) { left.iter += right;     return left; }
        friend constexpr array_line_iterator& operator -=  (       array_line_iterator& left,       difference_type      right ) { left.iter -= right;     return left; }
};

template < class type, int dim, class device >
class detail::array_line_const_iterator
{
    private: // Precondition
        static_assert ( dim >= 2 );

    private: // Typedef
        using base = std::span<array_upper<type,dim-1,device>>::iterator; // TODO: use span::const_iterator

    private: // Data
        base iter = base();

    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = array<type,dim-1,device>;
        using reference         = const array<type,dim-1,device>&;
        using pointer           = const array<type,dim-1,device>*;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr array_line_const_iterator ( ) = default;
        constexpr array_line_const_iterator ( base init_iter ) extends iter ( init_iter ) { };

    public: // Operator.member
        constexpr           operator base ( )                   const { return iter; }
        constexpr reference operator *    ( )                   const { return static_cast<reference>(iter.operator*());   }
        constexpr pointer   operator ->   ( )                   const { return static_cast<pointer>  (iter.operator->());  }
        constexpr reference operator []   ( difference_type t ) const { return static_cast<reference>(iter.operator[](t)); }

    public: // Operator.global
        friend constexpr bool                       operator ==  ( const array_line_const_iterator& left, const array_line_const_iterator& right ) { return left.iter == right.iter; }
        friend constexpr std::strong_ordering       operator <=> ( const array_line_const_iterator& left, const array_line_const_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter); }
        friend constexpr array_line_const_iterator  operator  +  ( const array_line_const_iterator& left,       difference_type            right ) { return array_line_const_iterator(left .iter + right); }
        friend constexpr array_line_const_iterator  operator  +  (       difference_type            left, const array_line_const_iterator& right ) { return array_line_const_iterator(right.iter + left);  }
        friend constexpr array_line_const_iterator  operator  -  ( const array_line_const_iterator& left,       difference_type            right ) { return array_line_const_iterator(left .iter - right); }
        friend constexpr difference_type            operator  -  ( const array_line_const_iterator& left, const array_line_const_iterator& right ) { return left.iter - right.iter; }
        friend constexpr array_line_const_iterator& operator ++  (       array_line_const_iterator& left                                         ) { ++left.iter;            return left; }
        friend constexpr array_line_const_iterator  operator ++  (       array_line_const_iterator& left,       int                              ) { auto it = left; ++left; return it;   }
        friend constexpr array_line_const_iterator& operator --  (       array_line_const_iterator& left                                         ) { --left.iter;;           return left; }
        friend constexpr array_line_const_iterator  operator --  (       array_line_const_iterator& left,       int                              ) { auto it = left; --left; return it;   }
        friend constexpr array_line_const_iterator& operator +=  (       array_line_const_iterator& left,       difference_type            right ) { left.iter += right;     return left; }
        friend constexpr array_line_const_iterator& operator -=  (       array_line_const_iterator& left,       difference_type            right ) { left.iter -= right;     return left; }
};
