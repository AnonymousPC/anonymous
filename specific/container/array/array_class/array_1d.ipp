#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires std::copyable<type>
    extends base ( not init.is_view() ? static_cast<const base&>(init) otherwise base(init.size()) )
{
    if ( init.is_view() ) [[unlikely]]
        device::copy(init.begin(), init.end(), base::begin());
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
    extends base ( not init.is_view() ? static_cast<base&&>(init) otherwise base(init.size()) )
{
    if ( init.is_view() ) [[unlikely]]
        device::move(init.begin(), init.end(), base::begin());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires std::copyable<type>
{
    if ( not right.is_view() ) [[likely]]
        base::operator=(static_cast<const base&>(right));
    else [[unlikely]]
    {
        base::resize(right.size());
        device::copy(right.begin(), right.end(), base::begin());
    }
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    if ( not right.is_view() ) [[likely]]
        base::operator=(static_cast<base&&>(right));
    else [[unlikely]]
    {
        base::resize(right.size());
        device::move(right.begin(), right.end(), base::begin());
    }
}


template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
    extends base ( init_size )
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires std::copyable<type>
    extends base ( init_size, init_value )
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( const std::initializer_list<type>& init )
    requires std::copyable<type>
    extends base ( init )
{

}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type()> auto init_value )
    extends array ( init_size )
{
    device::generate(base::begin(), base::end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type(int)> auto init_value )
    extends array ( init_size )
{
    for ( int i in range(init_size) )
        self[i] = init_value(i);
}

template < class type, class device >
constexpr array<type,1,device>::array ( const range<type>& init )
    requires std::copyable<type>
    extends array ( init.size() )
{
    device::copy(init.begin(), init.end(), base::begin());
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r )
    requires std::convertible_to<decltype(*r.begin()),type>
{
    if constexpr ( requires { std::ranges::size(r); } )
    {
        #if debug
            if ( r.size() < 0 )
                throw value_error("initialize array with negative size {}", r.size());
        #endif

        base::resize(std::ranges::size(r));
        if constexpr ( requires { device::move(std::ranges::begin(r), std::ranges::end(r), base::begin()); } )
            device::move(std::ranges::begin(r), std::ranges::end(r), base::begin());
        else
            std::ranges::move(r, base::begin());
    }
    else
        for ( auto&& val in r )
            self.base::push_back(std::forward<decltype(val)>(val));
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r, int init_size )
    requires std::convertible_to<decltype(*r.begin()),type>
    extends array ( init_size )
{
    #if debug
        if constexpr ( requires { std::ranges::size(r); } )
            if ( std::ranges::size(r) != init_size )
                throw value_error("initialize array with ambiguous size (with range-size = {}, explicit-size = {})", std::ranges::size(r), init_size);
    #endif

    if constexpr ( requires { device::move(std::ranges::begin(r), std::ranges::end(r), base::begin()); } )
        device::move(std::ranges::begin(r), std::ranges::end(r), base::begin());
    else
        std::ranges::move(r, base::begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires std::convertible_to<type2,type> but ( not std::same_as<type,type2> )
    extends array ( cvt.size() )
{
    if ( not cvt.is_view() ) [[likely]]
        device::transform(cvt.base::begin(), cvt.base::end(), base::begin(), [] (const auto& val) { return type(val); });
    else [[unlikely]]
        device::transform(cvt.begin(), cvt.end(), base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    if ( not cvt.is_view() ) [[likely]]
        device::transform(cvt.base::begin(), cvt.base::end(), base::begin(), [] (const auto& val) { return type(val); });
    else [[unlikely]]
        device::transform(cvt.begin(), cvt.end(), base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
constexpr int array<type,1,device>::dimension ( )
{
    return 1;
}

template < class type, class device >
constexpr int array<type,1,device>::size ( ) const
{
    if ( not is_view() ) [[likely]]
        return base::size();
    else [[unlikely]]
        return 1;
        //return span::from_host().column();
}

template < class type, class device >
constexpr array<int> array<type,1,device>::shape ( ) const
{
    return {1};
}

// template < class type, class device >
// constexpr static_array<int,1> array<type,1,device>::static_shape ( ) const
// {
//     return {1};
// }

// template < class type, class device >
// constexpr inplace_array<int,1> array<type,1,device>::inplace_shape ( ) const
// {
//     return {1};
// }

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    if ( not is_view() ) [[likely]]
        return base::empty();
    else [[unlikely]]
        return span::from_host().column() == 0;
}

template < class type, class device >
constexpr array<type,1,device>::const_pointer array<type,1,device>::data ( ) const
{
    if constexpr ( requires { base::data(); } )
        if ( not is_view() ) [[likely]]
            return base::data();
        else [[unlikely]]
            throw value_error("cannot get contiguous native data from array: it does not own its data and the borrowed data might sometimes be not contiguous");
    else
        static_assert(false, "cannot get contiguous native data from array: not supported on this device");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::begin ( )
{
    if ( not is_view() ) [[likely]]
        return iterator(base::begin());
    else [[unlikely]]
        throw value_error("not coded yet");
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::begin ( ) const
{
    if ( not is_view() ) [[likely]]
        return const_iterator(base::begin());
    else [[unlikely]]
        throw value_error("not coded yet");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::end ( )
{
    if ( not is_view() ) [[likely]]
        return iterator(base::end());
    else [[unlikely]]
        throw value_error("not coded yet");
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::end ( ) const
{
    if ( not is_view() ) [[likely]]
        return const_iterator(base::end());
    else [[unlikely]]
        throw value_error("not coded yet");
}

template < class type, class device >
constexpr array<type,1,device>::reference array<type,1,device>::operator [] ( int_type auto pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( not is_view() ) [[likely]]
        return pos >= 0 ? base::operator[](pos-1) otherwise
                          base::operator[](pos+size());
    //else [[unlikely]]
    //    return span::from_host()[&self - span::from_host().to_views().data() + 1, pos];
}

template < class type, class device >
constexpr array<type,1,device>::const_reference array<type,1,device>::operator [] ( int_type auto pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( not is_view() ) [[likely]]
        return pos >= 0 ? base::operator[](pos-1) otherwise
                          base::operator[](pos+size());
    //else [[unlikely]]
    //    return span::from_host()[&self - span::from_host().to_views().data() + 1, pos];
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    if ( is_view() )
        throw value_error("cannot clear array: it does not own its data");

    base::clear();
    base::shrink_to_fit();
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( int new_size )
{
    #if debug
        if ( new_size < 0 )
            throw value_error("resize array with negative size {}", new_size);
    #endif

    base::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
{
    base::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::pop ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    base::erase(pos >= 0 ? base::begin() + pos - 1 otherwise base::begin() + pos + size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::insert ( int pos, type new_value )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    base::insert(pos >= 0 ? base::begin() + pos - 1 otherwise base::begin() + pos + size(), std::move(new_value));
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::erase ( int pos_1, int pos_2 )
{
    let p1 = pos_1 >= 0 ? pos_1 otherwise pos_1 + size();
    let p2 = pos_2 >= 0 ? pos_2 otherwise pos_2 + size();

    #if debug
        if ( ( ( p1 < 1 or p1 > size() ) or
               ( p2 < 1 or p2 > size() ) )
        and not // Except for below:
             ( ( p1 == size() + 1 or p2 == 0 ) and p1 == p2 + 1 ) )
            throw index_error("index [{},{}] is out of range with size {}", pos_1, pos_2, size());
    #endif

    base::erase(base::begin() + p1 - 1, base::begin() + p2 - 1);
}

template < class type, class device >
constexpr bool array<type,1,device>::is_view ( ) const
{
    return span::is_view();
}

template < class type, class device >
class array<type,1,device>::iterator
    extends public device::template vector<type>::iterator
{
    private: // Data
        int step = 1;

    private: // Typedef
        using base = device::template vector<type>::iterator;

    public: // Typedef
        using iterator_concept = common_type<typename std::iterator_traits<base>::iterator_category,std::random_access_iterator_tag>;
        using value_type       = decay<typename std::iterator_traits<base>::reference>;
        using reference        = std::iterator_traits<base>::reference;
        using pointer          = std::iterator_traits<base>::pointer;
        using difference_type  = std::iterator_traits<base>::difference_type;

    public: // Core
        constexpr iterator ( ) = default;
        constexpr iterator ( base init_iter )                extends base ( init_iter )                     { };
        constexpr iterator ( base init_iter, int init_step ) extends base ( init_iter ), step ( init_step ) { }; 

    public: // Operator.member
        constexpr reference operator *  ( )                   const { return *static_cast<const base&>(self); }
        constexpr pointer   operator -> ( )                   const { return  static_cast<const base&>(self); }
        constexpr reference operator [] ( difference_type t ) const { return  static_cast<const base&>(self)[t]; }

    public: // Operator.global
        friend constexpr bool                 operator ==  ( const iterator&       left, const iterator&       right ) { return static_cast<const base&>(left) == static_cast<const base&>(right); }
        friend constexpr std::strong_ordering operator <=> ( const iterator&       left, const iterator&       right ) { return std::compare_strong_order_fallback(static_cast<const base&>(left), static_cast<const base&>(right)); }
        friend constexpr iterator             operator  +  ( const iterator&       left,       difference_type right ) { return iterator(static_cast<const base&>(left ) + left .step * right, left .step); }
        friend constexpr iterator             operator  +  (       difference_type left, const iterator&       right ) { return iterator(static_cast<const base&>(right) + right.step * left,  right.step); }
        friend constexpr iterator             operator  -  ( const iterator&       left,       difference_type right ) { return iterator(static_cast<const base&>(left ) - left .step * right, left .step); }
        friend constexpr difference_type      operator  -  ( const iterator&       left, const iterator&       right ) { return (static_cast<const base&>(left) - static_cast<const base&>(right)) / std::max(left.step, right.step); }
        friend constexpr iterator&            operator ++  (       iterator&       left                              ) { static_cast<base&>(left) += left.step;         return left; }
        friend constexpr iterator             operator ++  (       iterator&       left,       int                   ) { let it = left; ++left;                         return it;   }
        friend constexpr iterator&            operator --  (       iterator&       left                              ) { static_cast<base&>(left) -= left.step;         return left; }
        friend constexpr iterator             operator --  (       iterator&       left,       int                   ) { let it = left; --left;                         return it;   }
        friend constexpr iterator&            operator +=  (       iterator&       left,       difference_type right ) { static_cast<base&>(left) += left.step * right; return left; }
        friend constexpr iterator&            operator -=  (       iterator&       left,       difference_type right ) { static_cast<base&>(left) -= left.step * right; return left; }
};

template < class type, class device >
class array<type,1,device>::const_iterator
    extends public device::template vector<type>::const_iterator
{
    private: // Data
        int step = 1;
    
    public: // Typedef
        using iterator_concept = common_type<typename std::iterator_traits<base>::iterator_category,std::random_access_iterator_tag>;
        using value_type       = decay<typename std::iterator_traits<base>::reference>;
        using reference        = std::iterator_traits<base>::reference;
        using pointer          = std::iterator_traits<base>::pointer;
        using difference_type  = std::iterator_traits<base>::difference_type;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( base init_iter )                extends base ( init_iter )                     { };
        constexpr const_iterator ( base init_iter, int init_step ) extends base ( init_iter ), step ( init_step ) { }; 

        constexpr reference operator *  ( )                   const { return *static_cast<const base&>(self); }
        constexpr pointer   operator -> ( )                   const { return  static_cast<const base&>(self); }
        constexpr reference operator [] ( difference_type t ) const { return  static_cast<const base&>(self)[t]; }

    public: // Operator.global
        friend constexpr bool                 operator ==  ( const const_iterator& left, const const_iterator& right ) { return static_cast<const base&>(left) == static_cast<const base&>(right); }
        friend constexpr std::strong_ordering operator <=> ( const const_iterator& left, const const_iterator& right ) { return std::compare_strong_order_fallback(static_cast<const base&>(left), static_cast<const base&>(right)); }
        friend constexpr const_iterator       operator  +  ( const const_iterator& left,       difference_type right ) { return const_iterator(static_cast<const base&>(left ) + left .step * right, left .step); }
        friend constexpr const_iterator       operator  +  (       difference_type left, const const_iterator& right ) { return const_iterator(static_cast<const base&>(right) + right.step * left,  right.step); }
        friend constexpr const_iterator       operator  -  ( const const_iterator& left,       difference_type right ) { return const_iterator(static_cast<const base&>(left ) - left .step * right, left .step); }
        friend constexpr difference_type      operator  -  ( const const_iterator& left, const const_iterator& right ) { return (static_cast<const base&>(left) - static_cast<const base&>(right)) / std::max(left.step, right.step); }
        friend constexpr const_iterator&      operator ++  (       const_iterator& left                              ) { static_cast<base&>(left) += left.step;         return left; }
        friend constexpr const_iterator       operator ++  (       const_iterator& left,       int                   ) { let it = left; ++left;                         return it;   }
        friend constexpr const_iterator&      operator --  (       const_iterator& left                              ) { static_cast<base&>(left) -= left.step;         return left; }
        friend constexpr const_iterator       operator --  (       const_iterator& left,       int                   ) { let it = left; --left;                         return it;   }
        friend constexpr const_iterator&      operator +=  (       const_iterator& left,       difference_type right ) { static_cast<base&>(left) += left.step * right; return left; }
        friend constexpr const_iterator&      operator -=  (       const_iterator& left,       difference_type right ) { static_cast<base&>(left) -= left.step * right; return left; }
};