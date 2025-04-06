#pragma once

inline file_png::file_png ( path pth )
{
    open(pth);
}

inline file_png& file_png::open ( path pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, self.operator path(), boost::gil::png_tag(), depth());

    return self;
}

inline file_png& file_png::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, self.operator path(), boost::gil::png_tag(), depth());

    return self;
}

inline file_png& file_png::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    matrix<color>::clear();

    return self;
}

inline int& file_png::depth ( )
{
    return image_depth;
}

inline const int& file_png::depth ( ) const
{
    return image_depth;
}
