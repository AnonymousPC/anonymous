#pragma once

#define left_type                  decay<decltype(left  )>
#define left_value_type   typename decay<decltype(left  )>::value_type
#define vector_type                decay<decltype(vector)>
#define vector_value_type typename decay<decltype(vector)>::value_type
#define output_type                decay<decltype(output)>
#define output_value_type typename decay<decltype(output)>::value_type

#include "detail.hpp"

constexpr void cpu::linalg::unary_plus ( const auto right, auto output )
{
    detail::eigen_map(output).noalias() = + detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::unary_minus ( const auto right, auto output )
{
    detail::eigen_map(output).noalias() = - detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::plus ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) + detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::minus ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) - detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::left_scale ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = left * detail::eigen_map(right);
}

constexpr void cpu::linalg::right_scale ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) * right;
}

constexpr void cpu::linalg::multiply ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right);
}

constexpr void cpu::linalg::divide ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) / right;
}

constexpr void cpu::linalg::plus_equal ( auto left, const auto right, auto /*output*/ )
{
    detail::eigen_map(left) += detail::eigen_map<left_value_type>(right);
}

constexpr void cpu::linalg::minus_equal ( auto left, const auto right, auto /*output*/ )
{
    detail::eigen_map(left) -= detail::eigen_map<left_value_type>(right);
}

constexpr void cpu::linalg::right_scale_equal ( auto left, const auto right, auto /*output*/ )
{
    detail::eigen_map(left) *= right;
}

constexpr void cpu::linalg::multiply_equal ( auto left, const auto right, auto /*output*/ )
{
    detail::eigen_map(left) *= detail::eigen_map<left_value_type>(right);
}

constexpr void cpu::linalg::divide_equal ( auto left, const auto right, auto /*output*/ )
{
    detail::eigen_map(left) /= right;
}




constexpr void cpu::linalg::convolve ( const auto left, const auto right, auto output )
{
    detail::eigen_map<void,detail::eigen_map_tensor>(output) = detail::eigen_map<output_value_type,detail::eigen_map_tensor>(left).convolve(detail::eigen_map<output_value_type,detail::eigen_map_tensor>(right), detail::eigen_make_convolve_full_dims<decltype(left)::extents_type::rank()>());
}

constexpr void cpu::linalg::cross ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left).cross(detail::eigen_map<output_value_type>(right));
}

constexpr void cpu::linalg::dot ( const auto left, const auto right, auto output )
{
    output = detail::eigen_map<output_type>(left).dot(detail::eigen_map<output_type>(right));
}

constexpr void cpu::linalg::fft ( const auto vector, auto output )
{
    /* Eigen::Map<const Eigen::Matrix> has bug in Eigen::FFT, as
     * eigen_map[index] returns a rvalue instead of const lvalue&.
     * So we must map it manually.
     */
    let vector_map = [&]
        {
            if constexpr ( detail::is_contiguous_layout<typename decay<decltype(vector)>::layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size());
            else // if constexpr ( detail::is_strided_layout<typename decay<decltype(vector)>::layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size(), vector.stride(0));
        } ();
    let output_map = detail::eigen_map(output);
    Eigen::FFT<detail::eigen_nativize<output_value_type::value_type>>().fwd(output_map, vector_map);
}

constexpr void cpu::linalg::ifft ( const auto vector, auto output )
{
    /* Eigen::Map<const Eigen::Matrix> has bug in Eigen::FFT, as
     * eigen_map[index] returns a rvalue instead of const lvalue&.
     * So we must map it manually.
     */
    let vector_map = [&]
        {
            if constexpr ( detail::is_contiguous_layout<typename decay<decltype(vector)>::layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size());
            else // if constexpr ( detail::is_strided_layout<typename decay<decltype(vector)>::layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size(), vector.stride(0));
        } ();
    let output_map = detail::eigen_map(output);
    Eigen::FFT<detail::eigen_nativize<output_value_type::value_type>>().inv(output_map, vector_map);
}

constexpr void cpu::linalg::tensor ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right).transpose();
}

#undef left_type
#undef left_value_type
#undef vector_type
#undef vector_value_type
#undef output_type
#undef output_value_type