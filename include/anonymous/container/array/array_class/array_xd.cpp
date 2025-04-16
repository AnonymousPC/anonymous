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
        #ifdef debug
        if ( self.upper::shape() != right.info::shape() )
            throw value_error("copy assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        device::copy(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #ifdef debug
        if ( self.upper::shape() != right.upper::shape() )
            throw value_error("copy assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
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
        #ifdef debug
        if ( self.upper::shape() != right.info::shape() )
            throw value_error("move assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
        #endif
        device::move(right./*line-wise*/begin(), right./*line-wise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        #ifdef debug
        if ( self.upper::shape() != right.upper::shape() )
            throw value_error("move assign array with inconsistent shape (with left_ownership = false, left_shape = {}, right_shape = {})", self.shape(), right.shape());
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
    #ifdef debug
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
    #ifdef debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", shape());
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
    #ifdef debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", shape());
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
    #ifdef debug
    if ( not detail::check_first_until_second_last_as_positive(args...) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
    detail::md_generate(self, shape(), last_value_of(args...));
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( static_array<int,max_dim> init_shape )
    extends base  ( init_shape.product() ),
            info  ( init_shape ),
            lower ( init_shape )
{
    #ifdef debug
    if ( not init_shape.all([] (const auto& s) { return s >= 0; }) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( static_array<int,max_dim> init_shape, const type& init_value )
    requires copyable<type>
    extends base  ( init_shape.product(), init_value ),
            info  ( init_shape ),
            lower ( init_shape )
{
    #ifdef debug
    if ( not init_shape.all([] (const auto& s) { return s >= 0; }) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( static_array<int,max_dim> init_shape, function_type<type()> auto init_value )
    extends base  ( init_shape.product() ),
            info  ( init_shape ),
            lower ( init_shape )
{
    #ifdef debug
    if ( not init_shape.all([] (const auto& s) { return s >= 0; }) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
    device::generate(self.base::begin(), self.base::end(), init_value);
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( static_array<int,max_dim> init_shape, detail::invocable_r_by_n_ints<type,max_dim> auto init_value )
    extends base  ( init_shape.product() ),
            info  ( init_shape ),
            lower ( init_shape )
{
    #ifdef debug
    if ( not init_shape.all([] (const auto& s) { return s >= 0; }) )
        throw value_error("initialize array with negative shape {}", shape());
    #endif
    detail::md_generate(self, shape(), init_value);
}

template < class type, class device >
constexpr array<type,max_dim,device>::array ( std::initializer_list<array<type,max_dim-1,device>> init )
    requires copyable<type>
{
    auto shp = static_array<int,max_dim>();
    shp[1] = init.size();

    if ( init.size() != 0 )
    {
        #ifdef debug
            if ( not std::ranges::all_of(init | std::views::adjacent<2>, [] (const auto& adj) { const auto& [a, b] = adj; return a.shape() == b.shape(); }) )
                throw value_error("initialize array with ambiguous shape (with initializer = {}, shape_list = {})", typeid(init), init | std::views::transform([] (const auto& subarr) { return subarr.shape(); }) | std::ranges::to<array<static_array<int,max_dim-1>>>());
        #endif
        auto sub_shp = init.begin()[0].shape();
        detail::for_constexpr<2,max_dim>([&] <int index> { shp[index] = sub_shp[index-1]; });
        resize(shp);
        device::copy(init.begin(), init.end(), self./*line-wise*/begin());
    }
}

template < class type, class device >
template < class type2, class device2 >
constexpr array<type,max_dim,device>::array ( const array<type2,max_dim,device2>& cvt )
    requires ( same_as<type,type2> or same_as<device,device2> ) and
             convertible_to<type2,type> and
             ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> )
    extends array ( cvt.shape() )
{    
    if constexpr ( same_as<type,type2> )
        if constexpr ( same_as<device,device2> )
            /*copy constructor*/;
        else if constexpr ( same_as<device,cpu> )
            if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
                if ( cvt.ownership() )
                    device2::copy(cvt.array<type,max_dim,device2>::base::begin(), cvt.array<type,max_dim,device2>::base::end(), self.base::begin());
                else if ( cvt.contiguous() )
                    device2::copy(cvt.array<type,max_dim,device2>::upper::data(), cvt.array<type,max_dim,device2>::upper::data() + cvt.array<type,max_dim,device2>::upper::size(), self.base::data());
                else
                    device2::copy(cvt.array<type,max_dim,device2>::upper::begin(), cvt.array<type,max_dim,device2>::upper::end(), self./*line-wise*/begin());
            else
                device2::copy(cvt./*line-wise*/begin(), cvt./*line-wise*/end(), self./*line-wise*/begin());
        else
            if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
                if ( cvt.ownership() )
                    device::copy(cvt.array<type,max_dim,device2>::base::begin(), cvt.array<type,max_dim,device2>::base::end(), self.base::begin());
                else if ( cvt.contiguous() )
                    device::copy(cvt.array<type,max_dim,device2>::upper::data(), cvt.array<type,max_dim,device2>::upper::data() + cvt.array<type,max_dim,device2>::upper::size(), self.base::data());
                else
                    device::copy(cvt.array<type,max_dim,device2>::upper::begin(), cvt.array<type,max_dim,device2>::upper::end(), self./*line-wise*/begin());
            else
                device::copy(cvt./*line-wise*/begin(), cvt./*line-wise*/end(), self./*line-wise*/begin());
    else
        if ( cvt.ownership() )
            device::transform(cvt.array<type2,max_dim,device>::base::begin(), cvt.array<type2,max_dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
        else if ( cvt.contiguous() )
            device::transform(cvt.array<type2,max_dim,device>::upper::data(), cvt.array<type2,max_dim,device>::upper::data() + cvt.array<type2,max_dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type(val); });
        else
            device::transform(cvt.array<type2,max_dim,device>::upper::begin(), cvt.array<type2,max_dim,device>::upper::end(), self./*line-wise*/begin(), [] (const auto& line) { return array<type,max_dim-1,device>(line); });
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
    return ownership() ? info::size() :
                         upper::size();
}

