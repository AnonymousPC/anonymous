#pragma once

template < class type, class device >
constexpr array<type,max_dim,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(init));
        self.info ::resize(init.info::shape());
        self.lower::resize(init.info::shape());
    }
    else // if ( not init.ownership() )
    {
        self.resize(init.upper::shape());
        device::copy(init.upper::begin(), init.upper::end(), self./*line-wise*/begin());
    }
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( array&& init )
{
    if ( init.ownership() ) 
    {
        self.base ::operator=(static_cast<base&&>(init));
        self.info ::resize(init.info::shape());
        self.lower::resize(init.info::shape());
    }
    else // if ( not init.owenrship() )
    {
        self.resize(init.upper::shape());
        device::move(init.upper::begin(), init.upper::end(), self./*line-wise*/begin());
    }
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( self.ownership() and right.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(right));
        self.info ::resize(right.info::shape());
        self.lower::resize(right.info::shape());
    }
    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.upper::shape());
        device::copy(right.upper::begin(), right.upper::end(), self./*line-wise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.info::shape() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        device::copy(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.upper::shape() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        device::copy(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::operator = ( array&& right )
{
    if ( self.ownership() and right.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(right));
        self.info ::resize(right.info::shape());
        self.lower::resize(right.info::shape());
    }
    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.upper::shape());
        device::move(right.upper::begin(), right.upper::end(), self./*line-wise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.info::shape() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        device::move(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.upper::shape() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        device::move(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( int_type auto... args )
    requires ( sizeof...(args) == max_dim )
    extends base  ( detail::multiply_first_until_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,max_dim>{args...});
    #endif
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( auto... args )
    requires copyable<type> and
             ( sizeof...(args) - 1 == max_dim ) and 
             detail::ints_until_last_type<type,decltype(args)...>
    extends base  ( detail::multiply_first_until_second_last(args...), last_value_of(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,max_dim>{args...});
    #endif
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == max_dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends base  ( detail::multiply_first_until_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,max_dim>{args...});
    #endif
    device::generate(self.base::begin(), self.base::end(), last_value_of(args...));
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == max_dim ) and
             detail::ints_until_last_func_ints<type,decltype(args)...>
    extends base  ( detail::multiply_first_to_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,max_dim>{args...});
    #endif
    detail::md_generate(self, shape(), last_value_of(args...));
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( std::initializer_list<array<type,max_dim-1,device>> init )
    requires copyable<type>
{
    static_assert(false, "not coded yet. notice the shape is known till here");
}

template < class type, class device >
template < class type2 >
constexpr array<type,max_dim,device>::array ( const array<type2,max_dim,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends array ( cvt.shape() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,max_dim,device>::base::begin(), cvt.array<type2,max_dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
    else
        device::transform(cvt.array<type2,max_dim,device>::upper::begin(), cvt.array<type2,max_dim,device>::upper::end(), self./*line-wise*/begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,max_dim,device>::array ( const array<type2,max_dim,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.shape() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,max_dim,device>::base::begin(), cvt.array<type2,max_dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
    else
        device::transform(cvt.array<type2,max_dim,device>::upper::begin(), cvt.array<type2,max_dim,device>::upper::end(), self./*line-wise*/begin());
}

template < class type, class device >
template < class device2 >
constexpr array<type,max_dim,device>::array ( const array<type,max_dim,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends array ( cvt.shape() )
{
    static_assert(same_as<typename device ::layout_type,std::layout_right> or same_as<typename device ::layout_type,std::layout_left>);
    static_assert(same_as<typename device2::layout_type,std::layout_right> or same_as<typename device2::layout_type,std::layout_left>);

    if constexpr ( not same_as<device,cpu> )
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                device::copy(cvt.array<type,max_dim,device2>::base::begin(), cvt.array<type,max_dim,device2>::base::end(), self.base::begin());
            else
                device::copy(cvt.array<type,max_dim,device2>::upper::begin(), cvt.array<type,max_dim,device2>::upper::end(), self./*line-wise*/begin());
        else
            if ( cvt.ownership() )
                device::copy(cvt.array<type,max_dim,device2>::upper::begin(), cvt.array<type,max_dim,device2>::upper::end(), self./*line-wise*/begin());
            else
                device::copy(cvt.array<type,max_dim,device2>::upper::host().array<type,max_dim,device2>::base::begin(), cvt.array<type,max_dim,device2>::upper::host().array<type,max_dim,device2>::base::end(), self.base::begin());
    else
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                device2::copy(cvt.array<type,max_dim,device2>::base::begin(), cvt.array<type,max_dim,device2>::base::end(), self.base::begin());
            else
                device2::copy(cvt.array<type,max_dim,device2>::upper::begin(), cvt.array<type,max_dim,device2>::upper::end(), self./*line-wise*/begin());
        else
            if ( cvt.ownership() )
                device2::copy(cvt.array<type,max_dim,device2>::upper::begin(), cvt.array<type,max_dim,device2>::upper::end(), self./*line-wise*/begin());
            else
                device2::copy(cvt.array<type,max_dim,device2>::upper::host().array<type,max_dim,device2>::base::begin(), cvt.array<type,max_dim,device2>::upper::host().array<type,max_dim,device2>::base::end(), self.base::begin());
}

template < class type, class device >
constexpr int array<type,max_dim,device>::dimension ( )
{
    return max_dim;
}

template < class type, class device >
constexpr int array<type,max_dim,device>::size ( ) const
{
    [[assume(int(base::size()) == info::size())]];
    return ownership() ? info::size() otherwise
                         upper::size();
}

template < class type, class device >
constexpr static_array<int,max_dim> array<type,max_dim,device>::shape ( ) const
{   
    return ownership() ? info::shape() otherwise
                         upper::shape();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::row ( ) const
    requires ( max_dim == 2 )
{
    return ownership() ? info::row() otherwise
                         upper::row();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::column ( ) const
    requires ( max_dim == 2 )
{
    return ownership() ? info::column() otherwise
                         upper::column();
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::empty ( ) const
{
    [[assume(base::empty() == info::empty())]];
    return ownership() ? info::empty() otherwise
                         upper::empty();
}

template < class type, class device >
constexpr array<type,max_dim,device>::pointer array<type,max_dim,device>::data ( )
{
    return ownership() ? base::data() otherwise
                         throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_pointer array<type,max_dim,device>::data ( ) const
{
    return ownership() ? base::data() otherwise
                         throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, class device >
constexpr array<type,max_dim,device>::iterator array<type,max_dim,device>::begin ( )
{
    return ownership() ? lower::begin() otherwise
                         upper::begin();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_iterator array<type,max_dim,device>::begin ( ) const
{
    return ownership() ? lower::begin() otherwise
                         upper::begin();
}

template < class type, class device >
constexpr array<type,max_dim,device>::iterator array<type,max_dim,device>::end ( )
{
    return ownership() ? lower::end() otherwise
                         upper::end();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_iterator array<type,max_dim,device>::end ( ) const
{
    return ownership() ? lower::end() otherwise
                         upper::end();
}

template < class type, class device >
constexpr array<type,max_dim-1,device>& array<type,max_dim,device>::operator [] ( int pos )
{
    #if debug
    if ( pos < -get_size_axis<1>() or pos == 0 or pos > get_size_axis<1>() )
        throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), 1);
    #endif

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)                                  otherwise
                                    lower::operator[](pos+info::template get_size_axis<1>())  otherwise
                         pos >= 0 ? upper::operator[](pos-1)                                  otherwise
                                    upper::operator[](pos+upper::template get_size_axis<1>());
}

template < class type, class device >
constexpr const array<type,max_dim-1,device>& array<type,max_dim,device>::operator [] ( int pos ) const
{
    #if debug
    if ( pos < -get_size_axis<1>() or pos == 0 or pos > get_size_axis<1>() )
        throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), 1);
    #endif

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)                                  otherwise
                                    lower::operator[](pos+info::template get_size_axis<1>())  otherwise
                         pos >= 0 ? upper::operator[](pos-1)                                  otherwise
                                    upper::operator[](pos+upper::template get_size_axis<1>());
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::clear ( )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot clear array: it does not own its data");
    #endif

    base ::clear();
    base ::shrink_to_fit();
    info ::clear();
    lower::clear();
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( int new_size )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size < 0 )
        throw value_error("resize array with negative shape {} (on axis {})", new_size, axis);
    #endif
    
    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == max_dim )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot resize array: it does not own its data");
    if ( not detail::check_first_until_last_as_positive(args...) )
        throw value_error("resize array with negative shape {}", static_array<int,max_dim>{args...});
    #endif

    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( static_array<int,max_dim> new_size )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot resize array: it does not own its data");
 // if ( new_size.any([] (int s) { return s < 0;}))
 //     throw value_error("resize array with negative shape {}", new_size);
    #endif

    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::push ( array<type,max_dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::pop ( int old_pos )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::insert ( int old_pos, array<type,max_dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::erase ( int old_pos_1, int old_pos_2 )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, class device >
constexpr array<type,1,device>& array<type,max_dim,device>::flatten ( )
{
    return ownership() ? static_cast<array<type,1,device>&>(static_cast<flat&>(self)) otherwise
                         throw logic_error("cannot flatten array: it does not own its data");
}

template < class type, class device >
constexpr const array<type,1,device>& array<type,max_dim,device>::flatten ( ) const
{
    return ownership() ? static_cast<const array<type,1,device>&>(static_cast<const flat&>(self)) otherwise
                         throw logic_error("cannot flatten array: it does not own its data");
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::transpose ( )
{
    return ownership() ? lower::transpose() otherwise
                         upper::get_host();
}

template < class type, class device >
constexpr const array<type,max_dim,device>& array<type,max_dim,device>::transpose ( ) const
{
    return ownership() ? lower::transpose() otherwise
                         upper::get_host();
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::ownership ( ) const
{
    return upper::ownership();
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::contiguous ( ) const
{
    return ownership();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::get_size_top ( ) const
{
    return info::size();
}

template < class type, class device >
template < int axis >
constexpr int array<type,max_dim,device>::get_size_axis( ) const
{
    static_assert ( axis >= 1 and axis <= max_dim );
    return ownership() ? info ::template get_size_axis<axis>() otherwise
                         upper::template get_size_axis<axis>();
}

template < class type, class device >
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_rows ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) otherwise
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_rows ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) otherwise
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_columns ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) otherwise
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_columns ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) otherwise
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, class device >
constexpr array<type,max_dim,device>::reference array<type,max_dim,device>::get_value ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == max_dim );
    using mdspan = std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    [[assume(ownership())]];
    return mdspan(base::data(), info::shape())[offsets...];
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_reference array<type,max_dim,device>::get_value ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == max_dim );
    using mdspan = std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    [[assume(ownership())]];
    if constexpr ( is_pointer<typename  device::template pointer<type>> )
        return mdspan(const_cast<pointer>(base::data()), info::shape())[offsets...];
    else 
        return mdspan(static_cast<pointer>(base::data()), info::shape())[offsets...];
}

template < class type, class device >
constexpr array<type,max_dim,device>::pointer array<type,max_dim,device>::get_pointer ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == max_dim );
    using mdspan = std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    [[assume(ownership())]];
    return base::data() + mdspan(base::data(), info::shape()).mapping()(offsets...);
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_pointer array<type,max_dim,device>::get_pointer ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == max_dim );
    using mdspan = std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    [[assume(ownership())]];
    if constexpr ( is_pointer<typename  device::template pointer<type>> )
        return base::data() + mdspan(const_cast<pointer>(base::data()), info::shape()).mapping()(offsets...);
    else
        return base::data() + mdspan(static_cast<pointer>(base::data()), info::shape()).mapping()(offsets...);
}
