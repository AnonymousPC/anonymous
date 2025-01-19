#pragma once

template < class type, class traits, class alloc >
class opencl::basic_string
    extends public boost::compute::basic_string<type,traits>
{
    private: // Typedef
        using base = boost::compute::basic_string<type,traits>;

    public: // Typedef
        using value_type      = type;
        using reference       =       boost::compute::detail::buffer_value<type>;
        using const_reference = const boost::compute::detail::buffer_value<type>;
        using pointer         =       boost::compute::detail::device_ptr<type>;
        using const_pointer   = const boost::compute::detail::device_ptr<type>;
        using iterator        =       boost::compute::buffer_iterator<type>;
        using const_iterator  = const boost::compute::buffer_iterator<type>;

    public: // Core
        basic_string ( ) = default;
        
        basic_string ( const basic_string& init )
            extends base ( init.size() )
        {
            boost::compute::copy(init.begin(), init.end(), self.begin(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        basic_string ( basic_string&& init )
        {
            self = std::move(init);
        }

        basic_string& operator = ( const basic_string& right )
        {
            base::resize(right.size(), execution_context.get_command_queue());
            boost::compute::copy(right.begin(), right.end(), self.begin(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return self;
        }

        basic_string& operator = ( basic_string&& right )
        {
            self.as_vector() = std::move(right.as_vector());
            return self;
        }

    public: // Constructor
        using base::base;

        basic_string ( const_pointer init_data, int init_size )
        {
            as_vector().resize(init_size, execution_context.get_command_queue());
            boost::compute::copy(init_data, init_data + init_size, self.data(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

    public: // Member  
        pointer data ( )
        {
            return pointer(self.begin().get_buffer(), self.begin().get_index());
        }

        const_pointer data ( ) const
        {
            return const_pointer(self.begin().get_buffer(), self.begin().get_index());
        }

        void resize ( int new_size )
        {
            as_vector().resize(new_size, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        basic_string& erase ( int old_pos, int old_count )
        {
            as_vector().erase(self.begin() + old_pos, self.begin() + old_pos + old_count, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return self;
        }
        
        basic_string& insert ( int new_pos, const_pointer new_data, int new_size )
        {
            as_vector().insert(self.begin() + new_pos, new_data, new_data + new_size, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return self;
        }

        basic_string& append ( const_pointer new_data, int new_size )
        {
            let old_size = self.size();
            as_vector().resize(self.size() + new_size, execution_context.get_command_queue());
            boost::compute::copy(new_data, new_data + new_size, self.begin() + old_size, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return self;
        }

    private: // Detail
        boost::compute::vector<type>& as_vector ( )
        {
            static_assert(sizeof(self) == sizeof(boost::compute::vector<type>), "fatal error: abi not compatible");
            return reinterpret_cast<boost::compute::vector<type>&>(self);
        }

        const boost::compute::vector<type>& as_vector ( ) const
        {
            static_assert(sizeof(self) == sizeof(boost::compute::vector<type>), "fatal error: abi not compatible");
            return reinterpret_cast<const boost::compute::vector<type>&>(self);
        }
};