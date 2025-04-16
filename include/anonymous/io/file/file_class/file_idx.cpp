#pragma once

namespace detail
{
    struct file_idx_info_header
    {
        uint16_t         magic_num = 0x0;  // Always set as 0.
        uint8_t          type      = 0x08; // Shows the data-type, where { 0x08: uint8_t, 0x09: int8_t, 0x0b: int16_t, 0x0c: int32_t, 0x0d: float32_t, 0x0e: float64_t }.
        uint8_t          dimension = 0;    // Shows the data-dimension.
        vector<uint32_t> shape     = {};   // Shows the data-shape.
    };    

    template < class value_type, int dimension, bool first = true > auto           file_idx_read      ( auto&&, const static_array<int, dimension>& );
    template < class value_type, int dimension, bool first = true > void           file_idx_write     ( auto&&, const array<value_type,dimension>&  );
                                                                    decltype(auto) file_idx_write_aux ( const auto& /*data*/ );
                                                                    file_stream&   operator >>        ( file_stream&,       file_idx_info_header& );
                                                                    file_stream&   operator <<        ( file_stream&, const file_idx_info_header& );
    
} // namespace detail






file_idx::file_idx ( const path& pth )
{
    open(pth);
}

file_idx& file_idx::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);
    auto stream = file_stream(self.operator path(), file_stream::read_only(true));

    // Read header.
    auto info_head = detail::file_idx_info_header();
    stream >> info_head;
    if ( info_head.magic_num != 0x0 )
        throw file_error("cannot open idx-file: magic_num mismatches (with pos = [1,2]th-byte, magic_num = {:#x}, expected = 0x0)", info_head.magic_num);
    if ( not set<uint8_t>{0x08, 0x09, 0x0b, 0x0c, 0x0d, 0x0e}.contains(info_head.type) )
        throw file_error("cannot open idx-file: type not supported (with pos = 3rd-byte, type = {:#x}, expected = 0x08(uint8_t), 0x09(int8_t), 0x0b(int16_t), 0x0c(int32_t), 0x0d(float32_t), 0x0e(float64_t))", info_head.type);

    // Read data.
    if ( info_head.dimension == 1 )
    {
        if ( info_head.type == 0x08 )
            static_cast<any&>(self) = detail::file_idx_read<uint8_t,1>  (stream, info_head.shape);
        else if ( info_head.type == 0x09 )
            static_cast<any&>(self) = detail::file_idx_read<int8_t,1>   (stream, info_head.shape);
        else if ( info_head.type == 0x0b )
            static_cast<any&>(self) = detail::file_idx_read<int16_t,1>  (stream, info_head.shape);
        else if ( info_head.type == 0x0c )
            static_cast<any&>(self) = detail::file_idx_read<int32_t,1>  (stream, info_head.shape);
        else if ( info_head.type == 0x0d )
            static_cast<any&>(self) = detail::file_idx_read<float32_t,1>(stream, info_head.shape);
        else if ( info_head.type == 0x0e )
            static_cast<any&>(self) = detail::file_idx_read<float64_t,1>(stream, info_head.shape);
    }

    else if ( info_head.dimension == 2 )
    {
        if ( info_head.type == 0x08 )
            static_cast<any&>(self) = detail::file_idx_read<uint8_t,2>  (stream, info_head.shape);
        else if ( info_head.type == 0x09 )
            static_cast<any&>(self) = detail::file_idx_read<int8_t,2>   (stream, info_head.shape);
        else if ( info_head.type == 0x0b )
            static_cast<any&>(self) = detail::file_idx_read<int16_t,2>  (stream, info_head.shape);
        else if ( info_head.type == 0x0c )
            static_cast<any&>(self) = detail::file_idx_read<int32_t,2>  (stream, info_head.shape);
        else if ( info_head.type == 0x0d )
            static_cast<any&>(self) = detail::file_idx_read<float32_t,2>(stream, info_head.shape);
        else if ( info_head.type == 0x0e )
            static_cast<any&>(self) = detail::file_idx_read<float64_t,2>(stream, info_head.shape);
    }

    else if ( info_head.dimension == 3 )
    {
        if ( info_head.type == 0x08 )
            static_cast<any&>(self) = detail::file_idx_read<uint8_t,3>  (stream, info_head.shape);
        else if ( info_head.type == 0x09 )
            static_cast<any&>(self) = detail::file_idx_read<int8_t,3>   (stream, info_head.shape);
        else if ( info_head.type == 0x0b )
            static_cast<any&>(self) = detail::file_idx_read<int16_t,3>  (stream, info_head.shape);
        else if ( info_head.type == 0x0c )
            static_cast<any&>(self) = detail::file_idx_read<int32_t,3>  (stream, info_head.shape);
        else if ( info_head.type == 0x0d )
            static_cast<any&>(self) = detail::file_idx_read<float32_t,3>(stream, info_head.shape);
        else if ( info_head.type == 0x0e )
            static_cast<any&>(self) = detail::file_idx_read<float64_t,3>(stream, info_head.shape);
    }

    else
        throw file_error("cannot open idx-file {}: dimension not supported (with dimension = {}, expected = 1, 2, 3)", self.operator path(), info_head.dimension);

    return self;
}

