#pragma once

namespace std
{
    template < class type, size_t len >
    class inplace_vector
        : public vector<type>
    {

    };

} // namespace std
