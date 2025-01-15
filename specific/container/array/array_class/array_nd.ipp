#pragma once

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( const array& init )
    requires copyable<type>
    extends vector ( /*initialized latter*/ ),
            info   ( static_cast<const info&>(init) ),
            lower  ( self, static_shape() )
{
    if ( right.independent() ) [[likely]]
        vector::operator=(static_cast<const vector&>(right));
    else
    {
        resize(right.static_shape());
        device::copy(right.begin(), right.end(), begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( array&& init )
    extends vector ( /*initialized latter*/ ),
            info   ( static_cast<info&&>(init) ),
            lower  ( self, static_shape() )
{
    if ( right.independent() ) [[likely]]
        vector::operator=(static_cast<vector&&>(right));
    else
    {
        resize(right.static_shape());
        device::move(right.begin(), right.end(), begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( independent() and right.independent() ) [[likely]]
    {
        vector::operator=(static_cast<const vector&>(right));
        info  ::operator=(static_cast<const info  &>(right));
        lower ::resize(static_shape());
    }

    else
    {
        if ( independent() )
            resize(right.static_shape());
        #if debug
        else if ( static_shape() != right.static_shape() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", static_shape(), right.static_shape());
        #endif
        device::copy(right.begin(), right.end(), begin());    
    }

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( const array&& right )
{
    if ( independent() and right.independent() ) [[likely]]
    {
        vector::operator=(static_cast<const vector&>(right));
        info  ::operator=(static_cast<const info  &>(right));
        lower ::resize(static_shape());
    }

    else
    {
        if ( independent() )
            resize(right.static_shape());
        #if debug
        else if ( static_shape() != right.static_shape() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on shape (with left_shape = {}, right_shape = {})", static_shape(), right.static_shape());
        #endif
        device::copy(right.begin(), right.end(), begin());    
    }

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( int_type auto... args )
    requires ( sizeof...(args) == dim )
    extends vector ( args * ... ),
            info   ( self, { args... } ),
            upper  ( ),
            lower  ( self, { args... } )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and 
             detail::ints_until_last_type<type,decltype(args)...> and
             copyable<type>
    extends vector ( detail::multiply_first_to_second_last(args...), last_value_of(args...) ),
            info   ( self, { args... } ),
            upper  ( ),
            lower  ( self, { args... } )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends vector ( detail::multiply_first_to_second_last(args...) ),
            info   ( self, { args... } ),
            upper  ( ),
            lower  ( self, { args... } )
{
    device::generate(vector::begin(), vector::end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func_ints<type,decltype(args...)>
    extends vector ( detail::multiply_first_to_second_last(args...) ),
            info   ( self, { args... } ),
            upper  ( ),
            lower  ( self, { args... } )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::array ( const std::initializer_list<array<type,dim-1,device>>& init )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends vector ( cvt.size() ),
            info   ( static_cast<const info&>(cvt) ),
            upper  ( ),
            lower  ( self, static_shape() )
{
    if ( cvt.independent() ) [[likely]]
        device::transform(cvt.vector::begin(), cvt.vector::end(), vector::begin(), [] (const auto& val) { return type2(val); });
    else
        static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends vector ( cvt.size() ),
            info   ( static_cast<const info&>(cvt) ),
            upper  ( ),
            lower  ( self, static_shape() )
{
    if ( cvt.independent() ) [[likely]]
        device::transform(cvt.vector::begin(), cvt.vector::end(), vector::begin(), [] (const auto& val) { return type2(val); });
    else
     //
        static_assert(false, "not coded yet");
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
    if ( independent() ) [[likely]]
        return vector::size();
    else
        return upper::size();
}

// template < class type, int dim, class device >
//     requires ( dim >= 2 )
// constexpr array<int> array<type,dim,device>::shape ( ) const
// {
//     return info::shape();
// }

// template < class type, int dim, class device >
//     requires ( dim >= 2 )
// constexpr inplace_array<int> array<type,dim,device>::inplace_shape ( ) const
// {
//     return info::inplace_shape();
// }

// template < class type, int dim, class device >
//     requires ( dim >= 2 )
// constexpr static_array<int> array<type,dim,device>::static_shape ( ) const
// {
//     return info::static_shape();
// }

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::row ( ) const
{
    if ( independent() ) [[likely]]
        return info::row();
    else
        return upper::row();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::column ( ) const
    requires ( dim == 2 )
{
    if ( independent() ) [[likely]]
        return info::column();
    else
        return upper::column();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr int array<type,dim,device>::empty ( ) const
    requires ( dim == 2 )
{
    if ( independent() ) [[likely]]
        return vector::empty();
    else
        return upper::empty();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::data ( ) const
{
    if constexpr ( requires { { vector::data() } -> convertible_to<const_pointer>; } )
        if ( independent() ) [[likely]]
            return vector::data();
        else if ( ( upper::tag() == upper::row_tag    and same_as<typename device::layout_type,std::layout_right> ) or
                  ( upper::tag() == upper::column_tag and same_as<typename device::layout_type,std::layout_left > ) )
            return upper::data();
        else
            throw logic_error("cannot get native data from array: it does not own its data, and the borrowed data might be not contiguous");
    else
        static_assert(false, "cannot get native data from array: not supported on this device");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::begin ( )
{
    if ( independent() ) [[likely]]
        return lower::begin();
    else
        return upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::begin ( ) const
{
    if ( independent() ) [[likely]]
        return lower::begin()
    else
        return upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::end ( )
{
    if ( independent() ) [[likely]]
        return lower::end();
    else
        return upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::end ( ) const
{
    if ( independent() ) [[likely]]
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

    if ( independent() ) [[likely]]
        return lower::operator[](pos);
    else
        return upper::operator[](pos);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim-1,device>& array<type,dim,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    if ( independent() ) [[likely]]
        return lower::operator[](pos);
    else
        return upper::operator[](pos);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template_int_axis
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int new_size )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( const array<int,1>& new_size )
{
    #if debug
    if ( new_size.size() != dimension() )
        throw value_error("cannot resize array: dimension mismatches (with from_dimension = {}, to_dimension = {})", dimension(), new_size.size());
    #endif

    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == dim )
{
    static_assert(false, "not coded yet");
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& array<type,dim,device>::clear ( )
{
    if ( independent() ) [[likely]]
    {
        vector::clear();
        info::clear();
        lower::clear();
    }
    else 
        upper::clear();

    return self;
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
    return static_cast<flat&>(self);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,1,device>& array<type,dim,device>::as_flat ( ) const
{
    return static_cast<const flat&>(self);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,1,device>& array<type,dim,device>::as_transpose ( )
{
    return lower::as_transpose();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,1,device>& array<type,dim,device>::as_transpose ( ) const
{
    return lower::as_transpose();
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr bool array<type,dim,device>::independent ( ) const
{
    return upper::independent();
}
