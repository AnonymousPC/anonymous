#pragma once

template < int_type auto version >
constexpr array_type auto dct ( const array_type auto& vector )
    requires ( vector.dimension() == 1 ) and number_type<vector_value_type>
{
    if constexpr ( int_type<vector_value_type> )
        return dct<version> ( vector.template as_type<int_to_float_type<vector_value_type>>() );
    else if constexpr ( float_type<vector_value_type> )
    {
        if constexpr ( version == 1 )
        {
            static_assert(false, "This algorithm does not work... Fix it, and compare the results to python.scipy.fftpack.dct(arr, type=1, norm='ortho')");
            // This algorithm requries normalization within each step in calculation.
            auto arr = array(vector.size(), [&] (int k)
                        {
                            auto s = vector_value_type(0);
                            for ( int n in range(1, vector.size()) )
                                s += vector[n] * cos(radian(pi * (k-1) * (n-1) / (vector.size()-1)));
                            return s;
                        });
            arr[1]    *= sqrt(1.0 / (arr.size()-1));
            arr[-1]   *= sqrt(1.0 / (arr.size()-1));
            arr[2,-2] *= sqrt(2.0 / (arr.size()-1));
            return arr;
        }

        else if constexpr ( version == 2 ) // TODO: accelerate with fft.
        {
            auto arr = array(vector.size(), [&] (int k)
                        {
                            auto s = vector_value_type(0);
                            for ( int n in range(1, vector.size()) )
                                s += vector[n] * cos(radian(pi * (n-0.5) * (k-1) / vector.size()));
                            return s;
                        });
            arr[1]    *= sqrt(1.0 / arr.size());
            arr[2,-1] *= sqrt(2.0 / arr.size());
            return arr;
        }

        else if constexpr ( version == 3 ) // Usually treated as inverse of dct<2>
        {
            // This algorithm requries normalization within each step in calculation.
            auto norm_1 = sqrt(1.0 / vector.size());
            auto norm_n = sqrt(2.0 / vector.size());
            auto arr = array(vector.size(), [&] (int n)
                        {
                            auto s = vector_value_type(0);
                            for ( int k in range(1, vector.size()) )
                                s += vector[k] * cos(radian(pi * (n-0.5) * (k-1) / vector.size())) * (k == 1 ? norm_1 : norm_n);
                            return s;
                        });
            return arr;
        }

        else if constexpr ( version == 4 )
        {
            auto arr = array(vector.size(), [&] (int k)
                        {
                            auto s = vector_value_type(0);
                            for ( int n in range(1, vector.size()) )
                                s += vector[n] * cos(radian(pi * (n-0.5) * (k-0.5) / vector.size()));
                            return s;
                        });
            return arr *= sqrt(2.0 / arr.size());
        }

        else
            static_assert(false, "unrecognized dct type (with supported = DCT-I, DCT-II, DCT-III, DCT-IV)");
    }
}