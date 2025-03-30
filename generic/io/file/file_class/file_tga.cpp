#pragma once

file_tga& file_tga::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, path(self), boost::gil::targa_tag(), depth());

    return self;
}

file_tga& file_tga::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, path(self), boost::gil::targa_tag(), depth());

    return self;
}

int& file_tga::depth ( )
{
    return image_depth;
}

const int& file_tga::depth ( ) const
{
    return image_depth;
}
