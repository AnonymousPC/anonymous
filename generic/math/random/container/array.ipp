#pragma once

// Declared in "root/array/array_base/array_algo_1d.cpp"
//             "root/array/array_base/array_algo_nd.cpp"

template < class array_type, class value_type, class iterate_type, int dim >
    requires ( dim == 1 )
constexpr array_type& array_algo<array_type,value_type,iterate_type,dim>::sample ( int n )
    requires ( not is_view ) and std::copyable<value_type>
{
    #if debug
        if ( n < 0 or n > size() )
            throw value_error("cannot sample {} elements from array with size {}", n, size());
    #endif // debug

    array_type arr = array_type().resize(n); // As string_type conflicts in array_type(n).

    std::sample ( begin(), end(), arr.begin(), n, global_random_engine );

    return static_cast<array_type&>(self) = arr;
}

template < class array_type, class value_type, class iterate_type, int dim >
    requires ( dim == 1 )
constexpr array_type& array_algo<array_type,value_type,iterate_type,dim>::shuffle ( )
{
    std::shuffle ( begin(), end(), global_random_engine );

    return static_cast<array_type&>(self);
}