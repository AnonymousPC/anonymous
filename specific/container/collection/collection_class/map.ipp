#pragma once

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( )
    extends base   ( ),
            k_view ( self ),
            v_view ( self )
{

}

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( const map& init )
    requires copyable<type1> and copyable<type2>
    extends base   ( static_cast<const base&>(init) ),
            k_view ( self ), 
            v_view ( self )
{
    
}

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( map&& init )
    extends base   ( static_cast<base&&>(init) ),
            k_view ( self ),
            v_view ( self )
{
    
}

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::operator = ( const map& right )
    requires copyable<type1> and copyable<type2>
{
    base::operator=(static_cast<const base&>(right));
    return self;
}

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::operator = ( map&& right )
{
    base::operator=(static_cast<base&&>(right));
    return self;
}

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( const std::initializer_list<pair<const type1,type2>>& init )
    requires copyable<type1> and copyable<type2>
    extends base   ( /*initialized later*/ ),
            k_view ( self ),
            v_view ( self )
{
    for ( const auto& [k, v] in init )
        self[k] = v;
}

template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( std::from_range_t, std::ranges::input_range auto&& r )
    requires requires { std::declval<map>()[get<0>(*std::ranges::begin(r))] = get<1>(*std::ranges::begin(r)); }
    extends map ( )
{
    for ( auto&& [k, v] in r )
        self[std::forward<decltype(k)>(k)] = std::forward<decltype(v)>(v);
}

template < class type1, class type2, class compare, class device >
template < class type3, class type4, class compare2 >
constexpr map<type1,type2,compare,device>::map ( const map<type3,type4,compare2,device>& cvt )
    requires convertible_to<type3,type1> and convertible_to<type4,type2> but ( not same_as<type1,type3> or not same_as<type2,type4> )
    extends map ( )
{
    for ( auto&& [k, v] in cvt )
        self[type1(k)] = type2(v);
}

