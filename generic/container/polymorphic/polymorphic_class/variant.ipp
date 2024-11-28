#pragma once

/// Auxiliary

namespace aux
{
    template < class input_type, class... types > constexpr int index_of_unique_same_type          = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr int index_of_unique_convertible_type   = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr int index_of_unique_constructible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();
    template < class input_type, class... types > constexpr int index_of_unique_assignable_type    = [] { static_assert(false, "you need to specialize it"); return false; } ();
}






/// Class variant

// Core

template < class... types >
constexpr variant<types...>::variant ( )
    extends storage ( first_type_of<types...>() ),
            flag    ( 1 )
{

}

template < class... types >
constexpr variant<types...>::variant ( const variant& init )
    requires ( std::copyable<types> and ... )
    extends storage ( init.storage, init.flag ),
            flag    ( init.flag )
{

}

template < class... types >
constexpr variant<types...>::variant ( variant&& init )
    requires ( std::movable<types> and ... )
    extends storage ( std::move ( init.storage ), init.flag ),
            flag    ( init.flag )
{

}

template < class... types >
constexpr variant<types...>::variant ( auto init )
    requires aux::same_as_only_one_of<decay<decltype(init)>,types...>
    extends storage ( std::move ( init ) ),
            flag    ( aux::index_of_unique_same_type<decltype(init),types...> )
{

}

template < class... types >
constexpr variant<types...>::variant ( const auto& init )
    requires aux::not_same_but_convertible_to_only_one_of<decay<decltype(init)>,types...>
    extends storage ( init ),
            flag    ( aux::index_of_unique_convertible_type<decay<decltype(init)>,types...> )
{

}

template < class... types >
constexpr variant<types...>::variant ( const auto& init )
    requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(init)>,types...>
    extends storage ( init ),
            flag    ( aux::index_of_unique_constructible_type<decay<decltype(init)>,types...> )
{

}

template < class... types >
constexpr variant<types...>::~variant ( )
{
    storage.clear(flag);
}

template < class... types >
constexpr variant<types...>& variant<types...>::operator = ( const variant& right )
    requires ( std::copyable<types> and ... )
{
    self.storage.assign ( right.storage, self.flag, right.flag );
    self.flag = right.flag;

    return self;
}

template < class... types >
constexpr variant<types...>& variant<types...>::operator = ( variant&& right )
    requires ( std::movable<types> and ... )
{
    self.storage.assign ( std::move(right.storage), self.flag, right.flag );
    self.flag = right.flag;

    return self;
}

template < class... types >
constexpr variant<types...>& variant<types...>::operator = ( auto right )
    requires aux::same_as_only_one_of<decay<decltype(right)>,types...>
{
    self.storage.assign ( std::move(right), self.flag );
    self.flag = aux::index_of_unique_same_type<decltype(right),types...>;

    return self;
}

template < class... types >
constexpr variant<types...>& variant<types...>::operator = ( const auto& right )
    requires aux::not_same_but_assignable_to_only_one_of<decay<decltype(right)>,types...>
{
    self.storage.assign ( right, self.flag );
    self.flag = aux::index_of_unique_assignable_type<decay<decltype(right)>,types...>;

    return self;
}

// Member

template < class... types >
constexpr int variant<types...>::index ( ) const
{
    return flag;
}

template < class... types >
constexpr const std::type_info& variant<types...>::type ( ) const
{
    return index() == 0 ? typeid(void) otherwise *static_array{&(typeid(types))...}[index()];
}

template < class... types >
template < class output_type >
constexpr output_type& variant<types...>::value ( )
    requires aux::same_as_only_one_of<output_type,types...>
{
    if ( index() != aux::index_of_unique_same_type<output_type,types...> )
        throw type_error("bad variant access: cannot get {} from {} (whose index = {}, type = {})",
                         typeid(output_type), typeid(self), index(), type());

    return storage.template get<output_type>();
}

