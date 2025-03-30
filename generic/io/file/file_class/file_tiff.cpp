#pragma once

file_tiff& file_tiff::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, path(self), boost::gil::tiff_tag(), depth());

    return self;
}

file_tiff& file_tiff::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, path(self), boost::gil::tiff_tag(), depth());

    return self;
}

int& file_tiff::depth ( )
{
    return image_depth;
}

const int& file_tiff::depth ( ) const
{
    return image_depth;
}
