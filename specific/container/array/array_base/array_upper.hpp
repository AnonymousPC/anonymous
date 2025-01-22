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
            enum { rows, columns };

        public: // Typedef
            using value_type      = array<type,1,device>::value_type;
            using reference       = array<type,1,device>::reference;
            using const_reference = array<type,1,device>::const_reference;
            using pointer         = array<type,1,device>::pointer;
            using const_pointer   = array<type,1,device>::const_pointer;
        
        public: // Core
            constexpr array_upper ( ) = default;
            constexpr array_upper (       array<type,2,device>& );
            constexpr array_upper ( const array<type,2,device>& );

        public: // Member
            constexpr int                  size          ( )     const;
            constexpr int                  capacity      ( )     const = delete;
            constexpr array<int>           shape         ( )     const = delete;
            constexpr inplace_array<int,1> inplace_shape ( )     const = delete;
            constexpr static_array<int,1>  static_shape  ( )     const = delete;
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
            constexpr       array<type,2,device>& host        ( );
            constexpr const array<type,2,device>& host        ( ) const;
            constexpr       bool                  ownership   ( ) const;
            constexpr       bool                  contiguous  ( ) const;
            constexpr       auto                  attribute   ( ) const;
            constexpr       int                   offset      ( ) const;
            constexpr       int                   top_size    ( ) const;
    }

    template < class type, int dim, class device >
    class array_upper<type,dim,device>
    {
        private: // Data
            array<type,dim+1,device>* ptr1 = nullptr;
            array<type,dim,  device>* ptr2 = nullptr;

        public: // Attribute
            enum { rows, columns, transposed };

        public: // Typedef
            using value_type      = array<type,dim,device>::value_type;
            using reference       = array<type,dim,device>::reference;
            using const_reference = array<type,dim,device>::const_reference;
            using pointer         = array<type,dim,device>::pointer;
            using const_pointer   = array<type,dim,device>::const_pointer;
        
        public: // Core
            constexpr array_upper ( ) = default;
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
            constexpr       int                       row           ( )     const = delete;
            constexpr       int                       column        ( )     const = delete;
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
            template < int attribute > constexpr       array<type,dim+1,device>& host        ( )       requires ( attribute == 1 );
            template < int attribute > constexpr const array<type,dim+1,device>& host        ( ) const requires ( attribute == 1 );
            template < int attribute > constexpr       array<type,dim,  device>& host        ( )       requires ( attribute == 2 );
            template < int attribute > constexpr const array<type,dim,  device>& host        ( ) const requires ( attribute == 2 );
                                       constexpr       bool                      ownership   ( ) const;
                                       constexpr       bool                      contiguous  ( ) const;
                                       constexpr       auto                      attribute   ( ) const;
                                       constexpr       int                       offset      ( ) const;
                                       constexpr       int                       top_size    ( ) const;
                                       constexpr       reference                 at          ( int_type auto... args )       requires ( sizeof...(args) == dim );
                                       constexpr       const_reference           at          ( int_type auto... args ) const requires ( sizeof...(args) == dim );

        private: // Detail
            template < int from, int to > constexpr static int partial_size_of ( const auto& );
            template < int from, int to > constexpr static auto 
    }

} // namespace detail

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */