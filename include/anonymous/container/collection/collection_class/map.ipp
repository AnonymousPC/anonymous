#pragma once

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( std::initializer_list<pair<const type1,type2>> init )
    requires copyable<type1> and copyable<type2>
{
    for ( const auto& [k, v] in init )
        self[k] = v;
}

template < class type1, class type2, class compare, class device >
constexpr int map<type1,type2,compare,device>::size ( ) const
{
    return base::size();
}

template < class type1, class type2, class compare, class device >
constexpr bool map<type1,type2,compare,device>::empty ( ) const
{
    return base::empty();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::iterator map<type1,type2,compare,device>::begin ( )
{
    return base::begin();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::const_iterator map<type1,type2,compare,device>::begin ( ) const
{
    return base::begin();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::iterator map<type1,type2,compare,device>::end ( )
{
    return base::end();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::const_iterator map<type1,type2,compare,device>::end ( ) const
{
    return base::end();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::value_reference map<type1,type2,compare,device>::operator[] ( const type1& k )
{
    return base::operator[](k);
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::value_reference map<type1,type2,compare,device>::operator[] ( type1&& k )
{
    return base::operator[](std::move(k));
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::const_value_reference map<type1,type2,compare,device>::operator[] ( const type1& k ) const
{
    auto it = base::find(k);
    if ( it != base::end() )
        return get<1>(*it);
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class compare, class device > 
constexpr bool map<type1,type2,compare,device>::contains ( const type1& k ) const
{
    if constexpr ( requires { base::contains(k); } )
        return base::contains(k);
    else
        return base::find(k) != base::end();
}

template < class type1, class type2, class compare, class device > 
constexpr const auto& map<type1,type2,compare,device>::keys ( ) const
{
    return static_cast<const detail::map_keys<map,type1,device>&>(self);
}

template < class type1, class type2, class compare, class device > 
constexpr auto& map<type1,type2,compare,device>::values ( )
{
    return static_cast<detail::map_values<map,type2,device>&>(self);
}

template < class type1, class type2, class compare, class device > 
constexpr const auto& map<type1,type2,compare,device>::values ( ) const
{
    return static_cast<const detail::map_values<map,type2,device>&>(self);
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::pop ( const type1& k )
{
    auto pop_count = base::erase(k);
    if ( pop_count >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::update ( const map& m )
{
    for ( const auto& [k, v] in m )
        self[k] = v;

    return self;
}

template < class type1, class type2, class compare, class device >
constexpr auto map<type1,type2,compare,device>::emplace ( auto&&... args )
    requires constructible_from<typename base::value_type,decltype(args)...>
{
    return base::emplace(std::forward<decltype(args)>(args)...);
}

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::iterator
    extends public device::template map<type1,type2,compare>::iterator
{
    private: // Typedef
        using base = device::template map<type1,type2,compare>::iterator;

    public: // Typedef
        using value_type = device::template value_type<pair<const type1,type2>>;
        using reference  = device::template reference <pair<const type1,type2>>;
        using pointer    = device::template pointer   <pair<const type1,type2>>;

    public: // Override
        constexpr iterator ( ) = default;

        constexpr iterator ( base init_b )
            extends base ( std::move(init_b) )
        {

        }
        
        constexpr reference operator * ( ) const
        {
            return static_cast<reference>(base::operator*());
        }

        constexpr pointer operator -> ( ) const
        {
            return static_cast<pointer>(base::operator->());
        }

        constexpr reference operator [] ( int p ) const
            requires requires ( int i ) { base::operator[](i); }
        {
            return static_cast<reference>(base::operator[](p));
        }
        
        constexpr friend iterator operator + ( const iterator& left, int right )
            requires requires ( base b, int i ) { b + i; }
        {
            return static_cast<const base&>(left) + right;
        }

        constexpr friend iterator operator + ( int left, const iterator& right )
            requires requires ( int i, base b ) { i + b; }
        {
            return left + static_cast<const base&>(right);
        }
    
        constexpr friend iterator operator - ( const iterator& left, int right )
            requires requires ( base b, int i ) { b - i; }
        {
            return static_cast<const base&>(left) - right;
        }

        constexpr friend iterator& operator ++ ( iterator& left )
            requires requires ( base b ) { ++b; }
        {
            ++static_cast<base&>(left);
            return left;
        }

        constexpr friend iterator operator ++ ( iterator& left, int )
            requires requires ( base b ) { b++; }
        {
            auto it = left;
            ++left;
            return it;
        }

        constexpr friend iterator& operator -- ( iterator& left )
            requires requires ( base b ) { --b; }
        {
            --static_cast<base&>(left);
            return left;
        }

        constexpr friend iterator operator -- ( iterator& left, int )
            requires requires ( base b ) { b--; }
        {
            auto it = left;
            --left;
            return it;
        }
};

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::const_iterator
    extends public device::template map<type1,type2,compare>::const_iterator
{
    private: // Typedef
        using base = device::template map<type1,type2,compare>::const_iterator;

    public: // Typedef
        using value_type = device::template value_type     <pair<const type1,type2>>;
        using reference  = device::template const_reference<pair<const type1,type2>>;
        using pointer    = device::template const_pointer  <pair<const type1,type2>>;

    public: // Override
        constexpr const_iterator ( ) = default;

        constexpr const_iterator ( base init_b )
            extends base ( std::move(init_b) )
        {

        }
        
        constexpr reference operator * ( ) const
        {
            return static_cast<reference>(base::operator*());
        }

        constexpr pointer operator -> ( ) const
        {
            return static_cast<pointer>(base::operator->());
        }

        constexpr reference operator [] ( int p ) const
            requires requires ( int i ) { base::operator[](i); }
        {
            return static_cast<reference>(base::operator[](p));
        }
        
        constexpr friend const_iterator operator + ( const const_iterator& left, int right )
            requires requires ( base b, int i ) { b + i; }
        {
            return static_cast<const base&>(left) + right;
        }

        constexpr friend const_iterator operator + ( int left, const const_iterator& right )
            requires requires ( int i, base b ) { i + b; }
        {
            return left + static_cast<const base&>(right);
        }
    
        constexpr friend const_iterator operator - ( const const_iterator& left, int right )
            requires requires ( base b, int i ) { b - i; }
        {
            return static_cast<const base&>(left) - right;
        }

        constexpr friend const_iterator& operator ++ ( const_iterator& left )
            requires requires ( base b ) { ++b; }
        {
            ++static_cast<base&>(left);
            return left;
        }

        constexpr friend const_iterator operator ++ ( const_iterator& left, int )
            requires requires ( base b ) { b++; }
        {
            auto it = left;
            ++left;
            return it;
        }

        constexpr friend const_iterator& operator -- ( const_iterator& left )
            requires requires ( base b ) { --b; }
        {
            --static_cast<base&>(left);
            return left;
        }

        constexpr friend const_iterator operator -- ( const_iterator& left, int )
            requires requires ( base b ) { b--; }
        {
            auto it = left;
            --left;
            return it;
        }
};

