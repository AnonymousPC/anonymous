#pragma once

template < class type >
class opencl::accessor_type
{
    public: // Typedef
        using offset_policy    = accessor_type;
        using element_type     = type;
        using reference        = opencl::template reference<type>;
        using data_handle_type = opencl::template pointer  <type>;

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

template < class type >
class opencl::accessor_type<const type>
{
    public: // Typedef
        using offset_policy    = accessor_type;
        using element_type     = const type;
        using reference        = opencl::template const_reference<type>;
        using data_handle_type = opencl::template const_pointer  <type>;

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