template < class type, class device >
constexpr static_array<int,max_dim> array<type,max_dim,device>::shape ( ) const
{   
    return ownership() ? info::shape() :
                         upper::shape();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::row ( ) const
    requires ( max_dim == 2 )
{
    return ownership() ? info::row() :
                         upper::row();
}

template < class type, class device >
constexpr int array<type,max_dim,device>::column ( ) const
    requires ( max_dim == 2 )
{
    return ownership() ? info::column() :
                         upper::column();
}

template < class type, class device >
constexpr bool array<type,max_dim,device>::empty ( ) const
{
    [[assume(base::empty() == info::empty())]];
    return ownership() ? info::empty() :
                         upper::empty();
}

template < class type, class device >
constexpr array<type,max_dim,device>::pointer array<type,max_dim,device>::data ( )
{
    return ownership() ? base::data() :
                         throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_pointer array<type,max_dim,device>::data ( ) const
{
    return ownership() ? base::data() :
                         throw logic_error("cannot get native data from array: it does not own its data, meanwhile the borrowed data is not contiguous");
}

template < class type, class device >
constexpr array<type,max_dim,device>::iterator array<type,max_dim,device>::begin ( )
{
    return ownership() ? lower::begin() :
                         upper::begin();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_iterator array<type,max_dim,device>::begin ( ) const
{
    return ownership() ? lower::begin() :
                         upper::begin();
}

template < class type, class device >
constexpr array<type,max_dim,device>::iterator array<type,max_dim,device>::end ( )
{
    return ownership() ? lower::end() :
                         upper::end();
}

template < class type, class device >
constexpr array<type,max_dim,device>::const_iterator array<type,max_dim,device>::end ( ) const
{
    return ownership() ? lower::end() :
                         upper::end();
}

template < class type, class device >
constexpr array<type,max_dim-1,device>& array<type,max_dim,device>::operator [] ( int pos )
{
    #ifdef debug
    if ( pos < -get_size_axis<1>() or pos == 0 or pos > get_size_axis<1>() )
        throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), 1);
    #endif

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)                                  :
                                    lower::operator[](pos+info::template get_size_axis<1>())  :
                         pos >= 0 ? upper::operator[](pos-1)                                  :
                                    upper::operator[](pos+upper::template get_size_axis<1>());
}

