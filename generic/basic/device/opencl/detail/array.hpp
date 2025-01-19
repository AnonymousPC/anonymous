#pragma once

template < class type, int len >
class opencl::array 
    extends public boost::compute::array<type,len>
{
    public: // Core
        array ( ) = default;

        array ( const array& init )
        {
            boost::compute::copy(init.begin(), init.end(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        array& operator = ( const array& right )
        {
            boost::compute::copy(right.begin(), right.end(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return self;
        }
};