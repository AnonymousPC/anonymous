namespace detail
{
    template < std::endian endian, class type = void >
    constexpr bool requires_byteswap =
        sizeof(type) >= 2 and
        ( ( std::endian::native == std::endian::little and endian == std::endian::big    ) or
          ( std::endian::native == std::endian::big    and endian == std::endian::little ) );
}