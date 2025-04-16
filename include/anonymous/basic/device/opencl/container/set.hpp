#pragma once

template < class type, class compare, class alloc >
class opencl::set
    extends public boost::compute::flat_set<type>
{
    private: // Typedef
        using base = boost::compute::flat_set<type>;

    public: // Typedef
        using value_type      = opencl::template value_type     <type>;
        using reference       = opencl::template reference      <type>;
        using const_reference = opencl::template const_reference<type>;
        using pointer         = opencl::template pointer        <type>;
        using const_pointer   = opencl::template const_pointer  <type>;
        using iterator        = pointer;
        using const_iterator  = const_pointer;

    public: // Core
        set ( )
            extends base ( opencl::execution_context.context() )
        {

        }

        set ( const set& init )
            extends base ( static_cast<const base&>(init), opencl::execution_context.command_queue() )
        {
            opencl::execution_context.command_queue().finish();
        }

        set ( set&& init )
            extends set ( init ) // Falls into copy.
        {

        }

        set& operator = ( const set& right )
        {
            as_vector().resize(right.size(), opencl::execution_context.command_queue());
            boost::compute::copy(right.begin(), right.end(), self.begin(), opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return self;
        }

        set& operator = ( set&& right )
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

        iterator find ( const type& val ) const
        {
            auto it = base::find(val, opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return it;
        }

        std::pair<iterator,bool> insert ( const type& val )
        {
            auto p = base::insert(val, opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return std::pair<iterator,bool>(end(), p.second);

            /* Bug in boost::compute::flat_set. 
             * 
             * (Minimal reproducable):
             * boost::compute::flat_set<int> s;
             * for (int i = 0; i < 100; i++)
             *     auto buf = s.insert(i).first.get_buffer();
             * 
             * Return pair(end(), p.second) anyway here to avoid triggering it.
             */
        }

        size_t erase ( const type& val )
        {
            auto s = base::erase(val, opencl::execution_context.command_queue());
            opencl::execution_context.command_queue().finish();
            return s;
        }

    private: // Detail
        boost::compute::vector<type>& as_vector ( )
        {
            static_assert(layout_compatible_with<set,boost::compute::vector<type>>, "fatal error: abi not compatible");
            return reinterpret_cast<boost::compute::vector<type>&>(self);
        }

        const boost::compute::vector<type>& as_vector ( ) const
        {
            static_assert(layout_compatible_with<set,boost::compute::vector<type>>, "fatal error: abi not compatible");
            return reinterpret_cast<const boost::compute::vector<type>&>(self);
        }
};