file_idx& file_idx::save ( )
{
    // Save file.
    file_interface::save();
    auto stream = file_stream(self.operator path(), file_stream::write_only(true), file_stream::erase(true));

    // Write header.
    stream << info_header
    {
        .type = same_as<value_type,uint8_t>   ? 0x08 :
                same_as<value_type,int8_t>    ? 0x09 :
                same_as<value_type,int16_t>   ? 0x0b :
                same_as<value_type,int32_t>   ? 0x0c :
                same_as<value_type,float32_t> ? 0x0d :
            /*same_as<value_type,float64_t>*/ 0x0e,
        .dimension = dimension,
        .shape = arr.shape()
    };

    // Write data.
    if ( self.type() == typeid(array<uint8_t,1>) )
        file_idx_write<uint8_t,1>  (stream, self.value<array<uint8_t,1>>());
    else if ( self.type() == typeid(array<int8_t,1>) )
        file_idx_write<int8_t,1>   (stream, self.value<array<int8_t,1>>());
    else if ( self.type() == typeid(array<int16_t,1>) )
        file_idx_write<int16_t,1>  (stream, self.value<array<int16_t,1>>());
    else if ( self.type() == typeid(array<int32_t,1>) )
        file_idx_write<int32_t,1>  (stream, self.value<array<int32_t,1>>());
    else if ( self.type() == typeid(array<float32_t,1>) )
        file_idx_write<float32_t,1>(stream, self.value<array<float32_t,1>>());
    else if ( self.type() == typeid(array<float64_t,1>) )
        file_idx_write<float64_t,1>(stream, self.value<array<float64_t,1>>());

    else if ( self.type() == typeid(array<uint8_t,2>) )
        file_idx_write<uint8_t,2>  (stream, self.value<array<uint8_t,2>>());
    else if ( self.type() == typeid(array<int8_t,2>) )
        file_idx_write<int8_t,2>   (stream, self.value<array<int8_t,2>>());
    else if ( self.type() == typeid(array<int16_t,2>) )
        file_idx_write<int16_t,2>  (stream, self.value<array<int16_t,2>>());
    else if ( self.type() == typeid(array<int32_t,2>) )
        file_idx_write<int32_t,2>  (stream, self.value<array<int32_t,2>>());
    else if ( self.type() == typeid(array<float32_t,2>) )
        file_idx_write<float32_t,2>(stream, self.value<array<float32_t,2>>());
    else if ( self.type() == typeid(array<float64_t,2>) )
        file_idx_write<float64_t,2>(stream, self.value<array<float64_t,2>>());

    else if ( self.type() == typeid(array<uint8_t,3>) )
        file_idx_write<uint8_t,3>  (stream, self.value<array<uint8_t,3>>());
    else if ( self.type() == typeid(array<int8_t,3>) )
        file_idx_write<int8_t,3>   (stream, self.value<array<int8_t,3>>());
    else if ( self.type() == typeid(array<int16_t,3>) )
        file_idx_write<int16_t,3>  (stream, self.value<array<int16_t,3>>());
    else if ( self.type() == typeid(array<int32_t,3>) )
        file_idx_write<int32_t,3>  (stream, self.value<array<int32_t,3>>());
    else if ( self.type() == typeid(array<float32_t,3>) )
        file_idx_write<float32_t,3>(stream, self.value<array<float32_t,3>>());
    else if ( self.type() == typeid(array<float64_t,3>) )
        file_idx_write<float64_t,3>(stream, self.value<array<float64_t,3>>());

    else
        throw file_error("cannot save idx-file {}: type or dimension not supported (with dimension = {}, expected_type = uint8_t, int8_t, int16_t, int32_t, float32_t, float64_t, expected_dimension = 1, 2, 3)",
                         self.operator path(), self.type());

    return self;
}

file_idx& file_idx::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    any::operator=(nullptr);

    return self;
}











template < class value_type, int dimension, bool first >
array<value_type,dimension> detail::file_idx_read ( auto&& stream, const static_array<int,dimension>& shp )
{
    static_assert(same_as<typename array<value_type,dimension>::device_type::layout_type,std::layout_right>);
    auto arr = array<value_type,dimension>(shp);
    std::ranges::move(views::binary_istream<value_type,std::endian::big>(stream)
                          | std::views::take(shp.product()),
                      [&] { if constexpr ( dimension == 1 ) return arr.begin(); else return arr.flatten().begin(); });
    return arr;
}

template < class value_type, int dimension, bool first >
void detail::file_idx_write ( auto&& stream, const array<value_type,dimension>& arr )
{
    if constexpr ( first )


    if constexpr ( dimension == 1 )
        arr | std::ranges::to<views::binary_ostream<value_type,std::endian::big>>(std::ref(stream));

    else if constexpr ( dimension >= 2 )
        arr | std::views::transform([] (const auto& chunked_data) 
                {
                    return chunked | std::views::join;
                })
            | std::ranges::to<views::chunked_binary_ostream<value_type,std::endian::big>>(std::ref(stream), arr.shape().product() / arr.shape()[1]);
}

decltype(auto) file_idx::write_aux ( const auto& arr )
{
    if constexpr ( decay<decltype(arr)>::dimension() == 1 )
        return arr;
    else if constexpr ( decay<decltype(arr)>::dimension() == 2 )
        return arr | std::views::join;
    else
        return arr | std::views::transform([] (const auto& chunked_data) { return write_aux(chunked_data); })
                   | std::views::join;
}

file_stream& operator >> ( file_stream& left, file_idx::info_header& right )
{
    std::ranges::move(ranges::binary_istream_view<file_stream,uint16_t,std::endian::big>(left) | std::views::take(1), right.magic_num;
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
