#pragma once

namespace detail
{
    template < class type, int dim, class device >
    struct array_lower;

    template < class type, class device >
    struct array_upper<type,1,device>
    {
        static_assert(false, "not )
    }

    
} // namespace detail
