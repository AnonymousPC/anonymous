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

} // namespace detail

#if dll
    #include "detail.cpp"
#endif
