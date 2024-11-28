#pragma once

template < int dim, class value_type >
class array_coordinate;




template < int dim, class value_type >
    requires ( dim == 1 )
class array_coordinate<dim,value_type>
{
    private: // Data
        value_type first = value_type();

    public: // Core
        constexpr array_coordinate ( ) = default;
        constexpr array_coordinate ( value_type );
        constexpr operator array<value_type> ( ) const;
        constexpr static int size ( );

    public: // Member
        template < int index >          requires ( index == 1 or  index == -1 ) constexpr       auto& get ( );
        template < int index >          requires ( index == 1 or  index == -1 ) constexpr const auto& get ( ) const;
        template < int begin, int end > requires ( begin == 1 and end   == -1 ) constexpr       auto& get ( );
        template < int begin, int end > requires ( begin == 1 and end   == -1 ) constexpr const auto& get ( ) const;
        template < int index >          requires ( index == 1 or  index == -1 ) constexpr       auto  pop ( ) = delete;

    public: // Algo
        constexpr auto exist   ( const equalable_to<value_type> auto& ) const;
        constexpr auto exist   (       unary_pred  <value_type> auto  ) const;
        constexpr auto product (                                      ) const;
        constexpr auto product (       unary_op    <value_type> auto  ) const;

    public: // Operator
        constexpr bool operator ==  ( const array_coordinate& ) const = default;
        constexpr auto operator <=> ( const array_coordinate& ) const = default;
};

template < int dim, class value_type >
    requires ( dim >= 2 )
class array_coordinate<dim,value_type>
{
    private: // Data
        value_type                         first = value_type();
        array_coordinate<dim-1,value_type> other = array_coordinate<dim-1,value_type>();

    public: // Core
        constexpr array_coordinate ( ) = default;
        constexpr array_coordinate ( value_type c1, auto... cn )  requires ( std::is_convertible<decltype(cn),value_type>::value and ... and ( sizeof...(cn) + 1 == dim ) );
        constexpr operator array<value_type> ( ) const;
        constexpr static int size ( );

    public: // Member
        template < int index >          requires ( ( index >= -dim and index <= -1 ) or ( index >= 1 and index <= dim ) ) constexpr       auto& get ( );
        template < int index >          requires ( ( index >= -dim and index <= -1 ) or ( index >= 1 and index <= dim ) ) constexpr const auto& get ( ) const;
        template < int begin, int end > requires ( begin == 1 and end == -1 )                                             constexpr       auto& get ( );
        template < int begin, int end > requires ( begin == 1 and end == -1 )                                             constexpr const auto& get ( ) const;
        template < int begin, int end > requires ( begin == 2 and end == -1 )                                             constexpr       auto& get ( );
        template < int begin, int end > requires ( begin == 2 and end == -1 )                                             constexpr const auto& get ( ) const;
        template < int begin, int end > requires ( begin >= 3 and end == -1 )                                             constexpr       auto& get ( );
        template < int begin, int end > requires ( begin >= 3 and end == -1 )                                             constexpr const auto& get ( ) const;
        template < int index >          requires ( ( index >= -dim and index <= -1 ) or ( index >= 1 and index <= dim ) ) constexpr       auto  pop ( ) const;

    public: // Algo
        constexpr auto exist   ( const equalable_to<value_type> auto& ) const;
        constexpr auto exist   (       unary_pred  <value_type> auto  ) const;
        constexpr auto product (                                      ) const;
        constexpr auto product (       unary_op    <value_type> auto  ) const;

    public: // Operator
        constexpr bool operator ==  ( const array_coordinate& ) const = default;
        constexpr auto operator <=> ( const array_coordinate& ) const = default;

    private: // Auxiliary
        template < int index > constexpr static void operator_array_aux ( auto&, const auto& );
        template < int index > constexpr static void pop_aux            ( auto&, const auto& );
};


#include "array_coordinate.ipp"