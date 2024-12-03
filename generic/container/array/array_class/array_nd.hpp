#pragma once


template < class type, int dim >
    requires ( dim >= 2 )
class array<type,dim>
    extends public array<array<type,dim-1>>,
            public array_algo<array<type,dim>,type,array_line<type,dim-1>,dim>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    public: // Typedef
        using  value_type     = type;
        using  iterate_type   = array_line      <type,dim-1>;
        using  base           = array     <array<type,dim-1>>;
        using  array_algo     = array_algo<array<type,dim>,value_type,iterate_type,dim>;
        using  iterator       = iterate_type*;
        using  const_iterator = const iterate_type*;
        struct array_tag { };

    public: // Core
        constexpr          array ( )                                                 = default;
        constexpr explicit array ( int,  int_type auto... args )                       requires ( 1 + sizeof...(args)     == dim );
        constexpr          array ( int,       auto... args )                           requires ( 1 + sizeof...(args) - 1 == dim ) and std::copyable<type> and aux::ints_until_last_type     <type,int,    decltype(args)...>;
        constexpr          array ( int,       auto... args )                           requires ( 1 + sizeof...(args) - 1 == dim )                         and aux::ints_until_last_func     <type,int,    decltype(args)...>;
        constexpr          array ( int,  int, auto... args )                           requires ( 2 + sizeof...(args) - 1 == dim )                         and aux::ints_until_last_func_ints<type,int,int,decltype(args)...>;
        constexpr          array ( int,  const array_type<type,dim-1> auto& )          requires std::copyable<type>;
        constexpr          array ( int,  function_type<array<type,dim-1>()>    auto  );
        constexpr          array ( int,  function_type<array<type,dim-1>(int)> auto  );
        constexpr          array (       std::initializer_list<array<type,dim-1>>&&  );
        constexpr          array ( const array_type<type,dim> auto& )                  requires std::copyable<type>;
        constexpr          array ( const array_type           auto& arr )              requires ( not std::same_as<typename decay<decltype(arr)>::value_type,type> ) but std::convertible_to<typename decay<decltype(arr)>::value_type,type> and ( decay<decltype(arr)>::dimension() == 1 );

    public: // Conversion between types
        template < class type2 > constexpr          array ( const array<type2,dim>& )  requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array<type2,dim>& )  requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

    public: // Conversion between dims
        template < int dim2, int dim3 > constexpr explicit array ( array<array<type,dim3>,dim2> ) requires ( dim == dim2 + dim3 ); // Here type is same, then enable moving.

    public: // Interface
        constexpr        int            row         ( )     const;
        constexpr        int            column      ( )     const requires ( dim == 2 );
        constexpr        int            size        ( )     const;
        constexpr        bool           empty       ( )     const;
        constexpr        iterator       begin       ( );
        constexpr        const_iterator begin       ( )     const;
        constexpr        iterator       end         ( );
        constexpr        const_iterator end         ( )     const;
        constexpr        iterate_type&  operator [] ( int );
        constexpr const  iterate_type&  operator [] ( int ) const;

        template < int axis = 0 > constexpr array& resize ( int, int_type auto... args )    requires ( axis == 0 and 1 + sizeof...(args) == dim );
        template < int axis = 0 > constexpr array& resize ( const array_coordinate<dim>& )  requires ( axis == 0 );
        template < int axis = 0 > constexpr array& resize ( const array_type<int,1> auto& ) requires ( axis == 0 );
        template < int axis = 0 > constexpr array& resize ( int )                           requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;

    public: // Algo
        using array_algo::dimension,
              array_algo::shape,
              array_algo::static_shape,
              array_algo::inplace_shape,
              array_algo::tuple_shape,

              array_algo::clear,
              array_algo::erase,
              array_algo::insert,
              array_algo::push,
              array_algo::pop,

              array_algo::average,
              array_algo::adjacent_find,
              array_algo::adjacent_where,
              array_algo::all,
              array_algo::contains,
              array_algo::count,
              array_algo::each,
              array_algo::exist,
              array_algo::generate,
              array_algo::fill,
              array_algo::find,
              array_algo::is_partitioned,
              array_algo::is_sorted,
              array_algo::max,
              array_algo::min,
              array_algo::next_permutation,
              array_algo::none,
              array_algo::partition,
              array_algo::prev_permutation,
              array_algo::product,
              array_algo::remove,
              array_algo::replace,
              array_algo::reverse,
              array_algo::right_adjacent_find,
              array_algo::right_find,
              array_algo::rotate,
              array_algo::sample,
              array_algo::shuffle,
              array_algo::sort,
              array_algo::sum,
              array_algo::transform,
              array_algo::unique,
              array_algo::where;
};


#include "array_nd.ipp"