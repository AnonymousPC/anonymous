template < class base >
detail::opencl_container<base>::opencl_container ( )
    extends base ( opencl::execution_context.context() )
{
    
}

template < class base >
detail::opencl_container<base>::opencl_container ( const opencl_container& init )
    extends base ( opencl::execution_context.command_queue() )
{
    self.as_vector().resize(init.size(), opencl::execution_context.command_queue());
    boost::compute::copy(init.begin(), init.end(), self.begin(), opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
}

template < class base >
detail::opencl_container<base>::opencl_container ( opencl_container&& init )
    extends base ( opencl::execution_context.command_queue() )
{
    self.as_vector() = std::move(init.as_vector());
}

template < class base >
detail::opencl_container<base>& detail::opencl_container<base>::operator = ( const opencl_container& right )
{
    as_vector().resize(right.size(), opencl::execution_context.command_queue());
    boost::compute::copy(right.begin(), right.end(), self.begin(), opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return self;
}

template < class base >
detail::opencl_container<base>& detail::opencl_container<base>::operator = ( opencl_container&& right )
{
    self.as_vector() = std::move(right.as_vector());
    return self;
}

template < class base >
detail::opencl_container<base>::opencl_container ( auto&&... args )
    requires constructible_from<base,decltype(args)...,const boost::compute::context&>
    extends base ( std::forward<decltype(args)>(args)..., opencl::execution_context.context() )
{
    opencl::execution_context.command_queue().finish();
}

template < class base >
detail::opencl_container<base>::opencl_container ( auto&&... args )
    requires ( not constructible_from<base,decltype(args)...,const boost::compute::context&> ) and
             constructible_from<base,decltype(args)...,boost::compute::command_queue&>
    extends base ( std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue() )
{
    opencl::execution_context.command_queue().finish();
}

template < class base >
detail::opencl_container<base>::iterator detail::opencl_container<base>::begin ( )
{
    return base::begin();
}

template < class base >
detail::opencl_container<base>::const_iterator detail::opencl_container<base>::begin ( ) const
{
    return base::begin();
}

template < class base >
detail::opencl_container<base>::iterator detail::opencl_container<base>::end ( )
{
    return base::end();
}

template < class base >
detail::opencl_container<base>::const_iterator detail::opencl_container<base>::end ( ) const
{
    return base::end();
}

template < class base >
detail::opencl_container<base>::pointer detail::opencl_container<base>::data ( )
{
    return base::begin();
}

template < class base >
detail::opencl_container<base>::const_pointer detail::opencl_container<base>::data ( ) const
{
    return base::begin();
}

template < class base >
detail::opencl_container<base>::reference detail::opencl_container<base>::front ( )
{
    return base::front();
}

template < class base >
detail::opencl_container<base>::const_reference detail::opencl_container<base>::front ( ) const
{
    return base::front();
}

template < class base >
detail::opencl_container<base>::reference detail::opencl_container<base>::back ( )
{
    return base::back();
}

template < class base >
detail::opencl_container<base>::const_reference detail::opencl_container<base>::back ( ) const
{
    return base::back();
}

template < class base >
detail::opencl_container<base>::reference detail::opencl_container<base>::operator [] ( auto&&... args )
{
    return base::operator[](std::forward<decltype(args)>(args)...);
}

template < class base >
detail::opencl_container<base>::const_reference detail::opencl_container<base>::operator [] ( auto&&... args ) const
{
    return base::operator[](std::forward<decltype(args)>(args)...);
}

template < class base >
detail::opencl_container<base>::iterator detail::opencl_container<base>::find ( auto&&... args )
{
    auto result = base::find(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
detail::opencl_container<base>::const_iterator detail::opencl_container<base>::find ( auto&&... args ) const
{
    auto result = base::find(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
std::size_t detail::opencl_container<base>::count ( auto&&... args ) const
{
    auto result = base::count(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
void detail::opencl_container<base>::resize ( auto&&... args )
{
    base::resize(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
}

template < class base >
void detail::opencl_container<base>::reserve ( auto&&... args )
{
    base::reserve(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
}

template < class base >
void detail::opencl_container<base>::shrink_to_fit ( auto&&... args )
{
    base::shrink_to_fit(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
}

template < class base >
void detail::opencl_container<base>::clear ( auto&&... args )
{
    base::clear(std::forward<decltype(args)>(args)...);
}

template < class base >
void detail::opencl_container<base>::push_back ( auto&&... args )
{
    base::push_back(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
}

template < class base >
void detail::opencl_container<base>::pop_back ( auto&&... args )
{
    base::pop_back(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue()); 
    opencl::execution_context.command_queue().finish();
}

template < class base >
auto detail::opencl_container<base>::insert ( auto&&... args )
{
    auto result = base::insert(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    
    if constexpr ( same_as<decltype(result),typename base::iterator> )
        return iterator(result);
    else if constexpr ( same_as<decltype(result),std::pair<typename base::iterator,bool>> )
        return std::pair<iterator,bool>(result.first, result.second);
    else
        return result;
}

template < class base >
auto detail::opencl_container<base>::erase ( auto&&... args )
{
    auto result = base::erase(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    
    if constexpr ( same_as<decltype(result),typename base::iterator> )
        return iterator(result);
    else if constexpr ( same_as<decltype(result),std::size_t> )
        return size_t(result);
    else
        return result;
}

template < class base >
detail::opencl_container<base>::iterator detail::opencl_container<base>::lower_bound ( auto&&... args )
{
    auto result = base::lower_bound(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
detail::opencl_container<base>::const_iterator detail::opencl_container<base>::lower_bound ( auto&&... args ) const
{
    auto result = base::lower_bound(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
detail::opencl_container<base>::iterator detail::opencl_container<base>::upper_bound ( auto&&... args )
{
    auto result = base::upper_bound(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
detail::opencl_container<base>::const_iterator detail::opencl_container<base>::upper_bound ( auto&&... args ) const
{
    auto result = base::upper_bound(std::forward<decltype(args)>(args)..., opencl::execution_context.command_queue());
    opencl::execution_context.command_queue().finish();
    return result;
}

template < class base >
detail::opencl_container<base>::reference detail::opencl_container<base>::top ( )
{
    return base::top();
}

template < class base >
detail::opencl_container<base>::const_reference detail::opencl_container<base>::top ( ) const
{
    return base::top();
}

template < class base >
void detail::opencl_container<base>::pop ( )
{
    base::pop();
}

template < class base >
boost::compute::vector<typename detail::opencl_container<base>::value_type>& detail::opencl_container<base>::as_vector ( )
{
    return reinterpret_cast<boost::compute::vector<value_type>&>(self);
}

template < class base >
const boost::compute::vector<typename detail::opencl_container<base>::value_type>& detail::opencl_container<base>::as_vector ( ) const
{
    return reinterpret_cast<const boost::compute::vector<value_type>&>(self);
}