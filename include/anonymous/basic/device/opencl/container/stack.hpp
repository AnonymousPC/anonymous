#pragma once

template < class type, class alloc >
class opencl::stack
    extends public boost::compute::stack<type>
{
    private: // Typedef
        using base = boost::compute::stack<type>;

    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;

    public: // Override
        reference top ( )
        {
            return as_vector().back();
        }

        const_reference top ( ) const
        {
            return as_vector().back();
        } 

        type pop ( )       
        {
            auto poped = base::top();
            base::pop();
            return poped;
        } 

    private: // Detail
        boost::compute::vector<type>& as_vector ( )
        {
            static_assert(layout_compatible_with<stack,boost::compute::vector<type>>, "fatal error: abi not compatible");
            return reinterpret_cast<boost::compute::vector<type>&>(self);
        }

        const boost::compute::vector<type>& as_vector ( ) const
        {
            static_assert(layout_compatible_with<stack,boost::compute::vector<type>>, "fatal error: abi not compatible");
            return reinterpret_cast<const boost::compute::vector<type>&>(self);
        }                           
};