template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) 
        self.base::operator=(static_cast<const base&>(init));
    else // if ( not init.ownership() )
    {
        self.base::resize(init.upper::size());
        device::copy(init.upper::begin(), init.upper::end(), self.base::begin());
    }
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
{
    if ( init.ownership() ) 
        self.base::operator=(static_cast<base&&>(init));
    else // if ( not init.ownership() )
    {
        self.base::resize(init.upper::size());
        device::move(init.upper::begin(), init.upper::end(), self.base::begin());
    }
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( self.ownership() and right.ownership() ) 
        self.base::operator=(static_cast<const base&>(right));
    else if ( self.ownership() and not right.ownership() )
    {
        self.base::resize(right.size());
        device::copy(right.upper::begin(), right.upper::end(), self.base::begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        if constexpr ( debug )
            if ( self.size() != right.size() )
                throw value_error("cannot assign array (with left.ownership() = false, left.size() = {}, right.size() = {}): size mismatches", self.size(), right.size());

        device::copy(right.base::begin(), right.base::end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        if constexpr ( debug )
            if ( self.size() != right.size() )
                throw value_error("cannot assign array (with left.ownership() = false, left.size() = {}, right.size() = {}): size mismatches", self.size(), right.size());

        device::copy(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    if ( self.ownership() and right.ownership() ) 
        self.base::operator=(static_cast<base&&>(right));
    else if ( self.ownership() and not right.ownership() )
    {
        self.base::resize(right.upper::size());
        device::move(right.upper::begin(), right.upper::end(), self.base::begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        if constexpr ( debug )
            if ( self.size() != right.size() )
                throw value_error("cannot assign array (with left.ownership() = false, left.size() = {}, right.size() = {}): size mismatches", self.size(), right.size());

        device::move(right.base::begin(), right.base::end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        if constexpr ( debug )
            if ( self.size() != right.size() )
                throw value_error("cannot assign array (with left.ownership() = false, left.size() = {}, right.size() = {}): size mismatches", self.size(), right.size());

        device::move(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
{
    if constexpr ( debug )
        if ( init_size < 0 )
            throw value_error("cannot initialize array (with size() = {}): size is negative", init_size);

    resize(init_size);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires copyable<type>
{
    if constexpr ( debug )
        if ( init_size < 0 )
            throw value_error("cannot initialize array (with size() = {}): size is negative", init_size);

    resize(init_size);
    device::fill(self.base::begin(), self.base::end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, invocable_r<type> auto init_value )
{
    if constexpr ( debug )
        if ( init_size < 0 )
            throw value_error("cannot initialize array (with size() = {}): size is negative", init_size);

    resize(init_size);
    device::generate(self.base::begin(), self.base::end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, invocable_r<type,int> auto init_value )
{
    if constexpr ( debug )
        if ( init_size < 0 )
            throw value_error("cannot initialize array (with size() = {}): size is negative", init_size);

    resize(init_size);
    for ( int i in range(init_size) )
        self.base::operator[](i-1) = init_value(i);
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::initializer_list<type> init )
    requires copyable<type>
    extends base ( std::forward<decltype(init)>(init) )
{
    
}

template < class type, class device >
template < class type2, class device2 >
constexpr array<type,1,device>::array ( const array<type2,1,device2>& cvt )
    requires convertible_to<type2,type>  
    extends array ( cvt.size() )
{
    if constexpr ( same_as<type,type2> )
        if ( cvt.ownership() )
            common_type<device,device2>::copy(cvt.array<type,1,device2>::base::begin(), cvt.array<type,1,device2>::base::end(), self.base::begin());
        else
            common_type<device,device2>::copy(cvt.array<type,1,device2>::upper::begin(), cvt.array<type,1,device2>::upper::end(), self.base::begin());
    else
        if ( cvt.ownership() )
            common_type<device,device2>::transform(cvt.array<type2,1,device>::base::begin(), cvt.array<type2,1,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
        else
            common_type<device,device2>::transform(cvt.array<type2,1,device>::upper::begin(), cvt.array<type2,1,device>::upper::end(), self.base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2, class device2 >
constexpr array<type,1,device>::array ( const array<type2,1,device2>& cvt )
    requires constructible_to<type2,type>  
    extends array ( cvt.size() )
{
    if constexpr ( same_as<type,type2> )
        if ( cvt.ownership() )
            common_type<device,device2>::copy(cvt.array<type,1,device2>::base::begin(), cvt.array<type,1,device2>::base::end(), self.base::begin());
        else
            common_type<device,device2>::copy(cvt.array<type,1,device2>::upper::begin(), cvt.array<type,1,device2>::upper::end(), self.base::begin());
    else
        if ( cvt.ownership() )
            common_type<device,device2>::transform(cvt.array<type2,1,device>::base::begin(), cvt.array<type2,1,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
        else
            common_type<device,device2>::transform(cvt.array<type2,1,device>::upper::begin(), cvt.array<type2,1,device>::upper::end(), self.base::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
constexpr int array<type,1,device>::dimension ( )
{
    return 1;
}

template < class type, class device >
constexpr int array<type,1,device>::size ( ) const
{
    return ownership() ? base::size() :
                         upper::size();
}

template < class type, class device >
constexpr int array<type,1,device>::capacity ( ) const
{
    return ownership() ? base::capacity() :
                         throw logic_error("cannot get memory capacity (with ownership() = false): this array does not own its data");
}

template < class type, class device >
constexpr array<int> array<type,1,device>::shape ( ) const
{
    return { size() };
}

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    return ownership() ? base::empty() :
                         upper::empty();
}

template < class type, class device >
constexpr array<type,1,device>::pointer array<type,1,device>::data ( )
{
    return ownership()  ? base::data()  :
           contiguous() ? upper::data() :
                          throw logic_error("cannot get native data pointer (with ownership() = false): this array does not own its data, and the viewed data is not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::const_pointer array<type,1,device>::data ( ) const
{
    return ownership()  ? base::data()  :
           contiguous() ? upper::data() :
                          throw logic_error("cannot get native data pointer (with ownership() = false): this array does not own its data, and the viewed data is not contiguous");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::begin ( )
{
    return ownership() ? iterator(base::data(), 1) :
                         upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::begin ( ) const
{
    return ownership() ? const_iterator(base::data(), 1) :
                         upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::end ( )
{
    return ownership() ? iterator(base::data() + base::size(), 1) :
                         upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::end ( ) const
{
    return ownership() ? const_iterator(base::data() + base::size(), 1) :
                         upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::reference array<type,1,device>::operator [] ( int pos )
{
    if constexpr ( debug )
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    
    return ownership() ? pos >= 0 ? base ::operator[](pos-1)             :
                                    base ::operator[](pos+base::size())  :
                         pos >= 0 ? upper::operator[](pos-1)             :
                                    upper::operator[](pos+upper::size());
}

template < class type, class device >
constexpr array<type,1,device>::const_reference array<type,1,device>::operator [] ( int pos ) const
{
    if constexpr ( debug )
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    
    return ownership() ? pos >= 0 ? base ::operator[](pos-1)             :
                                    base ::operator[](pos+base::size())  :
                         pos >= 0 ? upper::operator[](pos-1)             :
                                    upper::operator[](pos+upper::size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    if constexpr ( debug )
        if ( not ownership() ) 
            throw logic_error("cannot clear array (with ownership() = false): this array does not own its data");

    base::clear();
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( int new_size )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot resize array (with ownership() = false): this array does not own its data");
        if ( new_size < 0 )
            throw value_error("cannot resize array (with resize.size() = {}): size is negative", new_size);
    }

    base::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( array<int> new_shape )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot resize array (with ownership() = false): this array does not own its data");
        if ( new_shape.size() != 1 )
            throw value_error("cannot resize array (with dimension() = 1, resize.shape() = {}): dimension mismatches", new_shape.size());
        if ( new_shape.exist([] (int s) { return s < 0; }) )
            throw value_error("cannot resize array (with resize.shape() = {}): shape is negative", new_shape);
    }

    base::resize(new_shape[1]);
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
    requires ( axis == 1 or axis == -1 )
{
    if constexpr ( debug )
        if ( not ownership() ) 
            throw logic_error("cannot push into array (with ownership() = false): this array does not own its data");

    base::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,1,device>& array<type,1,device>::pop ( )
    requires ( axis == 1 or axis == -1 )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot pop from array (with ownership() = false): this array does not own its data");
        if ( empty() )
            throw value_error("cannot pop from array (with empty() = true)");
    }

    base::pop_back();
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,1,device>& array<type,1,device>::insert ( int new_pos, type new_value )
    requires ( axis == 1 or axis == -1 )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot insert into array (with ownership() = false): this array does not own its data");
        if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
            throw index_error("index {} is out of range with size {}", new_pos, size());
    }
        
    base::insert(new_pos >= 0 ? base::begin() + new_pos - 1 : base::begin() + new_pos + base::size(), std::move(new_value));
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,1,device>& array<type,1,device>::erase ( int old_pos )
    requires ( axis == 1 or axis == -1 )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot erase from array (with ownership() = false): this array does not own its data");
        if ( old_pos < -size() or old_pos == 0 or old_pos > size() )
            throw index_error("index {} is out of range with size {}", old_pos, size());
    }

    base::erase(old_pos >= 0 ? base::begin() + old_pos - 1 : base::begin() + old_pos + base::size());
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::flatten ( )
{
    return self;
}

template < class type, class device >
constexpr const array<type,1,device>& array<type,1,device>::flatten ( ) const
{
    return self;
}

template < class type, class device >
constexpr bool array<type,1,device>::ownership ( ) const
{
    return upper::ownership();
}

template < class type, class device >
constexpr bool array<type,1,device>::contiguous ( ) const
{
    return ownership() or upper::contiguous();
}

template < class type, class device >
constexpr auto array<type,1,device>::mdspan ( )
{
    using type1 = std::mdspan<type,std::dextents<int,1>,typename device::layout_type,typename device::template accessor_type<type>>;
    using type2 = std::mdspan<type,std::dextents<int,1>,std::layout_stride,          typename device::template accessor_type<type>>;

    if ( contiguous() )
    {
        auto ptr = data();
        auto shp = std::dextents<int,1>{size()};
        auto mds = type1(ptr, shp);
        return variant<type1,type2>(mds);
    }
    else
    {
        auto ptr  = upper::get_pointer(0);
        auto shp  = std::dextents<int,1>{size()};
        auto strd = std::array   <int,1>{upper::get_stride()};
        auto mp   = typename type2::mapping_type(shp, strd);
        auto mds  = type2(ptr, mp);
        return variant<type1,type2>(mds);
    }
}

template < class type, class device >
constexpr const auto array<type,1,device>::mdspan ( ) const
{
    using type1 = std::mdspan<const type,std::dextents<int,1>,typename device::layout_type,typename device::template accessor_type<const type>>;
    using type2 = std::mdspan<const type,std::dextents<int,1>,std::layout_stride,          typename device::template accessor_type<const type>>;

    if ( contiguous() )
    {
        auto ptr = data();
        auto shp = std::dextents<int,1>{size()};
        auto mds = type1(ptr, shp);
        return variant<type1,type2>(mds);
    }
    else
    {
        auto ptr  = upper::get_pointer(0);
        auto shp  = std::dextents<int,1>{size()};
        auto strd = std::array   <int,1>{upper::get_stride()};
        auto mp   = typename type2::mapping_type(shp, strd);
        auto mds  = type2(ptr, mp);
        return variant<type1,type2>(mds);
    }
}

template < class type, class device >
constexpr detail::array_shape<1> array<type,1,device>::get_shape ( ) const
{
    return { size() };
}