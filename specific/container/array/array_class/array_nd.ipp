#pragma once


template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(init));
        self.info ::resize(init.info::static_shape());
        self.lower::resize(init.info::static_shape());
    }
    else // if ( not init.ownership() )
    {
        self.resize(init.upper::static_shape());
        if ( init.upper::contiguous() )
            device::copy(init.upper::data(), init.upper::data() + init.upper::size(), self.base::data());
        else
            device::copy(init.upper::begin(), init.upper::end(), self./*line-wise*/begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( array&& init )
{
    if ( init.ownership() ) 
    {
        self.base ::operator=(static_cast<base&&>(init));
        self.info ::resize(init.info::static_shape());
        self.lower::resize(init.info::static_shape());
    }
    else // if ( not init.owenrship() )
    {
        self.resize(init.upper::static_shape());
        if ( init.upper::contiguous() ) 
            device::move(init.upper::data(), init.upper::data() + init.upper::size(), self.base::data());
        else
            device::move(init.upper::begin(), init.upper::end(), self./*line-wise*/begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( self.ownership() and right.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(right));
        self.info ::resize(right.info::static_shape());
        self.lower::resize(right.info::static_shape());
    }
    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.upper::static_shape());
        if ( right.upper::contiguous() ) 
            device::copy(right.upper::data(), right.upper::data() + right.upper::size(), self.base::data());
        else
            device::copy(right.upper::begin(), right.upper::end(), self./*line-wise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::static_shape() != right.info::static_shape() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.static_shape(), right.static_shape());
        #endif
        if ( self.upper::contiguous() )
            device::copy(right.base::data(), right.base::data() + right.base::size(), self.upper::data());
        else
            device::copy(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::static_shape() != right.upper::static_shape() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.static_shape(), right.static_shape());
        #endif
        if ( self.upper::contiguous() and right.upper::contiguous() ) 
            device::copy(right.upper::data(), right.upper::data() + right.upper::size(), self.upper::data());
        else
            device::copy(right.upper::begin(), right.upper::end(), self.upper::end());
    }

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( array&& right )
{
    if ( self.ownership() and right.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(right));
        self.info ::resize(right.info::static_shape());
        self.lower::resize(right.info::static_shape());
    }
    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.upper::static_shape());
        if ( right.upper::contiguous() ) 
            device::move(right.upper::data(), right.upper::data() + right.upper::size(), self.base::data());
        else
            device::move(right.upper::begin(), right.upper::end(), self./*line-wise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::static_shape() != right.info::static_shape() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.static_shape(), right.static_shape());
        #endif
        if ( self.upper::contiguous() )
            device::move(right.base::data(), right.base::data() + right.base::size(), self.upper::data());
        else
            device::move(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::static_shape() != right.upper::static_shape() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.static_shape(), right.static_shape());
        #endif
        if ( self.upper::contiguous() and right.upper::contiguous() ) 
            device::move(right.upper::data(), right.upper::data() + right.upper::size(), self.upper::data());
        else
            device::move(right.upper::begin(), right.upper::end(), self.upper::end());
    }

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( int_type auto... args )
    requires ( sizeof...(args) == dim )
    extends base  ( detail::multiply_first_until_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,dim>{args...});
    #endif
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires copyable<type> and
             ( sizeof...(args) - 1 == dim ) and 
             detail::ints_until_last_type<type,decltype(args)...>
    extends base  ( detail::multiply_first_until_second_last(args...), last_value_of(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_shape());
    #endif
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends base  ( detail::multiply_first_until_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_shape());
    #endif
    device::generate(self.base::begin(), self.base::end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func_ints<type,decltype(args)...>
    extends base  ( detail::multiply_first_to_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_shape());
    #endif
    detail::md_generate(self, static_shape(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( std::initializer_list<array<type,dim-1,device>> init )
    requires copyable<type>
{
    static_assert(false, "not coded yet. notice the shape is known till here");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends array ( cvt.static_shape() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,dim,device>::base::begin(), cvt.array<type2,dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
    else if ( cvt.contiguous() )
        device::transform(cvt.array<type2,dim,device>::upper::data(), cvt.array<type2,dim,device>::upper::data() + cvt.array<type2,dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type2(val); });
    else
        device::transform(cvt.array<type2,dim,device>::upper::begin(), cvt.array<type2,dim,device>::upper::end(), self./*line-wise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.static_shape() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,dim,device>::base::begin(), cvt.array<type2,dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
    else if ( cvt.contiguous() )
        device::transform(cvt.array<type2,dim,device>::upper::data(), cvt.array<type2,dim,device>::upper::data() + cvt.array<type2,dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type2(val); });
    else
        device::transform(cvt.array<type2,dim,device>::upper::begin(), cvt.array<type2,dim,device>::upper::end(), self./*line-wise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class device2 >
constexpr array<type,dim,device>::array ( const array<type,dim,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends array ( cvt.static_shape() )
{
    if constexpr ( not same_as<device,cpu> )
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                device::copy(cvt.array<type,dim,device2>::base::begin(), cvt.array<type,dim,device2>::base::end(), self.base::begin());
            else if ( cvt.contiguous() )
                device::copy(cvt.array<type,dim,device2>::upper::data(), cvt.array<type,dim,device2>::upper::data() + cvt.array<type,dim,device2>::upper::size(), self.base::data());
            else
                device::copy(cvt.array<type,dim,device2>::upper::begin(), cvt.array<type,dim,device2>::upper::end(), self./*line-wise*/begin());
        else
            device::copy(cvt.array<type,dim,device2>::upper::begin(), cvt.array<type,dim,device2>::upper::end(), self./*line-wise*/begin());
    else
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                device2::copy(cvt.array<type,dim,device2>::base::begin(), cvt.array<type,dim,device2>::base::end(), self.base::begin());
            else if ( cvt.contiguous() )
                device2::copy(cvt.array<type,dim,device2>::upper::data(), cvt.array<type,dim,device2>::upper::data() + cvt.array<type,dim,device2>::upper::size(), self.base::data());
            else
                device2::copy(cvt.array<type,dim,device2>::upper::begin(), cvt.array<type,dim,device2>::upper::end(), self./*line-wise*/begin());
        else
            device2::copy(cvt.array<type,dim,device2>::upper::begin(), cvt.array<type,dim,device2>::upper::end(), self./*line-wise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::dimension ( )
{
    return dim;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::size ( ) const
{
    [[assume(int(base::size()) == info::size())]];
    return ownership() ? info::size() otherwise
                         upper::size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<int> array<type,dim,device>::shape ( ) const
{   
    return ownership() ? info::shape() otherwise
                         upper::shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr inplace_array<int,dim> array<type,dim,device>::inplace_shape ( ) const
{
    return ownership() ? info::inplace_shape() otherwise
                         upper::inplace_shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr static_array<int,dim> array<type,dim,device>::static_shape ( ) const
{
    return ownership() ? info::static_shape() otherwise
                         upper::static_shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::row ( ) const
{
    return ownership() ? info::row() otherwise
                         upper::row();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::column ( ) const
    requires ( dim == 2 )
{
    return ownership() ? info::column() otherwise
                         upper::column();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr bool array<type,dim,device>::empty ( ) const
{
    [[assume(base::empty() == info::empty())]];
    return ownership() ? info::empty() otherwise
                         upper::empty();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::data ( )
{
    return ownership()  ? base::data()  otherwise
           contiguous() ? upper::data() otherwise
                          throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::data ( ) const
{
    return ownership()  ? base::data()  otherwise
           contiguous() ? upper::data() otherwise
                          throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::begin ( )
{
    return ownership() ? lower::begin() otherwise
                         upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::begin ( ) const
{
    return ownership() ? lower::begin() otherwise
                         upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::end ( )
{
    return ownership() ? lower::end() otherwise
                         upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::end ( ) const
{
    return ownership() ? lower::end() otherwise 
                         upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim-1,device>& array<type,dim,device>::operator[] ( int pos )
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)            otherwise
                                    lower::operator[](pos+info::row())  otherwise
                         pos >= 0 ? upper::operator[](pos-1)            otherwise
                                    upper::operator[](pos+upper::row());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim-1,device>& array<type,dim,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)            otherwise
                                    lower::operator[](pos+info::row())  otherwise
                         pos >= 0 ? upper::operator[](pos-1)            otherwise
                                    upper::operator[](pos+upper::row());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::clear ( )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot clear array: it does not own its data");
    #endif

    base ::clear();
    base ::shrink_to_fit();
    info ::clear();
    lower::clear();
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int new_size )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size < 0 )
        throw value_error("resize array with negative shape {} (on axis {})", new_size, axis);
    #endif
    
    
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( const array<int,1>& new_size )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size.size() != dimension() )
        throw value_error("resize array with inconsistent dimension (with provided = {}, expected = {})", new_size.size(), dimension());
 // if ( new_size.any([] (int s) { return s < 0;}))
 //     throw value_error("resize array with negative shape {}", new_size);
    #endif

    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == dim )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot resize array: it does not own its data");
    if ( not detail::check_first_until_last_as_positive(args...) )
        throw value_error("resize array with negative shape {}", static_array<int,dim>{args...});
    #endif

    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::push ( array<type,dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::pop ( int old_pos )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::insert ( int old_pos, array<type,dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::erase ( int old_pos_1, int old_pos_2 )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,1,device>& array<type,dim,device>::as_flat ( )
{
    return ownership() ? static_cast<array<type,1,device>&>(static_cast<flat&>(self)) otherwise
                         throw logic_error("cannot make array as_flat: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,1,device>& array<type,dim,device>::as_flat ( ) const
{
    return ownership() ? static_cast<const array<type,1,device>&>(static_cast<const flat&>(self)) otherwise
                         throw logic_error("cannot make array as_flat: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::as_transpose ( )
{
    return ownership()                                           ? lower::as_transpose()     otherwise
           upper::get_attribute() == detail::transpose_attribute ? upper::template get_host<2>() otherwise
                                                                   throw logic_error("cannot make array as_transpose: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim,device>& array<type,dim,device>::as_transpose ( ) const
{
    return ownership()                                           ? lower::as_transpose()     otherwise
           upper::get_attribute() == detail::transpose_attribute ? upper::template get_host<2>() otherwise
                                                                   throw logic_error("cannot make array as_transpose: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr bool array<type,dim,device>::ownership ( ) const
{
    return upper::ownership();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr bool array<type,dim,device>::contiguous ( ) const
{
    return ownership() or upper::contiguous();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::get_size_top ( ) const
{
    return ownership() ? info::size() otherwise
                         upper::get_size_top();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int axis >
constexpr int array<type,dim,device>::get_size_axis ( ) const
{
    static_assert ( axis >= 1 and axis <= dimension() );
    return ownership() ? info ::template get_size_axis<axis>() otherwise
                         upper::template get_size_axis<axis>();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_rows ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) otherwise
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_rows ( int_type auto... offsets) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) otherwise
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_columns ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) otherwise
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_columns ( int_type auto... offsets) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) otherwise
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::reference array<type,dim,device>::get_value ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );
    return ownership() ? std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>
                             (base::data(), static_cast<const std::array<int,dim>&>(info::static_shape()))[offsets...] otherwise
                         upper::get_value(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_reference array<type,dim,device>::get_value ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );
    return ownership() ? std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>
                             (const_cast<pointer>(base::data()), static_cast<const std::array<int,dim>&>(info::static_shape()))[offsets...] otherwise
                         upper::get_value(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::get_pointer ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );
    return ownership() ? std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>
                             (base::data(), static_cast<const std::array<int,dim>&>(info::static_shape())).mapping()(offsets...) + base::data() otherwise
                         upper::get_pointer(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::get_pointer ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );
    if constexpr ( is_pointer<typename device::template pointer<type>> )
        return ownership() ? std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>
                                (const_cast<pointer>(base::data()), static_cast<const std::array<int,dim>&>(info::static_shape())).mapping()(offsets...) + base::data() otherwise
                             upper::get_pointer(offsets...);
    else
        return ownership() ? std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>
                                (static_cast<pointer>(base::data()), static_cast<const std::array<int,dim>&>(info::static_shape())).mapping()(offsets...) + base::data() otherwise
                             upper::get_pointer(offsets...);
}
