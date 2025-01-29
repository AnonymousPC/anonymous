#pragma once

namespace detail
{
    template < class collection_type, class type2, class device >
    class map_values
        extends public collection_algo<map_values<collection_type,type2,device>,type2,device>
    {
        public: // Typedef
            using  value_type            = device::template value_type     <type2>;
            using  reference             = device::template reference      <type2>;
            using  const_reference       = device::template const_reference<type2>;
            using  pointer               = device::template pointer        <type2>;
            using  const_pointer         = device::template const_pointer  <type2>;
            class  iterator; 
            class  const_iterator;      
            using  device_type           = device;

        public: // Member
            constexpr iterator begin ( )
            {
                return static_cast<collection_type&>(self).begin();
            }

            constexpr const_iterator begin ( ) const
            {
                return static_cast<const collection_type&>(self).begin();
            }

            constexpr iterator end ( )
            {
                return static_cast<collection_type&>(self).end();
            }

            constexpr const_iterator end ( ) const
            {
                return static_cast<const collection_type&>(self).end();
            }
    };

    template < class collection_type, class type2, class device >
    class map_values<collection_type,type2,device>::iterator
        extends public collection_type::iterator
    {
        private: // Typedef
            using base = collection_type::iterator;

        public: // Typedef
            using value_type = device::template value_type<type2>;
            using reference  = device::template reference <type2>;
            using pointer    = device::template pointer   <type2>;

        public: // Override
            constexpr iterator ( base init_b )
                extends base ( std::move(init_b) )
            {

            }

            constexpr reference operator * ( ) const
            {
                return base::operator*().value();
            }

            constexpr pointer operator -> ( ) const
            {
                return &(operator*());
            }

            constexpr reference operator [] ( int p ) const
                requires requires ( int i ) { base::operator[](i); }
            {
                return base::operator[](p).value();
            }

            constexpr friend iterator operator + ( const iterator& left, int right )
                requires requires ( base b, int i ) { b + i; }
            {
                return static_cast<const base&>(left) + right;
            }

            constexpr friend iterator operator + ( int left, const iterator& right )
                requires requires ( int i, base b ) { i + b; }
            {
                return left + static_cast<const base&>(right);
            }
        
            constexpr friend iterator operator - ( const iterator& left, int right )
                requires requires ( base b, int i ) { b - i; }
            {
                return static_cast<const base&>(left) - right;
            }

            constexpr friend iterator& operator ++ ( iterator& left )
                requires requires ( base b ) { ++b; }
            {
                ++static_cast<base&>(left);
                return left;
            }

            constexpr friend iterator operator ++ ( iterator& left, int )
                requires requires ( base b ) { b++; }
            {
                let it = left;
                ++left;
                return it;
            }

            constexpr friend iterator& operator -- ( iterator& left )
                requires requires ( base b ) { --b; }
            {
                --static_cast<base&>(left);
                return left;
            }

            constexpr friend iterator operator -- ( iterator& left, int )
                requires requires ( base b ) { b--; }
            {
                let it = left;
                --left;
                return it;
            }      
    };

    template < class collection_type, class type2, class device >
    class map_values<collection_type,type2,device>::const_iterator
        extends public collection_type::const_iterator
    {
        private: // Typedef
            using base = collection_type::const_iterator;

        public: // Typedef
            using value_type = device::template value_type     <type2>;
            using reference  = device::template const_reference<type2>;
            using pointer    = device::template const_pointer  <type2>;

        public: // Override
            constexpr const_iterator ( base init_b )
                extends base ( std::move(init_b) )
            {

            }

            constexpr reference operator * ( ) const
            {
                return base::operator*().value();
            }

            constexpr pointer operator -> ( ) const
            {
                return &(operator*());
            }

            constexpr reference operator [] ( int p ) const
                requires requires ( int i ) { base::operator[](i); }
            {
                return base::operator[](p).value();
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
                let it = left;
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
                let it = left;
                --left;
                return it;
            }      
    };
} // namespace detail