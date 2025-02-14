#pragma once

file_jpg::file_jpg ( const char* pth )
{
    open(pth);
}

file_jpg::file_jpg ( const path& pth )
{
    open(pth);
}

file_jpg& file_jpg::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, path(self), boost::gil::jpeg_tag(), depth());

    return self;
}

file_jpg& file_jpg::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, path(self), boost::gil::jpeg_tag(), depth());

    return self;
}

int& file_jpg::depth ( )
{
    return image_depth;
}

const int& file_jpg::depth ( ) const
{
    return image_depth;
}
