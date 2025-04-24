template < array_type type >
    requires float_type<typename type::value_type>
constexpr cross_entropy_loss<type>::cross_entropy_loss ( type init_outputs, type init_labels )
    extends outputs ( std::move ( init_outputs ) ),
            labels  ( std::move ( init_labels  ) )
{
    if ( from().shape() != to().shape() )
        throw math_error("ce_loss between outputs (with shape = {}) and labels (with shape = {}) must have same shapes", from().shape(), to().shape());
}

template < array_type type >
    requires float_type<typename type::value_type>
template < array_type type2 >
constexpr cross_entropy_loss<type>::operator cross_entropy_loss<type2> ( ) const
{
    return cross_entropy_loss<type2> ( from(), to() );
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr const type& cross_entropy_loss<type>::from ( ) const
{
    return outputs;
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr const type& cross_entropy_loss<type>::to ( ) const
{
    return labels;
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr type cross_entropy_loss<type>::grad ( ) const
{
    static_assert(false, "not coded yet");
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr typename cross_entropy_loss<type>::value_type cross_entropy_loss<type>::value ( ) const
{
    static_assert(false, "not coded yet");
//    auto loss = value_type(0);
//    for ( int i in range(from().size()) )
//        if constexpr ( type::dimension() == 1 )
//            loss += to()[i] * ln(from()[i]);
//        else
//            loss += to().flatten()[i] * ln(from().flatten()[i]);
//    return -loss;
}