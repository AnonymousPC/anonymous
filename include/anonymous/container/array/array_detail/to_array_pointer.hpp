class detail::to_array_pointer
{
    public:
        template < class type, int dim, class device > constexpr static       array<type,dim,device>& operator() (       detail::array_upper<type,dim,device>& );
        template < class type, int dim, class device > constexpr static const array<type,dim,device>& operator() ( const detail::array_upper<type,dim,device>& );
        template < class type, int dim, class device > constexpr static       array<type,dim,device>* operator() (       detail::array_upper<type,dim,device>* );
        template < class type, int dim, class device > constexpr static const array<type,dim,device>* operator() ( const detail::array_upper<type,dim,device>* );
};