template < class type, int dim, class device >
class detail::transform_to_array
{
    public:
        constexpr static       array<type,dim,device>& operator() (       detail::array_upper<type,dim,device>&  );
        constexpr static const array<type,dim,device>& operator() ( const detail::array_upper<type,dim,device>&  );
};