#pragma once

namespace detail
{
    template < class type, int dim, class device >
    class array_upper;

    template < class type, class device >
    class array_upper<type,1,device>
    {
        private: // Data
            array<type,2,device>* ptr = nullptr;

        public: // Attribute
            enum { rows_attribute, columns_attribute };

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;
            using iterator        = detail::array_iterator          <type,device>;
            using const_iterator  = detail::array_const_iterator    <type,device>;
        
        public: // Core
            constexpr array_upper ( )                    = default;
            constexpr array_upper ( const array_upper& ) = delete;

        public: // Constructor
            constexpr array_upper (       array<type,2,device>& );
            constexpr array_upper ( const array<type,2,device>& );

        public: // Member
            constexpr int                  size          ( )     const;
            constexpr int                  capacity      ( )     const = delete;
            constexpr array<int>           shape         ( )     const;
            constexpr inplace_array<int,1> inplace_shape ( )     const;
            constexpr static_array<int,1>  static_shape  ( )     const;
            constexpr int                  row           ( )     const = delete;
            constexpr int                  column        ( )     const = delete;
            constexpr bool                 empty         ( )     const;
            constexpr pointer              data          ( );
            constexpr const_pointer        data          ( )     const;
            constexpr iterator             begin         ( );
            constexpr const_iterator       begin         ( )     const;
            constexpr iterator             end           ( );
            constexpr const_iterator       end           ( )     const;
            constexpr reference            operator []   ( int );
            constexpr const_reference      operator []   ( int ) const;
        
        public: // Memory
            constexpr bool ownership  ( ) const;
            constexpr bool contiguous ( ) const;
            constexpr auto attribute  ( ) const;
            constexpr int  offset     ( ) const;
    
        public: // Up
            constexpr       array<type,2,device>& host     ( );
            constexpr const array<type,2,device>& host     ( ) const;
            constexpr       int                   top_size ( ) const;

        public: // Down
            constexpr       auto            rows     ( )           = delete;
            constexpr const auto            rows     ( )     const = delete;
            constexpr       auto            columns  ( )           = delete;
            constexpr const auto            columns  ( )     const = delete;
            constexpr       reference       at       ( int )       = delete;
            constexpr       const_reference at       ( int ) const = delete;
    };

    template < class type, int dim, class device >
        requires ( dim >= 2 )
    class array_upper<type,dim,device>
    {
        private: // Data
            array<type,dim+1,device>* ptr1 = nullptr;
            array<type,dim,  device>* ptr2 = nullptr;

        public: // Attribute
            enum { rows_attribute, columns_attribute, transpose_attribute };

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;
            using iterator        = std::span<array_upper<type,dim-1,device>>::iterator;
            using const_iterator  = std::span<array_upper<type,dim-1,device>>::const_iterator;
        
        public: // Core
            constexpr array_upper ( )                    = default;
            constexpr array_upper ( const array_upper& ) = delete;

        public: // Constructor
            constexpr array_upper (       array<type,dim+1,device>& );
            constexpr array_upper ( const array<type,dim+1,device>& );
            constexpr array_upper (       array<type,dim,  device>& );
            constexpr array_upper ( const array<type,dim,  device>& );

        public: // Member
            constexpr       int                       size          ( )     const;
            constexpr       int                       capacity      ( )     const = delete;
            constexpr       array<int>                shape         ( )     const;
            constexpr       inplace_array<int,dim>    inplace_shape ( )     const;
            constexpr       static_array<int,dim>     static_shape  ( )     const;
            constexpr       int                       row           ( )     const;
            constexpr       int                       column        ( )     const requires ( dim == 2 );
            constexpr       bool                      empty         ( )     const;
            constexpr       pointer                   data          ( );
            constexpr       const_pointer             data          ( )     const;
            constexpr       iterator                  begin         ( );
            constexpr       const_iterator            begin         ( )     const;
            constexpr       iterator                  end           ( );
            constexpr       const_iterator            end           ( )     const;
            constexpr       array<type,dim-1,device>& operator []   ( int );
            constexpr const array<type,dim-1,device>& operator []   ( int ) const;

        public: // Memory
            constexpr bool ownership  ( ) const;
            constexpr bool contiguous ( ) const;
            constexpr auto attribute  ( ) const;
            constexpr int  offset     ( ) const;
        
        public: // Host
            template < int attr > constexpr       array<type,dim+1,device>& host     ( )       requires ( attr == 1 );
            template < int attr > constexpr const array<type,dim+1,device>& host     ( ) const requires ( attr == 1 );
            template < int attr > constexpr       array<type,dim,  device>& host     ( )       requires ( attr == 2 );
            template < int attr > constexpr const array<type,dim,  device>& host     ( ) const requires ( attr == 2 );
                                  constexpr       int                       top_size ( ) const;

        public: // View
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> rows     ( int_type auto... offsets );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> rows     ( int_type auto... offsets ) const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> columns  ( int_type auto... offsets );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> columns  ( int_type auto... offsets ) const;
                                  constexpr       reference                                at       ( int_type auto... offsets );
                                  constexpr       const_reference                          at       ( int_type auto... offsets ) const;
    };

} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */