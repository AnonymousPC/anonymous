template < class alloc >
constexpr cpu::vector<bool,alloc>::vector ( size_t init_size, bool init_value )
    extends std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>> ( init_size, init_value )
{

}

template < class alloc >
constexpr cpu::vector<bool,alloc>::vector ( std::initializer_list<bool> init_value )
    extends std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>> ( reinterpret_cast<const detail::enum_bool*>(init_value.begin()), reinterpret_cast<const detail::enum_bool*>(init_value.end()) )
{

}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::begin ( )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_iterator cpu::vector<bool,alloc>::begin ( ) const
{
    return reinterpret_cast<const_iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::end ( )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::data() + std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::size());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_iterator cpu::vector<bool,alloc>::end ( ) const
{
    return reinterpret_cast<const_iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::data() + std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::size());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::data ( )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_iterator cpu::vector<bool,alloc>::data ( ) const
{
    return reinterpret_cast<const_iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::front ( )
{
    return reinterpret_cast<reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::front());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::front ( ) const
{
    return reinterpret_cast<const_reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::front());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::back ( )
{
    return reinterpret_cast<reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::back());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::back ( ) const
{
    return reinterpret_cast<const_reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::back());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::at ( size_t pos )
{
    return reinterpret_cast<reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::at(pos));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::at ( size_t pos ) const
{
    return reinterpret_cast<const_reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::at(pos));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::operator [] ( size_t pos )
{
    return reinterpret_cast<reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::operator[](pos));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::operator [] ( size_t pos ) const
{
    return reinterpret_cast<const_reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::operator[](pos));
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::resize ( size_t new_size )
{
    std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::resize(new_size);
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::resize ( size_t new_size, bool new_value )
{
    std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::resize(new_size, static_cast<detail::enum_bool>(new_value));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::insert ( const_iterator it, bool new_value )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::insert(reinterpret_cast<std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::const_iterator>(it), static_cast<detail::enum_bool>(new_value)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::insert ( const_iterator it, size_t new_size, bool new_value )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::insert(reinterpret_cast<std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::const_iterator>(it), new_size, static_cast<detail::enum_bool>(new_value)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::erase ( const_iterator it )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::erase(reinterpret_cast<std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::const_iterator>(it)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::erase ( const_iterator it1, const_iterator it2 )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::erase(reinterpret_cast<std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::const_iterator>(it1), reinterpret_cast<std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::const_iterator>(it2)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::emplace ( const_iterator it, auto&&... new_value )
{
    return reinterpret_cast<iterator>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::insert(reinterpret_cast<std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::const_iterator>(it), static_cast<detail::enum_bool>(bool(std::forward<decltype(new_value)>(new_value)...))));
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::push_back ( bool new_value )
{
    std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::push_back(static_cast<detail::enum_bool>(new_value));
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::pop_back ( )
{
    std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::pop_back();
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::emplace_back ( auto&&... new_value )
{
    return reinterpret_cast<reference>(std::vector<detail::enum_bool,typename std::allocator_traits<alloc>::template rebind_allocator<detail::enum_bool>>::reference(static_cast<detail::enum_bool>(bool(std::forward<decltype(new_value)>(new_value)...))));
}