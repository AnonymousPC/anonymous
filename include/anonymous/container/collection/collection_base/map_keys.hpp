namespace detail
{
    template < class collection_type, class type1, class device >
    class map_keys
        extends public collection_algo<map_keys<collection_type,type1,device>,type1,device>
    {
        public: // Typedef
            using  value_type            = device::template value_type     <type1>;
            using  reference             = device::template reference      <type1>;
            using  const_reference       = device::template const_reference<type1>;
            using  pointer               = device::template pointer        <type1>;
            using  const_pointer         = device::template const_pointer  <type1>;
         // class  iterator; 
            class  const_iterator;      
            using  device_type           = device;
            struct set_concept { };

        public: // Member
            constexpr int size ( ) const
            {
                return static_cast<const collection_type&>(self).size();
            }

            constexpr const_iterator begin ( ) const
            {
                return static_cast<const collection_type&>(self).begin();
            }

            constexpr const_iterator end ( ) const
            {
                return static_cast<const collection_type&>(self).end();
            }

            constexpr bool contains ( const type1& k ) const
            {
                return static_cast<const collection_type&>(self).contains(k);
            }
    };

    template < class collection_type, class type1, class device >
    class map_keys<collection_type,type1,device>::const_iterator
        extends public collection_type::const_iterator
    {
        private: // Typedef
            using base = collection_type::const_iterator;

        public: // Typedef
            using value_type = device::template value_type     <type1>;
            using reference  = device::template const_reference<type1>;
            using pointer    = device::template const_pointer  <type1>;

        public: // Override
            constexpr const_iterator ( ) = default;

            constexpr const_iterator ( base init_b )
                extends base ( std::move(init_b) )
            {

            }

            constexpr reference operator * ( ) const
            {
                return base::operator*().key();
            }

            constexpr pointer operator -> ( ) const
            {
                return &(operator*());
            }

            constexpr reference operator [] ( int p ) const
                requires requires ( int i ) { base::operator[](i); }
            {
                return base::operator[](p).key();
            }

            constexpr friend const_iterator operator + ( const const_iterator& left, int right )
                requires requires ( base b, int i ) { b + i; }
            {
                return static_cast<const base&>(left) + right;
            }

            constexpr friend const_iterator operator + ( int left, const const_iterator& right )
                requires requires ( int i, base b ) { i + b; }
            {
                return left + static_cast<const base&>(right);
            }
        
            constexpr friend const_iterator operator - ( const const_iterator& left, int right )
                requires requires ( base b, int i ) { b - i; }
            {
                return static_cast<const base&>(left) - right;
            }

            constexpr friend const_iterator& operator ++ ( const_iterator& left )
                requires requires ( base b ) { ++b; }
            {
                ++static_cast<base&>(left);
                return left;
            }

            constexpr friend const_iterator operator ++ ( const_iterator& left, int )
                requires requires ( base b ) { b++; }
            {
                auto it = left;
                ++left;
                return it;
            }

            constexpr friend const_iterator& operator -- ( const_iterator& left )
                requires requires ( base b ) { --b; }
            {
                --static_cast<base&>(left);
                return left;
            }

            constexpr friend const_iterator operator -- ( const_iterator& left, int )
                requires requires ( base b ) { b--; }
            {
                auto it = left;
                --left;
                return it;
            }      
    };
} // namespace detail