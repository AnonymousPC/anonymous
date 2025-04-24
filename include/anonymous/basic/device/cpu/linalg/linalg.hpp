#include "detail/mapping.cpp"

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
    output = detail::eigen_map<decltype(output)>(left).dot(detail::eigen_map<decltype(output)>(right));
}

constexpr void cpu::linalg::fft ( const auto vector, auto output )
{
    /* Eigen::Map<const Eigen::Matrix> has bug in Eigen::FFT, as
     * eigen_map[index] returns a rvalue instead of const lvalue&.
     * So we must map it manually.
     */
    auto vector_map = [&]
        {
            if constexpr ( detail::is_contiguous_layout<vector_layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size());
            else // if constexpr ( detail::is_strided_layout<vector_layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size(), vector.stride(0));
        } ();
    auto output_map = detail::eigen_map(output);
    Eigen::FFT<detail::eigen_nativize<output_value_type::value_type>>().fwd(output_map, vector_map);
}

constexpr void cpu::linalg::ifft ( const auto vector, auto output )
{
    /* Eigen::Map<const Eigen::Matrix> has bug in Eigen::FFT, as
     * eigen_map[index] returns a rvalue instead of const lvalue&.
     * So we must map it manually.
     */
    auto vector_map = [&]
        {
            if constexpr ( detail::is_contiguous_layout<vector_layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size());
            else // if constexpr ( detail::is_strided_layout<vector_layout_type> )
                return Eigen::Map</*non-const*/Eigen::Vector<detail::eigen_nativize<vector_value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(const_cast<vector_value_type*>(vector.data_handle()), vector.size(), vector.stride(0));
        } ();
    auto output_map = detail::eigen_map(output);
    Eigen::FFT<detail::eigen_nativize<output_value_type::value_type>>().inv(output_map, vector_map);
}

constexpr void cpu::linalg::tensor ( const auto left, const auto right, auto output )
{
    detail::eigen_map(output).noalias() = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right).transpose();
}