template < class... types >
template < class output_type >
constexpr const output_type& variant<types...>::value ( ) const
    requires aux::same_as_only_one_of<output_type,types...>
{
    if ( index() != aux::index_of_unique_same_type<output_type,types...> )
        throw type_error("bad variant access: cannot get {} from {} (whose index = {}, type = {})",
                         typeid(output_type), typeid(self), index(), type());

    return storage.template get<output_type>();
}

template < class... types >
template < int output_index >
constexpr typename variant<types...>::value_type<output_index>& variant<types...>::value ( )
    requires ( ( output_index >= -sizeof...(types) and output_index <= -1 ) or ( output_index >= 1 and output_index <= sizeof...(types) ) )
{
    return value<value_type<output_index>>();
}

template < class... types >
template < int output_index >
constexpr const typename variant<types...>::value_type<output_index>& variant<types...>::value ( ) const
    requires ( ( output_index >= -sizeof...(types) and output_index <= -1 ) or ( output_index >= 1 and output_index <= sizeof...(types) ) )
{
    return value<value_type<output_index>>();
}

template < class... types >
constexpr decltype(auto) variant<types...>::visit ( auto&& visitor )
    requires aux::all_invocable_and_returns_same_type<decltype(visitor),types&...>
{
    return storage.visit ( std::move(visitor), self.flag );
}

template < class... types >
constexpr decltype(auto) variant<types...>::visit ( auto&& visitor ) const
    requires aux::all_invocable_and_returns_same_type<decltype(visitor),const types&...>
{
    return storage.visit ( std::move(visitor), self.flag );
}












/// Class variant::union_type

// Declaration

/* In variant::union_obj, the flag and storage are controlled together.
 * storage.clear() must accept a pos-arg, and std::move() will never
 * clear the right one.
 */

template < class type >
union aux::union_of<type>
{
    private:
        type type_storage;

    public:
        constexpr          union_of ( const union_of&,  int );
        constexpr          union_of (       union_of&&, int );
        constexpr          union_of (       auto  val )                                           requires aux::same_as_only_one_of                             <decay<decltype(val)>,type>;
        constexpr          union_of ( const auto& val )                                           requires aux::not_same_but_convertible_to_only_one_of         <decay<decltype(val)>,type>;
        constexpr explicit union_of ( const auto& val )                                           requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(val)>,type>;
        constexpr         ~union_of ( );
        constexpr          union_of& assign ( const union_of&,  int, int );
        constexpr          union_of& assign (       union_of&&, int, int );
        constexpr          union_of& assign (       auto  val,  int )                             requires aux::same_as_only_one_of                             <decay<decltype(val)>,type>;
        constexpr          union_of& assign ( const auto& val,  int )                             requires aux::not_same_but_assignable_to_only_one_of          <decay<decltype(val)>,type>;

    public:
                                       constexpr       union_of&      clear ( int );
        template < class result_type > constexpr       result_type&   get   ( )                   requires aux::same_as_only_one_of                             <result_type,type>;
        template < class result_type > constexpr const result_type&   get   ( )             const requires aux::same_as_only_one_of                             <result_type,type>;
                                       constexpr       decltype(auto) visit ( auto&&, int );
                                       constexpr       decltype(auto) visit ( auto&&, int ) const;
};

template < class type, class... types >
union aux::union_of<type,types...>
{
    public:
        type               type_storage;
        union_of<types...> other_storage;

    public:
        constexpr          union_of ( const union_of&,  int );
        constexpr          union_of (       union_of&&, int );
        constexpr          union_of (       auto  val )                                           requires aux::same_as_only_one_of                             <decay<decltype(val)>,type,types...>;
        constexpr          union_of ( const auto& val )                                           requires aux::not_same_but_convertible_to_only_one_of         <decay<decltype(val)>,type,types...>;
        constexpr explicit union_of ( const auto& val )                                           requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(val)>,type,types...>;
        constexpr         ~union_of ( );
        constexpr          union_of& assign ( const union_of&,  int, int );
        constexpr          union_of& assign (       union_of&&, int, int );
        constexpr          union_of& assign (       auto  val,  int )                             requires aux::same_as_only_one_of                             <decay<decltype(val)>,type,types...>;
        constexpr          union_of& assign ( const auto& val,  int )                             requires aux::not_same_but_assignable_to_only_one_of          <decay<decltype(val)>,type,types...>;