template < class type1, class type2, class compare, class device >
template < class type3, class type4, class compare2 >
constexpr map<type1,type2,compare,device>::map ( const map<type3,type4,compare2,device>& cvt )
    requires constructible_from<type1,type3> and constructible_from<type2,type4> but ( not convertible_to<type3,type1> or not convertible_to<type4,type2> )
    extends map ( )
{
    for ( auto&& [k, v] in cvt )
        self[type1(k)] = type2(v);
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
    let it = base::find(k);
    if ( it != base::end() )
        return get<1>(*it);
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class compare, class device > 
constexpr const auto map<type1,type2,compare,device>::keys ( ) const
{
    return k_view;
}

template < class type1, class type2, class compare, class device > 
constexpr auto map<type1,type2,compare,device>::values ( )
{
    return v_view;
}

template < class type1, class type2, class compare, class device > 
constexpr const auto map<type1,type2,compare,device>::values ( ) const
{
    return v_view;
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::clear ( )
{
    base::clear();
    return self;
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
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::pop ( const type1& k )
{
    let pop_count = base::erase(k);
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
            let it = left;
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
            let it = left;
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
            let it = left;
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
            let it = left;
            --left;
            return it;
        }
};

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::keys_view
    extends public collection_algo<map<type1,type2,compare,device>::keys_view,const type1,compare,device>
{
    private: // Data
        map<type1,type2,compare,device>& h;

    private: // Access
        constexpr map<type1,type2,compare,device>& host ( )       
        {
            return h;
        }

        constexpr const map<type1,type2,compare,device>& host ( ) const
        {
            return h; 
        }

    public: // Typedef
        using  value_type            = device::template value_type     <type1>;
        using  reference             = device::template reference      <type1>;
        using  const_reference       = device::template const_reference<type1>;
        using  pointer               = device::template pointer        <type1>;
        using  const_pointer         = device::template const_pointer  <type1>;
     // class  iterator; 
        class  const_iterator;      
        using  compare_type          = compare;
        using  device_type           = device;
        struct set_tag { };

    public: // Core
        constexpr keys_view ( map<type1,type2,compare,device>& init_h )
            extends h ( init_h )
        {

        }

    public: // Member
        constexpr const_iterator begin ( ) const
        {
            return host().begin();
        }

        constexpr const_iterator end ( ) const
        {
            return host().end();
        }

        constexpr bool contains ( const type1& k )
        {
            return host().contains(k);
        }
};

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::keys_view::const_iterator
    extends public map<type1,type2,compare,device>::const_iterator
{
    private: // Typedef
        using base = map<type1,type2,compare,device>::const_iterator;

    public: // Typedef
        using value_type = device::template value_type     <type1>;
        using reference  = device::template const_reference<type1>;
        using pointer    = device::template const_pointer  <type1>;

    public: // Override
        constexpr const_iterator ( base init_b )
            extends base ( std::move(init_b) )
        {

        }

        constexpr reference operator * ( ) const
        {
            return base::operator*().key();
        }

        constexpr pointer operator -> ( ) const
        {
            return &(operator*());
        }

        constexpr reference operator [] ( int p ) const
            requires requires ( int i ) { base::operator[](i); }
        {
            return base::operator[](p).key();
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
            let it = left;
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
            let it = left;
            --left;
            return it;
        }      
};

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::values_view
    extends public collection_algo<map<type1,type2,compare,device>::values_view,type2,compare,device>
{
    private: // Data
        map<type1,type2,compare,device>& h;

    private: // Access
        constexpr map<type1,type2,compare,device>& host ( )       
        {
            return h;
        }

        constexpr const map<type1,type2,compare,device>& host ( ) const
        {
            return h; 
        }

    public: // Typedef
        using  value_type            = device::template value_type     <type1>;
        using  reference             = device::template reference      <type1>;
        using  const_reference       = device::template const_reference<type1>;
        using  pointer               = device::template pointer        <type1>;
        using  const_pointer         = device::template const_pointer  <type1>;
        class  iterator; 
        class  const_iterator;      
        using  compare_type          = compare;
        using  device_type           = device;

    public: // Core
        constexpr values_view ( map<type1,type2,compare,device>& init_h )
            extends h ( init_h )
        {

        }

    public: // Member
        constexpr iterator begin ( )
        {
            return host().begin();
        }

        constexpr const_iterator begin ( ) const
        {
            return host().begin();
        }

        constexpr iterator end ( )
        {
            return host().end();
        }

        constexpr const_iterator end ( ) const
        {
            return host().end();
        }
};

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::values_view::iterator
    extends public map<type1,type2,compare,device>::iterator
{
    private: // Typedef
        using base = map<type1,type2,compare,device>::iterator;

    public: // Typedef
        using value_type = device::template value_type<type2>;
        using reference  = device::template reference <type2>;
        using pointer    = device::template pointer   <type2>;

    public: // Override
        constexpr iterator ( base init_b )
            extends base ( std::move(init_b) )
        {

        }

        constexpr reference operator * ( ) const
        {
            return base::operator*().value();
        }

        constexpr pointer operator -> ( ) const
        {
            return &(operator*());
        }

        constexpr reference operator [] ( int p ) const
            requires requires ( int i ) { base::operator[](i); }
        {
            return base::operator[](p).value();
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
            let it = left;
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
            let it = left;
            --left;
            return it;
        }      
};

template < class type1, class type2, class compare, class device >
class map<type1,type2,compare,device>::values_view::const_iterator
    extends public map<type1,type2,compare,device>::const_iterator
{
    private: // Typedef
        using base = map<type1,type2,compare,device>::const_iterator;

    public: // Typedef
        using value_type = device::template value_type     <type2>;
        using reference  = device::template const_reference<type2>;
        using pointer    = device::template const_pointer  <type2>;

    public: // Override
        constexpr const_iterator ( base init_b )
            extends base ( std::move(init_b) )
        {

        }

        constexpr reference operator * ( ) const
        {
            return base::operator*().value();
        }

        constexpr pointer operator -> ( ) const
        {
            return &(operator*());
        }

        constexpr reference operator [] ( int p ) const
            requires requires ( int i ) { base::operator[](i); }
        {
            return base::operator[](p).value();
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
            let it = left;
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
            let it = left;
            --left;
            return it;
        }      
};