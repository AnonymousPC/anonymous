#pragma once

/// Class property_tree

// Core

template < class... types >
constexpr property_tree<types...>::property_tree ( auto val )
    requires aux::same_as_only_one_of<decay<decltype(val)>,types...>
    extends data ( new decltype(val) ( std::forward<decltype(val)>(val) ) )
{

}

template < class... types >
constexpr property_tree<types...>::property_tree ( const auto& val )
    requires aux::not_same_but_convertible_to_only_one_of<decay<decltype(val)>,types...>
    extends data ( new index_type_of<aux::index_of_unique_convertible_type<decay<decltype(val)>,types...>,types...> ( val ) )
{

}

template < class... types >
constexpr property_tree<types...>::property_tree ( const auto& val )
    requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(val)>,types...>
    extends data ( new index_type_of<aux::index_of_unique_constructible_type<decay<decltype(val)>,types...>,types...> ( val ) )
{

}

template < class... types >
constexpr property_tree<types...>& property_tree<types...>::operator = ( auto val )
    requires aux::same_as_only_one_of<decay<decltype(val)>,types...>
{
    self.data = new index_type_of<aux::index_of_unique_same_type<decay<decltype(val)>,types...>,types...> ( std::forward<decltype(val)>(val) );
    return self;
}

template < class... types >
constexpr property_tree<types...>& property_tree<types...>::operator = ( const auto& val )
    requires aux::not_same_but_assignable_to_only_one_of<decay<decltype(val)>,types...>
{
    self.data = new index_type_of<aux::index_of_unique_assignable_type<decay<decltype(val)>,types...>,types...> ( index_type_of<aux::index_of_unique_assignable_type<decay<decltype(val)>,types...>,types...>() = val );
    return self;
}

// Operator

template < class... types >
template < class result_type >
constexpr property_tree<types...>::operator result_type& ( )
    requires aux::same_as_only_one_of<result_type,types...>
{
    try
    {
        return *static_cast<result_type*>(data);
    }
    catch ( const type_error& e )
    {
        throw type_error("bad property_tree access: cannot get {} from {} (in which type == {}, index == {})",
                         typeid(result_type), typeid(self), type() == 0 ? string(typeid(void)) otherwise string(*array{&(typeid(types))...}[self.type()]), self.type());
    }
}

template < class... types >
template < class result_type >
constexpr property_tree<types...>::operator const result_type& ( ) const
    requires aux::same_as_only_one_of<result_type,types...>
{
    try
    {
        return *static_cast<const result_type*>(data);
    }
    catch ( const type_error& e )
    {
        throw type_error("bad property_tree access: cannot get {} from {} (in which type == {}, index == {})",
                         typeid(result_type), typeid(self), type() == 0 ? string(typeid(void)) otherwise string(*array{&(typeid(types))...}[self.type()]), self.type());
    }
}

// Member

template < class... types >
constexpr int property_tree<types...>::type ( ) const
{
    return data.type();
}

template < class... types >
constexpr decltype(auto) property_tree<types...>::visit ( auto&& visitor )
    requires aux::all_invocable_and_returns_same_type<decltype(visitor),types&...>
{
    return data.visit([&] (auto* ptr) { return std::move(visitor)(*ptr); });
}

template < class... types >
constexpr decltype(auto) property_tree<types...>::visit ( auto&& visitor ) const
    requires aux::all_invocable_and_returns_same_type<decltype(visitor),const types&...>
{
    return data.visit([&] (auto* ptr) { return std::move(visitor)(*ptr); });
}



/// Auxilairy

template < class type >
class aux::auto_ptr
{
    private: // Data
        type* ptr = nullptr;

    public: // Core
        constexpr  auto_ptr ( ) = default;
        constexpr  auto_ptr ( type* );
        constexpr  auto_ptr ( const auto_ptr&  )             requires std::copyable<type>;
        constexpr  auto_ptr (       auto_ptr&& );
        constexpr ~auto_ptr ( );
        constexpr  auto_ptr& operator = ( const auto_ptr&  ) requires std::copyable<type>;
        constexpr  auto_ptr& operator = (       auto_ptr&& );

    public: // Interface
        constexpr type& operator *  ( ) const;
        constexpr type* operator -> ( ) const;
};

template < class type >
constexpr aux::auto_ptr<type>::auto_ptr ( type* init )
    extends ptr ( init )
{

}

template < class type >
constexpr aux::auto_ptr<type>::auto_ptr ( const auto_ptr& init )
    requires std::copyable<type>
    extends ptr ( new type ( *init ) )
{

}

template < class type >
constexpr aux::auto_ptr<type>::auto_ptr ( auto_ptr&& init )
    extends ptr ( std::exchange ( init.ptr, nullptr ) )
{

}

template < class type >
constexpr aux::auto_ptr<type>::~auto_ptr ( )
{
    delete ptr;
}

template < class type >
constexpr aux::auto_ptr<type>& aux::auto_ptr<type>::operator = ( const auto_ptr& right )
    requires std::copyable<type>
{
    if ( std::movable<decay<decltype(right)>> and ptr != nullptr )
        *ptr = *right;
    else
        ptr = new type ( *right );
    return self;
}

template < class type >
constexpr aux::auto_ptr<type>& aux::auto_ptr<type>::operator = ( auto_ptr&& right )
{
    std::swap ( self.ptr, right.ptr );
    return self;
}

template < class type >
constexpr type& aux::auto_ptr<type>::operator * ( ) const
{
    return *ptr;
}

template < class type >
constexpr type* aux::auto_ptr<type>::operator -> ( ) const
{
    return ptr;
}