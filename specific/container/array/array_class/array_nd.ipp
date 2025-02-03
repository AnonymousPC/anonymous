#pragma once


template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( const array& init )
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
        if ( init.upper::contiguous() )
            device::copy(init.upper::data(), init.upper::data() + init.upper::size(), self.base::data());
        else
            device::copy(init.upper::begin(), init.upper::end(), self./*line-wise*/begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( array&& init )
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
        if ( init.upper::contiguous() ) 
            device::move(init.upper::data(), init.upper::data() + init.upper::size(), self.base::data());
        else
            device::move(init.upper::begin(), init.upper::end(), self./*line-wise*/begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( const array& right )
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
        if ( right.upper::contiguous() ) 
            device::copy(right.upper::data(), right.upper::data() + right.upper::size(), self.base::data());
        else
            device::copy(right.upper::begin(), right.upper::end(), self./*line-wise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.info::shape() )
            throw value_error("copy assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        if ( self.upper::contiguous() )
            device::copy(right.base::data(), right.base::data() + right.base::size(), self.upper::data());
        else
            device::copy(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.upper::shape() )
            throw value_error("copy assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        if ( self.upper::contiguous() and right.upper::contiguous() ) 
            device::copy(right.upper::data(), right.upper::data() + right.upper::size(), self.upper::data());
        else
            device::copy(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::operator = ( array&& right )
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
        if ( right.upper::contiguous() ) 
            device::move(right.upper::data(), right.upper::data() + right.upper::size(), self.base::data());
        else
            device::move(right.upper::begin(), right.upper::end(), self./*line-wise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.info::shape() )
            throw value_error("move assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        if ( self.upper::contiguous() )
            device::move(right.base::data(), right.base::data() + right.base::size(), self.upper::data());
        else
            device::move(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #if debug
        if ( self.upper::shape() != right.upper::shape() )
            throw value_error("move assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        if ( self.upper::contiguous() and right.upper::contiguous() ) 
            device::move(right.upper::data(), right.upper::data() + right.upper::size(), self.upper::data());
        else
            device::move(right.upper::begin(), right.upper::end(), self.upper::begin());
    }

    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
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
    requires ( dim >= 2 and dim <= max_dim - 1 )
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
        throw value_error("initialize array with negative shape {}", shape());
    #endif
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func<type,decltype(args)...>
    extends base  ( detail::multiply_first_until_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
    device::generate(self.base::begin(), self.base::end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_func_ints<type,decltype(args)...>
    extends base  ( detail::multiply_first_to_second_last(args...) ),
            info  ( args... ),
            lower ( args... )
{
    #if debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
    detail::md_generate(self, shape(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( std::initializer_list<array<type,dim-1,device>> init )
    requires copyable<type>
{
    let shp = static_array<int,dim>();
    shp[1] = init.size();

    if ( init.size() != 0 )
    {
        #if debug
            if ( not std::ranges::all_of(init | std::views::adjacent<2>, [] (const auto& adj) { const auto& [a, b] = adj; return a.shape() == b.shape(); }) )
                throw value_error("initialize array with ambiguous shape (with initializer = {}, shape_list = {})", typeid(init), init | std::views::transform([] (const auto& subarr) { return subarr.shape(); }) | std::ranges::to<array<static_array<int,dim-1>>>());
        #endif
        let sub_shp = init.begin()[0].shape();
        detail::for_constexpr<2,dim>([&] <int index> { shp[index] = sub_shp[index-1]; });
        resize(shp);
        device::copy(init.begin(), init.end(), self./*line-wise*/begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends array ( cvt.shape() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,dim,device>::base::begin(), cvt.array<type2,dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
    else if ( cvt.contiguous() )
        device::transform(cvt.array<type2,dim,device>::upper::data(), cvt.array<type2,dim,device>::upper::data() + cvt.array<type2,dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type2(val); });
    else
        device::transform(cvt.array<type2,dim,device>::upper::begin(), cvt.array<type2,dim,device>::upper::end(), self./*line-wise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < class type2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.shape() )
{
    if ( cvt.ownership() )
        device::transform(cvt.array<type2,dim,device>::base::begin(), cvt.array<type2,dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type2(val); });
    else if ( cvt.contiguous() )
        device::transform(cvt.array<type2,dim,device>::upper::data(), cvt.array<type2,dim,device>::upper::data() + cvt.array<type2,dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type2(val); });
    else
        device::transform(cvt.array<type2,dim,device>::upper::begin(), cvt.array<type2,dim,device>::upper::end(), self./*line-wise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < class device2 >
constexpr array<type,dim,device>::array ( const array<type,dim,device2>& cvt )
    requires same_as<device,cpu> or same_as<device2,cpu>
    extends array ( cvt.shape() )
{
    static_assert(same_as<typename device ::layout_type,std::layout_right> or same_as<typename device ::layout_type,std::layout_left>);
    static_assert(same_as<typename device2::layout_type,std::layout_right> or same_as<typename device2::layout_type,std::layout_left>);

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
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::dimension ( )
{
    return dim;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::size ( ) const
{
    [[assume(int(base::size()) == info::size())]];
    return ownership() ? info::size() otherwise
                         upper::size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr static_array<int,dim> array<type,dim,device>::shape ( ) const
{   
    return ownership() ? info::shape() otherwise
                         upper::shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::row ( ) const
    requires ( dim == 2 )
{
    return ownership() ? info::row() otherwise
                         upper::row();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::column ( ) const
    requires ( dim == 2 )
{
    return ownership() ? info::column() otherwise
                         upper::column();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool array<type,dim,device>::empty ( ) const
{
    [[assume(base::empty() == info::empty())]];
    return ownership() ? info::empty() otherwise
                         upper::empty();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::data ( )
{
    return ownership()  ? base::data()  otherwise
           contiguous() ? upper::data() otherwise
                          throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::data ( ) const
{
    return ownership()  ? base::data()  otherwise
           contiguous() ? upper::data() otherwise
                          throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::begin ( )
{
    return ownership() ? lower::begin() otherwise
                         upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::begin ( ) const
{
    return ownership() ? lower::begin() otherwise
                         upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::end ( )
{
    return ownership() ? lower::end() otherwise
                         upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::end ( ) const
{
    return ownership() ? lower::end() otherwise 
                         upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim-1,device>& array<type,dim,device>::operator [] ( int pos )
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

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,dim-1,device>& array<type,dim,device>::operator [] ( int pos ) const
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

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
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
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == dim )
{
    return resize({args...});
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( static_array<int,dim> new_shape )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot resize array: it does not own its data");
 // if ( new_size.any([] (int s) { return s < 0;}))
 //     throw value_error("resize array with negative shape {}", new_shape);
    #endif

    let [smaller_shape, smaller_size, smaller_resizable, smaller_relayoutable] = detail::md_common_smaller<device>(shape(), new_shape);
    if ( smaller_resizable )
    {
        if ( smaller_relayoutable )
            detail::md_relayout_strict_smaller(self, shape(), smaller_shape);
        base::resize(smaller_size);
    }

    let [larger_shape, larger_size, larger_resizable, larger_relayoutable] = detail::md_common_larger<device>(shape(), new_shape);
    if ( larger_resizable )
    {
        base::resize(larger_size);
        if ( larger_relayoutable )
            detail::md_relayout_strict_larger(self, smaller_shape, larger_shape);
    }

    info ::resize(new_shape);
    lower::resize(new_shape);
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::push ( array<type,dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot push into array: it does not own its data");
 // if ( array<int>(self.shape()).pop(axis) != new_value.shape() ) TODO: turn array<int> into inplace_array<int>.
 //     throw value_error("push array with mismatched shape (with axis = {}, origin_shape = {}, pushed_shape = {})");
    #endif

    let new_shape = shape();
    new_shape[axis] += 1;
    resize(new_shape);

    if constexpr ( axis == 1 or axis == -dim )
        self[-1] = std::move(new_value);
    else if constexpr ( axis == -1 or axis == dim )
        if constexpr ( dim == 2 )
            self.transpose()[-1] = std::move(new_value);
        else
            self.transpose()[-1] = std::move(new_value.transpose());
    else
        if constexpr ( axis > 0 )
            detail::md_push<device,axis>      (self, shape(), std::move(new_value));
        else
            detail::md_push<device,axis+dim+1>(self, shape(), std::move(new_value));
    
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::pop ( int old_pos )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot pop from array: it does not own its data");
    if ( old_pos < -shape()[axis] or old_pos == 0 or old_pos > shape()[axis] )
        throw index_error("index {} is out of range with shape {} axis {}", old_pos, shape(), axis);
    #endif

    let abs_pos = old_pos >= 0 ? old_pos otherwise old_pos + shape()[axis] + 1;
    let new_shape = shape();
    new_shape[axis] -= 1;

    if constexpr ( axis == 1 or axis == -dim )
        device::move(self.begin() + abs_pos, self.end(), self.begin() + abs_pos - 1);
    else if constexpr ( axis == -1 or axis == dim )
        device::move(self.transpose().begin() + abs_pos, self.transpose().end(), self.transpose().begin() + abs_pos - 1);
    else
        if constexpr ( axis > 0 )
            detail::md_pop<device,axis>      (self, shape(), abs_pos);
        else 
            detail::md_pop<device,axis+dim+1>(self, shape(), abs_pos);

    resize(new_shape);
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::insert ( int new_pos, array<type,dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot insert into array: it does not own its data");
    if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
        throw index_error("index {} is out of range with shape {} axis = {}", new_pos, shape(), axis);
 // if ( array<int>(self.shape()).pop(axis) != new_value.shape() ) TODO: turn array<int> into inplace_array<int>.
 //     throw value_error("push array with mismatched shape (with axis = {}, origin_shape = {}, pushed_shape = {})");
    #endif

    let abs_pos = new_pos >= 0 ? new_pos otherwise new_pos + shape()[axis] + 1;
    let new_shape = shape();
    new_shape[axis] += 1;
    resize(new_shape);

    if constexpr ( axis == 1 or axis == -dim )
    {
        device::move_backward(self.begin() + abs_pos - 1, self.end() - 1, self.end());
        self[abs_pos] = std::move(new_value);
    }
    else if constexpr ( axis == -1 or axis == dim )
    {
        device::move_backward(self.transpose().begin() + abs_pos - 1, self.transpose().end() - 1, self.transpose().end());
        if constexpr ( dim == 2 )
            self.transpose()[abs_pos] = std::move(new_value);
        else
            self.transpose()[abs_pos] = std::move(new_value.transpose());
    }
    else
        if constexpr ( axis > 0 )
            detail::md_insert<device,axis>      (self, shape(), abs_pos, std::move(new_value));
        else
            detail::md_insert<device,axis+dim+1>(self, shape(), abs_pos, std::move(new_value));
    
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::erase ( int old_pos_1, int old_pos_2 )
    requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
{
    #if debug
    if ( not ownership() ) 
        throw logic_error("cannot erase from array: it does not own its data");
    #endif

    let abs_pos_1 = old_pos_1 >= 0 ? old_pos_1 otherwise old_pos_1 + shape()[axis] + 1;
    let abs_pos_2 = old_pos_2 >= 0 ? old_pos_2 otherwise old_pos_2 + shape()[axis] + 1;
    #if debug
    if ( ( ( abs_pos_1 < 1 or abs_pos_1 > shape()[axis] ) or
           ( abs_pos_2 < 1 or abs_pos_2 > shape()[axis] ) )
    and not // Except for below:
         ( ( abs_pos_1 == shape()[axis] + 1 or abs_pos_2 == 0 ) and abs_pos_1 == abs_pos_2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with shape {} axis {}", old_pos_1, old_pos_2, shape(), axis);
    #endif
    let new_shape = shape();
    new_shape[axis] -= (abs_pos_2 - abs_pos_1 + 1);

    if constexpr ( axis == 1 or axis == -dim )
        device::move(self.begin() + abs_pos_2, self.end(), self.begin() + abs_pos_1 - 1);
    else if constexpr ( axis == -1 or axis == dim )
        device::move(self.transpose().begin() + abs_pos_2, self.transpose().end(), self.transpose().begin() + abs_pos_1 - 1);
    else
        if constexpr ( axis > 0 )
            detail::md_erase<device,axis>      (self, shape(), abs_pos_1, abs_pos_2);
        else 
            detail::md_erase<device,axis+dim+1>(self, shape(), abs_pos_1, abs_pos_2);

    resize(new_shape);
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,1,device>& array<type,dim,device>::flatten ( )
{
    return ownership() ? static_cast<array<type,1,device>&>(static_cast<base&>(self)) otherwise
                         throw logic_error("cannot flatten array: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,1,device>& array<type,dim,device>::flatten ( ) const
{
    return ownership() ? static_cast<const array<type,1,device>&>(static_cast<const base&>(self)) otherwise
                         throw logic_error("cannot flatten array: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::transpose ( )
{
    return ownership()                                           ? lower::transpose()            otherwise
           upper::get_attribute() == detail::transpose_attribute ? upper::template get_host<2>() otherwise
                                                                   throw logic_error("cannot transpose array: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,dim,device>& array<type,dim,device>::transpose ( ) const
{
    return ownership()                                           ? lower::transpose()            otherwise
           upper::get_attribute() == detail::transpose_attribute ? upper::template get_host<2>() otherwise
                                                                   throw logic_error("cannot transpose array as_transpose: it does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool array<type,dim,device>::ownership ( ) const
{
    return upper::ownership();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool array<type,dim,device>::contiguous ( ) const
{
    return ownership() or upper::contiguous();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::get_size_top ( ) const
{
    return ownership() ? info::size() otherwise
                         upper::get_size_top();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr int array<type,dim,device>::get_size_axis ( ) const
{
    static_assert ( axis >= 1 and axis <= dim );
    return ownership() ? info ::template get_size_axis<axis>() otherwise
                         upper::template get_size_axis<axis>();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_rows ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) otherwise
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_rows ( int_type auto... offsets) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) otherwise
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_columns ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) otherwise
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_columns ( int_type auto... offsets) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) otherwise
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::reference array<type,dim,device>::get_value ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    return ownership() ? mdspan(base::data(), info::shape())[offsets...] otherwise
                         upper::get_value(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_reference array<type,dim,device>::get_value ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    if constexpr ( is_pointer<typename device::template pointer<type>> )
        return ownership() ? mdspan(const_cast<pointer>(base::data()), info::shape())[offsets...] otherwise
                             upper::get_value(offsets...);
    else
        return ownership() ? mdspan(static_cast<pointer>(base::data()), info::shape())[offsets...] otherwise
                             upper::get_value(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::get_pointer ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    return ownership() ? base::data() + mdspan(base::data(), info::shape()).mapping()(offsets...) otherwise
                         upper::get_pointer(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::get_pointer ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    if constexpr ( is_pointer<typename device::template pointer<type>> )
        return ownership() ? base::data() + mdspan(const_cast<pointer>(base::data()), info::shape()).mapping()(offsets...) otherwise
                             upper::get_pointer(offsets...);
    else
        return ownership() ? base::data() + mdspan(static_cast<pointer>(base::data()), info::shape()).mapping()(offsets...) otherwise
                             upper::get_pointer(offsets...);
}
