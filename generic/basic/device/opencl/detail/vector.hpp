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
        using iterator        = pointer;
        using const_iterator  = const_pointer;

    public: // Core
        vector ( )
            extends base ( opencl::execution_context.queue() )
        {

        }

        vector ( const vector& init )
            extends base ( static_cast<const base&>(init), opencl::execution_context.queue() )
        {
            
        }

        vector ( vector&& ) = default;

        vector& operator = ( const vector& right )
        {
            base::resize(right.size(), opencl::execution_context.queue());
            boost::compute::copy(right.base::begin(), right.base::end(), self.base::begin(), opencl::execution_context.queue());
        }

    public: // Constructor
        vector ( auto&&... args )
            requires constructible_from<base,decltype(args)...,const boost::compute::context&>
            extends base ( std::forward<decltype(args)>(args)..., opencl::execution_context.context() )
        {
            
        }

        vector ( auto&&... args )
            requires constructible_from<base,decltype(args)...,boost::compute::command_queue&>
            extends base ( std::forward<decltype(args)>(args)..., opencl::execution_context.queue() )
        {
            
        }

    public: // Override
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

        reference operator [] ( int ofs )
        {
            return base::operator[](ofs);
        }

        const_reference operator [] ( int ofs ) const
        {
            return base::operator[](ofs);
        }

        void resize ( auto&&... args )
        {
            base::resize(std::forward<decltype(args)>(args)..., opencl::execution_context.queue());
            opencl::execution_context.queue().finish();   
        }

        void push_back ( auto&&... args )
        {
            base::push_back(std::forward<decltype(args)>(args)..., opencl::execution_context.queue());
            opencl::execution_context.queue().finish();   
        }

        void pop_back ( auto&&... args )
        {
            base::push_back(std::forward<decltype(args)>(args)..., opencl::execution_context.queue());
            opencl::execution_context.queue().finish();   
        }

        iterator insert ( auto&&... args )
        {
            let it = base::insert(std::forward<decltype(args)>(args)..., opencl::execution_context.queue());
            opencl::execution_context.queue().finish(); 
            return it; 
        }

        iterator erase ( auto&&... args )
        {
            let it = base::erase(std::forward<decltype(args)>(args)..., opencl::execution_context.queue());
            opencl::execution_context.queue().finish(); 
            return it; 
        }


};