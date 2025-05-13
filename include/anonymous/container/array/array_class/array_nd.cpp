#include "detail/md_operation.cpp"

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( const array& init )
    requires copyable<type>
{
    if ( init.ownership() ) 
    {
        self.base ::operator=(static_cast<const base&>(init));
        self.info ::set_resize(init.info::get_shape());
        self.lower::set_resize(init.info::get_shape());
    }
    else // if ( not init.ownership() )
    {
        self.set_resize(init.upper::get_shape());
        if ( init.upper::contiguous() )
            device::copy(init.upper::data(), init.upper::data() + init.upper::size(), self.base::data());
        else
            device::copy(init.upper::begin(), init.upper::end(), self./*linewise*/begin());
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( array&& init )
{
    if ( init.ownership() ) 
    {
        self.base ::operator=(static_cast<base&&>(init));
        self.info ::set_resize(init.info::get_shape());
        self.lower::set_resize(init.info::get_shape());
    }
    else // if ( not init.owenrship() )
    {
        self.set_resize(init.upper::get_shape());
        if ( init.upper::contiguous() ) 
            device::move(init.upper::data(), init.upper::data() + init.upper::size(), self.base::data());
        else
            device::move(init.upper::begin(), init.upper::end(), self./*linewise*/begin());
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
        self.info ::set_resize(right.info::get_shape());
        self.lower::set_resize(right.info::get_shape());
    }
    else if ( self.ownership() and not right.ownership() )
    {
        self.set_resize(right.upper::get_shape());
        if ( right.upper::contiguous() ) 
            device::copy(right.upper::data(), right.upper::data() + right.upper::size(), self.base::data());
        else
            device::copy(right.upper::begin(), right.upper::end(), self./*linewise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        if constexpr ( debug )
            if ( self.shape() != right.shape() )
                throw value_error("cannot assign array (with left.ownership() = false, left.shape() = {}, right.shape() = {}): shape mismatches", self.shape(), right.shape());

        if ( self.upper::contiguous() )
            device::copy(right.base::data(), right.base::data() + right.base::size(), self.upper::data());
        else
            device::copy(right./*linewise*/begin(), right./*linewise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        if constexpr ( debug )
            if ( self.shape() != right.shape() )
                throw value_error("cannot assign array (with left.ownership() = false, left.shape() = {}, right.shape() = {}): shape mismatches", self.shape(), right.shape());

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
        self.info ::set_resize(right.info::get_shape());
        self.lower::set_resize(right.info::get_shape());
    }
    else if ( self.ownership() and not right.ownership() )
    {
        self.set_resize(right.upper::get_shape());
        if ( right.upper::contiguous() ) 
            device::move(right.upper::data(), right.upper::data() + right.upper::size(), self.base::data());
        else
            device::move(right.upper::begin(), right.upper::end(), self./*linewise*/begin());
    }
    else if ( not self.ownership() and right.ownership() )
    {
        if constexpr ( debug )
            if ( self.shape() != right.shape() )
                throw value_error("cannot assign array (with left.ownership() = false, left.shape() = {}, right.shape() = {}): shape mismatches", self.shape(), right.shape());

        if ( self.upper::contiguous() )
            device::move(right.base::data(), right.base::data() + right.base::size(), self.upper::data());
        else
            device::move(right./*linewise*/begin(), right./*linewise*/end(), self.upper::begin());
    }
    else // if ( not self.ownership() and not right.ownership() )
    {
        if constexpr ( debug )
            if ( self.shape() != right.shape() )
                throw value_error("cannot assign array (with left.ownership() = false, left.shape() = {}, right.shape() = {}): shape mismatches", self.shape(), right.shape());

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
{
    if constexpr ( debug )
        if ( ( ( args < 0 ) or ... ) )
            throw value_error("cannot initialize array (with shape() = {}): shape is negative", array<int>{args...});

    set_resize({args...});
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( auto... args )
    requires copyable<type> and
             ( sizeof...(args) - 1 == dim ) and 
             detail::ints_until_last_type<type,decltype(args)...>
{
    if constexpr ( debug )
        if ( any_of_constexpr<1,dim>([&] <int index> { return index_value_of<index>(args...) < 0; }) )
            throw value_error("cannot initialize array (with shape() = {}): shape is negative", [&] { auto shp = array<int>(dim); for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); }); return shp; } () );

    set_resize([&] { auto shp = detail::array_shape<dim>(); for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); }); return shp; } ());
    device::fill(self.base::begin(), self.base::end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_generator<type,decltype(args)...>
{
    if constexpr ( debug )
        if ( any_of_constexpr<1,dim>([&] <int index> { return index_value_of<index>(args...) < 0; }) )
            throw value_error("cannot initialize array (with shape() = {}): shape is negative", [&] { auto shp = array<int>(dim); for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); }); return shp; } () );

    set_resize([&] { auto shp = detail::array_shape<dim>(); for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); }); return shp; } ());
    device::generate(self.base::begin(), self.base::end(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( auto... args )
    requires ( sizeof...(args) - 1 == dim ) and
             detail::ints_until_last_function<type,decltype(args)...>
{
    if constexpr ( debug )
        if ( any_of_constexpr<1,dim>([&] <int index> { return index_value_of<index>(args...) < 0; }) )
            throw value_error("cannot initialize array (with shape() = {}): shape is negative", [&] { auto shp = array<int>(dim); for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); }); return shp; } () );

    set_resize([&] { auto shp = detail::array_shape<dim>(); for_constexpr<1,dim>([&] <int index> { shp[index] = index_value_of<index>(args...); }); return shp; } ());
    detail::md_generate(self, info::get_shape(), last_value_of(args...));
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::array ( std::initializer_list<array<type,dim-1,device>> init )
    requires copyable<type>
{
    auto shp = detail::array_shape<dim>();
    shp[1] = init.size();
    if ( init.size() != 0 )
    {
        if constexpr ( debug )
            if ( not std::ranges::all_of(init | std::views::adjacent<2>, [] (const auto& adj) { const auto& [a, b] = adj; return a.shape() == b.shape(); }) )
                throw value_error("cannot initialize array: shape is inhomogeneous");
        
        auto sub_shp = init.begin()->get_shape();
        for_constexpr<2,dim>([&] <int index> { shp[index] = sub_shp[index-1]; });
    }

    set_resize(shp);
    device::copy(init.begin(), init.end(), self./*linewise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < class type2, class device2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device2>& cvt )
    requires convertible_to<type2,type>
{    
    set_resize(cvt.get_shape());

    if constexpr ( same_as<type,type2> )
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                common_type<device,device2>::copy(cvt.array<type,dim,device2>::base::begin(), cvt.array<type,dim,device2>::base::end(), self.base::begin());
            else if ( cvt.contiguous() )
                common_type<device,device2>::copy(cvt.array<type,dim,device2>::upper::data(), cvt.array<type,dim,device2>::upper::data() + cvt.array<type,dim,device2>::upper::size(), self.base::data());
            else
                common_type<device,device2>::copy(cvt.array<type,dim,device2>::upper::begin(), cvt.array<type,dim,device2>::upper::end(), self./*linewise*/begin());
        else
            common_type<device,device2>::copy(cvt./*linewise*/begin(), cvt./*linewise*/end(), self./*linewise*/begin());
    else
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                common_type<device,device2>::transform(cvt.array<type2,dim,device>::base::begin(), cvt.array<type2,dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
            else if ( cvt.contiguous() )
                common_type<device,device2>::transform(cvt.array<type2,dim,device>::upper::data(), cvt.array<type2,dim,device>::upper::data() + cvt.array<type2,dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type(val); });
            else
                common_type<device,device2>::transform(cvt.array<type2,dim,device>::upper::begin(), cvt.array<type2,dim,device>::upper::end(), self./*linewise*/begin(), [] (const auto& line) { return array<type,dim-1,device>(line); });
        else
            common_type<device,device2>::copy(cvt./*linewise*/begin(), cvt./*linewise*/end(), self./*linewise*/begin());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < class type2, class device2 >
constexpr array<type,dim,device>::array ( const array<type2,dim,device2>& cvt )
    requires constructible_to<type2,type>
{    
    set_resize(cvt.get_shape());

    if constexpr ( same_as<type,type2> )
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                common_type<device,device2>::copy(cvt.array<type,dim,device2>::base::begin(), cvt.array<type,dim,device2>::base::end(), self.base::begin());
            else if ( cvt.contiguous() )
                common_type<device,device2>::copy(cvt.array<type,dim,device2>::upper::data(), cvt.array<type,dim,device2>::upper::data() + cvt.array<type,dim,device2>::upper::size(), self.base::data());
            else
                common_type<device,device2>::copy(cvt.array<type,dim,device2>::upper::begin(), cvt.array<type,dim,device2>::upper::end(), self./*linewise*/begin());
        else
            common_type<device,device2>::copy(cvt./*linewise*/begin(), cvt./*linewise*/end(), self./*linewise*/begin());
    else
        if constexpr ( same_as<typename device::layout_type,typename device2::layout_type> )
            if ( cvt.ownership() )
                common_type<device,device2>::transform(cvt.array<type2,dim,device>::base::begin(), cvt.array<type2,dim,device>::base::end(), self.base::begin(), [] (const auto& val) { return type(val); });
            else if ( cvt.contiguous() )
                common_type<device,device2>::transform(cvt.array<type2,dim,device>::upper::data(), cvt.array<type2,dim,device>::upper::data() + cvt.array<type2,dim,device>::upper::size(), self.base::data(), [] (const auto& val) { return type(val); });
            else
                common_type<device,device2>::transform(cvt.array<type2,dim,device>::upper::begin(), cvt.array<type2,dim,device>::upper::end(), self./*linewise*/begin(), [] (const auto& line) { return array<type,dim-1,device>(line); });
        else
            common_type<device,device2>::copy(cvt./*linewise*/begin(), cvt./*linewise*/end(), self./*linewise*/begin());
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
    [[assume(base::size() == info::size())]];
    return ownership() ? info::size() :
                         upper::size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<int> array<type,dim,device>::shape ( ) const
{   
    return ownership() ? info::shape() :
                         upper::shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::row ( ) const
    requires ( dim == 2 )
{
    return ownership() ? info::row() :
                         upper::row();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::column ( ) const
    requires ( dim == 2 )
{
    return ownership() ? info::column() :
                         upper::column();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool array<type,dim,device>::empty ( ) const
{
    [[assume(base::empty() == info::empty())]];
    return ownership() ? info::empty() :
                         upper::empty();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::data ( )
{
    return ownership()  ? base::data()  :
           contiguous() ? upper::data() :
                          throw logic_error("cannot get native data pointer (with ownership() = false): this array does not own its data, and the viewed data is not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::data ( ) const
{
    return ownership()  ? base::data()  :
           contiguous() ? upper::data() :
                          throw logic_error("cannot get native data pointer (with ownership() = false): this array does not own its data, and the viewed data is not contiguous");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::begin ( )
{
    return ownership() ? lower::begin() :
                         upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::begin ( ) const
{
    return ownership() ? lower::begin() :
                         upper::begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::iterator array<type,dim,device>::end ( )
{
    return ownership() ? lower::end() :
                         upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_iterator array<type,dim,device>::end ( ) const
{
    return ownership() ? lower::end() : 
                         upper::end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim-1,device>& array<type,dim,device>::operator [] ( int pos )
{
    if constexpr ( debug )
        if ( pos < -get_size_axis<1>() or pos == 0 or pos > get_size_axis<1>() ) // Do not use "pos < -shape()[1] or ...", as it might recursive into "shape()[1]" -> "1 < -shape_array.shape()[1] or ...".
            throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), 1);

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)                                  :
                                    lower::operator[](pos+info::template get_size_axis<1>())  :
                         pos >= 0 ? upper::operator[](pos-1)                                  :
                                    upper::operator[](pos+upper::template get_size_axis<1>());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,dim-1,device>& array<type,dim,device>::operator [] ( int pos ) const
{
    if constexpr ( debug )
        if ( pos < -get_size_axis<1>() or pos == 0 or pos > get_size_axis<1>() ) // Do not use "pos < -shape()[1] or ...", as it might recursive into "shape()[1]" -> "1 < -shape_array.shape()[1] or ...".
            throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), 1);

    return ownership() ? pos >= 0 ? lower::operator[](pos-1)                                  :
                                    lower::operator[](pos+info::template get_size_axis<1>())  :
                         pos >= 0 ? upper::operator[](pos-1)                                  :
                                    upper::operator[](pos+upper::template get_size_axis<1>());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::clear ( )
{
    if constexpr ( debug )
        if ( not ownership() ) 
            throw logic_error("cannot clear array (with ownership() = false): this array does not own its data");

    base ::clear();
    info ::clear();
    lower::clear();
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( int_type auto... args )
    requires ( sizeof...(args) == dim )
{
    if constexpr ( debug )
    {
        if ( not ownership() )
            throw logic_error("cannot resize array (with ownership() = false): this array does not own its data");
        if ( ( ( args < 0 ) or ... ) )
            throw value_error("cannot resize array (with resize.shape() = {}): shape is negative", array{args...});
    }

    set_resize({args...});
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::resize ( array<int> new_shape )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot resize array (with ownership() = false): this array does not own its data");
        if ( new_shape.size() != dim )
            throw value_error("cannot resize array (with dimension() = {}, resize.shape() = {}): dimension mismatches", self.dimension(), new_shape.size());
        if ( new_shape.exist([] (int s) { return s < 0; }))
            throw value_error("cannot resize array (with resize.shape() = {}): shape is negative", new_shape);
    }

    set_resize([&] { auto shp = detail::array_shape<dim>(); for_constexpr<1,dim>([&] <int index> { shp[index] = new_shape[index]; }); return shp; } ());
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::push ( array<type,dim-1,device> new_value )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot push into array (with ownership() = false): this array does not own its data");
        if ( self.shape().erase(axis) != new_value.shape() )
            throw value_error("cannot push into arary (with axis = {}, shape() = {}, push.shape() = {}): shape is inhomogeneous", axis, self.shape(), new_value.shape());
    }

    auto new_shape = get_shape();
    new_shape[axis] += 1;
    set_resize(new_shape);

    if constexpr ( axis == 1 or axis == -dim )
        self[-1] = std::move(new_value);
    else if constexpr ( axis == -1 or axis == dim )
        if constexpr ( new_value.dimension() == 1 )
            self.transpose()[-1] = std::move(new_value);
        else
            self.transpose()[-1] = std::move(new_value.transpose());
    else
        if constexpr ( axis > 0 )
            detail::md_push<device,axis>      (self, get_shape(), std::move(new_value));
        else
            detail::md_push<device,axis+dim+1>(self, get_shape(), std::move(new_value));
    
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::pop ( )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot pop from array (with ownership() = false): this array does not own its data");
        if ( empty() )
            throw value_error("cannot pop from array (with empty() = true)");
    }

    auto new_shape = get_shape();
    new_shape[axis] -= 1;
    set_resize(new_shape);
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::insert ( int new_pos, array<type,dim-1,device> new_value )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot insert into array (with ownership() = false): this array does not own its data");
        if ( new_pos < -shape()[axis] or new_pos == 0 or new_pos > shape()[axis] )
            throw index_error("index {} is out of range with shape {} axis = {}", new_pos, shape(), axis);
        if ( self.shape().erase(axis) != new_value.shape() )
            throw value_error("cannot insert into array (with axis = {}, shape() = {}, insert.shape() = {}): shape is inhomogeneous", axis, self.shape(), new_value.shape());
    }

    auto new_shape = get_shape();
    new_shape[axis] += 1;
    set_resize(new_shape);

    auto abs_pos = new_pos >= 0 ? new_pos : new_pos + get_size_axis<axis>() + 1;
    if constexpr ( axis == 1 or axis == -dim )
    {
        device::move_backward(self.begin() + abs_pos - 1, self.end() - 1, self.end());
        self[abs_pos] = std::move(new_value);
    }
    else if constexpr ( axis == -1 or axis == dim )
    {
        device::move_backward(self.transpose().begin() + abs_pos - 1, self.transpose().end() - 1, self.transpose().end());
        if constexpr ( new_value.dimension() == 1 )
            self.transpose()[abs_pos] = std::move(new_value);
        else
            self.transpose()[abs_pos] = std::move(new_value.transpose());
    }
    else
        if constexpr ( axis > 0 )
            detail::md_insert<device,axis>      (self, get_shape(), abs_pos, std::move(new_value));
        else
            detail::md_insert<device,axis+dim+1>(self, get_shape(), abs_pos, std::move(new_value));
    
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr array<type,dim,device>& array<type,dim,device>::erase ( int old_pos )
    requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) )
{
    if constexpr ( debug )
    {
        if ( not ownership() ) 
            throw logic_error("cannot erase from array (with ownership() = false): this array does not own its data");
        if ( old_pos < -shape()[axis] or old_pos == 0 or old_pos > shape()[axis] )
            throw index_error("index {} is out of range with shape {} axis {}", old_pos, shape(), axis);
    }

    auto new_shape = get_shape();
    new_shape[axis] -= 1;

    auto abs_pos = old_pos >= 0 ? old_pos : old_pos + get_size_axis<axis>() + 1;
    if constexpr ( axis == 1 or axis == -dim )
        device::move(self.begin() + abs_pos, self.end(), self.begin() + abs_pos - 1);
    else if constexpr ( axis == -1 or axis == dim )
        device::move(self.transpose().begin() + abs_pos, self.transpose().end(), self.transpose().begin() + abs_pos - 1);
    else
        if constexpr ( axis > 0 )
            detail::md_erase<device,axis>      (self, get_shape(), abs_pos);
        else 
            detail::md_erase<device,axis+dim+1>(self, get_shape(), abs_pos);

    set_resize(new_shape);
    return self;
}


template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,1,device>& array<type,dim,device>::flatten ( )
{
    return ownership() ? static_cast<array<type,1,device>&>(static_cast<base&>(self)) :
                         throw logic_error("cannot flatten array (with ownership() = false): this array does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,1,device>& array<type,dim,device>::flatten ( ) const
{
    return ownership() ? static_cast<const array<type,1,device>&>(static_cast<const base&>(self)) :
                         throw logic_error("cannot flatten array (with ownership() = false): this array does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>& array<type,dim,device>::transpose ( )
{
    return ownership()                                           ? lower::transpose() :
           upper::get_attribute() == detail::transpose_attribute ? upper::template get_host<detail::transpose_attribute>() :
                                                                   throw logic_error("cannot transpose array (with ownership() = false): this array does not own its data");
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,dim,device>& array<type,dim,device>::transpose ( ) const
{
    return ownership()                                           ? lower::transpose() :
           upper::get_attribute() == detail::transpose_attribute ? upper::template get_host<detail::transpose_attribute>() :
                                                                   throw logic_error("cannot transpose array (with ownership() = false): this array does not own its data");
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
constexpr auto array<type,dim,device>::mdspan ( )
{
    using type1 = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,                       typename device::template accessor_type<type>>;
    using type2 = std::mdspan<type,std::dextents<int,dim>,std::layout_stride,                                 typename device::template accessor_type<type>>;
    using type3 = std::mdspan<type,std::dextents<int,dim>,std::layout_transpose<typename device::layout_type>,typename device::template accessor_type<type>>;
    if ( contiguous() )
    {
        auto ptr = data();
        auto shp = std::dextents<int,dim>(get_shape());
        auto mds = type1(ptr, shp);
        return variant<type1,type2,type3>(mds);
    }
    else if ( upper::get_attribute() == detail::rows_attribute )  
    {
        auto ptr      = [&] <int... index> ( std::integer_sequence<int,index...> ) { return upper::get_pointer((index * 0)...); } ( std::make_integer_sequence<int,dim>() );
        auto shp      = std::dextents<int,dim>(get_shape());
        auto strd     = std::array   <int,dim>();
        auto map_base = typename device::layout_type::template mapping<std::dextents<int,dim>>(shp);
        for_constexpr<0,dim-1>([&] <int index> { strd[index] = map_base.stride(index) * upper::get_stride(); });
        auto mp       = typename type2::mapping_type(shp, strd);
        auto mds      = type2(ptr, mp);
        return variant<type1,type2,type3>(mds);   
    }
    else if ( upper::get_attribute() == detail::columns_attribute )  
    {
        auto ptr      = [&] <int... index> ( std::integer_sequence<int,index...> ) { return upper::get_pointer((index * 0)...); } ( std::make_integer_sequence<int,dim>() );
        auto shp      = std::dextents<int,dim>(get_shape());
        auto strd     = std::array   <int,dim>();
        auto map_base = typename std::layout_transpose<typename device::layout_type>::template mapping<std::dextents<int,dim>>(shp);
        for_constexpr<0,dim-1>([&] <int index> { strd[index] = map_base.stride(index) * upper::get_stride(); });
        auto mp      = typename type2::mapping_type(shp, strd);
        auto mds      = type2(ptr, mp);
        return variant<type1,type2,type3>(mds);   
    }
    else // if ( upper::get_attribute() == detail::transpose_attribute )
    {
        auto ptr = upper::template get_host<detail::transpose_attribute>().data();
        auto shp = std::dextents<int,dim>(get_shape());
        auto mds = type3(ptr, shp);
        return variant<type1,type2,type3>(mds);
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const auto array<type,dim,device>::mdspan ( ) const
{
    using type1 = std::mdspan<const type,std::dextents<int,dim>,typename device::layout_type,                       typename device::template accessor_type<const type>>;
    using type2 = std::mdspan<const type,std::dextents<int,dim>,std::layout_stride,                                 typename device::template accessor_type<const type>>;
    using type3 = std::mdspan<const type,std::dextents<int,dim>,std::layout_transpose<typename device::layout_type>,typename device::template accessor_type<const type>>;
    if ( contiguous() )
    {
        auto ptr = data();
        auto shp = std::dextents<int,dim>(get_shape());
        auto mds = type1(ptr, shp);
        return variant<type1,type2,type3>(mds);
    }
    else if ( upper::get_attribute() == detail::rows_attribute )  
    {
        auto ptr      = [&] <int... index> ( std::integer_sequence<int,index...> ) { return upper::get_pointer((index * 0)...); } ( std::make_integer_sequence<int,dim>() );
        auto shp      = std::dextents<int,dim>(get_shape());
        auto strd     = std::array   <int,dim>();
        auto map_base = typename device::layout_type::template mapping<std::dextents<int,dim>>(shp);
        for_constexpr<0,dim-1>([&] <int index> { strd[index] = map_base.stride(index) * upper::get_stride(); });
        auto mp       = typename type2::mapping_type(shp, strd);
        auto mds      = type2(ptr, mp);
        return variant<type1,type2,type3>(mds);   
    }
    else if ( upper::get_attribute() == detail::columns_attribute )  
    {
        auto ptr      = [&] <int... index> ( std::integer_sequence<int,index...> ) { return upper::get_pointer((index * 0)...); } ( std::make_integer_sequence<int,dim>() );
        auto shp      = std::dextents<int,dim>(get_shape());
        auto strd     = std::array   <int,dim>();
        auto map_base = typename std::layout_transpose<typename device::layout_type>::template mapping<std::dextents<int,dim>>(shp);
        for_constexpr<0,dim-1>([&] <int index> { strd[index] = map_base.stride(index) * upper::get_stride(); });
        auto mp       = typename type2::mapping_type(shp, strd);
        auto mds      = type2(ptr, mp);
        return variant<type1,type2,type3>(mds);   
    }
    else // if ( upper::get_attribute() == detail::transpose_attribute )
    {
        auto ptr = upper::template get_host<detail::transpose_attribute>().data();
        auto shp = std::dextents<int,dim>(get_shape());
        auto mds = type3(ptr, shp);
        return variant<type1,type2,type3>(mds);
    }
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int array<type,dim,device>::get_size_top ( ) const
{
    return ownership() ? info::size() :
                         upper::get_size_top();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr int array<type,dim,device>::get_size_axis ( ) const
{
    static_assert ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
    
    if constexpr ( axis >= 0 )
        return ownership() ? info ::template get_size_axis<axis>() :
                             upper::template get_size_axis<axis>();
    else
        return get_size_axis<axis+dim+1>();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_shape<dim> array<type,dim,device>::get_shape ( ) const
{
    return ownership() ? info::get_shape() :
                         upper::get_shape();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_rows ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) :
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_rows ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_rows<dim2>(offsets...) :
                         upper::template get_rows<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_columns ( int_type auto... offsets ) 
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) :
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> array<type,dim,device>::get_columns ( int_type auto... offsets) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return ownership() ? lower::template get_columns<dim2>(offsets...) :
                         upper::template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::reference array<type,dim,device>::get_value ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    return ownership() ? mdspan(base::data(), info::get_shape())[offsets...] :
                         upper::get_value(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_reference array<type,dim,device>::get_value ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<const type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<const type>>;
    return ownership() ? mdspan(base::data(), info::get_shape())[offsets...] :
                         upper::get_value(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::pointer array<type,dim,device>::get_pointer ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<type>>;
    return ownership() ? base::data() + mdspan(base::data(), info::get_shape()).mapping()(offsets...) :
                         upper::get_pointer(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim,device>::const_pointer array<type,dim,device>::get_pointer ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );
    using mdspan = std::mdspan<const type,std::dextents<int,dim>,typename device::layout_type,typename device::template accessor_type<const type>>;
    return ownership() ? base::data() + mdspan(base::data(), info::get_shape()).mapping()(offsets...) :
                         upper::get_pointer(offsets...);
}


template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr void array<type,dim,device>::set_resize ( detail::array_shape<dim> new_shape )
{
    auto [smaller_shape, smaller_size, smaller_resizable, smaller_relayoutable] = detail::md_common_smaller<device>(get_shape(), new_shape);
    if ( smaller_resizable )
    {
        if ( smaller_relayoutable )
            detail::md_relayout_strict_smaller(self, get_shape(), smaller_shape);
        base::resize(smaller_size);
    }

    auto [larger_shape, larger_size, larger_resizable, larger_relayoutable] = detail::md_common_larger<device>(get_shape(), new_shape);
    if ( larger_resizable )
    {
        base::resize(larger_size);
        if ( larger_relayoutable )
            detail::md_relayout_strict_larger(self, smaller_shape, larger_shape);
    }

    info ::set_resize(new_shape);
    lower::set_resize(new_shape);
}