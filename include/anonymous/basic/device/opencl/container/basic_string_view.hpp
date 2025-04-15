#pragma once

template < class type, class traits >
class opencl::basic_string_view
{
    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;
        using iterator        = pointer;
        using const_iterator  = const_pointer;

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
            return ptr_1;
        }

        const_iterator end ( ) const
        {
            return ptr_2;
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
