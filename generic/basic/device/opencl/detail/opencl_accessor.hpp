#pragma once

namespace detail
{
    template < class type >
    class opencl_accessor
    {
        public: // Typedef
            using offset_policy    = opencl_accessor;
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
} // namespace detail


