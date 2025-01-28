#pragma once

namespace detail
{
    template < class type, int dim, class device >
    class array_upper;

    template < class type, class device >
    class array_upper<type,1,device>
    {
        public: // Data
            array<type,2,device>* ptr = nullptr;
            array_attribute       atr = no_attribute;
            int                   ofs = 0;

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;
            using iterator        = detail::array_iterator          <type,1,device>;
            using const_iterator  = detail::array_const_iterator    <type,1,device>;
        
        public: // Core
            constexpr array_upper ( ) = default;
            // TODO: make copy_constructor private and only accessible to friend: tuple_lower<type,dim,device>;

        public: // Constructor
            constexpr array_upper (       array<type,2,device>&, array_attribute, int );
            constexpr array_upper ( const array<type,2,device>&, array_attribute, int );

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
            constexpr bool            ownership  ( ) const;
            constexpr bool            contiguous ( ) const;
            constexpr array_attribute attribute  ( ) const;
            constexpr int             offset     ( ) const;
    
        public: // Host
                                  constexpr       array<type,2,device>& host      ( );
                                  constexpr const array<type,2,device>& host      ( ) const;
                                  constexpr       int                   top_size  ( ) const;
            template < int axis > constexpr       int                   axis_size ( ) const;

        public: // View
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
            array_attribute           atr  = no_attribute;
            int                       ofs  = 0;

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;
            using iterator        = detail::array_iterator          <type,dim,device>;
            using const_iterator  = detail::array_const_iterator    <type,dim,device>;
        
        public: // Core
            constexpr array_upper ( ) = default;
            // TODO: make copy_constructor private and only accessible to friend: tuple_lower<type,dim,device>;

        public: // Constructor
            constexpr array_upper (       array<type,dim+1,device>&, array_attribute, int );
            constexpr array_upper ( const array<type,dim+1,device>&, array_attribute, int );
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
            constexpr bool            ownership  ( ) const;
            constexpr bool            contiguous ( ) const;
            constexpr array_attribute attribute  ( ) const;
            constexpr int             offset     ( ) const;
        
        public: // Host
            template < int attr > constexpr       array<type,dim+1,device>& host      ( )       requires ( attr == 1 );
            template < int attr > constexpr const array<type,dim+1,device>& host      ( ) const requires ( attr == 1 );
            template < int attr > constexpr       array<type,dim,  device>& host      ( )       requires ( attr == 2 );
            template < int attr > constexpr const array<type,dim,  device>& host      ( ) const requires ( attr == 2 );
                                  constexpr       int                       top_size  ( ) const;
            template < int axis > constexpr       int                       axis_size ( ) const;

        public: // View
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> rows     ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> rows     ( int_type auto... ) const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> columns  ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> columns  ( int_type auto... ) const;
                                  constexpr       reference                                at       ( int_type auto... );
                                  constexpr       const_reference                          at       ( int_type auto... ) const;
    };

    template < class type, class device >
    class array_upper<type,max_dim,device>
    {
        private: // Data
            array<type,max_dim,device>* ptr = nullptr;

        public: // Typedef
            using value_type      = device::template value_type     <type>;
            using reference       = device::template reference      <type>;
            using const_reference = device::template const_reference<type>;
            using pointer         = device::template pointer        <type>;
            using const_pointer   = device::template const_pointer  <type>;
            using iterator        = detail::array_iterator          <type,max_dim,device>;
            using const_iterator  = detail::array_const_iterator    <type,max_dim,device>;
        
        public: // Core
            constexpr array_upper ( ) = default;
            // TODO: make copy_constructor private and only accessible to friend: tuple_lower<type,dim,device>;

        public: // Constructor
            constexpr array_upper (       array<type,max_dim,device>& );
            constexpr array_upper ( const array<type,max_dim,device>& );

        public: // Member
            constexpr       int                           size          ( )     const;
            constexpr       int                           capacity      ( )     const = delete;
            constexpr       array<int>                    shape         ( )     const;
            constexpr       inplace_array<int,max_dim>    inplace_shape ( )     const;
            constexpr       static_array<int,max_dim>     static_shape  ( )     const;
            constexpr       int                           row           ( )     const;
            constexpr       int                           column        ( )     const requires ( max_dim == 2 );
            constexpr       bool                          empty         ( )     const;
            constexpr       pointer                       data          ( )           = delete;
            constexpr       const_pointer                 data          ( )     const = delete;
            constexpr       iterator                      begin         ( );
            constexpr       const_iterator                begin         ( )     const;
            constexpr       iterator                      end           ( );
            constexpr       const_iterator                end           ( )     const;
            constexpr       array<type,max_dim-1,device>& operator []   ( int );
            constexpr const array<type,max_dim-1,device>& operator []   ( int ) const;

        public: // Memory
            constexpr bool            ownership  ( ) const;
            constexpr bool            contiguous ( ) const = delete;
            constexpr array_attribute attribute  ( ) const = delete;
            constexpr int             offset     ( ) const = delete;
        
        public: // Host
                                  constexpr       array<type,max_dim,device>& host      ( );
                                  constexpr const array<type,max_dim,device>& host      ( ) const;
                                  constexpr       int                         top_size  ( ) const = delete;
            template < int axis > constexpr       int                         axis_size ( ) const;

        public: // View
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> rows     ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> rows     ( int_type auto... ) const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> columns  ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> columns  ( int_type auto... ) const;
                                  constexpr       reference                                at       ( int_type auto... )       = delete;
                                  constexpr       const_reference                          at       ( int_type auto... ) const = delete;
    };

} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */