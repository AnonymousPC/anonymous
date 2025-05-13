template < class type, int dim, class device >
class detail::array_line_iterator
    extends public std::span<detail::array_upper<type,dim-1,device>>::iterator
{
    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = array<type,dim-1,device>;
        using reference         = array<type,dim-1,device>&;
        using pointer           = array<type,dim-1,device>*;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr array_line_iterator ( ) = default;
        constexpr array_line_iterator ( std::span<detail::array_upper<type,dim-1,device>>::iterator );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const;
};

template < class type, int dim, class device > constexpr bool                                          operator ==  ( detail::array_line_iterator<type,dim,device>,  detail::array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr std::strong_ordering                          operator <=> ( detail::array_line_iterator<type,dim,device>,  detail::array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>  operator +   ( detail::array_line_iterator<type,dim,device>,  std::ptrdiff_t                               );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>  operator +   ( std::ptrdiff_t,                                detail::array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>  operator -   ( detail::array_line_iterator<type,dim,device>,  std::ptrdiff_t                               );
template < class type, int dim, class device > constexpr std::ptrdiff_t                                operator -   ( detail::array_line_iterator<type,dim,device>,  detail::array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>& operator +=  ( detail::array_line_iterator<type,dim,device>&, std::ptrdiff_t                               );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>& operator -=  ( detail::array_line_iterator<type,dim,device>&, std::ptrdiff_t                               );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>& operator ++  ( detail::array_line_iterator<type,dim,device>&                                               );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>  operator ++  ( detail::array_line_iterator<type,dim,device>,  int                                          );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>& operator --  ( detail::array_line_iterator<type,dim,device>&                                               );
template < class type, int dim, class device > constexpr detail::array_line_iterator<type,dim,device>  operator --  ( detail::array_line_iterator<type,dim,device>,  int                                          );

template < class type, int dim, class device >
class detail::const_array_line_iterator
    extends public std::span<detail::array_upper<type,dim-1,device>>::iterator // TODO: use std::span::const_iterator once compiler supports it.
{
    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        =       array<type,dim-1,device>;
        using reference         = const array<type,dim-1,device>&;
        using pointer           = const array<type,dim-1,device>*;
        using difference_type   = std::ptrdiff_t;

    public: // Core
        constexpr const_array_line_iterator ( ) = default;
        constexpr const_array_line_iterator ( std::span<detail::array_upper<type,dim-1,device>>::iterator );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const;

    public: // Access
        constexpr std::span<detail::array_upper<type,dim-1,device>>::iterator base ( ) const;
};

template < class type, int dim, class device > constexpr bool                                                operator ==  ( detail::const_array_line_iterator<type,dim,device>,  detail::const_array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr std::strong_ordering                                operator <=> ( detail::const_array_line_iterator<type,dim,device>,  detail::const_array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>  operator +   ( detail::const_array_line_iterator<type,dim,device>,  std::ptrdiff_t                                     );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>  operator +   ( std::ptrdiff_t,                                      detail::const_array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>  operator -   ( detail::const_array_line_iterator<type,dim,device>,  std::ptrdiff_t                                     );
template < class type, int dim, class device > constexpr std::ptrdiff_t                                      operator -   ( detail::const_array_line_iterator<type,dim,device>,  detail::const_array_line_iterator<type,dim,device> );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>& operator +=  ( detail::const_array_line_iterator<type,dim,device>&, std::ptrdiff_t                                     );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>& operator -=  ( detail::const_array_line_iterator<type,dim,device>&, std::ptrdiff_t                                     );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>& operator ++  ( detail::const_array_line_iterator<type,dim,device>&                                                     );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>  operator ++  ( detail::const_array_line_iterator<type,dim,device>,  int                                                );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>& operator --  ( detail::const_array_line_iterator<type,dim,device>&                                                     );
template < class type, int dim, class device > constexpr detail::const_array_line_iterator<type,dim,device>  operator --  ( detail::const_array_line_iterator<type,dim,device>,  int                                                );

