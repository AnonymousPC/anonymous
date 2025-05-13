

template < class container, class type1, class device >
class detail::map_keys<container,type1,device>::const_iterator
    extends public container::const_iterator
{
    public: // Typedef
        using iterator_category = std::iterator_traits<typename container::const_iterator>::iterator_category;
        using value_type        = device::template value_type     <type1>;
        using reference         = device::template const_reference<type1>;
        using pointer           = device::template const_pointer  <type1>;
        using difference_type   = std::iterator_traits<typename container::const_iterator>::difference_type;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( container::const_iterator );

    public: // Operator
        constexpr reference operator *  ( )                 const;
        constexpr pointer   operator -> ( )                 const;
        constexpr reference operator [] ( difference_type ) const requires random_access_iterator<typename container::const_iterator>;
};