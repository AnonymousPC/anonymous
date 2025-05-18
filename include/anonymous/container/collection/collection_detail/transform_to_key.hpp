template < class type1, class type2, class device >
class detail::transform_to_key
{
    public:
        constexpr static device::template reference      <type1> operator() ( device::template reference      <typename device::template pair<const type1,type2>> );
        constexpr static device::template const_reference<type1> operator() ( device::template const_reference<typename device::template pair<const type1,type2>> );
};

#include "transform_to_key.cpp"