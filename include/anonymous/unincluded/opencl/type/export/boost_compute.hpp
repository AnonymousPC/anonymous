template < class type >
    requires requires ( type it ) 
    {
        { it->get_buffer() } -> std::same_as<boost::compute::buffer>;
        { it->get_index()  } -> std::same_as<size_t>;
    }                                                  
struct is_device_iterator<type>
    extends public boost::true_type
{
    
};