#pragma once

constexpr array_type auto operator + ( const array_type auto& right )
    requires number_type<right_value_type> or complex_type<right_value_type>
{
    using device        = right_device_type;
    using value_type    = decltype(+std::declval<right_value_type>());
    let   output        = array<value_type,right_dimension,device>().resize(right.shape());
    let   right_mdspan  = right .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( right_mdspan.index() )
    {
        case 1: device::linalg::unary_plus(right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::unary_plus(right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::unary_plus(right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator - ( const array_type auto& right )
    requires number_type<right_value_type> or complex_type<right_value_type>
{
    using device        = right_device_type;
    using value_type    = decltype(-std::declval<right_value_type>());
    let   output        = array<value_type,right_dimension,device>().resize(right.shape());
    let   right_mdspan  = right .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( right_mdspan.index() )
    {
        case 1: device::linalg::unary_minus(right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::unary_minus(right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::unary_minus(right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator + ( const array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.shape() != right.shape() )
        throw linalg_error("plus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device        = left_device_type;
    using value_type    = decltype(std::declval<left_value_type>() + std::declval<right_value_type>());
    let   output        = array<value_type,left_dimension,device>().resize(left.shape());
    let   left_mdspan   = left  .mdspan();
    let   right_mdspan  = right .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( 3 * left_mdspan.index() + right_mdspan.index() - 3 )
    {
        case 1: device::linalg::plus(left_mdspan.template value<1>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::plus(left_mdspan.template value<1>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::plus(left_mdspan.template value<1>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 4: device::linalg::plus(left_mdspan.template value<2>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 5: device::linalg::plus(left_mdspan.template value<2>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 6: device::linalg::plus(left_mdspan.template value<2>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 7: device::linalg::plus(left_mdspan.template value<3>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 8: device::linalg::plus(left_mdspan.template value<3>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 9: device::linalg::plus(left_mdspan.template value<3>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator - ( const array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.shape() != right.shape() )
        throw linalg_error("minus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device        = left_device_type;
    using value_type    = decltype(std::declval<left_value_type>() - std::declval<right_value_type>());
    let   output        = array<value_type,left_dimension,device>().resize(left.shape());
    let   left_mdspan   = left  .mdspan();
    let   right_mdspan  = right .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( 3 * left_mdspan.index() + right_mdspan.index() - 3 )
    {
        case 1: device::linalg::minus(left_mdspan.template value<1>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::minus(left_mdspan.template value<1>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::minus(left_mdspan.template value<1>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 4: device::linalg::minus(left_mdspan.template value<2>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 5: device::linalg::minus(left_mdspan.template value<2>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 6: device::linalg::minus(left_mdspan.template value<2>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 7: device::linalg::minus(left_mdspan.template value<3>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 8: device::linalg::minus(left_mdspan.template value<3>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 9: device::linalg::minus(left_mdspan.template value<3>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator * ( const auto& left, const array_type auto& right )
    requires ( number_type<left_type> or complex_type<left_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> )
{    
    using device        = right_device_type;
    using value_type    = decltype(std::declval<left_type>() * std::declval<right_value_type>());
    let   output        = array<value_type,right_dimension,device>().resize(right.shape());
    let   right_mdspan  = right .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( right_mdspan.index() )
    {
        case 1: device::linalg::left_scale(left, right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::left_scale(left, right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::left_scale(left, right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator * ( const array_type auto& left, const auto& right )
    requires ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type> or complex_type<right_type> )
{    
    using device        = left_device_type;
    using value_type    = decltype(std::declval<left_value_type>() * std::declval<right_type>());
    let   output        = array<value_type,left_dimension,device>().resize(left.shape());
    let   left_mdspan   = left  .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( left_mdspan.index() )
    {
        case 1: device::linalg::right_scale(left_mdspan.template value<1>(), right, output_mdspan.template value<1>()); break;
        case 2: device::linalg::right_scale(left_mdspan.template value<2>(), right, output_mdspan.template value<1>()); break;
        case 3: device::linalg::right_scale(left_mdspan.template value<3>(), right, output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == 2 and right_dimension == 2 ) and
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.column() != right.row() )
        throw linalg_error("multiply matrix with inconsistent column and row (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device        = left_device_type;
    using value_type    = decltype(std::declval<left_value_type>() * std::declval<right_value_type>());
    let   output        = array<value_type,2,device>(left.row(), right.column());
    let   left_mdspan   = left  .mdspan();
    let   right_mdspan  = right .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( 3 * left_mdspan.index() + right_mdspan.index() - 3 )
    {
        case 1: device::linalg::multiply(left_mdspan.template value<1>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::multiply(left_mdspan.template value<1>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::multiply(left_mdspan.template value<1>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 4: device::linalg::multiply(left_mdspan.template value<2>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 5: device::linalg::multiply(left_mdspan.template value<2>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 6: device::linalg::multiply(left_mdspan.template value<2>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 7: device::linalg::multiply(left_mdspan.template value<3>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 8: device::linalg::multiply(left_mdspan.template value<3>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 9: device::linalg::multiply(left_mdspan.template value<3>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto operator / ( const array_type auto& left, const auto& right )
    requires ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type> or complex_type<right_type> )
{    
    using device        = left_device_type;
    using value_type    = decltype(std::declval<left_value_type>() / std::declval<right_type>());
    let   output        = array<value_type,left_dimension,device>().resize(left.shape());
    let   left_mdspan   = left  .mdspan();
    let   output_mdspan = output.mdspan();

    switch ( left_mdspan.index() )
    {
        case 1: device::linalg::divide(left_mdspan.template value<1>(), right, output_mdspan.template value<1>()); break;
        case 2: device::linalg::divide(left_mdspan.template value<2>(), right, output_mdspan.template value<1>()); break;
        case 3: device::linalg::divide(left_mdspan.template value<3>(), right, output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return output;
}

constexpr array_type auto& operator += ( array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.shape() != right.shape() )
        throw linalg_error("plus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device       = left_device_type;
    let   left_mdspan  = left .mdspan();
    let   right_mdspan = right.mdspan();

    switch ( 3 * left_mdspan.index() + right_mdspan.index() - 3 )
    {
        case 1: device::linalg::plus_equal(left_mdspan.template value<1>(), right_mdspan.template value<1>()); break;
        case 2: device::linalg::plus_equal(left_mdspan.template value<1>(), right_mdspan.template value<2>()); break;
        case 3: device::linalg::plus_equal(left_mdspan.template value<1>(), right_mdspan.template value<3>()); break;
        case 4: device::linalg::plus_equal(left_mdspan.template value<2>(), right_mdspan.template value<1>()); break;
        case 5: device::linalg::plus_equal(left_mdspan.template value<2>(), right_mdspan.template value<2>()); break;
        case 6: device::linalg::plus_equal(left_mdspan.template value<2>(), right_mdspan.template value<3>()); break;
        case 7: device::linalg::plus_equal(left_mdspan.template value<3>(), right_mdspan.template value<1>()); break;
        case 8: device::linalg::plus_equal(left_mdspan.template value<3>(), right_mdspan.template value<2>()); break;
        case 9: device::linalg::plus_equal(left_mdspan.template value<3>(), right_mdspan.template value<3>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return left;
}

constexpr array_type auto& operator -= ( array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == right_dimension ) and 
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.shape() != right.shape() )
        throw linalg_error("minus array with inconsistent shape (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device       = left_device_type;
    let   left_mdspan  = left .mdspan();
    let   right_mdspan = right.mdspan();

    switch ( 3 * left_mdspan.index() + right_mdspan.index() - 3 )
    {
        case 1: device::linalg::minus_equal(left_mdspan.template value<1>(), right_mdspan.template value<1>()); break;
        case 2: device::linalg::minus_equal(left_mdspan.template value<1>(), right_mdspan.template value<2>()); break;
        case 3: device::linalg::minus_equal(left_mdspan.template value<1>(), right_mdspan.template value<3>()); break;
        case 4: device::linalg::minus_equal(left_mdspan.template value<2>(), right_mdspan.template value<1>()); break;
        case 5: device::linalg::minus_equal(left_mdspan.template value<2>(), right_mdspan.template value<2>()); break;
        case 6: device::linalg::minus_equal(left_mdspan.template value<2>(), right_mdspan.template value<3>()); break;
        case 7: device::linalg::minus_equal(left_mdspan.template value<3>(), right_mdspan.template value<1>()); break;
        case 8: device::linalg::minus_equal(left_mdspan.template value<3>(), right_mdspan.template value<2>()); break;
        case 9: device::linalg::minus_equal(left_mdspan.template value<3>(), right_mdspan.template value<3>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return left;
}

constexpr array_type auto& operator *= ( array_type auto& left, const auto& right )
    requires ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type> or complex_type<right_type> )
{   
    using device       = left_device_type;
    let   left_mdspan  = left .mdspan();
    let   right_mdspan = right.mdspan();

    switch ( left_mdspan.index() )
    {
        case 1: device::linalg::right_scale_equal(left_mdspan.template value<1>(), right); break;
        case 2: device::linalg::right_scale_equal(left_mdspan.template value<2>(), right); break;
        case 3: device::linalg::right_scale_equal(left_mdspan.template value<3>(), right); break;
        default: throw linalg_error("invalid mdspan");
    }

    return left;
}

constexpr array_type auto& operator * ( array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == 2 and right_dimension == 2 ) and
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.column() != right.row() )
        throw linalg_error("multiply matrix with inconsistent column and row (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device       = left_device_type;
    let   left_mdspan  = left  .mdspan();
    let   right_mdspan = right .mdspan();

    switch ( 3 * left_mdspan.index() + right_mdspan.index() - 3 )
    {
        case 1: device::linalg::multiply_equal(left_mdspan.template value<1>(), right_mdspan.template value<1>()); break;
        case 2: device::linalg::multiply_equal(left_mdspan.template value<1>(), right_mdspan.template value<2>()); break;
        case 3: device::linalg::multiply_equal(left_mdspan.template value<1>(), right_mdspan.template value<3>()); break;
        case 4: device::linalg::multiply_equal(left_mdspan.template value<2>(), right_mdspan.template value<1>()); break;
        case 5: device::linalg::multiply_equal(left_mdspan.template value<2>(), right_mdspan.template value<2>()); break;
        case 6: device::linalg::multiply_equal(left_mdspan.template value<2>(), right_mdspan.template value<3>()); break;
        case 7: device::linalg::multiply_equal(left_mdspan.template value<3>(), right_mdspan.template value<1>()); break;
        case 8: device::linalg::multiply_equal(left_mdspan.template value<3>(), right_mdspan.template value<2>()); break;
        case 9: device::linalg::multiply_equal(left_mdspan.template value<3>(), right_mdspan.template value<3>()); break;
        default: throw linalg_error("invalid mdspan");
    }

    return left;
}

constexpr array_type auto& operator /= ( array_type auto& left, const auto& right )
    requires ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_type> or complex_type<right_type> )
{   
    using device       = left_device_type;
    let   left_mdspan  = left .mdspan();
    let   right_mdspan = right.mdspan();

    switch ( left_mdspan.index() )
    {
        case 1: device::linalg::divide_equal(left_mdspan.template value<1>(), right); break;
        case 2: device::linalg::divide_equal(left_mdspan.template value<2>(), right); break;
        case 3: device::linalg::divide_equal(left_mdspan.template value<3>(), right); break;
        default: throw linalg_error("invalid mdspan");
    }

    return left;
}
