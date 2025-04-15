#pragma once

template < class type, class device >
class array<basic_string_view<type,device>,1,cpu>
    extends protected array<typename device::template basic_string_view<type>,1,cpu>
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
        using base::size,
              base::empty;

        constexpr iterator begin ( )
        {
            return static_cast<pointer>(base::data());
        }

        constexpr const_iterator begin ( ) const
        {
            return static_cast<const_pointer>(base::data());
        }

        constexpr iterator end ( )
        {
            return static_cast<pointer>(base::data() + base::size());
        }

        constexpr const_iterator end ( ) const
        {
            return static_cast<const_pointer>(base::data() + base::size());
        }

        constexpr reference operator [] ( int pos )
        {
            return static_cast<reference>(base::operator[](pos));
        }

        constexpr const_reference operator [] ( int pos ) const 
        {
            return static_cast<const reference>(base::operator[](pos));
        } 

    public: // Member
        constexpr array& push ( const value_type& new_value )
        {
            base::push(new_value);
            return self;
        }

    public: // Extension
        constexpr void push_back ( const value_type& new_value )
        {
            base::push_back(new_value);
        }
};

template < class type, int dim, class device >
class array<basic_string_view<type,device>,dim,cpu>
{
    static_assert(false, "deleted");
};