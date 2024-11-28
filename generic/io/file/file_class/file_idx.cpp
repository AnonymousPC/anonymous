#pragma once

// Header ( declaration )

struct file_idx::info_header
{
    uint16_t         magic_num = 0x0;  // Always set as 0.
    uint8_t          type      = 0x08; // Shows the data-type, where { 0x08: uint8_t, 0x09: int8_t, 0x0b: int16_t, 0x0c: int32_t, 0x0d: float32_t, 0x0e: float64_t }.
    uint8_t          dimension = 0;    // Shows the data-dimension.
    vector<uint32_t> shape     = {};   // Shows the data-shape.
};




/// Class file_idx

// Core

file_idx::file_idx ( const char* pth )
{
    open(pth);
}

file_idx::file_idx ( const path& pth )
{
    open(pth);
}

// Interface (override)

file_idx& file_idx::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);
    let stream = file_stream(self.file_interface<file_idx>::operator path(), file_stream::read_only(true)); // As base-class any is convertible to path.

    // Read header.
    let info_head = info_header();
    stream >> info_head;
    if ( info_head.magic_num != 0x0 )
        throw file_error("cannot open idx-file: magic_num mismatches (with pos = [1,2]th-byte, read = {:#x}, expected = 0x0)", info_head.magic_num);
    if ( not set<uint8_t>{0x08, 0x09, 0x0b, 0x0c, 0x0d, 0x0e}.contains(info_head.type) )
        throw file_error("cannot open idx-file: type not supported (with pos = 3rd-byte, read = {:#x}, expected = 0x08(uint8_t), 0x09(int8_t), 0x0b(int16_t), 0x0c(int32_t), 0x0d(float32_t), 0x0e(float64_t))", info_head.type);

    // Read data.
    if ( info_head.dimension == 1 )
    {
        if ( info_head.type == 0x08 )
            static_cast<any&>(self) = read<uint8_t,1>  (stream, info_head.shape);
        else if ( info_head.type == 0x09 )
            static_cast<any&>(self) = read<int8_t,1>   (stream, info_head.shape);
        else if ( info_head.type == 0x0b )
            static_cast<any&>(self) = read<int16_t,1>  (stream, info_head.shape);
        else if ( info_head.type == 0x0c )
            static_cast<any&>(self) = read<int32_t,1>  (stream, info_head.shape);
        else if ( info_head.type == 0x0d )
            static_cast<any&>(self) = read<float32_t,1>(stream, info_head.shape);
        else if ( info_head.type == 0x0e )
            static_cast<any&>(self) = read<float64_t,1>(stream, info_head.shape);
    }

    else if ( info_head.dimension == 2 )
    {
        if ( info_head.type == 0x08 )
            static_cast<any&>(self) = read<uint8_t,2>  (stream, info_head.shape);
        else if ( info_head.type == 0x09 )
            static_cast<any&>(self) = read<int8_t,2>   (stream, info_head.shape);
        else if ( info_head.type == 0x0b )
            static_cast<any&>(self) = read<int16_t,2>  (stream, info_head.shape);
        else if ( info_head.type == 0x0c )
            static_cast<any&>(self) = read<int32_t,2>  (stream, info_head.shape);
        else if ( info_head.type == 0x0d )
            static_cast<any&>(self) = read<float32_t,2>(stream, info_head.shape);
        else if ( info_head.type == 0x0e )
            static_cast<any&>(self) = read<float64_t,2>(stream, info_head.shape);
    }

    else if ( info_head.dimension == 3 )
    {
        if ( info_head.type == 0x08 )
            static_cast<any&>(self) = read<uint8_t,3>  (stream, info_head.shape);
        else if ( info_head.type == 0x09 )
            static_cast<any&>(self) = read<int8_t,3>   (stream, info_head.shape);
        else if ( info_head.type == 0x0b )
            static_cast<any&>(self) = read<int16_t,3>  (stream, info_head.shape);
        else if ( info_head.type == 0x0c )
            static_cast<any&>(self) = read<int32_t,3>  (stream, info_head.shape);
        else if ( info_head.type == 0x0d )
            static_cast<any&>(self) = read<float32_t,3>(stream, info_head.shape);
        else if ( info_head.type == 0x0e )
            static_cast<any&>(self) = read<float64_t,3>(stream, info_head.shape);
    }

    else
        throw file_error("cannot open idx-file {}: dimension not supported (with write = {}, expected = 1, 2, 3)", path(self), info_head.dimension);

    return self;
}

