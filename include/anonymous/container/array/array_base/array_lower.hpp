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
    class tuple_upper;

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class array_lower<type,dim,device>
    {
        private: // Data
            tuple_upper<type,dim-1,device> rows_view;
            tuple_upper<type,dim-1,device> columns_view;
            array_upper<type,dim,  device> transpose_view;

        public: // Typedef
            using value_type      = device::template value_type      <type>;
            using reference       = device::template reference       <type>;
            using const_reference = device::template const_reference <type>;
            using pointer         = device::template pointer         <type>;
            using const_pointer   = device::template const_pointer   <type>;
            using iterator        = detail::array_line_iterator      <type,dim,device>;
            using const_iterator  = detail::array_line_const_iterator<type,dim,device>;

        public: // Core
            constexpr array_lower ( );
            constexpr array_lower ( const array_lower& ) = delete;

        public: // Constructor
            constexpr array_lower ( const auto&... /*shape*/ );
            constexpr array_lower ( const static_array<int,dim>& /*shape*/ );

        public: // Member
            constexpr       iterator                  begin        ( );
            constexpr       const_iterator            begin        ( )     const;
            constexpr       iterator                  end          ( );
            constexpr       const_iterator            end          ( )     const;
            constexpr       array<type,dim-1,device>& operator []  ( int );
            constexpr const array<type,dim-1,device>& operator []  ( int ) const;

        public: // Member
            constexpr array_lower& clear  ( );
            constexpr array_lower& resize ( const static_array<int,dim>& );

        public: // View
            constexpr       array<type,dim, device>& transpose ( );
            constexpr const array<type,dim, device>& transpose ( ) const;

        public: // Detail
            template < int dim2 > constexpr        std::span<array_upper<type,dim2,device>> get_rows    ( int_type auto... );
            template < int dim2 > constexpr  const std::span<array_upper<type,dim2,device>> get_rows    ( int_type auto... ) const; 
            template < int dim2 > constexpr        std::span<array_upper<type,dim2,device>> get_columns ( int_type auto... );
            template < int dim2 > constexpr  const std::span<array_upper<type,dim2,device>> get_columns ( int_type auto... ) const;
    };
} // namespace detail
