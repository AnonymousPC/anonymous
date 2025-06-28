template < class type >
class cuda::accessor_type
{
    public: // Typedef
        using offset_policy    = accessor_type;
        using element_type     = cuda::template value_type<type>;
        using reference        = cuda::template reference <type>;
        using data_handle_type = cuda::template pointer   <type>;

    public: // Member
        constexpr reference        access ( data_handle_type, size_t ) const;
        constexpr data_handle_type offset ( data_handle_type, size_t ) const;
};

#include "accessor_type.cpp"