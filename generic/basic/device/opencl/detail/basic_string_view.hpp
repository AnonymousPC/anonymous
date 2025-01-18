#pragma once

template < class type, class traits >
class opencl::basic_string_view
{
    public: // Typedef
        using value_type      = type;
        using reference       =       boost::compute::detail::buffer_value<type>;
        using const_reference = const boost::compute::detail::buffer_value<type>;
        using pointer         =       boost::compute::detail::device_ptr<type>;
        using const_pointer   = const boost::compute::detail::device_ptr<type>;
        using iterator        =       boost::compute::buffer_iterator<type>;
        using const_iterator  = const boost::compute::buffer_iterator<type>;

    private: // Data
        const_pointer ptr_1 = const_pointer();
        const_pointer ptr_2 = const_pointer();

    public: // Core
        basic_string_view ( ) = default;

        basic_string_view ( const_pointer init_data, int init_size )
            extends ptr_1 ( init_data ),
                    ptr_2 ( init_data + init_size )
        {

        }

    public: // Member  
        int size ( ) const
        {
            return ptr_2 - ptr_1;
        }

        bool empty ( ) const
        {
            return ptr_1 == ptr_2;
        }

        const_iterator begin ( ) const
        {
            return const_iterator(ptr_1.get_buffer(), ptr_1.get_index());
        }

        const_iterator end ( ) const
        {
            return const_iterator(ptr_2.get_buffer(), ptr_2.get_index());
        }

        const_pointer data ( ) const
        {
            return ptr_1;
        }

        const_reference operator [] ( int pos ) const
        {
            return ptr_1[pos];
        }
};
