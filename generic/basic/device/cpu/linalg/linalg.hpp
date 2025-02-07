#pragma once

// constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
// {
//     using device = left_device_type;
//     let output = array<multiply_result<left_value_type,right_value_type>,2,device>;
    
//     int left_tag = left.is_contiguous() ? 0 otherwise left.is_strided() ? 1 otherwise 2;
//     int right_tag 

//     if ( left.is_contiguous() and right.is_contiguous() )
//         device::linalg::multiply(left.mdspan(), right.mdspan(), output.mdspan());

//     else if ( left.is_contiguous() and not right.is_contiguous() )
//         if ( right.is_strided() )
//             device::linalg::multiply(left.mdspan(), right.mdspan_strided(), output.mdspan());
//         else // if ( not right.is_strided() )
//             device::linalg::multiply(left.mdspan(), right.mdspan_transposed(), output.mdspan());

//     else if ( not left.is_contiguous() and right.is_contiguous() )
//         if ( left.is_strided() )
//             device::linalg::multiply(left.mdspan_strided(), right.mdspan(), output.mdspan());
//         else // if ( not left.is_strided() )
//             device::linalg::multiply(left.mdspan_transposed(), right.mdspan(), output.mdspan());

//     else // if ( not left.is_contiguous() and not right.is_contiguous() )
//         if ( left.is_strided() and right.is_strided() )
//             device::linalg::multiply(left.mdspan_strided(), right.mdspan_strided(), output.mdspan());
//         else if ( left.is_strided() and not right.is_strided() )
//             device::linalg::multiply(left.mdspan_strided(), right.mdspan_transposed(), output.mdspan());
//         else if ( not left.is_strided() and right.is_strided() )
//             device::linalg::multiply(left.mdspan_transposed(), right.mdspan_strided(), output.mdspan());
//         else // if ( not left.is_strided() and not right.tranposed() )
//             device::linalg::multiply(left.mdspan_transposed(), right.mdspan_transposed(), output.mdspan());

//     return output;
// }

constexpr void cpu::linalg::multiply ( auto left, auto right, auto output )
{
    print(left.get_size_top());
 //   detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right);
}




