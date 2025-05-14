namespace detail
{
    template < class container, class type, class device >
    class map_keys
        extends public collection_algo<map_keys<container,type,device>,type,device>
    {
        public: // Typedef
            using  value_type      = device::template value_type     <type>;
            using  const_reference = device::template const_reference<type>;
            using  const_pointer   = device::template const_pointer  <type>;
            class  const_iterator  = device::template transform_iterator<typename container::const_iterator,detail::to_key>;
            using  device_type     = device;
            struct set_concept { };

        public: // Member
            constexpr int            size     ( )             const;
            constexpr const_iterator begin    ( )             const;
            constexpr const_iterator end      ( )             const;

            constexpr bool           contains ( const type& ) const;
    };
    
} // namespace detail

#include "map_keys.cpp"