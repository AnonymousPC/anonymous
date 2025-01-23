#pragma once

namespace detail
{
    template < class type, int dim, class device >
    class array_lower;

    template < class type, class device >
    class array_lower<type,1,device>
    {
        static_assert(false, "nothing provided for 1-dimension array");
    };

    template < class type, int dim, class device >
    class tuple_of_vector_array_upper;

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class array_lower<type,dim,device>
    {
        private: // Data
            tuple_of_vector_array_upper<type,dim-1,device> rows_view;
            tuple_of_vector_array_upper<type,dim-1,device> columns_view;
                            array_upper<type,dim,  device> transpose_view;

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;
            using iterator        = std::span<array_upper<type,dim-1,device>>::iterator;
            using const_iterator  = std::span<array_upper<type,dim-1,device>>::const_iterator;

        public: // Core
            constexpr array_lower ( );
            constexpr array_lower ( const array_lower& ) = delete;

        public: // Constructor
            constexpr array_lower ( const auto&... /*shape*/ );

        public: // Member
            constexpr       static_array<int,dim>     static_shape ( ) const;
            constexpr       iterator                  begin        ( );
            constexpr       const_iterator            begin        ( )     const;
            constexpr       iterator                  end          ( );
            constexpr       const_iterator            end          ( )     const;
            constexpr       array<type,dim-1,device>& operator []  ( int );
            constexpr const array<type,dim-1,device>& operator []  ( int ) const;

            constexpr array_lower& clear  ( );
            constexpr array_lower& resize ( const static_array<int,dim>& );

        public: // View
            template < int dim2 >       std::span<array_upper<type,dim2,device>>  rows         ( int_type auto... offsets );
            template < int dim2 > const std::span<array_upper<type,dim2,device>>  rows         ( int_type auto... offsets ) const; 
            template < int dim2 >       std::span<array_upper<type,dim2,device>>  columns      ( int_type auto... offsets );
            template < int dim2 > const std::span<array_upper<type,dim2,device>>  columns      ( ) const;
                                                  array_upper<type,dim, device>&  as_transpose ( );
                                  const           array_upper<type,dim, device>&  as_transpose ( ) const;
    };
} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */
