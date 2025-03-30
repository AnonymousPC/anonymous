#pragma once

file_png& file_png::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, path(self), boost::gil::png_tag(), depth());

    return self;
}

file_png& file_png::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, path(self), boost::gil::png_tag(), depth());

    return self;
}

int& file_png::depth ( )
{
    return image_depth;
}

const int& file_png::depth ( ) const
{
    return image_depth;
}
