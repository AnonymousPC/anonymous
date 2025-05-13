#include "detail/enum_bool.cpp"

template < class type, class alloc >
class cpu::vector
    extends public std::vector<type,alloc>
{

};

template < class alloc >
class cpu::vector<bool,alloc>
    extends public std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_alloc<detail::enum_bool>>
{
    public: // Typedef
        using value_type      = bool;
        using reference       = bool&;
        using const_reference = const bool&;
        using pointer         = bool*;
        using const_pointer   = const bool*;
        using iterator        = bool*;
        using const_iterator  = const bool*;

    public: // Core
        using std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_alloc<detail::enum_bool>>::vector;
        constexpr vector ( std::size_t, bool );
        constexpr vector ( std::initializer_list<bool> );

    public: // Member 
        constexpr iterator        begin       ( );
        constexpr const_iterator  begin       ( )             const;
        constexpr iterator        end         ( );
        constexpr const_iterator  end         ( )             const;
        constexpr pointer         data        ( );
        constexpr const_pointer   data        ( )             const;
        constexpr reference       front       ( );
        constexpr const_reference front       ( )             const;
        constexpr reference       back        ( );
        constexpr const_reference back        ( )             const;
        constexpr reference       at          ( std::size_t );
        constexpr const_reference at          ( std::size_t ) const;
        constexpr reference       operator [] ( std::size_t );
        constexpr const_reference operator [] ( std::size_t ) const;

        constexpr void            resize       ( std::size_t );
        constexpr void            resize       ( std::size_t, bool );
        constexpr iterator        insert       ( const_iterator, bool );
        constexpr iterator        insert       ( const_iterator, std::size_t, bool );
        constexpr iterator        erase        ( const_iterator );
        constexpr iterator        erase        ( const_iterator, const_iterator );
        constexpr iterator        emplace      ( const_iterator, auto&&... );
        constexpr void            push_back    ( bool );
        constexpr void            pop_back     ( );
        constexpr reference       emplace_back ( auto&&... );
};

#include "vector.cpp"