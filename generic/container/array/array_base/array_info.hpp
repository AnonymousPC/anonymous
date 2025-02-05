#pragma once

namespace detail
{   
    template < class type, int dim, class device >
    class array_info;

    template < class type, class device >
    class array_info<type,1,device>
    {
        static_assert(false, "not provided for 1-dimension array");  
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class array_info<type,dim,device>
    {
        private: // Data
            static_array<int,dim> shp;

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;

        public: // Core
            constexpr array_info ( ) = default;

        public: // Consturctor
            constexpr array_info ( const auto&... /*shape*/ );

        public: // Member
            constexpr int                    size          ( ) const;
            constexpr static_array<int,dim>  shape         ( ) const;
            constexpr int                    row           ( ) const;
            constexpr int                    column        ( ) const requires ( dim == 2 );
            constexpr bool                   empty         ( ) const;
            constexpr array_info&            resize        ( const static_array<int,dim>& );

        public: // Detail
            template < int axis > constexpr int get_size_axis ( ) const;
          
    };
}