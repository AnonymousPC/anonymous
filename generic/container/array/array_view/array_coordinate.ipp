#pragma once

/// Class array_coordinate

/// dim == 1

// Core

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr array_coordinate<dim,value_type>::array_coordinate ( value_type init )
    extends first ( std::move ( init ) )
{

}

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr array_coordinate<dim,value_type>::operator array<value_type> ( ) const
{
    return array<value_type> { first };
}

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr int array_coordinate<dim,value_type>::size ( )
{
    return dim;
}

// Member

template < int dim, class value_type >
    requires ( dim == 1 )
template < int index >
    requires ( index == 1 or index == -1 )
constexpr auto& array_coordinate<dim,value_type>::get ( )
{
    return first;
}

template < int dim, class value_type >
    requires ( dim == 1 )
template < int index >
    requires ( index == 1 or index == -1 )
constexpr const auto& array_coordinate<dim,value_type>::get ( ) const
{
    return first;
}

template < int dim, class value_type >
    requires ( dim == 1 )
template < int begin, int end >
    requires ( begin == 1 and end == -1 )
constexpr auto& array_coordinate<dim,value_type>::get ( )
{
    return self;
}

template < int dim, class value_type >
    requires ( dim == 1 )
template < int begin, int end >
    requires ( begin == 1 and end == -1 )
constexpr const auto& array_coordinate<dim,value_type>::get ( ) const
{
    return self;
}

// Algo

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr auto array_coordinate<dim,value_type>::exist ( const equalable_to<value_type> auto& val ) const
{
    return get<1>() == val;
}

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr auto array_coordinate<dim,value_type>::exist ( unary_pred<value_type> auto pred ) const
{
    return pred ( get<1>() );
}

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr auto array_coordinate<dim,value_type>::product ( ) const
{
    return get<1>();
}

template < int dim, class value_type >
    requires ( dim == 1 )
constexpr auto array_coordinate<dim,value_type>::product ( unary_op<value_type> auto op ) const
{
    return op ( get<1>() );
}





/// dim >= 2

// Core

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr array_coordinate<dim,value_type>::array_coordinate ( value_type init_first, auto... init_other )
    requires ( std::is_convertible<decltype(init_other),value_type>::value and ... and ( sizeof...(init_other) + 1 == dim ) )
    extends first ( std::move ( init_first ) ),
            other ( std::forward<decltype(init_other)>(init_other)... )
{

}

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr array_coordinate<dim,value_type>::operator array<value_type> ( ) const
{
    let arr = array<value_type>(size());
    operator_array_aux<1> ( arr, self );
    return arr;
}

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr int array_coordinate<dim,value_type>::size ( )
{
    return dim;
}

// Member

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int index >
    requires ( ( index >= -dim and index <= -1 ) or ( index >= 1 and index <= dim ) )
constexpr auto& array_coordinate<dim,value_type>::get ( )
{
    if constexpr ( index == 1 or index == -dim )
        return first;
    else if constexpr ( index > 0 )
        return other.template get<index-1>();
    else
        return other.template get<index>();
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int index >
    requires ( ( index >= -dim and index <= -1 ) or ( index >= 1 and index <= dim ) )
constexpr const auto& array_coordinate<dim,value_type>::get ( ) const
{
    if constexpr ( index == 1 or index == -dim )
        return first;
    else if constexpr ( index > 0 )
        return other.template get<index-1>();
    else
        return other.template get<index>();
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int begin, int end >
    requires ( begin == 1 and end == -1 )
constexpr auto& array_coordinate<dim,value_type>::get ( )
{
    return self;
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int begin, int end >
    requires ( begin == 1 and end == -1 )
constexpr const auto& array_coordinate<dim,value_type>::get ( ) const
{
    return self;
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int begin, int end >
    requires ( begin == 2 and end == -1 )
constexpr auto& array_coordinate<dim,value_type>::get ( )
{
    return other;
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int begin, int end >
    requires ( begin == 2 and end == -1 )
constexpr const auto& array_coordinate<dim,value_type>::get ( ) const
{
    return other;
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int begin, int end >
    requires ( begin >= 3 and end == -1 )
constexpr auto& array_coordinate<dim,value_type>::get ( )
{
    return other.template get<begin-1,end>();
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int begin, int end >
    requires ( begin >= 3 and end == -1 )
constexpr const auto& array_coordinate<dim,value_type>::get ( ) const
{
    return other.template get<begin-1,end>();
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int index >
    requires ( ( index >= -dim and index <= -1 ) or ( index >= 1 and index <= dim ) )
[[nodiscard]]
constexpr auto array_coordinate<dim,value_type>::pop ( ) const
{
    let poped = array_coordinate<dim-1,value_type>();
    pop_aux<index> ( poped, self );
    return poped;
}

// Algo

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr auto array_coordinate<dim,value_type>::exist ( const equalable_to<value_type> auto& val ) const
{
    return get<1>() == val and get<2,-1>().exist(val);
}

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr auto array_coordinate<dim,value_type>::exist ( unary_pred<value_type> auto pred ) const
{
    return pred ( get<1>() ) and get<2,-1>().exist(pred);
}

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr auto array_coordinate<dim,value_type>::product ( ) const
{
    return get<1>() * get<2,-1>().product();
}

template < int dim, class value_type >
    requires ( dim >= 2 )
constexpr auto array_coordinate<dim,value_type>::product ( unary_op<value_type> auto op ) const
{
    return op ( get<1>() ) * get<2,-1>().product(op);
}

// Auxiliary

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int index >
constexpr void array_coordinate<dim,value_type>::operator_array_aux ( auto& arr, const auto& coor )
{
    arr[index] = coor.template get<index>();

    if constexpr ( index < coor.size() )
        operator_array_aux<index+1> ( arr, coor );
}

template < int dim, class value_type >
    requires ( dim >= 2 )
template < int index >
constexpr void array_coordinate<dim,value_type>::pop_aux ( auto& poped, const auto& src )
{
    if constexpr ( index == 1 or index == - src.size() )
        if constexpr ( src.size() == 1 )
            return;
        else
            return pop_aux<0> ( poped, src.template get<2,-1>() );
    else
    {
        poped.template get<1>() = src.template get<1>();

        if constexpr ( poped.size() >= 2 )
        {
            if constexpr ( index > 0 )
                pop_aux<index-1> ( poped.template get<2,-1>(), src.template get<2,-1>() );
            else
                pop_aux<index>   ( poped.template get<2,-1>(), src.template get<2,-1>() );
        }
    }
}