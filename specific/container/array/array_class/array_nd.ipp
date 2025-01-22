#pragma once

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) [[likely]]
    {
        self.base ::operator=(static_cast<const base&>(init));
        self.info ::resize(init.static_shape());
        self.lower::resize(init.static_shape());
    }
    else
    {
        self.resize(init.static_shape());
        device::copy(init.as_flat().begin(), init.as_flat().end(), self.as_flat().begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( array&& init )
{
    if ( init.ownership() ) [[likely]]
    {
        self.base ::operator=(static_cast<base&&>(init));
        self.info ::resize(init.static_shape());
        self.lower::resize(init.static_shape());
    }
    else
    {
        self.resize(init.static_shape());
        device::move(init.as_flat().begin(), init.as_flat().end(), self.as_flat().begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( self.ownership() and right.ownership() ) [[likely]]
    {
        self.base ::operator=(static_cast<const base&>(right));
        self.info ::resize(right.static_shape());
        self.lower::resize(right.static_shape());
    }

    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.static_shape());
        device::copy(right.as_flat().begin(), right.as_flat().end(), self.as_flat().begin());
    }

    else
    {
        #if debug
        if ( self.static_shape() == right.static_shape() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.static_shape(), right.static_shape());
        #endif
        device::copy(right.as_flat().begin(), right.as_flat().end(), self.as_flat().begin());
    } 

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( const array&& right )
{
    if ( self.ownership() and right.ownership() ) [[likely]]
    {
        self.base ::operator=(static_cast<base&&>(right));
        self.info ::resize(right.static_shape());
        self.lower::resize(right.static_shape());
    }

    else if ( self.ownership() and not right.ownership() )
    {
        self.resize(right.static_shape());
        device::move(right.as_flat().begin(), right.as_flat().end(), self.as_flat().begin());
    }

    else
    {
        #if debug
        if ( self.static_shape() == right.static_shape() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", self.static_shape(), right.static_shape());
        #endif
        device::move(right.as_flat().begin(), right.as_flat().end(), self.as_flat().begin());
    } 

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( int_type auto... args )
    requires ( sizeof...(args) == dim )
    extends base  ( multiply_first_until_last(args...) ),
            info  ( args... ),
            lower ( args... ),
{
    #if debug
    if ( not check_first_until_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,dim>{args...});
    #endif
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires copyable<type> and
             ( sizeof...(args) - 1 == dim ) and 
             detail::ints_until_last_type<type,decltype(args)...>
    extends base  ( multiply_first_until_second_last(args...), last_value_of(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,dim>{args...});
    #endif
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends base  ( multiply_first_until_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,dim>{args...});
    #endif
    device::generate(self.as_flat().begin(), self.as_flat().end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func_ints<type,decltype(args...)>
    extends vector ( multiply_first_to_second_last(args...) ),
            info   ( args... ),
            lower  ( args... )
{
    #if debug
    if ( not check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", static_array<int,dim>{args...});
    #endif
    device_generate_mdspan(last_value_of(args...)
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( std::initializer_list<array<type,dim-1,device>>& init )
{
    static_assert(false, "not coded yet. notice the shape is known till here");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
{
    self.resize(cvt.static_shape());
    device::transform(cvt.as_flat().begin(), cvt.as_flat().end(), self.as_flat().begin(), [] (const auto& val) { return type2(val); });
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
{
    self.resize(cvt.static_shape());
    device::transform(cvt.as_flat().begin(), cvt.as_flat().end(), self.as_flat().begin(), [] (const auto& val) { return type2(val); });
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
    assume[[base::size() == info::size()]];
    if ( ownership() ) [[likely]]
        return info::size();
    else
        return upper::size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<int> array<type,dim,device>::shape ( ) const
{   
    if ( ownership() ) [[likely]]
        return info::shape();
    else
        return upper::shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr inplace_array<int> array<type,dim,device>::inplace_shape ( ) const
{
    if ( ownership() ) [[likely]]
        return info::inplace_shape();
    else
        return upper::inplace_shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr static_array<int> array<type,dim,device>::static_shape ( ) const
{
    if ( ownership() ) [[likely]]
        return info::static_shape();
    else
        return upper::static_shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::row ( ) const
{
    if ( ownership() ) [[likely]]
        return info::row();
    else
        return upper::row();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::column ( ) const
    requires ( dim == 2 )
{
    if ( ownership() ) [[likely]]
        return info::column();
    else
        return upper::column();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::empty ( ) const
    requires ( dim == 2 )
{
    assume[[base::empty() == info::empty()]];
    if ( ownership() ) [[likely]]
        return info::empty();
    else
        return upper::empty();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::data ( )
{
    if ( ownership() ) [[likely]]
        return base::data();
    else if ( contiguous() )
        return upper::data();
    else
        throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data might be not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::data ( ) const
{
    if ( ownership() ) [[likely]]
        return base::data();
    else if ( contiguous() )
        return upper::data();
    else
        throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data might be not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::begin ( )
{
    if ( ownership() ) [[likely]]
        return lower::begin();
    else
        return upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::begin ( ) const
{
    if ( ownership() ) [[likely]]
        return lower::begin()
    else
        return upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::end ( )
{
    if ( ownership() ) [[likely]]
        return lower::end();
    else
        return upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::end ( ) const
{
    if ( ownership() ) [[likely]]
        return lower::end();
    else
        return upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim-1,device>& array<type,dim,device>::operator[] ( int pos )
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    if ( ownership() ) [[likely]]
        return pos >= 0 ? lower::operator[](pos-1) otherwise
                          lower::operator[](pos+size());
    else
        return pos >= 0 ? upper::operator[](pos-1) otherwise
                          upper::operator[](pos+size());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim-1,device>& array<type,dim,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    if ( ownership() ) [[likely]]
        return pos >= 0 ? lower::operator[](pos-1) otherwise
                          lower::operator[](pos+size());
    else
        return pos >= 0 ? upper::operator[](pos-1) otherwise
                          upper::operator[](pos+size());
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::clear ( )
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

template < class type, int dim, class device >
    requires ( dim >= 2 )
template_int_axis
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int new_size )
{
    #if debug
    if ( not ownership() ) [[unlikely]]
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size < 0 )
        throw value_error("resize array with negative shape {} (on axis {})", new_size, axis);
    #endif
    
    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( const array<int,1>& new_size )
{
    #if debug
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
    if ( args < 0 or ... )
        throw value_error("resize array with negative shape {}", static_array<int,dim>{args...});
    #endif

    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::push ( const array<type,dim-1,device>& new_value )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::pop ( int old_pos )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::insert ( int old_pos, const array<type,dim-1,device>& new_value )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::erase ( int old_pos_1, int old_pos_2 )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,1,device>& array<type,dim,device>::as_flat ( )
{
    if ( ownership() ) [[likely]]
        return static_cast<flat&>(self);
    else
        throw logic_error("cannot make array as_flat: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,1,device>& array<type,dim,device>::as_flat ( ) const
{
    if ( ownership() ) [[likely]]
        return static_cast<flat&>(self);
    else
        throw logic_error("cannot make array as_flat: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::as_transpose ( )
{
    if ( ownership() ) [[likely]]
        return lower::transpose();
    else if ( upper::attribute() == upper::transposed )
        return upper::template host<2>();
    else
        throw logic_error("cannot make array as_transpose: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim,device>& array<type,dim,device>::as_transpose ( ) const
{
    if ( ownership() ) [[likely]]
        return lower::transpose();
    else if ( upper::attribute() == upper::transposed )
        return upper::template host<2>();
    else
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
constexpr array<type,dim,device>::reference array<type,dim,device>::at ( int_type auto... args )
    requires ( sizeof...(args) == dim )
{
    if ( ownership() ) [[likely]]
        return std::mdspan<type,std::dextents<dim>,typename device::layout_type>(data(), static_cast<const std::array<int,dim>&>(static_shape()))[args...];
    else
        return upper::at(args...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_reference array<type,dim,device>::at ( int_type auto... args ) const
    requires ( sizeof...(args) == dim )
{
    if ( ownership() ) [[likely]]
        return std::mdspan<type,std::dextents<dim>,typename device::layout_type>(data(), static_cast<const std::array<int,dim>&>(static_shape()))[args...];
    else
        return upper::at(args...);
}
