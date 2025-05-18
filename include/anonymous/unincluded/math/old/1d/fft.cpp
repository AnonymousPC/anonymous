constexpr array_type auto fft ( const array_type auto& vector )
    requires ( vector.dimension() == 1 ) and ( numeric<vector_value_type> or complex_type<vector_value_type> )
{
    if constexpr ( integral<vector_value_type> or complex_int_type<vector_value_type> )
        return fft ( vector.template as_type<int_to_float_type<vector_value_type>>() );
    else if constexpr ( floating_point<vector_value_type> or complex_float_type<vector_value_type> )
    {
        try
        {
            if constexpr ( floating_point<vector_value_type> )
            {
                auto a = aux::to_eigen(vector);
                auto b = Eigen::Vector<std::complex<vector_value_type>,Eigen::Dynamic>(a.size());
                Eigen::FFT<vector_value_type>().fwd(b, a);
                return aux::from_eigen(b);
            }
            else if constexpr ( complex_float_type<vector_value_type> )
            {
                auto a = aux::to_eigen(vector);
                auto b = Eigen::Vector<std::complex<vector_value_type::value_type>,Eigen::Dynamic>(a.size());
                Eigen::FFT<vector_value_type::value_type>().fwd(b, a);
                return aux::from_eigen(b);
            }
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot fft vector [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}

constexpr array_type auto ifft ( const array_type auto& vector )
    requires ( vector.dimension() == 1 ) and ( numeric<vector_value_type> or complex_type<vector_value_type> )
{
    if constexpr ( integral<vector_value_type> )
        return ifft ( vector.template as_type<complex<int_to_float_type<vector_value_type>>>() );
    else if constexpr ( floating_point<vector_value_type> )
        return ifft ( vector.template as_type<complex<vector_value_type>>() );
    else if constexpr ( complex_int_type<vector_value_type> )
        return ifft ( vector.template as_type<int_to_float_type<vector_value_type>>() );
    else if constexpr ( complex_float_type<vector_value_type> )
    {
        try
        {
            auto a = aux::to_eigen(vector);
            auto b = Eigen::Vector<std::complex<vector_value_type::value_type>,Eigen::Dynamic>(a.size());
            Eigen::FFT<vector_value_type::value_type>().inv(b, a);
            return aux::from_eigen(b);
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot ifft vector [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}