file_idx& file_idx::save ( )
{
    // Save file.
    file_interface::save();
    let stream = file_stream(self.file_interface<file_idx>::operator path(), file_stream::write_only(true), file_stream::erase(true)); // As base-class any is convertible to path.

    // Write header and data
    if ( self.type() == typeid(array<uint8_t,1>) )
        write<uint8_t,1>  (stream, self.value<array<uint8_t,1>>());
    else if ( self.type() == typeid(array<int8_t,1>) )
        write<int8_t,1>   (stream, self.value<array<int8_t,1>>());
    else if ( self.type() == typeid(array<int16_t,1>) )
        write<int16_t,1>  (stream, self.value<array<int16_t,1>>());
    else if ( self.type() == typeid(array<int32_t,1>) )
        write<int32_t,1>  (stream, self.value<array<int32_t,1>>());
    else if ( self.type() == typeid(array<float32_t,1>) )
        write<float32_t,1>(stream, self.value<array<float32_t,1>>());
    else if ( self.type() == typeid(array<float64_t,1>) )
        write<float64_t,1>(stream, self.value<array<float64_t,1>>());

    else if ( self.type() == typeid(array<uint8_t,2>) )
        write<uint8_t,2>  (stream, self.value<array<uint8_t,2>>());
    else if ( self.type() == typeid(array<int8_t,2>) )
        write<int8_t,2>   (stream, self.value<array<int8_t,2>>());
    else if ( self.type() == typeid(array<int16_t,2>) )
        write<int16_t,2>  (stream, self.value<array<int16_t,2>>());
    else if ( self.type() == typeid(array<int32_t,2>) )
        write<int32_t,2>  (stream, self.value<array<int32_t,2>>());
    else if ( self.type() == typeid(array<float32_t,2>) )
        write<float32_t,2>(stream, self.value<array<float32_t,2>>());
    else if ( self.type() == typeid(array<float64_t,2>) )
        write<float64_t,2>(stream, self.value<array<float64_t,2>>());

    else if ( self.type() == typeid(array<uint8_t,3>) )
        write<uint8_t,3>  (stream, self.value<array<uint8_t,3>>());
    else if ( self.type() == typeid(array<int8_t,3>) )
        write<int8_t,3>   (stream, self.value<array<int8_t,3>>());
    else if ( self.type() == typeid(array<int16_t,3>) )
        write<int16_t,3>  (stream, self.value<array<int16_t,3>>());
    else if ( self.type() == typeid(array<int32_t,3>) )
        write<int32_t,3>  (stream, self.value<array<int32_t,3>>());
    else if ( self.type() == typeid(array<float32_t,3>) )
        write<float32_t,3>(stream, self.value<array<float32_t,3>>());
    else if ( self.type() == typeid(array<float64_t,3>) )
        write<float64_t,3>(stream, self.value<array<float64_t,3>>());

    else
        throw file_error("cannot save idx-file {}: type or dimension not supported (with write = {}, expected = [[array::value_type = uint8_t, int8_t, int16_t, int32_t, float32_t, float64_t, array::dimension = 1, 2, 3]])", path(self), self.type());

    return self;
}




// Auxiliary

template < class type, int dimension, bool first >
array<type,dimension> file_idx::read ( auto&& stream, const auto& shp )
{
    if constexpr ( dimension == 1 )
    {
        if constexpr ( first )
            return views::binary_istream<type,std::endian::big>(stream/*non-view*/)
                 | std::ranges::to<array<type>>(shp[1]);

        else
            return stream/*chunked-binary-istream-view*/
                 | std::ranges::to<array<type>>(shp[1]);
    }

    else if constexpr ( dimension >= 2 )
    {
        if constexpr ( first )
            return array<type,dimension>(
                   views::chunked_binary_istream<type,std::endian::big>(stream/*non-view*/, shp[2,-1].product())
                 | std::views::transform([&] (const auto& chunked_stream)
                     {
                         return read<type,dimension-1,false>(chunked_stream, shp[2,-1]);
                     })
                 | std::ranges::to<array<array<type,dimension-1>>>(shp[1]));

        else
            return array<type,dimension>(
                   stream/*chunked-binary-istream-view*/
                 | std::views::chunk(shp[2,-1].product())
                 | std::views::transform([&] (const auto& chunked_stream)
                     {
                         return read<type,dimension-1,false>(chunked_stream, shp[2,-1]);
                     })
                 | std::ranges::to<array<array<type,dimension-1>>>(shp[1]));
    }
}

template < class type, int dimension, bool first >
void file_idx::write ( auto&& stream, const auto& arr )
{
    if constexpr ( first )
        stream << info_header
        {
            .type = std::same_as<type,uint8_t>   ? 0x08 otherwise
                    std::same_as<type,int8_t>    ? 0x09 otherwise
                    std::same_as<type,int16_t>   ? 0x0b otherwise
                    std::same_as<type,int32_t>   ? 0x0c otherwise
                    std::same_as<type,float32_t> ? 0x0d otherwise
                  /*std::is_same<type,float64_t>*/ 0x0e,
            .dimension = dimension,
            .shape = arr.shape()
        };

    if constexpr ( dimension == 1 )
        arr | std::ranges::to<views::binary_ostream<type,std::endian::big>>(std::ref(stream));

    else if constexpr ( dimension >= 2 ) // Not good.
        arr | std::views::transform([&] (const auto& chunked_data)
                {
                    return write_aux(chunked_data);
                })
            | std::ranges::to<views::chunked_binary_ostream<type,std::endian::big>>(std::ref(stream), arr.shape()[2,-1].product());
}

decltype(auto) file_idx::write_aux ( const auto& arr )
{
    if constexpr ( arr.dimension() == 1 )
        return arr;
    else if constexpr ( arr.dimension() == 2 )
        return arr | std::views::join;
    else
        return arr | std::views::transform([] (const auto& chunked_data)
                       {
                           return write_aux(chunked_data);
                       })
                   | std::views::join;
}




// Header

file_stream& operator >> ( file_stream& left, file_idx::info_header& right )
{
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::big>(left) >> right.magic_num;
    ranges::binary_istream_view<file_stream,uint8_t, std::endian::big>(left) >> right.type >> right.dimension;
    right.shape.resize(right.dimension);
    for ( auto& size in right.shape )
        ranges::binary_istream_view<file_stream,uint32_t,std::endian::big>(left) >> size;
    return left;
}

file_stream& operator << ( file_stream& left, const file_idx::info_header& right )
{
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::big>(left) << right.magic_num;
    ranges::binary_ostream_view<file_stream,uint8_t, std::endian::big>(left) << right.type << right.dimension;
    for ( const auto& size in right.shape )
        ranges::binary_ostream_view<file_stream,uint32_t,std::endian::big>(left) << size;
    return left;
}
