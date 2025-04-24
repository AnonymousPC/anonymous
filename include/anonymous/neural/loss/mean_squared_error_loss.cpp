template < array_type type >
    requires float_type<typename type::value_type>
constexpr mean_squared_error_loss<type>::mean_squared_error_loss ( type init_outputs, type init_labels )
    extends outputs ( std::move ( init_outputs ) ),
            labels  ( std::move ( init_labels  ) )
{
    if ( from().shape() != to().shape() )
        throw math_error("mse_loss between outputs (with shape = {}) and labels (with shape = {}) must have same shapes", from().shape(), to().shape());
}

template < array_type type >
    requires float_type<typename type::value_type>
template < array_type type2 >
constexpr mean_squared_error_loss<type>::operator mean_squared_error_loss<type2> ( ) const
{
    return mean_squared_error_loss<type2> ( from(), to() );
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr const type& mean_squared_error_loss<type>::from ( ) const
{
    return outputs;
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr const type& mean_squared_error_loss<type>::to ( ) const
{
    return labels;
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr type mean_squared_error_loss<type>::grad ( ) const
{
    return from() - to();
}

template < array_type type >
    requires float_type<typename type::value_type>
constexpr typename mean_squared_error_loss<type>::value_type mean_squared_error_loss<type>::value ( ) const
{
    auto losses = from() - to();

    if constexpr ( type::dimension() == 1 )
    {
        auto avg = losses.average();
        return losses.average([&] (const auto& loss) { return (loss - avg) * (loss - avg); });
    }

    else if constexpr ( type::dimension() == 2 )
    {
        return losses.average([&] (const auto& sample_loss)
                              {
                                  auto avg = sample_loss.average();
                                  return sample_loss.average([&] (const auto& loss) { return (loss - avg) * (loss - avg); });
                              });
    }

    else
        static_assert(false, "loss.grad().shape() >= 3 is undesigned currently");
}