#pragma once

namespace detail
{
    template < class type, class... types >
    std::string opencl_create_with_source ( const char* src )
    {
        let str = std::regex_replace(src, std::regex("\\btype\\b"), typeid(demangle(type)));
    }

} // namespace detail
