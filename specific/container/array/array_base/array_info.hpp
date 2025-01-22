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

        public: // Core
            constexpr array_info ( ) = default;

        public: // Consturctor
            constexpr array_info ( const auto&... /*shape*/ );

        public: // Member
            constexpr int                    size          ( ) const;
            constexpr array<int>             shape         ( ) const;
            constexpr inplace_array<int,dim> inplace_shape ( ) const;
            constexpr static_array<int,dim>  static_shape  ( ) const;
            constexpr int                    row           ( ) const;
            constexpr int                    column        ( ) const requires ( dim == 2 );
            constexpr bool                   empty         ( ) const;

            constexpr array_info&            resize        ( const static_array<int,dim>& );
          
    };
} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */
