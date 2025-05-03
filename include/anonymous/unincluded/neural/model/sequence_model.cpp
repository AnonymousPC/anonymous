template < layer_type... types >
constexpr array_type auto sequence_model<types...>::forward ( const array_type auto& inputs )
{
    return self.tuplewise_forward(inputs);
}

template < layer_type... types >
constexpr array_type auto sequence_model<types...>::forward ( array_type auto inputs, optimizer_type auto& optimizer )
{
    return self.tuplewise_forward(std::move(inputs), optimizer);
}

template < layer_type... types >
constexpr void sequence_model<types...>::backward ( const loss_type auto& losses, optimizer_type auto& optimizer )
{
    return self.tuplewise_backward(losses, optimizer);
}


template < layer_type... types >
template < int index >
constexpr auto sequence_model<types...>::tuplewise_forward ( const auto& inputs ) const
{
    if constexpr ( index <= sizeof...(types) )
        return self.tuplewise_forward<index+1>(self[constexpr_index<index>()].forward(inputs));
    else
        return inputs;
}

template < layer_type... types >
template < int index >
constexpr auto sequence_model<types...>::tuplewise_forward ( auto inputs, auto& optimizer ) const
{
    if constexpr ( index <= sizeof...(types) )
        return self.tuplewise_forward<index+1>(self[constexpr_index<index>()].forward(std::move(inputs), optimizer[constexpr_index<index>()]), optimizer);
    else
        return inputs;
}

template < layer_type... types >
template < int index >
constexpr void sequence_model<types...>::tuplewise_backward ( const auto& losses, auto& optimizer )
{
    if constexpr ( index >= 1 )
    {
        if constexpr ( loss_type<decay<decltype(losses)>> )
            if constexpr ( requires { self[constexpr_index<index>()].backward(losses, optimizer[constexpr_index<index>()]); } ) // Instead of loss.grad().
                return self.tuplewise_backward<index-1>(self[constexpr_index<index>()].backward(losses,        optimizer[constexpr_index<index>()]), optimizer);
            else
                return self.tuplewise_backward<index-1>(self[constexpr_index<index>()].backward(losses.grad(), optimizer[constexpr_index<index>()]), optimizer);

        else if constexpr ( array_type<decay<decltype(losses)>> )
            return self.tuplewise_backward<index-1>(self[constexpr_index<index>()].backward(losses, optimizer[constexpr_index<index>()]), optimizer);

        else
            static_assert(false, "losses is neither loss_type nor array_type");
    }
}