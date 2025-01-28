#pragma once

template < class type, class alloc >
class opencl::vector
    extends public boost::compute::vector<type,alloc>
{
    private: // Typedef
        using base = boost::compute::vector<type,alloc>;

    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;
        using iterator        = base::iterator;
        using const_iterator  = base::const_iterator;

    public: // Override
        pointer data ( )
        {
            return pointer(self.begin().get_buffer(), self.begin().get_index());
        }

        const_pointer data ( ) const
        {
            return const_pointer(self.begin().get_buffer(), self.begin().get_index());
        }
};