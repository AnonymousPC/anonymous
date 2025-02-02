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
            using value_type      = device::template value_type          <type>;
            using reference       = device::template reference           <type>;
            using const_reference = device::template const_reference     <type>;
            using pointer         = device::template pointer             <type>;
            using const_pointer   = device::template const_pointer       <type>;
            using iterator        = device::template stride_pointer      <type>;
            using const_iterator  = device::template const_stride_pointer<type>;
        
        public: // Core
            constexpr array_upper ( ) = default;
            // TODO: make copy_constructor private and only accessible to friend: tuple_lower<type,dim,device>;

        public: // Constructor
            constexpr array_upper (       array<type,2,device>&, array_attribute, int );
            constexpr array_upper ( const array<type,2,device>&, array_attribute, int );

        public: // Member
            constexpr int                  size          ( )     const;
            constexpr int                  capacity      ( )     const = delete;
            constexpr static_array<int,1>  shape         ( )     const;
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
    
        public: // Detail
                                  constexpr       array_attribute       get_attribute ( )     const;
                                  constexpr       int                   get_offset    ( )     const;
                                  constexpr       array<type,2,device>& get_host      ( );
                                  constexpr const array<type,2,device>& get_host      ( )     const;
                                  constexpr       int                   get_size_top  ( )     const;
            template < int axis > constexpr       int                   get_size_axis ( )     const;
            template < int dim2 > constexpr       auto                  get_rows      ( )           = delete;
            template < int dim2 > constexpr const auto                  get_rows      ( )     const = delete;
            template < int dim2 > constexpr       auto                  get_columns   ( )           = delete;
            template < int dim2 > constexpr const auto                  get_columns   ( )     const = delete;
                                  constexpr       reference             get_value     ( int );
                                  constexpr       const_reference       get_value     ( int ) const;
                                  constexpr       pointer               get_pointer   ( int );
                                  constexpr       const_pointer         get_pointer   ( int ) const;
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
            using value_type      = device::template value_type      <type>;
            using reference       = device::template reference       <type>;
            using const_reference = device::template const_reference <type>;
            using pointer         = device::template pointer         <type>;
            using const_pointer   = device::template const_pointer   <type>;
            using iterator        = detail::array_line_iterator      <type,dim,device>;
            using const_iterator  = detail::array_line_const_iterator<type,dim,device>;
        
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
            constexpr       static_array<int,dim>     shape         ( )     const;
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

        public: // Detail
                                  constexpr       array_attribute                          get_attribute ( )                  const;
                                  constexpr       int                                      get_offset    ( )                  const;
            template < int attr > constexpr       array<type,dim+1,device>&                get_host      ( )                        requires ( attr == 1 );
            template < int attr > constexpr const array<type,dim+1,device>&                get_host      ( )                  const requires ( attr == 1 );
            template < int attr > constexpr       array<type,dim,  device>&                get_host      ( )                        requires ( attr == 2 );
            template < int attr > constexpr const array<type,dim,  device>&                get_host      ( )                  const requires ( attr == 2 );
                                  constexpr       int                                      get_size_top  ( )                  const;
            template < int axis > constexpr       int                                      get_size_axis ( )                  const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> get_rows      ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> get_rows      ( int_type auto... ) const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> get_columns   ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> get_columns   ( int_type auto... ) const;
                                  constexpr       reference                                get_value     ( int_type auto... );
                                  constexpr       const_reference                          get_value     ( int_type auto... ) const;
                                  constexpr       pointer                                  get_pointer   ( int_type auto... );
                                  constexpr       const_pointer                            get_pointer   ( int_type auto... ) const;
    };

    template < class type, class device >
    class array_upper<type,max_dim,device>
    {
        private: // Data
            array<type,max_dim,device>* ptr = nullptr;

        public: // Typedef
            using value_type      = device::template value_type      <type>;
            using reference       = device::template reference       <type>;
            using const_reference = device::template const_reference <type>;
            using pointer         = device::template pointer         <type>;
            using const_pointer   = device::template const_pointer   <type>;
            using iterator        = detail::array_line_iterator      <type,max_dim,device>;
            using const_iterator  = detail::array_line_const_iterator<type,max_dim,device>;
        
        public: // Core
            constexpr array_upper ( ) = default;
            // TODO: make copy_constructor private and only accessible to friend: tuple_lower<type,dim,device>;

        public: // Constructor
            constexpr array_upper (       array<type,max_dim,device>& );
            constexpr array_upper ( const array<type,max_dim,device>& );

        public: // Member
            constexpr       int                           size          ( )     const;
            constexpr       int                           capacity      ( )     const = delete;
            constexpr       static_array<int,max_dim>     shape         ( )     const;
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
            constexpr bool ownership  ( ) const;
            constexpr bool contiguous ( ) const = delete;

        public: // Detail
                                  constexpr       array_attribute                          get_attribute ( )                  const;
                                  constexpr       int                                      get_offset    ( )                  const;
                                  constexpr       array<type,max_dim,device>&              get_host      ( );
                                  constexpr const array<type,max_dim,device>&              get_host      ( )                  const;
                                  constexpr       int                                      get_size_top  ( )                  const = delete;
            template < int axis > constexpr       int                                      get_size_axis ( )                  const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> get_rows      ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> get_rows      ( int_type auto... ) const;
            template < int dim2 > constexpr       std::span<array_upper<type,dim2,device>> get_columns   ( int_type auto... );
            template < int dim2 > constexpr const std::span<array_upper<type,dim2,device>> get_columns   ( int_type auto... ) const;
                                  constexpr       reference                                get_value     ( int_type auto... )       = delete;
                                  constexpr       const_reference                          get_value     ( int_type auto... ) const = delete;
                                  constexpr       pointer                                  get_pointer   ( int_type auto... )       = delete;
                                  constexpr       const_pointer                            get_pointer   ( int_type auto... ) const = delete;
    };

} // namespace detail

#include "array_upper.ipp"