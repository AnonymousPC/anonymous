#pragma once

template < class type >
class opencl::reference
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Typedef
        using  value_type = type;
        struct opencl_reference_tag { };

    public: // Core 
        reference ( )                  = delete;
        reference ( const reference& ) = default;

    public: // Assign
        reference operator = ( const_reference<type> );

    public: // Conversion (type)
        template < class type2 > reference operator = ( const_reference<type2> );

    public: // Conversion (const)
        explicit reference ( const_reference<type> );

    public: // Conversion (device)
        reference operator = ( type );
        operator type ( ) const;

    public: // Conversion (boost::compute)
        reference ( boost::compute::buffer, size_t );
        reference ( boost::compute::detail::buffer_value<type> );
        operator    boost::compute::detail::buffer_value<type> ( ) const;

    public: // Member
        boost::compute::buffer get_buffer ( ) const;
        size_t                 get_index  ( ) const;
};

template < class type >
class opencl::const_reference
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Typedef
        using  value_type = type;
        struct opencl_const_reference_tag { };

    public: // Core
        const_reference ( )                        = delete;
        const_reference ( const const_reference& ) = default;

    public: // Assign
        const_reference operator = ( const_reference<type> ) = delete;

    public: // Conversion (type)
        template < class type2 > const_reference operator = ( const_reference<type2> ) = delete;

    public: // Conversion (const)
        const_reference ( reference<type> );

    public: // Conversion (device)
        const_reference operator = ( type ) = delete;
        operator type ( ) const;

    public: // Conversion (boost::compute)
        const_reference ( boost::compute::buffer, size_t );
        const_reference ( boost::compute::detail::buffer_value<type> );
        operator          boost::compute::detail::buffer_value<type> ( ) const = delete;

    public: // Member
        boost::compute::buffer get_buffer ( ) const;
        size_t                 get_index  ( ) const;
};

template < class type >               opencl::template       pointer<type> operator &   ( opencl::template       reference<type> );
template < class type >               opencl::template const_pointer<type> operator &   ( opencl::template const_reference<type> );
template < class type1, class type2 > bool                                 operator ==  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > bool                                 operator ==  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > bool                                 operator ==  ( opencl::template const_reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > bool                                 operator ==  ( opencl::template const_reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > compare_result<type1,type2>          operator <=> ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > compare_result<type1,type2>          operator <=> ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > compare_result<type1,type2>          operator <=> ( opencl::template const_reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > compare_result<type1,type2>          operator <=> ( opencl::template const_reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a <=> b; };
template < class type1, class type2 > opencl::template reference<type1>    operator +=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a +=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator +=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a +=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator -=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a -=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator -=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a -=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator *=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a *=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator *=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a *=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator /=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a /=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator /=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a /=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator %=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a %=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator %=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a %=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator &=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a &=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator &=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a &=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator |=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a |=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator |=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a |=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator ^=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a ^=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator ^=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a ^=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator <<= ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a <<= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator <<= ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a <<= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator >>= ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a >>= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator >>= ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a >>= b; };
template < class type >               opencl::template reference<type>     operator ++  ( opencl::template       reference<type>                                           ) requires requires ( type  a          ) {   ++  a; };
template < class type >               type                                 operator ++  ( opencl::template       reference<type>, int                                      ) requires requires ( type  a          ) { a ++;    };
template < class type >               opencl::template reference<type>     operator --  ( opencl::template       reference<type>                                           ) requires requires ( type  a          ) {   --  a; };
template < class type >               type                                 operator --  ( opencl::template       reference<type>, int                                      ) requires requires ( type  a          ) { a --;    };

#include "reference.ipp"