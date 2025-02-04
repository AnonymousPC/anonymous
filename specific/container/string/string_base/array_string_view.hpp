#pragma once

template < class type, class device >
class array<basic_string_view<type,device>,1,cpu>
    extends public array<typename device::template basic_string_view<type>,1,cpu>
{
    public: // Typedef
        using value_type      = device::template value_type     <basic_string_view<type,device>>;
        using reference       = device::template reference      <basic_string_view<type,device>>;
        using const_reference = device::template const_reference<basic_string_view<type,device>>;
        using pointer         = device::template pointer        <basic_string_view<type,device>>;
        using const_pointer   = device::template const_pointer  <basic_string_view<type,device>>;
        using iterator        = pointer;
        using const_iterator  = const_pointer;

    private: // Typedef
        using base = array<typename device::template basic_string_view<type>,1,cpu>;

    public: // Core
        using base::base;

    public: // Member
        constexpr reference operator [] ( int pos )
        {
            return static_cast<reference>(base::operator[](pos));
        }

        constexpr const_reference operator [] ( int pos ) const 
        {
            return static_cast<const reference>(base::operator[](pos));
        } 
};