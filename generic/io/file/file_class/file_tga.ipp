#pragma once

inline file_tga::file_tga ( path pth )
{
    open(pth);
}

inline file_tga& file_tga::open ( path pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, self.operator path(), boost::gil::targa_tag(), depth());

    return self;
}

inline file_tga& file_tga::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, self.operator path(), boost::gil::targa_tag(), depth());

    return self;
}

inline file_tga& file_tga::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    matrix<color>::clear();

    return self;
}

inline int& file_tga::depth ( )
{
    return image_depth;
}

inline const int& file_tga::depth ( ) const
{
    return image_depth;
}
