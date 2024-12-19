#pragma once
#define template_int_axis template < int axis = 1 > requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )

template < class type, int dim, class device >
    requires ( dim >= 2 )
class array
    extends public device::template vector<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    public: // Typedef
        using  value_type     = type;
        using  device_type    = device;
     // using  iterate_type   = array_view<type,dim-1,'l'>;
        class  iterator;
        class  const_iterator;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr explicit array ( int_type auto... args )                                             requires ( sizeof...(args)     == dim );
        constexpr          array ( auto... args )                                                      requires ( sizeof...(args) - 1 == dim ) and aux::ints_until_last_type     <type,decltype(args)...> and std::copyable<type>;
        constexpr          array ( auto... args )                                                      requires ( sizeof...(args) - 1 == dim ) and aux::ints_until_last_func     <type,decltype(args)...>;
        constexpr          array ( auto... args )                                                      requires ( sizeof...(args) - 1 == dim ) and aux::ints_until_last_func_ints<type,decltype(args)...>;
        constexpr          array ( int,  function_type<array<type,dim-1>()>    auto  );
        constexpr          array ( int,  function_type<array<type,dim-1>(int)> auto  );
        constexpr          array (       std::initializer_list<array<type,dim-1>>&&  );

    public: // Conversion (type)
                                 constexpr          array ( const array_type<type, dim,device> auto& ) requires std::copyable<type>;
        template < class type2 > constexpr          array ( const array_type<type2,dim,device> auto& ) requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array_type<type2,dim,device> auto& ) requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

    public: // Member
        constexpr        int            row         ( )     const;
        constexpr        int            column      ( )     const requires ( dim == 2 );
        constexpr        int                size        ( )     const;
        constexpr        int                capacity    ( )     const;
        constexpr        array<int>         shape       ( )     const;
        constexpr        inplace_array<int> inplace_shape ( ) const;
        constexpr        static_array<int>  static_shape ( ) const;
        constexpr        bool           empty       ( )     const;
        constexpr        type*          data        ( )     const;
        constexpr const  type*          data        ( )     const;
        constexpr        iterator       begin       ( );
        constexpr        const_iterator begin       ( )     const;
        constexpr        iterator       end         ( );
        constexpr        const_iterator end         ( )     const;
        constexpr        iterate_type   operator [] ( int );
        constexpr const  iterate_type   operator [] ( int ) const;

    public: // Member
        template_int_axis constexpr array& resize ( int_type auto... extents ) requires ( sizeof...(extents) == dim );
        template_int_axis constexpr array& clear  ( );
        template_int_axis constexpr array& push   ( const array_type<type,dim-1,device> auto& );
        template_int_axis constexpr array& pop    ( int );
        template_int_axis constexpr array& insert ( int, const array_type<type,dim-1,device> auto& );
        template_int_axis constexpr array& erase  ( int, int );
}

#include "array_nd.ipp"
#undef template_int_axis