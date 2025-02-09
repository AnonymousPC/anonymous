#pragma once

namespace detail
{
    template < class input_type >
    struct opencl_nativize_helper
    {
        using type = input_type;
    };

    template < complex_type input_type >
    struct opencl_nativize_helper<input_type>
    {
        using type = std::complex<typename input_type::value_type>;
    };

    template < class type >
    using opencl_nativize = opencl_nativize_helper<type>::type;

    std::string clblast_error_message ( clblast::StatusCode c ); // See detail.cpp

    void opencl_copy_mdspan ( const auto left, const auto output )
    {
        let status =
            clblast::Copy<detail::opencl_nativize<output_value_type>>(
                left.size(),
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), not detail::is_strided_layout<left_layout_type> ? 1 otherwise left.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("clblast error (with code = {}, message = {})", int(status), detail::clblast_error_message(status));
    }

    void opencl_add_scaled_mdspan_inplace ( auto scale, const auto right, const auto output )
    {
        let status = 
            clblast::Axpy<detail::opencl_nativize<output_value_type>>(
                right.size(), 
                scale,
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), not detail::is_strided_layout<right_layout_type> ? 1 otherwise right.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
    if ( status != clblast::StatusCode::kSuccess )
        throw opencl_error("clblast error (with code = {}, message = {})", int(status), detail::clblast_error_message(status));
    }

} // namespace detail

#if dll
    #include "detail.cpp"
#endif
