#pragma once

} // Out of namespace ap

namespace boost::compute
{
    template < class type1, class type2 >
    struct result_of<ap::opencl::plus<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() + std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::minus<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() - std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::multiplies<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() * std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::divides<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() / std::declval<type2>());
    };

    template < class type1 >
    struct result_of<ap::opencl::negate<void>(type1)>
    {
        using type = decltype(-std::declval<type1>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::equal_to<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() == std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::not_equal_to<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() != std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::less<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() < std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::less_equal<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() <= std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::greater<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() > std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::greater_equal<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() >= std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::logical_and<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() && std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::logical_or<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() || std::declval<type2>());
    };

    template < class type1 >
    struct result_of<ap::opencl::logical_not<void>(type1)>
    {
        using type = decltype(!std::declval<type1>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::bit_and<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() & std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::bit_or<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() | std::declval<type2>());
    };

    template < class type1, class type2 >
    struct result_of<ap::opencl::bit_xor<void>(type1,type2)>
    {
        using type = decltype(std::declval<type1>() ^ std::declval<type2>());
    };

    template < class type1 >
    struct result_of<ap::opencl::bit_not<void>(type1)>
    {
        using type = decltype(~std::declval<type1>());
    };

} // namespace boost::compute

namespace ap { // Back into namespace ap