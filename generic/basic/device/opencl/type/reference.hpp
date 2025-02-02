#pragma once

template < class type >
class opencl::reference
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Core 
        reference ( )                             = delete;
        reference ( const reference& )            = default;
        reference operator = ( const reference& );

    public: // Assign
                                 reference operator = (                 type   );
     //                          reference operator = (       reference<type > );
                                 reference operator = ( const_reference<type > );
        template < class type2 > reference operator = (                 type2  ) requires convertible_to<type2,type>;
        template < class type2 > reference operator = (       reference<type2> ) requires convertible_to<type2,type>;
        template < class type2 > reference operator = ( const_reference<type2> ) requires convertible_to<type2,type>;

    public: // Conversion
        explicit reference ( const_reference<type> );
        operator type ( ) const;

    public: // Boost.compute
        reference ( boost::compute::buffer, size_t );
        reference ( boost::compute::detail::buffer_value<type> );
        operator    boost::compute::detail::buffer_value<type> ( ) const;
        boost::compute::buffer get_buffer ( ) const;
        size_t                 get_index  ( ) const;
};

template < class type >
class opencl::const_reference
{
    private: // Data
        boost::compute::buffer buf = boost::compute::buffer();
        size_t                 idx = 0;

    public: // Core
        const_reference ( )                                   = delete;
        const_reference ( const const_reference& )            = default;
        const_reference operator = ( const const_reference& ) = delete;

    public: // Assign
                                 const_reference operator = (                 type   )                                     = delete;
                                 const_reference operator = (       reference<type > )                                     = delete;
     //                          const_reference operator = ( const_reference<type > )                                     = delete;
        template < class type2 > const_reference operator = (                 type2  ) requires convertible_to<type2,type> = delete;
        template < class type2 > const_reference operator = (       reference<type2> ) requires convertible_to<type2,type> = delete;
        template < class type2 > const_reference operator = ( const_reference<type2> ) requires convertible_to<type2,type> = delete;

    public: // Conversion
        const_reference ( reference<type> );
        operator type ( ) const;

    public: // Boost.compute
        const_reference ( boost::compute::buffer, size_t );
        const_reference ( boost::compute::detail::buffer_value<type> );
        operator          boost::compute::detail::buffer_value<type> ( ) const = delete;
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
template < class type1, class type2 > opencl::template reference<type1>    operator +=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a +=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator +=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a +=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator +=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a +=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator -=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a -=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator -=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a -=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator -=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a -=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator *=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a *=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator *=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a *=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator *=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a *=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator /=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a /=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator /=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a /=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator /=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a /=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator %=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a %=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator %=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a %=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator %=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a %=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator &=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a &=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator &=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a &=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator &=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a &=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator |=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a |=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator |=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a |=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator |=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a |=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator ^=  ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a ^=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator ^=  ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a ^=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator ^=  ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a ^=  b; };
template < class type1, class type2 > opencl::template reference<type1>    operator <<= ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a <<= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator <<= ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a <<= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator <<= ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a <<= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator >>= ( opencl::template       reference<type1>,                                  type2  ) requires requires ( type1 a, type2 b ) { a >>= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator >>= ( opencl::template       reference<type1>, opencl::template       reference<type2> ) requires requires ( type1 a, type2 b ) { a >>= b; };
template < class type1, class type2 > opencl::template reference<type1>    operator >>= ( opencl::template       reference<type1>, opencl::template const_reference<type2> ) requires requires ( type1 a, type2 b ) { a >>= b; };
template < class type >               opencl::template reference<type>     operator ++  ( opencl::template       reference<type>                                           ) requires requires ( type  a          ) {   ++  a; };
template < class type >               type                                 operator ++  ( opencl::template       reference<type>, int                                      ) requires requires ( type  a          ) { a ++;    };
template < class type >               opencl::template reference<type>     operator --  ( opencl::template       reference<type>                                           ) requires requires ( type  a          ) {   --  a; };
template < class type >               type                                 operator --  ( opencl::template       reference<type>, int                                      ) requires requires ( type  a          ) { a --;    };

#include "reference.ipp"