namespace detail
{
    string get_boost_gil_tag_name     (                             auto       );
    void   read_from_boost_gil_header (       matrix<color>&, path, auto, int& );
    void   read_from_boost_gil        (       matrix<color>&, path, auto, int& );    
    void   write_to_boost_gil         ( const matrix<color>&, path, auto, int  );

    template < class value_type, class layout_type > void read_from_boost_gil_impl (       matrix<color>&, path, auto, int  );
    template < class value_type, class layout_type > void write_to_boost_gil_impl  ( const matrix<color>&, path, auto, int  );
}

string detail::get_boost_gil_tag_name ( auto tag )
{
    if constexpr ( same_as<decltype(tag),boost::gil::bmp_tag> )
        return "bmp";
    else if constexpr ( same_as<decltype(tag),boost::gil::jpeg_tag> )
        return "jpg";
    else if constexpr ( same_as<decltype(tag),boost::gil::png_tag> )
        return "png";
    else if constexpr ( same_as<decltype(tag),boost::gil::pnm_tag> )
        return "pnm";
    else if constexpr ( same_as<decltype(tag),boost::gil::targa_tag> )
        return "tga";
    else if constexpr ( same_as<decltype(tag),boost::gil::tiff_tag> )
        return "tiff";
    else
        static_assert(false, "unrecognized tag");
}

void detail::read_from_boost_gil_header ( matrix<color>&, path pth, auto tag, int& dep )
{
    try
    {
        if constexpr ( same_as<decltype(tag),boost::gil::bmp_tag> )
            dep = boost::gil::read_image_info(pth.c_str(), tag)._info._bits_per_pixel;

        else if constexpr ( same_as<decltype(tag),boost::gil::jpeg_tag> )
        {
            auto info_head = boost::gil::read_image_info(pth.c_str(), tag)._info;
            dep = info_head._data_precision * info_head._num_components;
        }

        else if constexpr ( same_as<decltype(tag),boost::gil::png_tag> )
        {
            auto info_head = boost::gil::read_image_info(pth.c_str(), tag)._info;
            dep = info_head._bit_depth * info_head._num_channels;
        }

        else if constexpr ( same_as<decltype(tag),boost::gil::pnm_tag> )
        {
            auto info_head = boost::gil::read_image_info(pth.c_str(), tag)._info;
            dep = info_head._type == boost::gil::pnm_image_type::mono_asc_t::value  or info_head._type == boost::gil::pnm_image_type::mono_bin_t::value  ? 1                                          :
                  info_head._type == boost::gil::pnm_image_type::gray_asc_t::value  or info_head._type == boost::gil::pnm_image_type::gray_bin_t::value  ? 1 * int(log2(int(info_head._max_value+1))) :
                                   /*boost::gil::pnm_image_type::color_asc_t::value or info_head._type == boost::gil::pnm_image_type::color_bin_t::value*/ 3 * int(log2(int(info_head._max_value+1)));
        }

        else if constexpr ( same_as<decltype(tag),boost::gil::targa_tag> )
            dep = boost::gil::read_image_info(pth.c_str(), tag)._info._bits_per_pixel;

        else if constexpr ( same_as<decltype(tag),boost::gil::tiff_tag> )
        {
            auto info_head = boost::gil::read_image_info(pth.c_str(), tag)._info;
            dep = info_head._bits_per_sample * info_head._samples_per_pixel;
        }

        else
            static_assert(false, "unrecognized tag");
    }
    catch ( const std::ios_base::failure& e )
    {
        throw file_error("cannot open {}-file {}", get_boost_gil_tag_name(tag), pth.c_str()).from(e);
    }
}

void detail::read_from_boost_gil ( matrix<color>& image, path pth, auto tag, int& dep )
{
    read_from_boost_gil_header(image, pth, tag, dep);

    dep == 24  ? read_from_boost_gil_impl<uint8_t, boost::gil::rgb_layout_t >(image, pth, tag, dep) :
    dep == 32  ? read_from_boost_gil_impl<uint8_t, boost::gil::rgba_layout_t>(image, pth, tag, dep) :
    dep == 48  ? read_from_boost_gil_impl<uint16_t,boost::gil::rgb_layout_t >(image, pth, tag, dep) :
    dep == 64  ? read_from_boost_gil_impl<uint16_t,boost::gil::rgba_layout_t>(image, pth, tag, dep) :
                 throw file_error("cannot open {}-file {}: depth not supported (with depth = {})", get_boost_gil_tag_name(tag), pth, dep);
}

void detail::write_to_boost_gil ( const matrix<color>& image, path pth, auto tag, int dep )
{
    dep == 24  ? write_to_boost_gil_impl<uint8_t, boost::gil::rgb_layout_t >(image, pth, tag, dep) :
    dep == 32  ? write_to_boost_gil_impl<uint8_t, boost::gil::rgba_layout_t>(image, pth, tag, dep) :
    dep == 48  ? write_to_boost_gil_impl<uint16_t,boost::gil::rgb_layout_t >(image, pth, tag, dep) :
    dep == 64  ? write_to_boost_gil_impl<uint16_t,boost::gil::rgba_layout_t>(image, pth, tag, dep) :
                 throw file_error("cannot save {}-file {}: depth not supported (with depth = {})", get_boost_gil_tag_name(tag), pth, dep);;
}







