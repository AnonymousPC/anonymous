#pragma once

template < class context_type >
asio_context<context_type>::asio_context ( )
    requires default_initializable<context_type>
    extends ctx_ptr ( std::make_shared<context_type>() )
{
    
}

template < class context_type >
asio_context<context_type>::asio_context ( context_type& ctx ) 
    extends ctx_ptr ( &ctx, [] (auto) { } )
{
    
}

template < class context_type >
asio_scheduler<context_type> asio_context<context_type>::get_scheduler ( ) noexcept
{
    return asio_scheduler<context_type>(*ctx_ptr);
}