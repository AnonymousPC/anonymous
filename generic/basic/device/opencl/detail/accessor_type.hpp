#pragma once

template < class type >
class opencl::accessor_type
{
    public: // Typedef
        using offset_policy    = accessor_type;
        using element_type     = type;
        using reference        = boost::compute::detail::buffer_value<type>;
        using data_handle_type = boost::compute::detail::device_ptr<type>;

    public: // Member
        constexpr reference access ( data_handle_type p, std::size_t i ) const
        {
            return *(p + i);
        }

        constexpr data_handle_type offset ( data_handle_type p, std::size_t i ) const
        {
            return p + i;
        }
};