template < class value_type, class layout_type >
void detail::read_from_boost_gil_impl ( matrix<color>& image, path pth, auto tag, int dep )
{
    using gil_pixel_type = boost::gil::pixel<value_type,layout_type>;
    using gil_image_type = boost::gil::image<gil_pixel_type,false,std::allocator<value_type>>;
    auto   gil_image      = gil_image_type();

    if constexpr ( requires { boost::gil::read_image(pth.c_str(), gil_image, tag); } )
    {
        // Read image.
        try
        {
            boost::gil::read_image(pth.c_str(), gil_image, tag);
        }
        catch ( const std::ios_base::failure& e )
        {
            throw file_error("cannot open {}-file {}", get_boost_gil_tag_name(tag), pth).from(e);
        }

        // Convert image.
        auto gil_image_view = boost::gil::view(gil_image);
        image.resize(int(gil_image_view.height()), int(gil_image_view.width()));
        std::ranges::move(
            gil_image_view
                | std::views::transform([] (const auto& pixel)
                    {
                        if constexpr ( same_as<layout_type,boost::gil::gray_layout_t> )
                            return color(float(pixel[0])/std::numeric_limits<value_type>::max(),
                                         float(pixel[0])/std::numeric_limits<value_type>::max(),
                                         float(pixel[0])/std::numeric_limits<value_type>::max());

                        else if constexpr ( same_as<layout_type,boost::gil::rgb_layout_t> )
                            return color(float(pixel[0])/std::numeric_limits<value_type>::max(),
                                         float(pixel[1])/std::numeric_limits<value_type>::max(),
                                         float(pixel[2])/std::numeric_limits<value_type>::max());

                        else if constexpr ( same_as<layout_type,boost::gil::rgba_layout_t> )
                            return color(float(pixel[0])/std::numeric_limits<value_type>::max(),
                                         float(pixel[1])/std::numeric_limits<value_type>::max(),
                                         float(pixel[2])/std::numeric_limits<value_type>::max(),
                                         float(pixel[3])/std::numeric_limits<value_type>::max());
                   }),
            image.flatten().begin()
        );
    }

    else
        throw file_error("cannot open {}-file {}: depth not supported (with depth = {})", get_boost_gil_tag_name(tag), pth, dep);
}

template < class value_type, class layout_type >
void detail::write_to_boost_gil_impl ( const matrix<color>& image, path pth, auto tag, int dep )
{
    using gil_pixel_type = boost::gil::pixel<value_type,layout_type>;
    using gil_image_type = boost::gil::image<gil_pixel_type,false,std::allocator<value_type>>;
    auto   gil_image      = gil_image_type(image.column(), image.row());

    if constexpr ( requires { boost::gil::write_view(pth.c_str(), boost::gil::view(gil_image), tag); } )
    {
        // Convert image.
        auto gil_image_view = boost::gil::view(gil_image);
        std::ranges::copy(
            image.flatten()
                | std::views::transform([&] (const auto& pixel)
                    {
                        if ( pixel.red()   < 0 or pixel.red()   > 1 or
                             pixel.green() < 0 or pixel.green() > 1 or
                             pixel.blue()  < 0 or pixel.blue()  > 1 or 
                             pixel.alpha() < 0 or pixel.alpha() > 1 )
                            throw file_error("cannot save {}-file {}: value out of range (with pixel.red = {}, pixel.green = {}, pixel.blue = {}, pixel.alpha = {})", get_boost_gil_tag_name(tag), pth, pixel.red(), pixel.green(), pixel.blue(), pixel.alpha());

                        if constexpr ( same_as<layout_type,boost::gil::gray_layout_t> )
                            return gil_pixel_type(std::round((pixel.red() + pixel.green() + pixel.blue()) * pixel.alpha() / 3 * std::numeric_limits<value_type>::max()));
        
                        else if constexpr ( same_as<layout_type,boost::gil::rgb_layout_t> )
                            return gil_pixel_type(std::round(pixel.red  () * pixel.alpha() * std::numeric_limits<value_type>::max()),
                                                  std::round(pixel.green() * pixel.alpha() * std::numeric_limits<value_type>::max()),
                                                  std::round(pixel.blue () * pixel.alpha() * std::numeric_limits<value_type>::max()));
        
                        else if constexpr ( same_as<layout_type,boost::gil::rgba_layout_t> )
                            return gil_pixel_type(std::round(pixel.red  () * std::numeric_limits<value_type>::max()),
                                                  std::round(pixel.green() * std::numeric_limits<value_type>::max()),
                                                  std::round(pixel.blue () * std::numeric_limits<value_type>::max()),
                                                  std::round(pixel.alpha() * std::numeric_limits<value_type>::max()));
                    }),
            gil_image_view.begin()
        );

        // Write image.
        try
        {
            boost::gil::write_view(pth.c_str(), gil_image_view, tag);
        }
        catch ( const std::ios_base::failure& e )
        {
            throw file_error("cannot save {}-file {}", get_boost_gil_tag_name(tag), pth).from(e);
        }
    }

    else
        throw file_error("cannot save {}-file {}: depth not supported (with depth = {})", get_boost_gil_tag_name(tag), pth, dep);
}





#undef throw_unsupported_read_depth_error
#undef read_if_supported
#undef throw_unsupported_write_depth_error
#undef write_if_supported