    public:
                                       constexpr       union_of&      clear ( int );
        template < class result_type > constexpr       result_type&   get   ( )                   requires aux::same_as_only_one_of                             <result_type,type,types...>;
        template < class result_type > constexpr const result_type&   get   ( )             const requires aux::same_as_only_one_of                             <result_type,type,types...>;
                                       constexpr       decltype(auto) visit ( auto&&, int );
                                       constexpr       decltype(auto) visit ( auto&&, int ) const;
};






// Implemention if sizeof...(candicates) == 1

template < class type >
constexpr aux::union_of<type>::union_of ( const union_of& init, int )
{
    std::construct_at ( &type_storage, init.type_storage );
}

template < class type >
constexpr aux::union_of<type>::union_of ( union_of&& init, int )
{
    std::construct_at ( &type_storage, std::move(init.type_storage) );
}

template < class type >
constexpr aux::union_of<type>::union_of ( auto init )
    requires aux::same_as_only_one_of<decay<decltype(init)>,type>
{
    std::construct_at ( &type_storage, std::move(init) );
}

template < class type >
constexpr aux::union_of<type>::union_of ( const auto& init )
    requires aux::not_same_but_convertible_to_only_one_of<decay<decltype(init)>,type>
{
    std::construct_at ( &type_storage, init );
}

template < class type >
constexpr aux::union_of<type>::union_of ( const auto& init )
    requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(init)>,type>
{
    std::construct_at ( &type_storage, init );
}


template < class type >
constexpr aux::union_of<type>::~union_of ( )
{

}

template < class type >
constexpr aux::union_of<type>& aux::union_of<type>::assign ( const union_of& right, int self_flag, int /*right_flag == 1*/ )
{
    if ( self_flag == 1 )
        type_storage = right.type_storage;
    else
        std::construct_at ( &type_storage, right.type_storage );

    return self;
}

template < class type >
constexpr aux::union_of<type>& aux::union_of<type>::assign ( union_of&& right, int self_flag, int /*right_flag == 1*/ )
{
    if ( self_flag == 1 )
        type_storage = std::move(right.type_storage);
    else
        std::construct_at ( &type_storage, std::move(right.type_storage) );

    return self;
}

template < class type >
constexpr aux::union_of<type>& aux::union_of<type>::assign ( auto right, int self_flag )
    requires aux::same_as_only_one_of<decay<decltype(right)>,type>
{
    if ( self_flag == 1 )
        type_storage = std::move(right);
    else
        std::construct_at ( &type_storage, std::move(right) );

    return self;
}

template < class type >
constexpr aux::union_of<type>& aux::union_of<type>::assign ( const auto& right, int self_flag )
    requires aux::not_same_but_assignable_to_only_one_of<decay<decltype(right)>,type>
{
    if ( self_flag == 1 )
        type_storage = right;
    else
        std::construct_at ( &type_storage, right );

    return self;
}

template < class type >
constexpr aux::union_of<type>& aux::union_of<type>::clear ( int self_flag )
{
    if ( self_flag == 1 )
        std::destroy_at ( &type_storage );
    return self;
}

template < class type >
template < class result_type >
constexpr result_type& aux::union_of<type>::get ( )
    requires aux::same_as_only_one_of<result_type,type>
{
    return type_storage;
}

template < class type >
template < class result_type >
constexpr const result_type& aux::union_of<type>::get ( ) const
    requires aux::same_as_only_one_of<result_type,type>
{
    return type_storage;
}

template < class type >
constexpr decltype(auto) aux::union_of<type>::visit ( auto&& visitor, int ) // The variant will check if flag is out of range.
{
    return visitor ( type_storage );
}

