template < array_type type >
    requires floating_point<typename type::value_type>
constexpr binary_cross_entropy_loss<type>::binary_cross_entropy_loss ( type init_outputs, type init_labels )
    extends outputs ( std::move ( init_outputs ) ),
            labels  ( std::move ( init_labels  ) )
{
    if ( from().shape() != to().shape() )
        throw math_error("bce_loss between outputs (with shape = {}) and labels (with shape = {}) must have same shapes", from().shape(), to().shape());
}

template < array_type type >
    requires floating_point<typename type::value_type>
template < array_type type2 >
constexpr binary_cross_entropy_loss<type>::operator binary_cross_entropy_loss<type2> ( ) const
{
    return binary_cross_entropy_loss<type2> ( from(), to() );
}

template < array_type type >
    requires floating_point<typename type::value_type>
constexpr const type& binary_cross_entropy_loss<type>::from ( ) const
{
    return outputs;
}

template < array_type type >
    requires floating_point<typename type::value_type>
constexpr const type& binary_cross_entropy_loss<type>::to ( ) const
{
    return labels;
}

template < array_type type >
    requires floating_point<typename type::value_type>
constexpr type binary_cross_entropy_loss<type>::grad ( ) const
{
    static_assert(false, "not coded yet");
}

template < array_type type >
    requires floating_point<typename type::value_type>
constexpr typename binary_cross_entropy_loss<type>::value_type binary_cross_entropy_loss<type>::value ( ) const
{
    static_assert(false, "not coded yet");
//    auto loss = value_type(0);
//    for ( int i in range(from().size()) )
//        if constexpr ( type::dimension() == 1 )
//            loss += to()[i] * ln(from()[i]) + (1 - to()[i]) * ln(1 - from()[i]);
//        else
//            loss += to().flatten()[i] * ln(from().flatten()[i]) + (1 - to().flatten()[i]) * ln(1 - from().flatten()[i]);
//    return -loss;
}