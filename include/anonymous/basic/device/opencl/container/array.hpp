#pragma once

template < class type, int len >
class opencl::array 
    extends public boost::compute::array<type,len>
{
    private: // Typedef
        using base = boost::compute::array<type,len>;

    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;
        using iterator        = pointer;
        using const_iterator  = const_pointer;

    public: // Core
        array ( )
            extends array ( opencl::execution_context.context() )
        {

        }

        array ( const array& init )
            extends base ( static_cast<const base&>(init), opencl::execution_context.command_queue() )
        {
            opencl::execution_context.command_queue().finish();
        }

        array ( array&& init )
            extends array ( init ) // Falls into copy.
        {
            
        }

        array& operator = ( const array& right )
        {
            boost::compute::copy(right.begin(), right.end(), self.begin(), opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return self;
        }

        array& operator = ( array&& right )
        {
            return self = right; // Falls into copy.
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
};