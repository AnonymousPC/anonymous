template < class container, class type, int dim, class device >
class array_algo;

namespace detail
{
    enum array_attribute
    {
        rows_attribute,
        columns_attribute,
        transpose_attribute 
    };

    template < int dim >
    class array_shape;

    template < class type, int dim, class device >
    class array_lower;

    template < class type, int dim, class device >
    class array_upper;

    template < class type, int dim, class device >
    class array_uppers;

    template < class type, int dim, class device >
    class array_info;

    template < class type, int dim, class device >
    class transform_to_array;
    
} // namespace detail
