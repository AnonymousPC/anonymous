#pragma once

template < ap::string_type type >
constexpr auto std::hash<type>::operator() ( const type& str ) const
{   
    return type::device_type::template hash<typename type::device_type::template basic_string_view<typename type::value_type>>::operator()
                                           (typename type::device_type::template basic_string_view<typename type::value_type>(str.data(), str.size()));
}