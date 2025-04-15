#pragma once

namespace aux
{
    constexpr auto from_eigen ( const auto& );
    constexpr auto to_eigen   ( const auto& );
}

constexpr auto aux::from_eigen ( const auto& matrix )
{
    constexpr int dimension = not std::type_identity<matrix_type>::type::IsVectorAtCompileTime  ? 2 otherwise
                                  std::type_identity<matrix_type>::type::ColsAtCompileTime == 1 ? 1 otherwise
                                                                                                 -1;
    using value_type = conditional<not std::same_as<typename matrix_type::Scalar,decltype(std::complex(typename matrix_type::Scalar()))>,
                                   typename matrix_type::Scalar,
                                   complex<typename decltype(std::complex(typename matrix_type::Scalar()))::value_type>
                                  >;

    static_assert ( dimension == 1 or dimension == -1 or dimension == 2, "unhandlable dimension"  );
    static_assert ( number_type<value_type> or complex_type<value_type>, "unhandlable value_type" );

    if constexpr ( dimension == 1 or dimension == -1 )
    {
        if constexpr ( number_type<value_type> )
            return array<value_type,dimension> ( int(matrix.size()), [&] (int i) { return matrix(i-1); } );
        else if constexpr ( complex_type<value_type> )
            return array<value_type,dimension> ( int(matrix.size()), [&] (int i) { return value_type(matrix(i-1).real(), matrix(i-1).imag()); } );
    }

    else if constexpr ( dimension == 2 )
    {
        if constexpr ( number_type<value_type> )
            return array<value_type,dimension> ( int(matrix.rows()), int(matrix.cols()), [&] (int i, int j) { return matrix(i-1, j-1); } );
        else if constexpr ( complex_type<value_type> )
            return array<value_type,dimension> ( int(matrix.rows()), int(matrix.cols()), [&] (int i, int j) { return value_type(matrix(i-1, j-1).real(), matrix(i-1, j-1).imag()); } );
    }
}

constexpr auto aux::to_eigen ( const auto& matrix )
{
    constexpr int dimension = matrix.dimension();
    using value_type = matrix_value_type;

    static_assert ( dimension == 1 or dimension == -1 or dimension == 2, "unhandlable dimension"  );
    static_assert ( number_type<value_type> or complex_type<value_type>, "unhandlable value_type" );

    if constexpr ( dimension == 1 or dimension == -1 )
    {
        constexpr int row    = dimension == 1 ? Eigen::Dynamic otherwise 1;
        constexpr int column = dimension == 1 ? 1 otherwise Eigen::Dynamic;

        if constexpr ( number_type<matrix_value_type> )
        {
            let m = Eigen::Matrix<typename matrix_type::value_type,row,column> ( matrix.size() );
            for ( int i in range(matrix.size()) ) // TODO: Vectorize.
                m(i-1) = matrix[i];
            return m;
        }
        else if constexpr ( complex_type<value_type> )
        {
            let m = Eigen::Matrix<std::complex<typename matrix_type::value_type::value_type>,row,column> ( matrix.size() );
            for ( int i in range(matrix.size()) ) // TODO: Vectorize.
                m(i-1) = { matrix[i].real(), matrix[i].imag() };
            return m;
        }
    }

    else if constexpr ( matrix.dimension() == 2 )
    {
        if constexpr ( number_type<matrix_value_type> )
        {
            let m = Eigen::Matrix<typename matrix_type::value_type,Eigen::Dynamic,Eigen::Dynamic> ( matrix.row(), matrix.column() );
            for ( int i in range(matrix.row()) ) // TODO: Vectorize.
                for ( int j in range(matrix.column()) )
                    m(i-1, j-1) = matrix[i][j];
            return m;
        }
        else if constexpr ( complex_type<value_type> )
        {
            let m = Eigen::Matrix<std::complex<typename matrix_type::value_type::value_type>,Eigen::Dynamic,Eigen::Dynamic> ( matrix.row(), matrix.column() );
            for ( int i in range(matrix.row()) ) // TODO: Vectorize.
                for ( int j in range(matrix.column()) )
                    m(i-1, j-1) = { matrix[i][j].real(), matrix[i][j].imag() };
            return m;
        }
    }
}