template < class type >
constexpr decltype(auto) aux::union_of<type>::visit ( auto&& visitor, int ) const // The variant will check if flag is out of range.
{
    return visitor ( type_storage );
}





// Implemention if sizeof...(candicates) >= 2


template < class type, class... types >
constexpr aux::union_of<type,types...>::union_of ( const union_of& init, int init_flag )
{
    if ( init_flag == 1 )
        std::construct_at ( &type_storage,  init.type_storage );
    else
        std::construct_at ( &other_storage, init.other_storage, init_flag - 1 );
}

template < class type, class... types >
constexpr aux::union_of<type,types...>::union_of ( union_of&& init, int init_flag )
{
    if ( init_flag == 1 )
        std::construct_at ( &type_storage,  std::move(init.type_storage) );
    else
        std::construct_at ( &other_storage, std::move(init.other_storage), init_flag - 1 );
}

template < class type, class... types >
constexpr aux::union_of<type,types...>::union_of ( auto init )
    requires aux::same_as_only_one_of<decay<decltype(init)>,type,types...>
{
    if constexpr ( std::same_as<decltype(init),type> )
        std::construct_at ( &type_storage,  std::move(init) );
    else
        std::construct_at ( &other_storage, std::move(init) );
}

template < class type, class... types >
constexpr aux::union_of<type,types...>::union_of ( const auto& init )
    requires aux::not_same_but_convertible_to_only_one_of<decay<decltype(init)>,type,types...>
{
    if constexpr ( std::convertible_to<decay<decltype(init)>,type> )
        std::construct_at ( &type_storage,  init );
    else
        std::construct_at ( &other_storage, init );
}

template < class type, class... types >
constexpr aux::union_of<type,types...>::union_of ( const auto& init )
    requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(init)>,type,types...>
{
    if constexpr ( std::constructible_from<type,decay<decltype(init)>> )
        std::construct_at ( &type_storage,  init );
    else
        std::construct_at ( &other_storage, init );
}

template < class type, class... types >
constexpr aux::union_of<type,types...>::~union_of ( )
{

}

template < class type, class... types >
constexpr aux::union_of<type,types...>& aux::union_of<type,types...>::assign ( const union_of& right, int self_flag, int right_flag )
{
    if ( self_flag == 1 and right_flag == 1 )
        type_storage = right.type_storage;

    else if ( self_flag == 1 and right_flag != 1 )
    {
        clear ( self_flag );
        other_storage.assign ( right.other_storage, self_flag-1, right_flag-1 );
    }

    else if ( self_flag != 1 and right_flag == 1 )
    {
        clear ( self_flag );
        std::construct_at ( &type_storage, right.type_storage );
    }

    else /* if ( self_flag != 1 and right_flag != 1 ) */
        other_storage.assign ( right.other_storage, self_flag-1, right_flag-1 );

    return self;
}

template < class type, class... types >
constexpr aux::union_of<type,types...>& aux::union_of<type,types...>::assign ( union_of&& right, int self_flag, int right_flag )
{
    if ( self_flag == 1 and right_flag == 1 )
        type_storage = std::move(right.type_storage);

    else if ( self_flag == 1 and right_flag != 1 )
    {
        clear ( self_flag );
        other_storage.assign ( std::move(right.other_storage), self_flag-1, right_flag-1 );
    }

    else if ( self_flag != 1 and right_flag == 1 )
    {
        clear ( self_flag );
        std::construct_at ( &type_storage, std::move(right.type_storage) );
    }

    else /* if ( self_flag != 1 and right_flag != 1 ) */
        other_storage.assign ( std::move(right.other_storage), self_flag-1, right_flag-1 );

    return self;
}

