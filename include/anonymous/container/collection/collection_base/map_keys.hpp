namespace detail
{
    template < class container, class type1, class device >
    class map_keys
        extends public collection_algo<map_keys<container,type1,device>,type1,device>
    {
        public: // Typedef
            using  value_type      = device::template value_type     <type1>;
            using  const_reference = device::template const_reference<type1>;
            using  const_pointer   = device::template const_pointer  <type1>;
            class  const_iterator;      
            using  device_type     = device;
            struct set_concept { };

        public: // Member
            constexpr int            size     ( )              const;
            constexpr const_iterator begin    ( )              const;
            constexpr const_iterator end      ( )              const;

            constexpr bool           contains ( const type1& ) const;
    };
} // namespace detail