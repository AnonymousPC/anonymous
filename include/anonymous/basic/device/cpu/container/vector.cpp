template < class alloc >
constexpr cpu::vector<bool,alloc>::vector ( std::size_t init_size, bool init_value )
    extends base ( init_size, init_value )
{

}

template < class alloc >
constexpr cpu::vector<bool,alloc>::vector ( std::initializer_list<bool> init_value )
    extends base ( reinterpret_cast<const detail::enum_bool*>(init_value.begin()), reinterpret_cast<const detail::enum_bool*>(init_value.end()) )
{

}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::begin ( )
{
    return reinterpret_cast<iterator>(base::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_iterator cpu::vector<bool,alloc>::begin ( ) const
{
    return reinterpret_cast<const_iterator>(base::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::end ( )
{
    return reinterpret_cast<iterator>(base::data() + base::size());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_iterator cpu::vector<bool,alloc>::end ( ) const
{
    return reinterpret_cast<const_iterator>(base::data() + base::size());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::data ( )
{
    return reinterpret_cast<iterator>(base::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_iterator cpu::vector<bool,alloc>::data ( ) const
{
    return reinterpret_cast<const_iterator>(base::data());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::front ( )
{
    return reinterpret_cast<reference>(base::front());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::front ( ) const
{
    return reinterpret_cast<const_reference>(base::front());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::back ( )
{
    return reinterpret_cast<reference>(base::back());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::back ( ) const
{
    return reinterpret_cast<const_reference>(base::back());
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::at ( std::size_t pos )
{
    return reinterpret_cast<reference>(base::at(pos));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::at ( std::size_t pos ) const
{
    return reinterpret_cast<const_reference>(base::at(pos));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::operator [] ( std::size_t pos )
{
    return reinterpret_cast<reference>(base::operator[](pos));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::const_reference cpu::vector<bool,alloc>::operator [] ( std::size_t pos ) const
{
    return reinterpret_cast<const_reference>(base::operator[](pos));
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::resize ( std::size_t new_size )
{
    base::resize(new_size);
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::resize ( std::size_t new_size, bool new_value )
{
    base::resize(new_size, static_cast<detail::enum_bool>(new_value));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::insert ( const_iterator it, bool new_value )
{
    return reinterpret_cast<iterator>(base::insert(reinterpret_cast<base::const_iterator>(it), static_cast<detail::enum_bool>(new_value)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::insert ( const_iterator it, std::size_t new_size, bool new_value )
{
    return reinterpret_cast<iterator>(base::insert(reinterpret_cast<base::const_iterator>(it), new_size, static_cast<detail::enum_bool>(new_value)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::erase ( const_iterator it )
{
    return reinterpret_cast<iterator>(base::erase(reinterpret_cast<base::const_iterator>(it)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::erase ( const_iterator it1, const_iterator it2 )
{
    return reinterpret_cast<iterator>(base::erase(reinterpret_cast<base::const_iterator>(it1), reinterpret_cast<base::const_iterator>(it2)));
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::iterator cpu::vector<bool,alloc>::emplace ( const_iterator it, auto&&... new_value )
{
    return reinterpret_cast<iterator>(base::insert(reinterpret_cast<base::const_iterator>(it), static_cast<detail::enum_bool>(bool(std::forward<decltype(new_value)>(new_value)...))));
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::push_back ( bool new_value )
{
    base::push_back(static_cast<detail::enum_bool>(new_value));
}

template < class alloc >
constexpr void cpu::vector<bool,alloc>::pop_back ( )
{
    base::pop_back();
}

template < class alloc >
constexpr cpu::vector<bool,alloc>::reference cpu::vector<bool,alloc>::emplace_back ( auto&&... new_value )
{
    return reinterpret_cast<reference>(base::reference(static_cast<detail::enum_bool>(bool(std::forward<decltype(new_value)>(new_value)...))));
}