template < class type, class... types >
constexpr aux::union_of<type,types...>& aux::union_of<type,types...>::assign ( auto right, int self_flag )
    requires aux::same_as_only_one_of<decay<decltype(right)>,type,types...>
{
    constexpr int right_flag = std::same_as<decltype(right),type> ? 1 otherwise 0;

    if ( self_flag == 1 )
        if constexpr ( right_flag == 1 )
            type_storage = std::move(right);
        else
        {
            clear ( self_flag );
            other_storage.assign ( std::move(right/*.other_storage*/), self_flag-1 /*, right_flag-1*/ );
        }

    else
        if constexpr ( right_flag == 1 )
        {
            clear ( self_flag );
            std::construct_at ( &type_storage, std::move(right) );
        }
        else
            other_storage.assign ( std::move(right/*.other_storage*/), self_flag-1 /*, right_flag-1*/ );

    return self;
}

template < class type, class... types >
constexpr aux::union_of<type,types...>& aux::union_of<type,types...>::assign ( const auto& right, int self_flag )
    requires aux::not_same_but_assignable_to_only_one_of<decay<decltype(right)>,type,types...>
{
    constexpr int right_flag = std::assignable_from<type&,decay<decltype(right)>> ? 1 otherwise 0;

    if ( self_flag == 1 )
        if constexpr ( right_flag == 1 )
            type_storage = right;
        else
        {
            clear ( self_flag );
            other_storage.assign ( right/*.other_storage*/, self_flag-1 /*, right_flag-1*/ );
        }

    else
        if constexpr ( right_flag == 1 )
        {
            clear ( self_flag );
            std::construct_at ( &type_storage, right );
        }
        else
            other_storage.assign ( right/*.other_storage*/, self_flag-1 /*, right_flag-1*/ );

    return self;

}

template < class type, class... types >
constexpr aux::union_of<type,types...>& aux::union_of<type,types...>::clear ( int self_flag )
{
    if ( self_flag == 1 )
        std::destroy_at ( &type_storage );
    else
        other_storage.clear ( self_flag - 1 );

    return self;
}

template < class type, class... types >
template < class result_type >
constexpr result_type& aux::union_of<type,types...>::get ( )
    requires aux::same_as_only_one_of<result_type,type,types...>
{
    if constexpr ( std::same_as<result_type,type> )
        return type_storage;
    else
        return other_storage.template get<result_type>();
}

template < class type, class... types >
template < class result_type >
constexpr const result_type& aux::union_of<type,types...>::get ( ) const
    requires aux::same_as_only_one_of<result_type,type,types...>
{
    if constexpr ( std::same_as<result_type,type> )
        return type_storage;
    else
        return other_storage.template get<result_type>();
}

template < class type, class... types >
constexpr decltype(auto) aux::union_of<type,types...>::visit ( auto&& visitor, int self_flag )
{
    if ( self_flag == 1 )
        return visitor ( type_storage );
    else
        return other_storage.visit ( std::move ( visitor ), self_flag - 1 );
}

template < class type, class... types >
constexpr decltype(auto) aux::union_of<type,types...>::visit ( auto&& visitor, int self_flag ) const
{
    if ( self_flag == 1 )
        return visitor ( type_storage );
    else
        return other_storage.visit ( std::move ( visitor ), self_flag - 1 );
}







/// Global

template < class... types >
    requires ( printable<types> and ... )
constexpr std::ostream& operator << ( std::ostream& left, const variant<types...>& right )
{
    let printer = [&] (const auto& val) { left << val; };
    right.visit(printer);
    return left;
}





/// Auxiliary

template < class type >
constexpr bool aux::all_different<type> = true;

template < class type, class... types >
constexpr bool aux::all_different<type,types...> = not ( std::same_as<type,types> or ... ) and all_different<types...>;


template < class input_type, class type, class... types >
constexpr bool aux::same_as_only_one_of<input_type,type,types...> = aux::all_different<type,types...> and ( std::same_as<input_type,type> or ... or std::same_as<input_type,types> );


template < class input_type, class type >
constexpr bool aux::not_same_but_convertible_to_only_one_of<input_type,type> = not std::same_as<input_type,type> but std::convertible_to<input_type,type>;

