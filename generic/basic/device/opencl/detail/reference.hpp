#pragma once

template < class type >
class opencl::reference
{
    private: // Typedef
        boost::compute::buffer buf;
        size_t                 idx;
    
    public: // Core
        reference ( ) = delete;
        reference ( const reference& ) = default;
        reference& operator = ( const reference& ) = default;

    public: // Constructor
        reference ( boost::compute::buffer init_buf, size_t init_idx )
            extends buf ( init_buf ),
                    idx ( init_idx )
        {
            
        }

        reference ( boost::compute::detail::buffer_value<type> init )
            extends buf ( init.get_buffer() ),
                    idx ( init.get_index() )
        {
            
        }

    public: // Operator
        reference operator = ( const type& right )
        {
            boost::compute::detail::write_single_value<type>(right, buf, idx / sizeof(type), boost::compute::system::default_queue()).wait();
            return self;
        }

        opencl::template pointer<type> operator & ( ) const
        {
            return opencl::template pointer<type>(get_buffer(), get_index());
        }

        reference operator ++ ( )
        {
            // TODO: use get-or-build.
            let op = boost::compute::make_function_from_source<void()>
            (
                std::format("increment_{}", demangle(typeid(type))),
                std::format("void increment_{}", demangle(typeid(type)), )
            )

            return self;
        }

        type operator ++ ( int )
        {
            type tmp = self;
            ++self;
            return tmp;
        }

        
};