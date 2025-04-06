#pragma once

inline file_tiff::file_tiff ( path pth )
{
    open(pth);
}

inline file_tiff& file_tiff::open ( path pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, self.operator path(), boost::gil::tiff_tag(), depth());

    return self;
}

inline file_tiff& file_tiff::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, self.operator path(), boost::gil::tiff_tag(), depth());

    return self;
}

inline file_tiff& file_tiff::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    matrix<color>::clear();

    return self;
}

inline int& file_tiff::depth ( )
{
    return image_depth;
}

inline const int& file_tiff::depth ( ) const
{
    return image_depth;
}