template < class type, class device >
constexpr const array<type,max_dim-1,device>& array<type,max_dim,device>::operator [] ( int pos ) const
{
    #ifdef debug
    if ( pos < -get_size_axis<1>() or pos == 0 or pos > get_size_axis<1>() )
        throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), 1);
    #endif

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)                                  :
                                    lower::operator[](pos+info::template get_size_axis<1>())  :
                         pos >= 0 ? upper::operator[](pos-1)                                  :
                                    upper::operator[](pos+upper::template get_size_axis<1>());
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::clear ( )
{
    #ifdef debug
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
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == max_dim )
{
    return resize({args...});
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::resize ( static_array<int,max_dim> new_shape )
{
    #ifdef debug
    if ( not ownership() ) 
        throw logic_error("cannot resize array: it does not own its data");
 // if ( new_size.any([] (int s) { return s < 0;}))
 //     throw value_error("resize array with negative shape {}", new_shape);
    #endif

    auto [smaller_shape, smaller_size, smaller_resizable, smaller_relayoutable] = detail::md_common_smaller<device>(shape(), new_shape);
    if ( smaller_resizable )
    {
        if ( smaller_relayoutable )
            detail::md_relayout_strict_smaller(self, shape(), smaller_shape);
        base::resize(smaller_size);
    }

    auto [larger_shape, larger_size, larger_resizable, larger_relayoutable] = detail::md_common_larger<device>(shape(), new_shape);
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

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::push ( array<type,max_dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    #ifdef debug
    if ( not ownership() ) 
        throw logic_error("cannot push into array: it does not own its data");
 // if ( array<int>(self.shape()).pop(axis) != new_value.shape() ) TODO: turn array<int> into inplace_array<int>.
 //     throw value_error("push array with mismatched shape (with axis = {}, origin_shape = {}, pushed_shape = {})");
    #endif

    auto new_shape = shape();
    new_shape[axis] += 1;
    resize(new_shape);

    if constexpr ( axis == 1 or axis == -max_dim )
        self[-1] = std::move(new_value);
    else if constexpr ( axis == -1 or axis == max_dim )
        if constexpr ( max_dim == 2 )
            self.transpose()[-1] = std::move(new_value);
        else
            self.transpose()[-1] = std::move(new_value.transpose());
    else
        if constexpr ( axis > 0 )
            detail::md_push<device,axis>          (self, shape(), std::move(new_value));
        else
            detail::md_push<device,axis+max_dim+1>(self, shape(), std::move(new_value));
    
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::pop ( int old_pos )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    #ifdef debug
    if ( not ownership() ) 
        throw logic_error("cannot pop from array: it does not own its data");
    if ( old_pos < -shape()[axis] or old_pos == 0 or old_pos > shape()[axis] )
        throw index_error("index {} is out of range with shape {} axis {}", old_pos, shape(), axis);
    #endif

    auto abs_pos = old_pos >= 0 ? old_pos : old_pos + shape()[axis] + 1;
    auto new_shape = shape();
    new_shape[axis] -= 1;

    if constexpr ( axis == 1 or axis == -max_dim )
        device::move(self.begin() + abs_pos, self.end(), self.begin() + abs_pos - 1);
    else if constexpr ( axis == -1 or axis == max_dim )
        device::move(self.transpose().begin() + abs_pos, self.transpose().end(), self.transpose().begin() + abs_pos - 1);
    else
        if constexpr ( axis > 0 )
            detail::md_pop<device,axis>          (self, shape(), abs_pos);
        else 
            detail::md_pop<device,axis+max_dim+1>(self, shape(), abs_pos);

    resize(new_shape);
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::insert ( int new_pos, array<type,max_dim-1,device> new_value )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    #ifdef debug
    if ( not ownership() ) 
        throw logic_error("cannot insert into array: it does not own its data");
    if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
        throw index_error("index {} is out of range with shape {} axis = {}", new_pos, shape(), axis);
 // if ( array<int>(self.shape()).pop(axis) != new_value.shape() ) TODO: turn array<int> into inplace_array<int>.
 //     throw value_error("push array with mismatched shape (with axis = {}, origin_shape = {}, pushed_shape = {})");
    #endif

    auto abs_pos = new_pos >= 0 ? new_pos : new_pos + shape()[axis] + 1;
    auto new_shape = shape();
    new_shape[axis] += 1;
    resize(new_shape);

    if constexpr ( axis == 1 or axis == -max_dim )
    {
        device::move_backward(self.begin() + abs_pos - 1, self.end() - 1, self.end());
        self[abs_pos] = std::move(new_value);
    }
    else if constexpr ( axis == -1 or axis == max_dim )
    {
        device::move_backward(self.transpose().begin() + abs_pos - 1, self.transpose().end() - 1, self.transpose().end());
        if constexpr ( max_dim == 2 )
            self.transpose()[abs_pos] = std::move(new_value);
        else
            self.transpose()[abs_pos] = std::move(new_value.transpose());
    }
    else
        if constexpr ( axis > 0 )
            detail::md_insert<device,axis>          (self, shape(), abs_pos, std::move(new_value));
        else
            detail::md_insert<device,axis+max_dim+1>(self, shape(), abs_pos, std::move(new_value));
    
    return self;
}

template < class type, class device >
template < int axis >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::erase ( int old_pos_1, int old_pos_2 )
    requires ( ( axis >= 1 and axis <= max_dim ) or ( axis >= -max_dim and axis <= -1 ) )
{
    #ifdef debug
    if ( not ownership() ) 
        throw logic_error("cannot erase from array: it does not own its data");
    #endif

    auto abs_pos_1 = old_pos_1 >= 0 ? old_pos_1 : old_pos_1 + shape()[axis] + 1;
    auto abs_pos_2 = old_pos_2 >= 0 ? old_pos_2 : old_pos_2 + shape()[axis] + 1;
    #ifdef debug
    if ( ( ( abs_pos_1 < 1 or abs_pos_1 > shape()[axis] ) or
           ( abs_pos_2 < 1 or abs_pos_2 > shape()[axis] ) )
    and not // Except for below:
         ( ( abs_pos_1 == shape()[axis] + 1 or abs_pos_2 == 0 ) and abs_pos_1 == abs_pos_2 + 1 ) )
        throw index_error("index [{}, {}] is out of range with shape {} axis {}", old_pos_1, old_pos_2, shape(), axis);
    #endif
    auto new_shape = shape();
    new_shape[axis] -= (abs_pos_2 - abs_pos_1 + 1);

    if constexpr ( axis == 1 or axis == -max_dim )
        device::move(self.begin() + abs_pos_2, self.end(), self.begin() + abs_pos_1 - 1);
    else if constexpr ( axis == -1 or axis == max_dim )
        device::move(self.transpose().begin() + abs_pos_2, self.transpose().end(), self.transpose().begin() + abs_pos_1 - 1);
    else
        if constexpr ( axis > 0 )
            detail::md_erase<device,axis>          (self, shape(), abs_pos_1, abs_pos_2);
        else 
            detail::md_erase<device,axis+max_dim+1>(self, shape(), abs_pos_1, abs_pos_2);

    resize(new_shape);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,max_dim,device>::flatten ( )
{
    return ownership() ? static_cast<array<type,1,device>&>(static_cast<base&>(self)) :
                         throw logic_error("cannot flatten array: it does not own its data");
}

template < class type, class device >
constexpr const array<type,1,device>& array<type,max_dim,device>::flatten ( ) const
{
    return ownership() ? static_cast<const array<type,1,device>&>(static_cast<const base&>(self)) :
                         throw logic_error("cannot flatten array: it does not own its data");
}

template < class type, class device >
constexpr array<type,max_dim,device>& array<type,max_dim,device>::transpose ( )
{
    return ownership() ? lower::transpose() :
                         upper::get_host();
}

template < class type, class device >
constexpr const array<type,max_dim,device>& array<type,max_dim,device>::transpose ( ) const
{
    return ownership() ? lower::transpose() :
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
constexpr auto array<type,max_dim,device>::mdspan ( )
{
    using type1 = std::mdspan<type,std::dextents<int,max_dim>,typename device::layout_type,                       typename device::template accessor_type<type>>;
    using type2 = std::mdspan<type,std::dextents<int,max_dim>,std::layout_transpose<typename device::layout_type>,typename device::template accessor_type<type>>;
    if ( contiguous() )
    {
        auto ptr = data();
        auto shp = std::dextents<int,max_dim>(shape());
        auto mds = type1(ptr, shp);
        return variant<type1,type2>(mds);
    }
    else // if ( upper::attriande() == detail::transpose_attriande )
    {
        auto ptr = upper::get_host().data();
        auto shp = std::dextents<int,max_dim>(shape());
        auto mds = type2(ptr, shp);
        return variant<type1,type2>(mds);
    }
}

template < class type, class device >
constexpr const auto array<type,max_dim,device>::mdspan ( ) const
{
    using type1 = std::mdspan<const type,std::dextents<int,max_dim>,typename device::layout_type,                       typename device::template accessor_type<const type>>;
    using type2 = std::mdspan<const type,std::dextents<int,max_dim>,std::layout_transpose<typename device::layout_type>,typename device::template accessor_type<const type>>;
    if ( contiguous() )
    {
        auto ptr = data();
        auto shp = std::dextents<int,max_dim>(shape());
        auto mds = type1(ptr, shp);
        return variant<type1,type2>(mds);
    }
    else // if ( upper::attriande() == detail::transpose_attriande )
    {
        auto ptr = upper::get_host().data();
        auto shp = std::dextents<int,max_dim>(shape());
        auto mds = type2(ptr, shp);
        return variant<type1,type2>(mds);
    }
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
    return ownership() ? info ::template get_size_axis<axis>() :
                         upper::template get_size_axis<axis>();
}

template < class type, class device >
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_rows ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) :
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_rows ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) :
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_columns ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) :
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,max_dim,device>::get_columns ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) :
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
    using mdspan = std::mdspan<const type,std::dextents<int,max_dim>,typename device::layout_type,typename device::template accessor_type<const type>>;
    [[assume(ownership())]];
    return mdspan(base::data(), info::shape())[offsets...];
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
    using mdspan = std::mdspan<const type,std::dextents<int,max_dim>,typename device::layout_type,typename device::template accessor_type<const type>>;
    [[assume(ownership())]];
    return base::data() + mdspan(base::data(), info::shape()).mapping()(offsets...);
}
