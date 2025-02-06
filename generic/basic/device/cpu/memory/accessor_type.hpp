#pragma once

template < class type >
class cpu::accessor_type
{
    public: // Typedef
        using offset_policy    = accessor_type;
        using element_type     = type;
        using reference        = cpu::template reference<type>;
        using data_handle_type = cpu::template pointer  <type>;

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
class cpu::const_accessor_type
{
    public: // Typedef
        using offset_policy    = const_accessor_type;
        using element_type     = type;
        using reference        = cpu::template const_reference<type>;
        using data_handle_type = cpu::template const_pointer  <type>;

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


