namespace detail
{
    template < class container, class type2, class device >
    class map_values
        extends public collection_algo<map_values<container,type2,device>,type2,device>
    {
        public: // Typedef
            using value_type      = device::template value_type     <type2>;
            using reference       = device::template reference      <type2>;
            using const_reference = device::template const_reference<type2>;
            using pointer         = device::template pointer        <type2>;
            using const_pointer   = device::template const_pointer  <type2>;
            class iterator        = device::template value_iterator <typename container::iterator>;
            class const_iterator  = device::template value_iterator <typename container::const_iterator>;
            using device_type     = device;

        public: // Member
            constexpr int            size  ( ) const;
            constexpr iterator       begin ( );
            constexpr const_iterator begin ( ) const;
            constexpr iterator       end   ( );
            constexpr const_iterator end   ( ) const;
    };

} // namespace detail