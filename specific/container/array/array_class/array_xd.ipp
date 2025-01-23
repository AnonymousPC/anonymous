#pragma once

template < class type, class device >
constexpr array<type,max_dim,device>::array ( const array& init )
    requires copyable<type>
{
    self.base ::operator=(static_cast<const base&>(init));
    self.info ::resize(init.static_shape());
    self.lower::resize(init.static_shape());
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( array&& init )
{
    self.base ::operator=(static_cast<base&&>(init));
    self.info ::resize(init.static_shape());
    self.lower::resize(init.static_shape());
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::operator = ( const array& right )
    requires copyable<type>
{
    self.base ::operator=(static_cast<const base&>(right));
    self.info ::resize(right.static_shape());
    self.lower::resize(right.static_shape());
    return self;
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::operator = ( array&& right )
{
    self.base ::operator=(static_cast<base&&>(right));
    self.info ::resize(right.static_shape());
    self.lower::resize(right.static_shape());
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
    device::generate(self.as_flat().begin(), self.as_flat().end(), last_value_of(args...));
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
    detail::device_generate_mdspan(last_value_of(args...), self.data());
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
{
    self.resize(cvt.static_shape());
    device::transform(cvt.::begin(), cvt.base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,max_dim,device>::array ( const array<type2,max_dim,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
{
    self.resize(cvt.static_shape());
    device::transform(cvt.as_flat().begin(), cvt.as_flat().end(), self.as_flat().begin(), [] (const auto& val) { return type2(val); });
}

template < class type, class device >
constexpr int array<type,max_dim,device>::dimension ( )
{
    return max_dim;
}

template < class type, class device >
constexpr int array<type,max_dim,device>::size ( ) const
{
    [[assume(base::size() == info::size())]];
    return info::size();
}

template < class type, class device >
constexpr array<int> array<type,max_dim,device>::shape ( ) const
{   
    return info::shape();
}

template < class type, class device >
constexpr inplace_array<int,max_dim> array<type,max_dim,device>::inplace_shape ( ) const
{
    return info::shape();
}

template < class type, class device >
constexpr static_array<int,max_dim> array<type,max_dim,device>::static_shape ( ) const
{
    return info::static_shape();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::row ( ) const
{
    return info::row();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::column ( ) const
    requires ( max_dim == 2 )
{
    return info::column();
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::empty ( ) const
{
    return info::empty();
}

template < class type, class device >
constexpr array<type,max_dim,device>::pointer array<type,max_dim,device>::data ( )
{
    return base::data();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_pointer array<type,max_dim,device>::data ( ) const
{
    return base::data();
}

template < class type, class device >
constexpr array<type,max_dim,device>::iterator array<type,max_dim,device>::begin ( )
{
    return lower::begin();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_iterator array<type,max_dim,device>::begin ( ) const
{
    return lower::begin();
}

template < class type, class device >
constexpr array<type,max_dim,device>::iterator array<type,max_dim,device>::end ( )
{
    return lower::end();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_iterator array<type,max_dim,device>::end ( ) const
{
    return lower::end();
}

template < class type, class device >
constexpr array<type,max_dim-1,device>& array<type,max_dim,device>::operator[] ( int pos )
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    return pos >= 0 ? lower::operator[](pos-1) otherwise
                      lower::operator[](pos+size());
}

template < class type, class device >
constexpr const array<type,max_dim-1,device>& array<type,max_dim,device>::operator[] ( int pos ) const
{
    #if debug
    if ( pos < -row() or pos == 0 or pos > row() )
        throw index_error("index {} is out of range with size {}", pos, row());
    #endif

    return pos >= 0 ? lower::operator[](pos-1) otherwise
                      lower::operator[](pos+size());
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::clear ( )
{
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
    if ( new_size < 0 )
        throw value_error("resize array with negative shape {} (on axis {})", new_size, axis);
    #endif
    
    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( const array<int,1>& new_size )
{
    #if debug
    if ( new_size.size() != dimension() )
        throw value_error("resize array with inconsistent dimension (with provided = {}, expected = {})", new_size.size(), dimension());
 // if ( new_size.any([] (int s) { return s < 0;}))
 //     throw value_error("resize array with negative shape {}", new_size);
    #endif

    static_assert(false, "not coded yet. the elements should be moved carefully");
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == max_dim )
{
    #if debug
    if ( not detail::check_first_until_last_as_positive(args...) )
        throw value_error("resize array with negative shape {}", static_array<int,max_dim>{args...});
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
constexpr array<type,1,device>& array<type,max_dim,device>::as_flat ( )
{
    return static_cast<flat&>(self);
}

template < class type, class device >
constexpr const array<type,1,device>& array<type,max_dim,device>::as_flat ( ) const
{
    return static_cast<const flat&>(self);
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::as_transpose ( )
{
    return lower::as_transpose();
}

template < class type, class device >
constexpr const array<type,max_dim,device>& array<type,max_dim,device>::as_transpose ( ) const
{
    return lower::as_transpose();
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::ownership ( )
{
    return true;
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::contiguous ( )
{
    return true;
}

template < class type, class device >
template < int dim2 >
constexpr std::vector<detail::array_upper<type,dim2,device>>& array<type,max_dim,device>::rows ( ) 
{
    return lower::template rows<dim2>();
}

template < class type, class device >
template < int dim2 >
constexpr const std::vector<detail::array_upper<type,dim2,device>>& array<type,max_dim,device>::rows ( ) const
{
    return lower::template rows<dim2>();
}

template < class type, class device >
template < int dim2 >
constexpr std::vector<detail::array_upper<type,dim2,device>>& array<type,max_dim,device>::columns ( ) 
{
    return lower::template columns<dim2>();
}

template < class type, class device >
template < int dim2 >
constexpr const std::vector<detail::array_upper<type,dim2,device>>& array<type,max_dim,device>::columns ( ) const
{
    return lower::template columns<dim2>();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::top_size ( ) const
{
    return size();
}

template < class type, class device >
constexpr array<type,max_dim,device>::reference array<type,max_dim,device>::at ( int_type auto... args )
    requires ( sizeof...(args) == max_dim )
{
    return std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type>(data(), static_cast<const std::array<int,max_dim>&>(static_shape()))[args...];
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_reference array<type,max_dim,device>::at ( int_type auto... args ) const
    requires ( sizeof...(args) == max_dim )
{
    return std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type>(data(), static_cast<const std::array<int,max_dim>&>(static_shape()))[args...];
}
