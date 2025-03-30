#pragma once

file_bmp& file_bmp::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, path(self), boost::gil::bmp_tag(), depth());

    return self;
}

file_bmp& file_bmp::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, path(self), boost::gil::bmp_tag(), depth());

    return self;
}

int& file_bmp::depth ( )
{
    return image_depth;
}

const int& file_bmp::depth ( ) const
{
    return image_depth;
}
