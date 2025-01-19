#pragma once

template < class type, class alloc >
class opencl::vector
    extends public boost::compute::vector<type,alloc>
{
    private: // Typedef
        using base = boost::compute::vector<type,alloc>;

    public: // Core
        vector ( ) = default;

        vector ( const vector& init )
            extends base ( init.size() )
        {
            boost::compute::copy(init.begin(), init.end(), begin(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        vector ( vector&& ) = default;

        vector& operator = ( const vector& right )
        {
            base::resize(right.size(), execution_context.get_command_queue());
            boost::compute::copy(right.begin(), right.end(), begin(), execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return self;
        }

        vector& operator = ( vector&& ) = default;

    public: // Consturctor
        using base::base;

        vector ( auto&&... args )
            requires constructible_from<base,decltype(args)...,boost::compute::command_queue&>
            extends base ( std::forward<decltype(args)>(args)..., execution_context.get_command_queue() )
        {
            execution_context.get_command_queue().finish();
        }

    public: // Member
        void resize ( int new_size )
        {
            base::resize(new_size, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        void push_back ( const type& new_value )
        {
            base::push_back(new_value, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        void pop_back ( )
        {
            base::pop_back(execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
        }

        iterator insert ( iterator new_pos, const type& new_value )
        {
            let it = base::insert(new_pos, new_value, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return it;
        }

        iterator erase ( iterator old_pos )
        {
            let it = base::erase(old_pos, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return it;
        }

        iterator erase ( iterator old_pos_1, iterator old_pos_2 )
        {
            let it = base::erase(old_pos_1, old_pos_2, execution_context.get_command_queue());
            execution_context.get_command_queue().finish();
            return it;
        }
};