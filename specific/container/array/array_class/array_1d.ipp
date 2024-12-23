#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires std::copyable<type>
    extends vector ( not init.is_view() ? static_cast<const vector&>(init) otherwise vector(init.size()) )
{
    if ( init.is_view() ) [[unlikely]]
        device::copy(init.begin(), init.end(), vector::begin());
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
    extends vector ( not init.is_view() ? static_cast<vector&&>(init) otherwise vector(init.size()) )
{
    if ( init.is_view() ) [[unlikely]]
        device::move(init.begin(), init.end(), vector::begin());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires std::copyable<type>
{
    if ( not right.is_view() ) [[likely]]
        vector::operator=(static_cast<const vector&>(right));
    else [[unlikely]]
    {
        vector::resize(right.size());
        device::copy(right.begin(), right.end(), vector::begin());
    }
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    if ( not right.is_view() ) [[likely]]
        vector::operator=(static_cast<vector&&>(right));
    else [[unlikely]]
    {
        vector::resize(right.size());
        device::move(right.begin(), right.end(), vector::begin());
    }
}


template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
    extends vector ( init_size )
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires std::copyable<type>
    extends vector ( init_size, init_value )
{
    #if debug
        if ( init_size < 0 )
            throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( const std::initializer_list<type>& init )
    requires std::copyable<type>
    extends vector ( init )
{

}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type()> auto init_value )
    extends array ( init_size )
{
    device::generate(vector::begin(), vector::end(), init_value);
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
    device::copy(init.begin(), init.end(), vector::begin());
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r )
    requires std::convertible_to<std::ranges::range_value_t<decltype(r)>,type>
{
    if constexpr ( requires { r.size(); } )
    {
        #if debug
            if ( r.size() < 0 )
                throw value_error("construct array with negative size {}", r.size());
        #endif

        vector::resize(r.size());
        if constexpr ( requires { device::move(r.begin(), r.end(), vector::begin()); } )
            device::move(r.begin(), r.end(), vector::begin());
        else
            std::ranges::move(r, vector::begin());
    }
    else
        for ( auto&& val in r )
            self.vector::push_back(std::forward<decltype(val)>(val));
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r, int init_size )
    requires std::convertible_to<std::ranges::range_value_t<decltype(r)>,type>
    extends array ( init_size )
{
    #if debug
        if constexpr ( requires { r.size(); } )
            if ( r.size() != init_size )
                throw value_error("construct array with ambiguous size (with range-size = {}, explicit-size = {})", r.size(), r);
    #endif

    if constexpr ( requires { device::move(r.begin(), r.end(), vector::begin()); } )
        device::move(r.begin(), r.end(), vector::begin());
    else
        std::ranges::move(r, vector::begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires std::convertible_to<type2,type> but ( not std::same_as<type,type2> )
    extends array ( cvt.size() )
{
    if ( not cvt.is_view() ) [[likely]]
        device::transform(cvt.vector::begin(), cvt.vector::end(), vector::begin(), [] (const auto& val) { return type(val); });
    else [[unlikely]]
        device::transform(cvt.begin(), cvt.end(), vector::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    if ( not cvt.is_view() ) [[likely]]
        device::transform(cvt.vector::begin(), cvt.vector::end(), vector::begin(), [] (const auto& val) { return type(val); });
    else [[unlikely]]
        device::transform(cvt.begin(), cvt.end(), vector::begin(), [] (const auto& val) { return type(val); });
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
        return vector::size();
    else [[unlikely]]
        return mdspan::pointer()->column();
}

template < class type, class device >
constexpr array<int> array<type,1,device>::shape ( ) const
{
    return {1};
}

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    if ( not is_view() ) [[likely]]
        return vector::empty();
    else [[unlikely]]
        return mdspan::pointer()->column() == 0;
}

template < class type, class device >
constexpr type* array<type,1,device>::data ( )
{
    if ( not is_view() ) [[likely]]
        return const_cast<type*>(vector::data());
    else [[unlikely]]
        throw value_error("cannot get contiguous native data from array: it does not own its data and the borrowed data might sometimes be not contiguous");
}

template < class type, class device >
constexpr const type* array<type,1,device>::data ( ) const
{
    if ( not is_view() ) [[likely]]
        return vector::data();
    else [[unlikely]]
        throw value_error("cannot get contiguous native data from array: it does not own its data and the borrowed data might sometimes be not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::begin ( )
{
    if ( not is_view() ) [[likely]]
        return iterator(const_cast<type*>(vector::data()));
    else [[unlikely]]
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::begin ( ) const
{
    if ( not is_view() ) [[likely]]
        return iterator(const_cast<type*>(vector::data()));
    else [[unlikely]]

}

template < class type, class device >
constexpr type* array<type,1,device>::end ( )
    if ( not is_view() ) [[likely]]
        return iterator(const_cast<type*>(vector::data()));
    else [[unlikely]]

}

template < class type, class device >
constexpr const type* array<type,1,device>::end ( ) const
{
    if ( not is_view() ) [[likely]]
        return iterator(const_cast<type*>(vector::data()));
    else [[unlikely]]

}

template < class type, class device >
constexpr type& array<type,1,device>::operator [] ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( not is_view() ) [[likely]]
        return pos >= 0 ? vector::operator[](pos-1) otherwise
                          vector::operator[](pos+size());
    else [[unlikely]]
        return mdspan::pointer()->operator[](&self - mdspan::pointer()->views().data() + 1, pos);
}

template < class type, class device >
constexpr const type& array<type,1,device>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( not is_view() ) [[likely]]
        return pos >= 0 ? vector::operator[](pos-1) otherwise
                          vector::operator[](pos+size());
    else [[unlikely]]
        return mdspan::pointer()->operator[](&self - mdspan::pointer()->views().data() + 1, pos);
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    if ( is_view() )
        throw value_error("cannot call array.clear(): )

    vector::clear();
    vector::shrink_to_fit();
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( int new_size )
{
    #if debug
        if ( new_size < 0 )
            throw value_error("resize array with negative size {}", new_size);
    #endif

    vector::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
{
    vector::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::pop ( int pos )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    vector::erase(pos >= 0 ? vector::begin() + pos - 1 otherwise vector::begin() + pos + size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::insert ( int pos, type new_value )
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    vector::insert(pos >= 0 ? vector::begin() + pos - 1 otherwise vector::begin() + pos + size(), std::move(new_value));
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

    vector::erase(vector::begin() + p1 - 1, vector::begin() + p2 - 1);
}

template < class type, class device >
constexpr bool array<type,1,device>::is_view ( ) const
{
    return mdspan::pointer() != nullptr;
}

template < class type, class device >
    requires std::same_as<typename device::layout_type,std::layout_left>
class iterator
{
    private: // Data
        type* ptr = nullptr;
        int   stp = 1;

    public: // Typedef
        using  value_type      = type;
        using  pointer         = type*;
        using  reference       = type&;
        using  difference_type = std::ptrdiff_t;
        struct random_access_iterator_tag { };

    public: // Core
        constexpr iterator ( ) = default;
        constexpr iterator ( type* init_ptr )               extends ptr ( init_ptr )                   { };
        constexpr iterator ( type* init_ptr, int init_stp ) extends ptr ( init_ptr ), stp ( init_stp ) { }; 

    public: // Member
        constexpr type&           operator *  ( )             const { return *ptr; }
        constexpr type*           operator -> ( )             const { return ptr; }
        constexpr type&           operator [] ( int t )       const { return ptr[t]; }
        constexpr iterator        operator +  ( int t )       const { return iterator(ptr + t * stp, stp); }
        constexpr iterator        operator -  ( int t )       const { return iterator(ptr - t * stp, stp); }
        constexpr difference_type operator -  ( iterator it ) const { return (ptr - it.ptr) / stp; }
        constexpr iterator&       operator ++ ( )                   { ptr += stp; return self; }
        constexpr iterator        operator ++ ( int )               { let it = self; ++self; return it; }
        constexpr iterator&       operator += ( int t )             { ptr += t * stp; return self; }
        constexpr iterator&       operator -- ( )                   { ptr -= stp; return self; }
        constexpr iterator        operator -- ( int )               { let it = self; --self; return it; }
        constexpr iterator&       operator -= ( int t )             { ptr -= t * stp; return self; }

    public: // Operator
        friend constexpr bool operator ==  ( const iterator& left, const iterator& right ) { return left.ptr ==  right.ptr; }
        friend constexpr auto operator <=> ( const iterator& left, const iterator& right ) { return left.ptr <=> right.ptr; }
};