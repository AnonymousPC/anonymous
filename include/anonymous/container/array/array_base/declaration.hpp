template < class container, class type, int dim, class device >
class array_algo;

namespace detail
{
    enum array_attribute
    {
        no_attribute,
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
    class array_info;

    template < class type, int dim, class device >
    class array_line_iterator;

    template < class type, int dim, class device >
    class array_line_const_iterator;
    
} // namespace detail
