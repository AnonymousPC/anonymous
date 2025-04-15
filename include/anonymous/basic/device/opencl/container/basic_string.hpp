#pragma once

template < class type, class traits, class alloc >
class opencl::basic_string
    extends public boost::compute::basic_string<type,traits>
{
    private: // Typedef
        using base = boost::compute::basic_string<type,traits>;

    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;
        using iterator        = pointer;
        using const_iterator  = const_pointer;

    public: // Core
        basic_string ( ) = default;

    public: // Constructor
        using base::base;

        basic_string ( const_pointer init_data, int init_size )
        {
            as_vector().resize(init_size, opencl::execution_context.command_queue());
            boost::compute::copy(init_data, init_data + init_size, self.data(), opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
        }

    public: // Member  
        iterator begin ( )
        {
            return base::begin();
        }

        const_iterator begin ( ) const
        {
            return base::begin();
        }

        iterator end ( )
        {
            return base::end();
        }

        const_iterator end ( ) const
        {
            return base::end();
        }

        pointer data ( )
        {
            return base::begin();
        }

        const_pointer data ( ) const
        {
            return base::begin();
        }

        void resize ( int new_size )
        {
            as_vector().resize(new_size);
        }

        basic_string& append ( const_pointer new_data, int new_size )
        {
            let old_size = self.size();
            as_vector().resize(self.size() + new_size, opencl::execution_context.command_queue());
            boost::compute::copy(new_data, new_data + new_size, self.data() + old_size, opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return self;
        }

        basic_string& insert ( int new_pos, const_pointer new_data, int new_size )
        {
            as_vector().insert(self.data() + new_pos, new_data, new_data + new_size, opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return self;
        }

        basic_string& erase ( int old_pos, int old_count )
        {
            as_vector().erase(self.data() + old_pos, self.data() + old_pos + old_count, opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return self;
        }

    private: // Detail
        boost::compute::vector<type>& as_vector ( )
        {
            static_assert(layout_compatible_with<basic_string,boost::compute::vector<type>>, "fatal error: abi not compatible");
            return reinterpret_cast<boost::compute::vector<type>&>(self);
        }

        const boost::compute::vector<type>& as_vector ( ) const
        {
            static_assert(layout_compatible_with<basic_string,boost::compute::vector<type>>, "fatal error: abi not compatible");
            return reinterpret_cast<const boost::compute::vector<type>&>(self);
        }
};