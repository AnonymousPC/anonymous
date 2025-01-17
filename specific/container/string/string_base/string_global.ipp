#pragma once

/// Global

constexpr std::istream& operator >> ( std::istream& left, string_type auto& right )
{
    std::string buff;
    left >> buff;
    right = string(buff);

    return left;
}

constexpr std::ostream& operator << ( std::ostream& left, const string_type auto& right )
{
    for ( auto ch in right )
        if constexpr ( std::same_as<right_value_type,char> )
            left << ch;
        else
            for ( int i in range ( sizeof(ch) ) )
                left << reinterpret_cast<char*>(&ch)[i-1];

    return left;
}

constexpr bool operator == ( const general_string_type auto& left, const general_string_type auto& right )
    requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>
{
    auto left_view  = basic_string_view(left);
    auto right_view = basic_string_view(right);

    return std::equal ( left_view.begin(), left_view.end(), right_view.begin(), right_view.end() );
}

constexpr auto operator <=> ( const general_string_type auto& left, const general_string_type auto& right )
    requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>
{
    auto left_view  = basic_string_view(left);
    auto right_view = basic_string_view(right);

    return std::lexicographical_compare_three_way ( left_view.begin(), left_view.end(), right_view.begin(), right_view.end() );
}

constexpr string_type auto operator + ( const general_string_type auto& left, const general_string_type auto& right )
    requires ( string_type<left_type> or string_type<right_type> ) and std::same_as<left_value_type,right_value_type>
{
    using char_type  = left_value_type;
    auto  left_view  = basic_string_view(left);
    auto  right_view = basic_string_view(right);

    basic_string<left_value_type> str ( left_view.size() + right_view.size(), char_type('\0') );
    std::copy ( left_view .begin(), left_view .end(), str.begin() );
    std::copy ( right_view.begin(), right_view.end(), str.begin() + left_view.size() );

    return str;
}

constexpr string_type auto& operator += ( general_string_type auto& left, const general_string_type auto& right )
    requires std::same_as<left_type,basic_string<left_value_type>> and std::same_as<left_value_type,right_value_type>
{
    auto  right_view = basic_string_view(right);

    int old_size = left.size();
    left.resize ( left.size() + right_view.size() );
    std::copy ( right_view.begin(), right_view.end(), left.begin() + old_size );

    return left;
}

constexpr string_type auto operator * ( const string_type auto& left, int_type auto right )
{
    using char_type = left_value_type;

    #if debug
        if ( right < 0 )
            throw value_error("multiply string with negative times {}", right);
    #endif

    basic_string<left_value_type> str ( left.size() * right, char_type('\0') );
    for ( auto i in range ( right ) )
        std::copy ( left.begin(), left.end(), str.begin() + left.size() * ( i - 1 ) );

    return str;
}

constexpr string_type auto operator * ( int_type auto left, const string_type auto& right )
{
    using char_type  = right_value_type;

    #if debug
        if ( left < 0 )
            throw value_error("multiply string with negative times {}", left);
    #endif

    basic_string<left_value_type> str ( left * right.size(), char_type('\0') );
    for ( auto i in range ( left ) )
        std::copy ( right.begin(), right.end(), str.begin() + right.size() * ( i - 1 ) );

    return str;
}

constexpr string_type auto& operator *= ( string_type auto& left, int_type auto right )
{    
    #if debug
        if ( right < 0 )
            throw value_error("multiply string with negative times {}", right);
    #endif

    int old_size = left.size();
    left.resize ( left.size() * right );
    for ( auto i in range ( 2, right ) )
        std::copy ( left.begin(), left.begin() + old_size, left.begin() + old_size * ( i - 1 ) );

    return left;
}






// Auxiliary (see string_algo.cpp)

namespace aux
{
    template < class type >
    struct string_view_type_helper
    {
        constexpr static const bool value = false;
    };

    template < class char_type >
    struct string_view_type_helper<basic_string_view<char_type>>
    {
        constexpr static const bool value = true;
    };

    template < class input_type >
    concept string_view_type = string_view_type_helper<input_type>::value;
}