template < class input_type, class type, class... types >
constexpr bool aux::not_same_but_convertible_to_only_one_of<input_type,type,types...> = not ( std::same_as<input_type,type> or ... or std::same_as<input_type,types> )
                                                                                        but ( std::convertible_to<input_type,type> != not_same_but_convertible_to_only_one_of<input_type,types...> );

template < class input_type, class type >
constexpr bool aux::not_convertible_but_constructible_to_only_one_of<input_type,type> = not std::convertible_to<input_type,type> but std::constructible_from<type,input_type>;

template < class input_type, class type, class... types >
constexpr bool aux::not_convertible_but_constructible_to_only_one_of<input_type,type,types...> = not ( std::convertible_to<input_type,type> or ... or std::convertible_to<input_type,types> )
                                                                                                 but ( std::constructible_from<type,input_type> != not_convertible_but_constructible_to_only_one_of<input_type,types...> );

template < class input_type, class type >
constexpr bool aux::not_same_but_assignable_to_only_one_of<input_type,type> = not std::same_as<input_type,type> but std::assignable_from<type&,input_type>;

template < class input_type, class type, class... types >
constexpr bool aux::not_same_but_assignable_to_only_one_of<input_type,type,types...> = not ( std::same_as<input_type,type> or ... or std::same_as<input_type,types> )
                                                                                       but ( std::assignable_from<type&,input_type> != not_same_but_assignable_to_only_one_of<input_type,types...> );

template < class input_type, class type, class... types >
constexpr bool aux::not_assignable_to_any_of<input_type,type,types...> = not ( std::assignable_from<type&,input_type> or ... or std::assignable_from<types&,input_type> );


template < class input_type, class type >
constexpr int aux::index_of_unique_same_type<input_type,type> = std::same_as<input_type,type> ? 1 otherwise 0;

template < class input_type, class type, class... types >
constexpr int aux::index_of_unique_same_type<input_type,type,types...> = std::same_as<input_type,type>                       ? 1 otherwise
                                                                         index_of_unique_same_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                               1 + index_of_unique_same_type<input_type,types...>;

template < class input_type, class type >
constexpr int aux::index_of_unique_convertible_type<input_type,type> = std::convertible_to<input_type,type> ? 1 otherwise 0;

template < class input_type, class type, class... types >
constexpr int aux::index_of_unique_convertible_type<input_type,type,types...> = std::convertible_to<input_type,type>                       ? 1 otherwise
                                                                                index_of_unique_convertible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                             1 + index_of_unique_convertible_type<input_type,types...>;
template < class input_type, class type >
constexpr int aux::index_of_unique_constructible_type<input_type,type> = std::constructible_from<type,input_type> ? 1 otherwise 0;

template < class input_type, class type, class... types >
constexpr int aux::index_of_unique_constructible_type<input_type,type,types...> = std::constructible_from<type,input_type>                     ? 1 otherwise
                                                                                  index_of_unique_constructible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                                 1 + index_of_unique_constructible_type<input_type,types...>;
template < class input_type, class type >
constexpr int aux::index_of_unique_assignable_type<input_type,type> = std::assignable_from<type&,input_type> ? 1 otherwise 0;

template < class input_type, class type, class... types >
constexpr int aux::index_of_unique_assignable_type<input_type,type,types...> = std::assignable_from<type&,input_type>                     ? 1 otherwise
                                                                               index_of_unique_assignable_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                           1 + index_of_unique_assignable_type<input_type,types...>;


template < class input_type, class type >
constexpr bool aux::all_invocable_and_returns_same_type<input_type,type> = std::invocable<input_type,type>;

template < class input_type, class type, class... types >
constexpr bool aux::all_invocable_and_returns_same_type<input_type,type,types...> = []
{
    if constexpr ( ( std::invocable<input_type,type > and ... and std::invocable<input_type,types> ) )
        return ( std::same_as<invoke_result<input_type,type>,invoke_result<input_type,types>> and ... );
    else
        return false;
} ();