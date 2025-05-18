template < int dim >
constexpr detail::array_shape<dim>::array_shape ( )
    extends std::array<int,dim>()
{
    
}

template < int dim >
constexpr detail::array_shape<dim>::array_shape ( integral auto... args )
    requires ( sizeof...(args) == dim )
    extends std::array<int,dim>({std::forward<decltype(args)>(args)...})
{

}

template < int dim >
constexpr int detail::array_shape<dim>::size ( )
{
    return dim;
}

template < int dim >
constexpr int& detail::array_shape<dim>::operator [] ( int pos )
{
    if constexpr ( debug )
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());

    return pos >= 0 ? std::array<int,dim>::operator[](pos-1)     :
                      std::array<int,dim>::operator[](pos+size());
}

template < int dim >
constexpr const int& detail::array_shape<dim>::operator [] ( int pos ) const
{
    if constexpr ( debug )
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());

    return pos >= 0 ? std::array<int,dim>::operator[](pos-1)     :
                      std::array<int,dim>::operator[](pos+size());
}